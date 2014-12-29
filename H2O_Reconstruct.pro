QT       += core gui
CONFIG   -= console
TEMPLATE = app
CONFIG += release
INCLUDEPATH+="./FreeType/include"
LIBS   += -lgdi32 -lkernel32 -luser32  -lmsimg32 -lwinmm\
        -L"./FreeImage" -lfreeimage \
        -L"./FreeType"  -lfreetype

SOURCES += main.cpp \
    h2o_tile.cpp \
    h2o_painter.cpp \
    h2o_widget.cpp \
    h2o_interface.cpp \
    h2o_gdipainter.cpp \
    h2o_button.cpp \
    h2o_application.cpp \
    h2o_widgettest.cpp \
    h2o_dragtile.cpp \
    h2o_timer.cpp \
    h2o_gifplayer.cpp \
    h2o_typewriter.cpp \
    h2o_font.cpp \
    h2o_textedit.cpp \
    h2o_animation.cpp \
    h2o_captionscreen.cpp \
    h2o_file.cpp \
    h2o_imagefile.cpp \
    gamepanel.cpp \
    h2o_buffer2dabstract.cpp \
    h2o_lockscreen.cpp \
    lockscreendlg.cpp \
    wrongpswdlg.cpp \
    widgettest2.cpp

HEADERS += \
    H2O_Delegate.h \
    H2O_Lings.h \
    h2o_tile.h \
    h2o_painter.h \
    h2o_widget.h \
    h2o_interface.h \
    h2o_gdipainter.h \
    h2o_button.h \
    h2o_application.h \
    h2o_widgettest.h \
    h2o_dragtile.h \
    h2o_timer.h \
    h2o_gifplayer.h \
    h2o_typewriter.h \
    h2o_font.h \
    h2o_textedit.h \
    h2o_animation.h \
    h2o_captionscreen.h \
    h2o_file.h \
    h2o_imagefile.h \
    gamepanel.h \
    h2o_buffer2dabstract.h \
    h2o_lockscreen.h \
    lockscreendlg.h \
    wrongpswdlg.h \
    widgettest2.h

OTHER_FILES += \
    note.txt

