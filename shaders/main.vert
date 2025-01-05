#version 330 core
layout (location = 0) in vec3 apos;
layout (location = 1) in vec4 inCol;
layout (location = 2) in vec2 inTexCoord;

out vec4 outCol;
out vec2 texCoord;

void main(){
    gl_Position = vec4(apos, 1.0);
    outCol = inCol;
    texCoord = inTexCoord;
}
