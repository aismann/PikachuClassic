//
//  AlgorithmRandom.h
//  PikachuConnect
//
//  Created by NguyenHoang on 8/28/16.
//
//

#ifndef AlgorithmRandom_h
#define AlgorithmRandom_h

#include <stdio.h>
#include "cocos2d.h"

class AlgorithmRandom
{
private:
    std::vector<int> arrayIndex;
    std::vector<int> temp;
    int withMaxtrix;
    int hightMaxtrix;
    std::vector<int> arrayLookingFor;
public:
    AlgorithmRandom();
    virtual ~AlgorithmRandom();
    static AlgorithmRandom* getInstance();
    void setMaxtrixWithHight(int width, int hight);
    void createVectorIndexPikachu36(int width, int hight);
    void cloneMyVector();
    void setArrayIndex(const std::vector<int> &array);
    void createVectorRamdomIndex();
   int randomIndexFromVector(std::vector<int> &array);
    std::vector<int> getVectorLookingFor();
    void printVectorLookingFor();
   void createTempVector();
};

#endif /* AlgorithmRandom_h */
