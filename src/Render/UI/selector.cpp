#include "selector.h"

#include <iostream>


glm::vec2 g_windowSizes(640, 480);

void UI::selector::init()
{
	m_selector.push_back(ResourcesManager::getSprite("LampOFFSprite"));
	m_selector.push_back(ResourcesManager::getSprite("AndSprite"));
	m_selector.push_back(ResourcesManager::getSprite("OrSprite"));
	//m_selector.push_back(ResourcesManager::getSprite("ButtonSprite"));
	//std::cout << m_selector.size();
}

void UI::selector::update(GLFWwindow *pWindow)
{
	double x = 0.0f;
	double y = 0.0f;
	glfwGetCursorPos(pWindow, &x, &y);
	m_selector[positon]->setPosition({x, g_windowSizes.y - y });

}

void UI::selector::render()
{
	
	
	m_selector[positon]->render();
}

void UI::selector::ChangePositon(double direction)
{
	if (UI::selector::positon < m_selector.size() - 1 && direction > 0)
	{
		UI::selector::positon += 1;
	}

	if (UI::selector::positon > 0 && direction < 0)
	{
		UI::selector::positon -= 1;
	}

	std::cout << UI::selector::positon;
}


void UI::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	UI::selector::ChangePositon(yoffset);
}