#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"


#ifndef __CAMERA_H__
#define __CAMERA_H__

class Camera {
    private:
        GLuint mScreenW;
        GLuint mScreenH;

        glm::vec3 mCameraPos;
        glm::vec3 mCameraFront; // Direction vector pointing "forward" for the camera
        glm::vec3 mCameraUp;
        glm::vec3 mCameraLeft; // The x axis for the camera

        glm::mat4 P;
        glm::mat4 V;

        float mTheta;
        float mPhi;

        float mMovementSpeed = 0.1f;

    public:

    Camera(GLuint screenW, GLuint screenH, glm::vec3 eye, glm::vec3 lookAt, glm::vec3 up, float movementSpeed);
    Camera(const Camera& aOther)
        : mScreenW(aOther.mScreenW), mScreenH(aOther.mScreenH), mCameraPos(aOther.mCameraPos), mCameraFront(aOther.mCameraFront), mCameraUp(aOther.mCameraUp),
          mCameraLeft(aOther.mCameraLeft), mTheta(aOther.mTheta), mPhi(aOther.mPhi) { }

    void strafeForward();
    void strafeBackward();
    void strafeLeft();
    void strafeRight();

    void gazeLeft(double amount);
    void gazeRight(double amount);
    void gazeUpDown(double amount);
    void gazeLeftRight(double amount);

    GLuint getScreenWidth() { return mScreenW; }
    GLuint getScreenHeight() { return mScreenH; }

    glm::mat4 getPerspectiveMatrix() { return P; }
    glm::mat4 getViewMatrix() { return V; }
    glm::vec3 getPosition() { return mCameraPos; }
    float getTheta() { return mTheta; }
    float getPhi() { return mPhi; }

    private:

        void recomputeMatrices();
        void recomputeAngles();
        void recomputeCameraLeftFromUpAndFront();
        void recomputeCameraUpFromFrontAndLeft();
};
#endif