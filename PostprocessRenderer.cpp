#include "PostprocessRenderer.h"
#include "shader.h"

PostMesh* PostprocessRenderer::postMesh = nullptr;

PostprocessRenderer::PostprocessRenderer(const std::string& vxShader,const std::string& fgShader) {
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
