#ifndef H2O_GDIPAINTER_H
#define H2O_GDIPAINTER_H
#include"windows.h"
#include"H2O_Painter.h"
#include"H2O_Interface.h"
namespace ColdWater
{
    class GDIPainter:public Painter
    {
    public:
        vector<HWND> m_hWndList;
        vector<HDC> m_hDCList;
        vector<HBITMAP> m_hBitmapList;
        vector<HDC> m_hMemDCList;
        static CRITICAL_SECTION m_cs;


        GDIPainter();


        void init();//rarely use
        void paint();
        void preaddTile(Tile* tile);

        void destroy();
        void buildBitmap(Tile *ptile, int index);
    };
}

#endif // H2O_GDIPAINTER_H
