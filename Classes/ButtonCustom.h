//
//  ButtonCustom.h
//  PikachuConnect
//
//  Created by HarryNguyen on 8/18/16.
//
//

#ifndef ButtonCustom_h
#define ButtonCustom_h

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

class DelegateButton{
public:
  virtual void sendEventClickButton(int tag) = 0;
};

class ButtonCustom: public Node {
public:
  ui::Button* button;
  Sprite* buttonSprite;
  Label* lbText;
  int valueText;
  int tagButton;
  DelegateButton* mDelegate;
public:
  
  ButtonCustom();
  virtual ~ButtonCustom();
  void createUIButton(const char* fileName);
  void setValueText(int value);
  int getValueText();
  void onEnter();
  void onExit();
  void update(float dt);
  void setTagButton(int tag);
  int getTagButton();
  void buttonClick(Ref* pSender);
  void setDelegate(DelegateButton* delegate);
  void setEnableButton();
  void setDisableButton();
};

#endif /* ButtonCustom_h */
