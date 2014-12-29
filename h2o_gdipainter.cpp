#include "h2o_gdipainter.h"
using namespace ColdWater;
CRITICAL_SECTION GDIPainter::m_cs;
GDIPainter::GDIPainter()
{
    InitializeCriticalSection(&m_cs);///不初始化则崩溃
}
void GDIPainter::init()//rarely use
{
    HWND hw;
    Rect2D rect;
    HDC hdc,hMemDC;
    HBITMAP hBitmap;
    PAINTSTRUCT     ps ;
    for(int i=0;i<getTileNum();i++)
    {
        rect=getnTile(i)->getRect();
        hw=Interface::MainWindow(getnTile(i),"AAAAA");
        hdc=GetDC(hw);
        hBitmap=CreateCompatibleBitmap(hdc,
                                       rect.Size.Width+8,rect.Size.Height+30);
        hMemDC=CreateCompatibleDC(hdc);


        m_hWndList.push_back(hw);
        m_hDCList.push_back(hdc);
        m_hBitmapList.push_back(hBitmap);
        m_hMemDCList.push_back(hMemDC);

        ShowWindow(hw,SW_SHOW);
        SelectObject(hMemDC,hBitmap);
    }
}
void GDIPainter::destroy()
{
    for(int i=0;i<m_hDCList.size();i++)
    {
        DeleteObject(m_hDCList[i]);
        DeleteObject(m_hBitmapList[i]);
        DeleteObject(m_hMemDCList[i]);
    }
}
void GDIPainter::preaddTile(Tile *tile)
{
    HWND hw;
    Rect2D rect;
    HDC hdc,hMemDC;
    HBITMAP hBitmap;
    rect=tile->getRect();
    hw=Interface::MainWindow(tile,"AAAAA");
    hdc=GetDC(hw);
    hBitmap=CreateCompatibleBitmap(hdc,
                                   rect.Size.Width+8,rect.Size.Height+30);
    hMemDC=CreateCompatibleDC(hdc);


    m_hWndList.push_back(hw);
    m_hDCList.push_back(hdc);
    m_hBitmapList.push_back(hBitmap);
    m_hMemDCList.push_back(hMemDC);

    ShowWindow(hw,SW_SHOW);
    SelectObject(hMemDC,hBitmap);
}




void GDIPainter::paint()
{

    Tile* ptile;
    Rect2D rect;
    PAINTSTRUCT     ps ;
    HDC hdc;
    RECT crect;
   // printf("Tilenum%d\n",getTileNum());
   // CRITICAL_SECTION m_cs;

    if(!TryEnterCriticalSection(&m_cs))
    {
        //printf("Painter Too Busy\n");
        return;
    }

//    EnterCriticalSection(&m_cs);//防止几个线程同时过多地刷新
    for(int i=0;i<getTileNum();i++)
    {
        BeginPaint(m_hWndList[i], &ps) ;
        GetClientRect(m_hWndList[i],&crect);
        ptile=getnTile(i);
        rect=ptile->getRect();



        buildBitmap(ptile,i);
        //printf("%d,%d\n",crect.left,crect.top);
        BitBlt (m_hDCList[i], rect.Pos1.X+crect.left,rect.Pos1.Y+crect.top,
                rect.Size.Width,rect.Size.Height,m_hMemDCList[i], 0, 0, SRCCOPY) ;

        EndPaint(m_hWndList[i], &ps) ;
    }

    LeaveCriticalSection(&m_cs);

}

void GDIPainter::buildBitmap(Tile* ptile,int index)
{
    if(!ptile->IsHide())
    {
        Rect2D rect=ptile->getRect();
        Tile *parent=ptile->getParent();
        Point2D absp=parent?parent->Local2Root(rect.Pos1):Point2D(0,0);

        int bitmapwidth=ptile->getBitmap().Size.Width;
        int bitmapheight=ptile->getBitmap().Size.Height;
        //absp=ptile->getRoot()->Local2Parent(absp);
        //Point2D absp=rect.Pos1;

        HDC hChildMemDC     =CreateCompatibleDC(m_hMemDCList[index]);
        HBITMAP hChildBitmap=CreateCompatibleBitmap(m_hMemDCList[index],
                                                    bitmapwidth,bitmapheight);
        SetBitmapBits(hChildBitmap,
                      bitmapwidth*bitmapheight*sizeof(RGBPixel),
                      ptile->getBitmap().get());

       // hChildBitmap=CreateBitmap(bitmapwidth,bitmapheight,1,32,ptile->getBitmap().get());
        SelectObject(hChildMemDC,hChildBitmap);



        BLENDFUNCTION blend={AC_SRC_OVER,0,255,AC_SRC_ALPHA };

//        ::AlphaBlend (m_hMemDCList[index],absp.X,absp.Y,
//                        bitmapwidth,bitmapheight, hChildMemDC, 0, 0,
//                        bitmapwidth,bitmapheight,blend) ;

//        ::TransparentBlt (m_hMemDCList[index],absp.X,absp.Y,
//                      bitmapwidth,bitmapheight, hChildMemDC, 0, 0,
//                      bitmapwidth,bitmapheight,RGB(255,255,255)) ;

//        ::StretchBlt (m_hMemDCList[index],absp.X,absp.Y,
//                      rect.Size.Width,rect.Size.Height, hChildMemDC, 0, 0,
//                      bitmapwidth,bitmapheight,RGB(255,255,255)) ;

        ::BitBlt (m_hMemDCList[index],absp.X,absp.Y,
                      rect.Size.Width,rect.Size.Height, hChildMemDC, 0, 0,
                      SRCCOPY) ;


        DeleteObject(hChildBitmap);
        DeleteObject(hChildMemDC);
    }
    for(Tile::CHILDRENTYPE::iterator itr=ptile->childbegin();
        itr!=ptile->childend();++itr)
    {
        buildBitmap(*itr,index);
    }


}
