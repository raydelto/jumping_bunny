#include "MainMenuScene.h"
#include "JumpingGameScene.h"
#include "CreditsScene.h"
#include "HelpScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

USING_NS_CC;

CCScene* MainMenu::scene() {
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	MainMenu *layer = MainMenu::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MainMenu::init() {
	//////////////////////////////
	// 1. super init first
	if (!CCLayer::init()) {
		return false;
	}
	this->setKeypadEnabled(true);
	initAudio();
	initAnimations();
	initBackground();
	initMenu();

	return true;
}

void MainMenu::menuPlayCallback(CCObject* pSender) {
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	SimpleAudioEngine::sharedEngine()->stopAllEffects();

	// Change the game state to JumpingGame
	CCScene *pScene = JumpingGame::scene();
	CCDirector::sharedDirector()->replaceScene(pScene);
}

void MainMenu::menuCreditsCallback(CCObject* pSender) {
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f,  CreditsScene::scene()));
}


#if (CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY)
void MainMenu::menuInviteCallback(CCObject* pSender) {
	//BBM Invite code
}

#endif

void MainMenu::menuHelpCallback(CCObject* pSender) {
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f,  HelpScene::scene()));
}


void MainMenu::initMenu() {
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	// create menu items

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY)
	CCMenuItemImage *inviteItem = CCMenuItemImage::create("invite_friends.png", "invite_friends.png", this, menu_selector(MainMenu::menuInviteCallback));
	inviteItem->setPosition(ccp(winSize.width/2,winSize.height *.55));
	#endif
	CCMenuItemImage *playItem = CCMenuItemImage::create("play_button.png", "play_button_pressed.png", this, menu_selector(MainMenu::menuPlayCallback));
	playItem->setPosition(ccp(winSize.width/2,winSize.height *.4));

	CCMenuItemImage *creditsItem = CCMenuItemImage::create("credits_button.png", "credits_button_pressed.png", this, menu_selector(MainMenu::menuCreditsCallback));
	creditsItem->setPosition(ccp(winSize.width/2,winSize.height *.25));

	CCMenuItemImage *helpItem = CCMenuItemImage::create("help_button.png", "help_button_pressed.png", this, menu_selector(MainMenu::menuHelpCallback));
	helpItem->setPosition(ccp(winSize.width/2,winSize.height *.10));




	// create menu, it's an autorelease object

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY)
	CCMenu* pMenu = CCMenu::create(inviteItem, playItem, creditsItem, helpItem, NULL);
	#else
	CCMenu* pMenu = CCMenu::create(playItem, creditsItem, helpItem, NULL);
	#endif

	
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);
}

void MainMenu::initBackground() {
	CCSprite* background = CCSprite::create("splash_screen.png");
	background->setAnchorPoint(CCPointZero);
	background->setPosition(CCPointZero);
	this->addChild(background, 0);
}

void MainMenu::initAudio() {
	// Set background and audio effect volumes
	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1.0f);
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.0f);

	// Preload background music
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("music.ogg");

	// Preload audio effect
	SimpleAudioEngine::sharedEngine()->preloadEffect("jump.wav");
}

void MainMenu::initAnimations() {
	//Red Bricks init
	CCArray *redBrickFrames = new CCArray();
	redBrickFrames->addObject(CCSpriteFrame::create("red_brick.png", CCRectMake(0, 0, 198, 74)));
	redBrickFrames->addObject(CCSpriteFrame::create("broke_red_brick.png", CCRectMake(0, 0, 198, 74)));
	CCAnimation* redBrickAnimation = CCAnimation::createWithSpriteFrames(redBrickFrames);
	CCAnimationCache::sharedAnimationCache()->addAnimation(redBrickAnimation, "RedBrickAnimation");
	//Springs init
	CCArray *springFrames = new CCArray();
	springFrames->addObject(CCSpriteFrame::create("coffee.png", CCRectMake(0, 0, 58, 68)));
	springFrames->addObject(CCSpriteFrame::create("coffee2.png", CCRectMake(0, 0, 58, 68)));
	CCAnimation* springAnimation = CCAnimation::createWithSpriteFrames(springFrames);
	CCAnimationCache::sharedAnimationCache()->addAnimation(springAnimation, "SpringAnimation");
}

void MainMenu::keyBackClicked() {
	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
