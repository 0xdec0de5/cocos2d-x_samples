#pragma once

#include "cocos2d.h"
#include "Resources.h"
#include <assert.h>
#include <vector>

using namespace cocos2d;

class Core
{
private:

	unsigned int _playerSpeed = kPlayerSpeed;
	bool _playerMoving = false;
	unsigned short _playerHitpoints = 10u;

	bool init();
	Vec2 _targetPos = Vec2(0.0f, 0.0f);
	Vec2 _previousPos = Vec2(0.0f, 0.0f);
	float _targetAngle = 0.0f;
	Color _playerColor = Color::None;

	std::vector<Sprite*> _baddies{};

public:
	// Constants
	unsigned int kPlayerSpeed = 140u;

	static Core * sharedCore(void);

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