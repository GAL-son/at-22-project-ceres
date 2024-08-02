#pragma once
#ifndef OPEN_GL_CONTEXT
#define OPEN_GL_CONTEXT
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "../GraphicsContext.h"

/**
 * @class OpenGLContext
 *
 * @brief Class representing a Graphics context with OpenGL implementation
 */
class OpenGLContext : public GraphicsContext 
{
public:
	/**
	* @brief constructs a OpenGLContext
	*
	* @param windowHandle handle to GLFW window used for displaing graphics
	*/
	OpenGLContext(GLFWwindow* windowHandle);

	/**
	* @brief initialies OpenGL
	*/
	virtual void init() override;

	/**
	* @brief swaps OpenGL buffers
	*/
	virtual void swapBuffers() override;

private:
	GLFWwindow* windowHandle; ///< handle to GLFW window used for displaing graphics
};

#endif // !OPEN_GL_CONTEXT
