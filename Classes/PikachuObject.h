//
//  PikachuObject.h
//  PikachuConnect
//
//  Created by HarryNguyen on 8/18/16.
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
  int valueVisible;
  int model;
public:
  PikachuObject();
  virtual ~PikachuObject();
  void createUIObject();
  virtual void actionWhenClick();
  virtual void effectWhenDieObject();
  virtual void backToNormalObject();
  void hidePikachu();
  void updateNewPosition(const Vec2& position);
  
  virtual void setValueVisible(int valueVisible);
  virtual int getValueVisible();
  
  virtual void setTagObject(int tagObject);
  int getTagObject();
  
  virtual void setVisibleSprite();
  virtual void update(float dt);
  virtual void updateUI(int type);
  
  void objectWhenPause();
  void objectWhenPlay();
  
};

#endif /* PikachuObject_h */
