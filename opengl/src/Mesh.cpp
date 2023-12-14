#include "Mesh.h"
#include <iostream>

using namespace std;

Mesh::Mesh(Shader* shader, float shininess)
	: mShader(shader), mShininess(shininess)
{

}

Mesh::~Mesh() {
}

Shader* Mesh::getShader() {
	return mShader;
}

void Mesh::draw(Camera* camera, vector<Light*> lights) {
	glUseProgram(getShader()->getProgramId());

    for (size_t i = 0; i < lights.size(); i++) {
        lights[i]->draw(getShader());
    }

	GLuint Mloc = glGetUniformLocation(getShader()->getProgramId(), "M");
    glUniformMatrix4fv(Mloc, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
    GLuint Ploc = glGetUniformLocation(getShader()->getProgramId(), "P");
    glUniformMatrix4fv(Ploc, 1, GL_FALSE, glm::value_ptr(camera->getPerspectiveMatrix()));
    GLuint Vloc = glGetUniformLocation(getShader()->getProgramId(), "V");
    glUniformMatrix4fv(Vloc, 1, GL_FALSE, glm::value_ptr(camera->getViewMatrix()));

    GLuint viewPosLoc = glGetUniformLocation(getShader()->getProgramId(), "viewPos");
    glUniform3f(viewPosLoc, camera->getPosition().x, camera->getPosition().y, camera->getPosition().z);

    GLuint shininessLoc = glGetUniformLocation(getShader()->getProgramId(), "shininess");
    glUniform1f(shininessLoc, mShininess);
}