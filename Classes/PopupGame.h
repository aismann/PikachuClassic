//
//  PopupGame.h
//  PikachuConnection
//
//  Created by Hoang Nguyen on 11/15/16.
//
//

#ifndef PopupGame_h
#define PopupGame_h

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

class DelegateEventPopup
{
public:
    virtual void sendTagActionPopup(int tag) = 0;
};

class PopupGame: public Node
{
private:
    Size sizePopup;
    int typePopup;
    Label* labelPopup;
    DelegateEventPopup* delegate;
public:
    PopupGame();
    ~PopupGame();
    void createLayoutWithZorder();
    void createPopupWithbuttonWithFileName(const char* fileButton, const Vec2& pos, int tag);
    void createUibackGroundWithFileName(const char* fileName);
    void setTypePopup(int type);
    void btnClickPopup(Ref* psender);
    void setdelegate(DelegateEventPopup* mdelegate);
    void setLabelPopup(Label* label);
    Size sizeOfPopup();
};

#endif /* PopupGame_h */
