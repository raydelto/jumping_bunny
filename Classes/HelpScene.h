/*
 * HelpScene.h
 *
 *  Created on: Sep 6, 2013
 *      Author: root
 */

#ifndef HelpScene_H_
#define HelpScene_H_
#include "cocos2d.h"
USING_NS_CC;

class HelpScene : public CCLayer{
public:
	static cocos2d::CCScene* scene();
	CREATE_FUNC(HelpScene);
	HelpScene();
	virtual bool init();
	void initBackground();
	virtual void ccTouchesBegan(CCSet* touches, CCEvent* event);
	virtual ~HelpScene();
};

#endif /* HelpScene_H_ */
