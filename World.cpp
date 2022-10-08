#include "World.h"
World::World() {
	mMainCamera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
}

World::~World() {
	if (nullptr != mMainCamera) {
		delete mMainCamera;
	}
	for (const auto& obj : mObjects) {
		if (nullptr != obj) {
			delete obj;
		}
	}
	mObjects.resize(0);
	mObjects.shrink_to_fit();
}


void World::Initialize() {
	Model* object = new Model();
	mSun = glm::vec3(1.0f, glm::sqrt(3.0f), -glm::sqrt(3.0f));
	object->LoadModel("teapot/teapot.obj");
	Shader* shader = new Shader("teapot.vshader", "teapot.fshader");
	shader->BuildShader();
	object->SetShader(shader);
	mObjects.push_back(object);

}
void World::Update(float detalTime) {
	for (const auto& obj : mObjects) {
		if (nullptr != obj) {
			obj->Update(detalTime);
		}
	}
}
