#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d;

class MainMenu : public cocos2d::CCLayer
{
public:

    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(MainMenu);
    virtual void menuPlayCallback(CCObject* pSender);
    virtual void menuCreditsCallback(CCObject* pSender);
	virtual void menuHelpCallback(CCObject* pSender);
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY)
	virtual void menuInviteCallback(CCObject* pSender);
	#endif
    void initMenu();
    void initBackground();
	void initAudio();
	void initAnimations();
protected:
	virtual void keyBackClicked();

};

#endif // __MAINMENU_SCENE_H__
