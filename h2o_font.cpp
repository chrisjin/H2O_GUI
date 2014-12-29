#include "h2o_font.h"
using namespace ColdWater;
Font::Font()
{
}

void Font::createFont(int width, int height, const char *fontfile)
{
    int error=FT_New_Face(FREETYPE::Lib,fontfile,0,&m_Face);
    if(error)
    {
        printf("Error,FreeType Failed\n");
    }
    m_Width=width;
    m_Height=height;
    FT_Select_Size(m_Face,5);
    FT_Set_Pixel_Sizes(m_Face,width,height);
    FT_Select_Charmap(m_Face,FT_ENCODING_UNICODE);


    if(width<25)
    m_LoadParam=FT_LOAD_MONOCHROME|FT_LOAD_NO_AUTOHINT|FT_LOAD_RENDER;
    else
        m_LoadParam=FT_LOAD_DEFAULT|FT_LOAD_RENDER|FT_LOAD_FORCE_AUTOHINT;
}

void Font::createFont(int width, int height)
{
    createFont(width,height,"C:/Windows/Fonts/simsun.ttc");
}

void Letter::load(Font *font, wchar_t letter)
{
    m_Font=font;
    unsigned short LoadParam=m_Font->getLoadParam();
    FT_Face Face=m_Font->getFace();
    FT_Get_Char_Index(Face,letter);
    FT_Load_Char(Face,letter,
                 LoadParam);
    FT_Get_Glyph(Face->glyph, &m_Glyph );

    /////²ÎÊý
    if((LoadParam|FT_LOAD_MONOCHROME)==LoadParam)
        m_IsMono=1;
    else
        m_IsMono=0;
    if((LoadParam|FT_LOAD_RENDER)!=LoadParam)
    {
        if((LoadParam|FT_LOAD_MONOCHROME)==LoadParam)
            FT_Glyph_To_Bitmap( &m_Glyph, FT_RENDER_MODE_MONO, 0, 1 );
        else
            FT_Glyph_To_Bitmap( &m_Glyph, FT_RENDER_MODE_NORMAL, 0, 1 );
    }

   //  printf("KKKK%d\n",(FT_LOAD_DEFAULT|FT_LOAD_RENDER|FT_LOAD_MONOCHROME)!=(FT_LOAD_DEFAULT|FT_LOAD_RENDER));

    FT_BitmapGlyph bitmap_glyph=(FT_BitmapGlyph)m_Glyph;
    m_Bitmap=bitmap_glyph->bitmap;
    //FT_Bitmap_Embolden(FREETYPE::Lib,&m_Bitmap,1*64,1*64);
    /////³ß´ç
    int BaseLinePos=(int)(Face->size->metrics.ascender>>6);
    int HeightOnBaseLine=(int)(Face->glyph->metrics.horiBearingY>>6);

    int xoff=Face->glyph->metrics.horiBearingX>>6;
    int yoff=BaseLinePos-HeightOnBaseLine;

    ModeSize.Width=Face->glyph->advance.x>>6;
    ModeSize.Height=(Face->size->metrics.ascender>>6)-
                        (Face->size->metrics.descender>>6);
    Offset.Width=xoff;
    Offset.Height=yoff;

    BitmapSize.Width=m_Bitmap.width;
    BitmapSize.Height=m_Bitmap.rows;
    Character=letter;
   // m_Glyph=glyph;

}

void Letter::destroy()
{
    //FT_Bitmap_Done(FREETYPE::Lib,&m_Bitmap);
    FT_Done_Glyph(m_Glyph);
}





