#version 410

uniform vec3 color;

out vec4 outColor;

void main(void) {
    outColor = vec4(color, 1);
}
