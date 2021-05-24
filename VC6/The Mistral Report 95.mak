# Microsoft Developer Studio Generated NMAKE File, Based on The Mistral Report 95.dsp
!IF "$(CFG)" == ""
CFG=The Mistral Report 95 - Win32 Debug
!MESSAGE No configuration specified. Defaulting to The Mistral Report 95 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "The Mistral Report 95 - Win32 Release" && "$(CFG)" != "The Mistral Report 95 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "The Mistral Report 95.mak" CFG="The Mistral Report 95 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "The Mistral Report 95 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "The Mistral Report 95 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "The Mistral Report 95 - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\The Mistral Report 95.exe" "$(OUTDIR)\The Mistral Report 95.pch"


CLEAN :
	-@erase "$(INTDIR)\CGDIRenderer.obj"
	-@erase "$(INTDIR)\CPackedFileReader.obj"
	-@erase "$(INTDIR)\Crawler.obj"
	-@erase "$(INTDIR)\CreditsScreen.obj"
	-@erase "$(INTDIR)\CRenderer.obj"
	-@erase "$(INTDIR)\CRenderer_Rasterization.obj"
	-@erase "$(INTDIR)\CRenderer_Tesselation.obj"
	-@erase "$(INTDIR)\CTile3DProperties.obj"
	-@erase "$(INTDIR)\Dungeon.obj"
	-@erase "$(INTDIR)\EDirection_Utils.obj"
	-@erase "$(INTDIR)\Engine.obj"
	-@erase "$(INTDIR)\Events.obj"
	-@erase "$(INTDIR)\FixP.obj"
	-@erase "$(INTDIR)\GameMenu.obj"
	-@erase "$(INTDIR)\Globals.obj"
	-@erase "$(INTDIR)\HelpScreen.obj"
	-@erase "$(INTDIR)\Interrogation.obj"
	-@erase "$(INTDIR)\LoadBitmap.obj"
	-@erase "$(INTDIR)\Main.obj"
	-@erase "$(INTDIR)\MainMenu.obj"
	-@erase "$(INTDIR)\MapWithCharKey.obj"
	-@erase "$(INTDIR)\SpyTravel.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\The Mistral Report 95.pch"
	-@erase "$(INTDIR)\The Mistral Report 95.res"
	-@erase "$(INTDIR)\UI.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\Vec.obj"
	-@erase "$(INTDIR)\VisibilityStrategy.obj"
	-@erase "$(OUTDIR)\The Mistral Report 95.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "C:\the-mistral-report\the-mistral-report\base3d\include" /I "C:\the-mistral-report\the-mistral-report\menu\include" /I "C:\the-mistral-report\the-mistral-report\SoundSystem" /I "C:\the-mistral-report\the-mistral-report\Win32" /I "C:\the-mistral-report\the-mistral-report\The Mistral Report 95\\" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "MSVC" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x816 /fo"$(INTDIR)\The Mistral Report 95.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\The Mistral Report 95.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib shell32.lib winmm.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\The Mistral Report 95.pdb" /machine:I386 /out:"$(OUTDIR)\The Mistral Report 95.exe" 
LINK32_OBJS= \
	"$(INTDIR)\CGDIRenderer.obj" \
	"$(INTDIR)\CPackedFileReader.obj" \
	"$(INTDIR)\Crawler.obj" \
	"$(INTDIR)\CreditsScreen.obj" \
	"$(INTDIR)\CRenderer.obj" \
	"$(INTDIR)\CRenderer_Rasterization.obj" \
	"$(INTDIR)\CRenderer_Tesselation.obj" \
	"$(INTDIR)\CTile3DProperties.obj" \
	"$(INTDIR)\Dungeon.obj" \
	"$(INTDIR)\EDirection_Utils.obj" \
	"$(INTDIR)\Engine.obj" \
	"$(INTDIR)\Events.obj" \
	"$(INTDIR)\FixP.obj" \
	"$(INTDIR)\GameMenu.obj" \
	"$(INTDIR)\Globals.obj" \
	"$(INTDIR)\HelpScreen.obj" \
	"$(INTDIR)\Interrogation.obj" \
	"$(INTDIR)\LoadBitmap.obj" \
	"$(INTDIR)\Main.obj" \
	"$(INTDIR)\MainMenu.obj" \
	"$(INTDIR)\MapWithCharKey.obj" \
	"$(INTDIR)\SpyTravel.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\UI.obj" \
	"$(INTDIR)\Vec.obj" \
	"$(INTDIR)\VisibilityStrategy.obj" \
	"$(INTDIR)\The Mistral Report 95.res"

"$(OUTDIR)\The Mistral Report 95.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "The Mistral Report 95 - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\The Mistral Report 95.exe" "$(OUTDIR)\The Mistral Report 95.pch"


CLEAN :
	-@erase "$(INTDIR)\CGDIRenderer.obj"
	-@erase "$(INTDIR)\CPackedFileReader.obj"
	-@erase "$(INTDIR)\Crawler.obj"
	-@erase "$(INTDIR)\CreditsScreen.obj"
	-@erase "$(INTDIR)\CRenderer.obj"
	-@erase "$(INTDIR)\CRenderer_Rasterization.obj"
	-@erase "$(INTDIR)\CRenderer_Tesselation.obj"
	-@erase "$(INTDIR)\CTile3DProperties.obj"
	-@erase "$(INTDIR)\Dungeon.obj"
	-@erase "$(INTDIR)\EDirection_Utils.obj"
	-@erase "$(INTDIR)\Engine.obj"
	-@erase "$(INTDIR)\Events.obj"
	-@erase "$(INTDIR)\FixP.obj"
	-@erase "$(INTDIR)\GameMenu.obj"
	-@erase "$(INTDIR)\Globals.obj"
	-@erase "$(INTDIR)\HelpScreen.obj"
	-@erase "$(INTDIR)\Interrogation.obj"
	-@erase "$(INTDIR)\LoadBitmap.obj"
	-@erase "$(INTDIR)\Main.obj"
	-@erase "$(INTDIR)\MainMenu.obj"
	-@erase "$(INTDIR)\MapWithCharKey.obj"
	-@erase "$(INTDIR)\SpyTravel.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\The Mistral Report 95.pch"
	-@erase "$(INTDIR)\The Mistral Report 95.res"
	-@erase "$(INTDIR)\UI.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\Vec.obj"
	-@erase "$(INTDIR)\VisibilityStrategy.obj"
	-@erase "$(OUTDIR)\The Mistral Report 95.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX- /O2 /I "C:\the-mistral-report\the-mistral-report\base3d\include" /I "C:\the-mistral-report\the-mistral-report\menu\include" /I "C:\the-mistral-report\the-mistral-report\SoundSystem" /I "C:\the-mistral-report\the-mistral-report\Win32" /I "C:\the-mistral-report\the-mistral-report\The Mistral Report 95\\" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "MSVC" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\The Mistral Report 95.res" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\The Mistral Report 95.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib shell32.lib winmm.lib /nologo /subsystem:windows /pdb:none /machine:I386 /out:"$(OUTDIR)\The Mistral Report 95.exe" 
LINK32_OBJS= \
	"$(INTDIR)\CGDIRenderer.obj" \
	"$(INTDIR)\CPackedFileReader.obj" \
	"$(INTDIR)\Crawler.obj" \
	"$(INTDIR)\CreditsScreen.obj" \
	"$(INTDIR)\CRenderer.obj" \
	"$(INTDIR)\CRenderer_Rasterization.obj" \
	"$(INTDIR)\CRenderer_Tesselation.obj" \
	"$(INTDIR)\CTile3DProperties.obj" \
	"$(INTDIR)\Dungeon.obj" \
	"$(INTDIR)\EDirection_Utils.obj" \
	"$(INTDIR)\Engine.obj" \
	"$(INTDIR)\Events.obj" \
	"$(INTDIR)\FixP.obj" \
	"$(INTDIR)\GameMenu.obj" \
	"$(INTDIR)\Globals.obj" \
	"$(INTDIR)\HelpScreen.obj" \
	"$(INTDIR)\Interrogation.obj" \
	"$(INTDIR)\LoadBitmap.obj" \
	"$(INTDIR)\Main.obj" \
	"$(INTDIR)\MainMenu.obj" \
	"$(INTDIR)\MapWithCharKey.obj" \
	"$(INTDIR)\SpyTravel.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\UI.obj" \
	"$(INTDIR)\Vec.obj" \
	"$(INTDIR)\VisibilityStrategy.obj" \
	"$(INTDIR)\The Mistral Report 95.res"

"$(OUTDIR)\The Mistral Report 95.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("The Mistral Report 95.dep")
!INCLUDE "The Mistral Report 95.dep"
!ELSE 
!MESSAGE Warning: cannot find "The Mistral Report 95.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "The Mistral Report 95 - Win32 Release" || "$(CFG)" == "The Mistral Report 95 - Win32 Debug"
SOURCE=..\base3d\src\Win32Version\CGDIRenderer.c

"$(INTDIR)\CGDIRenderer.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\base3d\src\CPackedFileReader.c

"$(INTDIR)\CPackedFileReader.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\menu\src\Crawler.c

"$(INTDIR)\Crawler.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\menu\src\CreditsScreen.c

"$(INTDIR)\CreditsScreen.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\base3d\src\CRenderer.c

"$(INTDIR)\CRenderer.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\base3d\src\CRenderer_Rasterization.c

"$(INTDIR)\CRenderer_Rasterization.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\base3d\src\CRenderer_Tesselation.c

"$(INTDIR)\CRenderer_Tesselation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\base3d\src\CTile3DProperties.c

"$(INTDIR)\CTile3DProperties.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\base3d\src\Dungeon.c

"$(INTDIR)\Dungeon.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\base3d\src\EDirection_Utils.c

"$(INTDIR)\EDirection_Utils.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\menu\src\Engine.c

"$(INTDIR)\Engine.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\base3d\src\Events.c

"$(INTDIR)\Events.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\base3d\src\FixP.c

"$(INTDIR)\FixP.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\menu\src\GameMenu.c

"$(INTDIR)\GameMenu.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\base3d\src\Globals.c

"$(INTDIR)\Globals.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\menu\src\HelpScreen.c

"$(INTDIR)\HelpScreen.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\menu\src\Interrogation.c

"$(INTDIR)\Interrogation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\base3d\src\LoadBitmap.c

"$(INTDIR)\LoadBitmap.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\menu\src\Main.c

"$(INTDIR)\Main.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\menu\src\MainMenu.c

"$(INTDIR)\MainMenu.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\base3d\src\MapWithCharKey.c

"$(INTDIR)\MapWithCharKey.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\menu\src\SpyTravel.c

"$(INTDIR)\SpyTravel.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "The Mistral Report 95 - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "C:\the-mistral-report\the-mistral-report\base3d\include" /I "C:\the-mistral-report\the-mistral-report\menu\include" /I "C:\the-mistral-report\the-mistral-report\SoundSystem" /I "C:\the-mistral-report\the-mistral-report\Win32" /I "C:\the-mistral-report\the-mistral-report\The Mistral Report 95\\" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "MSVC" /Fp"$(INTDIR)\The Mistral Report 95.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\The Mistral Report 95.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "The Mistral Report 95 - Win32 Debug"

CPP_SWITCHES=/nologo /ML /W3 /GX- /O2 /I "C:\the-mistral-report\the-mistral-report\base3d\include" /I "C:\the-mistral-report\the-mistral-report\menu\include" /I "C:\the-mistral-report\the-mistral-report\SoundSystem" /I "C:\the-mistral-report\the-mistral-report\Win32" /I "C:\the-mistral-report\the-mistral-report\The Mistral Report 95\\" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "MSVC" /Fp"$(INTDIR)\The Mistral Report 95.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\The Mistral Report 95.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=".\The Mistral Report 95.rc"

"$(INTDIR)\The Mistral Report 95.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=..\menu\src\UI.c

"$(INTDIR)\UI.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\base3d\src\Vec.c

"$(INTDIR)\Vec.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\base3d\src\VisibilityStrategy.c

"$(INTDIR)\VisibilityStrategy.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

