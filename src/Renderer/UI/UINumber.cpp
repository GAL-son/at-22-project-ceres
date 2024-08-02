#include "UINumber.h"

#include <glad/glad.h>

#include "../OpenGL/Model.h"

UINumber::UINumber(float width, float height)
{
	textureOffset = { 0.0, 0.0 };
	value = 0;

	float x1 = width;
	float x2 = -width;
	float y1 = height;
	float y2 = -height;

	std::vector<Vertex> surfaceVerts =
	{
		Vertex{glm::vec3(x1,y1,0), glm::vec3(0, 1, 0), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0, 0.19)},
		Vertex{glm::vec3(x1,y2,0), glm::vec3(0, 1, 0), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.2, 0.19)},
		Vertex{glm::vec3(x2,y1,0), glm::vec3(0, 1, 0), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0, 0.0)},
		Vertex{glm::vec3(x2,y2,0), glm::vec3(0, 1, 0), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.2, 0.0)}
	};

	std::vector<GLuint> surfaceInds =
	{
		0, 1, 2,
		1, 3, 2
	};
	std::vector<Texture> surfTextures = { Texture("res/Test/Numbers.png", TEXTURE_DIFFUSE, 0) };

	this->surface = new Mesh(surfaceVerts, surfaceInds, surfTextures);
}

void UINumber::draw(Shader& shader, Camera& camera) 
{
	setValue(value);
	glUniform1i(glGetUniformLocation(shader.ID, "isSign"), 1);
	glUniform2f(glGetUniformLocation(shader.ID, "TextureOffset"), this->textureOffset.x, this->textureOffset.y);
	UIElement::draw(shader, camera);
}

void UINumber::setValue(int value)
{
	this->value = value;
	if (value > 4)
	{
		textureOffset.y = 0.5;
	}
	else
	{
		textureOffset.y = 0.0;
	}

	textureOffset.x = (value % 5) * offsetStep;
}

