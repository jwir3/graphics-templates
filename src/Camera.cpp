#include "Camera.h"
#include <cmath>

using namespace std;

Camera::Camera(GLuint screenW, GLuint screenH, glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 up, float movementSpeed)
: mCameraPos(cameraPos), mCameraFront(cameraFront), mCameraUp(up), mScreenW(screenW), mScreenH(screenH),
  mMovementSpeed(movementSpeed), mTheta(-90.0f), mPhi(0) {
    recomputeCameraLeftFromUpAndFront();
    recomputeMatrices();
}

void Camera::recomputeMatrices() {
    P = glm::perspective(45.0f, (GLfloat)mScreenW/(GLfloat)mScreenH, 0.1f, 100.0f);
    V = glm::lookAt(mCameraPos, mCameraPos + mCameraFront, mCameraUp);
}

void Camera::strafeForward() {
    mCameraPos = mCameraPos + (mCameraFront * mMovementSpeed);
    recomputeMatrices();
}

void Camera::strafeBackward() {
    mCameraPos = mCameraPos - (mCameraFront * mMovementSpeed);
    recomputeMatrices();
}

void Camera::strafeLeft() {
    mCameraPos = mCameraPos - glm::normalize(glm::cross(mCameraFront, mCameraUp)) * mMovementSpeed;
    recomputeMatrices();
}

void Camera::strafeRight() {
    mCameraPos = mCameraPos + glm::normalize(glm::cross(mCameraFront, mCameraUp)) * mMovementSpeed;
    recomputeMatrices();
}

void Camera::gazeUpDown(double amount) {
    mPhi = (mPhi + (mMovementSpeed * amount));
    if (mPhi > 360) {
        mPhi = mPhi - 360;
    }

    recomputeAngles();
    recomputeCameraUpFromFrontAndLeft();
    recomputeMatrices();
}

void Camera::gazeLeftRight(double amount) {
    mTheta = (mTheta + (mMovementSpeed * amount));
    if (mTheta > 360) {
        mTheta = mTheta - 360;
    }

    recomputeAngles();
    recomputeCameraLeftFromUpAndFront();
    recomputeMatrices();
}

void Camera::recomputeAngles() {
    glm::vec3 direction;
    direction.x = cos(glm::radians(mTheta)) * cos(glm::radians(mPhi));
    direction.y = sin(glm::radians(mPhi));
    direction.z = sin(glm::radians(mTheta)) * cos(glm::radians(mPhi));

    mCameraFront = glm::normalize(direction);
    // Our new lookAt position will be based in spherical coordinates
    // glm::vec3 lookAt = mCameraPos + mCameraFront;

    // float theta = (M_PI*mTheta) / 180.0;
    // float phi = (M_PI*mPhi) / 180.0;

    // cout << "phi is now: " << phi << endl;

    // float r = 8;
    // // float r = glm::length(mCameraPos);
    // // float r = glm::length(mCameraPos + mCameraFront);
    // float x = r * sin(theta) * cos(phi);
    // float y = r * sin(theta) * sin(phi);
    // float z = r * cos(theta);

    // glm::vec3 newLookAt = glm::vec3(x, y, z);
    // cout << "newLookAt is: " << newLookAt.x << ", " << newLookAt.y << ", " << newLookAt.z << endl;
    // mCameraFront = newLookAt - mCameraPos;
    // cout << "mCameraFront is now: " << mCameraFront.x << ", " << mCameraFront.y << ", " << mCameraFront.z << endl;
}

void Camera::recomputeCameraLeftFromUpAndFront() {
    glm::vec3 up = glm::normalize(mCameraUp);
    glm::vec3 forward = glm::normalize(mCameraFront);
    mCameraLeft = glm::cross(up, forward);
}

void Camera::recomputeCameraUpFromFrontAndLeft() {
    glm::vec3 forward = glm::normalize(mCameraFront);
    glm::vec3 left = glm::normalize(mCameraLeft);
    mCameraUp = glm::cross(forward, left);
}
