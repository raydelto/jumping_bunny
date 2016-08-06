#include "JumpingGameScene.h"
#include "GameOverScene.h"
#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

USING_NS_CC;

JumpingGame::JumpingGame() :
		m_playerSpringJumping(false), m_player(NULL), m_floor(NULL), m_leftArrow(
				NULL), m_rightArrow(NULL), m_lastGeneratedBrick(NULL) {

	m_visibleBricks = new CCArray();
	m_springs = new CCArray();
	m_winSize = CCDirector::sharedDirector()->getWinSize();
}

CCScene* JumpingGame::scene() {
	CCScene *scene = CCScene::create();
	JumpingGame *layer = JumpingGame::create();
	scene->addChild(layer);
	return scene;
}

void JumpingGame::initArrows() {
	m_leftArrow = CCSprite::create("left_arrow.png");
	m_leftArrow->setAnchorPoint(ccp(0, 0));
	m_leftArrow->setPosition(ccp(0.0f, m_winSize.height * 0.1));
	m_rightArrow = CCSprite::create("right_arrow.png");
	m_rightArrow->setAnchorPoint(ccp(0, 0));
	m_rightArrow->setPosition(
			ccp(m_winSize.width - (m_rightArrow->getContentSize().width),
					m_winSize.height * 0.1));
	this->addChild(m_leftArrow, 2);
	this->addChild(m_rightArrow, 2);
}

void JumpingGame::initScoreLabel() {
	CCSprite* scorePannel = CCSprite::create("score_panel.png");
	scorePannel->setPosition(
			ccp(m_winSize.width / 2,
					m_winSize.height
							- (scorePannel->getContentSize().height / 2)));
	this->addChild(scorePannel, 4);
	m_scoreLabel = CCLabelTTF::create("0", "Felt", 32);
	m_scoreLabel->setColor(ccc3(50, 200, 50));
	//m_scoreLabel->setAnchorPoint(ccp(0.0f, 0.0f));
	m_scoreLabel->setPosition(
			ccp(m_winSize.width / 2,
					m_winSize.height
							- (m_scoreLabel->getTextureRect().size.height * 0.75)));

	m_scoreLabel->setString("0");

	m_scoreLabel->setVisible(true);
	this->addChild(m_scoreLabel, 5);
}

void JumpingGame::initFloor() {
	m_floor = CCSprite::create("floor.png");
	m_floor->setAnchorPoint(CCPointZero);
	m_floor->setPosition(CCPointZero);
	this->addChild(m_floor, 0);
}

bool JumpingGame::init() {
	if (!CCLayer::init()) {
		return false;
	}
	m_positionRatio = m_winSize.height / MAX_VISIBLE_BRICKS;
	this->setKeypadEnabled(true);

	srand(time(NULL));

	initBackground();
	initFloor();
	initArrows();
	initGreenBricks();
	initPlayer();
	initScoreLabel();

	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music.ogg", true);
	CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(
			this, 0);
	this->schedule(schedule_selector(JumpingGame::updateGame));

	m_playerJumping = true;
	jump();

	return true;
}

void JumpingGame::ccTouchesBegan(CCSet* touches, CCEvent* event) {
	CCTouch* touch = (CCTouch*) (touches->anyObject());
	CCPoint location = touch->getLocation();
	float velocityFactor = 1.0;

	//BlackBerry Q series Hack
	#if(CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY ||  CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
	{
		CCSize screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();

		if(screenSize.height == 720){
			velocityFactor = 2.0;
		}
	}
	#endif

	if (collisions(m_leftArrow, &location)) {
		this->schedule(schedule_selector(JumpingGame::decreaseSpeed), 0.25);

		m_playerVelocity.x -= 150 * velocityFactor;
		m_player->setFlipX(false);
	} else if (collisions(m_rightArrow, &location)) {
		this->schedule(schedule_selector(JumpingGame::increaseSpeed), 0.25);


		m_playerVelocity.x += 150 * velocityFactor;

		m_player->setFlipX(true);
	}
}

void JumpingGame::increaseSpeed(float dt) {
	if (m_playerVelocity.x <= MAX_SPEED) {
		m_playerVelocity.x += SPEED_STEP;
	} else {
		this->unschedule(schedule_selector(JumpingGame::increaseSpeed));
	}
}

void JumpingGame::decreaseSpeed(float dt) {
	if (m_playerVelocity.x >= (MAX_SPEED * (-1.0f))) {
		m_playerVelocity.x -= SPEED_STEP;
	} else {
		this->unschedule(schedule_selector(JumpingGame::decreaseSpeed));
	}
}

bool JumpingGame::collisions(cocos2d::CCSprite* sprite,
		cocos2d::CCPoint* point) {
	CCPoint position = sprite->getPosition();
	CCSize size = sprite->getContentSize();
	CCRect spriteRect = CCRectMake(position.x, position.y, size.width,
			size.height);
	return spriteRect.containsPoint(*point);
}

bool JumpingGame::collisions(cocos2d::CCSprite* sprite1,
		cocos2d::CCSprite* sprite2) {
	CCPoint position1 = sprite1->getPosition();
	CCSize size1 = sprite1->getContentSize();
	CCRect spriteRect1 = CCRectMake(position1.x, position1.y, size1.width,
			size1.height);

	CCPoint position2 = sprite2->getPosition();
	CCSize size2 = sprite2->getContentSize();
	CCRect spriteRect2 = CCRectMake(position2.x, position2.y, size2.width,
			size2.height);
	return spriteRect1.intersectsRect(spriteRect2);
}

void JumpingGame::ccTouchesEnded(CCSet* touches, CCEvent* event) {
	this->unschedule(schedule_selector(JumpingGame::decreaseSpeed));
	this->unschedule(schedule_selector(JumpingGame::increaseSpeed));
	m_playerVelocity.x = 0.0f;
}

void JumpingGame::updateGame(float dt) {
	if (m_gameOver) {
		this->unschedule(schedule_selector(JumpingGame::updateGame));
		stopAllActions();
		SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
		SimpleAudioEngine::sharedEngine()->stopAllEffects();
		SimpleAudioEngine::sharedEngine()->playEffect("uh.wav", false);
		GameOverScene *pScene = GameOverScene::create();
		char scoreText[128];
		sprintf(scoreText, "%d", m_playerScore);
		pScene->getLayer()->getLabel()->setString(scoreText);
		CCDirector::sharedDirector()->replaceScene(
				CCTransitionFade::create(0.5f, pScene));
		//CCDirector::sharedDirector()->replaceScene(pScene);
		return;

	}
	updatePlayer();
	checkCollisions();
	scrollScene();
	updateBricks();
}
int JumpingGame::getRandomX(CCSprite* sprite) {
	return getRandom(0, m_winSize.width - sprite->getContentSize().width);
}

int JumpingGame::getRandom(int min, int max) {
	return (rand() % (max - min)) + min;
}

BrickSprite* JumpingGame::initBrick(const char * path) {
	CCTexture2D* blockTexture = CCTextureCache::sharedTextureCache()->addImage(
			path);
	BrickSprite* brick = BrickSprite::createWithTexture(blockTexture);
	brick->setAnchorPoint(ccp(0.0f, 0.0f));
	this->addChild(brick, 0);
	return brick;

}

void JumpingGame::initGreenBricks() {
	for (int i = 0; i < MAX_BRICKS; i++) {
		CCSprite* brick = initBrick("green_brick.png");
		brick->setTag(GREEN_BRICK);
		brick->setPosition(ccp(getRandomX(brick), (i + 1) * m_positionRatio));
		m_visibleBricks->addObject(brick);
	}
}

void JumpingGame::moveBrick(BrickSprite* sprite, int reverse) {
	CCFiniteTimeAction* actionMove = CCMoveTo::create(5.0f,
			ccp(
					reverse == BLUE_BRICK_REVERSE ?
							0 :
							m_winSize.width - sprite->getContentSize().width,
					sprite->getPositionY()));
	CCFiniteTimeAction* actionMoveDone = CCCallFuncN::create(this,
			callfuncN_selector(JumpingGame::blueBrickMoveFinished));
	sprite->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));
}

void JumpingGame::initBackground() {
	CCSprite* background = CCSprite::create("kk_bg.png");
	background->setAnchorPoint(ccp(0.0f, 0.0f));
	background->setPosition(ccp(0.0f, 0.0f));
	// Scale background to cover the whole window.
	/*CCRect bgRect = background->getTextureRect();
	 background->setScaleX(m_winSize.width / bgRect.size.width);
	 background->setScaleY(m_winSize.height / bgRect.size.height);*/

	// Add the background as a child to JumpingGame layer.
	this->addChild(background, 0);
}

void JumpingGame::initPlayer() {
	CCArray *playerAnimationFrames = new CCArray();
	playerAnimationFrames->addObject(
			CCSpriteFrame::create("dona_idle.png", CCRectMake(0, 0, 121, 154)));
	playerAnimationFrames->addObject(
			CCSpriteFrame::create("dona_jumping.png",
					CCRectMake(0, 0, 121, 154)));
	// Create player animation from the animation frames
	CCAnimation* playerAnimation = CCAnimation::createWithSpriteFrames(
			playerAnimationFrames);

	// Add player animation to animation cache
	CCAnimationCache::sharedAnimationCache()->addAnimation(playerAnimation,
			"PlayerAnimation");

	// Create player sprite from the first animation frame
	m_player =
			CCSprite::createWithSpriteFrame(
					dynamic_cast<CCSpriteFrame*>(playerAnimationFrames->objectAtIndex(
							0)));
	m_player->setAnchorPoint(ccp(0.0f, 0.0f));
	CCRect playerRect = m_player->getTextureRect();
	m_player->setPosition(
			ccp((m_winSize.width - playerRect.size.width) / 2.0f, 0.0f));
	this->addChild(m_player, 1);

	// Player animation frames are stored by the player animation
	CC_SAFE_RELEASE_NULL(playerAnimationFrames);

	m_playerVelocity = ccp(0.0f, 0.0f);
	m_playerScore = 0;
	m_playerJumping = false;
	m_gameOver = false;
}

void JumpingGame::updatePlayer() {
	float step = CCDirector::sharedDirector()->getAnimationInterval() * 2;
	CCPoint playerPosition = m_player->getPosition();

	playerPosition.x += m_playerVelocity.x * step;

	if (m_playerJumping) {
		// Apply gravity and update player position in Y-axis
		const float gravity = -300.0f;
		m_playerVelocity.y += gravity * step;
		playerPosition.y += m_playerVelocity.y * step;
	}

	// Player dropped outside from the screen?
	if (playerPosition.y < -100) {
		m_gameOver = true;
	}

	// Prevent the player from moving outside from the screen
	CCRect playerRect = m_player->getTextureRect();
	if (playerPosition.x < -m_player->getContentSize().width) {
		playerPosition.x = m_winSize.width + m_player->getContentSize().width;
	} else if (playerPosition.x > m_winSize.width + playerRect.size.width) {
		playerPosition.x = -playerRect.size.width;
	}

	// Set the new player position
	m_player->setPosition(playerPosition);

	float jumpingSpriteSpeed = m_playerSpringJumping ? 400.0f : 200.0f;

	// Update player animation
	if (m_playerVelocity.y >= jumpingSpriteSpeed) {
		m_player->setDisplayFrameWithAnimationName("PlayerAnimation", 1);
	} else {
		m_player->setDisplayFrameWithAnimationName("PlayerAnimation", 0);
	}

}

void JumpingGame::checkCollisions() {
	// Check player -> blocks collisions if player is moving down
	if (m_playerVelocity.y < 0.0f) {
		CCRect playerRect = m_player->getTextureRect();
		playerRect.origin.x = m_player->getPositionX() + 30;
		playerRect.origin.y = m_player->getPositionY();
		playerRect.size.width -= 60;
		playerRect.size.height = 5;

		CCObject* iterator = NULL;
		CCARRAY_FOREACH(m_springs, iterator)
		{
			CCSprite* spring = dynamic_cast<CCSprite*>(iterator);
			if (collisions(m_player, spring)) {
				spring->setDisplayFrameWithAnimationName("SpringAnimation", 1);
				spring->setTag(SPRING_PRESSED);
				springJump();
				return;
			}
		}
		CCARRAY_FOREACH(m_visibleBricks, iterator)
		{
			BrickSprite* brick = dynamic_cast<BrickSprite*>(iterator);
			CCRect blockRect = brick->getTextureRect();
			blockRect.origin.x = brick->getPositionX() + 20;
			blockRect.origin.y = brick->getPositionY() + 15;
			blockRect.size.width -= 40;
			blockRect.size.height = 20;
			if (playerRect.intersectsRect(blockRect)) {
				brickCollision(brick);
				break;
			}
		}
		if (m_floor != NULL && m_floor->getPositionY() >= 0) {
			CCRect floorRect = m_floor->getTextureRect();
			//floorRect.origin = ccp(0, m_floor->getPositionY());
			floorRect.origin = ccp(-m_player->getContentSize().width, 0);
			//floorRect.size.height *= 0.30;
			floorRect.size.width += (m_player->getContentSize().width * 2);

			if (playerRect.intersectsRect(floorRect)) {
				jump();
			}
		}
	}
}

void JumpingGame::brickCollision(BrickSprite* brick) {
	CCFiniteTimeAction* actionMove = NULL;
	CCFiniteTimeAction* actionMoveDone = NULL;
	switch (brick->getTag()) {
	case RED_BRICK_BROKEN:
	case WHITE_BRICK_HIDDEN:
		break;
	case RED_BRICK:
		brick->setDisplayFrameWithAnimationName("RedBrickAnimation", 1);
		actionMove = CCMoveTo::create(
				3.0f * (brick->getPositionY() / m_winSize.height),
				ccp(brick->getPositionX(), 0 - brick->getContentSize().height));
		actionMoveDone = CCCallFuncN::create(this,
				callfuncN_selector(JumpingGame::redBrickMoveFinished));
		brick->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));
		brick->setTag(RED_BRICK_BROKEN);
		break;
	case WHITE_BRICK:
		hideBrick(brick);
		jump();
		break;
	default:
		jump();
		break;
	}
}

void JumpingGame::scrollScene() {
	CCPoint playerPosition;
	playerPosition.x = m_player->getPositionX();
	playerPosition.y = m_player->getPositionY();

	float scrollBase = m_winSize.height * 0.30f;
	if (playerPosition.y > scrollBase) {
		updateScore();
		float scrollMove = scrollBase - playerPosition.y;
		// Move blocks down
		CCObject* iterator = NULL;
		CCARRAY_FOREACH(m_visibleBricks, iterator)
		{
			BrickSprite* brick = dynamic_cast<BrickSprite*>(iterator);
			CCPoint blockPosition = brick->getPosition();
			blockPosition.y += scrollMove;
			brick->setPosition(blockPosition);
			if (brick->getSpring() != NULL) {
				CCSprite* spring = brick->getSpring();
				spring->setPositionY(spring->getPositionY() + scrollMove);
			}
		}
		// Move player down
		playerPosition.y += scrollMove;
		m_player->setPosition(playerPosition);
		m_floor->setPositionY(m_floor->getPositionY() + scrollMove);
	}
}

BrickSprite* JumpingGame::getBrickOutsideScreen() {
	CCObject* iterator = NULL;
	bool stillSpringVisible = false;
	CCARRAY_FOREACH(m_visibleBricks, iterator)
	{
		stillSpringVisible = false;
		BrickSprite* brick = dynamic_cast<BrickSprite*>(iterator);
		CCPoint blockPosition = brick->getPosition();
		CCRect blockRect = brick->getTextureRect();

		if (blockPosition.y < -blockRect.size.height) {
			if (brick->getSpring() != NULL) {
				CCSprite* spring = brick->getSpring();
				if (spring->getPositionY() < -spring->getContentSize().height) {
					return brick;
				} else {
					stillSpringVisible = true;
				}
			}
			if (!stillSpringVisible) {
				return brick;
			}
		}
	}
	return NULL;
}

float JumpingGame::getHigherYPosition() {
	float position = 0.0f;
	CCObject* iterator = NULL;
	CCARRAY_FOREACH(m_visibleBricks, iterator)
	{
		CCSprite* brick = dynamic_cast<CCSprite*>(iterator);
		if (brick->getPositionY() > position) {
			position = brick->getPositionY();
		}
	}

	return position;

}

BrickSprite* JumpingGame::repositionBrick(BrickSprite* sprite) {

	CCPoint blockPosition = sprite->getPosition();
	blockPosition.x =
			sprite->getTag() == BLUE_BRICK
					|| sprite->getTag() == BLUE_BRICK_REVERSE ?
					0.0f : getRandomX(sprite);
	blockPosition.y = getHigherYPosition();
	blockPosition.y += m_positionRatio;
	sprite->setPosition(blockPosition);
	setSpring(sprite);
	return sprite;
}

void JumpingGame::updateBricks() {
	BrickSprite* outsideBrick = getBrickOutsideScreen();
	if (outsideBrick != NULL) {
		initBrickSpecs(repositionBrick(getNewBrick(outsideBrick)));
	}
}

void JumpingGame::initBrickSpecs(BrickSprite* brick) {
	switch (brick->getTag()) {
	case BLUE_BRICK_REVERSE:
	case BLUE_BRICK:
		brick->stopAllActions();
		moveBrick(brick, BLUE_BRICK);
		break;
	case WHITE_BRICK_HIDDEN:
		brick->setVisible(true);
		brick->setTag(WHITE_BRICK);
		break;
	}
}

bool JumpingGame::removeSpring(BrickSprite* brick) {
	if (brick->getSpring() != NULL) {
		CCSprite* spring = brick->getSpring();
		m_springs->removeObject(spring, false);
		this->removeChild(spring, true);
		CC_SAFE_RELEASE_NULL(spring);
		brick->setSpring(NULL);
		return true;
	}
	return false;
}

BrickSprite* JumpingGame::getNewBrick(BrickSprite* oldBrick) {
	removeSpring(oldBrick);
	if (m_playerScore < 500) {
		m_lastGeneratedBrick = oldBrick;
		return oldBrick;
	}
	int random = getRandom(0, m_playerScore);
	BrickSprite* newBrick = NULL;

	if (random >= 0 && random < 500) {
		newBrick = handleBrick(oldBrick, "green_brick.png", GREEN_BRICK, -1,
				GREEN_BRICK);
	} else if (random >= 500 && random < 750) {
		if (m_lastGeneratedBrick != NULL
				&& m_lastGeneratedBrick->getTag() == RED_BRICK) {
			newBrick = handleBrick(oldBrick, "green_brick.png", GREEN_BRICK, -1,
					GREEN_BRICK);
		} else {
			newBrick = handleBrick(oldBrick, "red_brick.png", RED_BRICK,
					RED_BRICK_BROKEN, RED_BRICK);
		}

	} else if (random >= 750 && random < 1250) {
		newBrick = handleBrick(oldBrick, "blue_brick.png", BLUE_BRICK,
				BLUE_BRICK_REVERSE, BLUE_BRICK);
	} else if (random >= 1250) {
		newBrick = handleBrick(oldBrick, "white_brick.png", WHITE_BRICK,
				WHITE_BRICK_HIDDEN, WHITE_BRICK);
	}
	return newBrick;
}

void JumpingGame::setSpring(BrickSprite* brick) {
	if (m_playerScore
			< 30|| brick->getTag() == RED_BRICK || brick->getTag() == RED_BRICK_BROKEN || brick->getTag() == BLUE_BRICK || brick->getTag() == BLUE_BRICK_REVERSE) {
		return;
	}
	int random = getRandom(1, 10);
//20% chances of putting a spring on the brick
	if (random <= 2) {
		CCSprite* spring = createSpring();
		spring->setPositionX(
				brick->getPositionX() + (brick->getContentSize().width * 0.45));
		spring->setPositionY(
				brick->getPositionY()
						+ (brick->getContentSize().height * 0.75f));
		this->addChild(spring, 0);
		brick->setSpring(spring);

	}
}

CCSprite* JumpingGame::createSpring() {
	CCSprite* spring = CCSprite::create("coffee.png");
	CCPoint anchor = spring->getAnchorPoint();
	spring->setAnchorPoint(ccp(anchor.x, 0.0f));
	spring->setTag(SPRING);
	m_springs->addObject(spring);
	return spring;

}

bool JumpingGame::removeBrick(BrickSprite* brick) {
	if (brick != NULL) {
		removeSpring(brick);
		m_visibleBricks->removeObject(brick, false);
		this->removeChild(brick, true);
		CC_SAFE_RELEASE_NULL(brick);
		return true;
	}
	return false;
}

bool JumpingGame::hideBrick(BrickSprite* brick) {
	if (brick != NULL && brick->getTag() == WHITE_BRICK) {
		removeSpring(brick);
		brick->setVisible(false);
		brick->setTag(WHITE_BRICK_HIDDEN);
		return true;
	}
	return false;
}

BrickSprite* JumpingGame::handleBrick(BrickSprite* oldBrick, const char * path,
		int tag1, int tag2, int newTag) {
	if (oldBrick->getTag() == tag1 || oldBrick->getTag() == tag2) {
		m_lastGeneratedBrick = oldBrick;
		return oldBrick;
	}

	removeBrick(oldBrick);
	BrickSprite* brick = initBrick(path);
	brick->setTag(newTag);
	m_visibleBricks->addObject(brick);
	m_lastGeneratedBrick = brick;
	return brick;
}

void JumpingGame::updateScore() {
	if (m_playerVelocity.y > 0.0f) {
		m_playerScore++;
		char scoreText[32];
		//CCSize screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();
		sprintf(scoreText, "%d", m_playerScore);
		m_scoreLabel->setString(scoreText);

	}
}

void JumpingGame::jump() {
	if (m_playerJumping) {
		// Play jump audio effect
		SimpleAudioEngine::sharedEngine()->playEffect("jump.wav", false);

		m_playerVelocity.y = m_winSize.height * 0.3;
		m_playerSpringJumping = false;
	}
}

void JumpingGame::springJump() {
	if (m_playerJumping) {
		SimpleAudioEngine::sharedEngine()->playEffect("jump.wav", false);
		m_playerVelocity.y = m_winSize.height * 0.6;
		m_playerSpringJumping = true;
	}
}

void JumpingGame::keyBackClicked(void) {
	CCLog("\nKeyBack pressed\n");
	CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

}

void JumpingGame::blueBrickMoveFinished(cocos2d::CCNode* sender) {
	BrickSprite* brick = dynamic_cast<BrickSprite*>(sender);
	if (brick) {
		brick->setTag(
				brick->getTag() == BLUE_BRICK ?
						BLUE_BRICK_REVERSE : BLUE_BRICK);
		moveBrick(brick, brick->getTag());
	}
}

void JumpingGame::redBrickMoveFinished(cocos2d::CCNode* sender) {
	CCSprite* sprite = dynamic_cast<CCSprite*>(sender);
	if (sprite) {
		sprite->setDisplayFrameWithAnimationName("RedBrickAnimation", 0);
		sprite->setTag(RED_BRICK);
	}
}

