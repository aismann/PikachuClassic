//
//  AIRandomSuggest.h
//  PikuchuConnect
//
//  Created by NguyenHoang on 11/10/16.
//
//

#ifndef AIRandomSuggest_h
#define AIRandomSuggest_h


#include <stdio.h>
#include <algorithm>
#include "cocos2d.h"
#include "PikachuObject.h"
#include "MyLine.h"
USING_NS_CC;

class DelegateAutoDrawer
{
public:
    virtual void listerDrawerAI(int type, int typeSub, int result, const Point& p1, const Point& p2)=0;
    virtual void listerDrawerULAI(int type, int typeSub, int downAndUp, int result, const Point& p1, const Point& p2) = 0;
};


class AIRandomSuggest {
public:
    std::vector<PikachuObject*> arrayPikachus;
    int width;
    int height;
    bool istype;
    DelegateAutoDrawer* delegate;
public:
    AIRandomSuggest();
    virtual ~AIRandomSuggest();
    static AIRandomSuggest* getInstance();
    
    bool  checkLineY(int y1, int y2, int x);
    bool  checkLineX(int x1, int x2, int y);
    int countNumberObjectBetween(const Point& p1, const Point& p2);
    int checkRectX(Point p1, Point p2);
    int checkRectY(Point p1, Point p2);
    int checkMoreLineY(Point p1, Point p2, int type);
    int checkMoreLineX(Point p1, Point p2, int type);
    void setArrayValueVisiable(const std::vector<PikachuObject*> &array);
    void setWidthAndHeightMaxtrix(int width, int height);
    std::vector<PikachuObject*> getArrayTagPikachu();
    MyLine checkTwoPointGenType(Point p1, Point p2);
    void setDelegate(DelegateAutoDrawer* mdelegate);
    void settype(bool istype);
};


#endif /* AIRandomSuggest_h */
