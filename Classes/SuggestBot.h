//
//  SuggestBot.h
//  PikuchuConnect
//
//  Created by HarryNguyen on 11/10/16.
//
//

#ifndef SuggestBot_h
#define SuggestBot_h

#include <stdio.h>
#include <algorithm>
#include "cocos2d.h"
#include "PikachuObject.h"
#include "MyLine.h"
USING_NS_CC;

class DelegateAutoDrawer {
public:
  virtual void listerDrawerAI(int type, int typeSub, int result, const Point& p1, const Point& p2)=0;
  virtual void listerDrawerULAI(int type, int typeSub, int downAndUp, int result, const Point& p1, const Point& p2) = 0;
};

class SuggestBot {
public:
  std::vector<PikachuObject*> pikachuObjectList;
  int width;
  int height;
  bool isType;
  DelegateAutoDrawer* delegate;
public:
  SuggestBot();
  virtual ~SuggestBot();
  static SuggestBot* getInstance();
  
  bool checkLineY(int y1, int y2, int x);
  bool checkLineX(int x1, int x2, int y);
  int countNumberObjectBetween(const Point& p1, const Point& p2);
  int checkRectX(Point p1, Point p2);
  int checkRectY(Point p1, Point p2);
  int checkMoreLineY(Point p1, Point p2, int type);
  int checkMoreLineX(Point p1, Point p2, int type);
  void setArrayValueVisible(const std::vector<PikachuObject*> &array);
  void setWidthAndHeightMatrix(int width, int height);
  std::vector<PikachuObject*> getArrayTagPikachu();
  MyLine checkTwoPointGenType(Point p1, Point p2);
  void setDelegate(DelegateAutoDrawer* mDelegate);
  void setType(bool isType);
};


#endif /* SuggestBot_h */
