//
//  PikachuObject.h
//  PikachuConnect
//
//  Created by NguyenHoang on 8/18/16.
//
//

#ifndef PikachuObject_h
#define PikachuObject_h

#include <stdio.h>
#include "cocos2d.h"
#include "BaseOject.h"


class PikachuObject: public BaseObject {
public:
    int tagObject;
    int valueVisiable;
    int model;
public:
    PikachuObject();
    virtual ~PikachuObject();
    void runActionStartGame();
    void createUIObject();
    virtual void actionWhenClick();
    virtual void effectWhenDieObject();
    virtual void backToStartObject();
    void hidePikachu();
    void updateNewPosition(const Vec2& position);
    
    virtual void setValueVisiable(int valueVisiable);
    virtual int getValueVisiable();
    
    virtual void setTagObject(int tagObject);
    int getTagObject();
    
    virtual void setVisiableSprite();
    virtual void update(float dt);
    virtual void onEnter();
    virtual void onExit();
    virtual void updateZorder(int newZoder);
    virtual void updateUI(int type);

    
    void objectWhenPause();
    void objectWhenPlay();
    
};

#endif /* PikachuObject_h */
