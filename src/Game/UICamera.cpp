#include "UICamera.h"

void UICamera::onUpdate(Timestep timestep)
{
	updateMatrix();
}

void UICamera::onEvent(Event& event)
{
	EventDispatcher dispatcher(event);
}
