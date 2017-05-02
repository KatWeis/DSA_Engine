#version 430

layout (location = 0) in vec3 position;

layout (location = 1) in vec2 uv;

layout (location = 2) in vec3 normal;

out vec3 fragNorm;

out vec4 fragLoc;

out vec2 fragUV;

out float red;

layout (location = 5) uniform mat4 worldView;

layout (location = 11) uniform mat4 modelWorld;

void main()
{
   gl_Position = worldView * modelWorld * vec4(position, 1);
   fragLoc = modelWorld * vec4(position, 1);
   red = (position.x + 1)/2;
   fragNorm = transpose(inverse(mat3(modelWorld))) * normal;
   fragUV = uv;
}