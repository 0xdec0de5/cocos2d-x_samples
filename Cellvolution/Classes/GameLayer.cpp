#include "GameLayer.h"
#include "GameMenu.h"
#include <cmath>

using namespace cocos2d;

GameLayer::GameLayer()
{
}

bool GameLayer::init()
{
	//Get windows size
	auto winSize = Director::getInstance()->getWinSize();

	//set poistion to middle of screen
	Vec2 pos;
	pos.x = winSize.width / 2;
	pos.y = winSize.height / 2;

	_player = new Player();
	_player->setPosition(pos);
	_player->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->addChild(_player, 400);

	// Add game background
	auto background = Sprite::create("image/game_background.png");
	background->setAnchorPoint(Vec2(0.5f, 0.5f));
    background->setPosition(pos);
	this->addChild(background, -1000);

	// Add blood overlay
	auto overlay = Sprite::create("image/overlay.png");
	overlay->setOpacity(0);
	overlay->setAnchorPoint(Vec2(0.5f, 0.5f));
    overlay->setPosition(pos);
	this->addChild(overlay, 1000, "OVERLAY");

	//Handle Touch Events
	auto listener = EventListenerMouse::create();

	listener->onMouseDown = CC_CALLBACK_1(GameLayer::onMouseDown, this);
	listener->onMouseUp = CC_CALLBACK_1(GameLayer::onMouseUp, this);
	listener->onMouseMove = CC_CALLBACK_1(GameLayer::onMouseMove, this);
	
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(
		listener, this);

	//Sink the update on frame function
	scheduleUpdate();

	// stop music
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();

	// Re-initialize Core
	auto core = Core::sharedCore();
    
    //Add labels
    Size windowSize = Director::getInstance()->getWinSize();
    
    std::string health = "Health: " + std::to_string(core->getHitpoints());
    
    _lblHP = Label::createWithTTF(health, "fonts/chemrea.ttf", 16);
    _lblHP->setColor(Color3B::RED);
    _lblHP->setPosition(Vec2(windowSize.width / 2 - 50, windowSize.height - 17));
    this->addChild(_lblHP, 10000);
    
    std::string score = "Score: " + std::to_string(core->getScore());
    _lblScore = Label::createWithTTF(score, "fonts/chemrea.ttf", 16);
    _lblScore->setColor(Color3B::YELLOW);
    _lblScore->setPosition(Vec2(windowSize.width / 2 + 50, windowSize.height - 17));
    this->addChild(_lblScore, 10000);
    
	core->setPlayerMoving(false);

	return true;
}

void GameLayer::update(float dt)
{
	this->playerMove(dt);
	this->updateBaddies(dt);
	this->handleCollision(dt);
    this->soundCheck(dt);
    this->updateUi(dt);

}

void GameLayer::updateUi(float dt)
{
    std::string score = "Score: " + std::to_string(Core::sharedCore()->getScore());
    std::string health = "Health: " + std::to_string(Core::sharedCore()->getHitpoints());
    
    _lblHP->setString(health);
    _lblScore->setString(score);
}

void GameLayer::soundCheck(float dt)
{
        if(SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
        {
            return;
        }
    
    std::string tune = "music/track" + std::to_string(randi(1, 14)) + ".mp3";
    Core::sharedCore()->setBackgroundMusic(tune, false);
    
}

void GameLayer::handleCollision(float dt)
{
	if (_pool.empty())
	{
		return;
	}

	auto core = Core::sharedCore();

	for (auto it = _pool.begin(); it != _pool.end(); )
	{
		Baddie * baddie = (Baddie*)*it;

		if (isCollide(baddie->getPosition(), baddie->getRadius(), _player->getPosition(), _player->getRadius())) 
		{
            Sound sound = Sound::None;
            
            if(baddie->getColor() == _player->getColor())
            {
                sound = Sound::Explosion_Success;
                core->playerScored();
            }
            else
            {
                //Deduct one hitpoint from player
                sound = Sound::Explosion_Fail;
                core->playerHit();
            }
            
			//Destroy the baddie
			if (_pool.contains(baddie)) {

				baddie->removeBaddie(sound);

				//update iterator
				it = _pool.erase(it);

			}

		}

		if (it != _pool.end())
		{
			it++;
		}
	}

	//Test if game over condtion
	if (core->getHitpoints() <= 0)
	{
		//Game Over!
		Director::getInstance()->replaceScene(GameMenu::scene());
	} 
	else if (core->getHitpoints() < 10)
	{
		auto hp = core->getHitpoints();

		float damage = (1.0f - ((float)hp / 10.0f)) * 255.0f;

		auto overlay = this->getChildByName("OVERLAY");
		overlay->setOpacity(damage);

	}
    
    //Test win condition
    if(core->getScore() >= 25)
    {
        //Win!
        Director::getInstance()->replaceScene(GameMenu::scene());
    }
}

void GameLayer::updateBaddies(float dt)
{
	_gameTime += dt;

	if (_gameTime > _baddieCount * 5)
	{
		_baddieCount++;
		this->addBaddie();

	}
}

void GameLayer::playerMove(float dt)
{
	auto core = Core::sharedCore();

	if (!core->getPlayerMoving())
	{
		return;
	}

	/*if (core->getTargetPostion().equals(Vec2::ZERO))
	{
		return;
	}*/

	auto playerPrevPosition = core->getPreviousPosition();
	auto playerPosition = _player->getPosition();
	auto targetPosition = core->getTargetPostion();

	float distance = playerPrevPosition.getDistance(playerPosition);

	if (distance > 10)
	{
		CCLOG("CRAZY MOVE HAPPENED");
	}

	float previousDistance = playerPrevPosition.getDistance(targetPosition);
	float currentDistance = playerPosition.getDistance(targetPosition);

	if (currentDistance < 1 || previousDistance < 0)
	{
		core->setPlayerMoving(false);
		return;
	}

	Vec2 newPosition = Vec2(playerPosition);

	// Set new position based on the elapsed time (dt) for this frame
	// As well we must take into account the angle at which the player
	// needs to move
	newPosition.x = newPosition.x +
		(dt * core->getPlayerSpeed() * cosf(core->getTargetAngle()));
	newPosition.y = newPosition.y +
		(dt * core->getPlayerSpeed() * sinf(core->getTargetAngle()));
		 
	_player->setPosition(newPosition);

	core->setPreviousPosition(newPosition);

}

void GameLayer::addBaddie()
{
	//if (_pool.empty())
	//{
		_pool.pushBack(new Baddie());
	//}

	Baddie* baddie = (Baddie*)_pool.back();
	//_pool.popBack();

	baddie->prepare();

	Vec2 pos;

	Size window = Director::getInstance()->getWinSize();

	do
	{
		float x = randi(0, window.width);
		float y = randi(0, window.height);
		pos = Vec2(x, y);

		if ( !isCollide(pos, baddie->getRadius(), _player->getPosition(), _player->getRadius() * 3.0f) )
		{
			break;
		}

	} while (true);

	baddie->setPosition(pos);

	if (!baddie->getParent())
	{
		this->addChild(baddie, 900, "BADDIE");
	}

	if (baddie->getColor() != _player->getColor())
	{
		FiniteTimeAction * move = baddie->getMoveAction();

		if (move)
		{
			baddie->runAction(move);
		}
	}

	ActionInterval * action = baddie->getRepeatAction();
	if (action)
	{
		baddie->runAction(action);
	}
}

cocos2d::Scene * GameLayer::scene()
{
	auto scene = Scene::create();
	scene->addChild(GameLayer::create());
	return scene;
}

void GameLayer::onMouseDown(Event * e)
{
	processEvent(e);
}

void GameLayer::onMouseUp(Event * e)
{
}

void GameLayer::onMouseMove(Event * e)
{
}

bool GameLayer::onTouchesBegin(Touch * t, Event * e)
{
	return false;
}

void GameLayer::onTouchesMoved(Touch * t, Event * e)
{
}

void GameLayer::onTouchesEnded(Touch * t, Event * e)
{
}

void GameLayer::processEvent(Event * e)
{
	if (!e) return;

	Vec2 locationInView = Vec2::ZERO;

	switch (e->getType())
	{
		case Event::Type::MOUSE:
		{
			auto mouseEvent = (EventMouse*)e;
			locationInView = mouseEvent->getLocationInView();
		}
		break;

		case Event::Type::GAME_CONTROLLER:
		case Event::Type::TOUCH:
		case Event::Type::KEYBOARD:
		{
			CCLOG("WE DONT HANDLE YET");
			return;
		}
        default:
            CCLOG("WE WONT HANDLE");
            return;
            
	}

	Core * core = Core::sharedCore();

	// Get the angle between p1 & click location
	Vec2 p1 = _player->getPosition();
	float dY = locationInView.y - p1.y;
	float dX = locationInView.x - p1.x;
	float angle = atan2f(dY, dX);
	core->setTargetAngle(angle);

	Size size = Director::getInstance()->getWinSize();
	auto cp = locationInView.getClampPoint(Vec2::ZERO, Vec2(size.width, size.height));
	core->setTargetPosition(cp);

	core->setPlayerMoving(true);

}
