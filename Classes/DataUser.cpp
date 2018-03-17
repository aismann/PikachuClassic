//
//  DataUser.cpp
//  PikachuConnection
//
//  Created by Hoang Nguyen on 11/19/16.
//
//

#include "DataUser.h"
/*Data User*/
DataUser::DataUser()
{
    
}
DataUser::~DataUser()
{
    
}

void DataUser::setArrayData(std::vector<int> arrayData)
{
    this->arrayData = arrayData;
}


void DataUser::createWithBasicInfor(int idUser,std::string nameUser, int score)
{
    this->idUser = idUser;
    this->score = score;
    this->nameUser =   nameUser;
}
