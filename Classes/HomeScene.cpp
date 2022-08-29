//
//  HomeScene.cpp
//  PikachuConnect
//
//  Created by HarryNguyen on 8/18/16.
//
//
#include "HomeScene.h"
#include "GameScene.h"
#include "AdmodAndroid.h"
#include "SimpleAudioEngine.h"
#define FONT_SIZE 60
#define ZOOM_SCALE 0.2f

enum {
  z_Oder_backGround = 0,
  z_Oder_Button = 1,
};

typedef enum {
  TAG_LAYOUT_HELP  = 1001,
  TAG_LAYOUT_CHART = 1002,
}LAYOUT;

enum{
  TAG_BTN_SOUND_ON = 101,
  TAG_BTN_SOUND_OFF = 102,
  TAG_BTN_START  = 103,
  TAG_BTN_CHART = 104,
  TAG_BTN_HELP = 105,
};

Scene* HomeScene::createHomeScene() {
  auto scene = Scene::create();
  auto layer = new HomeScene();
  layer->createUIHomeScene();
  scene->addChild(layer);
  return scene;
}

HomeScene::HomeScene() {}

HomeScene::~HomeScene() {}

void HomeScene::createUIHomeScene() {
  CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music.mp3",1);
#if  CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
  AdmodAndroid::showBanner();
#endif
  
  isHelp = false;
  winSize = Director::getInstance()->getWinSize();
  auto background =  Sprite::create("bgGameScene.png");
  background->setPosition(Vec2(winSize.width/2, winSize.height/2));
  this->addChild(background,z_Oder_backGround);
  
  /*SoundOn*/
  soundOnButton = ui::Button::create("btnSoundOn_Normal.png","","",cocos2d::ui::Widget::TextureResType::LOCAL);
  soundOnButton->setSwallowTouches(true);
  soundOnButton->setPosition(Vec2(soundOnButton->getContentSize().width, winSize.height - soundOnButton->getContentSize().height));
  soundOnButton->setTag(TAG_BTN_SOUND_ON);
  soundOnButton->addClickEventListener(CC_CALLBACK_1(HomeScene::handleClickButtonHomeScene,this));
  this->addChild(soundOnButton,z_Oder_Button);
  
  /*Sound-OFF*/
  soundOffButton = ui::Button::create("btnSoundOff.png","","",cocos2d::ui::Widget::TextureResType::LOCAL);
  soundOffButton->setSwallowTouches(true);
  soundOffButton->setPosition(soundOnButton->getPosition());
  soundOffButton->setTag(TAG_BTN_SOUND_OFF);
  soundOffButton->addClickEventListener(CC_CALLBACK_1(HomeScene::handleClickButtonHomeScene,this));
  this->addChild(soundOffButton,z_Oder_Button);
  
  if (UserDefault::getInstance()->getBoolForKey("sound",true)  == true) {
    soundOffButton->setVisible(false);
    soundOnButton->setVisible(true);
  } else {
    soundOffButton->setVisible(true);
    soundOnButton->setVisible(false);
  }
  
  /*Button-Start*/
  startButton = ui::Button::create("btnStart_Normal.png","","",cocos2d::ui::Widget::TextureResType::LOCAL);
  startButton->setPosition(Vec2(winSize.width*0.64, winSize.height*0.5));
  startButton->setTag(TAG_BTN_START);
  startButton->setZoomScale(ZOOM_SCALE);
  startButton->addClickEventListener(CC_CALLBACK_1(HomeScene::handleClickButtonHomeScene,this));
  this->addChild(startButton,z_Oder_Button);
  
  /*Label*/
  auto spNameGame = Label::createWithTTF("Pikachu Onet Classic", "GROBOLD.ttf", 120);
  spNameGame->setTextColor(Color4B::ORANGE);
  spNameGame->setPosition(Vec2(startButton->getPositionX(), startButton->getPositionY() + startButton->getContentSize().height*1.2));
  this->addChild(spNameGame,1000);
  
  
  /*Button CHART */
  chartButton = ui::Button::create("btnChart_Normal.png","","",cocos2d::ui::Widget::TextureResType::LOCAL);
  chartButton->setZoomScale(ZOOM_SCALE);
  chartButton->setPosition(Vec2(startButton->getPositionX() - chartButton->getContentSize().width*0.76,startButton->getPositionY() - chartButton->getContentSize().height*1.4));
  chartButton->setTag(TAG_BTN_CHART);
  chartButton->addClickEventListener(CC_CALLBACK_1(HomeScene::handleClickButtonHomeScene,this));
  this->addChild(chartButton,z_Oder_Button);
  
  /*Button- Help*/
  helpButton = ui::Button::create("btnHelp_Normal.png","","",cocos2d::ui::Widget::TextureResType::LOCAL);
  helpButton->setPosition(Vec2(startButton->getPositionX() + helpButton->getContentSize().width*0.76, chartButton->getPosition().y));
  helpButton->setZoomScale(ZOOM_SCALE);
  helpButton->setTag(TAG_BTN_HELP);
  helpButton->addClickEventListener(CC_CALLBACK_1(HomeScene::handleClickButtonHomeScene,this));
  this->addChild(helpButton,z_Oder_Button);
}



void HomeScene::createHelpGame() {
  isHelp = true;
  chartButton->setEnabled(false);
  startButton->setEnabled(false);
  helpButton->setEnabled(false);
  soundOffButton->setEnabled(false);
  soundOnButton->setEnabled(false);
  
  auto helpLayer = Layer::create();
  helpLayer->setAnchorPoint(Vec2::ZERO);
  helpLayer->setPosition(Vec2::ZERO);
  helpLayer->setTag(TAG_LAYOUT_HELP);
  this->addChild(helpLayer,TAG_LAYOUT_HELP);
  
  Sprite* bgHelp = Sprite::create("help.png");
  bgHelp->setPosition(Vec2(winSize.width/2, winSize.height/2));
  helpLayer->addChild(bgHelp,1000);
  
  
  /*button back*/
  ui::Button* backButton = ui::Button::create("buttonBack.png","","",ui::Widget::TextureResType::LOCAL);
  backButton->setPosition(Vec2(backButton->getContentSize().width, winSize.height - backButton->getContentSize().height));
  backButton->setTag(1245);
  backButton->addClickEventListener(CC_CALLBACK_1(HomeScene::handleClickButtonHomeScene,this));
  helpLayer->addChild(backButton,1000);
}

void HomeScene::handleClickButtonHomeScene(Ref* pSender) {
  int tag = ((ui::Button*)(pSender))->getTag();
  switch (tag) {
    case TAG_BTN_SOUND_ON:
      
      soundOffButton->setVisible(true);
      soundOnButton->setVisible(false);
      
      UserDefault::getInstance()->setBoolForKey("sound", false);
      CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.0f);
      CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.0f);
      break;
    case TAG_BTN_SOUND_OFF:
      soundOffButton->setVisible(false);
      soundOnButton->setVisible(true);
      UserDefault::getInstance()->setBoolForKey("sound", true);
      CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1.0f);
      CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(1.0f);
      break;
    case TAG_BTN_CHART:
#if  CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#endif
#if  CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
      AdmodAndroid::showAchievement();
#endif
      break;
    case TAG_BTN_HELP:
      createHelpGame();
      //Help
      break;
    case TAG_BTN_START:
      //StartGame
      Director::getInstance()->replaceScene(GameScene::createSceneGameScene());
      break;
    case 1245:
      if(this->getChildByTag(TAG_LAYOUT_HELP)) {
        isHelp = false;
        chartButton->setEnabled(true);
        startButton->setEnabled(true);
        helpButton->setEnabled(true);
        soundOffButton->setEnabled(true);
        soundOnButton->setEnabled(true);
        this->removeChildByTag(TAG_LAYOUT_HELP);
      }
      break;
    case 1246:
      if(this->getChildByTag(TAG_LAYOUT_CHART)) {
        chartButton->setEnabled(true);
        startButton->setEnabled(true);
        helpButton->setEnabled(true);
        soundOffButton->setEnabled(true);
        soundOnButton->setEnabled(true);
        this->removeChildByTag(TAG_LAYOUT_CHART);
      }
      break;
    default:
      break;
  }
  CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("soundClick.mp3");
}

void HomeScene::onEnter() {
  Layer::onEnter();
  EventListenerKeyboard *keyboardEvent = EventListenerKeyboard::create();
  keyboardEvent->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event*){
    if(keyCode == EventKeyboard::KeyCode::KEY_BACK){
      if (isHelp) {
        Director::getInstance()->replaceScene(HomeScene::createHomeScene());
      } else {
        Director::getInstance()->end();
      }
      
    }
  };
  Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardEvent, this);
}

void HomeScene::onExit() {
  Layer::onExit();
  Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this);
}





