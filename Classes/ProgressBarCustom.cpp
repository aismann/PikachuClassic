//
//  ProgressBarCustom.cpp
//  PikachuConnect
//
//  Created by HarryNguyen on 8/18/16.


#include "ProgressBarCustom.h"

ProgressBarCustom::ProgressBarCustom() {}

ProgressBarCustom::~ProgressBarCustom() {}

void ProgressBarCustom::createUIProgressBar(const Vec2& pos) {
  loadingBar = ui::LoadingBar::create("loading.png");
  loadingBar->setAnchorPoint(Vec2(0.5,0.5));
  loadingBar->setPosition(pos);
  loadingBar->setPercent(value);
  loadingBar->setDirection(ui::LoadingBar::Direction::LEFT);
  this->setContentSize(loadingBar->getContentSize());
  this->addChild(loadingBar);
  
}

ProgressBarCustom* ProgressBarCustom::getInstanceProgress(int valueLoading, int status) {
  ProgressBarCustom* object = new ProgressBarCustom();
  object->setValue(valueLoading);
  object->setStatus(status);
  return object;
}

void ProgressBarCustom::setValue(float value) {
  this->value = value;
}

float ProgressBarCustom::getValue() {
  return value;
}

void ProgressBarCustom::onEnter() {
  Node::onEnter();
  this->scheduleUpdate();
  
}

void ProgressBarCustom::onExit() {
  Node::onExit();
  this->unscheduleUpdate();
}

void ProgressBarCustom::update(float dt) {
  if(loadingBar == NULL) { return; }
  
  if(loadingStatus == IDLE_PROGRESS) {
    float value = loadingBar->getPercent();
    value  = value - updatePercent;
    loadingBar->setPercent(value);
    if (value <= 0) {
      if (mDelegate){
        mDelegate->sendStatusGame();
      }
      loadingStatus = END_GAME;
    }
  }
  
  if(loadingStatus == PAUSE_PROGRESS) {
    float value = loadingBar->getPercent();
    loadingBar->setPercent(value);
  }
  
  if (loadingStatus == ADDITION_TIME_PROGRESS) {
    float value = loadingBar->getPercent();
    if(levelGame < 2) {
      value  += 1.0f;
    } else if(levelGame >= 2 && levelGame < 5) {
      value += 1.4f;
    } else {
      value += 2.0f;
    }
    
    loadingBar->setPercent(value);
    loadingStatus = IDLE_PROGRESS;
  }
  if(loadingStatus == BUY_TIME_PROGRESS) {
    float value = loadingBar->getPercent();
    value += 30;
    loadingBar->setPercent(value);
    loadingStatus = IDLE_PROGRESS;
  }
}

void ProgressBarCustom::setStatus(int status) {
  this->loadingStatus = status;
}

void ProgressBarCustom::setDelegate(DelegateProgress* delegate) {
  mDelegate = delegate;
}

void ProgressBarCustom::setLevelGame(int level) {
  levelGame = level;
}

void ProgressBarCustom::setTimeUpdate(float dt) {
  updatePercent = dt;
}

void ProgressBarCustom::setLevel(int level){
  this->levelGame = level;
}
