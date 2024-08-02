#version 330 core

// From Vertex Shader
in vec3 crntPos;
in vec3 normal;
in vec3 color;
in vec2 texCoord;

// Texture uniforms
uniform sampler2D diffuse0;
uniform sampler2D specular0;
uniform vec2 TextureOffset;

uniform int isSign = 0;

// Camera Position
uniform vec3 camPos;

//Output color
out vec4 FragColor;

void main()
{ 
	vec2 isOffset = vec2(0.0, 0.0);

	vec2 newUV = vec2(texCoord.x+TextureOffset.x, texCoord.y+TextureOffset.y);
	if( texture(diffuse0, newUV).a < 0.1)
		discard;

	FragColor = texture(diffuse0, newUV);
}