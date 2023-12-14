#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "GLVertex.h"

#include "Mesh.h"
#include "Light.h"

#include <iostream>

using namespace std;

#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

class Triangle : public Mesh {
    GLVertex* v1;
    GLVertex* v2;
    GLVertex* v3;

    glm::vec3 mNormal;

    public:

    Triangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 color, Shader* shader, float shininess);
    ~Triangle();

    void draw(Camera* camera, vector<Light*> lights) override;

    glm::vec3 getNormal();
};
#endif