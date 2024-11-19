#include "GLload.h"
#include "VBO.h"
class VAO
{
public:
	VAO();
	~VAO();
	
	void linkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum dataType, GLsizeiptr stride, void* offset);
	void bind();
	void unbind();

private:
	GLuint vao;
};
