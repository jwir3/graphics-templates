#include <vector>

#include "Camera.h"
#include "Light.h"
#include "Mesh.h"

#ifndef __SCENE_H__
#define __SCENE_H__

/**
 * A class containing the definitions for all objects to be drawn. It contains a list of Mesh objects,
 * each having their own shader to represent materials. It also contains several lights and a single camera
 * defining the view.
 */
class Scene {
    private:
        Camera* mCamera;
        std::vector<Light*> mLights;
        std::vector<Mesh*> mMeshes;

    public:
        Scene(Camera* c);
        ~Scene();

        /**
         * Add a light to the scene.
         * 
         * @param l The {@link Light} to add. 
         */
        void addLight(Light* aLight);
        void addMesh(Mesh* m);

        void draw();

        Camera* getCamera() { return mCamera; }
};

#endif // __SCENE_H__

