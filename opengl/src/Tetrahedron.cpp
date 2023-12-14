#include <iostream>
#include "Quad.h"
#include "Tetrahedron.h"

using namespace std;

Tetrahedron::Tetrahedron(glm::vec3 apex, vector<glm::vec3> basePoints, glm::vec3 color, Shader* s, float shininess)
    : Mesh(s, shininess) {
    if (basePoints.size() != 4) {
        cerr << "A tetrahedron must have exactly four points for its base" << endl;
    }

    mBase = new Quad(basePoints[0], basePoints[1], basePoints[2], basePoints[3], color, s, shininess);

    // Assuming that the base is pointed downward, the quadrilateral is in the exact opposite
    // orientation that the triangles need to be.
    mSides.push_back(new Triangle(basePoints[2], apex, basePoints[3], color, s, shininess));
    mSides.push_back(new Triangle(basePoints[0], apex, basePoints[1], color, s, shininess));
    mSides.push_back(new Triangle(basePoints[2], basePoints[1], apex, color, s, shininess));
    mSides.push_back(new Triangle(basePoints[0], basePoints[3], apex, color, s, shininess));
}

Tetrahedron::~Tetrahedron() {
    delete mBase;
    for (size_t i = 0; i < mSides.size(); i++) {
        delete mSides[i];
    }
}

void Tetrahedron::draw(Camera* camera, vector<Light*> lights) {
    mBase->draw(camera, lights);
    for (size_t i = 0; i < mSides.size(); i++) {
        mSides[i]->draw(camera, lights);
    }
}