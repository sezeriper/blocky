#version 100

attribute vec3 pos;

uniform mat4 modelMat;
uniform mat4 viewProjMat;

void main() {
  gl_Position = viewProjMat * modelMat * vec4(pos, 1.0);
}