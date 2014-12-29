#ifndef H2O_ANIMATION_H
#define H2O_ANIMATION_H
#include"h2o_widget.h"
#include"h2o_timer.h"
namespace ColdWater
{
    class Widget;
    class Animation:public Widget
    {
        Timer m_Timer;
        short m_Speed;
    public:
        DEFCSTRCTOR(Animation,Widget)
        {

        }
        Animation();
        virtual void playFrame(){}
        void initTimer();
        void start();
        void stop();
        void setSpeed(short speed)
        {
            m_Speed=speed;
        }
    };
}
#endif // H2O_ANIMATION_H
