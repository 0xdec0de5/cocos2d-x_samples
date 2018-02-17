#pragma once

#include "cocos2d.h"
#include "GameLayer.h"


class GameMenu : public cocos2d::Layer
{
private:

public:
	static cocos2d::Scene* scene();

	void update(float deltaTime);

	virtual bool init();

	//New Game Click Handler
	void onNewGameClick(cocos2d::Ref * sender);

	CREATE_FUNC(GameMenu)

};