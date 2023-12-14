#include "Triangle.h"

Triangle::Triangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 color, Shader* shader, float shininess)
: Mesh(shader, shininess)
{
    v1 = new GLVertex(p1, color);
    v2 = new GLVertex(p2, color);
    v3 = new GLVertex(p3, color);

    // Compute normals for the triangle.
    glm::vec3 dirVec1 = glm::normalize(p2 - p1);
    glm::vec3 dirVec2 = glm::normalize(p3 - p1);

    mNormal = glm::normalize(glm::cross(dirVec1, dirVec2));

    v1->setNormal(mNormal);
    v2->setNormal(mNormal);
    v3->setNormal(mNormal);
}

Triangle::~Triangle() {
    delete v1;
    delete v2;
    delete v3;
}

glm::vec3 Triangle::getNormal() {
    return mNormal;
}

void Triangle::draw(Camera* camera, vector<Light*> lights) {
    // cout << "Drawing triangle..." << endl;
    this->Mesh::draw(camera, lights);
    // cout << "done drawing tri" << endl;

    GLfloat vertices[] = {
        v1->getPosition().x, v1->getPosition().y, v1->getPosition().z,
        v1->getColor().r, v1->getColor().g, v1->getColor().b,
        v1->getNormal().x, v1->getNormal().y, v1->getNormal().z,
        v2->getPosition().x, v2->getPosition().y, v2->getPosition().z,
        v2->getColor().r, v2->getColor().g, v2->getColor().b,
        v2->getNormal().x, v2->getNormal().y, v2->getNormal().z,
        v3->getPosition().x, v3->getPosition().y, v3->getPosition().z,
        v3->getColor().r, v3->getColor().g, v3->getColor().b,
        v3->getNormal().x, v3->getNormal().y, v3->getNormal().z
    };

    GLuint vertex_indices[] = {
        0, 1, 2
    };

    // Bind Vertex Data
    GLuint vertexBufferObject;
	glGenBuffers(1, &vertexBufferObject);

    GLuint vertexArrayObject;
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3* sizeof(float)));
	glEnableVertexAttribArray(1);

	// normal attribute
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6* sizeof(float)));
	glEnableVertexAttribArray(2);

    // glUseProgram(getShader()->getProgramId());
    glBindVertexArray(vertexArrayObject);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}