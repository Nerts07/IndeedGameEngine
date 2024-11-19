#ifndef Texture_H
#define Texture_H

#include "GLload.h"
#include "Shaders.h"

#include <iostream>

class Texture
{
public:

	enum class Filter
	{
		NEAREST,
		LINEAR
	};

	Texture(const char* filepath, Filter filter);
	void bind();
	void unbind();
	void deleteTexture();
	void textureFilter(Filter fil);
	void uniform(Shaders& shader, const char* uniform, GLuint unit);

private:
	GLuint texture;
	
	int layer;
	Filter filter;

};
#endif