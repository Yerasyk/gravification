#include <iostream>

#include <glad/glad.h> //OpenGL Functions
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "shader.h"

GLFWwindow* initializeWindow(int width, int height, const char* title){
    //Initialize glfw
    if(!glfwInit()){
        return nullptr;
    }

    // Request OpenGL 3.3 core when creating the window.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Create window and return pointer to that window
    GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (window == nullptr){
        glfwTerminate();
        return nullptr;
    }

    //Set current CONTEXT to window
    glfwMakeContextCurrent(window);

    //Loading OpenGL functions
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        glfwDestroyWindow(window);
        glfwTerminate();
        return nullptr;
    }

    return window;
}

void initializeImGui(GLFWwindow* window){
    //Init ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}
struct Settings
{
    bool wireFrame = false;
    float background[3] = {0.02f, 0.03f, 0.08f};
    bool usePulseShader = false;
    float pulseColor[3] = {1.0f, 1.0f, 1.0f};
} settings;

constexpr float PI = 3.14159265358979f;

int main()
{
    //Initialize window
    GLFWwindow* window = initializeWindow(800, 600, "Gravification");

    if (window == nullptr) {
        return 1;
    }

    //Init ImGui
    initializeImGui(window);

    ////////////////////////////////////////////////////////////////////////////////////////////////
    //ALL IN GAME STUFF

    //////////////////////////
    //Data
    
    //Square
    // float vertices[] = {
    //  0.5f,  0.5f, 0.0f,  // top right
    //  0.5f, -0.5f, 0.0f,  // bottom right
    // -0.5f, -0.5f, 0.0f,  // bottom left
    // -0.5f,  0.5f, 0.0f   // top left 
    // };

    // triangles side by side
    float vertices[] = {
     0.0f,  0.5f, 0.0f,  // top-top
     0.25f,  0.0f, 0.0f,  // middle-right
     -0.25f,  0.0f, 0.0f,  // middle-left
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    0.0f,  -0.5f, 0.0f   // bottom middle 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 2,   // first triangle
        1, 3, 5,    // second triangle
        2, 5, 4    // second triangle
    }; 
    // unsigned int indices1[] = {  // note that we start from 0!
    //     0, 1, 2   // first triangle
    // }; unsigned int indices2[] = {  // note that we start from 0!
    //     1, 3, 5    // second triangle
    // }; unsigned int indices3[] = {  // note that we start from 0!
    //     2, 5, 4    // second triangle
    // }; 
        
    //////////////////////////
    //Creating Vertex Buffer Object (copy data), Vertex Array Object (store attribute pointers), Element Buffer Object (store indices of vertices)
    unsigned int VBO, VAO, EBO;
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);
    
    //Creating Shader program: shad_out -> link -> shad_inp
    Shader shader1("./shaders/orig.vert", "./shaders/orig.frag");
    Shader shaderPulse("./shaders/orig.vert", "./shaders/sec.frag");

    //////////////////////////
    //Game Loop
    
    //[
        //0)bind VAO
        glBindVertexArray(VAO);
        //1)copy verticies and indixes into GPU
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        //2)set vertex attribure pointers
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    //]

    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();

        //Begin Interface Frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //Describe the interface for this frame
        ImGui::Begin("Settings");
        ImGui::ColorEdit3("Background", settings.background);
        ImGui::Checkbox("Wireframe", &settings.wireFrame);
        ImGui::ColorEdit3("Pulse Color", settings.pulseColor);
        ImGui::Checkbox("Use Pulse Shader", &settings.usePulseShader);
        ImGui::End();

        //Prepare interface drawing a function
        ImGui::Render();
        
        // Clear the background, accounting for window resizing.
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width,height);

        //Wireframe mode
        if(settings.wireFrame){
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        
        glClearColor(settings.background[0], settings.background[1], settings.background[2], 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        //3)use shader and VAO program and draw triangle
        if(!settings.usePulseShader){
            shader1.use();
        }else shaderPulse.use();

        //Pulse
        float time = glfwGetTime();
        float offset = 0.0f;
        float frequency = 4.0f;
        float phase = 0.0f;
        shaderPulse.setFloatVector("bg", settings.background, 1);
        shaderPulse.setFloatVector("ourColor", settings.pulseColor, 1);
        for(int i = 0; i < 3; i++){
            phase = (i*2*PI)/3;
            float brightness = ((sin(frequency*time - phase)/ 2 +0.5f));
            shaderPulse.setFloat("bright", brightness);
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(i*3*sizeof(unsigned int)));
        }

        // Draw the interface over the background, then present.
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    shader1.destroy();
    shaderPulse.destroy();

    ////////////////////////
    //Shut ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    //Shut GLFW
    glfwDestroyWindow(window);
    glfwTerminate();

    std::cout<<"All Closed & Finished"<<std::endl;
    return 0;
}