#include "h2o_tile.h"
using namespace ColdWater;

Tile* Tile::m_MouseFocusTile=0;
void Tile::initFlag()
{
    //m_Bitmap.flag=500;
    m_Parent=0;
    m_Painter=0;
    m_IsChange=1;
    m_IsDisabled=0;
    m_IsHide=0;
    m_IsGrabFocus=1;
    m_IsInset=0;
    m_IsMouseTrigger=1;
    setHover(50);
    //printf("%d,%d,%d\n",s_settimer,s_sizechange,s_hidechange);
}
Tile::Tile()
{
    initFlag();
}
Tile::Tile(const Point2D ori,const Size2D size,bool isalloc):m_Rect(ori,size)
{
    if(isalloc)
    m_Bitmap.Alloc(size);
    initFlag();
}

Painter*   Tile::getPainter()
{
    Tile* ptile=this;
    while(1)
    {
        if(ptile->m_Painter)
        {
            m_Painter=ptile->m_Painter;
            return ptile->m_Painter;
        }
        ptile=ptile->getParent();
        if(ptile==0)break;
    }
    return 0;
}

Tile* Tile::getRoot()
{
    Tile* pt=this;
    while(1)
    {
        pt=pt->getParent();
        if(!pt->getParent())
            return pt;
    }
}





///////////////////////////////////
///Coordinate
///////////////////////////////////
Tile* Tile::pick(const Point2D localpos)
{

//   for(int i=m_Children.size()-1;i>=0;i--)
//   {
//      if(m_Children[i]->getRect().IsIn(localpos))
//          return m_Children[i];
//   }
//   return this;

   for(CHILDRENTYPE::iterator itr=m_Children.end();
       itr!=m_Children.begin();)
   {
       --itr;
       if(!(*itr)->IsMouseTrigger())continue;
       if((*itr)->getRect().IsIn(localpos))
         return (*itr);
   }
   return this;
}
Point2D Tile::Parent2Local(const Point2D p)
{
    Point2D ret;
    Point2D OneEnd=getRect().Pos1;
    ret.X=p.X-OneEnd.X;
    ret.Y=p.Y-OneEnd.Y;
    return ret;
}
Point2D Tile::Local2Parent(const Point2D p)
{
    Point2D ret;
    Point2D OneEnd=getRect().Pos1;
    ret.X=p.X+OneEnd.X;
    ret.Y=p.Y+OneEnd.Y;
    return ret;
}
Point2D Tile::Local2Root(const Point2D p)
{
    Point2D curp=p;
    Tile* curt=this;

    while(1)
    {
       if(curt->getParent())
       curp=curt->Local2Parent(curp);
       else
           break;
       curt=curt->getParent();

    }
    return curp;
}
Point2D Tile::Root2Local(const Point2D p)
{
    Point2D curp=p;
    Tile* curt=this;
    while(1)
    {
       if(curt->getParent())
        curp=curt->Parent2Local(p);
       else
           break;
       curt=curt->getParent();

    }
    return curp;
}





///////////////////////////////////
///Repaint  由render调用
///////////////////////////////////
void Tile::handleChange()
{
    if(IsChange())
    updateBitmap(m_Bitmap);
    unsetChange();
}
void Tile::handleAllChildrenChange(Tile *ptile)
{
//    for(int i=0;i<ptile->m_Children.size();i++)
//    {
//       ptile->handleAllChildrenChange(ptile->m_Children[i]);
//    }
//    ptile->handleChange();
    for(CHILDRENTYPE::iterator itr=ptile->m_Children.begin();
        itr!=ptile->m_Children.end();
        ++itr)
    {
       ptile->handleAllChildrenChange(*itr);
    }
    ptile->handleChange();
}
void Tile::handleAllChildrenChange()
{
    handleAllChildrenChange(this);
}
//////使bfBitmap和data一致************************************************
void Tile::updateBitmap(Buffer2D<RGBPixel>& bfBitmap)
{
    //make the bitmap to paint

}




///////////////////////////////////
///Message   interface tile 消息
///////////////////////////////////
bool Tile::EventPreprocess(EVENT event,void* additionalinfo)
{
    return 0;
}
bool Tile::EventDispatch(EVENT event,void* additionalinfo)
{

    if(EventPreprocess(event,additionalinfo)==1)
        return 1;
    else
        return DefEventDispatch(event,additionalinfo);
}
bool Tile::DefEventDispatch(EVENT event,void* additionalinfo)
{
    static Point2D ParentCurPos;
    static Point2D LocalCurPos;
    //static Point2D SubLocalCurPos;
    static Tile* CurrentTile;
    static Tile* PrevTile=0;
    static Tile* LostFocusTile;
    static Tile* FocusTile;
    unsigned int uintval;
    wchar_t unicodechar;
    int timerid;
    switch(event)
    {
      case EVT_CREATE:
        CreateEvent();
        for(CHILDRENTYPE::iterator itr=m_Children.begin();
            itr!=m_Children.end();++itr)
        {
            (*itr)->EventDispatch(EVT_CREATE,0);

        }
        return 1;
      case EVT_MOUSEMOVE:
      case EVT_LBUTTONDOWN:
      case EVT_LBUTTONUP:
      case EVT_RBUTTONDOWN:
      case EVT_RBUTTONUP:
      case EVT_MOUSEHOVER:
        if(IsDisabled())return 0;
        if(!additionalinfo)return 0;
        ParentCurPos.X=((Point2D*)additionalinfo)->X;
        ParentCurPos.Y=((Point2D*)additionalinfo)->Y;
        LocalCurPos=Parent2Local(ParentCurPos);
        if(!IsCursorIn(ParentCurPos))
        {
            CurrentTile=0;
            return 0;
        }
        CurrentTile=pick(LocalCurPos);
        //SubLocalCurPos=CurrentTile->Parent2Local(LocalCurPos);
        if(CurrentTile==this)//此时LocalCurPos即为控件内部cursor
        {

           switch(event)
           {
           case EVT_MOUSEMOVE:
               MouseMoveEvent(LocalCurPos);
               break;
           case EVT_LBUTTONDOWN:
               LostFocusTile=getFocusTile();
               CurrentTile->setMouseFocus();
               if(LostFocusTile&&LostFocusTile!=CurrentTile)
               LostFocusTile->EventDispatch(EVT_LOSEFOCUS,(void*)CurrentTile);
               if(LostFocusTile!=CurrentTile)
               CurrentTile->EventDispatch(EVT_GRABFOCUS,LostFocusTile);
               LBDownEvent(LocalCurPos);
               break;
           case EVT_RBUTTONDOWN:
               RBDownEvent(LocalCurPos);
           case EVT_LBUTTONUP:
               LBUpEvent(LocalCurPos);
               break;
           case EVT_RBUTTONUP:
               RBUpEvent(LocalCurPos);
               break;
           case EVT_MOUSEHOVER:
               //printf("HHHHHH\n");
               MouseHoverEvent(LocalCurPos);
               break;
           }
        }
        else
        {
           CurrentTile->EventDispatch(event,&LocalCurPos);
        }
        if(PrevTile!=CurrentTile)
        {
           if(PrevTile)
              PrevTile->EventDispatch(EVT_MOUSELEAVE,CurrentTile);
           if(CurrentTile)
              CurrentTile->EventDispatch(EVT_MOUSEENTER,PrevTile);
           PrevTile=CurrentTile;
        }
        return 1;
      case EVT_MOUSEENTER:
        MouseEnterEvent((Tile*)additionalinfo);
        return 1;
      case EVT_MOUSELEAVE:
        MouseLeaveEvent((Tile*)additionalinfo);
        return 1;
      case EVT_TIMER:
        timerid=*((int*)additionalinfo);
        TimerEvent(timerid);
        for(CHILDRENTYPE::iterator itr=m_Children.begin();
            itr!=m_Children.end();itr++)
        {
            (*itr)->EventDispatch(EVT_TIMER,additionalinfo);
        }

        return 1;
      case EVT_LOSEFOCUS:
        LoseFocusEvent((Tile*)additionalinfo);
        return 1;
      case EVT_GRABFOCUS:
        GrabFocusEvent((Tile*)additionalinfo);
        return 1;
      case EVT_CHAR:
        FocusTile=getFocusTile();
        uintval=*((unsigned int*)(additionalinfo));
        if(FocusTile)
        FocusTile->CharEvent(uintval);
        return 1;
      case EVT_KEYDOWN:
        FocusTile=getFocusTile();
        uintval=*((unsigned int*)(additionalinfo));
        if(FocusTile)
        FocusTile->KeyDownEvent(uintval);
        return 1;
      case EVT_KEYUP:
        FocusTile=getFocusTile();
        uintval=*((unsigned int*)(additionalinfo));
        if(FocusTile)
        FocusTile->KeyUpEvent(uintval);
        return 1;
      case EVT_IME_ENDCOMPOSITION:
        FocusTile=getFocusTile();
        if(FocusTile)
        FocusTile->ImeEndEvent();
        return 1;
      case EVT_IME_CHAR:
        FocusTile=getFocusTile();
        unicodechar=*((wchar_t*)(additionalinfo));
        if(FocusTile)
        FocusTile->ImeCharEvent(unicodechar);
        return 1;


    }//switch end
    return 1;

}

void Tile::setTimer(int ID, int ms)
{
    Timer::setTimer(getRoot(),ID,ms);
}
void Tile::killTimer(int ID)
{
    Timer::killTimer(getRoot(),ID);
}

void Tile::setMouseFocus()
{
    if(!IsGrabFocus())
        return;
    if(m_MouseFocusTile==this)
        return;
    Tile* tile=getParent();
    m_MouseFocusTile=this;
    if(IsInset())
        return;
    if(tile)
    {
        for(CHILDRENTYPE::iterator itr=tile->m_Children.begin();
            itr!=tile->m_Children.end();itr++)
        {
            if((*itr)==this)
            {
                tile->m_Children.erase(itr);
                tile->m_Children.push_back(this);

                return;
            }


        }

    }
}
