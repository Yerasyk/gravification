#version 330 core

out vec4 FragColor;

uniform vec3 ourColor;
uniform vec3 bg;
uniform float bright;

void main()
{
    FragColor = vec4(mix(bg, ourColor, bright),1.0f);
}