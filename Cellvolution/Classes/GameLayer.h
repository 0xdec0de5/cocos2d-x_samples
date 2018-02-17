#pragma once

#include "cocos2d.h"
#include "Player.h"


class GameLayer : public cocos2d::Layer
{
private:
	Player * _player = nullptr;

public:
	GameLayer();

	virtual bool init();
	virtual void update(float);
	//virtual void draw();

	void PlayerMove(float);

	static cocos2d::Scene* scene();

	CREATE_FUNC(GameLayer)

	void onMouseDown(Event *);
	void onMouseUp(Event *);
	void onMouseMove(Event *);

	bool onTouchesBegin(Touch*, Event*);
	void onTouchesMoved(Touch*, Event*);
	void onTouchesEnded(Touch*, Event*);



};