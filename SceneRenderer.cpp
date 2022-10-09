#include "SceneRenderer.h"
#include "window.h"

SceneRenderer::SceneRenderer(World* world)
{
	mWorld = world;
	defaultShader = new Shader(".\\Shaders\\teapot.vshader", ".\\Shaders\\teapot.fshader");
	defaultShader->BuildShader();
}
SceneRenderer::~SceneRenderer()
{
	delete defaultShader;
}
void SceneRenderer::Update(float deltaTime) {
	float aspect = g_window->GetWidth() / g_window->GetHeight();
	SetMatrix(aspect);
}
void SceneRenderer::Render()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glViewport(0, 0, g_window->GetWidth(), g_window->GetHeight());
	//RenderPass
	for (const auto& obj : mWorld->GetObjects()) {
		if (nullptr == obj) continue;
		Shader* shader = obj->GetShader();
		shader = (shader == nullptr ? defaultShader : shader);
		SetUniformVariables(shader);
		obj->Draw();
	}
}
void SceneRenderer::SetMatrix(float aspect)
{
	Camera* mainCamera = mWorld->GetMainCamera();

	projection = mainCamera->projMatrix();
	view = mainCamera->viewMatrix();
	model = glm::mat4(1.0f);
	model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
}

void SceneRenderer::SetUniformVariables(Shader* shader)
{
	if (!shader) return;
	shader->Use();
	shader->SetMat4("projection", projection);
	shader->SetMat4("view", view);
	shader->SetMat4("model", model);
	shader->SetVec3("viewPos", mWorld->GetMainCamera()->eye());
	shader->SetVec3("light.direction", mWorld->GetSun());
	shader->SetVec3("light.ambient", glm::vec3(0.5f, 0.5f, 0.5f));
	shader->SetVec3("light.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
	shader->SetVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
	shader->SetVec4("blendParams",glm::vec4(1.f,1.f,0.f,0.f));
	shader->SetFloat("material.shininess", 32.0f);
}