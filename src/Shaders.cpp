#include "Shaders.h"
#include <sstream>
#include <fstream>
#include <iostream>

string Shaders::shaderParser(const char* filePath)
{
	ifstream file(filePath);
	if (!file.is_open())
	{
		cerr << "cant open some files" << endl;
        return "";
	}
    stringstream buff;
    buff << file.rdbuf();
	return buff.str();
}

Shaders::Shaders(const char* vertexFilePath, const char* fragmentFilePath)
{
	string vShader = shaderParser(vertexFilePath);
	string fShader = shaderParser(fragmentFilePath);

	const char* vertexShaderSource = vShader.c_str();
	const char* fragmentShaderSource = fShader.c_str();

    // Shader Compilation
    int success;
    char log[512];

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, log);
        cerr << "Cannot create vertexShader!" << endl;
    }

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, log);
        cerr << "Cannot create fragmentShader!" << endl;
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, log);
        cerr << "Cannot create the shader program!" << endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shaders::useShader()
{
    glUseProgram(shaderProgram);
}

void Shaders::setInt(const string& name, int value) const
{
    glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
}

void Shaders::setMatrix4fv(const string& name, glm::mat4 value) const 
{
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
    
}