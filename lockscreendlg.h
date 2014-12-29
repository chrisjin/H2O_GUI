#ifndef LOCKSCREENDLG_H
#define LOCKSCREENDLG_H
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
class LockScreenDlg:public Widget
{
public:
    TextEdit* Input;
    Button  * ConfirmBtn;
    HWND     hTray;
    HWND     hStart;
    DEFCSTRCTOR(LockScreenDlg,Widget)
    {
        Input=new TextEdit(Point2D(20,200),Size2D(800,20));
        ConfirmBtn=new Button(Point2D(20,300),Size2D(50,30));
        ConfirmBtn->setText("确定");
        getBitmap().fill(RGBPixel(0,255,255));
        Input->setPassWordEdit();
        this->addTile(Input);
        this->addTile(ConfirmBtn);
        ConfirmBtn->connect(Button::s_clicked,this,&LockScreenDlg::CheckPass);
        hTray = FindWindowExA(0,0,"shell_TrayWnd", "");
        hStart =FindWindowExA(hTray, 0, "Button", "");
        ShowWindow(hTray,0);
        ShowWindow(hStart,SW_HIDE);
        UpdateWindow(hStart);

        FILE *fp=fopen("config","r");
        char con[50];
        fscanf(fp,"%s",con);
        fclose(fp);

        int width = GetSystemMetrics ( SM_CXSCREEN );
        int height= GetSystemMetrics ( SM_CYSCREEN );
        ImageFile Image;
        Image.read(con);
        Image.rescale(Size2D(width,height));
        Image.writeToMem(getBitmap(),Point2D(0,0));

    }

    void CheckPass()
    {
        FILE *fp=fopen("password","r");
        char con[50];
        if(fp==0)
        {
            MessageBoxA(0,"文件未找到","文件未找到",MB_OK);
            exit(0);
        }
        fscanf(fp,"%s",con);
        fclose(fp);
        wchar_t *wcon=new wchar_t[strlen(con)+10];
        memset(wcon,0,strlen(con)+10);
        MultiByteToWideChar(CP_ACP,0,con,strlen(con),wcon,strlen(con)+10);
        if(wcon==Input->getCon())
        {
        MessageBoxA(0,"密码正确","密码正确",MB_OK);
        ShowWindow(hTray,SW_SHOW);
        ShowWindow(hStart,SW_SHOW);

        typedef int (*unhook)();
        HINSTANCE hUser = LoadLibraryA("mousehook.dll");
        int k=(int)GetProcAddress(hUser, "UnHook");
        unhook unho=(unhook)k;
        unho();

        exit(0);
        }
        else
        {
        MessageBoxA(0,"密码错误","密码错误",MB_OK);
        }
    }
};

#endif // LOCKSCREENDLG_H
