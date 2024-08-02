#pragma once
#ifndef OPEN_GL_RENDERER_CLASS_H
#define OPEN_GL_RENDERER_CLASS_H

#include <glm/glm.hpp>
#include "Model.h"
#include "../Object.h"


/**
 * @class OpenGLRenderer
 *
 * @brief Class giving acces to basic OpenGL commands
 */
class OpenGLRenderer {
public:
	/**
	* @brief fills the buffer with color
	*
	* @param color vec4 representing the RGBA color with values from 0.0 to 1.0
	*/
	void setClearColor(const glm::vec4 color);

	/**
	* @brief clears OpenGL buffers
	*/
	void clear();

	/**
	 * @brief Draws the given Object using the specified shader and camera.
	 * @param obj object to be rendered
	 * @param shader The shader used for rendering.
	 * @param camera The camera used for rendering.
	 */
	void drawModel(Object& obj, Shader& shader, Camera& camera);
};

#endif // !OPEN_GL_RENDERER_CLASS_H
 