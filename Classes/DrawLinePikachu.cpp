//
//  DrawLinePikachu.cpp
//  PikuchuConnect
//
//  Created by NguyenHoang on 10/23/16.
//
//

#include "DrawLinePikachu.h"

#define HEIGHT_LINE 10
#define COLOR_LINE Color4F::ORANGE
#define TAG_DRAWER 1034


DrawLinePikachu::DrawLinePikachu()
{
    
}
DrawLinePikachu::~DrawLinePikachu()
{
    
}
void DrawLinePikachu::onEnter()
{
    
}
void DrawLinePikachu::onExit()
{
    
}
void DrawLinePikachu::drawLineTwoPoint(const Point& p1, const Point& p2,  float timedelay)
{
    
    Node* node = new Node();
    node->setPosition(p1);
    mainscene->addChild(node,1000);
    DrawNode* drawerLine = DrawNode::create();
    drawerLine->setTag(TAG_DRAWER);
    if(p1.x == p2.x)
    {
        if(p1.y > p2.y)
        {
            drawerLine->drawSegment(p1,Vec2(p2.x , p2.y - p1.distance(p2)), HEIGHT_LINE, COLOR_LINE);
            
        }
        else
        {
            drawerLine->drawSegment(p1,Vec2(p2.x , p2.y + p1.distance(p2)), HEIGHT_LINE, COLOR_LINE);
            
        }
    }
    if(p1.y == p2.y)
    {
        if (p1.x > p2.x) {
            drawerLine->drawSegment(p1,Vec2(p2.x - p1.distance(p2), p2.y), HEIGHT_LINE, COLOR_LINE);
        }
        else
        {
            drawerLine->drawSegment(p1,Vec2(p2.x + p1.distance(p2), p2.y), HEIGHT_LINE, COLOR_LINE);
        }
        
    }
    node->addChild(drawerLine,TAG_DRAWER);
    auto delayTime = DelayTime::create(timedelay);
    auto actionHidden = CallFunc::create([=](){
        node->setVisible(false);
    });
    drawerLine->runAction(Sequence::create(delayTime,actionHidden, NULL));
    
}

void DrawLinePikachu::update(float dt)
{
    
}
void DrawLinePikachu::initWithScene(Node* node)
{
    mainscene = (Scene*) node;
}
