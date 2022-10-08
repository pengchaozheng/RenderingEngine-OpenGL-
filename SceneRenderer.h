#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "camera.h"
#include "model.h"
#include "shader.h"
#include "World.h"
#include "RenderTexture.h"
#include "IRenderer.h"
class Window;
extern  Window* g_window;
class SceneRenderer :public IRenderer
{
public:
	SceneRenderer(World* world);
	SceneRenderer(const SceneRenderer&) = delete;
	virtual ~SceneRenderer() override;
	virtual void Render() override;
	virtual void Update(float deltaTime) override;
private:
	// Shader 
	Shader* currentShader;
protected:
	// matrix 
	glm::mat4 projection;
	glm::mat4 view;
	glm::mat4 model;
	void SetMatrix(float aspect); // Parameter: float aspect => aspect
	void SetUniformVariables(Shader* shader);
};