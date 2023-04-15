#include <vector>
#include "Mesh.h"
#include "Triangle.h"
#include "Quad.h"
#include "Shader.h"

#ifndef __TETRAHEDRON_H__
#define __TETRAHEDRON_H__
class Tetrahedron : public Mesh {
    private:
        std::vector<Triangle*> mSides;
        Quad* mBase;
    
    public:
        Tetrahedron(glm::vec3 apex, std::vector<glm::vec3> basePoints, glm::vec3 color, Shader* s, float shininess);
        ~Tetrahedron();

        void draw(Camera* camera, std::vector<Light*> lights);
};
#endif