/*
 * CreditsScene.cpp
 *
 *  Created on: Sep 6, 2013
 *      Author: root
 */

#include "CreditsScene.h"
#include "MainMenuScene.h"

CreditsScene::CreditsScene() {
}

void CreditsScene::initBackground() {
	CCSprite* background = CCSprite::create("credits_screen.png");
	background->setAnchorPoint(CCPointZero);
	background->setPosition(CCPointZero);
	this->addChild(background);
}

void CreditsScene::ccTouchesBegan(CCSet* touches, CCEvent* event) {
	stopAllActions();
	CCDirector::sharedDirector()->replaceScene(
			CCTransitionFade::create(0.5f, MainMenu::scene()));
}

bool CreditsScene::init() {
	if (!CCLayer::init()) {
		return false;
	}
	initBackground();
	//CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 0);
	setTouchEnabled(true);
	return true;
}

CreditsScene::~CreditsScene() {
}

CCScene* CreditsScene::scene() {
	CCScene *scene = CCScene::create();
	CreditsScene *layer = CreditsScene::create();
	scene->addChild(layer);
	return scene;
}

