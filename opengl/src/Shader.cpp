#include "Shader.h"
#include <filesystem>
#include <iostream>

using namespace std;

Shader::Shader(string vertexFileName, string fragmentFileName) {
    loadShader(GL_VERTEX_SHADER, vertexFileName);
    loadShader(GL_FRAGMENT_SHADER, fragmentFileName);
    finalizeShaderPrograms();
}

Shader::~Shader() {
    glDeleteShader(mVertexShaderId);
    glDeleteShader(mFragmentShaderId);
    glDeleteProgram(mProgramId);
}

void Shader::loadShader(GLenum shaderType, string fileName) {
    // Determine if this is an absolute path or a relative path
    filesystem::path p(fileName);
    string effectivePathString(fileName);
    if (!p.is_absolute()) {
        filesystem::path effectivePath(filesystem::current_path());
        effectivePath /= "shaders";
        effectivePath /= fileName;
        effectivePathString = effectivePath.c_str();
    }

    string shaderDescription;
    GLuint* ptrToShaderId;

    switch (shaderType) {
        case GL_VERTEX_SHADER:
            mVertexShaderFileName = fileName;
            shaderDescription = "Vertex";
            ptrToShaderId = &mVertexShaderId;
            break;
        case GL_FRAGMENT_SHADER:
            shaderDescription = "Fragment";
            mFragmentShaderFileName = fileName;
            ptrToShaderId = &mFragmentShaderId;
            break;
    }

    cout << "Loading " << shaderDescription << " shader from file: " << effectivePathString.c_str() << endl;

    // Create the shaders
    GLuint unlinkedShaderId = glCreateShader(shaderType);

    // Read the Vertex Shader code from the file
    std::string shaderCode;
    std::ifstream shaderStream(effectivePathString.c_str(), std::ios::in);
    if (shaderStream.is_open()){
        string Line = "";
        while(getline(shaderStream, Line))
            shaderCode += "\n" + Line;
        shaderStream.close();
    }

    GLint result = GL_FALSE;
    int infoLogLength;

    cout << "Compiling " << shaderDescription << " shader..." << endl;

    const char* sourcePointer = shaderCode.c_str();
    glShaderSource(unlinkedShaderId, 1, &sourcePointer , NULL);
    glCompileShader(unlinkedShaderId);

    glGetShaderiv(unlinkedShaderId, GL_COMPILE_STATUS, &result);
    glGetShaderiv(unlinkedShaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
    vector<char> shaderErrorMessage(infoLogLength);
    glGetShaderInfoLog(unlinkedShaderId, infoLogLength, NULL, &shaderErrorMessage[0]);

    (*ptrToShaderId) = unlinkedShaderId;

    // cout << shaderErrorMessage[0] << endl;
}

void Shader::finalizeShaderPrograms() {
    GLint programLinkResult = GL_FALSE;

    // // TODO: Iterate through all shaders
    // if (mUnlinkedShaders.find(GL_VERTEX) != mUnlinkedShaders.end()
    //     && mUnlinkedShaders.find(GL_FRAGMENT) != mUnlinkedShaders.end()) {
    //         GLuint vertexId = mUnlinkedShaders.at(GL_VERTEX);
    //         GLuint fragmentId = mUnlinkedShaders.at(GL_FRAGMENT);
    int infoLogLength;

    // Link the program
    cout << "Linking program" << endl;
    mProgramId = glCreateProgram();
    glAttachShader(mProgramId, mVertexShaderId);
    glAttachShader(mProgramId, mFragmentShaderId);
    glLinkProgram(mProgramId);

    // Check the program
    glGetProgramiv(mProgramId, GL_LINK_STATUS, &programLinkResult);
    glGetProgramiv(mProgramId, GL_INFO_LOG_LENGTH, &infoLogLength);
    std::vector<char> programErrorMessage( max(infoLogLength, int(1)) );
    glGetProgramInfoLog(mProgramId, infoLogLength, NULL, &programErrorMessage[0]);
    cerr << programErrorMessage[0] << endl;
}