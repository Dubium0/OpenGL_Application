#include "Texture.h"
namespace dGL {
    /*
    Texture::Texture(GLenum target_, GLenum format_, int WIDTH_, int HEIGHT , GLuint unit = 0, GLint _wrapParam = GL_CLAMP_TO_EDGE, GLint _filterMode = GL_LINEAR):
        path(NULL), ID(0), WIDTH(WIDTH_), HEIGHT(HEIGHT), NR_CHANNELS(0), data(nullptr), target(target_) {

        glGenTextures(1, &ID);
        glActiveTexture(target);
        glBindTexture(target, ID);
        glTexParameteri(target, GL_TEXTURE_WRAP_S, _wrapParam);
        glTexParameteri(target, GL_TEXTURE_WRAP_T, _wrapParam);
        glTexParameteri(target, GL_TEXTURE_MAG_FILTER, _filterMode);
        glTexParameteri(target, GL_TEXTURE_MIN_FILTER, _filterMode);
        glTexImage2D(target, 0, format_, WIDTH, HEIGHT, 0, GL_RGBA,GL_FLOAT, NULL);
        glBindImageTexture(unit, ID, 0, GL_FALSE, 0, GL_READ_ONLY, format_);
    }

    */
    Texture::Texture(const std::string& _path, GLenum target, GLint _wrapParam = GL_CLAMP_TO_EDGE, GLint _filterMode = GL_LINEAR) :
	path(_path), ID(0), WIDTH(0), HEIGHT(0), NR_CHANNELS(0), data(nullptr), target(target){
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
}