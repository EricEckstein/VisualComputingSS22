#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices = 15) out;

in gl_PerVertex
{
  vec4 gl_Position;
} gl_in[];

out gl_PerVertex
{
  vec4 gl_Position;
}gl_out[];


void main() {   
	gl_out[0].gl_Position = gl_in[0].gl_Position;
}  
