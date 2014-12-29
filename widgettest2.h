#ifndef WIDGETTEST2_H
#define WIDGETTEST2_H


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
class Dialog :public Widget
{
public:
	DEFCSTRCTOR(Dialog, Widget)
	{
		getBitmap().fill(RGBPixel(0, 0, 255));
	}
};
class WidgetTest :public Widget
{
public:
	Button* innerbt;
	Button* stpbt;
	Button* conformbtn;
	Button* warbt;
	Widget* another;
	DragTile* dragtile;
	GIFPlayer* gifplayer;
	//GIFPlayer* gifplayer1;
	//GIFPlayer* gifplayer2;
	CaptionScreen *capscreen;
	TextEdit* textedit;
	//TextEdit* textedit1;
	Timer tm;
	int flag;
	FT_Face Face;

	DEFCSTRCTOR(WidgetTest, Widget)
	{
		int bottom = getRect().Size.Height;
		innerbt = new Button(Point2D(60, 30), Size2D(80, 40));
		innerbt->setText("Play");

		stpbt = new Button(Point2D(200, 30), Size2D(80, 40));
		stpbt->setText("Stop");
		

		//Dialog *dlg=new Dialog(Point2D(700,150),Size2D(200,100));
		//another=new Widget(Point2D(0,0),getRect().Size);
		dragtile = new DragTile(Point2D(50, 150), Size2D(60, 60));
		gifplayer = new GIFPlayer(Point2D(0,0));
		//gifplayer1 = new GIFPlayer(Point2D(340, 0));
		//gifplayer2 = new GIFPlayer(Point2D(0, 0));
		textedit = new TextEdit(Point2D(20, 100), Size2D(750, 20));
		textedit->showText("Hello!This is an edit control!");
		conformbtn = new Button(Point2D(790, 100), Size2D(80, 20));
		conformbtn->setText("Browse");


		//textedit1 = new TextEdit(Point2D(20, 250), Size2D(800, 25));
		//warbt=new Button(Point2D(550,0),2);
		capscreen = new CaptionScreen(Point2D(0, 0), getRect().Size);
		gifplayer->loadGIF("src/BTNSpellBreaker.gif");

		//gifplayer1->loadGIF("src/k.gif");
		//gifplayer2->loadGIF("src/measure_speed_wait.gif");
		//gifplayer2->setHide();
		//dragtile->addTile(gifplayer2);

		//another->addTile(innerbt);
		// another->addTile(dragtile);
		addTile(innerbt);
		addTile(stpbt);
		addTile(gifplayer);
		//addTile(gifplayer1);
		addTile(dragtile);
		addTile(textedit);
		//addTile(textedit1);
		addTile(conformbtn);
		//addTile(warbt);
		//addTile(dlg);
		//addTile(capscreen);
		dragtile->addTile(gifplayer);

		innerbt->connect(Button::s_clicked, this, &WidgetTest::show);
		stpbt->connect(Button::s_clicked, this, &WidgetTest::stop);
		conformbtn->connect(Button::s_clicked, this, &WidgetTest::pressconfirm);
		//tm.setTimer(this,&WidgetTest::show,50);


		for (int i = 0; i < getBitmap().getHeight();i++)
			getBitmap().fillLine(RGBPixel(255-i/2, 255-i/3, 255-i/2),i);
		//type.init();
		Font *font = new Font;
		font->createFont(14, 14, "C:/Windows/Fonts/simsun.ttc");


		//type.setFont(font);
		//type.setCurPosition(400, 10);
		//type.setOutput(getBitmap());


	}
	void pressconfirm()
	{
		OPENFILENAMEA ofn;       // common dialog box structure
		char szFile[MAX_PATH];       // buffer for file name

		memset(szFile, 0, 10);
		// Initialize OPENFILENAME
		ZeroMemory(&ofn, sizeof(OPENFILENAME));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = Interface::getWnd(this);
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrFilter = "All\0*.*\0Text\0*.TXT\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
		GetOpenFileNameA(&ofn);
		//repaint();
		//if (GetOpenFileNameW(&ofn)==TRUE) 

		//{
		////textedit1->showText(ofn.lpstrFile);
		//
		////gifplayer->setChange();
		////setChange();
		//      //repaint();
		//}
		gifplayer->clear();
		if (0 == gifplayer->loadGIF(szFile))
		{
			MessageBoxA(0,"Not GIF!","Error",MB_OK);
		}
		//dragtile->setRect(dragtile->getRect().Pos1,gifplayer->getRect().Size);
		//dragtile->repaint();
		textedit->clear();
		textedit->showText(szFile);
		//MessageBox(0,textedit->getCon().c_str(),textedit->getCon().c_str(),MB_OK);
	}
	void show()
	{

		gifplayer->start();
	}
	void stop()
	{

		gifplayer->stop();
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

	}
	virtual void MouseLeaveEvent(Tile* leavefor)
	{
		//gifplayer->stop();
	}

	//virtual void updateBitmap(Buffer2D<RGBPixel>& bfBitmap);
};
#endif // WIDGETTEST2_H
