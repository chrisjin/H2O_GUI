#include "h2o_interface.h"
using namespace ColdWater;
string Interface::WndClass_Name="class_1";
WNDCLASS Interface::WndClass={};
map<int,EVENT> Interface::Message_Map;
REGISTERWNDCLASS Interface::RegisterWndclass(GetModuleHandle(0),"CLASS_1");
BUILDMESSAGEMAP  Interface::BuildMessageMap;
map<Tile*,HWND> Interface::TileWnd_Map;

HWND Interface::MainWindow(Tile *ptile,const char* name)
{
    //ptile->connect(Tile::s_settimer,this,&Interface::setTimerSlot);
    HWND hwnd=CreateWindowEx(
		                    //WS_EX_TOOLWINDOW,
							WS_EX_APPWINDOW&WS_EX_TOPMOST,
							WndClass.lpszClassName,0,
                           WS_OVERLAPPEDWINDOW&~WS_SIZEBOX&(~WS_MAXIMIZEBOX),
                           //WS_POPUP,
                           CW_USEDEFAULT,CW_USEDEFAULT,
                           ptile->getRect().Size.Width+8,ptile->getRect().Size.Height+30,
                           0,0,
                           WndClass.hInstance,
                           ptile);
    if(ptile->IsTrackHover())
    {
    TRACKMOUSEEVENT Track=
         {
          sizeof(TRACKMOUSEEVENT),TME_HOVER,
          hwnd,ptile->getHoverTimeOut()
         };
    TrackMouseEvent(&Track);
    }

    return hwnd;
}

LRESULT Interface::WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static Tile* TopTile=0;
    Point2D* MousePos;
    TRACKMOUSEEVENT Track;
    int *timerid;
   // TimerInfo timerinfo;
    switch(message)
    {
        case WM_CREATE:
          TopTile=(Tile*)((CREATESTRUCT*)lParam)->lpCreateParams;

          //发送create消息之前必须把tile和wnd对插入map里
          TileWnd_Map.insert(pair<Tile*,HWND>(TopTile,hwnd));


          SetWindowLong(hwnd,GWL_USERDATA,(LONG)TopTile);
          TopTile->EventDispatch((Interface::Message_Map)[message],
                                 0);
        return 0;
        case WM_MOUSEMOVE:
        case WM_LBUTTONDOWN:
        case WM_RBUTTONDOWN:
        case WM_LBUTTONUP:
        case WM_RBUTTONUP:
        case WM_MOUSEHOVER:
          TopTile=(Tile*)GetWindowLong(hwnd,GWL_USERDATA);
          if(!TopTile)
              return 0;
          MousePos=new Point2D(LOWORD(lParam),HIWORD(lParam));
          //*MousePos=TopTile->Parent2Local(*MousePos);
          TopTile->EventDispatch((Interface::Message_Map)[message],
                                 MousePos);
          delete MousePos;

          if(TopTile->IsTrackHover())
          {
          Track.cbSize     =sizeof(TRACKMOUSEEVENT);
          Track.dwFlags    =TME_HOVER;
          Track.hwndTrack  =hwnd;
          Track.dwHoverTime=TopTile->getHoverTimeOut();
          TrackMouseEvent(&Track);
          }
        return 0;
        case WM_PAINT:
          TopTile=(Tile*)GetWindowLong(hwnd,GWL_USERDATA);
          TopTile->getPainter()->renderView();
        return 0;
        case WM_TIMER:
            TopTile=(Tile*)GetWindowLong(hwnd,GWL_USERDATA);//莫忘！！！！
            timerid=new int;
            *timerid=wParam;
            TopTile->EventDispatch((Interface::Message_Map)[message],timerid);
            delete timerid;
        return 0;
        case WM_CHAR:
            TopTile=(Tile*)GetWindowLong(hwnd,GWL_USERDATA);
            TopTile->EventDispatch((Interface::Message_Map)[message],&wParam);
        return 0;
        case WM_KEYDOWN:
            TopTile=(Tile*)GetWindowLong(hwnd,GWL_USERDATA);
            TopTile->EventDispatch((Interface::Message_Map)[message],&wParam);
        return 0;
        case WM_KEYUP:
            TopTile=(Tile*)GetWindowLong(hwnd,GWL_USERDATA);
            TopTile->EventDispatch((Interface::Message_Map)[message],&wParam);
        return 0;
        case WM_IME_ENDCOMPOSITION:
            TopTile=(Tile*)GetWindowLong(hwnd,GWL_USERDATA);
            TopTile->EventDispatch((Interface::Message_Map)[message],0);
        return 0;
        case WM_IME_CHAR:
            TopTile=(Tile*)GetWindowLong(hwnd,GWL_USERDATA);
            TopTile->EventDispatch((Interface::Message_Map)[message],&wParam);
        return 0;
        case WM_DESTROY:
            TopTile=(Tile*)GetWindowLong(hwnd,GWL_USERDATA);
            TopTile->EventDispatch((Interface::Message_Map)[message],&wParam);
            ShowWindow(hwnd,SW_HIDE);
        return 0;
		case WM_CLOSE:								
		    PostQuitMessage(0);						
		return 0;	
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}

Tile *Interface::getTile(HWND hwnd)
{
    return (Tile*)GetWindowLong(hwnd,GWL_USERDATA);
}

HWND Interface::getWnd(Tile *tile)
{
    if(TileWnd_Map.find(tile)!=TileWnd_Map.end())
    return TileWnd_Map[tile];
    else
        return NULL;
}

void Interface::destroyMainWnd(Tile *tile)
{
    HWND hw=TileWnd_Map[tile];
    SendMessage(hw,WM_DESTROY,0,0);
}



REGISTERWNDCLASS::REGISTERWNDCLASS(HINSTANCE hInstance,const char *name)
{
    Interface::WndClass.style= CS_HREDRAW | CS_VREDRAW ;
    Interface::WndClass.lpfnWndProc=Interface::WindowProc ;
    Interface::WndClass.cbClsExtra = 0 ;
    Interface::WndClass.cbWndExtra= 0 ;
    Interface::WndClass.hInstance  = hInstance ;
    Interface::WndClass.hIcon= LoadIcon (NULL, IDI_APPLICATION) ;
    Interface::WndClass.hCursor = LoadCursor (NULL, IDC_ARROW) ;
    Interface::WndClass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;
    Interface::WndClass.lpszMenuName = NULL ;
#ifdef UNICODE
    Interface::WndClass.lpszClassName=reinterpret_cast<LPCWSTR>(Interface::WndClass_Name.c_str());
#endif
#ifndef UNICODE
    Interface::WndClass.lpszClassName=GLOBAL_WndClass_Name.c_str();
#endif
    RegisterClass(&Interface::WndClass);
   //WndClass.lpszClassName=name;
}

#define MSGPAIR(Msg) pair<int,EVENT>(WM_##Msg,EVT_##Msg)
BUILDMESSAGEMAP::BUILDMESSAGEMAP()
{
    Interface::Message_Map.insert(MSGPAIR(MOUSEMOVE));
    Interface::Message_Map.insert(MSGPAIR(LBUTTONDOWN));
    Interface::Message_Map.insert(MSGPAIR(RBUTTONDOWN));
    Interface::Message_Map.insert(MSGPAIR(LBUTTONUP));
    Interface::Message_Map.insert(MSGPAIR(RBUTTONUP));
    Interface::Message_Map.insert(MSGPAIR(MOUSEHOVER));
    Interface::Message_Map.insert(MSGPAIR(TIMER));
    Interface::Message_Map.insert(MSGPAIR(CREATE));
    Interface::Message_Map.insert(MSGPAIR(CHAR));
    Interface::Message_Map.insert(MSGPAIR(KEYDOWN));
    Interface::Message_Map.insert(MSGPAIR(KEYUP));
    Interface::Message_Map.insert(MSGPAIR(IME_ENDCOMPOSITION));
    Interface::Message_Map.insert(MSGPAIR(IME_CHAR));
    Interface::Message_Map.insert(MSGPAIR(DESTROY));
}
