#version 330 core
layout (location = 0) in vec3 apos;
layout (location = 1) in vec4 inCol;

out vec4 outCol;

void main(){
    gl_Position = vec4(apos, 1.0);
    outCol = vec4(apos.x/2.0+0.5,apos.y/2.0+0.5,apos.z/2.0+0.5,1.0);//inCol;
}
