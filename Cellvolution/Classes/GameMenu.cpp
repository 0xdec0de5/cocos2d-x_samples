#include "GameMenu.h"
#include <string>

using namespace cocos2d;

cocos2d::Scene * GameMenu::scene()
{
	cocos2d::Scene * scene = nullptr;

	scene = cocos2d::Scene::create();
	auto * layer = GameMenu::create();
	scene->addChild(layer);
	return scene;

}

void GameMenu::update(float deltaTime)
{

}

bool GameMenu::init()
{
	const auto winSize = 
		cocos2d::Director::sharedDirector()->getWinSize();

	// Set our backgroung
	auto * background = cocos2d::Sprite::create("image\\loading.png");

	std::string buttons = "image\\button_sprites.png";

	//Create button sprites for menu
	auto newGameNormal = cocos2d::Sprite::create(buttons, cocos2d::Rect(0, 0, 210, 53));
	auto newGameSelected = cocos2d::Sprite::create(buttons, cocos2d::Rect(0, 53, 210, 53));
	auto newGameDisabled = cocos2d::Sprite::create(buttons, cocos2d::Rect(0, 53 * 2, 210, 53));

	// Create MenuItem for new game button
	auto newGameMenuItem = MenuItemSprite::create(

		newGameNormal, newGameSelected, newGameDisabled, 
		CC_CALLBACK_1(GameMenu::onNewGameClick, this)

	);

	auto menu = Menu::create(newGameMenuItem, nullptr);

	this->addChild(background);
	this->addChild(menu);

	return true;
}

void GameMenu::onNewGameClick(cocos2d::Ref * sender)
{
	auto gameScene = Scene::create();
	gameScene->addChild(GameLayer::create());

	Director::getInstance()->replaceScene(gameScene);
}
