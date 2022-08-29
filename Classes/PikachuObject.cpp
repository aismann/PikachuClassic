//
//  PikachuObject.cpp
//  PikachuConnect
//
//  Created by HarryNguyen on 8/18/16.
//
//

#include "PikachuObject.h"
#include "GameDefine.h"
#define SCALE_OBJECT 3
#define MAX_ARRAY 36
enum {
  z_Order_bgNode = 0,
  z_Order_Character = 1,
};

static std::string pikachuTileNames[MAX_ARRAY] = {"pieces1.png","pieces2.png","pieces3.png","pieces4.png","pieces5.png","pieces6.png",
  "pieces7.png","pieces8.png","pieces9.png","pieces10.png","pieces11.png","pieces12.png",
  "pieces13.png","pieces14.png","pieces15.png","pieces16.png","pieces17.png","pieces18.png",
  "pieces19.png","pieces20.png","pieces21.png","pieces22.png","pieces23.png","pieces24.png",
  "pieces25.png","pieces26.png","pieces27.png","pieces28.png","pieces29.png","pieces30.png",
  "pieces31.png","pieces32.png","pieces33.png","pieces34.png","pieces35.png","pieces36.png"};

PikachuObject::PikachuObject() {}

PikachuObject::~PikachuObject() {}


void PikachuObject::createUIObject() {
  bgNode = Sprite::create("bgAnimal1.png");
  bgNode->setPosition(this->getPosition());
  this->addChild(bgNode,z_Order_bgNode);
  character = Sprite::createWithSpriteFrameName(pikachuTileNames[type]);
  
  character->setPosition(this->getPosition());
  character->setScale(SCALE_OBJECT);
  this->addChild(character,z_Order_Character);
  if (valueVisible == TAG_PIKACHU_VISIBLE) {
    character->setVisible(true);
    bgNode->setVisible(true);
  } else {
    character->setVisible(false);
    bgNode->setVisible(false);
  }
}

void PikachuObject::updateUI(int type) {
  if(character) {
    character->setSpriteFrame(pikachuTileNames[type]);
  }
}

void PikachuObject::setTagObject(int tagObject) {
  this->tagObject = tagObject;
}

int PikachuObject::getTagObject() {
  return tagObject;
}

void PikachuObject::actionWhenClick() {
  auto action1 = ScaleTo::create(0.08f, 0.8f);
  auto action2 = DelayTime::create(0.02f);
  auto sequence = Sequence::create(action1, action2, NULL);
  bgNode->runAction(sequence);
}

void PikachuObject::effectWhenDieObject() {
  bgNode->setVisible(false);
  character->setVisible(false);
}

void PikachuObject::backToNormalObject() {
  bgNode->runAction(ScaleTo::create(0.1f, 1.0f));
}

void PikachuObject::hidePikachu() {
  bgNode->setVisible(false);
  character->setVisible(false);
}

void PikachuObject::updateNewPosition(const Vec2& position) {
  this->setPosition(position);
  if(bgNode) {
    bgNode->setPosition(this->getPosition());
  }
  if(character) {
    character->setPosition(this->getPosition());
  }
}

void PikachuObject::setValueVisible(int valueVisible) {
  this->valueVisible = valueVisible;
}

int PikachuObject::getValueVisible() {
  return valueVisible;
}

void PikachuObject::update(float dt) {
  if(this->getValueVisible() ==  TAG_PIKACHU_HIDDEN) {
    bgNode->setVisible(false);
    character->setVisible(false);
  } else {
    bgNode->setVisible(true);
    character->setVisible(true);
  }
}

void PikachuObject::setVisibleSprite() {
  if(bgNode->isVisible() == false) {
    bgNode->setVisible(true);
  }
  if(character->isVisible() == false) {
    character->setVisible(true);
  }
}

void PikachuObject::objectWhenPause() {
  
  if(bgNode) {
    bgNode->setLocalZOrder(10001);
  }
  if(character) {
    character->setLocalZOrder(10000);
  }
}

void PikachuObject::objectWhenPlay() {
  if(bgNode) {
    bgNode->setLocalZOrder(10000);
  }
  if(character) {
    character->setLocalZOrder(10001);
  }
}


