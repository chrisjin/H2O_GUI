#include "h2o_gifplayer.h"
using namespace ColdWater;
void GIFPlayer::init()
{
    m_CurrentFrame=0;
    m_FrameNum=0;
    unsetMouseTrigger();
    setSpeed(100);
    initTimer();
}

void GIFPlayer::TimerEvent(int id)//obsolete
{
//    //printf("mm mmmm\n");
//    if(id==TMID_GIFPLAYER)
//    {
//        //printf("mm mmmm%d\n",m_CurrentFrame);
//        if(m_CurrentFrame<m_FrameNum-1)
//        m_CurrentFrame++;
//        else
//           m_CurrentFrame=0;
//        setChange();
//        repaint();
//    }
}

void GIFPlayer::CreateEvent()
{
   // printf("CCC\n");
   // start();
}
void GIFPlayer::clear()
{
    for(int i=0;i<m_FrameList.size();i++)
	{
	    delete m_FrameList[i];
	}
	m_FrameList.clear();
	m_CurrentFrame=0;
    m_FrameNum=0;
}
bool GIFPlayer::loadGIF(const char *filename, int xx, int yy)
{
    FreeImage_Initialise();


    FREE_IMAGE_FORMAT format
            =FreeImage_GetFileType(filename);
    FIMULTIBITMAP* pGIFImage
            =FreeImage_OpenMultiBitmap(format,filename,
                                                       0,1,0,
                                                       GIF_PLAYBACK);
    m_FrameNum
            =FreeImage_GetPageCount(pGIFImage);


    for(int i=0;i<m_FrameNum;i++)
    {
        Buffer2D<RGBPixel>* pbuffer2d=new Buffer2D<RGBPixel>;
        FIBITMAP* frame,*frame0;
        frame0=FreeImage_LockPage(pGIFImage,i);
        int Width0 =FreeImage_GetWidth(frame0);
        int Height0=FreeImage_GetHeight(frame0);
		if (frame0 == 0)
			return 0;
        switch(m_ShowType)
        {
            case ST_FIXED:
                frame=frame0;
                pbuffer2d->Alloc(getRect().Size);
            break;
            case ST_FULL:
                frame=frame0;
                pbuffer2d->Alloc(Size2D(Width0,Height0));
                setSize(Size2D(Width0,Height0));
            break;

            case ST_STRETCH:
                frame=FreeImage_Rescale(frame0,
                                        getRect().Size.Width,
                                        getRect().Size.Height,
                                        FILTER_LANCZOS3);
                pbuffer2d->Alloc(getRect().Size);
            break;
        }
        int width=FreeImage_GetWidth(frame);
        int height=FreeImage_GetHeight(frame);

        int Pitch=FreeImage_GetPitch(frame);
        int Depth=FreeImage_GetBPP(frame);

        BYTE* Bits=FreeImage_GetBits(frame);


        BYTE pixelindex;
        RGBPixel* prgb;
        for(int x=0;x<width;x++)
            for(int y=0;y<height;y++)
            {

                prgb=pbuffer2d->get((x+xx),height-1-(y+yy));
                BYTE* loca=Bits+y*Pitch+x*Depth/8;
                if(!prgb)continue;
                prgb->c1=loca[0];
                prgb->c2=loca[1];
                prgb->c3=loca[2];
                prgb->c4=loca[3];


            }
        //prgb=pbuffer2d->get(55,55);


        m_FrameList.push_back(pbuffer2d);

        FreeImage_UnlockPage(pGIFImage,frame0,1);
    }
    //FreeImage_DeInitialise();
	setChange();
    repaint();

	return true;
}



void GIFPlayer::playFrame()
{

    if(m_CurrentFrame<m_FrameNum-1)
    m_CurrentFrame++;
    else
       m_CurrentFrame=0;
    setChange();
    repaint();
}

void GIFPlayer::updateBitmap(Buffer2D<RGBPixel> &bfBitmap)
{
    if(m_CurrentFrame<m_FrameList.size())
    bfBitmap=*m_FrameList[m_CurrentFrame];
    else
        bfBitmap.fill(RGBPixel(255,0,0));
}
