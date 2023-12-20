#pragma once
#include "Gl_Common.h"
namespace dGL {
	class IndexBuffer {
	public:
		IndexBuffer():ID(0) {}
		~IndexBuffer() {
			if (ID) {
				glDeleteBuffers(1, &ID);
				glCheckError();
			}
		}
		void Init(const void* data, unsigned int size) {
			glGenBuffers(1, &ID);
			glCheckError();
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
			glCheckError();
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
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