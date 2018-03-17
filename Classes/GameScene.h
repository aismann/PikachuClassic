
//  PikachuConnect
//
//  Created by NguyenHoang on 8/18/16.
//
//
#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ProgressBarCustom.h"
#include "ButtonCustom.h"
#include "GameBoard.h"
#include "AlgorithmPikachu.h"
#include "AIRandomSuggest.h"
#include "PopupGame.h"
#include "ButtonCustom.h"
#include "AlgorithmRandom.h"
USING_NS_CC;

class GameScene : public cocos2d::Layer,DelegateButton, DelegateDrawer, DelegateProgress, DelegateAutoDrawer, DelegateEventPopup
{
public:
    bool canTouchContinue;
    Label* lbCoint;
    Label* lbLevel;
    Label* lbScore;
    Label* lbMoneyGame;
    Size winSize;
    int countTouch;
    bool isFirstTouch;
    Vec2 posTouchOne;
    Vec2 posTouchTwo;
    int countRefresh;
    int countSuggest;
    
    int randomEat1;
    int randomEat2;
     int randomEat3;
    
    ProgressBarCustom* progress;
    int widthGameboard;
    int heightGameboard;
    GameBoard* gameboard;
    AlgorithmPikachu* algorithmEatBasic;
    AIRandomSuggest* aiRandomSuggestPikachu;
    
    std::vector<Vec2> arrayPositionTouch;
    int currentTouchID;
    bool ispause;
    int level;
    int score;
    int typeDropGameBoard;
    bool isShowOnePopup;
    ButtonCustom* btnAddTime;
    ButtonCustom* btnSuggest;
    ButtonCustom* btnRefresh;
    ButtonCustom* btnPause;
    ui::Button* btnBack;
    Sprite* imaginPut;
    ui::Button* btn_ok;
    cocos2d::ui::TextField* textFieldName;
    
public:
    static cocos2d::Scene* createSceneGameScene();
    virtual bool init();
    CREATE_FUNC(GameScene);
    void createProgressBarGameScene(int hardLevel);
    void createRightLayout();
    void createLeftLayout();
    void sendEventClickButton(int tag);
    void buttonClickGameScene(Ref* pSender);
    void update(float dt);
    virtual void listerDrawer(int type, int typeSub, int result, const Point& p1, const Point& p2);
    virtual void listerDrawerUL(int type, int typeSub, int downAndUp, int result, const Point& p1, const Point& p2);
    
    /*settouch*/
    bool onTouchBeginGameScene(Touch* mTouch, Event* pEvent);
    void onTouchEndGameScene(Touch* mTouch, Event* pEvent);
    
    bool ontouchStartTouchGame(Touch* mTouch, Event* pEevent);
    
    virtual void setStatusProressTime(int status);
    virtual void sendStatusGame();
    
    void updateScoreWith(int score);
    
    /*AI*/
    virtual void listerDrawerAI(int type, int typeSub, int result, const Point& p1, const Point& p2);
    virtual void listerDrawerULAI(int type, int typeSub, int downAndUp, int result, const Point& p1, const Point& p2);
    
    /*Event-Popup*/
    virtual void sendTagActionPopup(int tag);
    
    void createPopupBack();
    void createPopUpWin();
    void createPopupGameOver();
    void createPopUpPause();
    void createLayerStartGame();
    
    void drawerLineGeraric(const Point& p1,const Point& p2, const Point& p3, const Point& p4);
    void randomLevelPlay(int level , AlgorithmRandom* randomAI);
    void onEnter();
    void onExit();
    void rewardWhenClickExtractly(int typeEat);
    void animationLabelReward();
};

#endif // __GAME_SCENE_H__
