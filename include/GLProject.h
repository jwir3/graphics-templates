#include <GL/glew.h>
#include <glm/glm.hpp>

#include <GLFW/glfw3.h>

#include <string>
#include <iostream>
#include <cstdlib>

#include "Triangle.h"
// #include "Camera.h"
#include "Scene.h"

#ifndef __GL_PROJECT_H__
#define __GL_PROJECT_H__

/**
 * Creates a window using GLFW of a particular size and initializes all
 * GL-related functionality.
 */
class GLProject {
    GLFWwindow* mWindow;
    Scene* mScene = NULL;

    double mLastMouseX;
    double mLastMouseY;

    public:

        GLProject(int screenW, int screenH);
        ~GLProject();

        void setScene(Scene* s);
        GLFWwindow* getWindow() { return mWindow; }

        void initiateRenderLoop(void (*draw) (void));

    private:
        void initGL(int screenW, int screenH);

        void keyCallback(int key, int scancode, int action, int mods);
        void mouseCallback(double xPos, double yPos);
};

#endif