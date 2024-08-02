#include "Window.h"


static bool GLFWInitialized = false;

Window::Window(const WindowProperties& props)
{
	init(props);
}

Window::~Window()
{
	shutdown();
}

void Window::init(const WindowProperties& props)
{
	data.Title = props.title;
	data.height = props.height;
	data.width = props.width;	

	if (!GLFWInitialized)
	{
		int success = glfwInit();

		std::cout << success << std::endl;
		GLFWInitialized = true;
	}

	window = glfwCreateWindow((int)props.width, (int)props.height, data.Title.c_str(), nullptr, nullptr);

	context = new OpenGLContext(window);
	context->init();

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}


	glfwSetWindowUserPointer(window, &data);
	setVSync(true);

	//Set GLFW callbacks

	glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
			data.width = width;
			data.height = height;

			WindowResizedEvent event(width, height);
			data.eventCallback(event);
		});

	glfwSetWindowCloseCallback(window, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.eventCallback(event);
		});

	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scanCode, int action, int modes)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.eventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.eventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.eventCallback(event);
					break;
				}
				default:
					break;
			}
		});

	glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.eventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.eventCallback(event);
					break;
				}
				default:
					break;
			}
		});

	glfwSetScrollCallback(window, [](GLFWwindow* window, double xOffset, double yOffset) 
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.eventCallback(event);
		});

	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseMovedEvent event((float)xPos, (float)yPos);
			data.eventCallback(event);
		});
}

void Window::shutdown()
{
	glfwDestroyWindow(window);
}

void Window::onUpdate()
{
	glfwPollEvents();
	context->swapBuffers();
}

void Window::setVSync(bool enabled)
{
	if (enabled)
		glfwSwapInterval(1);
	else
		glfwSwapInterval(0);

	data.VSync = enabled;
}