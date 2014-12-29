#ifndef H2O_FONT_H
#define H2O_FONT_H
#include"H2O_Delegate.h"
#include"ft2build.h"
#include"h2o_typewriter.h"
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include FT_BITMAP_H
namespace ColdWater
{

    class Font : public Object
    {
        int m_Width;
        int m_Height;
        FT_Face m_Face;
        unsigned short m_LoadParam;
    public:

        Font();
        void createFont(int width,int height,const char* fontfile);
        void createFont(int width,int height);
        inline FT_Face getFace()
        {
            return m_Face;
        }
        inline unsigned short getLoadParam()
        {
            return m_LoadParam;
        }

    };
    class Letter
    {
        Font *m_Font;
        FT_Bitmap m_Bitmap;
        FT_Glyph m_Glyph;
        bool m_IsMono;
    public:
        wchar_t Character;
        Size2D ModeSize;
        Size2D BitmapSize;
        Size2D Offset;
        Point2D Position;


        void load(Font* font,wchar_t letter);
        inline unsigned char getPixel(int x,int y)
        {
            if(m_IsMono)
            return (((m_Bitmap.buffer[(x>>3)+y*m_Bitmap.pitch])<<(x%8))&0x80)?255:0;
            else
                return m_Bitmap.buffer[x+y*m_Bitmap.pitch];
        }
        void destroy();
    };
}
#endif // H2O_FONT_H
