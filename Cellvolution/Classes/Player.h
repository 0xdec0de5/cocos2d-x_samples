#pragma once

#include "cocos2d.h"
#include "Core.h"
#include "Resources.h"

using namespace cocos2d;

class Player : public Sprite
{
private:

	// Instances
	Core * _core;

	// Actions
	Action * _redAnimation;
	Action * _greenAnimation;
	Action * _blueAnimation;

	Sequence * _mainSequence;

	Color getRandomColor(Color);
	void changeColor();


public:

	virtual bool init();

	Color getColor();

	Player();
	~Player();

	CREATE_FUNC(Player)

};