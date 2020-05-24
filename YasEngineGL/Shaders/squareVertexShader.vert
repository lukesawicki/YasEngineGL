#version 430
 uniform float offset;
//layout (location 0) in vec3 position
void main(void)
{
	if(gl_VertexID == 0)
	{
		gl_Position = vec4(0.25 + offset, -0.25, 0.9, 1.0);
	}
	else
	{
		if(gl_VertexID == 1)
		{
			gl_Position = vec4(-0.25 + offset, -0.25, 0.9, 1.0);
		}
		else
		{
			gl_Position = vec4(0.25 + offset, 0.25, 0.9, 1.0);
		}
	}
}