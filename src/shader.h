#pragma once

#include <glad/glad.h>
#include <string>

#include <iostream>
#include <fstream>
#include <sstream>

class Shader
{
public:
    //Program ID
    unsigned int ID;

    //build shader program
    Shader(const char* vertexPath, const char* fragmentPath);

    //Use program
    void use();

    //utility uniform functions
    void setInt(const std::string& name, int value);
    void setBool(const std::string& name, bool value);
    void setFloat(const std::string& name, float value);
    void setFloatVector(const std::string& name, float x, float y, float z);
    void setFloatVector(const std::string& name, const float* values, int count);
    //
    void destroy();
private:
    void checkCompileErrors(unsigned int shader, std::string type);
};