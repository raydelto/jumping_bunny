#ifndef _GAME_OVER_SCENE_H_
#define _GAME_OVER_SCENE_H_

#include "cocos2d.h"

class GameOverLayer : public cocos2d::CCLayer
{
public:
    GameOverLayer():_label(NULL) {};
    virtual ~GameOverLayer();
    bool init();
    CREATE_FUNC(GameOverLayer);

    void gameOverDone();
    virtual void menuPlayCallback(CCObject* pSender);
    virtual void menuCreditsCallback(CCObject* pSender);
    void initMenu();
    void initBackground();
    void initScorePanel();

    CC_SYNTHESIZE_READONLY(cocos2d::CCLabelTTF*, _label, Label);
protected:
    void keyBackClicked(void);
private:
    void exitGame();
};

class GameOverScene : public cocos2d::CCScene
{
public:
    GameOverScene():_layer(NULL) {};
    ~GameOverScene();
    bool init();
    CREATE_FUNC(GameOverScene);


    CC_SYNTHESIZE_READONLY(GameOverLayer*, _layer, Layer);

};

#endif // _GAME_OVER_SCENE_H_
