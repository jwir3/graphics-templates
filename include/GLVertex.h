
#include <glm/glm.hpp>

#ifndef __GL_VERTEX_H__
#define __GL_VERTEX_H__

class GLVertex {
    glm::vec3 mPosition;
    glm::vec3 mNormal;
    glm::vec3 mColor;

    public:

    GLVertex(glm::vec3 pos, glm::vec3 color);

    glm::vec3 getPosition();
    glm::vec3 getColor();

    glm::vec3 getNormal();
    void setNormal(glm::vec3 aNormal);
};

#endif