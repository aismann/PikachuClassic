//
//  DrawLinePikachu.h
//  PikuchuConnect
//
//  Created by NguyenHoang on 10/23/16.
//
//

#ifndef DrawLinePikachu_h
#define DrawLinePikachu_h

#include <stdio.h>

#include "cocos2d.h"
USING_NS_CC;


class DrawLinePikachu : public Ref
{
public:
    Scene* mainscene;

public:
    DrawLinePikachu();
    virtual ~DrawLinePikachu();
    virtual void onEnter();
    virtual void onExit();
    void drawLineTwoPoint(const Point& p1, const Point& p2, float timedelay);
    void update(float dt);
    void initWithScene(Node* node);
};

#endif /* DrawLinePikachu_h */
