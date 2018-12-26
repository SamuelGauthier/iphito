#version 410

uniform vec3 curveColor;

out vec4 outColor;

void main(void) {
    outColor = vec4(curveColor, 1);
}
