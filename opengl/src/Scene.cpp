#include "Scene.h"
#include <iostream>

using namespace std;

Scene::Scene(Camera* c)
    : mCamera(c) {

}

Scene::~Scene() {

}

void Scene::addMesh(Mesh* aMesh) {
    mMeshes.push_back(aMesh);
}

void Scene::addLight(Light* aLight) {
    mLights.push_back(aLight);
}

void Scene::draw() {
    // Draw each mesh with the lights and camera provided
    for (size_t i = 0; i < mMeshes.size(); i++) {
        mMeshes[i]->draw(mCamera, mLights);
    }
}