#version 330 core
in vec3 FragPos;
in vec3 Normal;
in vec3 ObjColor;

out vec4 FragColor;

uniform vec3 ambientLightColor;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;
uniform float shininess;

float specularStrength = 0.5;

void main()
{
    // Ambient Component
    vec3 ambient = ambientLightColor;

    // Diffuse Component
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    float contrib = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = contrib * lightColor;

    // Specular Component
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm); 

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = specularStrength * spec * lightColor;  

    vec3 result = (diffuse + ambient + specular) * ObjColor;
    FragColor = vec4(result, 1.0);
}
