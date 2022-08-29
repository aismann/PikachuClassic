//
//  GoogleReward.cpp
//  PikachuOnetClassic
//
//  Created by Harry Nguyen on 7/15/17.
//
//

#include "GoogleReward.h"
#include "AdmodAndroid.h"
void GoogleReward::unlockAchievement(int levelUnlock){
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
  AdmodAndroid::unlockAchievement(levelUnlock);
#endif
}
