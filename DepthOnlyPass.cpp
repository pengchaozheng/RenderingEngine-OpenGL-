#include "DepthOnlyPass.h"


DepthOnlyPass::DepthOnlyPass(World* world):SceneRenderer(world){
	mOverrideShader = new Shader(".\\Shaders\\depthOnly_vert.glsl", ".\\Shaders\\depthOnly_frag.glsl");
	mOverrideShader->BuildShader();
	mOutputRT = new RenderTexture(800, 600, 0, GL_NONE, GL_DEPTH_COMPONENT32);
}
DepthOnlyPass::~DepthOnlyPass() {
	if (nullptr != mOverrideShader) {
		delete mOverrideShader;
		mOverrideShader = nullptr;
	}
	if (nullptr != mOutputRT) {
		delete mOutputRT;
		mOutputRT = nullptr;
	}
}

void DepthOnlyPass::Update(float deltaTime) {
	model = glm::mat4(1);
	Camera* mainCam = mWorld->GetMainCamera();
	glm::vec3  worldUp = mainCam->front;
	worldUp.y = 0;
	worldUp = glm::normalize(worldUp);
	glm::vec3 center = mainCam->position + worldUp * orthoDepth ;
	view = glm::lookAt(center, center +glm::vec3(0.f,-3.f,0.f), worldUp);
	projection = glm::ortho(-1*orthoWidth, orthoWidth,-1.f* orthoHeight,orthoHeight, -1*orthoDepth, orthoDepth);
}

void DepthOnlyPass::Render() {
	mOutputRT->Bind();
	mOutputRT->Clear();
	for (const auto& obj : mWorld->GetObjects()) {
		if (nullptr == obj) continue;
		SetUniformVariables(mOverrideShader);
		obj->Draw(*mOverrideShader);
	}
}

