#version 330 core

out vec4 FragColor;

in vec3 aCol;
in vec3 aPos;
in vec3 aNormal;

void main()
{
    vec3 light_position = vec3(15.0, 30.0, -15.0);
    vec3 light_ambient  = vec3(1.0, 1.0, 1.0);
    vec3 light_color  = vec3(1.0, 1.0, 1.0);

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * light_ambient;

    vec3 norm = normalize(aNormal);
    vec3 lightDir = normalize(light_position - aPos);  

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * light_color;

    vec3 result = (ambient + diffuse) * aCol;

    float angle = acos(dot(norm, normalize(vec3(norm.x, norm.y, 0.0))));

    //FragColor = vec4(result, 1.0f);
    FragColor = vec4(norm, 1.0f);
    //FragColor = vec4(aCol, 1.0f);
}