
#include "Core.h"
#include <string>

static bool s_bFirstRun = true;
static Core s_sharedCore;

Core * Core::sharedCore(void)
{
	if (s_bFirstRun)
	{
		s_sharedCore.init();
		s_bFirstRun = false;
	}
	return &s_sharedCore;
}

void Core::setPreviousPosition(Vec2 position)
{
	this->_previousPos = position;
}

Vec2 Core::getPreviousPosition()
{
	return this->_previousPos;
}

void Core::setTargetPosition(Vec2 position)
{
	this->_targetPos = position;
}

Vec2 Core::getTargetPostion()
{
	return this->_targetPos;
}

void Core::setTargetAngle(float angle)
{
	this->_targetAngle = angle;
}

float Core::getTargetAngle()
{
	return this->_targetAngle;
}

bool Core::init()
{

	auto spritecache = SpriteFrameCache::getInstance();

	// the .plist file can be generated with any of the tools mentioned below
	spritecache->addSpriteFramesWithFile(
		"image\\game_sprites.plist",
		"image\\game_sprites.png"
	);

	// Get the explosion sprites
	Vector<SpriteFrame*> explosionFrame;
	explosionFrame.reserve(12);

	for (auto i = 1u; i < 13; i++)
	{
		std::string name = "explosion_";

		if (i < 10)
		{
			name = name + "0" + std::to_string(i);
		}
		else
		{
			name = name + std::to_string(i);
		}

		name += ".png";

		/*
		char s[100] = {0};
		sprintf(s, "explosion_%02d.png", i);
		*/

		explosionFrame.pushBack(spritecache->getSpriteFrameByName(name));
	}

	Animation * explosionAnimation = Animation::createWithSpriteFrames(
		explosionFrame, 0.05);

	AnimationCache::getInstance()->addAnimation(explosionAnimation,
		"Explosion");


	// Get the  player sprites
	Vector<SpriteFrame*> redFrame;
	redFrame.reserve(8);
	Vector<SpriteFrame*> blueFrame;
	blueFrame.reserve(8);
	Vector<SpriteFrame*> greenFrame;
	greenFrame.reserve(8);

	for (auto i = 1u; i < 9; i++)
	{
		std::string name = "_" + std::to_string(i)+ ".png";

		redFrame.pushBack(spritecache->getSpriteFrameByName("player_red" + name));
		blueFrame.pushBack(spritecache->getSpriteFrameByName("player_blue" + name));
		greenFrame.pushBack(spritecache->getSpriteFrameByName("player_green" + name));
	}

	Animation * redAnimation = Animation::createWithSpriteFrames(
		redFrame, 0.2);
	Animation * blueAnimation = Animation::createWithSpriteFrames(
		blueFrame, 0.2);
	Animation * greenAnimation = Animation::createWithSpriteFrames(
		greenFrame, 0.2);

	AnimationCache::getInstance()->addAnimation(redAnimation,
		"RED");
	AnimationCache::getInstance()->addAnimation(blueAnimation,
		"BLUE");
	AnimationCache::getInstance()->addAnimation(greenAnimation,
		"GREEN");


	// Get the rogue sprites
	Vector<SpriteFrame*> rogueFrame;
	rogueFrame.reserve(14);

	for (auto i = 1u; i < 15; i++)
	{
		std::string name = "rogue_";

		if (i < 10)
		{
			name = name + "0" + std::to_string(i);
		}
		else
		{
			name = name + std::to_string(i);
		}

		name += ".png";

		rogueFrame.pushBack(spritecache->getSpriteFrameByName(name));
	}

	Animation * rogueAnimation = Animation::createWithSpriteFrames(
		rogueFrame, 0.2);

	AnimationCache::getInstance()->addAnimation(rogueAnimation,
		"ROGUE");

	return true;
}