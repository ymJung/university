; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CCalendarDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Calendar.h"

ClassCount=3
Class1=CCalendarApp
Class2=CCalendarDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_CALENDAR_DIALOG

[CLS:CCalendarApp]
Type=0
HeaderFile=Calendar.h
ImplementationFile=Calendar.cpp
Filter=N

[CLS:CCalendarDlg]
Type=0
HeaderFile=CalendarDlg.h
ImplementationFile=CalendarDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_BUTTON_ABOUT

[CLS:CAboutDlg]
Type=0
HeaderFile=CalendarDlg.h
ImplementationFile=CalendarDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_CALENDAR_DIALOG]
Type=1
Class=CCalendarDlg
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT_YEAR,edit,1350762624
Control4=IDC_SCROLL_YEAR,scrollbar,1342308353
Control5=IDC_COMBO_MONTH,combobox,1342374979
Control6=IDD_ABOUTBOX,button,1342242816
Control7=IDC_STATIC,button,1342177287
Control8=IDC_STATIC,button,1342177287
Control9=IDC_STATIC,static,1342177294
Control10=IDC_DATETIMEPICKER1,SysDateTimePick32,1342242857

