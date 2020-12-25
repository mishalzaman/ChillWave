#version 150

in  vec3 position;
out vec3 eyeVector;

void main(void)
{
    gl_Position = vec4(position, 1.0);
}