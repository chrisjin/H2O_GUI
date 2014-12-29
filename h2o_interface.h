#ifndef H2O_INTERFACE_H
#define H2O_INTERFACE_H

#include<windows.h>
#include<map>
#include"H2O_Tile.h"
#include"H2O_Lings.h"
#include"H2O_Painter.h"
/*

    �����Ϣ��
    1����h2o_lings�������Ӧ��EVTö��Ԫ��
    2���ڱ�cpp��insert��Ϣ��
    3���ڱ�cpp�������Ӧ��case�����涨additionalinfo�ĺ���
*/
//extern string GLOBAL_WndClass_Name="class_1";
//extern WNDCLASS GLOBAL_WndClass;
//extern map<int,EVENT> GLOBAL_Message_Map;
namespace ColdWater
{
    class REGISTERWNDCLASS
    {
    public:
        REGISTERWNDCLASS(HINSTANCE hInstance,const char *name);
    };

    //extern REGISTERWNDCLASS RegisterWndclass(GetModuleHandle(0),"CLASS_1");



    class BUILDMESSAGEMAP
    {
    public:
        BUILDMESSAGEMAP();
    };
    //extern BUILDMESSAGEMAP BuildMessageMap;

    class Tile;
    class Interface
    {
    public:
        static string WndClass_Name;
        static WNDCLASS WndClass;
        static map<int,EVENT> Message_Map;
        static map<Tile*,HWND> TileWnd_Map;
     //   static Tile* m_pTile;
        static REGISTERWNDCLASS RegisterWndclass;
        static BUILDMESSAGEMAP  BuildMessageMap;
        static HWND MainWindow(Tile* ptile, const char *name);
        static LRESULT CALLBACK WindowProc(HWND hwnd,UINT message,
                                           WPARAM wParam,LPARAM lParam);
        static Tile* getTile(HWND hwnd);
        static HWND  getWnd(Tile* tile);
        static void destroyMainWnd(Tile* tile);
        //void setTimerSlot(TimerInfo* pTimerInfo);
     //   void setTimer(HWND hwnd,int ms)

    };

}
#endif // H2O_INTERFACE_H
