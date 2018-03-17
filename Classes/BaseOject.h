//
//  BaseOject.h
//  PikachuConnect
//
//  Created by NguyenHoang on 8/18/16.
//
//

#ifndef BaseOject_h
#define BaseOject_h

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class BaseObject: public Node
{
public:
    Sprite* bgNode;
    Sprite* character;
    Label* textCharacter;
    int type;
    Vec2 posMaxtrix;
    Vec2 position;
public:
    
    BaseObject();
    virtual ~BaseObject();
    virtual  void createUIObject(int model);
    void setTypeObject(int type);
    int getTypeObject();
    virtual void runActionStartGame();
    void setPosMaxtrix(Vec2 posMaxtrix);
    Vec2 getPosMaxtrix();
    void setPositionObject(const Vec2& pos);
    virtual void actionWhenClick();
    
    virtual void effectWhenDieObject();
    virtual void backToStartObject();
    
    virtual void setVisiableSprite();
    virtual void updateZorder(int newZoder);
    virtual void updateUI(int type);
};

#endif /* BaseOject_h */
