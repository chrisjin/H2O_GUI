#ifndef H2O_DRAGTILE_H
#define H2O_DRAGTILE_H
#include"h2o_widget.h"
namespace ColdWater
{
    class DragTile:public Widget
    {
    public:
        Point2D m_Offset;
        bool m_IsBegin;
        DEFCSTRCTOR(DragTile,Widget)
        {
            m_IsBegin=0;
        }
        virtual void LBUpEvent(Point2D LocalPos);
        virtual void LBDownEvent(Point2D LocalPos);
        virtual void updateBitmap(Buffer2D<RGBPixel>& bfBitmap);
        virtual void MouseMoveEvent(Point2D LocalPos);
        virtual void MouseLeaveEvent(Tile* leavefor);
        virtual void TimerEvent(int id);
    };
}
#endif // H2O_DRAGTILE_H
