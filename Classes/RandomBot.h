//
//  RandomBot.h
//  PikachuConnect
//
//  Created by HarryNguyen on 8/28/16.
//
//

#ifndef RandomBot_h
#define RandomBot_h

#include <stdio.h>
#include "cocos2d.h"

class RandomBot {
private:
  int withMatrix;
  int heightMatrix;
  std::vector<int> arrayIndex;
  std::vector<int> temp;
  std::vector<int> expectedVector;
public:
  RandomBot();
  virtual ~RandomBot();
  static RandomBot* getInstance();
  void setWithHeightMatrix(int width, int hight);
  void createVectorIndexPikachu36(int width, int hight);
  void cloneMyVector();
  void setArrayIndex(const std::vector<int> &array);
  void createVectorRandomIndex();
  int randomIndexFromVector(std::vector<int> &array);
  std::vector<int> getExpectedVector();
  void printVectorLookingFor();
  void createTempVector();
};

#endif /* RandomBot_h */
