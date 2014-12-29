#include "h2o_timer.h"
using namespace ColdWater;
Timer::Timer()
{
    m_IsStart=0;
    m_Tmstruct=0;
	m_hThread=0;
}

void Timer::setTimer(Tile *pt, int id, int ms)
{
    HWND hw=Interface::getWnd(pt);
    if(hw!=NULL)
        SetTimer(hw,
                id,
                ms,0);
    else
        printf("Error,Wnd NotFound\n");
}

void Timer::killTimer(Tile *pt,int id)
{
    HWND hw=Interface::getWnd(pt);
    if(hw!=NULL)
        KillTimer(hw,id);
    else
        printf("Error,Wnd NotFound\n");

}

void Timer::start()
{
    
	if(!m_IsStart)
	{
        SetEvent(m_Tmstruct->m_hCtrlEvent);
		if(!m_hThread)
		m_hThread=(HANDLE)_beginthread(ThreadCallback,0,(void*)m_Tmstruct);
	}

    m_IsStart=1;
}

void Timer::stop()
{
    if(m_IsStart)
    {
    //CloseHandle(m_Tmstruct->hTimer);
    //DeleteObject(m_Tmstruct->hTimer);
		//SuspendThread(m_hThread);
		ResetEvent(m_Tmstruct->m_hCtrlEvent);
		m_IsStart=0;
    }
}
void ColdWater::ThreadCallback(void*p)
{
    int i=0;
    TimerStruct* ptimer=(TimerStruct*)p;
    ptimer->hTimer=CreateWaitableTimer(0,1,0);
    HANDLE htimer=ptimer->hTimer;
    LARGE_INTEGER liduetime;
    liduetime.QuadPart=-(ptimer->iPeriod*10000);
    SetWaitableTimer(htimer,&liduetime,0,0,0,0);
    while(1)
    {
        WaitForSingleObject(ptimer->m_hCtrlEvent,-1);
		if(WaitForSingleObject(htimer,INFINITE)!=WAIT_OBJECT_0)
        {
          break;
        }
		
        else
        {
             ptimer->pFunc->call();
             SetWaitableTimer(htimer,&liduetime,0,0,0,0);
        }

    }

    _endthread();
}

void CALLBACK TimeProc(UINT uID,UINT uMsg,DWORD dwUser,DWORD dw1,DWORD dw2)
{



}
