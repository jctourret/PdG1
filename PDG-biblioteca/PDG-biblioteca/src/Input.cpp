#include "Input.h"

Input::Input(Window* _window)
{
	window = _window;
}

Input::~Input()
{

}

bool Input::isKeyDown(int key)
{
	return (glfwGetKey(window->getWindow(), key) == GLFW_PRESS);
}

bool Input::isKeyUp(int key)
{
	return (glfwGetKey(window->getWindow(), key) == GLFW_RELEASE);
}
