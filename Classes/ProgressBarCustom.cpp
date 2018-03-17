//
//  ProgressBarCustom.cpp
//  PikachuConnect
//
//  Created by NguyenHoang on 8/18/16.


#include "ProgressBarCustom.h"
ProgressBarCustom::ProgressBarCustom()
{
}
ProgressBarCustom::~ProgressBarCustom()
{
    
}

void ProgressBarCustom::createUIProgressBar(const Vec2& pos)
{
    loadingbar = ui::LoadingBar::create("loading.png");
    loadingbar->setAnchorPoint(Vec2(0.5,0.5));
    loadingbar->setPosition(pos);
    loadingbar->setPercent(value);
    loadingbar->setDirection(ui::LoadingBar::Direction::LEFT);
    this->setContentSize(loadingbar->getContentSize());
    this->addChild(loadingbar);

}
ProgressBarCustom* ProgressBarCustom::getInstaceProgress(int valueLoading, int status)
{
    ProgressBarCustom* object = new ProgressBarCustom();
    object->setvalue(valueLoading);
    object->setStatus(status);
    return object;
}
void ProgressBarCustom::setvalue(float value)
{
    this->value = value;
}
float ProgressBarCustom::getValue()
{
    return value;
}

void ProgressBarCustom::onEnter()
{
    Node::onEnter();
    this->scheduleUpdate();
    
}
void ProgressBarCustom::onExit()
{
    Node::onExit();
    this->unscheduleUpdate();
}
void ProgressBarCustom::update(float dt)
{
    
    if (loadingbar != NULL)
    {
        if (statusLoaing == IDLE_PROGRESS)
        {
            float value = loadingbar->getPercent();
            value  = value - percenUpdate;
            loadingbar->setPercent(value);
            if (value <= 0)
            {
                if (mDelegate)
                {
                    mDelegate->sendStatusGame()
                    ;
                }
                statusLoaing = END_GAME;
            }
        }
        if(statusLoaing == PAUSE_PROGRESS)
        {
            float value = loadingbar->getPercent();
            loadingbar->setPercent(value);
        }
        if (statusLoaing == ADDTIME_PROGRESS)
        {
            float value = loadingbar->getPercent();
            if(levelGame < 2 )
            {
                value  += 1.0f;
            }
            else if(levelGame >= 2 && levelGame < 5)
            {
                value += 1.4f;
            }
            else
            {
                value += 2.0f;
            }
            
            loadingbar->setPercent(value);
            statusLoaing = IDLE_PROGRESS;
        }
        if(statusLoaing == BUYTIME_PROGRESS){
            float value = loadingbar->getPercent();
            value += 30;
            loadingbar->setPercent(value);
            statusLoaing = IDLE_PROGRESS;
        }
    }
}
void ProgressBarCustom::setStatus(int status)
{
    this->statusLoaing = status;
}
void ProgressBarCustom::setDelegate(DelegateProgress* delegate)
{
    mDelegate = delegate;
}
void ProgressBarCustom::setLevelGame(int level)
{
    levelGame = level;
}
void ProgressBarCustom::setTimeUpdate(float dt)
{
    percenUpdate = dt;
}
void ProgressBarCustom::setLevel(int level)
{
    this->levelGame = level;
}
