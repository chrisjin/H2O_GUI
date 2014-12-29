#include "h2o_button.h"
using namespace ColdWater;
Button::Button(Point2D ori, int lengthlevel):Widget(ori,Size2D(32*lengthlevel+64,32))
{
    m_IsPress=0;
    createWar3Skin();

}

void Button::createWriter()
{
    Font *font=new Font;
    font->createFont(16,16,"C:/Windows/Fonts/simsun.ttc");


    m_Writer.setFont(font);
    //m_Writer.setCurPosition(0,getRect().Size.Height/2-9);

}

Button::Button(Point2D ori,Size2D size):Widget(ori,size)
{
    m_IsPress=0;
    createWriter();
    //printf("ssss\n");
    createDefaultSkin();
}
void Button::createDefaultSkin()
{

    m_PressImg.Alloc(getRect().Size);
    m_ReleaseImg.Alloc(getRect().Size);
    m_HoverImg.Alloc(getRect().Size);
    m_PressImg.fill(RGBPixel(0,0,0));
    int insetx=5;
    if(insetx<3)
        insetx=3;
    //int insety=insetx*((double)getRect().Size.Height/(double)getRect().Size.Width);
    int insety=3;
    if(insety==0)
        insety=1;


	for (int i = 0; i < m_ReleaseImg.getHeight(); i++)
	{
		m_ReleaseImg.fillLine(RGBPixel(200-2*i, 200-2*i, 200-2*i),i);
		m_HoverImg.fillLine(RGBPixel(220 - i, 220 - i, 220 - i), i);
		m_PressImg.fill(m_ReleaseImg, Rect2D(Point2D(insetx, insety), getRect().Size));
	}
    //m_ReleaseImg.fill(RGBPixel(200,200,200));
    //m_HoverImg.fill(RGBPixel(220,220,220));
    //m_PressImg.fill(m_ReleaseImg,Rect2D(Point2D(insetx,insety),getRect().Size));

    getBitmap().copy(m_ReleaseImg);


}

void Button::createWar3Skin()
{
    ImageFile rel_l;
    ImageFile rel_m;
    ImageFile rel_r;

    ImageFile pr_l;
    ImageFile pr_m;
    ImageFile pr_r;

    rel_l.read("src/releasebt/l.bmp");
    rel_m.read("src/releasebt/m.bmp");
    rel_r.read("src/releasebt/r.bmp");
    pr_l.read("src/pressbt/l.bmp");
    pr_m.read("src/pressbt/m.bmp");
    pr_r.read("src/pressbt/r.bmp");

    int newwidth=(int)((double)rel_l.getWidth()*
            ((double)getRect().Size.Height/(double)rel_l.getHeight()));

    rel_l.rescale(Size2D(newwidth,getRect().Size.Height));
    rel_r.rescale(Size2D(newwidth,getRect().Size.Height));
    rel_m.rescale(Size2D(1,getRect().Size.Height));
    pr_l.rescale(Size2D(newwidth,getRect().Size.Height));
    pr_r.rescale(Size2D(newwidth,getRect().Size.Height));
    pr_m.rescale(Size2D(1,getRect().Size.Height));

    int n_m=getRect().Size.Width-2*newwidth;


    m_PressImg.Alloc(getRect().Size);
    m_ReleaseImg.Alloc(getRect().Size);

    rel_l.writeToMem(m_ReleaseImg,Point2D(0,0));
    for(int i=newwidth;i<getRect().Size.Width;i++)
    rel_m.writeToMem(m_ReleaseImg,Point2D(i,0));
    rel_r.writeToMem(m_ReleaseImg,Point2D(m_ReleaseImg.Size.Width-newwidth,0));

    pr_l.writeToMem(m_PressImg,Point2D(0,0));
    for(int i=newwidth;i<getRect().Size.Width;i++)
    pr_m.writeToMem(m_PressImg,Point2D(i,0));
    pr_r.writeToMem(m_PressImg,Point2D(m_ReleaseImg.Size.Width-newwidth,0));

    getBitmap().copy(m_ReleaseImg);


}

void Button::setText(const char *con)
{

    int insetx=5;
    int insety=3;
    m_Writer.setOutput(m_ReleaseImg);
    m_Writer.writeInRect(con,Rect2D(Point2D(0,0),getRect().Size));
    m_Writer.setOutput(m_HoverImg);
    m_Writer.writeInRect(con,Rect2D(Point2D(0,0),getRect().Size));
    m_PressImg.fill(m_ReleaseImg,Rect2D(Point2D(insetx,insety),getRect().Size));
    getBitmap().copy(m_ReleaseImg);
}

void Button::setText(const wchar_t *con)
{
    int insetx=5;
    int insety=3;
    m_Writer.setOutput(m_ReleaseImg);
    m_Writer.writeInRect(con,Rect2D(Point2D(0,0),getRect().Size));
    m_Writer.setOutput(m_HoverImg);
    m_Writer.writeInRect(con,Rect2D(Point2D(0,0),getRect().Size));
    m_PressImg.fill(m_ReleaseImg,Rect2D(Point2D(insetx,insety),getRect().Size));
    getBitmap().copy(m_ReleaseImg);
}

void Button::LBUpEvent(Point2D LocalPos)
{
    if(IsPress())
        emitSignal(s_clicked);
    unsetPress();
    setChange();
    repaint();

}

void Button::LBDownEvent(Point2D LocalPos)
{
    setPress();
    setChange();
    repaint();

}
void Button::MouseLeaveEvent(Tile *leavefor)
{
    unsetPress();
    unsetHover();
    setChange();
    repaint();
}

void Button::MouseHoverEvent(Point2D LocalPos)
{
    setHover();
    setChange();
    repaint();
    //printf("MMM\n");
    //getBitmap().fill(RGBPixel(0,222,222));
  //  repaint();
}

void Button::TimerEvent(int id)
{
  //  printf("MMMM\n");
}

void Button::updateBitmap(Buffer2D<RGBPixel> &bfBitmap)
{
    if(IsPress())
       bfBitmap.copy(m_PressImg);
    else
       {
       if(!IsHover())
       bfBitmap.copy(m_ReleaseImg);
       else
           bfBitmap.copy(m_HoverImg);
       }
}

