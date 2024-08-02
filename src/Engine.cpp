#include "Engine.h"

//#define GLFW_INCLUDE_NONE

Engine* Engine::staticInstance = nullptr;

Engine::Engine()
{
	window = new Window(WindowProperties("ENGINE", 1080,1920));
	window->setEventCallback(BIND_EVENT_FN(onEvent));
	window->setVSync(false);

	if (Engine::staticInstance == nullptr)
		staticInstance = this;
}

Engine::~Engine()
{
	delete window;
}

void Engine::run()
{	
	// Engine loop
	while (isRunning)
	{
		float time = (float)glfwGetTime();
		Timestep timestep = time - lastFrameTime;
		lastFrameTime = time;

		for (Layer* layer : layerStack)
			layer->onUpdate(timestep);

		window->onUpdate();
	}
}

void Engine::onEvent(Event& e)
{
	EventDispatcher dispatcher(e);

	dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));

	for (auto it = layerStack.end(); it != layerStack.begin(); )
	{
		(*--it)->onEvent(e);
		if (e.isEventHandeled())
		{
			break;
		}
	}
}

void Engine::pushLayer(Layer* layer)
{
	layerStack.pushLayer(layer);
}

void Engine::pushOverlay(Layer* overlay)
{
	layerStack.pushOverlay(overlay);
}

bool Engine::onWindowClose(WindowCloseEvent& e)
{
	isRunning = false;
	return true;
}