#pragma once 

#include "../OpenGL/DolphinGL.h"
#include <glfw3.h>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <filesystem>
// hint for context that will be created in main
struct ContextSettings {
	int SCREEN_WIDTH = 800;
	int SCREEN_HEIGHT = 600;
	std::string WINDOW_NAME = "default window";
	std::string OPENGL_VERSION = "430";
};

class Test {
public:
	Test(ContextSettings& contextSettings) {};

	// This function called after initialization of openGl context so you can setup your vertex array and shader here.
	virtual void OnSetup() {}; 
	// Create your Imgui stuff here
	virtual void OnImguiUpdate(const double& deltaTime,const ImGuiIO& io) {};
	// Do your rendering stuff here
	virtual void OnRenderUpdate(const double& deltaTime, int SCREEN_WIDTH =800,int SCREEN_HEIGHT = 600) {};
	// Keyboard input callback
	virtual void InputCallBack(GLFWwindow* window, const double& deltaTime){}
	// Get mouse position on change
	virtual void OnMouseMovement(GLFWwindow* window, double xpos, double ypos, const double& deltaTime){}
	// Get mouse scroll offset
	virtual void OnMouseScroll(GLFWwindow* window, double xoffset, double yoffset, const double& deltaTime){}

};