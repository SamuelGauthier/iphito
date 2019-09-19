#version 410

layout(location=0) in vec4 inPosition;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(void) {
    gl_Position = projection * view * model * inPosition;
}
