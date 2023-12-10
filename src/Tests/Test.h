#pragma once 

#include "../OpenGL/DolphinGL.h"
#include <glfw3.h>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <filesystem>

struct ContextSettings {
	int SCREEN_WIDTH = 800;
	int SCREEN_HEIGHT = 600;
	std::string WINDOW_NAME = "default window";
	std::string OPENGL_VERSION = "430";
};

class Test {
public:
	Test(ContextSettings& contextSettings) {};

	virtual void OnSetup() {};
	virtual void OnImguiUpdate(const double& deltaTime,const ImGuiIO& io) {};
	virtual void OnRenderUpdate(const double& deltaTime, int SCREEN_WIDTH =800,int SCREEN_HEIGHT = 600) {};
	virtual void InputCallBack(GLFWwindow* window, const double& deltaTime){}
	virtual void OnMouseMovement(GLFWwindow* window, double xpos, double ypos, const double& deltaTime){}
	virtual void OnMouseScroll(GLFWwindow* window, double xoffset, double yoffset, const double& deltaTime){}

};