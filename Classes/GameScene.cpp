
//  PikachuConnect
//
//  Created by NguyenHoang on 8/18/16.
//
//
#include "GameScene.h"
#include "ButtonCustom.h"
#include "GameDefine.h"
#include "HomeScene.h"
#include "PikachuObject.h"
#include "MyLine.h"
#include "DrawLinePikachu.h"
#include "PopupGame.h"
#include "AdmodAndroid.h"
#include "SimpleAudioEngine.h"
#include "GoogleReward.h"

#define WIDTH_BUTTON 138
#define HEIGHT_BUTTON 138
#define BUFFER_LABEL 20.0f
#define FONT_SIZE_LARGE 50
#define FONT_SIZE_SMALL 46
#define MAX_WIDTH 14
#define MAX_HEIGHT 7
#define COUNT_TOUCH_START 0
#define BUFFER_DRAW_Y 26
#define BUFFER_DRAW_X 10
#define TIME_UPDATE_PROGRESS 0.028f
#define TAG_BTN_OK_INPUT 12344
#define COLOR_BG_POP_UP Color4B(50.0f/255.0f, 50.0f/255.0f, 50.0f/255.0f,100.0f)

enum{
    z_Order_bg = 0,
    z_Order_gameBoard = 1,
    z_Order_Layout = 2,
};

typedef enum
{
    TAG_BACK_OKAY = 100,
    TAG_BACK_CLOSE = 101,
    TAG_WIN_NEXT = 104,
    TAG_OVER_REPLAY = 105,
    TAG_OVER_MAINHOME = 106,
    TAG_PAUSE_PLAY = 107,
    TAG_PAUSE_HOME = 108,
}TAG_BUTTON;


typedef enum
{
    TAG_POP_UP_BACK = 1400,
    TAG_POP_UP_REFRESH = 1401,
    TAG_POP_UP_WIN = 1402,
    TAG_POP_UP_GAMEOVER = 1403,
    TAG_POP_UP_PAUSE = 1404,
    TAG_LAYER_START_GAME = 1405,
    
}TAG_POPUP;

#define TIME_DELAY 0.054f
#define TIME_DELAY_LINE 0.034f

USING_NS_CC;

Scene* GameScene::createSceneGameScene()
{
    auto scene = Scene::create();
    auto layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    if(!arrayPositionTouch.empty())
    {
        arrayPositionTouch.clear();
    }
    countSuggest = 3;
    countRefresh = 3;
    isShowOnePopup = false;
    ispause = false;
    currentTouchID = -1;
    
    isFirstTouch = false;
    countTouch = COUNT_TOUCH_START;
    winSize = Director::getInstance()->getWinSize();
    auto sprite = Sprite::create("bgGameScene.png");
    sprite->setPosition(Vec2(winSize.width/2, winSize.height/2));
    this->addChild(sprite);
    
    /*setup data in game*/
    level = UserDefault::getInstance()->getIntegerForKey("Level-Local", 1);  /*Setup Data*/
    score = 0;
    this->createProgressBarGameScene(1.0f + level/200.0f);
    this->createLeftLayout();           /* Left Layout */
    this->createRightLayout();          /* Right Layout */
    widthGameboard = MAX_WIDTH;
    heightGameboard = MAX_HEIGHT;
    
    /*random type PIKACHU*/
    AlgorithmRandom* randomAI = AlgorithmRandom::getInstance();
    this->randomLevelPlay(level, randomAI);
    
    /*Ramdom type drop here*/
    if(level == 1)
    {
        typeDropGameBoard = DROP_IDLE;
    }
    else
    {
        srand( (unsigned)time(NULL) );
        typeDropGameBoard = rand()%4;
    }
    
    randomAI->setMaxtrixWithHight(widthGameboard-2, heightGameboard-2);
    randomAI->createVectorRamdomIndex();
    randomAI->printVectorLookingFor();
    
    
    /*Create gameboard*/
    gameboard =  new GameBoard(widthGameboard,heightGameboard);
    gameboard->initWithScene(this);
    Vec2 pos = gameboard->convertToWorldSpace(Vec2((Director::getInstance()->getWinSize().width/2 - widthGameboard/2*SHAPE_WIDTH - SHAPE_WIDTH/6)*widthGameboard/MAX_WIDTH,-SHAPE_HEIGHT*0.6));
    gameboard->setVectorTypePikachu(randomAI->getVectorLookingFor());
    gameboard->setPositionGameBoard(pos);
    gameboard->setPosition(pos);
    gameboard->createGameboard();
    gameboard->setGameboardTypeDrop(typeDropGameBoard);     /*game board set type drop*/
    gameboard->printPikachuType();
    
    srand( (unsigned)time(NULL) );
    randomEat1 = rand() %  11;
    randomEat2 = rand() %  21 + 10;
    randomEat3 = rand() %  16 + 20;
    
    
    /*create AI check eat two pikachu*/
    algorithmEatBasic = new AlgorithmPikachu();
    algorithmEatBasic->setTypeBuildAL(true);
    algorithmEatBasic->setWidthAndHeightMaxtrix(widthGameboard, heightGameboard);
    algorithmEatBasic->setArrayValueVisiable(gameboard->getArrayValuePikachus());
    algorithmEatBasic->setDelegate(this);
    
    /*setAI auto update Pikachu when not path eat */
    aiRandomSuggestPikachu = new AIRandomSuggest();
    aiRandomSuggestPikachu->settype(false);
    aiRandomSuggestPikachu->setWidthAndHeightMaxtrix(widthGameboard, heightGameboard);
    aiRandomSuggestPikachu->setArrayValueVisiable(gameboard->getArrayValuePikachus());
    aiRandomSuggestPikachu->setDelegate(this);
    gameboard->setAIForGame(aiRandomSuggestPikachu);
    
    
    /*Create Layer Start*/
    this->createLayerStartGame();
    
    /*Add Touch Event*/
    auto touch = EventListenerTouchOneByOne::create();
    touch->setSwallowTouches(true);
    touch->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBeginGameScene, this);
    touch->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEndGameScene, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touch, this);
    this->scheduleUpdate();   /*update*/
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    AdmodAndroid::hideBanner();
#endif
    GoogleReward::unlockachievementGoogle(level);
    return true;
}

#pragma TOUCH_EVENT

bool GameScene::onTouchBeginGameScene(Touch* mtouch, Event* pEvent)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    AdmodAndroid::hideBanner();
#endif
    CCLOG("Touch id %d", mtouch->getID());
    if(gameboard && !ispause )
    {
        if(countTouch < 2 && currentTouchID != 0)
        {
            currentTouchID = mtouch->getID();
            Vec2 pos =  gameboard->convertPosGameboard(mtouch->getLocation());
            CCLOG("Touch id %d", currentTouchID);
            if (currentTouchID == 0)
            {
                if(pos.x >= 1 && pos.x <= widthGameboard-2 && pos.y >=1 && pos.y <= heightGameboard-2)
                {
                    if(gameboard->getAtPosGameboard(pos)->getValueVisiable() != TAG_PIKACHU_HIDDEN)
                    {
                        if (pos.x == posTouchOne.x && pos.y == posTouchOne.y && countTouch == 1)
                        {
                            PikachuObject* pikachu = gameboard->getAtPosGameboard(pos);
                            pikachu->backToStartObject();
                            posTouchOne = Vec2(-1,-1);
                            countTouch = 0;
                            currentTouchID = -1;
                            
                        }
                        else
                        {
                            countTouch ++;
                            if(countTouch %2 == 1)
                            {
                                posTouchOne = pos;
                            }
                            PikachuObject* pikachu = gameboard->getAtPosGameboard(pos);
                            pikachu->actionWhenClick();
                            /*click*/
                            if(countTouch == 1)
                            {
                                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("PClick.mp3");
                            }
                            if (countTouch < 2)
                            {
                                this->scheduleOnce([=](float dt)
                                                   {
                                                       gameboard->actionBackGameboard(pos);
                                                   }, 0.1f, "updateBack");
                            }
                            return true;
                        }
                    }
                    else
                    {
                        currentTouchID = -1;
                    }
                }
                else
                {
                    currentTouchID = -1;
                }
            }
        }
    }
    return false;
}

void GameScene::onTouchEndGameScene(Touch* mTouch, Event* pEvent)
{
    
    if(countTouch == 2  && currentTouchID  != -1 && !ispause)
    {
        currentTouchID = mTouch->getID();
        posTouchTwo = gameboard->convertPosGameboard(mTouch->getLocation());
        if(posTouchTwo.x >= 0 && posTouchTwo.x <= widthGameboard-1 && posTouchTwo.y >=0 && posTouchTwo.y <= heightGameboard-1)
        {
            
            MyLine lineGame = algorithmEatBasic->checkTwoPoint(posTouchOne, posTouchTwo);
            PikachuObject* object1 = gameboard->getAtPosGameboard(posTouchOne);
            PikachuObject* object2 = gameboard->getAtPosGameboard(posTouchTwo);
            if (lineGame.checZeroLine())
            {
                this->scheduleOnce([=](float dt){
                    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("PMiss.mp3");
                }, 0.1f, "UpdateSound1");
                
                object1->backToStartObject();
                object2->backToStartObject();
            }
            else
            {
                if(object1->getTypeObject() == object2->getTypeObject())
                {
                    if(object1->getTypeObject() == randomEat1){
                        this->rewardWhenClickExtractly(1);
                    }
                    if(object1->getTypeObject() == randomEat2){
                        this->rewardWhenClickExtractly(2);
                    }
                    if(object1->getTypeObject() == randomEat3){
                        this->rewardWhenClickExtractly(1);
                    }
                    object1->effectWhenDieObject();
                    object2->effectWhenDieObject();
                    
                    progress->setStatus(ADDTIME_PROGRESS);
                    gameboard->setValueHiddenObjectWithPosition(posTouchOne, posTouchTwo);
                    gameboard->dropPikachu(typeDropGameBoard);
                    algorithmEatBasic->setArrayValueVisiable(gameboard->getArrayValuePikachus());
                    aiRandomSuggestPikachu->setArrayValueVisiable(gameboard->getArrayValuePikachus());
                    
                }
                else
                {
                    this->scheduleOnce([=](float dt){
                        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("PMiss.mp3");
                    }, 0.1f, "UpdateSound2");
                    object1->backToStartObject();
                    object2->backToStartObject();
                }
            }
            countTouch = 0;
        }
        gameboard->actionBackGameboard(Vec2::ZERO);
    }
    currentTouchID = -1;
    
}

void GameScene::rewardWhenClickExtractly(int typeEat){
    if(typeEat == 1)
    {
        if(level < 4)
        {
            UserDefault::getInstance()->setIntegerForKey(BUGGET_MONEY_BUY, UserDefault::getInstance()->getIntegerForKey(BUGGET_MONEY_BUY, DEFAULT_MONEY_GAME) + REWARD_EAT_EASY);
        }
        else {
            
            UserDefault::getInstance()->setIntegerForKey(BUGGET_MONEY_BUY, UserDefault::getInstance()->getIntegerForKey(BUGGET_MONEY_BUY, DEFAULT_MONEY_GAME) + REWARD_EAT_EASY*2);
        }
    }
    if(typeEat == 2)
    {
        if(level < 4)
        {
            UserDefault::getInstance()->setIntegerForKey(BUGGET_MONEY_BUY, UserDefault::getInstance()->getIntegerForKey(BUGGET_MONEY_BUY, DEFAULT_MONEY_GAME) + REWARD_EAT_HARD);
        }
        else {
            
            UserDefault::getInstance()->setIntegerForKey(BUGGET_MONEY_BUY, UserDefault::getInstance()->getIntegerForKey(BUGGET_MONEY_BUY, DEFAULT_MONEY_GAME) + REWARD_EAT_HARD*2);
        }
    }
    if(lbMoneyGame != nullptr){
        char bufferReward[20] = {0};
        sprintf(bufferReward, "%d",UserDefault::getInstance()->getIntegerForKey(BUGGET_MONEY_BUY, DEFAULT_MONEY_GAME));
        lbMoneyGame->setString(bufferReward);
        this->animationLabelReward();
    }
}

void GameScene::animationLabelReward(){
    auto action1 = ScaleTo::create(0.15, 2.0);
    auto action2 = DelayTime::create(0.1);
    auto action3 = ScaleTo::create(0.15,1.0f );
    lbMoneyGame->runAction(Sequence::create(action1,action2,action3, NULL));
}

#pragma DRAWER_OPENGL
/*hoangnc4
 31/10/2016
 Drawer line for path
 */
void GameScene::listerDrawer(int type, int typeSub, int result, const Point& p1, const Point& p2)
{
    if (gameboard)
    {
        
        algorithmEatBasic->setTypeBuildAL(true);
        PikachuObject* object1 = gameboard->getAtPosGameboard(p1);
        PikachuObject* object2 = gameboard->getAtPosGameboard(p2);
        if(object1->getTypeObject() == object2->getTypeObject())
        {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("PSucces.mp3");
            /*update score*/
            if(algorithmEatBasic->typeBuild == true)
            {
                this->updateScoreWith(2);
            }
            if (type == LINE)
            {
                Point pos1 = gameboard->getPositionScene(Vec2(p1.x, p1.y));
                Point pos2 = gameboard->getPositionScene(Vec2(p2.x, p2.y));
                DrawLinePikachu* drawLine = new DrawLinePikachu();
                drawLine->initWithScene(this);
                drawLine->drawLineTwoPoint(pos1,pos2,TIME_DELAY_LINE);
            }
            if (type == Z_SHAPE)
            {
                if(typeSub == X_AXIS)
                {
                    Point pos1 = gameboard->getPositionScene(Vec2(p1.x, p1.y));
                    Point pos2 = gameboard->getPositionScene(Vec2(result, p1.y));
                    Point pos3 = gameboard->getPositionScene(Vec2(result, p2.y));
                    Point pos4 = gameboard->getPositionScene(Vec2(p2.x, p2.y));
                    
                    this->drawerLineGeraric(pos1, pos2, pos3, pos4);
                }
                else
                {
                    Point pos1 = gameboard->getPositionScene(Vec2(p1.x, p1.y));
                    Point pos2 = gameboard->getPositionScene(Vec2(p1.x, result));
                    Point pos3 = gameboard->getPositionScene(Vec2(p2.x, result));
                    Point pos4 = gameboard->getPositionScene(Vec2(p2.x, p2.y));
                    
                    this->drawerLineGeraric(pos1, pos2, pos3, pos4);
                }
            }
        }
    }
}
void GameScene::listerDrawerUL(int type, int typeSub, int downAndUp, int result, const Point& p1, const Point& p2)
{
    if (gameboard)
    {
        PikachuObject* object1 = gameboard->getAtPosGameboard(p1);
        PikachuObject* object2 = gameboard->getAtPosGameboard(p2);
        if(object1->getTypeObject() == object2->getTypeObject())
        {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("PSucces.mp3");
            /*update score*/
            if(algorithmEatBasic->typeBuild == true)
            {
                this->updateScoreWith(2);
            }
            if (type == U_SHAPE)
            {
                if(typeSub == X_AXIS)
                {
                    Point pos1 = gameboard->getPositionScene(Vec2(p1.x, p1.y));
                    Point pos2 = gameboard->getPositionScene(Vec2(result, p1.y));
                    Point pos3 = gameboard->getPositionScene(Vec2(result, p2.y));
                    Point pos4 = gameboard->getPositionScene(Vec2(p2.x, p2.y));
                    
                    Point temp2 =  Point(pos2.x - BUFFER_DRAW_X* downAndUp, pos2.y);
                    Point temp3 =  Point(pos3.x - BUFFER_DRAW_X* downAndUp, pos3.y);
                    
                    this->drawerLineGeraric(pos1, temp2, temp3, pos4);
                    
                }
                if(typeSub == Y_AXIS)
                {
                    Point pos1 = gameboard->getPositionScene(Vec2(p1.x, p1.y));
                    Point pos2 = gameboard->getPositionScene(Vec2(p1.x, result));
                    Point pos3 = gameboard->getPositionScene(Vec2(p2.x, result));
                    Point pos4 = gameboard->getPositionScene(Vec2(p2.x, p2.y));
                    
                    Point temp2 =  Point(pos2.x, pos2.y - BUFFER_DRAW_Y*downAndUp);
                    Point temp3 = Point(pos3.x, pos3.y - BUFFER_DRAW_Y*downAndUp);
                    
                    this->drawerLineGeraric(pos1, temp2, temp3, pos4);
                }
            }
            if(type == L_SHAPE)
            {
                if(typeSub == X_AXIS)
                {
                    Point pos1 = gameboard->getPositionScene(Vec2(p1.x, p1.y));
                    Point pos2 = gameboard->getPositionScene(Vec2(result, p1.y));
                    Point pos3 = gameboard->getPositionScene(Vec2(result, p2.y));
                    Point pos4 = gameboard->getPositionScene(Vec2(p2.x, p2.y));
                    
                    this->drawerLineGeraric(pos1, pos2, pos3, pos4);
                    
                }
                if(typeSub == Y_AXIS)
                {
                    Point pos1 = gameboard->getPositionScene(Vec2(p1.x, p1.y));
                    Point pos2 = gameboard->getPositionScene(Vec2(p1.x, result));
                    Point pos3 = gameboard->getPositionScene(Vec2(p2.x, result));
                    Point pos4 = gameboard->getPositionScene(Vec2(p2.x, p2.y));
                    this->drawerLineGeraric(pos1, pos2, pos3, pos4);
                }
            }
            
        }
    }
    
}

void GameScene::updateScoreWith(int score)
{
    this->score = this->score + score;
    char bufferAddScore[20]= {0};
    sprintf(bufferAddScore, "Score: %d", this->score);
    lbScore->setString(bufferAddScore);
}

#pragma CREATE_UI_GAME

void GameScene::createLeftLayout()
{
    
    auto spriteRight = Sprite::create("layoutButton.png");
    spriteRight->setAnchorPoint(Vec2::ZERO);
    spriteRight->setPosition(Vec2(0, winSize.height - spriteRight->getContentSize().height));
    this->addChild(spriteRight,z_Order_Layout);
    
    /*Button back*/
    btnBack = ui::Button::create("buttonBack.png","","",ui::Widget::TextureResType::LOCAL);
    btnBack->setPosition(Vec2(spriteRight->getPositionX() + btnBack->getContentSize().width*0.6, spriteRight->getPositionY() + spriteRight->getContentSize().height/2 + 5.0f));
    btnBack->setTag(TAG_BTN_BACK);
    btnBack->addClickEventListener(CC_CALLBACK_1(GameScene::buttonClickGameScene,this));
    this->addChild(btnBack,z_Order_Layout);
    
    
    /*Label Level*/
    char bufferLevel[20] = {0};
    sprintf(bufferLevel, "Level: %d", level);
    lbLevel = Label::createWithTTF(bufferLevel, "GROBOLD.ttf", FONT_SIZE_LARGE);
    lbLevel->setAnchorPoint(Vec2(0, 0.5));
    lbLevel->setPosition(Vec2(btnBack->getPositionX() + btnBack->getContentSize().width*0.64, spriteRight->getPositionY() + spriteRight->getContentSize().height*0.5));
    this->addChild(lbLevel,z_Order_Layout);
    
    /*Label Score*/
    char bufferScore[20] = {0};
    sprintf(bufferScore, "Score: %d", score);
    lbScore = Label::createWithTTF(bufferScore, "GROBOLD.ttf", FONT_SIZE_LARGE);
    lbScore->setAnchorPoint(Vec2(0, 0.5));
    lbScore->setPosition(Vec2(lbLevel->getPositionX() + lbLevel->getContentSize().width*1.12 + BUFFER_LABEL, lbLevel->getPositionY()));
    this->addChild(lbScore,z_Order_Layout);
    
    
    /*Money Item*/
    Sprite* spr_Money = Sprite::create("moneyItem.png");
    spr_Money->setPosition(Vec2(lbScore->getPositionX() + lbScore->getContentSize().width*1.46, lbLevel->getPositionY() + lbScore->getContentSize().height*0.36 ));
    this->addChild(spr_Money,z_Order_Layout);
    
    char bufferCoin[20] = {0};
    sprintf(bufferCoin, "%d", UserDefault::getInstance()->getIntegerForKey(BUGGET_MONEY_BUY, DEFAULT_MONEY_GAME));
    lbMoneyGame = Label::createWithTTF(bufferCoin, "GROBOLD.ttf", FONT_SIZE_LARGE);
    lbMoneyGame->setAnchorPoint(Vec2(0, 0.5));
    lbMoneyGame->setPosition(Vec2(spr_Money->getPositionX() + spr_Money->getContentSize().width*0.64 , lbLevel->getPositionY()));
    this->addChild(lbMoneyGame,z_Order_Layout);
    
}

void GameScene::createRightLayout()
{
    /*LeftLayout*/
    auto bgLeftLayout = Sprite::create("layoutButton.png");
    bgLeftLayout->setAnchorPoint(Vec2::ZERO);
    bgLeftLayout->setPosition(Vec2(winSize.width - bgLeftLayout->getContentSize().width, winSize.height - bgLeftLayout->getContentSize().height));
    this->addChild(bgLeftLayout,z_Order_Layout);
    
    
    /*Button Refresh*/
    btnAddTime = new ButtonCustom();
    btnAddTime->setPosition(Vec2(bgLeftLayout->getPositionX() + 10.0f ,bgLeftLayout->getPositionY() + HEIGHT_BUTTON/2 + 10.0f));
    btnAddTime->setValueText(0);
    btnAddTime->setTagButton(TAG_BTN_ADDTIME);
    btnAddTime->createUIButton("buttonAddTime.png");
    btnAddTime->setDelegate(this);
    this->addChild(btnAddTime,z_Order_Layout);
    
    
    /*Button Refresh*/
    btnRefresh = new ButtonCustom();
    btnRefresh->setPosition(Vec2(btnAddTime->getPositionX() + WIDTH_BUTTON*1.3,btnAddTime->getPositionY()));
    btnRefresh->setValueText(countRefresh);
    btnRefresh->setTagButton(TAG_BTN_REFRESH);
    btnRefresh->createUIButton("buttonRefresh.png");
    btnRefresh->setDelegate(this);
    this->addChild(btnRefresh,z_Order_Layout);
    
    /*Suggest*/
    btnSuggest = new ButtonCustom();
    btnSuggest->setPosition(Vec2(btnRefresh->getPositionX() + WIDTH_BUTTON*1.3,btnRefresh->getPositionY()));
    btnSuggest->setTagButton(TAG_BTN_SUGGEST);
    btnSuggest->setValueText(countSuggest);
    btnSuggest->createUIButton("buttonSuggest.png");
    btnSuggest->setDelegate(this);
    this->addChild(btnSuggest,z_Order_Layout);
    
    /*Pause*/
    btnPause = new ButtonCustom();
    btnPause->setPosition(Vec2(btnSuggest->getPositionX() + WIDTH_BUTTON*1.3,btnSuggest->getPositionY()));
    btnPause->setTagButton(TAG_BTN_PAUSE);
    btnPause->setValueText(0);
    btnPause->createUIButton("buttonPause.png");
    btnPause->setDelegate(this);
    this->addChild(btnPause,z_Order_Layout);
}

#pragma DELEGATE_PROGRESSBAR
void GameScene::createProgressBarGameScene(int hardLevel)
{
    auto sp_loading = Sprite::create("bg_Loading.png");
    sp_loading->setPosition(Vec2(winSize.width*0.52, winSize.height - sp_loading->getContentSize().height));
    this->addChild(sp_loading,z_Order_bg);
    
    progress = ProgressBarCustom::getInstaceProgress(100.0f, IDLE_PROGRESS);
    progress->createUIProgressBar(sp_loading->getPosition());
    progress->setTimeUpdate(TIME_UPDATE_PROGRESS*hardLevel);
    progress->setDelegate(this);
    progress->setLevel(level);
    this->addChild(progress,z_Order_bg);
}


void GameScene::setStatusProressTime(int status)
{
    
}
void GameScene::sendStatusGame()
{
    if(isShowOnePopup == false)
    {
        isShowOnePopup = true;
        this->createPopupGameOver();
    }
}


void GameScene::update(float dt)
{
    if(gameboard && gameboard->isStatus == false)
    {
        gameboard->update(dt);
    }
    if(gameboard->isStatus == true && isShowOnePopup == false)
    {
        isShowOnePopup = true;
        this->createPopUpWin();
    }
    if(UserDefault::getInstance()->getIntegerForKey(BUGGET_MONEY_BUY, DEFAULT_MONEY_GAME) < COST_MONEY_BUY && btnAddTime!= nullptr){
        btnAddTime->setDisnableButton();
    }
    if(UserDefault::getInstance()->getIntegerForKey(BUGGET_MONEY_BUY, DEFAULT_MONEY_GAME) >= COST_MONEY_BUY && btnAddTime!= nullptr){
        btnAddTime->setEnableButton();
    }
}

#pragma CREATE_POP_UP
void GameScene::createPopupBack()
{
    Sprite* tempButtonSize = Sprite::create("btn-ok-back.png");
    LayerColor* colorBg = LayerColor::create(COLOR_BG_POP_UP, winSize.width, winSize.height);
    colorBg->setPosition(Vec2::ZERO);
    PopupGame* popupBack = new PopupGame();
    popupBack->setdelegate(this);
    popupBack->setPosition(Vec2::ZERO);
    popupBack->createLayoutWithZorder();
    popupBack->createUibackGroundWithFileName("popup-back.png");
    popupBack->createPopupWithbuttonWithFileName("btn-ok-back.png",Vec2( winSize.width/2 - tempButtonSize->getContentSize().width/2 - 10, winSize.height*0.36),TAG_BACK_OKAY);
    popupBack->createPopupWithbuttonWithFileName("btn-close-back.png", Vec2(winSize.width/2  + tempButtonSize->getContentSize().width/2 + 10,winSize.height*0.36), TAG_BACK_CLOSE);
    popupBack->setTag(TAG_POP_UP_BACK);
    popupBack->addChild(colorBg,1);
    this->addChild(popupBack,TAG_POP_UP_BACK);
    
}


void GameScene::createPopUpWin()
{
    if(progress)
    {
        progress->setStatus(PAUSE_PROGRESS);
    }
    PopupGame* popupWin = new PopupGame();
    popupWin->setdelegate(this);
    popupWin->setPosition(Vec2::ZERO);
    popupWin->createLayoutWithZorder();
    popupWin->createUibackGroundWithFileName("popup-win.png");
    popupWin->createPopupWithbuttonWithFileName("btn-next-win.png",Vec2( winSize.width/2, winSize.height/4),TAG_WIN_NEXT);
    popupWin->setTag(TAG_POP_UP_WIN);
    
    /*Level*/
    char bufferLevel[512] = {0};
    sprintf(bufferLevel, "Level: %d", level);
    Label* labelCompletelevel = Label::createWithTTF(bufferLevel, "GROBOLD.ttf", 64);
    labelCompletelevel->setPosition(Vec2(winSize.width/2, winSize.height*0.52));
    popupWin->setLabelPopup(labelCompletelevel);
    
    /*Score*/
    char coinWinBuffer[512] = {0};
    char bufferScore[512] = {0};
    int tempLevel =  UserDefault::getInstance()->getIntegerForKey("BestLevel", 1);
    if(level >= tempLevel){
        tempLevel = level;
    }
    sprintf(bufferScore, "Best level: %d",tempLevel);
    Label* scoreCompletelevel = Label::createWithTTF(bufferScore, "GROBOLD.ttf", 64);
    scoreCompletelevel->setPosition(Vec2(winSize.width/2, labelCompletelevel->getPositionY()- scoreCompletelevel->getContentSize().height*1.4));
    popupWin->setLabelPopup(scoreCompletelevel);
    this->addChild(popupWin,TAG_POP_UP_WIN);
    auto coinReward = Sprite::create("coin-reward.png");
    if(level > UserDefault::getInstance()->getIntegerForKey("BestLevel", 0))
    {
        UserDefault::getInstance()->setIntegerForKey("BestLevel", level);
        UserDefault::getInstance()->setIntegerForKey(BUGGET_MONEY_BUY, UserDefault::getInstance()->getIntegerForKey(BUGGET_MONEY_BUY, DEFAULT_MONEY_GAME) + REWARD_WIN_GAME_MONEY*2);
        sprintf(coinWinBuffer, "+ %d coins new record", REWARD_WIN_GAME_MONEY*2);
        
        coinReward->setPosition(Vec2(winSize.width*0.46 - scoreCompletelevel->getContentSize().width/2, scoreCompletelevel->getPositionY() - scoreCompletelevel->getContentSize().height/2 - coinReward->getContentSize().height/2));
        
    }else{
        UserDefault::getInstance()->setIntegerForKey(BUGGET_MONEY_BUY, UserDefault::getInstance()->getIntegerForKey(BUGGET_MONEY_BUY, DEFAULT_MONEY_GAME) + REWARD_WIN_GAME_MONEY);
        sprintf(coinWinBuffer, "+ %d coins win", REWARD_WIN_GAME_MONEY);
        coinReward->setPosition(Vec2(winSize.width*0.5 - scoreCompletelevel->getContentSize().width/2, scoreCompletelevel->getPositionY() - scoreCompletelevel->getContentSize().height/2 - coinReward->getContentSize().height/2));
    }
    popupWin->addChild(coinReward,TAG_POP_UP_WIN);
    
    auto lbCoin = Label::createWithTTF(coinWinBuffer, "GROBOLD.ttf", 54);
    lbCoin->setPosition(Vec2(0, 0.5f));
    lbCoin->setPosition(Vec2(coinReward->getPositionX() + coinReward->getContentSize().width/2 + lbCoin->getContentSize().width/2,coinReward->getPositionY()));
    popupWin->addChild(lbCoin,TAG_POP_UP_WIN);
    
}
void GameScene::createPopupGameOver()
{
    if(progress)
    {
        progress->setStatus(PAUSE_PROGRESS);
    }
    Sprite* temp = Sprite::create("btn-mainhome-over.png");
    PopupGame* popupGameover = new PopupGame();
    popupGameover->setdelegate(this);
    popupGameover->setPosition(Vec2::ZERO);
    popupGameover->createLayoutWithZorder();
    popupGameover->createUibackGroundWithFileName("popup-gameover.png");
    popupGameover->createPopupWithbuttonWithFileName("btn-mainhome-over.png",Vec2( winSize.width/2 - temp->getContentSize().width*2/3, winSize.height*0.28),TAG_OVER_MAINHOME);
    popupGameover->createPopupWithbuttonWithFileName("btn-replay-over.png",Vec2(winSize.width/2 + temp->getContentSize().width*2/3,winSize.height*0.28), TAG_OVER_REPLAY);
    
    /*level*/
    char bufferLevelGameover[512] = {0};
    sprintf(bufferLevelGameover, "Level %d", level);
    Label* levelGameover = Label::createWithTTF(bufferLevelGameover, "GROBOLD.ttf", 52);
    levelGameover->setPosition(Vec2(winSize.width/2, winSize.height/2 - temp->getContentSize().height*0.6));
    popupGameover->setLabelPopup(levelGameover);
    
    popupGameover->setTag(TAG_POP_UP_GAMEOVER);
    this->addChild(popupGameover,TAG_POP_UP_GAMEOVER);
    
}
void GameScene::createPopUpPause()
{
    if(progress)
    {
        progress->setStatus(PAUSE_PROGRESS);
    }
    Sprite* temp = Sprite::create("btn-mainhome-over.png");
    PopupGame* popupPause = new PopupGame();
    popupPause->setdelegate(this);
    popupPause->setPosition(Vec2::ZERO);
    popupPause->createLayoutWithZorder();
    popupPause->createUibackGroundWithFileName("popup-pause.png");
    popupPause->createPopupWithbuttonWithFileName("btn-mainhome-over.png",Vec2( winSize.width/2 - temp->getContentSize().width*2/3, winSize.height*0.28),TAG_PAUSE_HOME);
    popupPause->createPopupWithbuttonWithFileName("btnplay-pause.png",Vec2(winSize.width/2 + temp->getContentSize().width*2/3,winSize.height*0.28), TAG_PAUSE_PLAY);
    
    popupPause->setTag(TAG_POP_UP_PAUSE);
    this->addChild(popupPause,TAG_POP_UP_PAUSE);
}

void GameScene::sendTagActionPopup(int tag)
{
    switch (tag)
    {
        case TAG_PAUSE_PLAY:
            if (this->getChildByTag(TAG_POP_UP_PAUSE))
            {
                this->removeChildByTag(TAG_POP_UP_PAUSE);
                ispause = false;
                if(progress)
                {
                    progress->setStatus(IDLE_PROGRESS);
                }
                gameboard->gameboardWhenPlay();
            }
            
            break;
        case TAG_PAUSE_HOME:
            Director::getInstance()->replaceScene(HomeScene::createHomeScene());
            break;
        case TAG_BACK_OKAY:
            Director::getInstance()->replaceScene(HomeScene::createHomeScene());
            break;
        case TAG_BACK_CLOSE:
            if (this->getChildByTag(TAG_POP_UP_BACK))
            {
                this->removeChildByTag(TAG_POP_UP_BACK);
                ispause = false;
                if(progress)
                {
                    progress->setStatus(IDLE_PROGRESS);
                }
                gameboard->gameboardWhenPlay();
            }
            break;
        case TAG_WIN_NEXT:
            UserDefault::getInstance()->setIntegerForKey("Level-Local", UserDefault::getInstance()->getIntegerForKey("Level-Local", 1) + 1);
            Director::getInstance()->replaceScene(GameScene::createSceneGameScene());
            break;
            
        case TAG_OVER_REPLAY:
            UserDefault::getInstance()->setIntegerForKey("Level-Local", UserDefault::getInstance()->getIntegerForKey("Level-Local", 1));
            Director::getInstance()->replaceScene(GameScene::createSceneGameScene());
            break;
        case TAG_OVER_MAINHOME:
            UserDefault::getInstance()->setIntegerForKey("Level-Local",1);
            Director::getInstance()->replaceScene(HomeScene::createHomeScene());
            break;
        default:
            break;
    }
}

#pragma EVENT_CLICK_BUTTON
void GameScene::sendEventClickButton(int tag)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("soundClick.mp3");
    CCLOG("tag click %d", tag);
    switch (tag) {
        case TAG_BTN_REFRESH:
            if(ispause == false)
            {
                if(countRefresh > 0)
                {
                    countRefresh--;
                    if(gameboard){
                        gameboard->refreshGameBoard();
                    }
                }else{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
                    AdmodAndroid::showFullAdvertiment();
                    if(AdmodAndroid::getStatusShowFull() == true){
                        countRefresh = 3;
                    }else{
                        countRefresh = 0;
                    }
#endif
                }
                btnRefresh->setValueText(countRefresh);
            }
            break;
        case TAG_BTN_PAUSE:
            if(progress)
            {
                ispause = true;
                progress->setStatus(PAUSE_PROGRESS);
                gameboard->gameboardWhenPause();
                createPopUpPause();
            }
            break;
        case TAG_BTN_SUGGEST:
            if(btnSuggest)
            {
                if(countSuggest > 0 )
                {
                    countSuggest--;
                    if(ispause == false)
                    {
                        aiRandomSuggestPikachu->settype(true);
                        this->scheduleOnce([=](float dt){
                            
                            if(aiRandomSuggestPikachu)
                            {
                                aiRandomSuggestPikachu->settype(false);
                            }
                        }, 0.6f,"updateSuggestFalse");
                    }
                }else{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
                    AdmodAndroid::showFullAdvertiment();
                    if(AdmodAndroid::getStatusShowFull() == true){
                        countSuggest = 3;
                    }else{
                        countSuggest = 0;
                    }
#endif
                }
                btnSuggest->setValueText(countSuggest);
            }
            break;
        case TAG_BTN_ADDTIME:
            if(progress && UserDefault::getInstance()->getIntegerForKey(BUGGET_MONEY_BUY, DEFAULT_MONEY_GAME) >= COST_MONEY_BUY){
                UserDefault::getInstance()->setIntegerForKey(BUGGET_MONEY_BUY, UserDefault::getInstance()->getIntegerForKey(BUGGET_MONEY_BUY, DEFAULT_MONEY_GAME) - COST_MONEY_BUY);
                progress->setStatus(BUYTIME_PROGRESS);
                
                char bufferDiscountItem[20] = {0};
                sprintf(bufferDiscountItem, "%d", UserDefault::getInstance()->getIntegerForKey(BUGGET_MONEY_BUY, DEFAULT_MONEY_GAME));
                lbMoneyGame->setString(bufferDiscountItem);
            }
            break;
        default:
            break;
    }
}
void GameScene::buttonClickGameScene(Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("soundClick.mp3");
    int tag = ((ui::Button*)pSender)->getTag();
    switch (tag)
    {
        case TAG_BTN_BACK:
            if(ispause == false)
            {
                if(progress)
                {
                    progress->setStatus(PAUSE_PROGRESS);
                }
                gameboard->gameboardWhenPause();
                ispause = true;
                createPopupBack();
            }
            break;
        default:
            break;
    }
}

#pragma DRAWER_LISTEN
void GameScene::listerDrawerAI(int type, int typeSub, int result, const Point& p1, const Point& p2)
{
    if (gameboard)
    {
        PikachuObject* object1 = gameboard->getAtPosGameboard(p1);
        PikachuObject* object2 = gameboard->getAtPosGameboard(p2);
        if(object1->getTypeObject() == object2->getTypeObject())
        {
            if (type == LINE)
            {
                Point pos1 = gameboard->getPositionScene(Vec2(p1.x, p1.y));
                Point pos2 = gameboard->getPositionScene(Vec2(p2.x, p2.y));
                DrawLinePikachu* drawLine = new DrawLinePikachu();
                drawLine->initWithScene(this);
                drawLine->drawLineTwoPoint(pos1,pos2,TIME_DELAY_LINE);
            }
            if (type == Z_SHAPE)
            {
                if(typeSub == X_AXIS)
                {
                    Point pos1 = gameboard->getPositionScene(Vec2(p1.x, p1.y));
                    Point pos2 = gameboard->getPositionScene(Vec2(result, p1.y));
                    Point pos3 = gameboard->getPositionScene(Vec2(result, p2.y));
                    Point pos4 = gameboard->getPositionScene(Vec2(p2.x, p2.y));
                    this->drawerLineGeraric(pos1, pos2, pos3, pos4);
                }
                else
                {
                    Point pos1 = gameboard->getPositionScene(Vec2(p1.x, p1.y));
                    Point pos2 = gameboard->getPositionScene(Vec2(p1.x, result));
                    Point pos3 = gameboard->getPositionScene(Vec2(p2.x, result));
                    Point pos4 = gameboard->getPositionScene(Vec2(p2.x, p2.y));
                    this->drawerLineGeraric(pos1, pos2, pos3, pos4);
                }
            }
        }
    }
    
}
void GameScene::listerDrawerULAI(int type, int typeSub, int downAndUp, int result, const Point& p1, const Point& p2)
{
    if (gameboard)
    {
        PikachuObject* object1 = gameboard->getAtPosGameboard(p1);
        PikachuObject* object2 = gameboard->getAtPosGameboard(p2);
        if(object1->getTypeObject() == object2->getTypeObject())
        {
            if (type == U_SHAPE)
            {
                if(typeSub == X_AXIS)
                {
                    Point pos1 = gameboard->getPositionScene(Vec2(p1.x, p1.y));
                    Point pos2 = gameboard->getPositionScene(Vec2(result, p1.y));
                    Point pos3 = gameboard->getPositionScene(Vec2(result, p2.y));
                    Point pos4 = gameboard->getPositionScene(Vec2(p2.x, p2.y));
                    Point temp2 =  Point(pos2.x - BUFFER_DRAW_X* downAndUp, pos2.y);
                    Point temp3 =  Point(pos3.x - BUFFER_DRAW_X* downAndUp, pos3.y);
                    
                    this->drawerLineGeraric(pos1, temp2, temp3, pos4);
                    
                }
                if(typeSub == Y_AXIS)
                {
                    Point pos1 = gameboard->getPositionScene(Vec2(p1.x, p1.y));
                    Point pos2 = gameboard->getPositionScene(Vec2(p1.x, result));
                    Point pos3 = gameboard->getPositionScene(Vec2(p2.x, result));
                    Point pos4 = gameboard->getPositionScene(Vec2(p2.x, p2.y));
                    Point temp2 =  Point(pos2.x, pos2.y - BUFFER_DRAW_Y*downAndUp);
                    Point temp3 = Point(pos3.x, pos3.y - BUFFER_DRAW_Y*downAndUp);
                    
                    this->drawerLineGeraric(pos1, temp2, temp3, pos4);
                }
            }
            if(type == L_SHAPE)
            {
                if(typeSub == X_AXIS)
                {
                    Point pos1 = gameboard->getPositionScene(Vec2(p1.x, p1.y));
                    Point pos2 = gameboard->getPositionScene(Vec2(result, p1.y));
                    Point pos3 = gameboard->getPositionScene(Vec2(result, p2.y));
                    Point pos4 = gameboard->getPositionScene(Vec2(p2.x, p2.y));
                    this->drawerLineGeraric(pos1, pos2, pos3, pos4);
                }
                if(typeSub == Y_AXIS)
                {
                    Point pos1 = gameboard->getPositionScene(Vec2(p1.x, p1.y));
                    Point pos2 = gameboard->getPositionScene(Vec2(p1.x, result));
                    Point pos3 = gameboard->getPositionScene(Vec2(p2.x, result));
                    Point pos4 = gameboard->getPositionScene(Vec2(p2.x, p2.y));
                    this->drawerLineGeraric(pos1, pos2, pos3, pos4);
                }
            }
            
        }
    }
    
}
void GameScene::drawerLineGeraric(const Point& p1,const Point& p2, const Point& p3, const Point& p4)
{
    DrawLinePikachu* drawLine = new DrawLinePikachu();
    drawLine->initWithScene(this);
    drawLine->drawLineTwoPoint(p1,p2,TIME_DELAY);
    
    DrawLinePikachu* drawLine2 = new DrawLinePikachu();
    drawLine2->initWithScene(this);
    drawLine2->drawLineTwoPoint(p2,p3,TIME_DELAY);
    
    DrawLinePikachu* drawLine3 = new DrawLinePikachu();
    drawLine3->initWithScene(this);
    drawLine3->drawLineTwoPoint(p3,p4,TIME_DELAY);
}

void GameScene::randomLevelPlay(int level , AlgorithmRandom* randomAI)
{
    if (level == 1)
    {
        randomAI->createVectorIndexPikachu36(3, 6);
    }
    else if(level == 2)
    {
        randomAI->createVectorIndexPikachu36(4, 5);
    }
    else if(level >= 3 && level < 5)
    {
        randomAI->createVectorIndexPikachu36(4,6);
    }
    else if(level >= 5 && level < 7)
    {
        randomAI->createVectorIndexPikachu36(5,6);
    }
    else
    {
        randomAI->createVectorIndexPikachu36(6, 6);
    }
}
void GameScene::createLayerStartGame()
{
    ispause = true;
    if(gameboard)
    {
        gameboard->gameboardWhenPause();
    }
    if(progress)
    {
        progress->setStatus(PAUSE_PROGRESS);
    }
    
    LayerColor* colorBgStart = LayerColor::create(COLOR_BG_POP_UP, winSize.width, winSize.height);
    colorBgStart->setPosition(Vec2::ZERO);
    colorBgStart->setTag(TAG_LAYER_START_GAME);
    Label* lbPause = Label::createWithTTF("Tap to play", "GROBOLD.ttf", 72);
    lbPause->setPosition(Vec2(winSize.width/2, winSize.height/2));
    colorBgStart->addChild(lbPause, 100);
    this->addChild(colorBgStart,TAG_LAYER_START_GAME);
    
    /*Add Touch Event*/
    auto touch = EventListenerTouchOneByOne::create();
    touch->setSwallowTouches(true);
    touch->onTouchBegan = CC_CALLBACK_2(GameScene::ontouchStartTouchGame, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touch, colorBgStart);
}
bool GameScene::ontouchStartTouchGame(Touch* mTouch, Event* pEevent)
{
    if(gameboard)
    {
        gameboard->gameboardWhenPlay();
    }
    if(this->getChildByTag(TAG_LAYER_START_GAME))
    {
        this->removeChildByTag(TAG_LAYER_START_GAME);
    }
    this->scheduleOnce([=](float dt){
        ispause = false;
        if(progress)
        {
            progress->setStatus(IDLE_PROGRESS);
        }
        
    }, 0.4f, "StartGame");
    return true;
}
void GameScene::onEnter()
{
    Layer::onEnter();
    EventListenerKeyboard *keyboardEvent = EventListenerKeyboard::create();
    keyboardEvent->onKeyReleased = [](EventKeyboard::KeyCode keyCode, Event*){
        if(keyCode == EventKeyboard::KeyCode::KEY_BACK){
            Director::getInstance()->replaceScene(HomeScene::createHomeScene());
        }
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardEvent, this);
}
void GameScene::onExit()
{
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this);
    
}

