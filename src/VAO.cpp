#include "VAO.h"
#include <vector>
#include <iostream>
VAO::VAO()
{
	glGenVertexArrays(1, &vao);
	
}
void VAO::linkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum dataType, GLsizeiptr stride, void* offset)
{
	VBO.bind();
	glVertexAttribPointer(layout, numComponents, dataType, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBO.unbind();
}

void VAO::bind()
{
	glBindVertexArray(vao);
}
void VAO::unbind()
{
	glBindVertexArray(0);
}
VAO::~VAO()
{
	std::clog << "VAO deleted: " << vao << std::endl;
	glDeleteBuffers(1, &vao);
}
