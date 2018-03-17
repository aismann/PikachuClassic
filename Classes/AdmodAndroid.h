//
//  AdmodAndroid.h

#include <string>
#include "cocos2d.h"
using namespace cocos2d;

class AdmodAndroid{
public:
    static void showBanner();
    static void hideBanner();
    static void showFullAdvertiment();
    static void unlockAchiment(int levelUnlock);
    static void showAchiment();
    static bool getStatusShowFull();
};


