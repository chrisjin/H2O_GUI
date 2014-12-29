#ifndef H2O_TEXTEDIT_H
#define H2O_TEXTEDIT_H
#include"h2o_widget.h"
#include"h2o_typewriter.h"
#include"h2o_font.h"
#include"h2o_timer.h"
namespace ColdWater
{
    class Timer;
    class Caret : public Widget
    {
    public:
        DEFCSTRCTOR(Caret,Widget)
        {

        }
    };
    class TextEdit : public Widget
    {
        bool m_IsShowCaret;
        Caret *m_Caret;
        TypeWriter *m_Writer;
        Font *m_Font;
        Timer *m_Timer;
        bool   m_IsPassWordEdit;
        wstring m_Con;
    public:
        wstring getCon(){return m_Con;}
        TextEdit();
        DEFCSTRCTOR(TextEdit,Widget)
        {
            m_IsPassWordEdit=0;
            setInset();
            m_IsShowCaret=0;
            getBitmap().fill(RGBPixel(255,255,255));
            m_Caret=new Caret(Point2D(2,0),Size2D(1,getRect().Size.Height));
            m_Caret->getBitmap().fill(RGBPixel(255,255,255));
            m_Caret->setHide();
            RGBPixel *rgb;
            for(int i=2;i<getRect().Size.Height-1;i++)
            {

                    rgb=m_Caret->getBitmap().get(0,i);
                    if(rgb)
                    rgb->c1=rgb->c2=rgb->c3=0;

            }

            addTile(m_Caret);


            m_Writer=new TypeWriter;
            m_Font=new Font;
            m_Font->createFont(getRect().Size.Height-4,0,
                               "C:/Windows/Fonts/simsun.ttc");
            m_Writer->setFont(m_Font);
            m_Writer->setCurPosition(2,3);
            m_Writer->setOutput(getBitmap());

            m_Timer=new Timer;
            m_Timer->setTimer(this,&TextEdit::flashCaret,500);
        }
		void clear();
        void setPassWordEdit(){m_IsPassWordEdit=1;}
        void flashCaret();
		void showText(const char* text);
		void showText(wstring text);
        virtual void GrabFocusEvent(Tile *);
        virtual void LoseFocusEvent(Tile* pre);
        virtual void TimerEvent(int id);
        void updateBitmap(Buffer2D<RGBPixel> &bfBitmap);
        virtual void ImeCharEvent(wchar_t a);
        virtual void CharEvent(unsigned int a);

    };
}
#endif // H2O_TEXTEDIT_H
