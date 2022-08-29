//
//  ButtonCustom.cpp
//  PikachuConnect
//
//  Created by HarryNguyen on 8/18/16.
//
//

#include "ButtonCustom.h"
enum {
  z_Order_Button = 0,
  z_Order_Label = 1,
};

ButtonCustom::ButtonCustom() {
  valueText = 0;
}

ButtonCustom::~ButtonCustom() {}

void ButtonCustom::createUIButton(const char* fileName) {
  button = ui::Button::create(fileName,"","",ui::Widget::TextureResType::LOCAL);
  button->setPosition(Vec2::ZERO);
  button->setTag(tagButton);
  button->addClickEventListener(CC_CALLBACK_1(ButtonCustom::buttonClick,this));
  this->addChild(button,z_Order_Button);
  
  buttonSprite = Sprite::create("bgCountItem.png");
  buttonSprite->setScale(1.4f);
  buttonSprite->setPosition(Vec2(10, 30));
  button->addChild(buttonSprite,z_Order_Button);
  
  char strValue[4] = {0};
  sprintf(strValue, "%d",valueText);
  lbText = Label::createWithTTF(strValue, "GROBOLD.ttf", 50);
  lbText->setPosition(buttonSprite->getPosition());
  lbText->setTextColor(Color4B::BLACK);
  button->addChild(lbText,z_Order_Label);
  
  if(valueText <= 0) {
    buttonSprite->setVisible(false);
    lbText->setVisible(false);
  } else {
    buttonSprite->setVisible(true);
    lbText->setVisible(true);
  }
}

void ButtonCustom::onEnter() {
  Node::onEnter();
  this->scheduleUpdate();
}

void ButtonCustom::onExit() {
  Node::onExit();
  this->unscheduleUpdate();
}

void ButtonCustom::update(float dt) {
  if(valueText >0) {
    char strValueUpdate[4] = {0};
    sprintf(strValueUpdate, "%d",valueText);
    lbText->setString(strValueUpdate);
    lbText->setVisible(true);
    buttonSprite->setVisible(true);
  } else {
    buttonSprite->setVisible(false);
    lbText->setVisible(false);
  }
}

void ButtonCustom::setValueText(int value) {
  this->valueText = value;
}

int ButtonCustom::getValueText() {
  return valueText;
}

void ButtonCustom::setTagButton(int tag) {
  this->tagButton = tag;
}

int ButtonCustom::getTagButton() {
  return tagButton;
}

void ButtonCustom::buttonClick(Ref* pSender) {
  int tag = ((ui::Button*)pSender)->getTag();
  if(mDelegate) {
    mDelegate->sendEventClickButton(tag);
  }
}

void ButtonCustom::setDelegate(DelegateButton* delegate) {
  this->mDelegate = delegate;
}

void ButtonCustom::setEnableButton() {
  button->setEnabled(true);
}

void ButtonCustom::setDisableButton() {
  button->setEnabled(false);
}
