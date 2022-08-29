//
//  CheckPairBot.h
//  PikachuConnect
//
//  Created by HarryNguyen on 8/19/16.
//
//

#ifndef suggestionBot_h
#define suggestionBot_h

#include <stdio.h>
#include <algorithm> 
#include "cocos2d.h"
#include "PikachuObject.h"
#include "MyLine.h"
USING_NS_CC;

class DelegateDrawer {
public:
  virtual void listerDrawer(int type, int typeSub, int result, const Point& p1, const Point& p2)=0;
  virtual void listerDrawerUL(int type, int typeSub, int downAndUp, int result, const Point& p1, const Point& p2) = 0;
};

class CheckPairBot {
public:
  std::vector<PikachuObject*> pikachuObjectList;
  int width;
  int height;
  bool typeBuild;
public:
  DelegateDrawer* delegate;
  CheckPairBot();
  virtual ~CheckPairBot();
  static CheckPairBot* getInstance();
  
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
  //Check pos
  MyLine checkTwoPoint(Point p1, Point p2);
  
  void setDelegate(DelegateDrawer* mDelegate);
  void setTypeBuildAL(bool isBuilt);
};

#endif /* suggestionBot_h */
