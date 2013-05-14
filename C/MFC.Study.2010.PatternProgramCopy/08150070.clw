; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMy08150070View
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "08150070.h"
LastPage=0

ClassCount=11
Class1=CMy08150070App
Class2=CMy08150070Doc
Class3=CMy08150070View
Class4=CMainFrame

ResourceCount=8
Resource1=IDD_ABOUTBOX
Resource2=IDD_DIALOG1
Class5=CChildFrame
Class6=CAboutDlg
Resource3=IDR_MY0815TYPE
Class7=CDownSampleDlg
Resource4=IDD_DIALOG2
Class8=CUpSampleDlg
Resource5=IDD_DIALOG3
Class9=CQuantizationDlg
Resource6=IDR_MAINFRAME
Class10=CConstantDlg
Resource7=IDD_DIALOG4
Class11=CStressTransformDlg
Resource8=IDD_DIALOG5

[CLS:CMy08150070App]
Type=0
HeaderFile=08150070.h
ImplementationFile=08150070.cpp
Filter=N

[CLS:CMy08150070Doc]
Type=0
HeaderFile=08150070Doc.h
ImplementationFile=08150070Doc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=CMy08150070Doc

[CLS:CMy08150070View]
Type=0
HeaderFile=08150070View.h
ImplementationFile=08150070View.cpp
Filter=C
LastObject=ID_XOR_OPERATE
BaseClass=CView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M
LastObject=CChildFrame


[CLS:CAboutDlg]
Type=0
HeaderFile=08150070.cpp
ImplementationFile=08150070.cpp
Filter=D
LastObject=ID_APP_ABOUT

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

[MNU:IDR_MY0815TYPE]
Type=1
Class=CMy08150070View
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
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_VIEW_TOOLBAR
Command16=ID_VIEW_STATUS_BAR
Command17=ID_WINDOW_NEW
Command18=ID_WINDOW_CASCADE
Command19=ID_WINDOW_TILE_HORZ
Command20=ID_WINDOW_ARRANGE
Command21=ID_APP_ABOUT
Command22=ID_DOWN_SAMPLING
Command23=ID_UP_SAMPLING
Command24=ID_QUANTIZATION
Command25=ID_SUM_CONSTANT
Command26=ID_SUB_CONSTANT
Command27=ID_MUL_CONSTANT
Command28=ID_DIV_CONSTANT
Command29=ID_NEGA_TRANSFORM
Command30=ID_GAMMA_CORRECTION
Command31=ID_BINARIZATION
Command32=ID_STRESS_TRANSFORM
Command33=ID_AND_OPERATE
Command34=ID_OR_OPERATE
Command35=ID_XOR_OPERATE
Command36=ID_HISTO_STRETCH
Command37=ID_END_IN_SEARCH
Command38=ID_HISTOGRAM
CommandCount=38

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:IDD_DIALOG1]
Type=1
Class=CDownSampleDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_STATIC,static,1342308352

[CLS:CDownSampleDlg]
Type=0
HeaderFile=DownSampleDlg.h
ImplementationFile=DownSampleDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDownSampleDlg

[DLG:IDD_DIALOG2]
Type=1
Class=CUpSampleDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_STATIC,static,1342308352

[CLS:CUpSampleDlg]
Type=0
HeaderFile=UpSampleDlg.h
ImplementationFile=UpSampleDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CUpSampleDlg

[DLG:IDD_DIALOG3]
Type=1
Class=CQuantizationDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT1,edit,1350631552

[CLS:CQuantizationDlg]
Type=0
HeaderFile=QuantizationDlg.h
ImplementationFile=QuantizationDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CQuantizationDlg

[DLG:IDD_DIALOG4]
Type=1
Class=CConstantDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT1,edit,1350631552

[CLS:CConstantDlg]
Type=0
HeaderFile=ConstantDlg.h
ImplementationFile=ConstantDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CConstantDlg

[DLG:IDD_DIALOG5]
Type=1
Class=CStressTransformDlg
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT1,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT2,edit,1350631552

[CLS:CStressTransformDlg]
Type=0
HeaderFile=StressTransformDlg.h
ImplementationFile=StressTransformDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_EDIT1

