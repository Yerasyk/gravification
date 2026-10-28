#include <iostream>

#include <glad/glad.h> //OpenGL Functions
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "shader.h"

int main()
{
    //Initialize glfw
    if(!glfwInit()){
        return 1;
    }

    // Request OpenGL 3.3 core when creating the window.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Create window and return pointer to that window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Gravification", nullptr, nullptr);
    if (window == nullptr){
        glfwTerminate();
        return 1;
    }

    //Set current CONTEXT to window
    glfwMakeContextCurrent(window);

    //Loading OpenGL functions
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        glfwDestroyWindow(window);
        glfwTerminate();
        return 1;
    }

    //Init ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    ////////////////////////////////////////////////////////////////////////////////////////////////
    //ALL IN GAME STUFF

    //////////////////////////
    //Data
    bool wireFrame = false;
    bool shaders = false;

    float background[3] = {0.02f, 0.03f, 0.08f};
    float pulseColor[3] = {1.0f, 1.0f, 1.0f};

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
    // unsigned int indices[] = {  // note that we start from 0!
    //     0, 1, 2,   // first triangle
    //     1, 3, 5,    // second triangle
    //     2, 5, 4    // second triangle
    // }; 
    unsigned int indices1[] = {  // note that we start from 0!
        0, 1, 2   // first triangle
    }; unsigned int indices2[] = {  // note that we start from 0!
        1, 3, 5    // second triangle
    }; unsigned int indices3[] = {  // note that we start from 0!
        2, 5, 4    // second triangle
    }; 
        
    //////////////////////////
    //Creating Vertex Buffer Object (copy data), Vertex Array Object (store attribute pointers), Element Buffer Object (store indices of vertices)
    unsigned int VBO[3], VAO[3], EBO[3];
    glGenBuffers(3, VBO);
    glGenBuffers(3, EBO);
    glGenVertexArrays(3, VAO);
    
    //Creating Shader program: shad_out -> link -> shad_inp
    Shader shader1("./shaders/orig.vert", "./shaders/orig.frag");
    Shader shader2("./shaders/orig.vert", "./shaders/sec.frag");

    //////////////////////////
    //Game Loop
    
    //[
        //0)bind VAO
        glBindVertexArray(VAO[0]);
        //1)copy verticies and indixes into GPU
        glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);
        //2)set vertex attribure pointers
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    //]
    //[
        //0)bind VAO
        glBindVertexArray(VAO[1]);
        //1)copy verticies and indixes into GPU
        glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);
        //2)set vertex attribure pointers
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    //]
    //[
        //0)bind VAO
        glBindVertexArray(VAO[2]);
        //1)copy verticies and indixes into GPU
        glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[2]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices3), indices3, GL_STATIC_DRAW);
        //2)set vertex attribure pointers
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    //]
    //[...]

    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();

        //Begin Interface Frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //Describe the interface for this frame
        ImGui::Begin("Settings");
        ImGui::ColorEdit3("Background", background);
        ImGui::Checkbox("Wireframe", &wireFrame);
        ImGui::ColorEdit3("Pulse Color", pulseColor);
        ImGui::Checkbox("Shader2", &shaders);
        ImGui::End();

        //Prepare interface drawing a function
        ImGui::Render();
        
        // Clear the background, accounting for window resizing.
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width,height);

        //Wireframe mode
        if(wireFrame){
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        
        glClearColor(background[0], background[1], background[2], 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        //3)use shader and VAO program and draw triangle
        if(!shaders){
            shader1.use();
        }else shader2.use();

        //Pulse
        float time = glfwGetTime();
        float offset = 0.0f;
        shader2.setFloatVector("bg",background[0],background[1],background[2]);
        shader2.setFloatVector("ourColor",pulseColor[0],pulseColor[1],pulseColor[2]);
        
        for(auto el : VAO){
            offset = (offset+0.5f);
            float brightness = ((sin(time + offset)/ 2 +0.5f));
            shader2.setFloat("bright", brightness);
            glBindVertexArray(el);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        }

        // Draw the interface over the background, then present.
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }
    glDeleteVertexArrays(3, VAO);
    glDeleteBuffers(3, VBO);
    glDeleteBuffers(3, EBO);
    shader1.destroy();
    shader2.destroy();

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