#pragma once
#include "IRenderer.h"
#include"mesh.h"
#include"glm/glm.hpp"
class PostprocessRenderer :public IRenderer
{
public:
	PostprocessRenderer(IRenderer* parent, const std::string& vxShader, const std::string& fgShader);
	virtual ~PostprocessRenderer();
protected:
	static PostMesh* postMesh;
	IRenderer* input;
};


class EdgeDetectRenderer :public PostprocessRenderer {
public:
	EdgeDetectRenderer(IRenderer* parent) :PostprocessRenderer(parent,".\\Shaders\\edgeDetect_vert.glsl", ".\\Shaders\\edgeDetect_frag.glsl"){
		if (parent && parent->GetOutputRT()) {
			RenderTexture* input = parent->GetOutputRT();
			mOutputRT = new RenderTexture(input->width(),input->height(),0,GL_RG8);
		}
	};
	virtual void Render() override;
	virtual void Update(float deltaTime) {}
};
