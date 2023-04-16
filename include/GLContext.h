#include <GL/glew.h>
#include <glm/glm.hpp>

#include <GLFW/glfw3.h>

#include <string>
#include <iostream>
#include <cstdlib>

#include "Scene.h"

#ifndef __GL_CONTEXT_H__
#define __GL_CONTEXT_H__

class GLContext {
    GLFWwindow* mWindow;
    Scene* mScene = NULL;

    double mLastMouseX;
    double mLastMouseY;

    public:
        GLContext(int screenW, int screenH);
        ~GLContext();

        void setScene(Scene* s);
        GLFWwindow* getWindow() { return mWindow; }

        void initiateRenderLoop(void (*draw) (void));

    private:
        void initGL(int screenW, int screenH);

        void keyCallback(int key, int scancode, int action, int mods);
        void mouseCallback(double xPos, double yPos);
};

#endif // __GL_CONTEXT_H__