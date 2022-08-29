//
//  BaseOject.cpp
//  PikachuConnect
//
//  Created by HarryNguyen on 8/18/16.
//
//

#include "BaseOject.h"
BaseObject::BaseObject() {}

BaseObject::~BaseObject() {}

void BaseObject::setTypeObject(int type) {
  this->type = type;
}

int BaseObject::getTypeObject() {
  return type;
}

void BaseObject::setMatrixPosition(Vec2 matrixPosition) {
  this->matrixPosition = matrixPosition;
}

Vec2 BaseObject::getMatrixPosition() {
  return matrixPosition;
}

void BaseObject::setPositionObject(const Vec2& pos) {
  position = pos;
}

