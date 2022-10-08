#include "RenderTexture.h"
#include<iostream>
RenderTexture::RenderTexture(int width, int height, int depth,  GLenum formatColor, GLenum formatDepth)
	:mFormatColor(formatColor), mFormatDepth(formatDepth) 
	, mWidth(width), mHeight(height) , mDepth(depth) {
	glGenFramebuffers(1,&mFbo);
	glBindFramebuffer(GL_FRAMEBUFFER,mFbo);
	if (0 != depth) {
		glGenRenderbuffers(1, &mRboDepth);
		glBindRenderbuffer(GL_RENDERBUFFER, mRboDepth);
		GLenum format = GL_NONE;
		if (16 == depth) {
			format = GL_DEPTH_COMPONENT16;
		}else if (24 == depth) {
			format = GL_DEPTH_COMPONENT24;
		}
		else if (32 == depth) {
			format = GL_DEPTH_COMPONENT32;
		}
		glRenderbufferStorage(GL_RENDERBUFFER, format,mWidth,mHeight);
	}
	if (mFormatColor) {
		glGenTextures(1, &mTexColor);
		glBindTexture(GL_TEXTURE_2D, mTexColor);
		glTexImage2D(GL_TEXTURE_2D,0, formatColor, mWidth,mHeight,0,GL_RGBA,GL_UNSIGNED_BYTE,0);
		glFramebufferTexture2D(GL_DRAW_BUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D, mTexColor,0);
	}
	if (mFormatDepth) {
		glGenTextures(1,&mTexDepth);
		glBindTexture(GL_TEXTURE_2D,mTexDepth);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, mWidth, mHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, mTexDepth, 0);
	}
	//disable color buffer
	if (!mFormatColor) {
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
	}
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "Failed to bind framebuffer" << std::endl;
	}
	glBindFramebuffer(GL_FRAMEBUFFER,0);
}

RenderTexture::~RenderTexture() noexcept {
	if (0 != mRboDepth) {
		glDeleteRenderbuffers(1, &mRboDepth);
		mRboDepth = 0;
	}
	if (0 != mTexColor) {
		glDeleteTextures(1,&mTexColor);
		mTexColor = 0;
	}
	if (0 != mTexDepth) {
		glDeleteTextures(1, &mTexDepth);
		mTexDepth = 0;
	}
	if (0 != mFbo) {
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		glDeleteFramebuffers(1,&mFbo);
		mFbo = 0;
		
	}
}
void RenderTexture::Bind() const {
	glViewport(0, 0, mWidth, mHeight);
	glBindFramebuffer(GL_FRAMEBUFFER,mFbo);
}

void RenderTexture::Clear()const noexcept {
	glClearColor(0.f, 0.f, 0.f, 1.f);
	GLuint clearMask = GL_NONE;
	if (mFormatColor) {
		clearMask |= GL_COLOR_BUFFER_BIT;
	}
	if (mFormatDepth) {
		clearMask |= GL_DEPTH_BUFFER_BIT;
	}
	glClear(clearMask);
}
