#include "h2o_application.h"
using namespace ColdWater;

void Application::run()
{
    MSG msg;
    while(GetMessage(&msg, NULL, 0, 0))
    {
      TranslateMessage(&msg) ;
      DispatchMessage(&msg) ;
    }
    /*
    while(1)
    {
        if(PeekMessage(&msg, NULL, 0, 0,PM_REMOVE))
        {
            if(msg.message==WM_QUIT)
                break;
            TranslateMessage(&msg) ;
            DispatchMessage(&msg) ;
        }
        else
        {

        }
    }
    */

}
