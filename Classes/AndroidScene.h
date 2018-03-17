
//  Created by Nguyễn Chí Hoàng on 7/3/15.
//
//


#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;
class AndroidScene: public Layer{
    public:
        static Scene* CreateScene();
        virtual bool init();
        CREATE_FUNC(AndroidScene);
       void update(float dt);
};
