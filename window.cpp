#include "window.h"
#include"DepthOnlyPass.h"
#include"PostprocessRenderer.h"
#include"event_handler.h"
Window::Window(unsigned int width, unsigned int height, const char* windowTitle)
{
	this->width = width;
	this->height = height;
	this->windowTitle = windowTitle;

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

	DepthOnlyPass* depthOnlyRenderer = new DepthOnlyPass(mWorld);
	mRenderers.push_back(depthOnlyRenderer);
	EdgeDetectRenderer* edgeRender = new EdgeDetectRenderer(depthOnlyRenderer);
	mRenderers.push_back(edgeRender);

	SceneRenderer* sceneRenderer = new SceneRenderer(mWorld);
	mRenderers.push_back(sceneRenderer);
	static glfwCallbackData cb{ mWorld->GetMainCamera()};
	glfwSetWindowUserPointer(window, &cb);
}
void Window::Run()
{
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glClearColor(0.f, 0.f, 0.f, 0.0f);
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
	glfwSetKeyCallback(window, glfwindow_key_cb);
	glfwSetMouseButtonCallback(window, glfwindow_mouseButton_cb);
	glfwSetCursorPosCallback(window, glfwindow_mouseMotion_cb);
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
void Window::FramebufferSize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
static void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	windowHandle->FramebufferSize(window, width, height);
}