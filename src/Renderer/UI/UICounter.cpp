#include "UICounter.h"

UICounter::UICounter(float width, float height, int size)
{
	this->value = 0;
	this->height = height;
	this->width = width;
	for (int i = 0; i < size; i++)
	{
		UINumber num(width / (size * 2), height);
		num.setValue(i);
		fields.push_back(num);
	}
	setElements();
}

void UICounter::setValue(int tvalue)
{
	this->value = tvalue;
	for (int i = fields.size() - 1; i >= 0; i--)
	{
		fields[i].setValue(tvalue % 10);
		tvalue /= 10;
	}
}

void UICounter::draw(Shader& shader, Camera& camera)
{
	setElements();
	for (int i = 0; i < fields.size(); i++)
	{
		fields[i].draw(shader, camera);
	}
}

void UICounter::setElements()
{

	float offset = width / fields.size();
	int count = fields.size();
	for (int i = 0; i < count; i++)
	{
		fields[i].setPosition(this->position.x + (i * offset) - (((count / 2) - 0.5) * width), this->position.y);
	}
}

