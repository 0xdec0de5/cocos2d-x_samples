#pragma once

#include "cocos2d.h"
#include "Resources.h"
#include <assert.h>

using namespace cocos2d;

class Core
{
private:
	bool init();
	Vec2 _targetPos = Vec2(0.0f, 0.0f);
	Vec2 _previousPos = Vec2(0.0f, 0.0f);
	float _targetAngle = 0.0f;

public:
	static Core * sharedCore(void);

	void setTargetPosition(Vec2);
	Vec2 getTargetPostion();

	void setPreviousPosition(Vec2);
	Vec2 getPreviousPosition();

	void setTargetAngle(float);
	float getTargetAngle();

	Color PlayerColor;
};

inline float randf(int min, int max)
{
	assert(max >= min);
	return min + (rand() % (max - min + 1));
}