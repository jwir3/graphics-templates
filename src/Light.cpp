#include "Light.h"

Light::Light(glm::vec3 color) 
    : mColor(color) {

}

Light::~Light() {

}

AmbientLight::AmbientLight(glm::vec3 color)
    :Light(color) {
}

AmbientLight::~AmbientLight() { }

void AmbientLight::draw(Shader* shader) {
    GLuint ambientLightColorLoc = glGetUniformLocation(shader->getProgramId(), "ambientLightColor");
    glUniform3f(ambientLightColorLoc, getColor().r, getColor().g, getColor().b);
}

PointLight::PointLight(glm::vec3 color, glm::vec3 position)
    : Light(color), mPosition(position) {
}

PointLight::~PointLight() {

}

void PointLight::draw(Shader* shader) {
    GLuint diffuseLightPosLoc = glGetUniformLocation(shader->getProgramId(), "lightPos");
    glUniform3f(diffuseLightPosLoc, mPosition.x, mPosition.y, mPosition.z);
    GLuint diffuseLightColorLoc = glGetUniformLocation(shader->getProgramId(), "lightColor");
    glUniform3f(diffuseLightColorLoc, getColor().r, getColor().g, getColor().b);    
}