#shader vertex
#version 330

layout(location = 0) in vec3 vPosition;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main()
{
	gl_Position = projection * view * model * vec4(vPosition, 1.0);

}

#shader fragment
#version 330

out vec4 FragColor;

void main()
{
	FragColor = vec4(0.5f, 0.3f, 0.3f, 0.5f);
}