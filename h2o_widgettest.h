#ifndef H2O_WIDGETTEST_H
#define H2O_WIDGETTEST_H
#include"H2O_Widget.h"
#include"H2O_Button.h"
#include"H2O_DragTile.h"
#include"h2o_gifplayer.h"
#include"ft2build.h"
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include FT_BITMAP_H
#include"h2o_typewriter.h"
#include"h2o_font.h"
#include"h2o_textedit.h"
#include"h2o_captionscreen.h"
using namespace ColdWater;
class WidgetTest:public Widget
{
public:
    Button* innerbt;
    Button* stpbt;

    Button* warbt;
    Widget* another;
    DragTile* dragtile;
    GIFPlayer* gifplayer;
    GIFPlayer* gifplayer1;
    GIFPlayer* gifplayer2;
    CaptionScreen *capscreen;
    TextEdit* textedit;
    TextEdit* textedit1;
    Timer tm;
    int flag;
    FT_Face Face;
    TypeWriter type;
    DEFCSTRCTOR(WidgetTest,Widget)
    {
       innerbt=new Button(Point2D(60,60),Size2D(60,50));
       //innerbt->setText("È·¶¨");
       innerbt->setText("开始");

       stpbt=new Button(Point2D(200,30),Size2D(60,50));
       another=new Widget(Point2D(0,0),getRect().Size);
       dragtile=new DragTile(Point2D(100,100),Size2D(60,60));
       gifplayer=new GIFPlayer(Point2D(200,100),Size2D(80,80));
       gifplayer1=new GIFPlayer(Point2D(300,100),Size2D(160,160));
       gifplayer2=new GIFPlayer(Point2D(0,0));
       textedit=new TextEdit(Point2D(20,200),Size2D(800,20));
       textedit1=new TextEdit(Point2D(20,250),Size2D(800,25));
       warbt=new Button(Point2D(550,0),2);
       capscreen=new CaptionScreen(Point2D(0,0),getRect().Size);
       gifplayer->loadGIF("src/BTNSpellBreaker.gif");
       gifplayer1->loadGIF("src/test.gif");
        gifplayer2->loadGIF("src/measure_speed_wait.gif");
       //dragtile->addTile(gifplayer2);

       another->addTile(innerbt);
      // another->addTile(dragtile);
       addTile(innerbt);
       addTile(stpbt);
       addTile(gifplayer);
        addTile(gifplayer1);
       addTile(dragtile);
       addTile(textedit);
       addTile(textedit1);
       addTile(warbt);
       //addTile(capscreen);
       dragtile->addTile(gifplayer2);

       innerbt->connect(Button::s_clicked,this,&WidgetTest::alert);
       stpbt->connect(Button::s_clicked,this,&WidgetTest::stop);

       tm.setTimer(this,&WidgetTest::show,50);



       getBitmap().fill(RGBPixel(0,255,255));
       //type.init();
       Font *font=new Font;
       font->createFont(14,14,"C:/Windows/Fonts/simsun.ttc");


       type.setFont(font);
       type.setCurPosition(400,10);
       type.setOutput(getBitmap());
       type.write("×òÒ¹ÐÇ³½×òÒ¹·ç");
       type.newline();
       type.write("»­Â¥Î÷ÅÏ¹ðÌÃ¶«");
       type.newline();
       type.write("ÉíÎÞ²Ê·ïË«·ÉÒí");
       type.newline();
       type.write("ÐÄÓÐÁéÏ¬Ò»µãÍ¨");
       type.newline();
       type.write("¸ô×ùËÍ¹³´º¾ÆÅ¯");
       type.newline();
       type.write("·Ö²ÜÉä¸²À¯µÆºì");
       type.newline();
       type.write("àµÓàÌý¹ÄÓ¦¹ÙÈ¥");
       type.newline();
       type.write("×ßÂíÀ¼Ì¨Àà×ªÅî");
    }
    void show()
    {
         //printf("ssss\n");

        type.write("?");
        repaint();
    }
    void stop()
    {
        MessageBox(0,textedit->getCon().c_str(),textedit->getCon().c_str(),MB_OK);
         tm.stop();
    }
    void alert()
    {
       //MessageBoxA(0,"sss","sss",MB_OK);

        //Timer::setTimeOutFunc(this,&WidgetTest::show);
        tm.start();
        //gifplayer->start();
      //innerbt->setHide();
    }

    virtual void MouseEnterEvent(Tile* leavefrom)
    {


    }
    virtual void CreateEvent()
    {
        capscreen->setSpeed(10);
        capscreen->initTimer();
        capscreen->start();
        gifplayer2->start();
        gifplayer1->start();
        gifplayer->start();
    }
    virtual void MouseLeaveEvent(Tile* leavefor)
    {
        //gifplayer->stop();
    }

    //virtual void updateBitmap(Buffer2D<RGBPixel>& bfBitmap);
};

#endif // H2O_WIDGETTEST_H
