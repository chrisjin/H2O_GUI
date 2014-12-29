#ifndef H2O_GIFPLAYER_H
#define H2O_GIFPLAYER_H
#include"h2o_widget.h"
#include"h2o_timer.h"
#include"FreeImage/FreeImage.h"
#include"h2o_animation.h"
namespace ColdWater
{
    enum SHOWTYPE
    {
        ST_STRETCH,
        ST_FIXED,
        ST_FULL
    };

    class GIFPlayer:public Animation
    {
        vector<Buffer2D<RGBPixel>*> m_FrameList;
        int m_FrameNum;
        int m_CurrentFrame;
        Timer m_Timer;
        SHOWTYPE m_ShowType;
    public:


        GIFPlayer(Point2D pos,Size2D size,SHOWTYPE showtype=ST_STRETCH):Animation(pos,size)
        {
            init();
            m_ShowType=showtype;
        }
        GIFPlayer()
        {
            init();
        }
        GIFPlayer(const Point2D pos,SHOWTYPE showtype=ST_FULL)
        {
            initFlag();
            init();
            m_ShowType=showtype;
            setOri(pos);
        }
        void init();
        void playFrame();
        void updateBitmap(Buffer2D<RGBPixel> &bfBitmap);
        void TimerEvent(int id);
        void CreateEvent();
        bool loadGIF(const char* filename,int xx=0,int yy=0);
		void clear();


    };
}

#endif // H2O_GIFPLAYER_H
