//
//  DataUser.hpp
//  PikachuConnection
//
//  Created by Hoang Nguyen on 11/19/16.
//
//

#ifndef DataUser_hpp
#define DataUser_hpp
#include "cocos2d.h"
using namespace cocos2d;
class DataUser {
public:
  int idUser;
  std::string nameUser;
  std::string email;
  std::string urlImage;
  Vec2 locationUser;
  int score;
  std::vector<int> arrayData;
public:
  
  DataUser();
  void setArrayData(std::vector<int> arrayData);
  virtual ~DataUser();
  void createWithBasicInfo(int idUser,std::string nameUser, int score);
};
#endif /* DataUser_hpp */
