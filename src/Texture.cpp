#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>
#include "Textures.h"
#include <iostream>

using namespace std;

Texture::Texture(const char* filepath, Filter filter)
{


    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    textureFilter(filter);

    stbi_set_flip_vertically_on_load(true);

    int width, height, nrChannels;
    unsigned char* data = stbi_load(filepath, &width, &height, &nrChannels, 0);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        cerr << "Error, no texture loaded!" << filepath <<  endl;
    }


    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::uniform(Shaders& shader, const char* uniform, GLuint unit)
{
    GLuint texUni = glGetUniformLocation(shader.shaderProgram, uniform);
    shader.useShader();
    glUniform1i(texUni, unit);
}

void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, texture);
}

void Texture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::deleteTexture()
{
    glDeleteTextures(1, &texture);
}

void Texture::textureFilter(Filter fil)
{
    if (fil == Filter::NEAREST)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }
    if (fil == Filter::LINEAR)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
}
