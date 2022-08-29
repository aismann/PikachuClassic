//
//  GameBoard.cpp
//  PikachuConnect
//
//  Created by HarryNguyen on 8/18/16.
//
//


#include "GameBoard.h"
#include "GameDefine.h"
#include "RandomBot.h"

GameBoard::GameBoard(int width, int height) {
  isStatus = false;
  isPausing = false;
  widthGameBoard = width;
  heightGameBoard = height;
  if(!pikachus.empty()) {
    pikachus.clear();
  }
}

GameBoard::~GameBoard() {}

void GameBoard::setPositionGameBoard(const Vec2& pos) {
  positionGameBoard = pos;
}


std::vector<PikachuObject*> GameBoard::getArrayValuePikachu() {
  return pikachus;
}

void GameBoard::setVectorTypePikachu(std::vector<int> array) {
  this->indexPikachus = array;
}

Vec2 GameBoard::convertPosGameBoard(const Vec2& pos) {
  Vec2 vec2Result;
  Vec2 posConvert = Vec2(this->convertToWorldSpace(this->getPosition()).x + SHAPE_WIDTH /2,
                         this->convertToWorldSpace(this->getPosition()).y + SHAPE_HEIGHT/2);
  if(pos.x < posConvert.x ||
     pos.y < posConvert.y ||
     pos.x > posConvert.x + (widthGameBoard) *SHAPE_WIDTH ||
     pos.y > posConvert.y + (heightGameBoard)* SHAPE_HEIGHT) {
    vec2Result = Vec2(-1, -1);
  } else {
    int realWidth = pos.x - posConvert.x;
    int realHeight = pos.y - posConvert.y;
    int cellPosX = realWidth/SHAPE_WIDTH;
    int cellPosY = realHeight/SHAPE_HEIGHT;
    vec2Result =  Vec2(cellPosX, cellPosY);
  }
  return vec2Result;
}

Vec2 GameBoard::getPositionScene(const Vec2& pos) {
  if(pos.x < 0 ||
     pos.y < 0 ||
     pos.x > widthGameBoard-1 ||
     pos.y > heightGameBoard-1) {
    return Vec2(-1,-1);
  } else {
    float pointX = pos.x * SHAPE_WIDTH/2 + this->getPositionX() + SHAPE_WIDTH/2;
    float pointY = pos.y * SHAPE_HEIGHT/2 + this->getPositionY() + SHAPE_HEIGHT/2;
    return Vec2(pointX,pointY);
  }
}

void GameBoard::createGameBoard() {
  for (int i = 0; i < heightGameBoard; i++) {
    for (int j = 0; j < widthGameBoard; j++) {
      PikachuObject* object = new PikachuObject();
      int visibleTag = 0;
      int type;
      if(i == 0 ||
         i == heightGameBoard-1 ||
         j == 0 ||
         j ==  widthGameBoard-1) {
        type = 0;
        visibleTag = TAG_PIKACHU_HIDDEN;
      } else {
        visibleTag = TAG_PIKACHU_VISIBLE;
        type = RandomBot::getInstance()->randomIndexFromVector(indexPikachus)-1;
      }
      if (type <= 0) {
        type = 0;
      }
      if(type >= 35){
        type = 35;
      }
      object->setTypeObject(type);
      object->setValueVisible(visibleTag);
      object->setMatrixPosition(Vec2(j, i));
      object->setPosition(this->getPositionScene(Vec2(j, i)));
      object->createUIObject();
      int tagObject = (j + (heightGameBoard - i)* widthGameBoard);
      object->setTagObject(tagObject);
      gameScene->addChild(object, tagObject);
      pikachus.push_back(object);
    }
  }
}

PikachuObject* GameBoard::getAtPosGameBoard(const Vec2& pos) {
  return pikachus.at(pos.x + pos.y*widthGameBoard);;
}

void GameBoard::initWithScene(Node* gameScene) {
  if(this->gameScene != NULL) {
    this->gameScene = (Scene*)gameScene;
  }
}

void GameBoard::setHiddenObjectValue(const Vec2& pos1, const Vec2& pos2) {
  pikachus.at(pos1.x + pos1.y* widthGameBoard)->setValueVisible(TAG_PIKACHU_HIDDEN);
  pikachus.at(pos2.x + pos2.y* widthGameBoard)->setValueVisible(TAG_PIKACHU_HIDDEN);
}

void GameBoard::dropPikachu(int dropType) {
  PikachuObject* pikachu = nullptr;
  if(dropType == DROP_LEFT) {
    for (int col = 1; col <= heightGameBoard-2 ; col++) {
      int rightCount = 0;
      for (int row = 1 ; row <= widthGameBoard-2; row++) {
        pikachu = pikachus.at(row + col*widthGameBoard);
        if(pikachu->getValueVisible() == TAG_PIKACHU_HIDDEN) {
          rightCount ++;
        } else {
          if(rightCount > 0) {
            int newRow = row - rightCount;
            swapTwoObject(Vec2(newRow, col), Vec2(row,col));
          }
        }
      }
    }
  }
  
  if(dropType == DROP_RIGHT) {
    for (int col = 1; col <= heightGameBoard-2 ; col++) {
      int rightCount = 0;
      for (int row = widthGameBoard - 2 ; row > 0; row--) {
        pikachu = pikachus.at(row + col*widthGameBoard);
        if(pikachu->getValueVisible() == TAG_PIKACHU_HIDDEN) {
          rightCount ++;
        }
        else {
          if(rightCount > 0) {
            int newRow = row + rightCount;
            swapTwoObject(Vec2(newRow, col), Vec2(row,col));
          }
        }
      }
    }
    
  }
  if(dropType == DROP_UP) {
    for (int row = 1 ; row <= widthGameBoard-2 ; row ++ ) {
      int upCount = 0;
      for (int col = heightGameBoard - 2; col > 0 ; col--) {
        pikachu = pikachus.at( row + col*widthGameBoard);
        if(pikachu->getValueVisible() == TAG_PIKACHU_HIDDEN) {
          upCount++;
        } else {
          if(upCount > 0) {
            int newHeight = col + upCount;
            swapTwoObject(Vec2(row, newHeight), Vec2(row, col));
          }
        }
      }
    }
  }
  if(dropType == DROP_DOWN) {
    for (int row = 1 ; row <= widthGameBoard-2; row++) {
      int downCount = 0;
      for (int col = 1; col <= heightGameBoard-2; col++) {
        pikachu = pikachus.at(row + col*widthGameBoard);
        if (pikachu->getValueVisible() == TAG_PIKACHU_HIDDEN) {
          downCount ++;
        }
        else {
          if(downCount > 0) {
            int newHeight = col - downCount;
            swapTwoObject(Vec2(row, newHeight), Vec2(row, col));
          }
        }
      }
    }
  }
}

void swapTag(int &a, int &b) {
  int temp = a;
  a = b ;
  b = temp;
}

void GameBoard::swapTwoObject(const Vec2& pos1, const Vec2& pos2) {
  PikachuObject* object1 = this->getAtPosGameBoard(pos1);
  PikachuObject* object2 = this->getAtPosGameBoard(pos2);
  
  int a = object1->getTagObject();
  int b = object2->getTagObject();
  swapTag(a, b);
  if(object1 && object2) {
    object1->updateNewPosition(getPositionScene(Vec2(pos2.x, pos2.y)));
    object1->setMatrixPosition(pos2);
    object1->setValueVisible(TAG_PIKACHU_HIDDEN);
    object1->setTagObject(a);
    object1->setLocalZOrder(a);
    
    object2->updateNewPosition(getPositionScene(Vec2(pos1.x, pos1.y)));
    object2->setMatrixPosition(pos1);
    object2->setValueVisible(TAG_PIKACHU_VISIBLE);
    object2->setTagObject(b);
    object2->setLocalZOrder(b);
    
    pikachus.at(pos1.x + pos1.y*widthGameBoard) = object2;
    pikachus.at(pos2.x + pos2.y*widthGameBoard) = object1;
  }
}

/*auto change type when not connection */
bool GameBoard::isNeedToShuffle() {
  std::vector<PikachuObject*> arraysPikachuVisiable;
  std::vector<PikachuObject*> arraySampleValue;
  if(!arraysPikachuVisiable.empty()) {
    arraysPikachuVisiable.clear();
  }
  
  /*get all object have tagvisibale != hiden*/
  for (int i = 0; i < pikachus.size(); i++) {
    if(pikachus.at(i)->getValueVisible() == TAG_PIKACHU_VISIBLE) {
      arraysPikachuVisiable.push_back(pikachus.at(i));
    }
  }
  std::vector<PikachuObject*> arraysPikachuVisiable_Clone = arraysPikachuVisiable;
  
  /*get array object same type */
  for (int j = 0; j < arraysPikachuVisiable.size(); j ++) {
    int type1 = arraysPikachuVisiable.at(j)->getTypeObject();
    for (int  k = 0; k < arraysPikachuVisiable_Clone.size(); k++) {
      int type2 = arraysPikachuVisiable_Clone.at(k)->getTypeObject();
      if(type1 == type2) {
        arraySampleValue.push_back(arraysPikachuVisiable_Clone.at(k));
        arraysPikachuVisiable_Clone.erase(arraysPikachuVisiable_Clone.begin() + k);
        k--;
      }
    }
  }
  
  std::vector<PikachuObject*> arraySampleValue_Clone = arraySampleValue;
  std::vector<Vec2> SubPositionArraySamType;
  
  /*check exits line of objective same type*/
  bool isCheckAutoGen = false;
  bool isLastArray = false;
  for (int  h = 0 ; h < arraySampleValue.size();) {
    
    int value = arraySampleValue.at(h)->getTypeObject();
    int count = 0;
    for (int m = h; h < arraySampleValue_Clone.size(); m++) {
      if (m >= arraySampleValue_Clone.size()) {
        if(!SubPositionArraySamType.empty()) {
          /*check at here*/
          int countLast = 0;
          for (int delta = 0; delta < SubPositionArraySamType.size()-1; delta++) {
            countLast++;
            if(checkCanConnectWithVector(SubPositionArraySamType.at(delta), SubPositionArraySamType.at(delta+1))) {
              isCheckAutoGen = true;
              break;
            }
          }
          if(countLast == SubPositionArraySamType.size() - 1 && !isCheckAutoGen) {
            isLastArray = true;
            SubPositionArraySamType.clear();
            break;
          }
          if(isCheckAutoGen == true) {
            SubPositionArraySamType.clear();
            break;
          }
        }
      } else {
        if(arraySampleValue_Clone.at(m)->getTypeObject() != value) {
          
          h = h + count;
          //  CCLOG("index of h %d \t Sum object %d", h, count);
          if (!SubPositionArraySamType.empty()) {
            /*check at here*/
            int xCount = 0 ;
            for (int  x = 0 ; x < SubPositionArraySamType.size()-1; x++) {
              xCount ++;
              if(checkCanConnectWithVector(SubPositionArraySamType.at(x), SubPositionArraySamType.at(x+1))) {
                isCheckAutoGen = true;
                break;
              }
            }
            
            if(xCount <= SubPositionArraySamType.size() ||
               isCheckAutoGen == true) {
              SubPositionArraySamType.clear();
              break;
            }
          }
          break;
        } else {
          count ++;
          SubPositionArraySamType.push_back(arraySampleValue_Clone.at(m)->getMatrixPosition());
        }
      }
    }
    
    if(isCheckAutoGen == true || isLastArray == true) {
      break;
    }
  }
  if(isCheckAutoGen == false) {
    /*create array type */
    std::vector<int> targetTypeArray;
    if(!targetTypeArray.empty()) {
      targetTypeArray.clear();
    }
    for (int i = 0 ; i < arraySampleValue.size(); i++) {
      int type = arraySampleValue.at(i)->getTypeObject();
      targetTypeArray.push_back(type);
    }
    
    /*gen type at here*/
    for (int i = 0 ; i < arraySampleValue.size(); i ++) {
      PikachuObject* objective = arraySampleValue.at(i);
      int newtype =RandomBot::getInstance()->randomIndexFromVector(targetTypeArray);
      
      for (int j = 0; j < pikachus.size(); j++) {
        PikachuObject* objective2 = pikachus.at(j);
        if(objective2->getMatrixPosition() == objective->getMatrixPosition()) {
          objective2->setTypeObject(newtype);
          objective2->updateUI(newtype);
          pikachus.at(j) = objective2;
        }
      }
    }
  }
  return isCheckAutoGen;
}

bool GameBoard::checkCanConnectWithVector(const Vec2& pos, const Vec2 &pos2) {
  MyLine line = suggestBot->checkTwoPointGenType(pos, pos2);
  if(!line.checZeroLine()) {
    return  true;
  }
  return false;
}

void GameBoard::startCheckAuto() {
  int temp = 0;
  for (int i = 0; i < pikachus.size(); i++) {
    if(pikachus.at(i)->getValueVisible() == TAG_PIKACHU_VISIBLE) {
      temp ++;
    }
  }
  if(temp <= 60) {
    isNeedToShuffle();
  }
}

void GameBoard::revertToNormalObjectAfterNotPair(const Vec2& pos) {
  for (int i = 0; i < pikachus.size(); i++) {
    PikachuObject* pikaChuobject = pikachus.at(i);
    if(pikaChuobject->getMatrixPosition() != pos) {
      pikaChuobject->backToNormalObject();
    }
  }
}

void GameBoard::setSuggestBotForGame(SuggestBot* suggestBot) {
  this->suggestBot = suggestBot;
}

void GameBoard::update(float dt) {
  if(!isPausing) {
    this->startCheckAuto();
    this->checkStatusGameBoard();
  }
}

void GameBoard::setGameBoardTypeDrop(int typeDrop) {
  this->typeDrop = typeDrop;
}

void GameBoard::pauseGame() {
  isPausing  = true;
  for (int i = 0; i < widthGameBoard; i ++) {
    for (int j = 0; j < heightGameBoard; j++) {
      PikachuObject* pikachuObject = pikachus.at(i + j*widthGameBoard);
      pikachuObject->objectWhenPause();
    }
  }
}

void GameBoard::setBameBoardPlay() {
  isPausing  = false;
  for (int i = 0; i < widthGameBoard; i ++) {
    for (int j = 0; j < heightGameBoard; j++) {
      PikachuObject* pikachuObject = pikachus.at(i + j*widthGameBoard);
      pikachuObject->objectWhenPlay();
    }
  }
}

void GameBoard::refreshGameBoard(){
  std::vector<int> arrayTemp;
  for (int i = 0 ; i < pikachus.size(); i++) {
    if(pikachus.at(i)->getValueVisible() == TAG_PIKACHU_VISIBLE){
      arrayTemp.push_back(pikachus.at(i)->getTypeObject());
    }
  }
  
  /*gen type at here*/
  for (int i = 0 ; i < pikachus.size(); i ++) {
    if(pikachus.at(i)->getValueVisible() == TAG_PIKACHU_VISIBLE){
      PikachuObject* objective = pikachus.at(i);
      int newtype =RandomBot::getInstance()->randomIndexFromVector(arrayTemp) - 1;
      if(newtype <= 0){
        newtype = 0;
      }
      for (int j = 0; j < pikachus.size(); j++) {
        if(pikachus.at(i)->getValueVisible() == TAG_PIKACHU_VISIBLE){
          PikachuObject* objective2 = pikachus.at(j);
          if(objective2->getMatrixPosition() == objective->getMatrixPosition()) {
            objective2->setTypeObject(newtype);
            objective2->updateUI(newtype);
            pikachus.at(j) = objective2;
          }
        }
      }
    }
  }
}


bool GameBoard::checkStatusGameBoard() {
  bool isWin = true;
  for (int i = 0 ; i < pikachus.size(); i++) {
    if(pikachus.at(i)->getValueVisible() != TAG_PIKACHU_HIDDEN) {
      isWin = false;
    }
  }
  isStatus = isWin;
  return isWin;
}

std::vector<int> GameBoard::arrayTypePikachus() {
  std::vector<int> arrayType;
  for (int i = 0 ; i < pikachus.size(); i++) {
    if(pikachus.at(i)->getValueVisible() != TAG_PIKACHU_HIDDEN) {
      arrayType.push_back(pikachus.at(i)->getTypeObject());
    }
  }
  return arrayType;
}

void GameBoard::printPikachuType() {
  std::cout<<"\n"<<"\n";
  for (int i = heightGameBoard-1 ; i >= 0; i--) {
    for (int j = 0; j < widthGameBoard; j++) {
      if(i == 0 ||
         i == heightGameBoard -1 ||
         j == 0 ||
         j == widthGameBoard-1) {
        std::cout<<"\t";
      } else {
        std::cout<< pikachus.at(j + i* widthGameBoard)->getTypeObject();
        
      }
    }
    std::cout<<"\n";
  }
  std::cout<<"\n"<<"\n";
}

