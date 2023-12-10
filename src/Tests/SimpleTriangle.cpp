#pragma once
#include "SimpleTriangle.h"
std::string currentDir = "../../../src/Tests/";
// adjust your context here
SimpleTriangle::SimpleTriangle(ContextSettings& settings): Test(settings){
	// constructor
	settings.OPENGL_VERSION = "430";
	settings.SCREEN_HEIGHT = 600;
	settings.SCREEN_WIDTH = 800;
	settings.WINDOW_NAME = "Simple Triangle";
	lastX = 300;
	lastY = 400;
	position = glm::vec3(0.0f);
	rotation = glm::vec3(0.0f);
	scale = glm::vec3(1.0f);
	
	model = glm::mat4(1.0f);
	view = glm::mat4(1.0f); 
	projection = glm::mat4(1.0f);

	vertexArray = nullptr;
	vertexBuffer = nullptr;
	
	shader= nullptr;
	camera= nullptr;
}

void SimpleTriangle::OnSetup() {
					//positions       // colors
	vertices = {	 0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // top 
					-0.5f,-0.5f, 0.0f, 0.0f, 1.0f, 0.0f,// left  bottom
					 0.5f,-0.5f, 0.0f, 0.0f, 0.0f, 1.0f// right bottom
								};

	vertexArray = new dGL::VertexArray();
	vertexBuffer = new dGL::VertexBuffer(&vertices[0],sizeof(float)*vertices.size());
	dGL::VertexArrayAttribute attribute = dGL::VertexArrayAttribute();
	attribute.PushAttributef(3);// positions
	attribute.PushAttributef(3);// colors
	vertexArray->AddVertexArrayAttributef(*vertexBuffer, attribute);
	shader = new dGL::Shader(currentDir + "Resources/Shaders/simpleVertexShader.vert", currentDir + "Resources/Shaders/simpleFragmentShader.frag");
	camera = new dGL::Camera();
	camera->Position = glm::vec3(0.0f, 0.0f, 2.0f);
	glfwSwapInterval(0);
	
	
	

}
void SimpleTriangle::OnImguiUpdate(const double& deltaTime, const ImGuiIO& io) {
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Simple Triangle Inspector");
	ImGui::Text("Triangle Transform");
	ImGui::SliderFloat3("Position", glm::value_ptr(position),-10.0f,10.0f);
	ImGui::SliderFloat3("Rotation", glm::value_ptr(rotation), -180.0f, 180.0f);
	ImGui::SliderFloat3("Scale", glm::value_ptr(scale), 0.0f, 10.0f);

	ImGui::Text("Camera Settings");
	ImGui::SliderFloat("Movement Speed", &camera->MovementSpeed, 0.0f, 50.0f);
	ImGui::SliderFloat("Sensitivity", &camera->MouseSensitivity, 0.0f, 5.0f);
	ImGui::SliderFloat3("Camera Position", glm::value_ptr(camera->Position), -100.f, 100.0f);
	ImGui::SliderFloat("Camera Pitch", &camera->Pitch, -100.f, 100.0f);
	ImGui::SliderFloat("Camera Yaw", &camera->Yaw, -180.f, 180.0f);
	camera->updateCameraVectors();

	ImGui::Text("Application Stats");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
	ImGui::End();

	ImGui::Begin("Controls ");
	ImGui::Text(" To look around, right click with your mouse. ");
	ImGui::Text(" To move around, right click with your mouse and use movement keys. ");
	ImGui::Text( "Movement Keys :\n'W' : forward \n'A' : left \n'S' : backward \n'D' : right \n'Q' : ascend \n'E' : descend  ");

	
	ImGui::End();
}
void SimpleTriangle::OnRenderUpdate(const double& deltaTime,int SCREEN_WIDTH, int SCREEN_HEIGHT) {
	glClearColor(0.28f, 0.28f, 0.28f, 1.0f);
	dGL::glCheckError();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	dGL::glCheckError();
	glEnable(GL_DEPTH_TEST); // enable depth test
	dGL::glCheckError();
	

	model = glm::mat4(1.0f);
	model = glm::scale(model, scale);
	model = glm::rotate(model, glm::radians(rotation.x),glm::vec3(1.0f,0.0f,0.0f));
	model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, position);
	view = camera->GetViewMatrix();
	projection = glm::perspective(glm::radians(camera->Zoom), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 10000.0f);
	shader->SetMatrixf("model", glm::value_ptr(model));
	shader->SetMatrixf("view", glm::value_ptr(view));
	shader->SetMatrixf("projection", glm::value_ptr(projection));

	shader->Bind();
	vertexArray->Bind();
	glDrawArrays(GL_TRIANGLES, 0, 3);
	dGL::glCheckError();

	


}
void SimpleTriangle::InputCallBack(GLFWwindow* window, const double& deltaTime) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {

		if (onCameraMode)
			camera->ProcessKeyboard(dGL::FORWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {

		if (onCameraMode)
			camera->ProcessKeyboard(dGL::BACKWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {

		if (onCameraMode)
			camera->ProcessKeyboard(dGL::LEFT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {

		if (onCameraMode)
			camera->ProcessKeyboard(dGL::RIGHT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		if (onCameraMode)
			camera->ProcessKeyboard(dGL::UPWARD, deltaTime);

	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {

		if (onCameraMode)
			camera->ProcessKeyboard(dGL::DOWNWARD, deltaTime);

	}
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {

		onCameraMode = true;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE) {

		onCameraMode = false;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}


}
void SimpleTriangle::OnMouseMovement(GLFWwindow* window, double xpos, double ypos, const double& deltaTime) {
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;
	if (onCameraMode)
		camera->ProcessMouseMovement(xoffset, yoffset);
}
void SimpleTriangle::OnMouseScroll(GLFWwindow* window, double xoffset, double yoffset, const double& deltaTime) {

	if (onCameraMode)
		camera->ProcessMouseScroll(yoffset);
}