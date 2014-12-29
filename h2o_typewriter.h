#ifndef H2O_TYPEWRITER_H
#define H2O_TYPEWRITER_H
#include"h2o_interface.h"
#include<string>
#include"ft2build.h"
#include"h2o_font.h"
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include FT_BITMAP_H
#include FT_OUTLINE_H
namespace ColdWater
{
    using namespace std;
    class Font;
    class Letter;
    class FREETYPE
    {
    public:
        FREETYPE();
        static FT_Library Lib;
    };
    class LetterManager
    {
        vector<Letter*> m_LetterList;
        int m_LineNum;

        int m_CurX;
        int m_CurY;
    public:
        void pushLetter(Letter* letter);


    };
    class TypeWriter:public Object
    {
        Buffer2D<RGBPixel> m_OutputBuffer;
        int m_CurX;
        int m_CurY;
        int m_BegX;
        int m_BegY;
        int m_CurIndex;
        //FT_Face m_Face;
        Font *m_Font;
        wstring m_Con;
    public:
        TypeWriter();
        void setFont(Font *font);
        void setOutput(const Buffer2D<RGBPixel>& pbuffer);
        void setCurPosition(int x,int y);


        void moveCurPosition(int index);
        void write(const char* con);
        void write(const wchar_t* wcon);
        void write(Letter* letter,int size);
        void loadLetters(Letter* letter,const wchar_t* wcon);
        void writeInRect(const wchar_t *wcon,const Rect2D rect);
        void writeInRect(const char* con,const Rect2D rect);
        void newline();
        void backspace();
        int  getCurX(){return m_CurX;}
        wstring getCon(){return m_Con;}
    };
}
#endif // H2O_TYPEWRITER_H
