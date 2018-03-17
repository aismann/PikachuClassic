//
//  GoogleReward.cpp
//  PikachuOnetClassic
//
//  Created by HoangNC on 7/15/17.
//
//

#include "GoogleReward.h"
#include "AdmodAndroid.h"
void GoogleReward::unlockachievementGoogle(int levelUnlock){
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    AdmodAndroid::unlockAchiment(levelUnlock);
#endif
}
