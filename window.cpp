#include "window.h"

Window::Window(unsigned int width, unsigned int height, const char* windowTitle)
{
	this->width = width;
	this->height = height;
	this->windowTitle = windowTitle;

	this->lastX = width / 2;
	this->lastY = height / 2;
	firstMouse = true;

	deltaTime = 0.0f;
	lastFrame = 0.0f;

	windowHandle = this;
	mWorld = new World();
}
Window::~Window()
{
	windowHandle = nullptr;
	if (nullptr != mWorld) {
		delete mWorld;
	}
	for (int i = 0; i < mRenderers.size(); i++) {
		if (mRenderers[i] != nullptr) {
			delete(mRenderers[i]);
		}
	}
}
void Window::Initialize()
{
	if (!GLFWInitialize())
	{
		return;
	}

	if (!CreateWindow())
	{
		return;
	}

	if (!GLEWInitialize())
	{
		return;
	}
	mWorld->Initialize();
	SceneRenderer* sceneRenderer = new SceneRenderer(mWorld);
	mRenderers.push_back(sceneRenderer);
}
void Window::Run()
{
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		ProcessInput();
		glClearColor(1.f, 1.f, 1.f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		mWorld->Update(deltaTime);
		for (int i = 0; i < mRenderers.size(); i++) {
			IRenderer* renderer = mRenderers[i];
			if (nullptr != renderer) {
				renderer->Update(deltaTime);
			}
		}
		for (int i = 0; i < mRenderers.size(); i++) {
			IRenderer* renderer = mRenderers[i];
			if (nullptr != renderer) {
				renderer->Render();
			}
		}
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
void Window::Shutdown()
{
	glfwTerminate();
}
unsigned int Window::GetWidth() { return width; }
unsigned int Window::GetHeight() { return height; }
bool Window::GLFWInitialize()
{
	if (!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW\n";
		std::getchar();
		return false;
	}

	glfwWindowHint(GLFW_SAMPLES, 1);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
#endif
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	return true;
}
bool Window::CreateWindow()
{
	window = glfwCreateWindow(width, height, windowTitle, nullptr, nullptr);
	if (window == nullptr)
	{
		std::cerr << "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorial.\n";
		getchar();
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
	glfwSetCursorPosCallback(window, MouseCallback);
	glfwSetScrollCallback(window, ScrollCallback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	return true;
}
bool Window::GLEWInitialize()
{
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Failed to initialize GLEW\n";
		getchar();
		return false;
	}

	return true;
}
void Window::ProcessInput()
{
	Camera* currentCamera = mWorld->GetMainCamera();

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		currentCamera->ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		currentCamera->ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		currentCamera->ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		currentCamera->ProcessKeyboard(RIGHT, deltaTime);

	/* if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		SaveScreenshot(fileName); */
}
void Window::FramebufferSize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
void Window::Mouse(GLFWwindow* window, double xPos, double yPos)
{
	Camera* currentCamera = mWorld->GetMainCamera();

	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	float xOffset = xPos - lastX;
	float yOffset = lastY - yPos;

	lastX = xPos;
	lastY = yPos;

	currentCamera->ProcessMouseMovement(xOffset, yOffset);
}
void Window::Scroll(GLFWwindow* window, double xOffset, double yOffset)
{
	Camera* currentCamera = mWorld->GetMainCamera();
	currentCamera->ProcessMouseScroll(yOffset);
}
static void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	windowHandle->FramebufferSize(window, width, height);
}
static void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
	windowHandle->Mouse(window, xPos, yPos);
}
static void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	windowHandle->Scroll(window, xOffset, yOffset);
}