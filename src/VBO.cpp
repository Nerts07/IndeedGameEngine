#include "VBO.h"
#include <iostream>

VBO::VBO() : vbo(0)
{

}

void VBO::vboInit(const void* data, GLsizeiptr size)
{
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void VBO::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
}
void VBO::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VBO::~VBO()
{
	std::clog << "destructing vertex: " << vbo << std::endl;
	glDeleteBuffers(1, &vbo);
}