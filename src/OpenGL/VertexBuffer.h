#pragma once
#include "Gl_Common.h"
namespace dGL {
	class VertexBuffer {
	public:


		VertexBuffer(const void* data, unsigned int size) : ID(0) {
			glGenBuffers(1, &ID);
			glCheckError();
			Bind();
			glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
			glCheckError();
			UnBind();
		}
		~VertexBuffer(){
			glDeleteBuffers(1, &ID);
			glCheckError();
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