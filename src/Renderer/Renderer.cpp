#include "Renderer.h"

OpenGLRenderer* Renderer::usedRenderer = new OpenGLRenderer;

void Renderer::beginScene()
{
}

void Renderer::endScene()
{
}

void Renderer::submit(Object& obj, Shader& shader, Camera& camera)
{
	usedRenderer->drawModel(obj, shader, camera);
}

void Renderer::flush()
{
}

void Renderer::clearBuffers()
{
	usedRenderer->clear();
}

void Renderer::clearColor(glm::vec4 color)
{
	usedRenderer->setClearColor(color);
}
