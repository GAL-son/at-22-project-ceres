#pragma once
#ifndef RENDERER_CLASS_H
#define RENDERER_CLASS_H

#include "OpenGL/OpenGLRenderer.h"
#include "OpenGL/Skybox.h"

/**
 * @class Renderer
 * @brief Provides rendering functionality for the scene.
 */
class Renderer
{
public:
	/**
	 * @brief Begins a new rendering scene.
	 */
	static void beginScene();

	/**
	 * @brief Ends the current rendering scene.
	 */
	static void endScene();

	/**
	 * @brief Submits an object for rendering.
	 * @param obj The object to render.
	 * @param shader The shader used for rendering.
	 * @param camera The camera used for rendering.
	 */
	static void submit(Object& obj, Shader& shader, Camera& camera);

	/**
	 * @brief Flushes the rendering queue.
	 */
	static void flush();

	/**
	 * @brief Clears the color and depth buffers.
	 */
	static void clearBuffers();

	/**
	 * @brief Clears the color buffer to the specified color.
	 * @param color The color to clear the buffer to.
	 */
	static void clearColor(glm::vec4 color);

private:
	static OpenGLRenderer* usedRenderer; ///< The renderer used for rendering.
};

#endif // !RENDERER_CLASS_H
