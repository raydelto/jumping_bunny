/*
 * CreditsScene.h
 *
 *  Created on: Sep 6, 2013
 *      Author: root
 */

#ifndef CREDITSSCENE_H_
#define CREDITSSCENE_H_
#include "cocos2d.h"
USING_NS_CC;

class CreditsScene : public CCLayer{
public:
	static cocos2d::CCScene* scene();
	CREATE_FUNC(CreditsScene);
	CreditsScene();
	virtual bool init();
	void initBackground();
	virtual void ccTouchesBegan(CCSet* touches, CCEvent* event);
	virtual ~CreditsScene();
};

#endif /* CREDITSSCENE_H_ */
