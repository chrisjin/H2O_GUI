#############################################################################
# Makefile for building: H2O_Reconstruct
# Generated by qmake (2.01a) (Qt 4.7.4) on: ?? ?? 18 11:04:53 2013
# Project:  H2O_Reconstruct.pro
# Template: app
# Command: f:\qtsdk\desktop\qt\4.7.4\msvc2008\bin\qmake.exe -spec f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\win32-msvc2008 CONFIG+=release -o Makefile H2O_Reconstruct.pro
#############################################################################

first: release
install: release-install
uninstall: release-uninstall
MAKEFILE      = Makefile
QMAKE         = f:\qtsdk\desktop\qt\4.7.4\msvc2008\bin\qmake.exe
DEL_FILE      = del
CHK_DIR_EXISTS= if not exist
MKDIR         = mkdir
COPY          = copy /y
COPY_FILE     = $(COPY)
COPY_DIR      = xcopy /s /q /y /i
INSTALL_FILE  = $(COPY_FILE)
INSTALL_PROGRAM = $(COPY_FILE)
INSTALL_DIR   = $(COPY_DIR)
DEL_FILE      = del
SYMLINK       = 
DEL_DIR       = rmdir
MOVE          = move
CHK_DIR_EXISTS= if not exist
MKDIR         = mkdir
SUBTARGETS    =  \
		release \
		debug

release: $(MAKEFILE).Release FORCE
	$(MAKE) -f $(MAKEFILE).Release
release-make_default: $(MAKEFILE).Release FORCE
	$(MAKE) -f $(MAKEFILE).Release 
release-make_first: $(MAKEFILE).Release FORCE
	$(MAKE) -f $(MAKEFILE).Release first
release-all: $(MAKEFILE).Release FORCE
	$(MAKE) -f $(MAKEFILE).Release all
release-clean: $(MAKEFILE).Release FORCE
	$(MAKE) -f $(MAKEFILE).Release clean
release-distclean: $(MAKEFILE).Release FORCE
	$(MAKE) -f $(MAKEFILE).Release distclean
release-install: $(MAKEFILE).Release FORCE
	$(MAKE) -f $(MAKEFILE).Release install
release-uninstall: $(MAKEFILE).Release FORCE
	$(MAKE) -f $(MAKEFILE).Release uninstall
debug: $(MAKEFILE).Debug FORCE
	$(MAKE) -f $(MAKEFILE).Debug
debug-make_default: $(MAKEFILE).Debug FORCE
	$(MAKE) -f $(MAKEFILE).Debug 
debug-make_first: $(MAKEFILE).Debug FORCE
	$(MAKE) -f $(MAKEFILE).Debug first
debug-all: $(MAKEFILE).Debug FORCE
	$(MAKE) -f $(MAKEFILE).Debug all
debug-clean: $(MAKEFILE).Debug FORCE
	$(MAKE) -f $(MAKEFILE).Debug clean
debug-distclean: $(MAKEFILE).Debug FORCE
	$(MAKE) -f $(MAKEFILE).Debug distclean
debug-install: $(MAKEFILE).Debug FORCE
	$(MAKE) -f $(MAKEFILE).Debug install
debug-uninstall: $(MAKEFILE).Debug FORCE
	$(MAKE) -f $(MAKEFILE).Debug uninstall

Makefile: H2O_Reconstruct.pro  f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\win32-msvc2008\qmake.conf f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\qconfig.pri \
		f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\modules\qt_webkit_version.pri \
		f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\features\qt_functions.prf \
		f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\features\qt_config.prf \
		f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\features\exclusive_builds.prf \
		f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\features\default_pre.prf \
		f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\features\win32\default_pre.prf \
		f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\features\release.prf \
		f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\features\debug_and_release.prf \
		f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\features\default_post.prf \
		f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\features\win32\default_post.prf \
		f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\features\win32\rtti.prf \
		f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\features\win32\exceptions.prf \
		f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\features\win32\stl.prf \
		f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\features\shared.prf \
		f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\features\win32\embed_manifest_exe.prf \
		f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\features\win32\embed_manifest_dll.prf \
		f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\features\warn_on.prf \
		f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\features\qt.prf \
		f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\features\win32\thread.prf \
		f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\features\moc.prf \
		f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\features\win32\windows.prf \
		f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\features\resources.prf \
		f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\features\uic.prf \
		f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\features\yacc.prf \
		f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\features\lex.prf \
		f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\features\incredibuild_xge.prf \
		f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\features\include_source_dir.prf \
		f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\lib\qtmain.prl
	$(QMAKE) -spec f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\win32-msvc2008 CONFIG+=release -o Makefile H2O_Reconstruct.pro
f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\qconfig.pri:
f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\modules\qt_webkit_version.pri:
f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\features\qt_functions.prf:
f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\features\qt_config.prf:
f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\features\exclusive_builds.prf:
f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\features\default_pre.prf:
f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\features\win32\default_pre.prf:
f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\features\release.prf:
f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\features\debug_and_release.prf:
f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\features\default_post.prf:
f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\features\win32\default_post.prf:
f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\features\win32\rtti.prf:
f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\features\win32\exceptions.prf:
f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\features\win32\stl.prf:
f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\features\shared.prf:
f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\features\win32\embed_manifest_exe.prf:
f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\features\win32\embed_manifest_dll.prf:
f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\features\warn_on.prf:
f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\features\qt.prf:
f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\features\win32\thread.prf:
f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\features\moc.prf:
f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\features\win32\windows.prf:
f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\features\resources.prf:
f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\features\uic.prf:
f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\features\yacc.prf:
f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\features\lex.prf:
f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\features\incredibuild_xge.prf:
f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\features\include_source_dir.prf:
f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\lib\qtmain.prl:
qmake: qmake_all FORCE
	@$(QMAKE) -spec f:\QtSDK\Desktop\Qt\4.7.4\msvc2008\mkspecs\win32-msvc2008 CONFIG+=release -o Makefile H2O_Reconstruct.pro

qmake_all: FORCE

make_default: release-make_default debug-make_default FORCE
make_first: release-make_first debug-make_first FORCE
all: release-all debug-all FORCE
clean: release-clean debug-clean FORCE
	-$(DEL_FILE) ".\H2O_Reconstruct.intermediate.manifest"
	-$(DEL_FILE) H2O_Reconstruct.exp
distclean: release-distclean debug-distclean FORCE
	-$(DEL_FILE) Makefile

check: first

release-mocclean: $(MAKEFILE).Release
	$(MAKE) -f $(MAKEFILE).Release mocclean
debug-mocclean: $(MAKEFILE).Debug
	$(MAKE) -f $(MAKEFILE).Debug mocclean
mocclean: release-mocclean debug-mocclean

release-mocables: $(MAKEFILE).Release
	$(MAKE) -f $(MAKEFILE).Release mocables
debug-mocables: $(MAKEFILE).Debug
	$(MAKE) -f $(MAKEFILE).Debug mocables
mocables: release-mocables debug-mocables
FORCE:

$(MAKEFILE).Release: Makefile
$(MAKEFILE).Debug: Makefile
