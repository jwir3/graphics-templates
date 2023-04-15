
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include "Shader.h"

#ifndef __LIGHT_H__
#define __LIGHT_H__
class Light {
    private:
        glm::vec3 mColor;
        
    public:
        Light(glm::vec3 color);
        Light(const Light& aOther)
            : mColor(aOther.mColor) {}

        ~Light();

        glm::vec3 getColor() { return mColor; }

        virtual void draw(Shader* shader) = 0;
};

class AmbientLight : public Light {
    public:
        AmbientLight(glm::vec3 color);
        AmbientLight(const AmbientLight& aOther)
            : Light(aOther) {}
        ~AmbientLight();

        void draw(Shader* shader);
};

class PointLight: public Light {
    private:
        glm::vec3 mPosition;
    
    public:
        PointLight(glm::vec3 color, glm::vec3 position);
        PointLight(const PointLight& aOther)
            : Light(aOther), mPosition(aOther.mPosition) {}
        ~PointLight();

        glm::vec3 getPosition() { return mPosition; }

        void draw(Shader* shader);
};

#endif