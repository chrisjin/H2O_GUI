#ifndef H2O_IMAGEFILE_H
#define H2O_IMAGEFILE_H
#include"h2o_file.h"
#include"h2o_tile.h"
#include"FreeImage/FreeImage.h"
namespace ColdWater
{
    class ImageFile:public File
    {
        int m_Width;
        int m_Height;
        FIBITMAP* m_hImage;
        BYTE *m_Bits;

        DWORD m_Pitch;
        DWORD m_Depth;
    public:
        ImageFile();
        int getWidth()
        {
            return m_Width;
        }
        int getHeight()
        {
            return m_Height;
        }
        void read(const char *filename);
        void rescale(const Size2D size);
        BYTE *get(int x, int y);
        void writeToMem(Buffer2D<RGBPixel> &Buff,const Point2D despos,const Rect2D orirect);
        void writeToMem(Buffer2D<RGBPixel> &Buff,const Point2D despos);
    };
}
#endif // H2O_IMAGEFILE_H
