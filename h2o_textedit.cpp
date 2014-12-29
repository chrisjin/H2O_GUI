#include "h2o_textedit.h"
using namespace ColdWater;
TextEdit::TextEdit()
{
}

void TextEdit::flashCaret()
{

        if(!m_IsShowCaret)
            return;
        if(m_Caret->IsHide())
            m_Caret->unsetHide();
        else
            m_Caret->setHide();
        repaint();

}

void TextEdit::GrabFocusEvent(Tile *)
{
    m_Caret->unsetHide();
    if(!m_IsShowCaret)
    m_Timer->start();
    m_IsShowCaret=1;
    repaint();
}


void TextEdit::LoseFocusEvent(Tile *pre)
{
    m_IsShowCaret=0;
    if(m_IsShowCaret)
    m_Timer->stop();
    m_Caret->setHide();

    repaint();
}

void TextEdit::TimerEvent(int id)//obsolete
{
    if(id==TMID_TEXTEDIT)
    {
       // printf("ss\n");
        if(m_Caret->IsHide())
            m_Caret->unsetHide();
        else
            m_Caret->setHide();
        repaint();
    }
}

void TextEdit::updateBitmap(Buffer2D<RGBPixel> &bfBitmap)
{

}
void TextEdit::showText(const char* text)
{
    for(int i=0;i<strlen(text);i++)
	CharEvent(text[i]);
    setChange();
    repaint();
}

void TextEdit::showText(wstring text)
{
	for(int i=0;i<text.size();i++)
	ImeCharEvent(text[i]);
    setChange();
    repaint();
}

void TextEdit::ImeCharEvent(wchar_t a)
{
    if(a!=0x08)
    {
    wstring buff;
    buff.push_back(a);
    if(!m_IsPassWordEdit)
    m_Writer->write(buff.c_str());
    else
        m_Writer->write("*");
    m_Con.push_back(a);
    }
    else
    {
        m_Writer->backspace();
        if(m_Con.size()>=1)
        m_Con.erase(m_Con.end()-1);
    }
    m_Caret->setOri(Point2D(m_Writer->getCurX(),0));
    setChange();
    repaint();
}

void TextEdit::CharEvent(unsigned int a)
{
    if(a!=0x08)
    {
    char buff[5];
    sprintf(buff,"%c",a);
    if(!m_IsPassWordEdit)
        m_Writer->write(buff);
    else
        m_Writer->write("*");
    m_Con.push_back(a);
    }
    else
    {
        m_Writer->backspace();
        if(m_Con.size()>=1)
        m_Con.erase(m_Con.end()-1);
    }
    m_Caret->setOri(Point2D(m_Writer->getCurX(),0));
    setChange();
    repaint();
}

void TextEdit::clear()
{
	m_Writer->setCurPosition(2, 3);
	getBitmap().fill(RGBPixel(255, 255, 255));
	m_Caret->setOri(Point2D(m_Writer->getCurX(), 0));
}


