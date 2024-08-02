#include "OpenGLRenderer.h"
#include <glad/glad.h>

void OpenGLRenderer::setClearColor(const glm::vec4 color)
{
	glClearColor(color.r, color.g, color.b, color.a);
}

void OpenGLRenderer::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderer::drawModel(Object& obj, Shader& shader, Camera& camera)
{
	obj.draw(shader, camera);
}

