#ifndef H2O_CAPTIONSCREEN_H
#define H2O_CAPTIONSCREEN_H
#include"h2o_animation.h"

namespace ColdWater
{
    class CaptionScreen:public Animation
    {

    public:
        CaptionScreen();
        DEFCSTRCTOR(CaptionScreen,Animation)
        {

            getBitmap().fill(RGBPixel(255,255,255));
        }
        virtual void playFrame();
    };
}
#endif // H2O_CAPTIONSCREEN_H
