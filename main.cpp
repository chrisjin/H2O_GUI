#include<stdio.h>
#include<vector>
#include<map>
#include<Windows.h>
#include<string>
#include<iostream>
#include<time.h>
#include"H2O_Delegate.h"
#include"H2O_Tile.h"
#include"H2O_Button.h"
#include"H2O_Painter.h"
#include"H2O_Widget.h"
#include"H2O_Application.h"
#include"H2O_Interface.h"
#include"H2O_GDIPainter.h"
#include"WidgetTest2.h"
#include"gamepanel.h"

#include"lockscreendlg.h"

//#include"zzza.h"
using namespace std;
using namespace ColdWater;

int __stdcall WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,
LPSTR lpCmdLine,
int nCmdShow
)
{
    //zzzAClass a;
    //printf;
    Application app;
    GDIPainter* paint=new GDIPainter;


    WidgetTest* widget=new WidgetTest(Point2D(0,0),Size2D(900,400));
//    widget->flag=100;
//    WidgetTest* widget2=new WidgetTest(Point2D(0,0),Size2D(900,300));
//    widget2->flag=200;

//    Button *bt =new Button(Point2D(0,0),Size2D(200,300));



//    GamePanel* gp=new GamePanel(Point2D(0,0),Size2D(400,450));
//    //paint->addTile(widget2);
    paint->addTile(widget);

//    typedef int (*hook)(HWND);
//    HINSTANCE hUser = LoadLibraryA("mousehook.dll");
//    int k=(int)GetProcAddress(hUser, "SetHook");
//    hook ho=(hook)k;
//    ho(0);

//    int width = GetSystemMetrics ( SM_CXSCREEN );
//    int height= GetSystemMetrics ( SM_CYSCREEN );
//    LockScreenDlg* lock=new LockScreenDlg(Point2D(0,0),Size2D(width,height));
//    paint->addTile(lock);




    //printf("%d,%d\n",GetWindowLong(hwnd,GWL_USERDATA),wid);
    app.run();

     return 0;
}

