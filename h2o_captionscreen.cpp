#include "h2o_captionscreen.h"
using namespace ColdWater;
CaptionScreen::CaptionScreen()
{
}

void CaptionScreen::playFrame()
{
    static int kk=255;
    if(kk<0)
    {
        stop();
        setHide();
        unsetMouseTrigger();
        return;
    }
    getBitmap().fill(RGBPixel(kk,kk,kk));
    kk--;
}
