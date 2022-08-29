//
//  HomeScene.hpp
//  PikachuConnect
//
//  Created by HarryNguyen on 8/18/16.
//
//

#ifndef HomeScene_h
#define HomeScene_h

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "DataUser.h"
USING_NS_CC;

class HomeScene : public Layer {
public:
  Size winSize;
  ui::Button* soundOffButton;
  ui::Button* soundOnButton;
  ui::Button* chartButton;
  ui::Button* helpButton ;
  ui::Button* startButton;
  Layer*  chartLayer ;
  Sprite* chartBackgroundSprite;
  bool isHelp;
  std::vector<DataUser*> arrayUser;
public:
  static Scene* createHomeScene();
  HomeScene();
  virtual ~HomeScene();
  void createUIHomeScene();
  void handleClickButtonHomeScene(Ref* pSender);
  void createHelpGame();
  void createChartGame();
  void onEnter();
  void onExit();
  
};



#endif /* HomeScene_h */
