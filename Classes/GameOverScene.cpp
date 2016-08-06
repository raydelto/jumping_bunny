#include "GameOverScene.h"
#include "JumpingGameScene.h"
#include "CreditsScene.h"

using namespace cocos2d;

bool GameOverScene::init() {
	if (CCScene::init()) {
		this->_layer = GameOverLayer::create();
		this->_layer->retain();
		this->addChild(_layer);

		return true;
	} else {
		return false;
	}
}

GameOverScene::~GameOverScene() {
	if (_layer) {
		_layer->release();
		_layer = NULL;
	}
}

bool GameOverLayer::init() {
	this->setKeypadEnabled(true);
	initBackground();
	initMenu();
	initScorePanel();

	return true;
}

void GameOverLayer::initScorePanel() {
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite* scorePanel = CCSprite::create("score_panel.png");
	scorePanel->setPosition(ccp(winSize.width/2,winSize.height * 0.72f));
	this->addChild(scorePanel,1);
	this->_label = CCLabelTTF::create("0", "Felt", 48);
	_label->retain();
	_label->setColor(ccc3(50, 200, 50));
	_label->setPosition(ccp(winSize.width/2, winSize.height*0.74));
	this->addChild(_label,1);

}


void GameOverLayer::initMenu() {
	// create menu items
	CCMenuItemImage *playItem = CCMenuItemImage::create("play_button.png", "play_button.png", this, menu_selector(GameOverLayer::menuPlayCallback));
	playItem->setPosition(ccp(playItem->getContentSize().width/2,CCDirector::sharedDirector()->getWinSize().height /2));

	CCMenuItemImage *exitItem = CCMenuItemImage::create("credits_button.png", "credits_button_pressed.png", this, menu_selector(GameOverLayer::menuCreditsCallback));
	exitItem->setPosition(
			ccp(CCDirector::sharedDirector()->getWinSize().width - (exitItem->getContentSize().width/2), CCDirector::sharedDirector()->getWinSize().height /2));

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(playItem, exitItem, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);
}

void GameOverLayer::initBackground() {
	CCSprite* background = CCSprite::create("gameover.png");
	background->setAnchorPoint(CCPointZero);
	background->setPosition(CCPointZero);
	this->addChild(background, 0);
}


void GameOverLayer::menuCreditsCallback(CCObject* pSender) {
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f,  CreditsScene::scene()));
}

void GameOverLayer::exitGame(){
	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

}



void GameOverLayer::menuPlayCallback(CCObject* pSender) {
	// Change the game state to JumpingGame
	CCScene *pScene = JumpingGame::scene();
	CCDirector::sharedDirector()->replaceScene(pScene);

}

void GameOverLayer::gameOverDone() {
	CCDirector::sharedDirector()->replaceScene(JumpingGame::scene());
}

GameOverLayer::~GameOverLayer() {
	if (_label) {
		_label->release();
		_label = NULL;
	}
}
void GameOverLayer::keyBackClicked() {
	CCLog("\nKeyBack pressed\n");
	exitGame();
}
