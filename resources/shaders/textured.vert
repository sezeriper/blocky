#version 100

uniform mat4 u_model_mat;
uniform mat4 u_view_proj_mat;

attribute vec3 pos;
attribute vec2 uvs;

varying vec2 v_uvs;

void main() {
  gl_Position = u_view_proj_mat * u_model_mat * vec4(pos, 1.0);
  v_uvs = uvs;
}
