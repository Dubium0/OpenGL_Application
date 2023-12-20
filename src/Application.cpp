// Application.cpp : Defines the entry point for the application.
// creates context for opengl
// runs Actual test

#include "Application.h"
#include "Tests/SimpleTriangle.h"

// global variables
double deltaTime;
int current_WIDTH, currentHEIGHT; // this values will be changed in frame buffer size callback
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
//global test
Test* test;

int main()
{
    //Insert your test here---------
    ContextSettings settings;
    test = new SimpleTriangle(settings);

    // glfw initialization------------------------------------------------------------
    GLFWwindow* window;

    int major = settings.OPENGL_VERSION[0] - '0';
    int minor = settings.OPENGL_VERSION[1] - '0';
    
    /* Initialize the library */
    if (!glfwInit())
        return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    current_WIDTH = settings.SCREEN_WIDTH;
    currentHEIGHT = settings.SCREEN_HEIGHT;
    window = glfwCreateWindow(current_WIDTH, currentHEIGHT, settings.WINDOW_NAME.c_str(), NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK)
        std::cout << "GlEW IS NOT OKEY (HELP)" << std::endl;

    glViewport(0, 0, current_WIDTH, currentHEIGHT);  // this is ver common thats why I'm setting this here

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // adjust viewport size
    glfwSetCursorPosCallback(window, mouse_callback); // mouse position 
    glfwSetScrollCallback(window, scroll_callback); // scrolling

    

    //--------------------------------------------------------------------------------------------------------
    //--init imgui---------------
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    std::string version = "#version " + settings.OPENGL_VERSION;
    const char* glsl_version = version.c_str();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    //-------------------------------

    // call test setup 
    test->OnSetup();
	
    double lastFrame =0;
    while (!glfwWindowShouldClose(window)) {
        // delta time calculation
        double currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

       
        //process input
        processInput(window);

        // Imgui Update ----------------------------------
        test->OnImguiUpdate(deltaTime,io);
        //------------------------------------------------
        //--Render----------------------------------------
        ImGui::Render();
        test->OnRenderUpdate(deltaTime,current_WIDTH,currentHEIGHT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        //------------------------------------------------

        //--- finalize loop--------------
        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    
    glfwDestroyWindow(window);
    glfwTerminate();
	return 0;
}

// set your default call backs in those function
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
    if (!height)  height = 1;
    current_WIDTH = width;
    currentHEIGHT = height;
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    test->OnMouseScroll(window, xoffset, yoffset, deltaTime);
}
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
    test->OnMouseMovement(window, xposIn, yposIn, deltaTime);
}
void processInput(GLFWwindow* window) {
    test->InputCallBack(window, deltaTime);
}