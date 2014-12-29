#include "h2o_typewriter.h"
using namespace ColdWater;
FT_Library FREETYPE::Lib;
TypeWriter::TypeWriter()
{
    m_Font=0;
}

void TypeWriter::setFont(Font *font)
{
    m_Font=font;
}





void TypeWriter::setOutput(const Buffer2D<RGBPixel> &pbuffer)
{
    m_OutputBuffer=pbuffer;
}

void TypeWriter::setCurPosition(int x, int y)
{
    m_CurX=x;
    m_CurY=y;
    m_BegX=x;
    m_BegY=y;
    m_Con.clear();
    m_CurIndex=0;
}

void TypeWriter::moveCurPosition(int index)
{
    if(index>=0&&index<m_Con.length())
        m_CurIndex=index;
}

void TypeWriter::write(const char *con)
{



    wchar_t *wcon=new wchar_t[strlen(con)+10];
    memset(wcon,0,strlen(con)+10);
    MultiByteToWideChar(CP_ACP,0,con,strlen(con),wcon,strlen(con)+10);
    write(wcon);

    delete wcon;

}

void TypeWriter::write(const wchar_t *wcon)
{
    FT_Face Face;
    if(!m_Font)
        return;
    Face=m_Font->getFace();

    int wlength=wcslen(wcon);

    Letter *letters=new Letter[wlength];
    loadLetters(letters,wcon);
    write(letters,wlength);
    for(int i=0;i<wlength;i++)
    {
        letters[i].destroy();
    }
}

void TypeWriter::write(Letter *letters, int size)
{
    for(int i=0;i<size;i++)
    {
        m_Con.push_back(letters[i].Character);
    }
    int wlength=size;
    m_CurIndex+=wlength;
    for(int i=0;i<wlength;i++)
    {
        //Letter aletter=letters[i];
        //aletter.load(m_Font,wcon[i]);
        int xoff=letters[i].Offset.Width;
        int yoff=letters[i].Offset.Height;
        for(int x=0;x<letters[i].BitmapSize.Width;x++)
            for(int y=0;y<letters[i].BitmapSize.Height;y++)
            {
                 RGBPixel* rgb=m_OutputBuffer.get(m_CurX+xoff+x,
                                                  m_CurY+yoff+y);
                 if(!rgb)continue;

                 unsigned char flag=letters[i].getPixel(x,y);
                 rgb->c1=(255-flag)/255*rgb->c1;
                 rgb->c2=(255-flag)/255*rgb->c2;
                 rgb->c3=(255-flag)/255*rgb->c3;


            }

        m_CurX+=letters[i].ModeSize.Width;

    }
}

void TypeWriter::loadLetters(Letter *letter, const wchar_t *wcon)
{
    int wlength=wcslen(wcon);
    for(int i=0;i<wlength;i++)
    {
        letter[i].load(m_Font,wcon[i]);
    }
}

void TypeWriter::writeInRect(const wchar_t *wcon, const Rect2D rect)
{
    int wlength=wcslen(wcon);
    Letter *letters=new Letter[wlength];
    loadLetters(letters,wcon);
    int length=0;
    int width=0;
    for(int i=0;i<wlength;i++)
    {
        length+=letters[i].ModeSize.Width;
    }
    width=letters[0].ModeSize.Width;

    int posx=rect.Pos1.X+((double)rect.Size.Width-(double)length)/(double)2;
    int posy=rect.Pos1.Y+((double)rect.Size.Height-(double)width)/(double)2;

    setCurPosition(posx,posy);
    write(letters,wlength);
    for(int i=0;i<wlength;i++)
    {
        letters[i].destroy();
    }
}

void TypeWriter::writeInRect(const char *con, const Rect2D rect)
{
    wchar_t *wcon=new wchar_t[strlen(con)+10];
    memset(wcon,0,strlen(con)+10);
    MultiByteToWideChar(CP_ACP,0,con,strlen(con),wcon,strlen(con)+10);
    writeInRect(wcon,rect);

    delete wcon;
}

void TypeWriter::newline()
{
    FT_Face Face;
    if(!m_Font)
        return;
    Face=m_Font->getFace();
    m_CurY+=(Face->size->metrics.ascender>>6)+10;
    m_CurX=m_BegX;
}

void TypeWriter::backspace()
{
    if(!m_CurIndex)
        return;
    FT_Face Face;
    if(!m_Font)
        return;
    Face=m_Font->getFace();
    FT_UInt cindex=FT_Get_Char_Index(Face,m_Con[m_CurIndex-1]);


    FT_Load_Glyph(Face,cindex,FT_LOAD_MONOCHROME|FT_LOAD_RENDER);

    FT_Glyph glyph;
    FT_Get_Glyph(Face->glyph, &glyph );
    FT_Glyph_To_Bitmap( &glyph, FT_RENDER_MODE_MONO, 0, 1 );
    FT_BitmapGlyph bitmap_glyph=(FT_BitmapGlyph)glyph;
    FT_Bitmap bitmap=bitmap_glyph->bitmap;
    //FT_Done_Glyph(glyph);
    m_CurX-=(Face->glyph->advance.x>>6);
    if(m_Con.length())
    m_Con.erase(m_Con.end()-1);
    m_CurIndex--;

    int BaseLinePos=(int)(Face->size->metrics.ascender>>6);
    int HeightOnBaseLine=(int)(Face->glyph->metrics.horiBearingY>>6);
    int xoff=Face->glyph->metrics.horiBearingX>>6;
    int yoff=BaseLinePos-HeightOnBaseLine;

    for(int x=0;x<Face->glyph->advance.x+1;x++)
        for(int y=0;y<(Face->size->metrics.ascender>>6)-
            (Face->size->metrics.descender>>6);y++)
        {
             RGBPixel* rgb=m_OutputBuffer.get(m_CurX+xoff+x,
                                              m_CurY+yoff+y);
             if(!rgb)continue;
             rgb->c1=255;
             rgb->c2=255;
             rgb->c3=255;
        }

}


FREETYPE::FREETYPE()
{
    int error=FT_Init_FreeType(&Lib);
    if(error)
    {
        printf("Error,FreeType Init Failed\n");
    }
}
FREETYPE GLOBAL_Init_FreeType;

void LetterManager::pushLetter(Letter *letter)
{
}



