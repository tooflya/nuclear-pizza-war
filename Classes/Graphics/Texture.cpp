#ifndef CONST_TEXTURE
#define CONST_TEXTURE

#include "Texture.h"

// ===========================================================
// Inner Classes
// ===========================================================

// ===========================================================
// Constants
// ===========================================================

// ===========================================================
// Fields
// ===========================================================

// ===========================================================
// Constructors
// ===========================================================

Texture::Texture(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount)
{
	this->mTexture = CCTextureCache::sharedTextureCache()->addImage(pszFileName);

	this->mTextureFileName = pszFileName;
			
	this->mHorizontalFramesCount = pHorizontalFramesCount;
	this->mVerticalFramesCount   = pVerticalFramesCount;
}

// ===========================================================
// Methods
// ===========================================================

int Texture::getHorizontalFramesCount()
{
	return this->mHorizontalFramesCount;
}

int Texture::getVerticalFramesCount()
{
	return this->mVerticalFramesCount;
}

CCTexture2D* Texture::getTexture()
{
	return this->mTexture;
}

// ===========================================================
// Virtual Methods
// ===========================================================

#endif