/*
 * SplashScene.cpp
 *
 *  Created on: Aug 22, 2013
 *      Author: raydelto
 */

#include "SplashScene.h"
#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

USING_NS_CC;

SplashScene::SplashScene() {

}

SplashScene::~SplashScene() {
}


CCScene* SplashScene::scene() {
	CCScene *scene = CCScene::create();
	SplashScene *layer = SplashScene::create();
	scene->addChild(layer);
	return scene;
}

bool SplashScene::init() {
	if (!CCLayer::init()) {
		return false;
	}

	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

	CCSprite* logo = CCSprite::create("splash_screen.png");
	logo->setPosition(ccp(screenSize.width / 2, screenSize.height / 2));
	this->addChild(logo, 1);
	CCFiniteTimeAction *seq1 = CCSequence::create(CCDelayTime::create(3.0), CCCallFuncN::create(this, callfuncN_selector(SplashScene::startGame)), NULL);

	this->runAction(seq1);
	return true;
}


void SplashScene::startGame() {
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f,MainMenu::scene()));

}
