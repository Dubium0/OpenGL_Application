#include "Texture.h"
namespace dGL {
 
    void Texture::Init(const std::string& _path, GLenum target, GLint _wrapParam = GL_CLAMP_TO_EDGE, GLint _filterMode = GL_LINEAR)
	{
        glGenTextures(1, &ID);
        glCheckError();
        glBindTexture(target, ID);
        glCheckError();
        // set the texture wrapping parameters
        glTexParameteri(target, GL_TEXTURE_WRAP_S, _wrapParam);	
        glCheckError();
        glTexParameteri(target, GL_TEXTURE_WRAP_T, _wrapParam);
        glCheckError();
        // set texture filtering parameters
        glTexParameteri(target, GL_TEXTURE_MIN_FILTER, _filterMode);
        glCheckError();
        glTexParameteri(target, GL_TEXTURE_MAG_FILTER, _filterMode);
        glCheckError();
        // load image, create texture and generate mipmaps

        stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.

        data = stbi_load(path.c_str(), &WIDTH, &HEIGHT, &NR_CHANNELS, 4);
        if (data)
        {

            glTexImage2D(target, 0, GL_RGBA, WIDTH, HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glCheckError();
            glGenerateMipmap(target);
            glCheckError();

        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        glBindTexture(target, 0);
        glCheckError();
        stbi_image_free(data);
        

    }

    void Texture::InitEmptyImage2DTexture( int TEXTURE_WIDTH, int TEXTURE_HEIGHT, unsigned int bindingUnit,
        GLenum access,
        GLenum target,
        GLint _wrapParam ,
        GLint _filterMode,
        GLint internalFormat,
        GLenum format,
        GLenum type) {

        glGenTextures(1, &ID);
        glBindTexture(target, ID);
        glTexParameteri(target, GL_TEXTURE_WRAP_S, _wrapParam);
        glTexParameteri(target, GL_TEXTURE_WRAP_T, _wrapParam);
        glTexParameteri(target, GL_TEXTURE_MAG_FILTER, _filterMode);
        glTexParameteri(target, GL_TEXTURE_MIN_FILTER, _filterMode);
        glTexImage2D(target, 0, internalFormat, TEXTURE_WIDTH, TEXTURE_HEIGHT, 0, format, type, NULL);
        glBindImageTexture(bindingUnit, ID, 0, GL_FALSE, 0, access, GL_RGBA32F);
    }



}