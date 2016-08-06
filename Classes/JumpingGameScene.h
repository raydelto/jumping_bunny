#ifndef __JUMPINGGAME_SCENE_H__
#define __JUMPINGGAME_SCENE_H__

#include "cocos2d.h"
#include "BrickSprite.h"

#define MAX_BRICKS 16
#define MAX_SPRINGS 3
#define MAX_VISIBLE_BRICKS 13
#define GREEN_BRICK 1
#define BLUE_BRICK 2
#define BLUE_BRICK_REVERSE 3
#define RED_BRICK 4
#define RED_BRICK_BROKEN 5
#define WHITE_BRICK 6
#define WHITE_BRICK_HIDDEN 7
#define SPRING 8
#define SPRING_PRESSED 9
#define MAX_SPEED 450.0f
#define SPEED_STEP 10.0f

class JumpingGame : public cocos2d::CCLayer
{
public:

	JumpingGame();
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(JumpingGame);
    virtual void ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    virtual void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    void updateGame(float dt);
    void initBackground();
    void initArrows();
    void initGreenBricks();
    BrickSprite* initBrick(const char * path);
    void initFloor();
    void initPlayer();
    void initScoreLabel();
    void updatePlayer();
    void checkCollisions();
    void scrollScene();
    void updateBricks();
    void updateScore();
    void jump();
    void springJump();



protected:
    void keyBackClicked(void);
    void blueBrickMoveFinished(cocos2d::CCNode* sender);
    void redBrickMoveFinished(cocos2d::CCNode* sender);
    void moveBrick(BrickSprite* sprite, int reverse);
	bool collisions(cocos2d::CCSprite* sprite, cocos2d::CCPoint* point);
	bool collisions(cocos2d::CCSprite* sprite1,	cocos2d::CCSprite* sprite2);


private:
    int m_playerScore;
    bool m_playerJumping;
    bool m_playerSpringJumping;
    bool m_gameOver;
    float m_positionRatio;
    cocos2d::CCSprite* m_player;
    cocos2d::CCSprite* m_floor;
    cocos2d::CCSprite* m_leftArrow;
    cocos2d::CCSprite* m_rightArrow;
    cocos2d::CCPoint m_playerVelocity;
    cocos2d::CCSprite* m_lastGeneratedBrick;
    cocos2d::CCLabelTTF* m_scoreLabel;
    cocos2d::CCArray* m_visibleBricks;
    cocos2d::CCArray* m_springs;
    cocos2d::CCSize m_winSize;

    int getRandomX(cocos2d::CCSprite* sprite);
    BrickSprite* getBrickOutsideScreen();
    float getHigherYPosition();
    BrickSprite* repositionBrick(BrickSprite* sprite);
    BrickSprite* getNewBrick(BrickSprite* oldBrick);
    BrickSprite* handleBrick(BrickSprite* oldBrick, const char * path, int tag1, int tag2, int newTag);
    int getRandom(int min, int max);
    void initBrickSpecs(BrickSprite* brick);
    void setSpring(BrickSprite* brick);
    void increaseSpeed(float dt);
    void decreaseSpeed(float dt);
    cocos2d::CCSprite* createSpring();
    void brickCollision(BrickSprite* brick);
    bool removeSpring(BrickSprite* brick);
    bool removeBrick(BrickSprite* brick);
    bool hideBrick(BrickSprite* brick);


};

#endif // __JUMPINGGAME_SCENE_H__
