#pragma once

#include "cocos2d.h"
#include "Player.h"
#include "Baddie.h"


class GameLayer : public cocos2d::Layer
{
private:
	Player * _player = nullptr;
	float _gameTime = 0.0f;
	int _baddieCount = 0;
	Vector<Sprite*> _pool = Vector<Sprite*>(100);

	Label * _lblHealth;
	Label * _lblScore;

	void processEvent(Event * e);

	void onMouseDown(Event *);
	void onMouseUp(Event *);
	void onMouseMove(Event *);

	bool onTouchesBegin(Touch*, Event*);
	void onTouchesMoved(Touch*, Event*);
	void onTouchesEnded(Touch*, Event*);

	void handleCollision(float);
	void updateBaddies(float);
    void playerMove(float);
    void updateMusic(float);
    void updateUi(float);
	void addBaddie();

public:
	GameLayer();

	virtual bool init();
	virtual void update(float);

	static cocos2d::Scene* scene();

	CREATE_FUNC(GameLayer)




};
