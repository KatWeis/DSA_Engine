#version 430

in vec3 textDir;

layout (location = 20) uniform samplerCube cubeMap;

void main()
{
  gl_FragColor = texture(cubeMap, textDir);
}