#include <iostream>

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

using namespace std;

int main()
{
    //Initialize glfw
    if(!glfwInit()){
        return 1;
    }

    //Gives Imgui info about OpenGL (version)
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

    //Init ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    ////////////////////////
    //ALL IN GAME STUFF

    float background[3] = {0.02f, 0.03f, 0.08f};

    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();

        //Begin Interface Frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //Describe the interface for this frame
        ImGui::Begin("Settings");
        ImGui::ColorEdit3("Background", background);
        ImGui::End();

        //Prepare interface drawing a function
        ImGui::Render();
        
        // Clear the background, accounting for window resizing.
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        glViewport(0, 0, width,height);

        glClearColor(background[0], background[1], background[2], 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw the interface over the background, then present.
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }
    
    ////////////////////////
    //Shut ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    //Shut GLFW
    glfwDestroyWindow(window);
    glfwTerminate();

    cout<<"All Closed & Finished"<<endl;
    return 0;
}