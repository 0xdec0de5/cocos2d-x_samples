#include "Player.h"

#include <random>

Color Player::getRandomColor(Color c)
{
	float rnd = randf(0, 1);

	if (c == Color::None)
	{
		if (rnd < 0.333)
		{
			return Color::Red;
		}
		else if (rnd > 0.665)
		{
			return Color::Blue;
		}
		else
		{
			return Color::Green;
		}
	}
	else
	{
		if (c == Color::Red)
		{
			return rnd < 0.5 ? Color::Green : Color::Blue;
		}

		if (c == Color::Green)
		{
			return rnd < 0.5 ? Color::Red : Color::Blue;
		}
		if (c == Color::Blue)
		{
			return rnd < 0.5 ? Color::Green : Color::Red;
		}
	}
}

void Player::changeColor()
{
	Color color = getRandomColor(_core->getPlayerColor());
	_core->setPlayerColor(color);

	if (this->getNumberOfRunningActions() > 0)
	{
		this->stopAllActions();
	}

	this->runAction(_mainSequence);

	if (color == Color::Red)
	{
		this->runAction(_redAnimation);
	}

	if (color == Color::Green)
	{
		this->runAction(_greenAnimation);
	}

	if (color == Color::Blue)
	{
		this->runAction(_blueAnimation);
	}

}

bool Player::init()
{
	_core = Core::sharedCore();

	auto redAnimate = Animate::create(
		AnimationCache::sharedAnimationCache()->getAnimation("RED"));
	auto greenAnimate = Animate::create(
		AnimationCache::sharedAnimationCache()->getAnimation("GREEN"));
	auto blueAnimate = Animate::create(
		AnimationCache::sharedAnimationCache()->getAnimation("BLUE"));

	_redAnimation = RepeatForever::create(redAnimate);
	_greenAnimation = RepeatForever::create(greenAnimate);
	_blueAnimation = RepeatForever::create(blueAnimate);

	_redAnimation->retain();
	_greenAnimation->retain();
	_blueAnimation->retain();

	_mainSequence = Sequence::create(DelayTime::create(12.0f), Blink::create(1.0f, 15),
		CallFunc::create(this, CC_CALLFUNC_SELECTOR(Player::changeColor)), nullptr);
	_mainSequence->setTag(1000);

	changeColor();


	return true;
}

float Player::getRadius()
{
	return kPlayerRadius;
}

Color Player::getColor()
{
	return _core->getPlayerColor();
}

Player::Player()
{
	init();
}

Player::~Player()
{
}
