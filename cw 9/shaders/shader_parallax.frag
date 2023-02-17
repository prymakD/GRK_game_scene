#version 330 core

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;
in vec3 Tangent;
in vec3 Bitangent;

out vec4 color;

uniform sampler2D diffuseMap;
uniform sampler2D normalMap;
uniform sampler2D heightMap;

uniform vec3 lightPos;
uniform float heightScale;

vec3 GetNormalFromMap()
{
    vec3 normal = texture(normalMap, TexCoord).rgb;
    normal = normalize(normal * 2.0 - 1.0);
    
    mat3 TBN = mat3(Tangent, Bitangent, Normal);
    return normalize(TBN * normal);
}

void main()
{
    vec3 ambient = vec3(0.3);
    vec3 diffuse = vec3(0.7);
    vec3 specular = vec3(0.2);
    
    vec3 lightColor = vec3(1.0);
    
    vec3 viewPos = vec3(0.0, 0.0, 3.0);
    
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 normal = GetNormalFromMap();
    vec3 viewDir = normalize(viewPos - FragPos);
    
    vec3 height = texture(heightMap, TexCoord).rgb;
    vec3 pos = FragPos + normal * height * heightScale;
    
    vec3 diffuseValue = max(dot(normal, lightDir), 0.0) * diffuse * lightColor;
    vec3 specularValue = pow(max(dot(viewDir, reflect(-lightDir, normal)), 0.0), 32.0) * specular *lightColor;
    vec4 result = vec4((ambient + diffuseValue + specularValue) * texture(diffuseMap, TexCoord).rgb, 1.0);

    color = vec4(result);
}