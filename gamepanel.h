#ifndef GAMEPANEL_H
#define GAMEPANEL_H
#include"h2o_widget.h"
#include"h2o_button.h"
using namespace ColdWater;
class GamePanel:public Widget
{
public:
    Button *startbt;
    Button *quitbt;
    DEFCSTRCTOR(GamePanel,Widget)
    {
        getBitmap().fill(RGBPixel(200,200,0));
        startbt=new Button(Point2D(getHCenter()-75,getRect().Size.Height-150),
                           Size2D(150,30));
        quitbt=new Button(Point2D(getHCenter()-50,getRect().Size.Height-100),
                           Size2D(100,30));
        startbt->setText(L"Game Start");
        quitbt->setText(L"Quit");
        addTile(startbt);
        addTile(quitbt);
        quitbt->connect(Button::s_clicked,this,&GamePanel::quit);
        startbt->connect(Button::s_clicked,this,&GamePanel::start);
    }
    void quit()
    {
        Interface::destroyMainWnd(this);
        PostQuitMessage(0);
    }
    void start()
    {
        startbt->setHide();
        quitbt->setHide();
        quitbt->setDisabled();
    }
};

#endif // GAMEPANEL_H
