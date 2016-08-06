#include "AppDelegate.h"
#include "MainMenuScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() {
}

bool AppDelegate::applicationDidFinishLaunching() {
	// initialize director
	CCDirector *pDirector = CCDirector::sharedDirector();

	pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

	CCSize screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();
	//CCSize designSize = CCSizeMake(480, 320);
	CCSize designSize = CCSizeMake(768, 1280);
	std::vector<std::string> searchPaths;

	CCLog("Screen width = %f height = %f\n", screenSize.width, screenSize.height);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//IOS Specific Settings
	// OpenGLView initialized in testsAppDelegate.mm on ios platform
	//if device's screen width is greater than 768, use high definition images

	if (screenSize.width >= 640) {
		searchPaths.push_back("iphone5");
		pDirector->setContentScaleFactor(1136.0f / designSize.height);
	} else {
		searchPaths.push_back("iphone");
		pDirector->setContentScaleFactor(1024.0f / designSize.height);
	}

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY ||  CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
	if (screenSize.height >= 1280) {
		//Z10
		CCLog("Loading Z10 Design Size");
		searchPaths.push_back("hd");
		pDirector->setContentScaleFactor(1280.0f / designSize.height);
		CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionExactFit);


	}else{
		//Q5 and Q10
		CCLog("Loading Q10 / Q5 Design Size");
		searchPaths.push_back("q");
		pDirector->setContentScaleFactor(720.0f / designSize.height);
		CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionFixedHeight);
	}
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID ||  CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	if (screenSize.height >= 1280) {
		//High Resolution
		CCLog("Loading Android HD Size");
		searchPaths.push_back("hd");
		pDirector->setContentScaleFactor(1280.0f / designSize.height);

	} else if (screenSize.height >= 800) {
		//Mid resolution
		CCLog("Loading Android MD Size");
		searchPaths.push_back("md");
		pDirector->setContentScaleFactor(800.0f / designSize.height);

	} else {
		//Low resolution
		CCLog("Loading Android SD Size");
		searchPaths.push_back("sd");
		pDirector->setContentScaleFactor(320.0f / designSize.height);

	}
	CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionExactFit);
#endif
	CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);




	// set FPS. the default value is 1.0/60 if you don't call this
	pDirector->setAnimationInterval(1.0 / 60);

	// create a scene. it's an autorelease object

	// run
	pDirector->runWithScene(MainMenu::scene());
	// add layer as a child to scene

	CCLog("Finished launching...");
	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
	CCDirector::sharedDirector()->stopAnimation();
	// if you use SimpleAudioEngine, it must be pause
	// CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	CCDirector::sharedDirector()->startAnimation();

	// if you use SimpleAudioEngine, it must resume here
	// CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
