//
//  GameDefine.h
//  PikachuConnect
//
//  Created by NguyenHoang on 8/18/16.
//
//

#ifndef GameDefine_h
#define GameDefine_h

enum STATUS_LOADING {
    IDLE_PROGRESS = 1,
    PAUSE_PROGRESS = 2,
    ADDTIME_PROGRESS = 3,
    DELETIME_PROGRESS = 4,
    BUYTIME_PROGRESS = 5,
    END_GAME = 6
};

enum{
    TAG_BTN_ADDTIME = 200,
    TAG_BTN_REFRESH = 201,
    TAG_BTN_PAUSE = 202,
    TAG_BTN_BACK =203,
    TAG_BTN_SUGGEST =204
};
typedef enum{
    DROP_LEFT = 0,
    DROP_RIGHT = 1,
    DROP_UP = 2,
    DROP_DOWN = 3,
    DROP_IDLE = 4
}STATUS_DROP;


typedef enum
{
    LINE  = 0,
    Z_SHAPE = 1,
    L_SHAPE = 2,
    U_SHAPE = 3
}TypeEatPikachu;

#define SUM_ARRAY_RESOURE 36



#define GAME_XXX "game2"
#define X_AXIS 1
#define Y_AXIS 2

#define SHAPE_WIDTH 160
#define SHAPE_HEIGHT 200

//
//#define DELTA_X 17
//#define DELTA_Y 40  

#define TAG_PIKACHU_HIDDEN 0
#define TAG_PIKACHU_VISIABLE 1

#define BUGGET_MONEY_BUY "moneybuy"
#define COST_MONEY_BUY 10
#define REWARD_WIN_GAME_MONEY 3
#define REWARD_EAT_EASY 1
#define REWARD_EAT_HARD 2
#define DEFAULT_MONEY_GAME 20

#endif /* GameDefine_h */
