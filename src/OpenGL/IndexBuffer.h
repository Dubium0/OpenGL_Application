#pragma once
#include "Gl_Common.h"
namespace dGL {
	class IndexBuffer {
	public:
		IndexBuffer(const void* data, unsigned int size) {
			glGenBuffers(1, &ID);
			glCheckError();
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
			glCheckError();
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
			glCheckError();

		}
		~IndexBuffer() {
			glDeleteBuffers(1, &ID);
			glCheckError();
		}

		inline void Bind() const{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
			glCheckError();
		}
		
		inline void UnBind() const{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			glCheckError();
		}

	private:
		unsigned int ID;
	};

}