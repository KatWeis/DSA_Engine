#version 430

layout (location = 0) in vec3 position;

out vec3 textDir;

layout (location = 5) uniform mat4 worldView;

void main()
{
   gl_Position = worldView * vec4(position, 1);
   textDir =  position;
}