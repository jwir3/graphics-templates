#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#ifndef __SHADER_H__
#define __SHADER_H__

/**
 * @brief A program that can be used to draw a 3D object.
 *
 * A Shader must consist of at least a vertex program and a fragment program. All other
 * programs are optional.
 *
 */
class Shader {
    private:
        GLuint mProgramId;

        // Individual shader ids
        GLuint mVertexShaderId;
        GLuint mFragmentShaderId;

        std::string mVertexShaderFileName;
        std::string mFragmentShaderFileName;

        void finalizeShaderPrograms();

    public:
        Shader(std::string vertexFileName, std::string fragmentFileName);
        ~Shader();

        void loadShader(GLenum shaderType, std::string fileName);

        GLuint getProgramId() { return mProgramId; }

        GLuint getVertexShaderId() { return mVertexShaderId; }
        GLuint getFragmentShaderId() { return mFragmentShaderId; }
};
#endif // __SHADER_H__