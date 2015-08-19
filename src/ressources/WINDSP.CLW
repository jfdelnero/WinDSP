; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=Noice_module_dialog
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "windsp.h"
LastPage=0

ClassCount=19
Class1=CChildView
Class2=Delay_module_dialog
Class3=Delay_module_dialog2
Class4=Delay_module_dialog3
Class5=Filter_dialog
Class6=LFO_module_dialog
Class7=CMainFrame
Class8=Output_dialog
Class9=SignalTransform_dialog
Class10=Visu_dialog
Class11=Volume_module_dialog
Class12=CWinDSPApp
Class13=CAboutDlg

ResourceCount=19
Resource1=IDD_MODULE_OUTPUT (English (U.S.))
Resource2=IDD_MODULE_FILTER (English (U.S.))
Resource3=IDD_MODULE_NOISE (English (U.S.))
Resource4=IDD_MODULE_DETECTOR (English (U.S.))
Resource5=IDD_MODULE_DELAY (English (U.S.))
Resource6=IDD_MODULE_SCOPE (English (U.S.))
Resource7=IDD_MODULE_MINFO (English (U.S.))
Resource8=IDD_MODULE_MIX (English (U.S.))
Resource9=IDD_MODULE_SIGNALTRANSFORM1 (English (U.S.))
Class14=Mix_dialog
Resource10=IDD_MODULE_AGENT (English (U.S.))
Class15=reverb_dialog
Resource11=IDD_DIALOG_CONFIG
Class16=detector_dialog
Resource12=IDD_MODULE_SIGNALTRANSFORM (English (U.S.))
Class17=CDialog_Config
Resource13=IDD_MODULE_REVERB (English (U.S.))
Resource14=IDD_MODULE_MMORSE (English (U.S.))
Class18=Info_Dialog
Resource15=IDD_ABOUTBOX
Resource16=IDD_MODULE_VOLUME (English (U.S.))
Resource17=IDD_MODULE_LFO (English (U.S.))
Resource18=IDD_DIALOGSTART
Class19=Noice_module_dialog
Resource19=IDR_MAINFRAME

[CLS:CChildView]
Type=0
BaseClass=CWnd 
HeaderFile=..\core\ChildView.h
ImplementationFile=..\core\ChildView.cpp
LastObject=BMODULE15
Filter=W
VirtualFilter=WC

[CLS:Delay_module_dialog]
Type=0
BaseClass=CDialog
HeaderFile=..\modules\delay\Delay_module_dialog.h
ImplementationFile=..\modules\delay\Delay_module_dialog.cpp
LastObject=Delay_module_dialog

[CLS:Delay_module_dialog2]
Type=0
BaseClass=CDialog
HeaderFile=..\modules\delay\Delay_module_dialog2.h
ImplementationFile=..\modules\delay\Delay_module_dialog2.cpp
LastObject=Delay_module_dialog2

[CLS:Delay_module_dialog3]
Type=0
BaseClass=CDialog
HeaderFile=..\modules\delay\Delay_module_dialog3.h
ImplementationFile=..\modules\delay\Delay_module_dialog3.cpp
LastObject=IDC_SLIDER14
Filter=D
VirtualFilter=dWC

[CLS:Filter_dialog]
Type=0
BaseClass=CDialog
HeaderFile=..\modules\filter\Filter_dialog.h
ImplementationFile=..\modules\filter\Filter_dialog.cpp
LastObject=Filter_dialog

[CLS:LFO_module_dialog]
Type=0
BaseClass=CDialog
HeaderFile=..\modules\lfo\LFO_module_dialog.h
ImplementationFile=..\modules\lfo\LFO_module_dialog.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_SLIDER1

[CLS:CMainFrame]
Type=0
HeaderFile=..\core\mainfrm.h
ImplementationFile=..\core\mainfrm.cpp
BaseClass=CFrameWnd
LastObject=BMODULE15
Filter=T
VirtualFilter=fWC

[CLS:Output_dialog]
Type=0
BaseClass=CDialog
HeaderFile=..\modules\output\Output_dialog.h
ImplementationFile=..\modules\output\Output_dialog.cpp
LastObject=ID_APP_ABOUT
Filter=D
VirtualFilter=dWC

[CLS:SignalTransform_dialog]
Type=0
BaseClass=CDialog
HeaderFile=..\modules\ST\SignalTransform_dialog.h
ImplementationFile=..\modules\ST\SignalTransform_dialog.cpp
Filter=D
VirtualFilter=dWC
LastObject=BMODULE15

[CLS:Visu_dialog]
Type=0
BaseClass=CDialog
HeaderFile=..\modules\scope\Visu_dialog.h
ImplementationFile=..\modules\scope\Visu_dialog.cpp
Filter=D
VirtualFilter=dWC
LastObject=Visu_dialog

[CLS:Volume_module_dialog]
Type=0
BaseClass=CDialog
HeaderFile=..\modules\volume\Volume_module_dialog.h
ImplementationFile=..\modules\volume\Volume_module_dialog.cpp
LastObject=ID_BMODULE01
Filter=D
VirtualFilter=dWC

[CLS:CWinDSPApp]
Type=0
BaseClass=CWinApp
HeaderFile=..\core\WinDSP.h
ImplementationFile=..\core\WinDSP.cpp
LastObject=BMODULE15

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=..\core\WinDSP.cpp
ImplementationFile=..\core\WinDSP.cpp
LastObject=IDC_BUTTON1
Filter=D
VirtualFilter=dWC

[DLG:IDD_DELAY_MODULE]
Type=1
Class=Delay_module_dialog

[DLG:IDD_PROPPAGE_MEDIUM]
Type=1
Class=Delay_module_dialog2

[DLG:IDD_MODULE_DELAY]
Type=1
Class=Delay_module_dialog3

[DLG:IDD_MODULE_FILTER]
Type=1
Class=Filter_dialog

[DLG:IDD_MODULE_LFO]
Type=1
Class=LFO_module_dialog

[DLG:IDD_MODULE_OUTPUT]
Type=1
Class=Output_dialog

[DLG:IDD_MODULE_SIGNALTRANSFORM]
Type=1
Class=SignalTransform_dialog

[DLG:IDD_MODULE_SCOPE]
Type=1
Class=Visu_dialog

[DLG:IDD_MODULE_VOLUME]
Type=1
Class=Volume_module_dialog

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=8
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDOK,button,1342373889
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1350572558
Control6=IDC_BUTTON1,button,1342275584
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352

[DLG:IDD_MODULE_LFO (English (U.S.))]
Type=1
Class=?
ControlCount=19
Control1=IDC_STATIC,static,1342308352
Control2=IDOK,button,1342242816
Control3=IDC_SLIDER1,msctls_trackbar32,1342242853
Control4=IDC_EDIT1,edit,1350633600
Control5=IDC_SLIDER2,msctls_trackbar32,1342242853
Control6=IDC_SLIDER3,msctls_trackbar32,1342242853
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EDIT3,edit,1350633600
Control11=IDC_CHECK3,button,1342242819
Control12=IDC_CHECK4,button,1342242819
Control13=IDC_CHECK5,button,1342242819
Control14=IDC_SLIDER5,msctls_trackbar32,1342242853
Control15=IDC_STATIC,static,1342308352
Control16=IDC_CHECK7,button,1342242819
Control17=IDC_CHECK8,button,1342242819
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352

[DLG:IDD_MODULE_FILTER (English (U.S.))]
Type=1
Class=?
ControlCount=22
Control1=IDC_STATIC,static,1342308352
Control2=IDOK,button,1342242816
Control3=IDC_SLIDER1,msctls_trackbar32,1342242855
Control4=IDC_SLIDER2,msctls_trackbar32,1342242855
Control5=IDC_SLIDER3,msctls_trackbar32,1342242855
Control6=IDC_SLIDER5,msctls_trackbar32,1342242855
Control7=IDC_SLIDER6,msctls_trackbar32,1342242855
Control8=IDC_SLIDER7,msctls_trackbar32,1342242855
Control9=IDC_SLIDER8,msctls_trackbar32,1342242855
Control10=IDC_SLIDER9,msctls_trackbar32,1342242855
Control11=IDC_SLIDER10,msctls_trackbar32,1342242855
Control12=IDC_SLIDER11,msctls_trackbar32,1342242855
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352

[DLG:IDD_MODULE_VOLUME (English (U.S.))]
Type=1
Class=?
ControlCount=10
Control1=IDC_STATIC,static,1342308352
Control2=IDOK,button,1342242816
Control3=IDC_SLIDER1,msctls_trackbar32,1342242855
Control4=IDC_EDIT1,edit,1350633600
Control5=IDC_SLIDER2,msctls_trackbar32,1342242855
Control6=IDC_EDIT2,edit,1350633600
Control7=IDC_CHECK2,button,1342242819
Control8=IDC_CHECK4,button,1342242819
Control9=IDC_CHECK3,button,1342242819
Control10=IDC_CHECK5,button,1342242819

[DLG:IDD_MODULE_SIGNALTRANSFORM (English (U.S.))]
Type=1
Class=?
ControlCount=11
Control1=IDC_STATIC,static,1342308352
Control2=IDOK,button,1342242816
Control3=IDC_CHECK1,button,1342242819
Control4=IDC_CHECK2,button,1342242819
Control5=IDC_CHECK3,button,1342242819
Control6=IDC_CHECK4,button,1342242819
Control7=IDC_SLIDER1,msctls_trackbar32,1342242840
Control8=IDC_EDIT1,edit,1350633600
Control9=IDC_STATIC,static,1342308352
Control10=IDC_CHECK5,button,1342242819
Control11=IDC_CHECK6,button,1342242819

[DLG:IDD_MODULE_SCOPE (English (U.S.))]
Type=1
Class=?
ControlCount=4
Control1=IDOK,button,1342279424
Control2=IDC_BUTTON1,button,1342275584
Control3=IDC_BUTTON2,button,1342275584
Control4=IDC_BUTTON3,button,1342275584

[DLG:IDD_MODULE_DELAY (English (U.S.))]
Type=1
Class=?
ControlCount=13
Control1=IDC_STATIC,static,1342308352
Control2=IDOK,button,1342242816
Control3=IDC_SLIDER1,msctls_trackbar32,1342242853
Control4=IDC_EDIT1,edit,1350633600
Control5=IDC_SLIDER2,msctls_trackbar32,1342242853
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT2,edit,1350633600
Control9=IDC_SLIDER4,msctls_trackbar32,1342242853
Control10=IDC_STATIC,static,1342308352
Control11=IDC_EDIT4,edit,1350633600
Control12=IDC_SLIDER14,msctls_trackbar32,1342242853
Control13=IDC_STATIC,static,1342308352

[DLG:IDD_MODULE_OUTPUT (English (U.S.))]
Type=1
Class=?
ControlCount=5
Control1=IDC_STATIC,static,1342308352
Control2=IDOK,button,1342242816
Control3=IDC_CHECK1,button,1342242819
Control4=IDC_CHECK2,button,1342242819
Control5=IDC_BUTTON1,button,1342242816

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_BMODULE01
Command2=ID_BMODULE02
Command3=ID_BMODULE03
Command4=ID_BMODULE04
Command5=ID_BMODULE05
Command6=ID_BMODULE08
Command7=ID_BMODULE09
Command8=ID_BMODULE10
Command9=ID_BMODULE11
Command10=ID_BMODULE12
Command11=ID_BMODULE13
Command12=ID_BMODULE14
Command13=ID_BNOISE
Command14=BMODULE15
Command15=ID_BMODULE06
Command16=ID_BSTOP
Command17=ID_BMIX
CommandCount=17

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FICHIER_OUVRIR
Command2=ID_FICHIER_ENREGISTRER
Command3=ID_APP_EXIT
Command4=ID_VIEW_TOOLBAR
Command5=ID_VIEW_STATUS_BAR
Command6=ID_OPTIONS_ESSON
Command7=ID_APP_ABOUT
CommandCount=7

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_EDIT_PASTE
Command3=ID_EDIT_UNDO
Command4=ID_EDIT_CUT
Command5=ID_NEXT_PANE
Command6=ID_PREV_PANE
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_CUT
Command10=ID_EDIT_UNDO
CommandCount=10

[CLS:Mix_dialog]
Type=0
HeaderFile=..\modules\mix\Mix_dialog.h
ImplementationFile=..\modules\mix\Mix_dialog.cpp
BaseClass=CDialog
Filter=D
LastObject=65535
VirtualFilter=dWC

[DLG:IDD_MODULE_MIX (English (U.S.))]
Type=1
Class=Mix_dialog
ControlCount=3
Control1=65535,static,1342308352
Control2=IDOK,button,1342242816
Control3=IDC_SLIDER1,msctls_trackbar32,1342242853

[DLG:IDD_MODULE_REVERB (English (U.S.))]
Type=1
Class=reverb_dialog
ControlCount=8
Control1=IDC_STATIC,static,1342308352
Control2=IDOK,button,1342242816
Control3=IDC_SLIDER1,msctls_trackbar32,1342242855
Control4=IDC_EDIT1,edit,1350633600
Control5=IDC_SLIDER2,msctls_trackbar32,1342242855
Control6=IDC_EDIT2,edit,1350633600
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352

[CLS:reverb_dialog]
Type=0
HeaderFile=..\modules\reverb\reverb_dialog.h
ImplementationFile=..\modules\reverb\reverb_dialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_SLIDER2

[DLG:IDD_MODULE_DETECTOR (English (U.S.))]
Type=1
Class=detector_dialog
ControlCount=12
Control1=IDC_STATIC,static,1342308352
Control2=IDOK,button,1342242816
Control3=IDC_SLIDER1,msctls_trackbar32,1342242840
Control4=IDC_SLIDER2,msctls_trackbar32,1342242840
Control5=IDC_SLIDER12,msctls_trackbar32,1073807384
Control6=IDC_SLIDER5,msctls_trackbar32,1342242840
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1073872896
Control11=IDC_SLIDER13,msctls_trackbar32,1342242840
Control12=IDC_STATIC,static,1342308352

[CLS:detector_dialog]
Type=0
HeaderFile=..\modules\detector\detector_dialog.h
ImplementationFile=..\modules\detector\detector_dialog.cpp
BaseClass=CDialog
Filter=D
LastObject=detector_dialog
VirtualFilter=dWC

[DLG:IDD_DIALOG_CONFIG]
Type=1
Class=CDialog_Config
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDC_CHECK1,button,1342242819
Control3=IDC_CHECK2,button,1342242819
Control4=IDC_CHECK3,button,1342242819
Control5=IDC_CHECK4,button,1342242819
Control6=IDC_CHECK5,button,1342242819

[CLS:CDialog_Config]
Type=0
HeaderFile=..\core\dialog_config.h
ImplementationFile=..\core\dialog_config.cpp
BaseClass=CDialog
LastObject=CDialog_Config

[DLG:IDD_MODULE_SIGNALTRANSFORM1 (English (U.S.))]
Type=1
Class=?
ControlCount=11
Control1=IDC_STATIC,static,1342308352
Control2=IDOK,button,1342242816
Control3=IDC_CHECK1,button,1342242819
Control4=IDC_CHECK2,button,1342242819
Control5=IDC_CHECK3,button,1342242819
Control6=IDC_CHECK4,button,1342242819
Control7=IDC_SLIDER1,msctls_trackbar32,1342242840
Control8=IDC_EDIT1,edit,1350633600
Control9=IDC_STATIC,static,1342308352
Control10=IDC_CHECK5,button,1342242819
Control11=IDC_CHECK6,button,1342242819

[DLG:IDD_MODULE_MINFO (English (U.S.))]
Type=1
Class=Info_Dialog
ControlCount=3
Control1=IDC_EDIT1,edit,1350635652
Control2=IDC_STATIC,static,1342308352
Control3=IDOK,button,1342242816

[CLS:Info_Dialog]
Type=0
HeaderFile=Info_Dialog.h
ImplementationFile=Info_Dialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=Info_Dialog

[DLG:IDD_DIALOGSTART]
Type=1
Class=?
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1350573582

[DLG:IDD_MODULE_MMORSE (English (U.S.))]
Type=1
Class=?
ControlCount=3
Control1=IDC_EDIT1,edit,1350635652
Control2=IDC_STATIC,static,1342308352
Control3=IDOK,button,1342242816

[DLG:IDD_MODULE_AGENT (English (U.S.))]
Type=1
Class=?
ControlCount=19
Control1=IDC_STATIC,static,1342308352
Control2=IDOK,button,1342242816
Control3=IDC_SLIDER1,msctls_trackbar32,1342242853
Control4=IDC_STATIC,static,1342308352
Control5=IDC_SLIDER4,msctls_trackbar32,1342242853
Control6=IDC_STATIC,static,1342308352
Control7=IDC_CHECK15,button,1342242819
Control8=IDC_CHECK3,button,1342242819
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EDIT1,edit,1350631552
Control11=IDC_EDIT5,edit,1350631552
Control12=IDC_EDIT2,edit,1350631552
Control13=IDC_EDIT4,edit,1350631552
Control14=IDC_EDIT6,edit,1350631552
Control15=IDC_EDIT7,edit,1350631552
Control16=IDC_EDIT8,edit,1350631552
Control17=IDC_EDIT9,edit,1350631552
Control18=IDC_EDIT10,edit,1350631552
Control19=IDC_EDIT11,edit,1350631552

[DLG:IDD_MODULE_NOISE (English (U.S.))]
Type=1
Class=Noice_module_dialog
ControlCount=10
Control1=IDC_STATIC,static,1342308352
Control2=IDOK,button,1342242816
Control3=IDC_SLIDER1,msctls_trackbar32,1342242855
Control4=IDC_EDIT1,edit,1350633600
Control5=IDC_SLIDER2,msctls_trackbar32,1342242855
Control6=IDC_EDIT2,edit,1350633600
Control7=IDC_CHECK2,button,1342242819
Control8=IDC_CHECK4,button,1342242819
Control9=IDC_CHECK3,button,1342242819
Control10=IDC_CHECK5,button,1342242819

[CLS:Noice_module_dialog]
Type=0
HeaderFile=..\modules\noise\noise_module_dialog.h
ImplementationFile=..\modules\noise\noise_module_dialog.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_BNOISE
VirtualFilter=dWC

