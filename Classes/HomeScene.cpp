//
//  HomeScene.cpp
//  PikachuConnect
//
//  Created by NguyenHoang on 8/18/16.
//
//
#include "HomeScene.h"
#include "GameScene.h"
#include "AdmodAndroid.h"
#include "SimpleAudioEngine.h"
#define FONT_SIZE 60
enum{
    z_Oder_backGround = 0,
    z_Oder_Button = 1,
};

typedef  enum
{
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

#define ZOOM_SCALE 0.2f

Scene* HomeScene::createHomeScene()
{
    auto scene = Scene::create();
    auto layer = new HomeScene();
    layer->createUIHomeScene();
    scene->addChild(layer);
    return scene;
}

HomeScene::HomeScene()
{
    
}
HomeScene::~HomeScene()
{
    
}
void HomeScene::createUIHomeScene()
{
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
    btnSoundOn = ui::Button::create("btnSoundOn_Normal.png","","",cocos2d::ui::Widget::TextureResType::LOCAL);
    btnSoundOn->setSwallowTouches(true);
    btnSoundOn->setPosition(Vec2(btnSoundOn->getContentSize().width, winSize.height - btnSoundOn->getContentSize().height));
    btnSoundOn->setTag(TAG_BTN_SOUND_ON);
    btnSoundOn->addClickEventListener(CC_CALLBACK_1(HomeScene::btnClickButtonHomeScene,this));
    this->addChild(btnSoundOn,z_Oder_Button);
    
    /*Sound-OFF*/
    btnSoudOff = ui::Button::create("btnSoundOff.png","","",cocos2d::ui::Widget::TextureResType::LOCAL);
    btnSoudOff->setSwallowTouches(true);
    btnSoudOff->setPosition(btnSoundOn->getPosition());
    btnSoudOff->setTag(TAG_BTN_SOUND_OFF);
    btnSoudOff->addClickEventListener(CC_CALLBACK_1(HomeScene::btnClickButtonHomeScene,this));
    this->addChild(btnSoudOff,z_Oder_Button);
    
    if (UserDefault::getInstance()->getBoolForKey("sound",true)  == true)
    {
        btnSoudOff->setVisible(false);
        btnSoundOn->setVisible(true);
    }
    else
    {
        btnSoudOff->setVisible(true);
        btnSoundOn->setVisible(false);
    }
    
    /*Button-Start*/
    btnStart = ui::Button::create("btnStart_Normal.png","","",cocos2d::ui::Widget::TextureResType::LOCAL);
    btnStart->setPosition(Vec2(winSize.width*0.64, winSize.height*0.5));
    btnStart->setTag(TAG_BTN_START);
    btnStart->setZoomScale(ZOOM_SCALE);
    btnStart->addClickEventListener(CC_CALLBACK_1(HomeScene::btnClickButtonHomeScene,this));
    this->addChild(btnStart,z_Oder_Button);
    
    /*Label*/
    auto spNameGame = Label::createWithTTF("Pikachu Onet Classic", "GROBOLD.ttf", 120);
    spNameGame->setTextColor(Color4B::ORANGE);
    spNameGame->setPosition(Vec2(btnStart->getPositionX(), btnStart->getPositionY() + btnStart->getContentSize().height*1.2));
    this->addChild(spNameGame,1000);

    
    /*Button CHART */
    btnChart = ui::Button::create("btnChart_Normal.png","","",cocos2d::ui::Widget::TextureResType::LOCAL);
    btnChart->setZoomScale(ZOOM_SCALE);
    btnChart->setPosition(Vec2(btnStart->getPositionX() - btnChart->getContentSize().width*0.76,btnStart->getPositionY() - btnChart->getContentSize().height*1.4));
    btnChart->setTag(TAG_BTN_CHART);
    btnChart->addClickEventListener(CC_CALLBACK_1(HomeScene::btnClickButtonHomeScene,this));
    this->addChild(btnChart,z_Oder_Button);
    
    /*Button- Help*/
    btnHelp = ui::Button::create("btnHelp_Normal.png","","",cocos2d::ui::Widget::TextureResType::LOCAL);
    btnHelp->setPosition(Vec2(btnStart->getPositionX() + btnHelp->getContentSize().width*0.76, btnChart->getPosition().y));
    btnHelp->setZoomScale(ZOOM_SCALE);
    btnHelp->setTag(TAG_BTN_HELP);
    btnHelp->addClickEventListener(CC_CALLBACK_1(HomeScene::btnClickButtonHomeScene,this));
    this->addChild(btnHelp,z_Oder_Button);
}



void HomeScene::createHelpGame()
{
    
    isHelp = true;
    btnChart->setEnabled(false);
    btnStart->setEnabled(false);
    btnHelp->setEnabled(false);
    btnSoudOff->setEnabled(false);
    btnSoundOn->setEnabled(false);
    
    auto helpLayer = Layer::create();
    helpLayer->setAnchorPoint(Vec2::ZERO);
    helpLayer->setPosition(Vec2::ZERO);
    helpLayer->setTag(TAG_LAYOUT_HELP);
    this->addChild(helpLayer,TAG_LAYOUT_HELP);
    
    Sprite* bgHelp = Sprite::create("help.png");
    bgHelp->setPosition(Vec2(winSize.width/2, winSize.height/2));
    helpLayer->addChild(bgHelp,1000);
    
    
    /*button back*/
    ui::Button* btnBack = ui::Button::create("buttonBack.png","","",ui::Widget::TextureResType::LOCAL);
    btnBack->setPosition(Vec2(btnBack->getContentSize().width, winSize.height - btnBack->getContentSize().height));
    btnBack->setTag(1245);
    btnBack->addClickEventListener(CC_CALLBACK_1(HomeScene::btnClickButtonHomeScene,this));
    helpLayer->addChild(btnBack,1000);
    
}
void HomeScene::btnClickButtonHomeScene(Ref* pSender)
{
    int tag = ((ui::Button*)(pSender))->getTag();
    switch (tag) {
        case TAG_BTN_SOUND_ON:
            
            btnSoudOff->setVisible(true);
            btnSoundOn->setVisible(false);
            
            UserDefault::getInstance()->setBoolForKey("sound", false);
            CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.0f);
            CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.0f);
            break;
        case TAG_BTN_SOUND_OFF:
            btnSoudOff->setVisible(false);
            btnSoundOn->setVisible(true);
            UserDefault::getInstance()->setBoolForKey("sound", true);
            CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1.0f);
            CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(1.0f);
            break;
        case TAG_BTN_CHART:
            
#if  CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#endif
#if  CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
            AdmodAndroid::showAchiment();
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
            if(this->getChildByTag(TAG_LAYOUT_HELP))
            {
                isHelp = false;
                btnChart->setEnabled(true);
                btnStart->setEnabled(true);
                btnHelp->setEnabled(true);
                btnSoudOff->setEnabled(true);
                btnSoundOn->setEnabled(true);
                this->removeChildByTag(TAG_LAYOUT_HELP);
            }
            break;
        case 1246:
            if(this->getChildByTag(TAG_LAYOUT_CHART))
            {
                btnChart->setEnabled(true);
                btnStart->setEnabled(true);
                btnHelp->setEnabled(true);
                btnSoudOff->setEnabled(true);
                btnSoundOn->setEnabled(true);
                this->removeChildByTag(TAG_LAYOUT_CHART);
            }
            break;
        default:
            break;
    }
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("soundClick.mp3");
}


void HomeScene::onEnter()
{
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
void HomeScene::onExit()
{
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this);
    
}





