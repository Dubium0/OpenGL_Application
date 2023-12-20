#pragma once
#include "Gl_Common.h"
namespace dGL {
	class VertexBuffer {
	public:

		VertexBuffer() : ID(0) {}
		void Init(const void* data, unsigned int size) {
			glGenBuffers(1, &ID);
			glCheckError();
			Bind();
			glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
			glCheckError();
			UnBind();
		}

		~VertexBuffer(){
			if (ID) {
				glDeleteBuffers(1, &ID);
				glCheckError();
			}
		}
	
		inline void Bind() const {
			glBindBuffer(GL_ARRAY_BUFFER, ID);
			glCheckError();
		}
	
		inline void UnBind() const {
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glCheckError();
		}



	private:
		unsigned int ID;

	};
}