#ifndef H2O_DELEGATE_H
#define H2O_DELEGATE_H
#pragma warning(disable:4100 4018)
#include<stdio.h>
#include<vector>
#include<map>
using namespace std;
namespace ColdWater
{
    template<class InputType,class OutPutType>
    union cast_union
    {
        InputType in;
        OutPutType out;
    };
    template <class InputType, class OutPutType>
    OutPutType All_cast(InputType a)
    {
        cast_union<InputType,OutPutType> u;
        u.in=a;
        return u.out;
    }

    class VoidClass
    {
        // int Test(int);
    };

    class Object;
    class Function1
    {
    public:
        VoidClass *VoidObject;
        void(VoidClass::*func)(void*);

        template<class CALLORTYPE1,class CALLORTYPE2,class ARGTYPE>
        Function1(CALLORTYPE1 *pthis,void(CALLORTYPE2::*pfunc)(ARGTYPE))
        {
            bind(pthis,pfunc);
        }
        template<class CALLORTYPE1,class CALLORTYPE2,class ARGTYPE>
        void bind(CALLORTYPE1 *pthis,void(CALLORTYPE2::*pfunc)(ARGTYPE))
        {
             VoidObject=reinterpret_cast<VoidClass *>(pthis);
             func=All_cast<void(CALLORTYPE2::*)(ARGTYPE),void(VoidClass::*)(void*)>(pfunc);
             //(caller->*func)
        }
        template<class ARGTYPE>
        void call(ARGTYPE p)
        {
            void(VoidClass::*pfunc)(ARGTYPE);
            pfunc=reinterpret_cast<void(VoidClass::*)(ARGTYPE)>(func);
            (VoidObject->*pfunc)(p);
        }
    };
    class Function0
    {
    public:
        VoidClass *VoidObject;
        void(VoidClass::*func)();
        template<class CALLORTYPE1,class CALLORTYPE2>
        Function0(CALLORTYPE1 *pthis,void(CALLORTYPE2::*pfunc)())
        {
            bind(pthis,pfunc);
        }
        template<class CALLORTYPE1,class CALLORTYPE2>
        void bind(CALLORTYPE1 *pthis,void(CALLORTYPE2::*pfunc)())
        {
            VoidObject=reinterpret_cast<VoidClass *>(pthis);
            func=All_cast<void(CALLORTYPE2::*)(),void(VoidClass::*)(void) >(pfunc);
             //(caller->*func)
        }
        void call()
        {
            (VoidObject->*func)();
        }
    };


    ///////////////////////////////////


    ///////////////////////////////////

    #define DEFSIGNAL(Name) \
        static void Name(){static string SIGNAL_DEOPTIMIZATION##Name=#Name;}

    #define EMIT(Name)  \
        do\
        {\
            if(MapCall0.find(Name)!=MapCall0.end())\
            {\
               vector<Functionvv>* pfuncs=MapCall0[Name];\
               if(pfuncs)\
                 for(int i=0;i<pfuncs->size();i++)\
                 {\
                   (*pfuncs)[i].call();     \
                 }\
            }\
        }while(0)

    #define H2O_FOREACH(Type,itr,Container)\
        for(vector<Elename>::iterator itr=Container.begin;\
            itr!=Container.end();itr++)

    typedef void(*SIGNALTYPE)(void);
    template<class CALLORTYPE1,class CALLORTYPE2,class CALLORTYPE3>
    void connect(CALLORTYPE1* pEmiter,SIGNALTYPE Signal,
                 CALLORTYPE2* pReactor,void(CALLORTYPE3::*pfunc)(void));
    template<class CALLORTYPE1,class CALLORTYPE2,class CALLORTYPE3,class ARGTYPE>
    void connect(CALLORTYPE1* pEmiter,SIGNALTYPE Signal,
                 CALLORTYPE2* pReactor,void(CALLORTYPE3::*pfunc)(ARGTYPE));

    class Object
    {
    public:
        map<SIGNALTYPE,vector<Function0>* > MapCall0;
        map<SIGNALTYPE,vector<Function1>* > MapCall1;

        template<class CALLORTYPE1,class CALLORTYPE2>
        void connect(SIGNALTYPE Signal,
                            CALLORTYPE1* pReactor,void(CALLORTYPE2::*pfunc)(void))
        {
            //Signal();
            ColdWater::connect(this,Signal,pReactor,pfunc);
        }
        template<class CALLORTYPE1,class CALLORTYPE2,class ARGTYPE>
        void connect(SIGNALTYPE Signal,
                            CALLORTYPE1* pReactor,void(CALLORTYPE2::*pfunc)(ARGTYPE))
        {
            //Signal();
            ColdWater::connect(this,Signal,pReactor,pfunc);
        }
        void emitSignal(SIGNALTYPE Signal)
        {
            if(MapCall0.find(Signal)!=MapCall0.end())
            {
               vector<Function0>* pfuncs=MapCall0[Signal];
               if(pfuncs)
                 for(int i=0;i<pfuncs->size();i++)
                 {
                   (*pfuncs)[i].call();
                 }
            }
            else
            {
                printf("%d SLOTNotFound\n",Signal);
            }
        }
        template<class ARGTYPE>
        void emitSignal(SIGNALTYPE Signal,ARGTYPE Arg)
        {
            if(MapCall1.find(Signal)!=MapCall1.end())
            {
               vector<Function1>* pfuncs=MapCall1[Signal];
               if(pfuncs)
                 for(int i=0;i<pfuncs->size();i++)
                 {
                   (*pfuncs)[i].call(Arg);
                 }
            }
            else
            {
                printf("%d SlotNotFound\n",Signal);
            }
        }


    };
    template<class CALLORTYPE1,class CALLORTYPE2,class CALLORTYPE3>
    void connect(CALLORTYPE1* pEmiter,SIGNALTYPE Signal,
                 CALLORTYPE2* pReactor,void(CALLORTYPE3::*pfunc)(void))
    {

        Function0 SlotFunc(pReactor,pfunc);
        map<SIGNALTYPE,vector<Function0>* >::iterator MapCall_itr;
        MapCall_itr=pEmiter->MapCall0.find(Signal);
        if(MapCall_itr==pEmiter->MapCall0.end())
        {
            pEmiter->MapCall0[Signal]=new vector<Function0>;

        }
        else
        {
            if(!pEmiter->MapCall0[Signal])
            {
                pEmiter->MapCall0[Signal]=new vector<Function0>;

            }
        }
        pEmiter->MapCall0[Signal]->push_back(SlotFunc);
    }
    template<class CALLORTYPE1,class CALLORTYPE2,class CALLORTYPE3,class ARGTYPE>
    void connect(CALLORTYPE1* pEmiter,SIGNALTYPE Signal,
                 CALLORTYPE2* pReactor,void(CALLORTYPE3::*pfunc)(ARGTYPE))
    {

        Function1 SlotFunc(pReactor,pfunc);
        map<SIGNALTYPE,vector<Function1>* >::iterator MapCall_itr;
        MapCall_itr=pEmiter->MapCall1.find(Signal);
        if(MapCall_itr==pEmiter->MapCall1.end())
        {
            pEmiter->MapCall1[Signal]=new vector<Function1>;

        }
        else
        {
            if(!pEmiter->MapCall1[Signal])
            {
                pEmiter->MapCall1[Signal]=new vector<Function1>;

            }
        }
        pEmiter->MapCall1[Signal]->push_back(SlotFunc);
    }
}//namespace
#endif // H2O_DELEGATE_H
