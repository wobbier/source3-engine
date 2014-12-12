#version 330 core
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 

struct Light {
    vec3 position;
    vec3 spotDir;
    float spotCutOff;
    float spotOuterCutOff;
  
    float constant;
    float linear;
    float quadratic;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;       
};

in vec3 Position;
in vec3 Normal;
in vec2 TexCoords;

out vec4 color;

uniform vec3 viewPos;
uniform Light light;
uniform Material material;

void main()
{    
    // Properties
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - Position);   // Direction of the fragment to the light
    vec3 viewDir = normalize(viewPos - Position);
    vec3 reflectDir = reflect(-lightDir, norm);       
    
    // Check if lighting is inside the spotlight cone
    float theta = dot(lightDir, normalize(-light.spotDir)); 
    float epsilon = (light.spotCutOff - light.spotOuterCutOff);
    float intensity = clamp((theta - light.spotOuterCutOff) / epsilon, 0.0, 1.0);
    
    // Diffuse shading    
    float diffuse = max(dot(norm, lightDir), 0.0);
    
    // Specular shading    
    float specular = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    
    // Attenuation
    float distance = length(light.position - Position);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    // Combine results
    vec3 ambientColor = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuseColor = light.diffuse * diffuse * vec3(texture(material.diffuse, TexCoords)) * intensity;
    vec3 specularColor = light.specular * specular * vec3(texture(material.specular, TexCoords)) * intensity;
    ambientColor *= attenuation;
    diffuseColor *= attenuation;
    specularColor *= attenuation;
    color = vec4(ambientColor + diffuseColor + specularColor, 1.0f);
}