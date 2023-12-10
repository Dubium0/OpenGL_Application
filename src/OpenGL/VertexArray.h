#pragma once
#include "Gl_Common.h"
#include <vector>
#include "VertexBuffer.h"
namespace dGL {

	class VertexArrayAttribute {
	private:
		unsigned int stride;
		std::vector<unsigned int> sizeArray;



	public:

		VertexArrayAttribute() : stride(0) {};
		void PushAttributef(unsigned int size) {
			stride += size;
			sizeArray.push_back(size);
		}

		inline const std::vector<unsigned int> GetElements() const& { return sizeArray; }
		inline unsigned int GetStride() const { return stride; }
	};

	class VertexArray
	{
	public:
		VertexArray(): ID(0) {
			glGenVertexArrays(1, &ID);
			glCheckError();
			glBindVertexArray(ID);
			glCheckError();
		}
	
		~VertexArray() {
			glDeleteVertexArrays(1, &ID);
			glCheckError();
		}
	
		inline void Bind() const {
			glBindVertexArray(ID);
			glCheckError();
		}
	
		inline void UnBind() const {
			glBindVertexArray(0);
			glCheckError();
		}
	
		void AddVertexArrayAttributef(const VertexBuffer& vbo, const VertexArrayAttribute& attributes) {
			Bind();
			vbo.Bind();
			const std::vector<unsigned int>& sizeArray = attributes.GetElements();
			unsigned int offSet = 0;
			for (unsigned int i = 0; i < sizeArray.size(); i++) {
				glVertexAttribPointer(i, sizeArray[i], GL_FLOAT, GL_FALSE, attributes.GetStride() * sizeof(float), (void*)(offSet * sizeof(float)));
				glCheckError();
				glEnableVertexAttribArray(i);
				glCheckError();
				offSet += sizeArray[i];
			}
			UnBind();
			vbo.UnBind();
		}
	

	private:
		unsigned int ID;

	};
}