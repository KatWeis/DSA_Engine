#version 430

out vec4 fragColor;

in float red;

layout (location = 6) uniform vec3 lightLoc;

layout (location = 7) uniform vec3 camLoc;

layout (location = 8) uniform float ambientStr;

layout (location = 9) uniform float specStr;

layout (location = 10) uniform sampler2D myTexture;

in vec4 fragLoc;

in vec3 fragNorm;

in vec2 fragUV;

vec3 norm = normalize(fragNorm);

vec4 lightDir = normalize(vec4(lightLoc, 1) - fragLoc);

float diff = max(dot(lightDir, vec4(norm, 1)), 0);

vec4 diffuse = diff * vec4(1, 1, 1, 1);

vec4 viewDir = normalize(vec4(camLoc, 1) - fragLoc);

vec4 reflectDir = reflect(-lightDir, vec4(norm, 1));

float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

vec4 specular = specStr * spec * vec4(1, 1, 1, 1);

layout (location = 4) uniform float time;

vec4 ambient = ambientStr * vec4(1, 1, 1, 1);

void main()
{
  float green = (sin(time)+1)/2;
  float blue = (cos(time)+1)/2;
  gl_FragColor = texture(myTexture, fragUV) * (ambient + diffuse + specular);
}