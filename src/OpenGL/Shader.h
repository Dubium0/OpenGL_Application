#pragma once
#include "Gl_Common.h"
#include <fstream>
#include <sstream>
namespace dGL {
	class Shader {
	public:
		Shader(const std::string& vertexPath, const std::string& fragmentPath);
		// Most functionalities are same so I will make compute shader as an option here
		Shader(const std::string& computeShaderPath);
		~Shader(){ glDeleteProgram(ID);}

		inline void Bind() const {
			glUseProgram(ID);
			glCheckError();
		}
	
		inline void UnBind() const {
			glUseProgram(0);
			glCheckError();
		}

		inline void SetBool(const std::string& name, bool value) const {
			Bind();
			glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
			glCheckError();
		}
	
		inline void SetInt(const std::string& name, int value) const {
			Bind();
			glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
			glCheckError();

		}
	
		inline void SetFloat(const std::string& name, float value) const {
			Bind();
			glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
			glCheckError();
		}
	
		inline void SetMatrixf(const std::string& name, const float* m4) const {
			Bind();
			glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, m4);
			glCheckError();
		}
	
		inline void SetVec3(const std::string& name, const float* v3) const {
			Bind();
			glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, v3);
			glCheckError();
		}






	private:
		unsigned int ID;
	
		std::string getShaderCode(const std::string& path) const;
	
		void checkCompileErrors(unsigned int shader, std::string type) const;

	};
}
