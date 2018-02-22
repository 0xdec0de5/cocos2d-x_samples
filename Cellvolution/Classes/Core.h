#pragma once

#include "cocos2d.h"
#include "audio/include/SimpleAudioEngine.h"
#include "Resources.h"
#include <time.h>
#include <assert.h>
#include <vector>
#include <string>

using namespace CocosDenshion;
using namespace cocos2d;

class Core
{
private:

	unsigned int _playerSpeed = kPlayerSpeed;
	bool _playerMoving = false;
	unsigned short _playerHitpoints = 10u;
	unsigned short _playerScore = 0u;

    bool init();
    void preloadEffects();
    
	Vec2 _targetPos = Vec2(0.0f, 0.0f);
	Vec2 _previousPos = Vec2(0.0f, 0.0f);
	float _targetAngle = 0.0f;
	Color _playerColor = Color::None;

	std::vector<Sprite*> _baddies{};

public:
    
	// Constants
	unsigned int kPlayerSpeed = 140u;

	void stopEffect(unsigned int);
	unsigned int playEffect(Sound);
	void setBackgroundMusic(std::string, bool);

	static Core * sharedCore(void);
    
    unsigned short getScore();
    void playerScored();
    
	unsigned short getHitpoints();
	void playerHit();

	const std::vector<Sprite*> getBaddies();

	void setTargetPosition(Vec2);
	Vec2 getTargetPostion();

	void setPreviousPosition(Vec2);
	Vec2 getPreviousPosition();

	void setTargetAngle(float);
	float getTargetAngle();

	void setPlayerColor(Color);
	Color getPlayerColor();

	void setPlayerSpeed(unsigned int);
	unsigned int getPlayerSpeed();

	void setPlayerMoving(bool);
	bool getPlayerMoving();

};

inline float randf(int min, int max)
{
    assert(max >= min);
	return min + (rand() % (max - min + 1));
}

inline int randi(int min, int max)
{
	return randf(min, max);
}
