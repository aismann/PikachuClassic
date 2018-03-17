//
//  BaseOject.cpp
//  PikachuConnect
//
//  Created by NguyenHoang on 8/18/16.
//
//

#include "BaseOject.h"
BaseObject::BaseObject()
{
    
}
BaseObject::~BaseObject()
{
    
}
void BaseObject::createUIObject(int model)
{
}
void BaseObject::setTypeObject(int type)
{
    this->type = type;
}
int BaseObject::getTypeObject()
{
    return type;
}
void BaseObject::runActionStartGame()
{
    
}
void BaseObject::setPosMaxtrix(Vec2 posMaxtrix)
{
    this->posMaxtrix = posMaxtrix;
}
Vec2 BaseObject::getPosMaxtrix()
{
    return posMaxtrix;
}
void BaseObject::setPositionObject(const Vec2& pos)
{
    position = pos;
}
void BaseObject::actionWhenClick()
{
    
}
void BaseObject::updateZorder(int newZoder)
{
    
}
void BaseObject::updateUI(int type)
{
    
}


void BaseObject::effectWhenDieObject()
{
    
}
void BaseObject::backToStartObject()
{
    
}

void BaseObject::setVisiableSprite()
{
    
}
