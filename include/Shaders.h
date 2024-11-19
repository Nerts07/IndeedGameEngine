#ifndef Shaders_H
#define Shaders_H

#include "GLload.h"
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

class Shaders
{
public:
	Shaders(const char* vertexFilePath, const char* fragmentFilePath);
	string shaderParser(const char* filePath);
	void setInt(const string& name, int value) const;
	void setMatrix4fv(const std::string& name, glm::mat4 value) const;
	void useShader();
	GLuint shaderProgram;
	GLuint vertexShader;
	GLuint fragmentShader;
private:
	const char* filePath;
	const char* vertexFilePath;
	const char* fragmentFilePath;



};
#endif