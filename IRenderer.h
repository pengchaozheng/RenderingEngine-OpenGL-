#pragma once
#include"Shader.h"
#include"World.h"
#include"RenderTexture.h"

class IRenderer {
public:
	virtual ~IRenderer() {};
	__forceinline RenderTexture* GetOutputRT() noexcept { return mOutputRT;}
	__forceinline void SetWorld(World* world) noexcept { mWorld = world; }
	virtual void Render() = 0;
	virtual void Update(float deltaTime) {}
protected:
	World*	mWorld;
	Shader* mOverrideShader;
	RenderTexture* mOutputRT;
};