#pragma once
#include "Gl_Common.h"
namespace dGL {

    class ShaderStorageBuffer {

    public:
        ShaderStorageBuffer() :ID(0) {}
        ~ShaderStorageBuffer() {
            if (ID) {
                glDeleteBuffers(1, &ID);
                glCheckError();
            }
        }
        void Init(const void* data, unsigned int size, unsigned int bufferBase, GLenum usage) {
            glGenBuffers(1, &ID);
            glCheckError();
            glBindBuffer(GL_SHADER_STORAGE_BUFFER, ID);
            glCheckError();
            glBufferData(GL_SHADER_STORAGE_BUFFER, size, data, usage);
            glCheckError();
            glBindBufferBase(GL_SHADER_STORAGE_BUFFER, bufferBase, ID);
            glCheckError();
        }
        inline void Bind() const {
            glBindBuffer(GL_SHADER_STORAGE_BUFFER, ID);
            glCheckError();
        }
        inline void UnBind() const {
            glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
            glCheckError();
        }

    private:
	    unsigned int ID;


    };
}