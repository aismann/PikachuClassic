//
//  SuggestBot.cpp
//  PikuchuConnect
//
//  Created by HarryNguyen on 11/10/16.
//
//

#include "SuggestBot.h"
#include "GameDefine.h"
#define NO_VALUE 2048
#define VALUE 1024

static SuggestBot* suggestionBot = NULL;

SuggestBot::SuggestBot() {}

SuggestBot::~SuggestBot() {}

SuggestBot* SuggestBot::getInstance() {
  if (suggestionBot != NULL) {
    suggestionBot = new SuggestBot();
  }
  return suggestionBot;
}

void SuggestBot::setWidthAndHeightMatrix(int width, int height) {
  this->width = width;
  this->height = height;
}

void SuggestBot::setArrayValueVisible(const std::vector<PikachuObject*> &array) {
  pikachuObjectList = array;
  
}

std::vector<PikachuObject*> SuggestBot::getArrayTagPikachu() {
  return pikachuObjectList;
}

int SuggestBot::countNumberObjectBetween(const Point& p1, const Point& p2) {
  int temp = 0;
  if(p1.x == p2.x && p1.y != p2.y) {
    int min = std::min(p1.y,p2.y);
    int max = std::max(p1.y,p2.y);
    for (int y = min ; y <= max; y++) {
      if(pikachuObjectList.at(p1.x + y*width)->getValueVisible() == TAG_PIKACHU_VISIBLE) {
        temp++;
      }
    }
  } else if(p1.y == p2.y && p1.x != p2.x) {
    int min = std::min(p1.x,p2.x);
    int max = std::max(p1.x,p2.x);
    for (int x = min ; x <= max; x++) {
      if(pikachuObjectList.at(x + p1.y*width)->getValueVisible() == TAG_PIKACHU_VISIBLE) {
        temp++;
      }
    }
  } else if(p1.x == p2.x && p1.y == p2.y) {
    return VALUE;
  } else {
    return NO_VALUE;
  }
  return temp;
}

bool SuggestBot::checkLineY(int y1, int y2, int x){
  if (countNumberObjectBetween(Point(x,y1), Point(x,y2)) > 2) {
    return false;
  }
  else {
    if(delegate && isType == true) {
      delegate->listerDrawerAI(LINE,Y_AXIS,x, Point(x,y1), Point(x,y2));
    }
  }
  return true;
}

bool SuggestBot::checkLineX(int x1, int x2, int y) {
  if (countNumberObjectBetween(Point(x1,y), Point(x2,y)) > 2) {
    return false;
  } else {
    if(delegate && isType == true) {
      delegate->listerDrawerAI(LINE,X_AXIS, y, Point(x1,y), Point(x2,y));
    }
  }
  return true;
}

int SuggestBot::checkRectY(Point p1, Point p2) {
  Point pMinY = p1, pMaxY = p2;
  if (p1.y > p2.y) {
    pMinY = p2;
    pMaxY = p1;
  }
  for (int y = pMinY.y + 1; y <= pMaxY.y; y++) {
    if((countNumberObjectBetween(Point(pMinY.x,pMinY.y), Point(pMinY.x,y)) == 1 &&
        countNumberObjectBetween(Point(pMinY.x,y), Point(pMaxY.x, y)) == 0 )&&
       (countNumberObjectBetween(Point(pMaxY.x, y), Point(pMaxY.x, pMaxY.y)) == 1 ||
        countNumberObjectBetween(Point(pMaxY.x, y), Point(pMaxY.x, pMaxY.y)) == VALUE)) {
      
      if(delegate && isType == true) {
        delegate->listerDrawerAI(Z_SHAPE,Y_AXIS, y, p1, p2);
      }
      return y;
    }
  }
  return -1;
}

int SuggestBot::checkRectX(Point p1, Point p2) {
  Point pMinX = p1, pMaxX = p2;
  if (p1.x > p2.x) {
    pMinX = p2;
    pMaxX = p1;
  }
  for (int x = pMinX.x + 1; x <= pMaxX.x; x++) {
    if((countNumberObjectBetween(Point(pMinX.x,pMinX.y), Point(x,pMinX.y)) == 1 &&
        countNumberObjectBetween(Point(x,pMinX.y), Point(x, pMaxX.y)) == 0) &&
       (countNumberObjectBetween(Point(x, pMaxX.y), Point(pMaxX.x, pMaxX.y)) == 1 ||
        countNumberObjectBetween(Point(x, pMaxX.y), Point(pMaxX.x, pMaxX.y)) == VALUE)) {
      if(delegate && isType == true) {
        delegate->listerDrawerAI(Z_SHAPE, X_AXIS, x, p1, p2);
      }
      return x;
    }
  }
  return -1;
}

int SuggestBot::checkMoreLineX(Point p1, Point p2, int type) {
  Point pMinX = p1, pMaxX = p2;
  if (p1.x > p2.x) {
    pMinX = p2;
    pMaxX = p1;
  }
  int x = pMaxX.x;
  int col = pMinX.y;
  if (type == -1) {
    x = pMinX.x;
    col = pMaxX.y;
  }
  
  if (countNumberObjectBetween(Point(pMinX.x,col), Point(pMaxX.x,col)) == 1 ||
      p1.x == p2.x) {
    if(countNumberObjectBetween(Point(pMinX.x, pMinX.y), Point(x, col)) == 1 &&
       countNumberObjectBetween(Point(pMaxX.x, pMaxX.y), Point(x, col)) == 1) {
      if(delegate && isType == true) {
        delegate->listerDrawerULAI(L_SHAPE,X_AXIS,type,x,p1,p2);
      }
      CCLOG("L---X %d",x);
      return x;
    }
    x+= type;
    while (pikachuObjectList.at(x + pMinX.y*width)->getValueVisible() != TAG_PIKACHU_VISIBLE &&
           pikachuObjectList.at(x + pMaxX.y*width)->getValueVisible() != TAG_PIKACHU_VISIBLE) {
      if (countNumberObjectBetween(Point(x, pMinX.y),Point(x, pMaxX.y)) == 0) {
        if(delegate && isType == true) {
          delegate->listerDrawerULAI(U_SHAPE,X_AXIS,type,x,p1,p2);
        }
        CCLOG("U---X %d",x);
        return x;
      }
      if( x >= 1 && x <= width -2) {
        x += type;
      }
    }
  }
  return -1;
}

// CheckMoreLineY
int SuggestBot::checkMoreLineY(Point p1, Point p2, int type) {
  Point pMinY = p1, pMaxY = p2;
  if (p1.y > p2.y) {
    pMinY = p2;
    pMaxY = p1;
  }
  // find line and y begin
  int y = pMaxY.y;
  int row = pMinY.x;
  if(type == -1) {
    y = pMinY.y;
    row = pMaxY.x;
  }
  if (countNumberObjectBetween(Point(row, pMinY.y), Point(row, pMaxY.y)) == 1 ||
      p1.y == p2.y) {
    if(countNumberObjectBetween(Point(pMinY.x, pMinY.y), Point(row, y)) == 1 &&
       countNumberObjectBetween(Point(pMaxY.x, pMaxY.y), Point(row, y)) == 1) {
      if(delegate && isType == true) {
        delegate->listerDrawerULAI(L_SHAPE,Y_AXIS,type,y,p1,p2);
      }
      CCLOG("L---Y %d",y);
      return y;
    }
    y+= type;
    while (pikachuObjectList.at(pMinY.x + y*width)->getValueVisible() != TAG_PIKACHU_VISIBLE &&
           pikachuObjectList.at(pMaxY.x + y*width)->getValueVisible() != TAG_PIKACHU_VISIBLE) {
      if (countNumberObjectBetween(Point(pMinY.x,y),Point(pMaxY.x,y)) == 0) {
        if(delegate && isType == true) {
          delegate->listerDrawerULAI(U_SHAPE,Y_AXIS,type,y,p1,p2);
        }
        CCLOG("U---Y %d",y);
        return y;
      }
      if(y >=1 && y <= height -2) {
        y += type;
      }
    }
  }
  return -1;
}

void SuggestBot::setDelegate(DelegateAutoDrawer* mDelegate) {
  this->delegate = mDelegate;
}

void SuggestBot::setType(bool isType) {
  this->isType = isType;
}

MyLine SuggestBot::checkTwoPointGenType(Point p1, Point p2) {
  // check line with x
  if (p1.x == p2.x) {
    if (checkLineY(p1.y, p2.y, p1.x)) {
      return  MyLine(p1, p2);
    }
  }
  // check line with y
  if (p1.y == p2.y) {
    if (checkLineX(p1.x, p2.x, p1.y)) {
      return  MyLine(p1, p2);
    }
  }
  
  int t = -1; // t is column find
  
  //  check in rectangle with x
  if ((t = checkRectX(p1, p2)) != -1) {
    return  MyLine( Point(p1.x, t),  Point(p2.x, t));
  }
  
  // check in rectangle with y
  if ((t = checkRectY(p1, p2)) != -1) {
    return  MyLine( Point(t, p1.y),  Point(t, p2.y));
  }
  // check more right
  if ((t = checkMoreLineX(p1, p2, 1)) != -1) {
    return  MyLine(Point(t, p1.y),  Point(t, p2.y));
  }
  // check more left
  if ((t = checkMoreLineX(p1, p2, -1)) != -1) {
    return  MyLine( Point(t,p1.y),  Point(t, p2.y));
  }
  //  check more Up
  if ((t = checkMoreLineY(p1, p2, 1)) != -1) {
    return  MyLine( Point(p1.x, t),  Point(p2.x, t));
  }
  // check more Down
  if ((t = checkMoreLineY(p1, p2, -1)) != -1) {
    return  MyLine( Point(p1.x, t),  Point(p2.x, t));
  }
  return MyLine(Point::ZERO, Point::ZERO);
}



