
//  KidRunCity
//
//  Created by Nguyễn Chí Hoàng on 7/3/15.
//
//
#include "AndroidScene.h"
#include "HomeScene.h"
Scene* AndroidScene::CreateScene(){
    auto newScene = Scene::create();
    auto layer = AndroidScene::create();
    newScene->addChild(layer);
    return newScene;
}
bool AndroidScene::init(){
    if(!Layer::init()){
        return false;
    }
    CCLOG("11111111111111111111");
    LayerColor* gameoverLayer = LayerColor::create(Color4B(255,255,255,200), Director::getInstance()->getWinSize().width, Director::getInstance()->getWinSize().height);
    this->addChild(gameoverLayer,100);
    
    auto backGround = Sprite::create("logo.png");
    backGround->setPosition(Vec2( Director::getInstance()->getWinSize().width/2 , Director::getInstance()->getWinSize().height/2 ));
    gameoverLayer->addChild(backGround);
    scheduleOnce(schedule_selector(AndroidScene::update), 3.0f);
    return true;
}

void AndroidScene::update(float dt){
    Director::getInstance()->replaceScene(HomeScene::createHomeScene());
}
