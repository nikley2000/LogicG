#pragma once
#include <vector>
#include <memory>
#include "../../Render/Sprite.h"
#include <string>
#include "../../Resources/ResourceManager.h"
#include <GLFW/glfw3.h>
#include "../../Resources/Objects/Objects.h"


namespace UI
{


	

	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

	class selector
	{
	public:
		selector() = delete;
		~selector() = delete;

		static void init();
		
		static void update(GLFWwindow* pWindow);

		static void render();


		static void ChangePositon(double direction);

		static Object getObject();


	private:
		typedef std::vector<Object> SelectorVec;
		static inline  SelectorVec m_selector;
		static inline int position = 0;
	};
}