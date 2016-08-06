/*
 * BrickSprite.h
 *
 *  Created on: Aug 18, 2013
 *      Author: raydelto
 */

#ifndef BRICKSPRITE_H_
#define BRICKSPRITE_H_

#include <cocos2d.h>
using namespace cocos2d;

class BrickSprite: public CCSprite {
public:

	BrickSprite();
	virtual ~BrickSprite();
    static BrickSprite* createWithFile(const char * pszFileName);
    static BrickSprite* createWithTexture(CCTexture2D *pTexture);

	CCSprite* getSpring() {
		return m_spring;
	}

	void setSpring(CCSprite* spring) {
		m_spring = spring;
	}
protected:
    CCSprite* m_spring;
};

#endif /* BRICKSPRITE_H_ */
