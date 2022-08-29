//
//  BaseOject.h
//  PikachuConnect
//
//  Created by HarryNguyen on 8/18/16.
//
//

#ifndef BaseOject_h
#define BaseOject_h

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class BaseObject: public Node {
public:
  Sprite* bgNode;
  Sprite* character;
  Label* textCharacter;
  int type;
  Vec2 matrixPosition;
  Vec2 position;
public:
  
  BaseObject();
  virtual ~BaseObject();
  void setTypeObject(int type);
  int getTypeObject();
  void setMatrixPosition(Vec2 matrixPosition);
  Vec2 getMatrixPosition();
  void setPositionObject(const Vec2& pos);  
};

#endif /* BaseOject_h */
