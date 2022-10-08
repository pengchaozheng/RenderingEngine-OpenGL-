#pragma once
#include"Camera.h"
#include"model.h"
#include<vector>
class World
{
public:
	World();
	~World();
	void Initialize();
	__forceinline  Camera* GetMainCamera() noexcept {return mMainCamera;}
	__forceinline const std::vector<Model*>& GetObjects() { return mObjects;}
	__forceinline  glm::vec3 GetSun() noexcept { return mSun;}
	void Update(float detalTime);
private:
	glm::vec3   mSun;
	std::vector<Model*> mObjects;
	Camera* mMainCamera;
};

