#include "Baddie.h"
#include <string>

void Baddie::destroyMe()
{
	Director::getInstance()->getActionManager()->removeAllActionsFromTarget(this);

}

bool Baddie::init()
{
	this->initWithSpriteFrameName("cell_blue_1.png");
	this->setVisible(false);

	return true;
}

void Baddie::update(float)
{
}

void Baddie::move(float)
{
}

void Baddie::prepare()
{
	std::string image{};
	SpriteFrame* frame;

	int rnd = randi(1, 3);

	if (rnd == 1)
	{
		image = "cell_red_1.png";
		_color = Color::Red;
	}
	else if (rnd == 2)
	{
		image = "cell_green_1.png";
		_color = Color::Green;
	}
	else 
	{
		image = "cell_blue_1.png";
		_color = Color::Blue;
	}

	frame = SpriteFrameCache::getInstance()->spriteFrameByName(image);
	this->setDisplayFrame(frame);
	this->_radius = calcRadius(this);
	this->setVisible(true);

}

Baddie::Baddie()
{
	init();
}

Baddie::~Baddie()
{
}

void Baddie::removeBaddie(Node * gameLayer)
{
	Animation* explosion = AnimationCache::getInstance()->getAnimation("Explosion");
	Animate* animate = Animate::create(explosion);

	auto sequence = Sequence::create(animate,
		CallFunc::create(this, CC_CALLFUNC_SELECTOR(Baddie::destroyMe)), nullptr);

	this->stopAllActions();

	this->runAction(sequence/*Repeat::create(animate, 1)*/);

	//gameLayer->removeChild(this);
}

float Baddie::getRadius()
{
	return _radius;
}

Color Baddie::getColor()
{
	return _color;
}

void Baddie::setColor(Color color)
{
	_color = color;
}

bool Baddie::getMoving()
{
	return _isMoving;
}

void Baddie::triggerIsMoving()
{
	_isMoving = false;

	const auto baddies = _core->getBaddies();

	for (auto it = baddies.begin(); it != baddies.end(); it++)
	{
		Sprite * baddie = *it;

		if (isCollide(this->getPosition(), 3, baddie->getPosition(), 3))
		{
			auto angle = randi(0, 360);
			baddie->runAction(MoveTo::create(0.5f, baddie->getPosition() + Vec2(sin(angle) * 10, cos(angle) * 10)));
			angle = (angle + 180) % 360;
			this->runAction(MoveTo::create(0.5f, ccpAdd(this->getPosition(), Vec2(sin(angle) * 10, cos(angle) * 10))));
		}
	}
}

ActionInterval * Baddie::getRepeatAction()
{
	ActionInterval * action = nullptr;

	ScaleBy * scale = ScaleBy::create(2.5f, 1.3f);
	ActionInterval * reverse = scale->reverse();

	action = RepeatForever::create(Sequence::create(scale, reverse, NULL));
	return action;
}

FiniteTimeAction * Baddie::getMoveAction()
{
	this->_isMoving = true;

	// This is the bad guy's speed
	float modifiedBaddieSpeed = 4.0f;

	FiniteTimeAction * move = MoveTo::create(modifiedBaddieSpeed, _core->getPreviousPosition());

	return Sequence::create(move, NULL);
}
