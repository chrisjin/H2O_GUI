#include "h2o_widget.h"
using namespace ColdWater;
void Widget::repaint()
{
    Painter* painter=getPainter();
    if(!painter)
    {
       // printf(__FUNCDNAME__);
        printf(__FILE__);
        printf(":");
        printf("ERROR Painter NotFound\n",painter);
        return;
    }

    painter->renderView();//先更新所有子元素变化再绘制到屏幕
}
