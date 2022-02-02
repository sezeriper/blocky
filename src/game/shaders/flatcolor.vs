#version 100

attribute vec3 pos;

uniform mat4 modelMat;

void main() {
  gl_Position = modelMat * vec4(pos, 1.0);
}