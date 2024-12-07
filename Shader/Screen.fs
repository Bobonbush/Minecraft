#version 330

out vec4 outColor;
in vec2 coords;

uniform sampler2D uTexture;
uniform vec4 color = vec4(1.0, 1.0, 1.0, 1.0);

void main() {
    outColor = texture(uTexture, coords);
    if(outColor.a < 0.1) discard;
    outColor *= color;
}