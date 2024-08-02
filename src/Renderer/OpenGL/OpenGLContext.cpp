#include "OpenGLContext.h"
#include <glad/glad.h>

OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
	: windowHandle(windowHandle)
{
}

void OpenGLContext::init()
{
	glfwMakeContextCurrent(windowHandle);

	//Tell glfw what version of OpenGL is used (3.3 in this case)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Tell glfw what profile is used (core - only modern version)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	int gladStatus = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

void OpenGLContext::swapBuffers()
{
	glfwSwapBuffers(windowHandle);
}
