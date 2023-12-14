#include "Quad.h"

Quad::Quad(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4, glm::vec3 color, Shader* shader, float shininess)
    : Mesh(shader, shininess) {
    tri1 = new Triangle(p1, p2, p3, color, shader, shininess);
    tri2 = new Triangle(p3, p4, p1, color, shader, shininess);
}

Quad::~Quad() {

}

void Quad::draw(Camera* camera, std::vector<Light*> lights) {
    tri1->draw(camera, lights);
    tri2->draw(camera, lights);
}