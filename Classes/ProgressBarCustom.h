//
//  ProgressBarCustom.h
//  PikachuConnect
//
//  Created by HarryNguyen on 8/18/16.
//
//
#ifndef ProgressBarCustom_h
#define ProgressBarCustom_h

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "GameDefine.h"
USING_NS_CC;

class DelegateProgress {
public:
  virtual void setStatusProgressTime(int status) = 0;
  virtual void sendStatusGame() = 0;
};

class ProgressBarCustom: public Node
{
public:
  ui::LoadingBar* loadingBar;
  int loadingStatus;
  int value;
  DelegateProgress* mDelegate;
  int countTime;
  int levelGame;
  float updatePercent;
public:
  void createUIProgressBar(const Vec2& pos);
  ProgressBarCustom();
  virtual ~ProgressBarCustom();
  virtual void onEnter();
  virtual void onExit();
  void update(float dt);
  void setStatus(int status);
  void setValue(float value);
  float getValue();
  static ProgressBarCustom* getInstanceProgress(int valueLoading,  int status);
  void setDelegate(DelegateProgress* delegate);
  void setLevelGame(int level);
  void setTimeUpdate(float dt);
  void setLevel(int level);
};

#endif /* ProgressBarCustom_h */
