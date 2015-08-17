# Microsoft Developer Studio Project File - Name="WinDSP" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=WinDSP - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "WinDSP.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "WinDSP.mak" CFG="WinDSP - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "WinDSP - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "WinDSP - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "WinDSP - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I ".\core\\" /I ".\ressources\\" /I ".\modules\delay\\" /I ".\modules\detector\\" /I ".\modules\filter\\" /I ".\modules\input\\" /I ".\modules\lfo\\" /I ".\modules\mix\\" /I ".\modules\output\\" /I ".\modules\reverb\\" /I ".\modules\scope\\" /I ".\modules\st\\" /I ".\modules\t\\" /I ".\modules\volume\\" /I ".\modules\info\\" /I ".\modules\morse\\" /I ".\modules\feedback\\" /I ".\modules\agent\\" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /YX /FD /c
# SUBTRACT CPP /X
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x40c /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 winmm.lib /nologo /subsystem:windows /machine:I386
# SUBTRACT LINK32 /map /nodefaultlib

!ELSEIF  "$(CFG)" == "WinDSP - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I ".\core\\" /I ".\ressources\\" /I ".\modules\delay\\" /I ".\modules\detector\\" /I ".\modules\filter\\" /I ".\modules\input\\" /I ".\modules\lfo\\" /I ".\modules\mix\\" /I ".\modules\output\\" /I ".\modules\reverb\\" /I ".\modules\scope\\" /I ".\modules\st\\" /I ".\modules\t\\" /I ".\modules\volume\\" /I ".\modules\info\\" /I ".\modules\morse\\" /I ".\modules\feedback\\" /I ".\modules\agent\\" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x40c /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 winmm.lib /nologo /subsystem:windows /debug /machine:I386 /out:"Debug/WinDSP_D.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "WinDSP - Win32 Release"
# Name "WinDSP - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "modules"

# PROP Default_Filter ""
# Begin Group "delay"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\modules\delay\delay_module.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\delay\delay_module.h
# End Source File
# Begin Source File

SOURCE=.\modules\delay\delay_module_dialog.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\delay\delay_module_dialog.h
# End Source File
# End Group
# Begin Group "input"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\modules\input\input_module.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\input\input_module.h
# End Source File
# End Group
# Begin Group "mix"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\modules\mix\mix_dialog.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\mix\mix_dialog.h
# End Source File
# Begin Source File

SOURCE=.\modules\mix\mix_module.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\mix\mix_module.h
# End Source File
# End Group
# Begin Group "output"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\modules\output\output_dialog.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\output\output_dialog.h
# End Source File
# Begin Source File

SOURCE=.\modules\output\output_module.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\output\output_module.h
# End Source File
# End Group
# Begin Group "T"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\modules\t\t_module.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\t\t_module.h
# End Source File
# End Group
# Begin Group "lfo"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\modules\lfo\lfo_module.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\lfo\lfo_module.h
# End Source File
# Begin Source File

SOURCE=.\modules\lfo\lfo_module_dialog.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\lfo\lfo_module_dialog.h
# End Source File
# End Group
# Begin Group "Volume"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\modules\volume\volume_module.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\volume\volume_module.h
# End Source File
# Begin Source File

SOURCE=.\modules\volume\volume_module_dialog.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\volume\volume_module_dialog.h
# End Source File
# End Group
# Begin Group "Signal_Transform"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\modules\st\signal_transform_dialog.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\st\signal_transform_dialog.h
# End Source File
# Begin Source File

SOURCE=.\modules\st\signal_transform_module.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\st\signal_transform_module.h
# End Source File
# End Group
# Begin Group "Visu"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\modules\scope\fft.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\scope\fft.h
# End Source File
# Begin Source File

SOURCE=.\modules\scope\visu_dialog.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\scope\visu_dialog.h
# End Source File
# Begin Source File

SOURCE=.\modules\scope\visu_module.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\scope\visu_module.h
# End Source File
# End Group
# Begin Group "Reverb"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\modules\reverb\reverb.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\reverb\reverb.h
# End Source File
# Begin Source File

SOURCE=.\modules\reverb\reverb_dialog.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\reverb\reverb_dialog.h
# End Source File
# Begin Source File

SOURCE=.\modules\reverb\reverb_module.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\reverb\reverb_module.h
# End Source File
# End Group
# Begin Group "Filter"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\modules\filter\filter_dialog.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\filter\filter_dialog.h
# End Source File
# Begin Source File

SOURCE=.\modules\filter\filter_iir.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\filter\filter_iir.h
# End Source File
# Begin Source File

SOURCE=.\modules\filter\filter_module.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\filter\filter_module.h
# End Source File
# End Group
# Begin Group "Detector"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\modules\detector\detector_dialog.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\detector\detector_dialog.h
# End Source File
# Begin Source File

SOURCE=.\modules\detector\detector_module.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\detector\detector_module.h
# End Source File
# End Group
# Begin Group "Info"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\modules\info\info_dialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ressources\info_dialog.h
# End Source File
# Begin Source File

SOURCE=.\modules\info\info_module.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\info\info_module.h
# End Source File
# End Group
# Begin Group "Morse"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\modules\morse\morse_dialog.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\morse\morse_dialog.h
# End Source File
# Begin Source File

SOURCE=.\modules\morse\morse_module.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\morse\morse_module.h
# End Source File
# End Group
# Begin Group "FeedBack"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\modules\feedback\feedback.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\feedback\feedback.h
# End Source File
# End Group
# Begin Group "Agent"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\modules\agent\agent_module.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\agent\agent_module.h
# End Source File
# Begin Source File

SOURCE=.\modules\agent\agent_module_dialog.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\agent\agent_module_dialog.h
# End Source File
# End Group
# End Group
# Begin Source File

SOURCE=.\core\ChildView.cpp
# End Source File
# Begin Source File

SOURCE=.\core\dialog_config.cpp
# End Source File
# Begin Source File

SOURCE=.\core\fast_rout_x86.cpp
# End Source File
# Begin Source File

SOURCE=.\core\fast_rout_x86.h
# End Source File
# Begin Source File

SOURCE=.\core\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\core\scheduler.cpp
# End Source File
# Begin Source File

SOURCE=.\core\sound_io.cpp
# End Source File
# Begin Source File

SOURCE=.\core\startdialog.cpp
# End Source File
# Begin Source File

SOURCE=.\core\StdAfx.cpp
# End Source File
# Begin Source File

SOURCE=.\core\utils.cpp
# End Source File
# Begin Source File

SOURCE=.\core\utils.h
# End Source File
# Begin Source File

SOURCE=.\core\WinDSP.cpp
# End Source File
# Begin Source File

SOURCE=.\ressources\WinDSP.rc
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\core\ChildView.h
# End Source File
# Begin Source File

SOURCE=.\core\dialog_config.h
# End Source File
# Begin Source File

SOURCE=.\core\fastroutx86.h
# End Source File
# Begin Source File

SOURCE=.\core\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\core\module.h
# End Source File
# Begin Source File

SOURCE=.\ressources\resource.h
# End Source File
# Begin Source File

SOURCE=.\core\scheduler.h
# End Source File
# Begin Source File

SOURCE=.\core\sound_io.h
# End Source File
# Begin Source File

SOURCE=.\ressources\startdialog.h
# End Source File
# Begin Source File

SOURCE=.\core\WinDSP.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\RESSOURCES\agent_module.ico
# End Source File
# Begin Source File

SOURCE=.\ressources\ban1.bmp
# End Source File
# Begin Source File

SOURCE=.\ressources\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\ressources\delay_module.ico
# End Source File
# Begin Source File

SOURCE=.\ressources\detector_module.ico
# End Source File
# Begin Source File

SOURCE=.\ressources\echo_module.ico
# End Source File
# Begin Source File

SOURCE=.\RESSOURCES\feedback_module.ico
# End Source File
# Begin Source File

SOURCE=.\ressources\filter_module.ico
# End Source File
# Begin Source File

SOURCE=.\ressources\info_module.ico
# End Source File
# Begin Source File

SOURCE=.\ressources\input_module.ico
# End Source File
# Begin Source File

SOURCE=.\ressources\lfo_module.ico
# End Source File
# Begin Source File

SOURCE=.\ressources\mix_module.ico
# End Source File
# Begin Source File

SOURCE=.\ressources\module3.ico
# End Source File
# Begin Source File

SOURCE=.\ressources\morse_module.ico
# End Source File
# Begin Source File

SOURCE=.\ressources\output_module.ico
# End Source File
# Begin Source File

SOURCE=.\ressources\revb_module.ico
# End Source File
# Begin Source File

SOURCE=.\ressources\scope_module.ico
# End Source File
# Begin Source File

SOURCE=.\ressources\st_module.ico
# End Source File
# Begin Source File

SOURCE=.\ressources\start.bmp
# End Source File
# Begin Source File

SOURCE=.\ressources\t_module.ico
# End Source File
# Begin Source File

SOURCE=.\ressources\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\ressources\vco_module.ico
# End Source File
# Begin Source File

SOURCE=.\ressources\vol_module.ico
# End Source File
# Begin Source File

SOURCE=.\ressources\WinDSP.ico
# End Source File
# Begin Source File

SOURCE=.\ressources\WinDSP.rc2
# End Source File
# End Group
# End Target
# End Project
