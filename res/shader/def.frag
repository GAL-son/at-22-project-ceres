#version 330 core

// From Vertex Shader
in vec3 crntPos;
in vec3 normal;
in vec3 color;
in vec2 texCoord;

// Texture uniforms
uniform sampler2D diffuse0;
uniform sampler2D specular0;

// Camera Position
uniform vec3 camPos;

//Output color
out vec4 FragColor;

uniform float brightness;

//Light Struct
struct LightSource
{
	int Type;
    vec3 Position;
    vec3 Direction;
    vec3 Color;
	float Intensity;
};

//LightSource uniforms
uniform LightSource lights[64];

//LightNone
vec4 lightNone(LightSource light)
{
    return vec4(0.0, 0.0, 0.0, 1.0);
}

//LightDirect
vec4 lightDirect(LightSource light)
{
    //Diffiusion color
	vec3 normal_normalized = normalize(normal);
	vec3 lightDirection = normalize(light.Direction);
	float diffuse = max(dot(normal, lightDirection), 0.0f) * light.Intensity;

    //Specular color
	float specular = 0.0f;
	if(diffuse != 0.0f)
	{
		float specularLight = 0.6f;
		vec3 viewDirection = normalize(camPos - crntPos);
		vec3 reflectionDirection = reflect(-lightDirection, normal);

		vec3 halfwayvec = normalize(viewDirection + lightDirection); 

		float specAmount = pow(max(dot(normal, halfwayvec), 0.0f), 16);
		specular = specAmount * specularLight;
	}

	return vec4(light.Color * (diffuse * light.Intensity) + specular, 1.0f);
}

//LightPoint
vec4 lightPoint(LightSource light)
{
    vec3 lightVec = light.Position - crntPos;

	// intensity of light with respect to distance
	float dist = length(lightVec);
	float a = 0.1f;
	float b = -0.2;
	float inten = (1.0f / (a * dist * dist + b * dist + 1.0f)) * light.Intensity;

	//Diffiusion color
	vec3 normal_normalized = normalize(normal);
	vec3 lightDirection = normalize(lightVec);
	float diffuse = max(dot(normal_normalized , lightDirection), 0.0f);

	//Specular color
	float specularLight = 0.6f;
	vec3 viewDirecion = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirecion, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;
	 
	// final color modifier
	return vec4(light.Color * (diffuse * inten), 1.0);
}

void main()
{
    vec4 baseColor = texture(diffuse0, texCoord);
    vec4 colorModifier = vec4(0.0, 0.0, 0.0, 1.0);
    int i = 0;
    while(i < 64)
    {   
        LightSource crntLight = lights[i];
        if(crntLight.Type == 0) //NONE
        {
            colorModifier += lightNone(crntLight);
            i += 1;
            continue;
        }
        if(crntLight.Type == 1) //DIRECT
        {
            colorModifier += lightDirect(crntLight);
            i += 1;
            continue;
        }
        if (crntLight.Type == 2) //POINT
        {
            colorModifier += lightPoint(crntLight);
            i += 1;
            continue;
        }
              
        i += 1;
    }

	FragColor = baseColor * (colorModifier);
}