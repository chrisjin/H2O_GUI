#include "h2o_animation.h"
using namespace ColdWater;


Animation::Animation()
{
}

void Animation::initTimer()
{
    m_Timer.setTimer(this,&Animation::playFrame,m_Speed);
}

void Animation::start()
{

    m_Timer.start();
}

void Animation::stop()
{
    m_Timer.stop();
}
