//
//  GameBoard.h
//  PikachuConnect
//
//  Created by NguyenHoang on 8/18/16.
//
//

#ifndef GameBoard_h
#define GameBoard_h

#include <stdio.h>
#include <iostream>
#include "cocos2d.h"
#include "PikachuObject.h"
#include "AIRandomSuggest.h"
USING_NS_CC;


class GameBoard: public Layer
{
public:
    int widthGameboard;
    int heightGameboard;
    Scene* gameScene;
    std::vector<PikachuObject*> pikachus;
    Vec2 postionGameboad;
    std::vector<int> arrayindexPikachu;
    int typeDrop;
    AIRandomSuggest* AI;
    bool isPause;
    bool isStatus;
public:
    GameBoard(int width, int height);
    virtual ~GameBoard();

    
    Vec2 convertPosGameboard(const Vec2& pos);
    Vec2 getPositionScene(const Vec2& pos);
    void createGameboard();
    void initWithScene(Node* gamescene);
    PikachuObject* getAtPosGameboard(const Vec2& pos);
    void setPositionGameBoard(const Vec2& pos);
    
    std::vector<PikachuObject*> getArrayValuePikachus();
    
    void setValueHiddenObjectWithPosition(const Vec2& pos1, const Vec2& pos2);
    void dropPikachu(int statusDrop);
    
    void update(float dt);
    void setGameboardTypeDrop(int drop);
    
    void printPikachuType();
    
    void swapTwoObject(const Vec2& pos1, const Vec2& pos2);
    
    void setVectorTypePikachu(std::vector<int> array);
    
    bool checkAllPikachu();
    void setAIForGame(AIRandomSuggest* _AI);
    void startCheckAuto();
    bool checkCanConnectWithVector(const Vec2& pos, const Vec2 &pos2);
    
  
    void actionBackGameboard(const Vec2& pos);
    
    bool checkStatusGameboard();
    
    void gameboardWhenPause();
    void gameboardWhenPlay();
    void runAnimationWhenStartGame();
    void refreshGameBoard();
    
    std::vector<int> arrayTypePikachus();
};

#endif /* GameBoard_h */
