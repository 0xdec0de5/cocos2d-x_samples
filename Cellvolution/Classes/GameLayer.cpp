#include "GameLayer.h"
#include <cmath>

using namespace cocos2d;

GameLayer::GameLayer()
{
}

bool GameLayer::init()
{

	//Get windows size
	auto winSize = Director::getInstance()->getWinSize();

	//set poistion of player to middle of screen
	Vec2 pos;
	pos.x = winSize.width / 2;
	pos.y = winSize.height / 2;

	_player = new Player();
	_player->setPosition(pos);
	this->addChild(_player, 400);

	// Add game background
	auto background = Sprite::create("image\\game_background.png");
	this->addChild(background, -1000);

	// Add blood overlay
	auto overlay = Sprite::create("image\\overlay.png");
	overlay->setOpacity(0);
	this->addChild(overlay, 1000);

	//Handle Touch Events
	auto listener = EventListenerMouse::create();

	listener->onMouseDown = CC_CALLBACK_1(GameLayer::onMouseDown, this);
	listener->onMouseUp = CC_CALLBACK_1(GameLayer::onMouseUp, this);
	listener->onMouseMove = CC_CALLBACK_1(GameLayer::onMouseMove, this);
	
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(
		listener, this);

	//Sink the update on frame function
	scheduleUpdate();

	// TODO start music


	// Set GameState to playing


	return true;
}

void GameLayer::update(float dt)
{
	this->PlayerMove(dt);
}

void GameLayer::PlayerMove(float dt)
{
	auto core = Core::sharedCore();

	if (core->getTargetPostion().equals(Vec2::ZERO))
	{
		return;
	}

	auto playerPrevPosition = core->getPreviousPosition();
	auto playerPosition = _player->getPosition();
	auto targetPosition = core->getTargetPostion();

	//Calculate the angle for the player to move
	float dY = targetPosition.y - playerPosition.y;
	float dX = targetPosition.x - playerPosition.x;

	core->setTargetAngle(atan2f(dY, dX));

	//float d = cocos2d::ccpDistance(playerPrev)





}

cocos2d::Scene * GameLayer::scene()
{
	auto scene = Scene::create();
	scene->addChild(GameLayer::create());
	return scene;
}

void GameLayer::onMouseDown(Event * e)
{
	auto mouseEvent = (EventMouse*)e;
	Vec2 p = mouseEvent->getLocation();
	Core::sharedCore()->setTargetPosition(p);
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
