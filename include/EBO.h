#ifndef EBO_H
#define EBO_H

#include "GLload.h"
#include <vector>

class EBO
{
public:
	EBO(std::vector<GLuint> indices);
	~EBO();
	void bind();
	void unbind();
	
private:
	GLuint ebo;

};

#endif