#pragma once 

#include "Test.h"
#include <gtc/type_ptr.hpp>

class SimpleTriangle : public Test {
public:
	// adjust your context here
	SimpleTriangle(ContextSettings& settings); 
	~SimpleTriangle() {
		vertexArray->~VertexArray();
		vertexBuffer->~VertexBuffer();
		shader->~Shader();
		delete camera;
	}
	void OnSetup() override;
	void OnImguiUpdate(const double& deltaTime, const ImGuiIO& io) override;
	void OnRenderUpdate(const double& deltaTime,int SCREEN_WIDTH = 800, int SCREEN_HEIGHT = 600) override;
	void InputCallBack(GLFWwindow* window, const double& deltaTime) override;
	void OnMouseMovement(GLFWwindow* window, double xpos, double ypos, const double& deltaTime) override;
	void OnMouseScroll(GLFWwindow* window, double xoffset, double yoffset, const double& deltaTime) override;


private:
	std::vector<float> vertices;

	glm::vec3 position, rotation, scale;
	glm::mat4 model, view, projection;

	dGL::VertexArray* vertexArray;
	dGL::VertexBuffer* vertexBuffer;

	dGL::Shader* shader;
	dGL::Camera* camera;

	float lastX, lastY;
	bool firstMouse = true;
	bool onCameraMode = false;

	





};