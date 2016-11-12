//---------------------------------------------------------------------------

#include <vcl.h>
#include <windows.h>

#include "catalogadmin.h"
#include "PressAdminForm.h"
#include "BookTypeAdminForm.h"
#include "ExcelImport.h"
#include "catalogbuilt.h"
#include "catalognewandrec.h"
#include "Qikanguanli.h"
#include "mutibooktongyi.h"
#include "Catalogkanli.h"
#include "wenjukanli.h"
#pragma hdrstop
//---------------------------------------------------------------------------
//   Important note about DLL memory management when your DLL uses the
//   static version of the RunTime Library:
//
//   If your DLL exports any functions that pass String objects (or structs/
//   classes containing nested Strings) as parameter or function results,
//   you will need to add the library MEMMGR.LIB to both the DLL project and
//   any other projects that use the DLL.  You will also need to use MEMMGR.LIB
//   if any other projects which use the DLL will be performing new or delete
//   operations on any non-TObject-derived classes which are exported from the
//   DLL. Adding MEMMGR.LIB to your project will change the DLL and its calling
//   EXE's to use the BORLNDMM.DLL as their memory manager.  In these cases,
//   the file BORLNDMM.DLL should be deployed along with your DLL.
//
//   To avoid using BORLNDMM.DLL, pass string information using "char *" or
//   ShortString parameters.
//
//   If your DLL uses the dynamic version of the RTL, you do not need to
//   explicitly add MEMMGR.LIB as this will be done implicitly for you
//---------------------------------------------------------------------------

#pragma argsused

TApplication* DllApplication = NULL;

int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void* lpReserved)
{
	switch(reason)                                                 //手工增加
	{
		case DLL_PROCESS_ATTACH:
			CoInitialize(NULL);
			DllApplication = Application;
			break;
		case DLL_PROCESS_DETACH:
			CoUninitialize();
			Application = DllApplication;
			break;
		case DLL_THREAD_ATTACH:
			break;
		case DLL_THREAD_DETACH:
			break;
	}

	return 1;
}
//---------------------------------------------------------------------------

void __stdcall ManagePress(TApplication* app, TADOConnection* con,HWND MainHandle)
{
	SendMessage(MainHandle,WM_SETREDRAW,0,0);
	Application = app;
	TfrmPressAdmin* frm = new TfrmPressAdmin(Application);
	frm->Init(Application, con);
	SendMessage(MainHandle,WM_SETREDRAW,1,0);
	RedrawWindow(MainHandle,NULL,0,RDW_FRAME|RDW_INVALIDATE | RDW_ALLCHILDREN|RDW_NOINTERNALPAINT);
}

void __stdcall ManageBookType(TApplication* app, TADOConnection* con,HWND MainHandle)
{
	SendMessage(MainHandle,WM_SETREDRAW,0,0);
	Application = app;
	TfrmBookTypeAdmin* frm = new TfrmBookTypeAdmin(Application);
	frm->Init(Application,con);
	frm->ShowModal();
	SendMessage(MainHandle,WM_SETREDRAW,1,0);
	RedrawWindow(MainHandle,NULL,0,RDW_FRAME|RDW_INVALIDATE | RDW_ALLCHILDREN|RDW_NOINTERNALPAINT);
}

void __stdcall CatalogKan(TApplication* app, TADOConnection* con,int stgid,int userid,HWND MainHandle,int version)
{
	SendMessage(MainHandle,WM_SETREDRAW,0,0);
	Application = app;
	TfrmCatalogkanli* frm = new TfrmCatalogkanli(Application,con,stgid,userid);
        frm->version=version;
	frm->Show();
	SendMessage(MainHandle,WM_SETREDRAW,1,0);
	RedrawWindow(MainHandle,NULL,0,RDW_FRAME|RDW_INVALIDATE | RDW_ALLCHILDREN|RDW_NOINTERNALPAINT);
}

void __stdcall Catalogbuilt(TApplication* app, TADOConnection* con,HWND MainHandle)
{
	SendMessage(MainHandle,WM_SETREDRAW,0,0);
	Application = app;
	Tfrmcatalogbuit* frm = new Tfrmcatalogbuit(Application,con);
	frm->Show();
	SendMessage(MainHandle,WM_SETREDRAW,1,0);
	RedrawWindow(MainHandle,NULL,0,RDW_FRAME|RDW_INVALIDATE | RDW_ALLCHILDREN|RDW_NOINTERNALPAINT);
}
void __stdcall Catalogneworrec(TApplication* app, TADOConnection* con,int stgid,int userid,HWND MainHandle)
{
	SendMessage(MainHandle,WM_SETREDRAW,0,0);
	Application = app;
	Tfrmcatalognewrecoment* frm = new Tfrmcatalognewrecoment(Application,con);
        frm->fstgid = stgid;
        frm->fuserid = userid;
	frm->Show();
	SendMessage(MainHandle,WM_SETREDRAW,1,0);
	RedrawWindow(MainHandle,NULL,0,RDW_FRAME|RDW_INVALIDATE | RDW_ALLCHILDREN|RDW_NOINTERNALPAINT);
}


void __stdcall Multibook(TApplication* app, TADOConnection* con,int stgid,int userid,HWND MainHandle)
{
	SendMessage(MainHandle,WM_SETREDRAW,0,0);
	Tfrmmutibook *frm = new Tfrmmutibook(Application,con);
	frm->stgid = stgid;
	frm->userid = userid;
	frm->ShowModal();
	SendMessage(MainHandle,WM_SETREDRAW,1,0);
	RedrawWindow(MainHandle,NULL,0,RDW_FRAME|RDW_INVALIDATE | RDW_ALLCHILDREN|RDW_NOINTERNALPAINT);
}
void __stdcall QiKanguanli(TApplication* app, TADOConnection* con,int stgid,HWND MainHandle,int version)
{
	SendMessage(MainHandle,WM_SETREDRAW,0,0);
	Application = app;
	TfrmQikanguanli* frm = new TfrmQikanguanli(Application,con,stgid);
        frm->version=version;
	frm->Show();
	SendMessage(MainHandle,WM_SETREDRAW,1,0);
	RedrawWindow(MainHandle,NULL,0,RDW_FRAME|RDW_INVALIDATE | RDW_ALLCHILDREN|RDW_NOINTERNALPAINT);
}
void __stdcall WenJuguanli(TApplication* app, TADOConnection* con,int stgid,int userid,HWND MainHandle)
{
	SendMessage(MainHandle,WM_SETREDRAW,0,0);
	Application = app;
	Tfrmwenjukanli* frm = new Tfrmwenjukanli(Application,con,stgid,userid);
	frm->Show();
	SendMessage(MainHandle,WM_SETREDRAW,1,0);
	RedrawWindow(MainHandle,NULL,0,RDW_FRAME|RDW_INVALIDATE | RDW_ALLCHILDREN|RDW_NOINTERNALPAINT);
}






