#version 330 core
out vec4 fragColor;

in vec4 outCol;

//uniform vec4 uniCol;

void main(){
    fragColor = outCol;
        //uniCol;
        //vec4(1.0f,0.5f,0.2f,1.0f);
}
