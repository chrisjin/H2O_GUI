#ifndef H2O_BUTTON_H
#define H2O_BUTTON_H
#include"H2O_Widget.h"
#include"h2o_imagefile.h"
#include"h2o_typewriter.h"
namespace ColdWater
{
    class Button:public Widget
    {
    private:
        DEFFLAG(Press)
        DEFFLAG(Hover)
        Buffer2D<RGBPixel> m_PressImg;
        Buffer2D<RGBPixel> m_ReleaseImg;
        Buffer2D<RGBPixel> m_HoverImg;
        TypeWriter m_Writer;
    public:
        Button(Point2D ori,Size2D size);
        Button(Point2D ori,int lengthlevel);
        void createWriter();
        void createDefaultSkin();
        void createWar3Skin();

        void setText(const char* con);
        void setText(const wchar_t* con);
        virtual void LBUpEvent(Point2D LocalPos);
        virtual void LBDownEvent(Point2D LocalPos);
        virtual void updateBitmap(Buffer2D<RGBPixel>& bfBitmap);
        virtual void MouseLeaveEvent(Tile* leavefor);
        virtual void MouseHoverEvent(Point2D LocalPos);
        virtual void TimerEvent(int id);
    public:
        DEFSIGNAL(s_clicked)
    };
}

#endif // H2O_BUTTON_H
