//
//  AlgorithmRandom.cpp
//  PikachuConnect
//
//  Created by NguyenHoang on 8/28/16.
//
//

#include "AlgorithmRandom.h"
#include "GameDefine.h"

void swap (int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
// A function to generate a random permutation of arr[]
void randomize (std::vector<int> & arr, int n )
{
    srand( (unsigned)time(NULL) );
    
    for (int i = n-1; i > 0; i--)
    {
        int j = rand() % (i+1);
        swap(&arr[i], &arr[j]);
    }
}

static AlgorithmRandom* object = nullptr;
AlgorithmRandom::AlgorithmRandom()
{
    
}
AlgorithmRandom::~AlgorithmRandom()
{
    
}
AlgorithmRandom* AlgorithmRandom::getInstance()
{
    if(object == nullptr)
    {
        object = new AlgorithmRandom();
    }
    return object;
}
void AlgorithmRandom::createVectorIndexPikachu36(int width, int hight)
{
    if(!arrayIndex.empty())
    {
        arrayIndex.clear();
    }
    for (int i = 1; i <= hight; i ++ )
    {
        for (int j = 1 ; j <= width ; j++)
        {
            arrayIndex.push_back(j + (i-1)*width);
        }
    }
}
void AlgorithmRandom::setArrayIndex(const std::vector<int> &array)
{
    this->arrayIndex = array;
}
void AlgorithmRandom::setMaxtrixWithHight(int width, int hight)
{
    this->withMaxtrix = width;
    this->hightMaxtrix = hight;
}

void AlgorithmRandom::createVectorRamdomIndex()
{
    srand( (unsigned)time(NULL) );
    if(!arrayLookingFor.empty())
    {
        arrayLookingFor.clear();
    }
    if (withMaxtrix*hightMaxtrix/2 <= arrayIndex.size())
    {
        arrayIndex = arrayIndex;
    }
    else
    {
        createTempVector();
        size_t sizeIndex = arrayIndex.size();
        for (int i = 0 ; i < SUM_ARRAY_RESOURE - sizeIndex; i++)
        {
            arrayIndex.push_back(randomIndexFromVector(temp));
        }
        
    }
    for (int i = 0 ; i < withMaxtrix*hightMaxtrix/2; i++)
    {
        int tempIndex = randomIndexFromVector(arrayIndex);
        arrayLookingFor.push_back(tempIndex);
    }
    cloneMyVector();
    
}


void AlgorithmRandom::createTempVector()
{
    if(!temp.empty())
    {
        temp.clear();
    }
    
    srand( (unsigned)time(NULL) );
    int sumNeedIndex = SUM_ARRAY_RESOURE - (int)arrayIndex.size();
    for (int i = 0; i < sumNeedIndex; i++)
    {
        
        int k = rand() % (SUM_ARRAY_RESOURE-1);
        if (k < arrayIndex.size()-1)
        {
            temp.push_back(arrayIndex.at(k));
        }
        else
        {
            temp.push_back(k);
        }
    }
    
}
void AlgorithmRandom::cloneMyVector()
{
    std::vector<int> temp;
    if(!temp.empty())
    {
        temp.clear();
    }
    for (int i = 0 ; i < withMaxtrix*hightMaxtrix/2; i++)
    {
        temp.push_back(arrayLookingFor.at(i));
        temp.push_back(arrayLookingFor.at(i));
    }
    arrayLookingFor = temp;
    randomize(arrayLookingFor, (int)arrayLookingFor.size());
}
int AlgorithmRandom::randomIndexFromVector(std::vector<int> &array)
{
    srand( (unsigned)time(NULL) );
    int result = 0 ;
    if(!array.empty())
    {
        int j = rand() % array.size();
        result = array.at(j);
        int temp =  array.at(j);
        array.at(j) = array.at(array.size()-1);
        array.at(array.size()-1) = temp;
        array.pop_back();
    }
    return result;
}
std::vector<int> AlgorithmRandom::getVectorLookingFor()
{
    return arrayLookingFor;
}
void AlgorithmRandom::printVectorLookingFor()
{
    for (int k = 0; k < arrayLookingFor.size(); k++)
    {
        CCLOG("%d",arrayLookingFor.at(k));
    }
}
