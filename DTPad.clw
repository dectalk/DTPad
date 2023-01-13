; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDTPadApp
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "DTPad.h"
LastPage=0

ClassCount=7
Class1=CDTPadApp
Class2=CDTPadDoc
Class3=CDTPadView
Class4=CMainFrame
Class7=CSettingsDLG

ResourceCount=4
Resource1=IDD_DIALOG1
Resource2=IDD_ABOUTBOX
Resource3=IDR_TEXTTYPE
Class5=CChildFrame
Class6=CAboutDlg
Resource4=IDR_MAINFRAME

[CLS:CDTPadApp]
Type=0
HeaderFile=DTPad.h
ImplementationFile=DTPad.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CDTPadApp

[CLS:CDTPadDoc]
Type=0
HeaderFile=DTPadDoc.h
ImplementationFile=DTPadDoc.cpp
Filter=N
LastObject=CDTPadDoc

[CLS:CDTPadView]
Type=0
HeaderFile=DTPadView.h
ImplementationFile=DTPadView.cpp
Filter=C
LastObject=CDTPadView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M


[CLS:CAboutDlg]
Type=0
HeaderFile=DTPad.cpp
ImplementationFile=DTPad.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_APP_ABOUT
CommandCount=8

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_TEXTTYPE]
Type=1
Class=CDTPadView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_REDO
Command13=ID_EDIT_CUT
Command14=ID_EDIT_COPY
Command15=ID_EDIT_PASTE
Command16=ID_EDIT_CLEAR
Command17=ID_EDIT_CLEAR_ALL
Command18=ID_EDIT_SELECT_ALL
Command19=ID_EDIT_FIND
Command20=ID_EDIT_REPEAT
Command21=ID_EDIT_REPLACE
Command22=ID_TTS_SPEAKDOC
Command23=ID_TTS_SPEAKSEL
Command24=ID_TTS_PAUSE
Command25=ID_TTS_STOP
Command26=ID_TTS_CREATEWAV
Command27=ID_TTS_CREATERAW
Command28=ID_TTS_CREATELOG
Command29=ID_TTS_RESET
Command30=ID_TTS_LOADDICT
Command31=ID_TTS_UNLOADDICT
Command32=ID_TTS_VERSION
Command33=ID_TTS_RATEUP
Command34=ID_TTS_RATEDOWN
Command35=ID_TTS_NEXTVOICE
Command36=ID_TTS_PREVVOICE
Command37=ID_TTS_SETTINGS
Command38=ID_TTS_LOADDLL
Command39=ID_VIEW_TOOLBAR
Command40=ID_VIEW_STATUS_BAR
Command41=ID_WINDOW_NEW
Command42=ID_WINDOW_CASCADE
Command43=ID_WINDOW_TILE_HORZ
Command44=ID_WINDOW_TILE_VERT
Command45=ID_WINDOW_ARRANGE
Command46=ID_APP_ABOUT
CommandCount=46

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_REDO
Command7=ID_EDIT_CUT
Command8=ID_EDIT_COPY
Command9=ID_EDIT_PASTE
Command10=ID_EDIT_CLEAR_ALL
Command11=ID_EDIT_SELECT_ALL
Command12=ID_EDIT_FIND
Command13=ID_EDIT_REPEAT
Command14=ID_EDIT_REPLACE
Command15=ID_TTS_SPEAKDOC
Command16=ID_TTS_SPEAKSEL
Command17=ID_TTS_PAUSE
Command18=ID_TTS_STOP
Command19=ID_TTS_CREATEWAV
Command20=ID_TTS_CREATERAW
Command21=ID_TTS_CREATELOG
Command22=ID_TTS_RESET
Command23=ID_TTS_LOADDICT
Command24=ID_TTS_UNLOADDICT
Command25=ID_TTS_VERSION
Command26=ID_TTS_RATEUP
Command27=ID_TTS_RATEDOWN
Command28=ID_TTS_NEXTVOICE
Command29=ID_TTS_PREVVOICE
Command30=ID_TTS_SETTINGS
Command31=ID_TTS_LOADDLL
Command32=ID_EDIT_UNDO
Command33=ID_EDIT_CUT
Command34=ID_EDIT_COPY
Command35=ID_EDIT_PASTE
Command36=ID_NEXT_PANE
Command37=ID_PREV_PANE
CommandCount=37

[DLG:IDD_DIALOG1]
Type=1
Class=CSettingsDLG
ControlCount=12
Control1=IDC_STATIC,static,1342308352
Control2=IDC_DEVICE,combobox,1344339971
Control3=IDC_OWN,button,1342242819
Control4=IDC_STATIC,static,1342308352
Control5=IDC_FORMAT,combobox,1344339971
Control6=IDC_STATIC,static,1342308352
Control7=IDC_LOGMODE,combobox,1344339971
Control8=IDC_STARTSPEAK,button,1342242819
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STARTMSG,edit,1350631552
Control11=IDOK,button,1342242817
Control12=IDCANCEL,button,1342242816

[CLS:CSettingsDLG]
Type=0
HeaderFile=SettingsDLG.h
ImplementationFile=SettingsDLG.cpp
BaseClass=CDialog
Filter=D
LastObject=CSettingsDLG
VirtualFilter=dWC

