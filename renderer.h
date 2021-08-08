#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "camera.h"
#include "model.h"
#include "shader.h"

class Renderer
{
public:
	Renderer();
	Renderer(const Renderer&) = delete;
	~Renderer();

	Camera* GetCamera();
	void Render(float aspect);
private:
	// Shader ����
	Shader* currentShader;

	// matrix ����
	glm::mat4 projection;
	glm::mat4 view;
	glm::mat4 model;

	// Camera ����
	Camera* camera;

	// model ����
	Model* object;

	// Light Direction ����
	glm::vec3 lightDir;

	void SetMatrix(float aspect); // Parameter: float aspect => aspect�� window���� ������. => �Ϲ�ȭ??
	void SetUniformVariables();
};