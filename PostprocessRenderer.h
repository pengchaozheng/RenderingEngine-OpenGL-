#pragma once
#include "IRenderer.h"
#include"mesh.h"
#include"glm/glm.hpp"
class PostprocessRenderer :IRenderer
{
public:
	PostprocessRenderer(const std::string& vxShader, const std::string& fgShader);
	virtual ~PostprocessRenderer();
protected:
	static PostMesh* postMesh;
};

