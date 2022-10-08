#include "PostprocessRenderer.h"
#include "shader.h"

PostMesh* PostprocessRenderer::postMesh = nullptr;

PostprocessRenderer::PostprocessRenderer(IRenderer* parent,const std::string& vxShader,const std::string& fgShader) {
	input = parent;
	mOverrideShader = new Shader(vxShader.c_str(), fgShader.c_str());
	mOverrideShader->BuildShader();
	if (nullptr == postMesh) {
		postMesh = new PostMesh();
	}
}

PostprocessRenderer::~PostprocessRenderer() {
	delete mOverrideShader;
	mOverrideShader = nullptr;
}


void EdgeDetectRenderer::Render() {
	mOutputRT->Bind();
	mOverrideShader->Use();
	glBindTexture(GL_TEXTURE_2D,input->GetOutputRT()->textureDepth());
	postMesh->Draw(*mOverrideShader);
}