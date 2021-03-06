#version 450

layout(location=0) in vec3 fragNormal;
layout(location=1) in vec3 fragPosition;
layout(location=2) in vec3 fragCameraPosition;

void main() {

    const float ambientStrength = 0.4f;
    const vec3 lightColor = vec3(1.0f);
    const vec3 lightPosition = vec3(15.0f, 15.0f, 15.0f);
    const float specularStrength = 0.5f;

    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(fragNormal);
    vec3 lightDirection = normalize(lightPosition - fragPosition);
    float diff = max(dot(norm, lightDirection), 0.0);
    vec3 diffuse = 0.7 * diff * lightColor;


    vec3 viewDir = normalize(fragCameraPosition - fragPosition);
    vec3 reflectDir = reflect(-lightDirection, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * vec3(1.0,0.,0.);

    gl_FragColor = vec4(result, 1.0);
}
