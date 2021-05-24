# Microsoft Developer Studio Project File - Name="The Mistral Report 95" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=The Mistral Report 95 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "The Mistral Report 95.mak".
!MESSAGE 
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

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "The Mistral Report 95 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "C:\the-mistral-report\the-mistral-report\base3d\include" /I "C:\the-mistral-report\the-mistral-report\menu\include" /I "C:\the-mistral-report\the-mistral-report\SoundSystem" /I "C:\the-mistral-report\the-mistral-report\Win32" /I "C:\the-mistral-report\the-mistral-report\The Mistral Report 95\\" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "MSVC" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x816 /d "NDEBUG"
# ADD RSC /l 0x816 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib shell32.lib winmm.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "The Mistral Report 95 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /ML /W3 /GX- /O2 /I "C:\the-mistral-report\the-mistral-report\base3d\include" /I "C:\the-mistral-report\the-mistral-report\menu\include" /I "C:\the-mistral-report\the-mistral-report\SoundSystem" /I "C:\the-mistral-report\the-mistral-report\Win32" /I "C:\the-mistral-report\the-mistral-report\The Mistral Report 95\\" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "MSVC" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /mktyplib203 /win32
# ADD BASE RSC /l 0x816 /d "_DEBUG"
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib shell32.lib winmm.lib /nologo /subsystem:windows /pdb:none /machine:I386

!ENDIF 

# Begin Target

# Name "The Mistral Report 95 - Win32 Release"
# Name "The Mistral Report 95 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\base3d\src\Win32Version\CGDIRenderer.c
# End Source File
# Begin Source File

SOURCE=..\base3d\src\CPackedFileReader.c
# End Source File
# Begin Source File

SOURCE=..\menu\src\Crawler.c
# End Source File
# Begin Source File

SOURCE=..\menu\src\CreditsScreen.c
# End Source File
# Begin Source File

SOURCE=..\base3d\src\CRenderer.c
# End Source File
# Begin Source File

SOURCE=..\base3d\src\CRenderer_Rasterization.c
# End Source File
# Begin Source File

SOURCE=..\base3d\src\CRenderer_Tesselation.c
# End Source File
# Begin Source File

SOURCE=..\base3d\src\CTile3DProperties.c
# End Source File
# Begin Source File

SOURCE=..\base3d\src\Dungeon.c
# End Source File
# Begin Source File

SOURCE=..\base3d\src\EDirection_Utils.c
# End Source File
# Begin Source File

SOURCE=..\menu\src\Engine.c
# End Source File
# Begin Source File

SOURCE=..\base3d\src\Events.c
# End Source File
# Begin Source File

SOURCE=..\base3d\src\FixP.c
# End Source File
# Begin Source File

SOURCE=..\menu\src\GameMenu.c
# End Source File
# Begin Source File

SOURCE=..\base3d\src\Globals.c
# End Source File
# Begin Source File

SOURCE=..\menu\src\HelpScreen.c
# End Source File
# Begin Source File

SOURCE=..\menu\src\Interrogation.c
# End Source File
# Begin Source File

SOURCE=..\base3d\src\LoadBitmap.c
# End Source File
# Begin Source File

SOURCE=..\menu\src\Main.c
# End Source File
# Begin Source File

SOURCE=..\menu\src\MainMenu.c
# End Source File
# Begin Source File

SOURCE=..\base3d\src\MapWithCharKey.c
# End Source File
# Begin Source File

SOURCE=..\menu\src\SpyTravel.c
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=".\The Mistral Report 95.rc"
# End Source File
# Begin Source File

SOURCE=..\menu\src\UI.c
# End Source File
# Begin Source File

SOURCE=..\base3d\src\Vec.c
# End Source File
# Begin Source File

SOURCE=..\base3d\src\VisibilityStrategy.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\base3d\include\CActor.h
# End Source File
# Begin Source File

SOURCE=..\base3d\include\Common.h
# End Source File
# Begin Source File

SOURCE=..\base3d\include\CPackedFileReader.h
# End Source File
# Begin Source File

SOURCE=..\base3d\include\CRenderer.h
# End Source File
# Begin Source File

SOURCE=..\base3d\include\CTile3DProperties.h
# End Source File
# Begin Source File

SOURCE=..\base3d\include\Dungeon.h
# End Source File
# Begin Source File

SOURCE=..\base3d\include\EDirection_Utils.h
# End Source File
# Begin Source File

SOURCE=..\menu\include\Engine.h
# End Source File
# Begin Source File

SOURCE=..\base3d\include\Enums.h
# End Source File
# Begin Source File

SOURCE=..\base3d\include\FixP.h
# End Source File
# Begin Source File

SOURCE=..\base3d\include\Globals.h
# End Source File
# Begin Source File

SOURCE=..\base3d\include\LoadBitmap.h
# End Source File
# Begin Source File

SOURCE=..\base3d\include\MapWithCharKey.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=..\menu\include\SpyTravel.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=".\The Mistral Report 95.h"
# End Source File
# Begin Source File

SOURCE=..\menu\include\UI.h
# End Source File
# Begin Source File

SOURCE=..\base3d\include\Vec.h
# End Source File
# Begin Source File

SOURCE=..\base3d\include\VisibilityStrategy.h
# End Source File
# Begin Source File

SOURCE=..\base3d\include\Win32Int.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\small.ico
# End Source File
# Begin Source File

SOURCE=".\The Mistral Report 95.ico"
# End Source File
# End Group
# Begin Source File

SOURCE=.\bong.wav
# End Source File
# Begin Source File

SOURCE=.\dead.wav
# End Source File
# Begin Source File

SOURCE=.\detected.wav
# End Source File
# Begin Source File

SOURCE=.\detected2.wav
# End Source File
# Begin Source File

SOURCE=.\enemydead.wav
# End Source File
# Begin Source File

SOURCE=.\enemyfire.wav
# End Source File
# Begin Source File

SOURCE=.\fire.wav
# End Source File
# Begin Source File

SOURCE=.\gotclue.wav
# End Source File
# Begin Source File

SOURCE=.\hurt.wav
# End Source File
# Begin Source File

SOURCE=.\menu_move.wav
# End Source File
# Begin Source File

SOURCE=.\menu_select.wav
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
