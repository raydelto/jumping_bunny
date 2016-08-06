/*
 * SplashScene.h
 *
 *  Created on: Aug 22, 2013
 *      Author: raydelto
 */

#ifndef SPLASHSCENE_H_
#define SPLASHSCENE_H_
#include "cocos2d.h"
using namespace cocos2d;

class SplashScene: public CCLayer
{
public:
	CREATE_FUNC(SplashScene)
	;
	SplashScene();
	virtual ~SplashScene();
	static CCScene* scene();
	virtual bool init();
	void startGame();
};

#endif /* SPLASHSCENE_H_ */
