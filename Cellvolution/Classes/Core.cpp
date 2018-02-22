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

unsigned short Core::getScore()
{
	return this->_playerScore;
}

void Core::playerScored()
{
	this->_playerScore++;
}

unsigned short Core::getHitpoints()
{
    return _playerHitpoints;
}

void Core::playerHit()
{
	_playerHitpoints = _playerHitpoints - 1;
}

const std::vector<Sprite*> Core::getBaddies()
{
	return _baddies;
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

void Core::setPlayerColor(Color color)
{
	this->_playerColor = color;
}

Color Core::getPlayerColor()
{
	return this->_playerColor;
}

void Core::setPlayerSpeed(unsigned int speed)
{
	this->_playerSpeed = speed;
}

unsigned int Core::getPlayerSpeed()
{
	return this->_playerSpeed;
}

void Core::setPlayerMoving(bool isMoving)
{
	this->_playerMoving = isMoving;
}

bool Core::getPlayerMoving()
{
	return this->_playerMoving;
}

bool Core::init()
{
	this->setPlayerSpeed(kPlayerSpeed);

	auto spritecache = SpriteFrameCache::getInstance();

	// the .plist file can be generated with any of the tools mentioned below
	spritecache->addSpriteFramesWithFile(
		"image/game_sprites.plist",
		"image/game_sprites.png"
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
		explosionFrame, 0.05f);

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

    //Preload all sounds
    preloadEffects();
    
    SimpleAudioEngine::getInstance()->setEffectsVolume(1.0f);
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1.0f);
    
	return true;
}

void Core::preloadEffects()
{
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic(music_theme.c_str());
    
    for(auto i = 1u; i <= 14; i++)
    {
        std::string music = "music/track" + std::to_string(i) + ".mp3";
        SimpleAudioEngine::getInstance()->preloadBackgroundMusic(music.c_str());
    }
    
    SimpleAudioEngine::getInstance()->preloadEffect(sound_arrow_shot.c_str());
    SimpleAudioEngine::getInstance()->preloadEffect(sound_damage.c_str());
    SimpleAudioEngine::getInstance()->preloadEffect(sound_explosion_bad.c_str());
    SimpleAudioEngine::getInstance()->preloadEffect(sound_explosion_exploded.c_str());
    SimpleAudioEngine::getInstance()->preloadEffect(sound_explosion_good.c_str());
    SimpleAudioEngine::getInstance()->preloadEffect(sound_explosion_grenade.c_str());
    SimpleAudioEngine::getInstance()->preloadEffect(sound_explosion_evolved.c_str());
    SimpleAudioEngine::getInstance()->preloadEffect(sound_health.c_str());
    SimpleAudioEngine::getInstance()->preloadEffect(sound_pacman.c_str());
    SimpleAudioEngine::getInstance()->preloadEffect(sound_speed_finished.c_str());
    SimpleAudioEngine::getInstance()->preloadEffect(sound_pain.c_str());
    SimpleAudioEngine::getInstance()->preloadEffect(sound_pain_immune.c_str());
    SimpleAudioEngine::getInstance()->preloadEffect(sound_score.c_str());
    SimpleAudioEngine::getInstance()->preloadEffect(sound_speed.c_str());
    SimpleAudioEngine::getInstance()->preloadEffect(sound_tick.c_str());
    SimpleAudioEngine::getInstance()->preloadEffect(sound_slomo_expired.c_str());
    SimpleAudioEngine::getInstance()->preloadEffect(sound_slomo_reload.c_str());
    SimpleAudioEngine::getInstance()->preloadEffect(sound_slomo_begin.c_str());
    SimpleAudioEngine::getInstance()->preloadEffect(sound_rogue_tick.c_str());
    SimpleAudioEngine::getInstance()->preloadEffect(sound_explosion_mutant.c_str());
}

void Core::stopEffect(unsigned int effectId)
{
    SimpleAudioEngine::getInstance()->stopEffect(effectId);
}

unsigned int Core::playEffect(Sound sound)
{
    switch(sound)
    {
        case Sound::Explosion_Good:
            return SimpleAudioEngine::getInstance()->playEffect(sound_explosion_good.c_str());
        case Sound::Explosion_Bad:
            return SimpleAudioEngine::getInstance()->playEffect(sound_explosion_bad.c_str());
        case Sound::None:
        default:
            return 0;
    }
}

void Core::setBackgroundMusic(std::string music, bool loop = false)
{
    SimpleAudioEngine::getInstance()->playBackgroundMusic(music.c_str(), loop);
}
