/*
 * BrickSprite.cpp
 *
 *  Created on: Aug 18, 2013
 *      Author: raydelto
 */

#include "BrickSprite.h"

BrickSprite::BrickSprite() :
		m_spring(NULL) {

}

BrickSprite::~BrickSprite() {
}

BrickSprite* BrickSprite::createWithFile(const char* pszFileName) {
	BrickSprite* brick = new BrickSprite();
	if (brick && brick->initWithFile(pszFileName)) {
		brick->autorelease();
		return brick;
	}
	CCLog("Error creating BRICK SPRITE with file name %s", pszFileName);
	CC_SAFE_DELETE(brick);
	return NULL;
}


BrickSprite* BrickSprite::createWithTexture(CCTexture2D *pTexture){
	BrickSprite *brick = new BrickSprite();
    if (brick && brick->initWithTexture(pTexture))
    {
        brick->autorelease();
        return brick;
    }
    CCLog("Error creating BRICK SPRITE with Texture");
    CC_SAFE_DELETE(brick);
    return NULL;
}



