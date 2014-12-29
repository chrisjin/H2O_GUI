#ifndef H2O_TIMER_H
#define H2O_TIMER_H
#include"H2O_Delegate.h"
#include"h2o_tile.h"
#include"h2o_interface.h"
#include<process.h>
namespace ColdWater
{
    class Tile;
    void ThreadCallback(void* p);
    void CALLBACK TimeProc(UINT uID,UINT uMsg,DWORD dwUser,DWORD dw1,DWORD dw2);

    struct TimerStruct
    {
        Function0* pFunc;
        int iPeriod;
        HANDLE hTimer;
		HANDLE m_hCtrlEvent;
    };
    class Timer:public Object
    {





        //void(*m_TimerThread)();
        HANDLE m_hThread;
		
        //HANDLE m_hTimer;
        TimerStruct *m_Tmstruct;
        bool m_IsStart;

    public:
        Timer();
        ////////////////////////
        //高精度模式
        ////////////////////////
        void start();
        void stop();
        template<class CALLORTYPE1,class CALLORTYPE2>
        void setTimer(CALLORTYPE1 *pthis,void(CALLORTYPE2::*pfunc)(),int ms)
        {
            if(m_Tmstruct)
            {
                if(m_Tmstruct->pFunc)
                    free(m_Tmstruct->pFunc);
                free(m_Tmstruct);
            }
            m_Tmstruct=new TimerStruct;
            m_Tmstruct->pFunc=new Function0(pthis,pfunc);
            m_Tmstruct->iPeriod=ms;
			m_Tmstruct->m_hCtrlEvent=CreateEvent(0,1,1,0);
			//m_hThread=(HANDLE)_beginthread(ThreadCallback,0,(void*)m_Tmstruct);
			//SuspendThread(m_hThread);
        }

        ////////////////////////
        //立即消息模式
        ////////////////////////
        static void setTimer(Tile* pt,int id,int ms);
        static void killTimer(Tile *pt,int id);

    };
}
#endif // H2O_TIMER_H
