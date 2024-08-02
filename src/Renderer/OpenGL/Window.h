#ifndef WINDOW_CLASS_H
#define WINDOW_CLASS_H

#include <string>
#include <iostream>

#include "../../Events/Event.h"
#include "../../Events/ApplicationEvent.h"
#include "../../Events/KeyEvent.h"
#include "../../Events/MouseEvent.h"

#include "../GraphicsContext.h"
#include "OpenGLContext.h"

/**
 * @struct WindowProperties
 *
 * @brief structure defcribing a window properties
 */
struct WindowProperties
{
	std::string title; ///< Title of a window
	unsigned int width; ///< Width of a window
	unsigned int height; ///< Height of a window

	/**
	 * @brief WindowProperties
	 * @param title new window title (default = "ENGINE")
	 * @param height new window (deafult = 720)
	 * @param width new window (default = 720)
	 */
	WindowProperties(
		const std::string& title = "ENGINE",
		unsigned int height = 720,
		unsigned int width = 1280
	) : title(title), height(height), width(width) {}
};

/**
* @class Window
*
* @brief Class abstracting the GLFW window
*/
class Window {
public:
	/**
	* @brief Constructs a Window object.
	* 
	* @param props properties of new window
	*/
	Window(const WindowProperties& props = WindowProperties());

	/**
	* @brief Window class Destructor
	*/
	virtual ~Window();

	using EventCallbackFn = std::function<void(Event&)>;

	/**
	 * @brief Function called on every update to update the Window
	 */
	void onUpdate();

	/**
	 * @brief gets width of a window
	 * 
	 * @return width of window
	 */
	inline unsigned int getWidth() const { return data.width; }

	/**
	 * @brief gets height of a window
	 *
	 * @return height of window
	 */
	inline unsigned int getHeight() const { return data.height; }

	/**
	 * @brief sets event callback function
	 *
	 * @param callback function assigned to given callback
	 */
	inline void setEventCallback(const EventCallbackFn& callback) { data.eventCallback = callback; }

	/**
	 * @brief sets VSync 
	 *
	 * @param enabled value of vsync flag
	 */
	void setVSync(bool enabled);

	/**
	 * @brief returns whether vsync is enabled
	 *
	 * @return true if enabled otherwise false
	 */
	bool isVSync() const { return data.VSync; }

	/**
	 * @brief returns pointer to GLFW window
	 *
	 * @return pointer to GLFW window
	 */
	inline GLFWwindow* getGLFWWindow() const { return window; }

private:
	/**
	 * @brief initializes window with given propertirs
	 *
	 * @param props properties used to initialize window
	 */
	void init(const WindowProperties& props);

	/**
	 * @brief closes the window
	 */
	void shutdown();

	GLFWwindow* window; ///< pointer to GLFW window
	GraphicsContext* context; ///< pointer to Graphiscs context used for displaing graphics

	/**
	 * @struct WindowData
	 *
	 * @brief structure containing data about the window
	 */
	struct WindowData
	{
		std::string Title;
		unsigned int width, height;
		bool VSync;

		EventCallbackFn eventCallback;
	};

	WindowData data; ///< structure containing data about the window
};

#endif // !WINDOW_CLASS_H
