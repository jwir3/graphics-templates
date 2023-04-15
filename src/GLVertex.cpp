#include "GLVertex.h"

GLVertex::GLVertex(glm::vec3 pos, glm::vec3 color) {
    mPosition = pos;
    mColor = color;
}

glm::vec3 GLVertex::getPosition() {
    return mPosition;
}

glm::vec3 GLVertex::getColor() {
    return mColor;
}

glm::vec3 GLVertex::getNormal() {
    return mNormal;
}

void GLVertex::setNormal(glm::vec3 aNormal) {
    mNormal = aNormal;
}