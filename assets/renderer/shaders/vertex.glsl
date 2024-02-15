attribute vec4 a_position;

uniform mat3 u_transform;

void main() {
    gl_Position = vec4(u_transform * vec3(a_position.xy, 1.0), 1.0);
}