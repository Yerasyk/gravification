cmake_minimum_required(VERSION 3.20)

project(Gravification LANGUAGES CXX)

add_executable(gravification main.cpp)

target_compile_features(gravification PRIVATE cxx_std_20)

#GLFW Package
find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(gravification PRIVATE glfw)

#ImGUI Package
find_package(imgui CONFIG REQUIRED)
target_link_libraries(gravification PRIVATE imgui::imgui)

#OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(gravification PRIVATE OpenGL::GL)