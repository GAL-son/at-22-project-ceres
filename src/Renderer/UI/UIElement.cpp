#include "UIElement.h"
#include "../Renderer.h"

UIElement::UIElement(float width, float height)
{
	float x1 = width;
	float x2 = -width;
	float y1 = height;
	float y2 = -height;

	std::vector<Vertex> surfaceVerts =
	{
		Vertex{glm::vec3(x1,y1,0), glm::vec3(0, 1, 0), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0, 1.0)},
		Vertex{glm::vec3(x1,y2,0), glm::vec3(0, 1, 0), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0, 1.0)},
		Vertex{glm::vec3(x2,y1,0), glm::vec3(0, 1, 0), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0, 0.0)},
		Vertex{glm::vec3(x2,y2,0), glm::vec3(0, 1, 0), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0, 0.0)}
	};

	std::vector<GLuint> surfaceInds =
	{
		0, 1, 2,
		2, 1, 3
	};
	std::vector<Texture> surfTextures = { Texture("res/Test/EmptyTexture.png", TEXTURE_DIFFUSE, 0) };

	this->surface = new Mesh(surfaceVerts, surfaceInds, surfTextures);
}

void UIElement::draw(Shader& shader, Camera& camera)
{
	if (!visible) return;
	glDepthFunc(GL_ALWAYS);
	surface->draw(shader, camera, glm::mat4(1.0), glm::vec3(position, 0.0));
}

void UIElement::setTexture(const char* path)
{
	surface->textures.clear();
	surface->textures.push_back(Texture(path, TEXTURE_DIFFUSE, 0));
}
