#include "h2o_imagefile.h"
using namespace ColdWater;
ImageFile::ImageFile()
{
}

void ImageFile::read(const char *filename)
{
    FREE_IMAGE_FORMAT format=FreeImage_GetFileType(filename);
    m_hImage=FreeImage_Load(format,filename);

    m_Bits=FreeImage_GetBits(m_hImage);
   //
    m_Pitch=FreeImage_GetPitch(m_hImage);
    m_Height= FreeImage_GetHeight(m_hImage);
    m_Width=FreeImage_GetWidth(m_hImage);
    m_Depth=FreeImage_GetBPP(m_hImage);

}

void ImageFile::rescale(const Size2D size)
{
    m_hImage=FreeImage_Rescale(m_hImage,
                               size.Width,size.Height,FILTER_LANCZOS3);

    m_Bits=FreeImage_GetBits(m_hImage);
   //
    m_Pitch=FreeImage_GetPitch(m_hImage);
    m_Height= FreeImage_GetHeight(m_hImage);
    m_Width=FreeImage_GetWidth(m_hImage);
    m_Depth=FreeImage_GetBPP(m_hImage);
}

BYTE *ImageFile::get(int x,int y)
{
   BYTE *ret=m_Bits;
  // cout<<":::::"<<Width<<endl;
   x=x>=m_Width?(m_Width-1):x;
   y=y>=m_Height?(m_Height-1):y;
   if(x<0)x=0;
   if(y<0)y=0;
   ret+=y*m_Pitch+x*m_Depth/8;
   return ret;

}

void ImageFile::writeToMem(Buffer2D<RGBPixel> &Buff,const Point2D despos,
                           const Rect2D orirect)
{
   RGBPixel* pt;
   BYTE *pt1;
   for(int i=0;i<orirect.Size.Width;i++)
       for(int j=0;j<orirect.Size.Height;j++)
       {
          pt=Buff.get(i+despos.X,j+despos.Y);
          pt1=get(i+orirect.Pos1.X,j+orirect.Pos1.Y);
          if(pt&&pt1)
               memcpy(pt,pt1,sizeof(RGBPixel)) ;
       }
}

void ImageFile::writeToMem(Buffer2D<RGBPixel> &Buff, const Point2D despos)
{
    writeToMem(
                Buff,despos,
               Rect2D(Point2D(0,0),
                      Size2D(m_Width,m_Height))
               );
}
