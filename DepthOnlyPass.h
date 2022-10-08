#include"SceneRenderer.h"
#pragma once

const float orthoWidth = 5.f;
const float orthoHeight = orthoWidth;
const float orthoDepth = orthoWidth;

class DepthOnlyPass :public SceneRenderer
{
public:
	DepthOnlyPass(World* world);
	virtual ~DepthOnlyPass() override;
	virtual void Render() override;
	virtual void Update(float deltaTime) override;
};

