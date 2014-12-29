#ifndef H2O_WIDGET_H
#define H2O_WIDGET_H
#include"H2O_Painter.h"
#include"H2O_Tile.h"
#define DEFCSTRCTOR(classname,inhname)\
    classname(const Point2D pos,const Size2D size,bool isalloc=1):inhname(pos,size,isalloc)
/////////////////////////////////////////////////////////
/*
  Widget/Tile        TypeWriter     Painter
      ^                               ^
      |                               |
      |                               |
 Button,GIFPlayer                   GDIPainter
*/
///////////////////////////////////////////////////////////





namespace ColdWater
{
    class Widget:public Tile
    {
    public:
       Widget()
       {
         connect(s_hidechange,this,&Widget::repaint);
       }
       DEFCSTRCTOR(Widget,Tile)
       {
           connect(s_hidechange,this,&Widget::repaint);
       }
       void repaint();
    };

}


#endif // H2O_WIDGET_H
