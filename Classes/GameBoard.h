//
//  GameBoard.h
//  PikachuConnect
//
//  Created by HarryNguyen on 8/18/16.
//
//

#ifndef GameBoard_h
#define GameBoard_h

#include <stdio.h>
#include <iostream>
#include "cocos2d.h"
#include "PikachuObject.h"
#include "SuggestBot.h"
USING_NS_CC;

class GameBoard: public Layer {
public:
  int widthGameBoard;
  int heightGameBoard;
  Vec2 positionGameBoard;
  Scene* gameScene;
  std::vector<PikachuObject*> pikachus;
  std::vector<int> arrayTypePikachus();
  std::vector<int> indexPikachus;
  int typeDrop;
  SuggestBot* suggestBot;
  bool isPausing;
  bool isStatus;
public:
  GameBoard(int width, int height);
  virtual ~GameBoard();
  void createGameBoard();
  void initWithScene(Node* gameScene);

  Vec2 convertPosGameBoard(const Vec2& pos);
  Vec2 getPositionScene(const Vec2& pos);
  PikachuObject* getAtPosGameBoard(const Vec2& pos);
  void setPositionGameBoard(const Vec2& pos);
  
  std::vector<PikachuObject*> getArrayValuePikachu();
  
  void setHiddenObjectValue(const Vec2& pos1, const Vec2& pos2);
  void dropPikachu(int dropType);
  
  void update(float dt);
  void setGameBoardTypeDrop(int typeDrop);
  void swapTwoObject(const Vec2& pos1, const Vec2& pos2);
  void setVectorTypePikachu(std::vector<int> array);
  
  bool isNeedToShuffle();
  void setSuggestBotForGame(SuggestBot* suggestBot);
  void startCheckAuto();
  bool checkCanConnectWithVector(const Vec2& pos, const Vec2 &pos2);
  
  void revertToNormalObjectAfterNotPair(const Vec2& pos);
  bool checkStatusGameBoard();
  
  void pauseGame();
  void setBameBoardPlay();
  void refreshGameBoard();
  void printPikachuType();
};

#endif /* GameBoard_h */
