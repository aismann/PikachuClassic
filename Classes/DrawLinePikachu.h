//
//  DrawLinePikachu.h
//  PikuchuConnect
//
//  Created by HarryNguyen on 10/23/16.
//
//

#ifndef DrawLinePikachu_h
#define DrawLinePikachu_h

#include <stdio.h>

#include "cocos2d.h"
USING_NS_CC;

class DrawLinePikachu : public Ref {
public:
  Scene* mainScene;
  
public:
  DrawLinePikachu();
  virtual ~DrawLinePikachu();
  void drawLineTwoPoint(const Point& p1, const Point& p2, float timeDelay);
  void initWithScene(Node* node);
};

#endif /* DrawLinePikachu_h */
