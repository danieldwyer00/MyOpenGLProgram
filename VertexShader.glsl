#version 430
layout(location = 0) in vec3 vertPos;
layout(location = 1) in vec3 vertColor;
out vec4 fragColor;
void main()
{
	fragColor = vec4(vertColor, 1.0);
	gl_Position = vec4(vertPos, 1.0);
}