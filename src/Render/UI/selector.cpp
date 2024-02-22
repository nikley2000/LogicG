#include "selector.h"
#include <iostream>


glm::vec2 g_windowSizes(640, 480);

void UI::selector::init()
{
	m_selector.push_back(AND());
	m_selector.push_back(OR());
	m_selector.push_back(LAMP());

}

void UI::selector::update(GLFWwindow *pWindow)
{
	double x = 0.0f;
	double y = 0.0f;
	glfwGetCursorPos(pWindow, &x, &y);
	m_selector[position].setPosition({x, g_windowSizes.y - y });

}

void UI::selector::render()
{
	
	
	m_selector[position].render();
}

void UI::selector::ChangePositon(double direction)
{
	if (UI::selector::position < m_selector.size() - 1 && direction > 0)
	{
		UI::selector::position += 1;
	}

	if (UI::selector::position > 0 && direction < 0)
	{
		UI::selector::position -= 1;
	}

	std::cout << UI::selector::position;
}


void UI::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	UI::selector::ChangePositon(yoffset);
}


Object UI::selector::getObject()
{
	return m_selector[position];
}