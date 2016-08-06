/*
 * HelpScene.cpp
 *
 *  Created on: Sep 6, 2013
 *      Author: root
 */

#include "HelpScene.h"
#include "MainMenuScene.h"

HelpScene::HelpScene() {
}

void HelpScene::initBackground() {
	CCSprite* background = CCSprite::create("help_screen.png");
	background->setAnchorPoint(CCPointZero);
	background->setPosition(CCPointZero);
	this->addChild(background);
}

void HelpScene::ccTouchesBegan(CCSet* touches, CCEvent* event) {
	stopAllActions();
	CCDirector::sharedDirector()->replaceScene(
			CCTransitionFade::create(0.5f, MainMenu::scene()));
}

bool HelpScene::init() {
	if (!CCLayer::init()) {
		return false;
	}
	initBackground();
	//CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 0);
	setTouchEnabled(true);
	return true;
}

HelpScene::~HelpScene() {
}

CCScene* HelpScene::scene() {
	CCScene *scene = CCScene::create();
	HelpScene *layer = HelpScene::create();
	scene->addChild(layer);
	return scene;
}

