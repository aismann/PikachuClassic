//
//  AdmodAndroid.h

#include <string>
#include "cocos2d.h"
using namespace cocos2d;

class AdmodAndroid{
public:
  static void showBanner();
  static void hideBanner();
  static void showFullAds();
  static void unlockAchievement(int levelUnlock);
  static void showAchievement();
  static bool getStatusShowFull();
};


