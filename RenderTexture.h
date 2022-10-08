#pragma once
#include<GL/glew.h>
#include <glm/glm.hpp>
class RenderTexture
{
public:
	RenderTexture(int width, int height,int depth =0,GLenum formatColor = GL_RGBA8, GLenum formatDepth = GL_NONE);
	~RenderTexture() noexcept;
	void Bind() const;
	__forceinline int  height() const noexcept { return mHeight;}
	__forceinline int  width() const noexcept {return mWidth;}
	__forceinline GLenum formatColor() const noexcept {return mFormatColor;}
	__forceinline GLenum formatDepth() const noexcept { return mFormatDepth; }
	__forceinline void SetClearColor(glm::vec4 color) { mClearColor = color; }
	void Clear()const noexcept;
private:
	int mHeight, mWidth;
	GLenum mFormatColor;
	GLenum mFormatDepth;
	GLenum mDepth;
	GLuint mFbo{GL_NONE};
	GLuint mRboDepth{GL_NONE};
	GLuint mTexColor{GL_NONE};
	GLuint mTexDepth{};
	glm::vec4  mClearColor;
};

