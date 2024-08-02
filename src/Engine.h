#ifndef ENGINE_CLASS_H
#define ENGINE_CLASS_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "LayerStack.h"
#include "Renderer/OpenGL/Window.h"
#include "Core/Timestep.h"
#include "Core/Input.h"

#include "GameObject.h"

/**
 * @def BIND_EVENT_FN(x)
 *
 * @brief Binds function
 *
 * @param x function name
 */
#define BIND_EVENT_FN(x) std::bind(&Engine::x, this, std::placeholders::_1)

 /**
  * @class Engine
  *
  * @brief The main class responsible for running the engine.
  */
class Engine
{
public:
	/**
	 * @brief Constructs an Engine object.
	 */
	Engine();

	/**
	 * @brief Destructs the Engine object.
	 */
	virtual ~Engine();

	/**
	 * @brief Runs the engine.
	 */
	void run();

	/**
	 * @brief Handles events.
	 *
	 * @param e The event to handle.
	 */
	void onEvent(Event& e);

	/**
	 * @brief Pushes a layer onto the layer stack.
	 *
	 * @param layer The layer to push.
	 */
	void pushLayer(Layer* layer);

	/**
	 * @brief Pushes an overlay onto the layer stack.
	 *
	 * @param overlay The overlay to push.
	 */
	void pushOverlay(Layer* overlay);

	/**
	 * @brief Gets the window associated with the engine.
	 *
	 * @return The window.
	 */
	Window& getWindow() { return *window; }

	/**
	 * @brief Gets the instance of the Engine.
	 *
	 * @return The Engine instance.
	 */
	static Engine& get() { return *staticInstance; }

private:
	/**
	 * @brief Handles the WindowCloseEvent.
	 *
	 * @param e The WindowCloseEvent.
	 * @return Whether the event was handled.
	 */
	bool onWindowClose(WindowCloseEvent& e);

	Window* window; /**< The window associated with the engine. */
	LayerStack layerStack; /**< The layer stack. */

	bool isRunning = true; /**< Flag indicating if the engine is running. */
	float lastFrameTime; /**< Time of the last frame. */

	static Engine* staticInstance; /**< Static instance of the Engine. */
};

#endif // !ENGINE_CLASS_H
