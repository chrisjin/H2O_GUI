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

    painter->renderView();//�ȸ���������Ԫ�ر仯�ٻ��Ƶ���Ļ
}
