// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Include GLFW
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include "GLProject.h"
#include "Triangle.h"
#include "GLVertex.h"
#include "Camera.h"
#include "Shader.h"
#include "Light.h"
#include "Scene.h"
#include "Tetrahedron.h"

#define DEFAULT_SCREEN_WIDTH 1400
#define DEFAULT_SCREEN_HEIGHT 800

Scene* scene;

Scene* buildScene(int screenW, int screenH) {
    glm::vec3 dirTowardOrigin = glm::normalize(glm::vec3(0, 0, -10));
	Camera* camera = new Camera(screenW, screenH, glm::vec3(0, 0, 10), dirTowardOrigin, glm::vec3(0, 1, 0), 0.2f);

    Scene* scene = new Scene(camera);

    // Shaders are located in the shaders/ directory
    Shader* s = new Shader("PhongShader.vert.glsl", "PhongShader.frag.glsl");

    AmbientLight* amb = new AmbientLight(glm::vec3(0.1, 0.1, 0.1));
    PointLight* pointLight = new PointLight(glm::vec3(1.0, 1.0, 1.0), glm::vec3(0, 10, 10));
    scene->addLight(amb);
    scene->addLight(pointLight);

	glm::vec3 pyramidColor(1.0, 0.5, 0.2);

    vector<glm::vec3> basePoints;
    basePoints.push_back(glm::vec3(4.0, 0, -4.0));
    basePoints.push_back(glm::vec3(4.0, 0, 4.0));
    basePoints.push_back(glm::vec3(-4.0, 0, 4.0));
    basePoints.push_back(glm::vec3(-4.0, 0, -4.0));

    scene->addMesh(new Tetrahedron(glm::vec3(0, 4, 0), basePoints, pyramidColor, s, 128));

    return scene;
}

void draw() {
	// Dark blue background
	glClearColor(0.2f, 0.2f, 0.3f, 0.0f);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    // We want to enable depth testing.
    glEnable(GL_DEPTH_TEST);

    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    scene->draw();
}

int main( int argc, char* argv[]) {
    int screenW = DEFAULT_SCREEN_WIDTH;
    int screenH = DEFAULT_SCREEN_HEIGHT;

    // TODO: Add a --help/usage statement.

    GLProject p(screenW, screenH);
    scene = buildScene(screenW, screenH);
    p.setScene(scene);

    p.initiateRenderLoop(draw);

	return 0;
}
