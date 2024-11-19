#ifndef VBO_H
#define VBO_H



#include "GLload.h"

class VBO
{
public:
	VBO();
	~VBO();

	void vboInit(const void* data, GLsizeiptr size);
	void bind() const;
	void unbind() const;
private:
	GLuint vbo;
};
#endif // VBO_H