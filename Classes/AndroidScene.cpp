
//  KidRunCity
//
//  Created by Harry Nguyen on 7/3/15.
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
  LayerColor* gameOverLayer = LayerColor::create(Color4B(255,255,255,200),
                                                 Director::getInstance()->getWinSize().width, Director::getInstance()->getWinSize().height);
  this->addChild(gameOverLayer,100);
  
  auto backGround = Sprite::create("logo.png");
  backGround->setPosition(Vec2( Director::getInstance()->getWinSize().width/2,
                               Director::getInstance()->getWinSize().height/2 ));
  gameOverLayer->addChild(backGround);
  scheduleOnce(schedule_selector(AndroidScene::update), 3.0f);
  return true;
}

void AndroidScene::update(float dt){
  Director::getInstance()->replaceScene(HomeScene::createHomeScene());
}
