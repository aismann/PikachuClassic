//
//  DAPikachu.h
//  PikachuConnect
//
//  Created by NguyenHoang on 8/19/16.
//
//

#ifndef DAPikachu_h
#define DAPikachu_h

#include <stdio.h>
#include <algorithm> 
#include "cocos2d.h"
#include "PikachuObject.h"
#include "MyLine.h"
USING_NS_CC;

class DelegateDrawer
{
public:
    virtual void listerDrawer(int type, int typeSub, int result, const Point& p1, const Point& p2)=0;
    virtual void listerDrawerUL(int type, int typeSub, int downAndUp, int result, const Point& p1, const Point& p2) = 0;
};

class AlgorithmPikachu {
public:
    std::vector<PikachuObject*> arrayPikachus;
    int width;
    int height;
    bool typeBuild;
public:
    DelegateDrawer* delegate;
    AlgorithmPikachu();
    virtual ~AlgorithmPikachu();
    static AlgorithmPikachu* getInstance();
    
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
    //Check pos
    MyLine checkTwoPoint(Point p1, Point p2);
    
    void setDelegate(DelegateDrawer* mdelegate);
    void setTypeBuildAL(bool isbuild);
};

#endif /* DAPikachu_h */
