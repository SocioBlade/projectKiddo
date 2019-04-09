#version 440
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec2 uv_coords;

out vec2 uv_frag;

void main()
{
	uv_frag = uv_coords;

	gl_Position = vec4(vertex_position,1); 

}