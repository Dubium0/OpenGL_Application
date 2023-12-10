#pragma once 
#include "Gl_Common.h"
#include <stb_image.h>
namespace dGL {

	class Texture {
	public:
		//Texture(GLenum target, GLenum format, int WIDTH, int HEIGHT, GLuint unit = 0, GLint _wrapParam = GL_CLAMP_TO_EDGE, GLint _filterMode = GL_LINEAR);
		Texture(const std::string& _path, GLenum target, GLint _wrapParam, GLint _filterMode);
		~Texture() {
			glDeleteTextures(1, &ID);
			glCheckError();
		}
		inline void Bind(unsigned int channel) const {
			glActiveTexture(GL_TEXTURE0 + channel);
			glCheckError();
			glBindTexture(target, ID);
			glCheckError();
		}
		inline void UnBind() const {
			glBindTexture(target, 0);
			glCheckError();

		}
	private:
		unsigned int ID;
		std::string path;
		unsigned char* data;
		GLenum target;
		int WIDTH, HEIGHT, NR_CHANNELS;
	


	};
}