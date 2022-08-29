
//  PikachuConnect
//
//  Created by HarryNguyen on 8/18/16.
//
//
#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ProgressBarCustom.h"
#include "ButtonCustom.h"
#include "GameBoard.h"
#include "CheckPairBot.h"
#include "SuggestBot.h"
#include "PopupGame.h"
#include "ButtonCustom.h"
#include "RandomBot.h"
USING_NS_CC;

class GameScene : public cocos2d::Layer,DelegateButton, DelegateDrawer, DelegateProgress, DelegateAutoDrawer, DelegateEventPopup {
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
  int widthGameBoard;
  int heightGameBoard;
  GameBoard* gameBoard;
  CheckPairBot* algorithmEatBasic;
  SuggestBot* SuggestBotPikachu;
  
  std::vector<Vec2> arrayPositionTouch;
  int currentTouchID;
  bool isPausing;
  int level;
  int score;
  int typeDropGameBoard;
  bool isShowOnePopup;
  ButtonCustom* addTimeButton;
  ButtonCustom* suggestButton;
  ButtonCustom* refreshButton;
  ButtonCustom* pauseButton;
  ui::Button* backButton;
  ui::Button* okayButton;
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
  bool onTouchStartGame(Touch* mTouch, Event* pEvent);
  
  virtual void setStatusProgressTime(int status);
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
  
  void drawerLine(const Point& p1,const Point& p2, const Point& p3, const Point& p4);
  void randomLevelPlay(int level , RandomBot* randomAI);
  void onEnter();
  void onExit();
  void rewardWhenClickExactly(int typeEat);
  void animationLabelReward();
};

#endif // __GAME_SCENE_H__
