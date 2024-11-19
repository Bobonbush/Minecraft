#version 330

out vec4 outColor;
in vec2 aCoords;

uniform sampler2D uTexture;

void main() {
    outColor = texture(uTexture, aCoords);
}