precision mediump int;
precision mediump float;

// uniform mat4 u_Transform;
// uniform vec4 u_Color;

attribute vec3 position;

void main() {
  // Transform the location of the vertex from object coordinates to world coordinates (normalized device coordinates)
  // gl_Position = u_Transform * vec4(a_Vertex, 1.0);
  gl_Position = vec4(position, 1.0);
}
