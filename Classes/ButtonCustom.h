//
//  ButtonCustom.h
//  PikachuConnect
//
//  Created by NguyenHoang on 8/18/16.
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
    Sprite* spritebutton;
    Label* lbText;
    int valueText;
    int tagButton;
    DelegateButton* mdelegate;
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
    int getTagButotn();
    void buttonClick(Ref* pSender);
    void setDelegate(DelegateButton* delegate);
    void setEnableButton();
    void setDisnableButton();
};

#endif /* ButtonCustom_h */
