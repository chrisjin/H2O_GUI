#include "h2o_dragtile.h"
using namespace ColdWater;
void DragTile::MouseMoveEvent(Point2D LocalPos)
{
    if(m_IsBegin)
    {
        Point2D Parpos=Local2Parent(LocalPos);
        Point2D NewOri;
        NewOri.X=Parpos.X-m_Offset.X;
        NewOri.Y=Parpos.Y-m_Offset.Y;
        setOri(NewOri);
        repaint();
    }
}

void DragTile::MouseLeaveEvent(Tile *leavefor)
{
    //m_IsBegin=0;
}

void DragTile::TimerEvent(int id)
{
   POINT pos;
   Point2D localpos;
   Point2D NewOri;
   //printf("ssss%d\n",m_IsBegin);
   Tile* pRoot=getRoot();

    GetCursorPos(&pos);
    ScreenToClient(Interface::TileWnd_Map[pRoot],&pos);
    localpos.X=pos.x;
    localpos.Y=pos.y;

    //printf("%d,%d,%d\n",((WidgetTest*)pRoot)->flag,localpos.X,localpos.Y);
    if(!pRoot->IsCursorIn(localpos))
    {
       m_IsBegin=0;
       killTimer(TMID_DRAGTILE);
    }
   if(id==TMID_DRAGTILE&&m_IsBegin)
   {



        localpos=pRoot->Parent2Local(localpos);

        //printf("%d,%d,%d\n",((WidgetTest*)pRoot)->flag,localpos.X,localpos.Y);


        localpos=getParent()->Root2Local(localpos);

        NewOri.X=localpos.X-m_Offset.X;
        NewOri.Y=localpos.Y-m_Offset.Y;
        setOri(NewOri);
        repaint();
   }
}

void DragTile::LBUpEvent(Point2D LocalPos)
{
    if(m_IsBegin)
    {
    m_IsBegin=0;
    killTimer(TMID_DRAGTILE);
    }
}

void DragTile::LBDownEvent(Point2D LocalPos)
{
    //printf("dddd%d,%d,%d\n",m_IsBegin,LocalPos.X,LocalPos.Y);
    m_IsBegin=1;
    m_Offset=LocalPos;
    setTimer(TMID_DRAGTILE,5);
}

void DragTile::updateBitmap(Buffer2D<RGBPixel> &bfBitmap)
{
    bfBitmap.fill(RGBPixel(0,255,0));
}
