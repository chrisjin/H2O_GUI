#ifndef H2O_TILE_H
#define H2O_TILE_H
#include"H2O_Delegate.h"
#include"H2O_Lings.h"
#include"h2o_timer.h"
#include<list>
#define DEFFLAG(name) \
    private:  bool m_Is##name;\
    public:   inline bool Is##name() {return m_Is##name;}\
    public:   inline void set##name() {m_Is##name=1;}\
    public:   inline void unset##name() {m_Is##name=0;}

namespace ColdWater
{
    class Painter;
    class Timer;
    class Tile:public Object
    {
    public:
        typedef list<Tile*> CHILDRENTYPE;
    private:
        DEFFLAG(Change)    //Tile   判断
        DEFFLAG(Disabled)  //Tile   判断
        DEFFLAG(GrabFocus)
        DEFFLAG(Inset)    //是否始终位于最下方
        DEFFLAG(MouseTrigger)
    private:
        bool m_IsHide;      //render 判断
        bool m_IsTrackHover;//interface判断
        int  m_HoverTimeOut;

        Buffer2D<RGBPixel>  m_Bitmap;
        Rect2D              m_Rect;
        Tile *              m_Parent;
        static Tile* m_MouseFocusTile;
        CHILDRENTYPE       m_Children;
        CHILDRENTYPE::iterator m_Children_itr;
        Painter*            m_Painter;
        friend class Painter;

    public:
        void initFlag();
        Tile();
        Tile(const Point2D ori,const Size2D size,bool IsAlloc=1);
        //void f();

    public:
        DEFSIGNAL(s_hidechange)//void
        DEFSIGNAL(s_sizechange)//void
        //DEFSIGNAL(s_settimer)//*TimerEvent
    public:
        ///////////////////////////////////
        ///iterator
        ///////////////////////////////////

        Tile* child(){return *m_Children_itr;}


        Tile* childat(int index)
        {
            m_Children_itr=m_Children.begin();
            for(int i=0;i<index;i++)
                ++m_Children_itr;
            return *m_Children_itr;
        }

        CHILDRENTYPE::iterator childend(){return m_Children.end();}
        CHILDRENTYPE::iterator childbegin(){return m_Children.begin();}

    public:

        ///////////////////////////////////
        ///Set
        ///////////////////////////////////
        void addTile(Tile *pTile)
                    {m_Children.push_back(pTile);pTile->m_Parent=this;}
        void setRect(const Point2D ori,const Size2D size)////?????
                    {}
        void setSize(const Size2D size,bool Isalloc=0)
                    {m_Rect.setSize(size);if(Isalloc)m_Bitmap.ReAlloc(size);}////?????
        void setHide()
                    {m_IsHide=1;emitSignal(s_hidechange);}
        void unsetHide()
                    {m_IsHide=0;}
        void setHover(int timeout=100)
                    {m_IsTrackHover=1;m_HoverTimeOut=timeout;}
        void unsetHover()
                    {m_IsTrackHover=0;}
        void setOri(Point2D pos)
                    {m_Rect.setPos1(pos);}
        void setTimer(int ID,int ms);

        void killTimer(int ID);

        template<class CALLORTYPE1,class CALLORTYPE2>
        void setTimeOutFunc(CALLORTYPE1* pReactor,void(CALLORTYPE2::*pfunc)(void))
        {
            //printf("DDD\n");
            Timer::setTimeOutFunc(pReactor,pfunc);
        }

        void setMouseFocus();

    protected:
        void setPainter(Painter* painter)
                    {m_Painter=painter;}
    public:
        ///////////////////////////////////
        ///Get
        ///////////////////////////////////
        Rect2D&             getRect()           {return m_Rect;}
        Buffer2D<RGBPixel>& getBitmap()         {return m_Bitmap;}
        Tile*               getnChild(int index){return childat(index);}
        Tile*               getParent()         {return m_Parent;}
        int                 getChildNum()       {return m_Children.size();}
        bool                IsHide()            {return m_IsHide;}
        int                 getHoverTimeOut()   {return m_HoverTimeOut;}
        bool                IsTrackHover()      {return m_IsTrackHover;}
        inline bool         IsCursorIn(const Point2D parentpos)
                                                {return getRect().IsIn(parentpos);}
        static Tile*        getFocusTile()
                                                {return m_MouseFocusTile;}
        Painter*            getPainter();
        Tile*               getRoot();
        int                 getHCenter()        {return getRect().Size.Width/2;}
        int                 getVCenter()        {return getRect().Size.Height/2;}


        ///////////////////////////////////
        ///Coordinate
        ///////////////////////////////////
        Tile* pick(const Point2D localpos);
        Point2D Parent2Local(const Point2D p);
        Point2D Local2Parent(const Point2D p);
        Point2D Local2Root(const Point2D p);
        Point2D Root2Local(const Point2D p);





        ///////////////////////////////////
        ///Repaint  由render调用
        ///////////////////////////////////
        void handleChange();
        void handleAllChildrenChange(Tile *ptile);
        void handleAllChildrenChange();
        //////使bfBitmap和data一致************************************************
        virtual void updateBitmap(Buffer2D<RGBPixel>& bfBitmap);




        ///////////////////////////////////
        ///Message   interface tile 消息
        ///////////////////////////////////
        virtual bool EventPreprocess(EVENT event,void* additionalinfo);
        ///////Mouse   additionalinfo=parentpos
        bool EventDispatch(EVENT event,void* additionalinfo);

        bool DefEventDispatch(EVENT event,void* additionalinfo);

        virtual void MouseMoveEvent(Point2D LocalPos){}
        virtual void LBDownEvent(Point2D LocalPos){}
        virtual void RBDownEvent(Point2D LocalPos){}
        virtual void LBUpEvent(Point2D LocalPos){}
        virtual void RBUpEvent(Point2D LocalPos){}
        virtual void MBDownEvent(Point2D LocalPos){}
        virtual void MouseHoverEvent(Point2D LocalPos){}
        virtual void MouseLeaveEvent(Tile* leavefor){}
        virtual void MouseEnterEvent(Tile* leavefrom){}
        virtual void TimerEvent(int id){}
        virtual void CreateEvent(){}
        virtual void LoseFocusEvent(Tile*){}
        virtual void GrabFocusEvent(Tile*){}
        virtual void CharEvent(unsigned int a){}
        virtual void KeyDownEvent(unsigned int a){}
        virtual void KeyUpEvent(unsigned int a){}
        virtual void ImeEndEvent(){}

        virtual void ImeCharEvent(wchar_t a){}

    };
}


#endif // H2O_TILE_H
