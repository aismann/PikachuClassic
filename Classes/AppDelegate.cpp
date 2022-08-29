#include "AppDelegate.h"
#include "HomeScene.h"
#include "AndroidScene.h"
#include "SimpleAudioEngine.h"
#include "GameDefine.h"
USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(2208, 1242);

AppDelegate::AppDelegate() {}

AppDelegate::~AppDelegate() {}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs() {
  //set OpenGL context attributions,now can only set six attributions:
  //red,green,blue,alpha,depth,stencil
  GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
  
  GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages,
// don't modify or remove this function
static int register_all_packages() {
  return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
  // initialize director
  auto director = Director::getInstance();
  auto glview = director->getOpenGLView();
  if(!glview) {
    glview = GLViewImpl::create("PikachuSpace");
    director->setOpenGLView(glview);
  }
  
  // turn on display FPS
  director->setDisplayStats(false);
  
  // set FPS. the default value is 1.0/60 if you don't call this
  director->setAnimationInterval(1.0 / 60);
  
  // Set the design resolution
  glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::EXACT_FIT);
  
  register_all_packages();
  /*Add search path*/
  FileUtils::getInstance()->addSearchPath("fonts");
  FileUtils::getInstance()->addSearchPath("imagehome");
  FileUtils::getInstance()->addSearchPath("imagegameScene");
  FileUtils::getInstance()->addSearchPath("popup");
  FileUtils::getInstance()->addSearchPath("sound");
  FileUtils::getInstance()->addSearchPath("icon");
  SpriteFrameCache::getInstance()->addSpriteFramesWithFile("PikachuImage.plist");
  
  
  if(UserDefault::getInstance()->getBoolForKey("sound", true)) {
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1.0f);
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(1.0f);
  } else {
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.0f);
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.0f);
  }
#if  CC_TARGET_PLATFORM == CC_PLATFORM_IOS
  auto scene = HomeScene::createHomeScene();
  director->runWithScene(scene);
#endif
#if  CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
  auto scene = AndroidScene::CreateScene();
  director->runWithScene(scene);
#endif
  
  return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
  Director::getInstance()->stopAnimation();
  
  // if you use SimpleAudioEngine, it must be pause
  // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
  Director::getInstance()->startAnimation();
  
  // if you use SimpleAudioEngine, it must resume here
  // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
