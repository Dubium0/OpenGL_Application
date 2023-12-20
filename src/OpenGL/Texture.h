#pragma once 
#include "Gl_Common.h"
#include <stb_image.h>
namespace dGL {
	
	class Texture {
	public:
		
		Texture(): ID(0), path(""), data(nullptr),target(NULL),WIDTH(0), HEIGHT(0), NR_CHANNELS(0){}
		~Texture() {
			if (ID) {
				glDeleteTextures(1, &ID);
				glCheckError();
			}
		}
		void Init(const std::string& _path, GLenum target, GLint _wrapParam, GLint _filterMode);
		void InitEmptyImage2DTexture(int TEXTURE_WIDTH, int TEXTURE_HEIGHT, unsigned int bindingUnit,
			GLenum access = GL_READ_ONLY,
			GLenum target = GL_TEXTURE_2D,
			GLint _wrapParam = GL_CLAMP_TO_EDGE,
			GLint _filterMode = GL_LINEAR,
			GLint internalFormat = GL_RGBA32F,
			GLenum format = GL_RGBA,
			GLenum type = GL_FLOAT);
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