#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "Light.h"
#include "Shader.h"
#include "Camera.h"

#ifndef __MESH_H__
#define __MESH_H__

/**
 * @brief A 3D mesh to be rendered.
 *
 * A Mesh is a 3D object to be rendered within a {@link Scene @endlink}. It must have some type of material, which
 * is represented by a shader.
 *
 */
class Mesh {
    private:
        float mShininess;
        Shader* mShader;

        void linkShadersIfFinished();

    public:
        Mesh(Shader* material, float shininess);
        ~Mesh();

        Shader* getShader();

        virtual void draw(Camera* camera, std::vector<Light*> lights);
};
#endif