#version 330

out vec4 outColor;
in vec2 coords;

uniform sampler2D uTexture;

void main() {
    outColor = texture(uTexture, coords);
    if(outColor.a < 0.1) discard;
}