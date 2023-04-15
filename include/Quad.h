#include "Mesh.h"
#include "Triangle.h"

#ifndef __QUAD_H__
#define __QUAD_H__
class Quad : public Mesh {
    private:
        Triangle* tri1;
        Triangle* tri2;

    public:
        Quad(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4, glm::vec3 color, Shader* shader, float shininess);
        ~Quad();

        void draw(Camera* camera, vector<Light*> lights);
};
#endif