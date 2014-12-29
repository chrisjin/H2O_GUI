#ifndef WRONGPSWDLG_H
#define WRONGPSWDLG_H
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
class WrongPswDlg:public Widget
{
public:
    WrongPswDlg();
    Button  * ConfirmBtn;
    DEFCSTRCTOR(WrongPswDlg,Widget)
    {

    }
};

#endif // WRONGPSWDLG_H
