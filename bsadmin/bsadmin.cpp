//---------------------------------------------------------------------------

#include <vcl.h>
#include <windows.h>
#include "catalognewandrec.h"
#include "bsadmin.h"
#include "StorageMngForm.h"
#include "WholesaleMngForm.h"
#include "RetailMngForm.h"
#include "ProcureMng.h"
#include "StorageReturnMngForm.h"
#include "WholesaleMngReturnForm.h"
#include "RetailReturnMngForm.h"
#include <tchar.h>
#include "CheckQuery.h"
//#include "Supplier.h"
#include "\BIOrderManage\UnitBIOrder.h"
//#include "suppliermodify.h"
//#include "Stockcheckxuyi.h"
#include "fastcheck.h"
//#include "ZNProcureMng.h"
//#include "procurequery.h"
//#include "ZNruku.h"
//#include "ZNfahuo.h"
#include "Ysbooksale.h"
//#include "Ordermodify.h"
//#include "Unitchaigoufromorder.h"
//#include "Unitdistribute.h"
//#include "Unitask.h"
//#include "Unitsiglefenfa.h"
#include "StockAdjust.h"
#include "UnitDiaobo.h"
#include "ReturnStock.h"
#include "MemberOrder.h"
#include "Unitdaixiao.h"
#include "Unitshengdaifahuo.h"
#include "Unitwsalehuizhongsearch.h"
#include "TeacherFD.h"
#include "TeacherSearch.h"
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
   Rpdefine::DataID = IntToStr((int)HInstance);
	switch(reason)                                                 //手工增加
	{
		case DLL_PROCESS_ATTACH:
			CoInitialize(NULL);
			SetLocaleInfo(GetThreadLocale(), LOCALE_IDATE, _TEXT("2"));
            SetLocaleInfo(GetThreadLocale(), LOCALE_ITIME, _TEXT("1"));
			SetLocaleInfo(GetThreadLocale(), LOCALE_SDATE, _TEXT("yyyy-mm-dd"));
            SetLocaleInfo(GetThreadLocale(), LOCALE_STIME, _TEXT("HH-mm-ss"));
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
void __stdcall ManageMarketing(LandInfo* li,HWND MainHandle)
{                          //批销
	SendMessage(MainHandle,WM_SETREDRAW,0,0);
	Application = li->app;
	TfrmWholesaleMng* frm = new TfrmWholesaleMng(Application,1);
        frm->MainHandle=MainHandle;
	frm->Init(li);
        SendMessage(MainHandle,WM_SETREDRAW,1,0);
	RedrawWindow(MainHandle,NULL,0,RDW_FRAME|RDW_INVALIDATE | RDW_ALLCHILDREN|RDW_NOINTERNALPAINT);
}

void __stdcall ManageRetail(AnsiString powerlist,LandInfo* li,HWND MainHandle)
{                           //零售
	SendMessage(MainHandle,WM_SETREDRAW,0,0);
	Application = li->app;
	TfrmRetailMng* frm = new TfrmRetailMng(Application);
	//权限
   //powerchangdiscount,powerguadan,powertuihuan,powerinputprice
	if (powerlist.SubString(1,1)=="1") {
		frm->powerchangdiscount=true;
	}else frm->powerchangdiscount=false;

	if (powerlist.SubString(2,1)=="1") {
		frm->powerguadan=true;
	}else frm->powerguadan=false;

	if (powerlist.SubString(3,1)=="1") {
		frm->powertuihuan=true;
	}else frm->powertuihuan=false;

	if (powerlist.SubString(4,1)=="1") {
		frm->powerinputprice=true;
	}else frm->powerinputprice=false;



	frm->Init(li);
	SendMessage(MainHandle,WM_SETREDRAW,1,0);
	RedrawWindow(MainHandle,NULL,0,RDW_FRAME|RDW_INVALIDATE | RDW_ALLCHILDREN|RDW_NOINTERNALPAINT);


}

void __stdcall ManageOrder(LandInfo* li,HWND MainHandle)
{
	//SendMessage(MainHandle,WM_SETREDRAW,0,0);
  //	Application = li->app;
   //	TfrmOrderMng * frm = new TfrmOrderMng(Application);
   //	frm->Init(li);
   //	SendMessage(MainHandle,WM_SETREDRAW,1,0);
   //	RedrawWindow(MainHandle,NULL,0,RDW_FRAME|RDW_INVALIDATE | RDW_ALLCHILDREN|RDW_NOINTERNALPAINT);
}
void __stdcall DiaoxiaoCaigouFahuo(LandInfo* li,HWND MainHandle)
{                       //  省代发货
	SendMessage(MainHandle,WM_SETREDRAW,0,0);
  	Application = li->app;
   Tfrmshengdaifahuo * frm = new Tfrmshengdaifahuo(Application);
   frm->init(li);
   	SendMessage(MainHandle,WM_SETREDRAW,1,0);
   RedrawWindow(MainHandle,NULL,0,RDW_FRAME|RDW_INVALIDATE | RDW_ALLCHILDREN|RDW_NOINTERNALPAINT);
}



void __stdcall ManageProcurement(LandInfo* li,HWND MainHandle)
{
//	Application = li->app;
//	TfrmProcureMng* frm = new TfrmProcureMng(Application);
//	frm->Init(li);
}

void __stdcall DaiXiao(LandInfo* li,HWND MainHandle)
{                         //省代采购
               	SendMessage(MainHandle,WM_SETREDRAW,0,0);
      	Application = li->app;
	Tfrmdaixiao* frm = new Tfrmdaixiao(Application);
       frm->init(li->con,li->userID,li->storageID,li->UserName);

      	SendMessage(MainHandle,WM_SETREDRAW,1,0);
     	RedrawWindow(MainHandle,NULL,0,RDW_FRAME|RDW_INVALIDATE | RDW_ALLCHILDREN|RDW_NOINTERNALPAINT);
}
void __stdcall ManageStorage(LandInfo* li,HWND MainHandle)
{                      //入库
       	SendMessage(MainHandle,WM_SETREDRAW,0,0);
      	Application = li->app;
	TfrmStorageMng* frm = new TfrmStorageMng(Application);
	frm->Init(li);
      	SendMessage(MainHandle,WM_SETREDRAW,1,0);
     	RedrawWindow(MainHandle,NULL,0,RDW_FRAME|RDW_INVALIDATE | RDW_ALLCHILDREN|RDW_NOINTERNALPAINT);
}

void __stdcall CheckQuery(LandInfo* li,HWND MainHandle)
{                          //结帐查询
	SendMessage(MainHandle,WM_SETREDRAW,0,0);
	Application = li->app;
	TfrmCheckQuery* frm = new TfrmCheckQuery(Application);
	frm->stgid = li->storageID ;
	frm->Init(li->app, li->con);
	SendMessage(MainHandle,WM_SETREDRAW,1,0);
	RedrawWindow(MainHandle,NULL,0,RDW_FRAME|RDW_INVALIDATE | RDW_ALLCHILDREN|RDW_NOINTERNALPAINT);
}
void __stdcall SupplierManage(LandInfo* li,HWND MainHandle)
{
	
}
void __stdcall OrderManage(LandInfo *li,HWND MainHandle)
{
  /*Application = li->app ;
  TfrmOrderMng *frm = new TfrmOrderMng(Application);
  frm->Init(li); */
}
void __stdcall ProcureManage(LandInfo *li,HWND MainHandle)
{                   //采购
	SendMessage(MainHandle,WM_SETREDRAW,0,0);
	Application = li->app ;
	TfrmProcureMng *frm = new TfrmProcureMng(Application);
	frm->Init(li);
	SendMessage(MainHandle,WM_SETREDRAW,1,0);
	RedrawWindow(MainHandle,NULL,0,RDW_FRAME|RDW_INVALIDATE | RDW_ALLCHILDREN|RDW_NOINTERNALPAINT);
}

void __stdcall ManageReturnStorage(LandInfo* li,HWND MainHandle)
{                         //入库退货
      	SendMessage(MainHandle,WM_SETREDRAW,0,0);
	Application = li->app;
	TfrmStorageReturnMng* frm = new TfrmStorageReturnMng(Application);
	frm->Init(li);
       	SendMessage(MainHandle,WM_SETREDRAW,1,0);
      	RedrawWindow(MainHandle,NULL,0,RDW_FRAME|RDW_INVALIDATE | RDW_ALLCHILDREN|RDW_NOINTERNALPAINT);
}

void __stdcall ManageReturnMarketing(LandInfo* li,HWND MainHandle)
{                     //批肖退货
	SendMessage(MainHandle,WM_SETREDRAW,0,0);
	Application = li->app;
	TfrmWholesaleReturnMng* frm = new TfrmWholesaleReturnMng(Application);
       // frm->MainHandle=MainHandle;
	frm->Init(li);
	SendMessage(MainHandle,WM_SETREDRAW,1,0);
	RedrawWindow(MainHandle,NULL,0,RDW_FRAME|RDW_INVALIDATE | RDW_ALLCHILDREN|RDW_NOINTERNALPAINT);
}

void __stdcall ManageReturnRetail(LandInfo* li,HWND MainHandle)
{                      //零售退货
	SendMessage(MainHandle,WM_SETREDRAW,0,0);
	Application = li->app;
	TfrmRetailReturnMng* frm = new TfrmRetailReturnMng(Application);

	frm->Init(li);
	SendMessage(MainHandle,WM_SETREDRAW,1,0);
   RedrawWindow(MainHandle,NULL,0,RDW_FRAME|RDW_INVALIDATE | RDW_ALLCHILDREN|RDW_NOINTERNALPAINT);
}
void __stdcall StockAdjust(LandInfo *li,HWND MainHandle)
{                     //库存调整
  SendMessage(MainHandle,WM_SETREDRAW,0,0);
  Application = li->app ;
  TfrmStockAdjust * frm = new TfrmStockAdjust(Application);
  frm->init(li);
  frm->Show();
  SendMessage(MainHandle,WM_SETREDRAW,1,0);
  RedrawWindow(MainHandle,NULL,0,RDW_FRAME|RDW_INVALIDATE | RDW_ALLCHILDREN|RDW_NOINTERNALPAINT);
}
 void __stdcall BIOrderManage(LandInfo *li,int type,HWND MainHandle)
 {

                       //订单在用的
	SendMessage(MainHandle,WM_SETREDRAW,0,0);
   Application  = li->app ;
   TfrmBIorder * frm = new TfrmBIorder(Application);
   frm->type = type;
   frm->init(li);
   SendMessage(MainHandle,WM_SETREDRAW,1,0);
	RedrawWindow(MainHandle,NULL,0,RDW_FRAME|RDW_INVALIDATE | RDW_ALLCHILDREN|RDW_NOINTERNALPAINT);

 }


 void __stdcall fastcheck(LandInfo *li,HWND MainHandle)
{                       //当时快截结帐
	 SendMessage(MainHandle,WM_SETREDRAW,0,0);
	 Application = li->app ;
	 Tfrmfastcheck *frm = new Tfrmfastcheck(Application,li->con,li->storageID);
	 frm->username = li->UserName ;
	 frm->Show();
	 SendMessage(MainHandle,WM_SETREDRAW,1,0);
	 RedrawWindow(MainHandle,NULL,0,RDW_FRAME|RDW_INVALIDATE | RDW_ALLCHILDREN|RDW_NOINTERNALPAINT);
}


void __stdcall BIOrderManageDanHao(LandInfo *li,AnsiString Danhao,HWND MainHandle)
  {                //订单
	SendMessage(MainHandle,WM_SETREDRAW,0,0);
  	Application  = li->app ;
   TfrmBIorder * frm = new TfrmBIorder(Application);
   frm->init(li,Danhao);
   frm->Show();
  SendMessage(MainHandle,WM_SETREDRAW,1,0);
	RedrawWindow(MainHandle,NULL,0,RDW_FRAME|RDW_INVALIDATE | RDW_ALLCHILDREN|RDW_NOINTERNALPAINT);

  }

/*void __stdcall ZNStorage(LandInfo *li,HWND MainHandle)
{
	SendMessage(MainHandle,WM_SETREDRAW,0,0);
	Application = li->app ;
	TfrmZNruku *frm = new TfrmZNruku(Application);
	frm->Init(li);
SendMessage(MainHandle,WM_SETREDRAW,1,0);
	RedrawWindow(MainHandle,NULL,0,RDW_FRAME|RDW_INVALIDATE | RDW_ALLCHILDREN|RDW_NOINTERNALPAINT);
} */

/*void __stdcall ZNWsale(LandInfo *li,HWND MainHandle)
{
	SendMessage(MainHandle,WM_SETREDRAW,0,0);
	Application = li->app ;
	TfrmZNfahuo *frm = new TfrmZNfahuo(Application);
	frm->Init(li);
	SendMessage(MainHandle,WM_SETREDRAW,1,0);
	RedrawWindow(MainHandle,NULL,0,RDW_FRAME|RDW_INVALIDATE | RDW_ALLCHILDREN|RDW_NOINTERNALPAINT);
}
*/
 void __stdcall Ysbooksale(LandInfo *li,HWND MainHandle)
 {
	SendMessage(MainHandle,WM_SETREDRAW,0,0);
   Application  = li->app ;
   TfrmYsbooksale * frm = new TfrmYsbooksale(Application);
   frm->init(li);
   frm->Show();
   SendMessage(MainHandle,WM_SETREDRAW,1,0);
   RedrawWindow(MainHandle,NULL,0,RDW_FRAME|RDW_INVALIDATE | RDW_ALLCHILDREN|RDW_NOINTERNALPAINT);
 }


 void __stdcall DiaoBo(LandInfo *li,int modle,AnsiString Danhao,HWND MainHandle)
 {                 //调拨
	SendMessage(MainHandle,WM_SETREDRAW,0,0);
	Application  = li->app ;
        Tfrmdiaobo *frm;
        if (modle==10) {
               frm = new Tfrmdiaobo(Application,li->con,li->storageID,li->userID,0);//申请配送
        }else if (modle == 11) {
               frm = new Tfrmdiaobo(Application,li->con,li->storageID,li->userID,1);//申请配送
        }else
        {
            frm = new Tfrmdiaobo(Application,li->con,li->storageID,li->userID,modle);
        }

	frm->username = li->UserName  ;
        frm->ispowertozuofei=li->qfclient;
	frm->Show();
	if ((modle == 11)||(modle==10)) {
		frm->QryNtHeader(Danhao);
	}
	SendMessage(MainHandle,WM_SETREDRAW,1,0);
	RedrawWindow(MainHandle,NULL,0,RDW_FRAME|RDW_INVALIDATE | RDW_ALLCHILDREN|RDW_NOINTERNALPAINT);

 }

 void __stdcall ZNReturnStock(LandInfo *li,HWND MainHandle)
{                         //未动库存
	SendMessage(MainHandle,WM_SETREDRAW,0,0);
	Application = li->app ;
	TfrmReturnStock *frm = new TfrmReturnStock(Application,li->con,li->userID,li->storageID);
	frm->Show();
	SendMessage(MainHandle,WM_SETREDRAW,1,0);
	RedrawWindow(MainHandle,NULL,0,RDW_FRAME|RDW_INVALIDATE | RDW_ALLCHILDREN|RDW_NOINTERNALPAINT);
}
void __stdcall Catalogneworrecbsadmin(TApplication* app, TADOConnection* con,HWND MainHandle,LandInfo *li)
{                          //非省代快截发货
	SendMessage(MainHandle,WM_SETREDRAW,0,0);
	Application = app;
	Tfrmcatalogneworrec* frm = new Tfrmcatalogneworrec(Application,con);
        frm->init(li);
	frm->Show();
	SendMessage(MainHandle,WM_SETREDRAW,1,0);
	RedrawWindow(MainHandle,NULL,0,RDW_FRAME|RDW_INVALIDATE | RDW_ALLCHILDREN|RDW_NOINTERNALPAINT);
}
 void __stdcall pixiaohuizhong(LandInfo* li,HWND MainHandle)
 {
                         //批销汇总
	SendMessage(MainHandle,WM_SETREDRAW,0,0);
		Application = li->app ;
	Tfrmwsalehuizhong* frm = new Tfrmwsalehuizhong(Application);
		frm->init(li);
	frm->Show();
	SendMessage(MainHandle,WM_SETREDRAW,1,0);
	RedrawWindow(MainHandle,NULL,0,RDW_FRAME|RDW_INVALIDATE | RDW_ALLCHILDREN|RDW_NOINTERNALPAINT);

 }
void __stdcall Tearcher(LandInfo* li,HWND MainHandle)
{
	SendMessage(MainHandle,WM_SETREDRAW,0,0);
		Application = li->app ;
	TfrmteacherFD* frm = new TfrmteacherFD(Application);
		frm->init(li);
	frm->Show();
	SendMessage(MainHandle,WM_SETREDRAW,1,0);
	RedrawWindow(MainHandle,NULL,0,RDW_FRAME|RDW_INVALIDATE | RDW_ALLCHILDREN|RDW_NOINTERNALPAINT);
}

void __stdcall TearcherSearch(LandInfo* li,HWND MainHandle)
{
	SendMessage(MainHandle,WM_SETREDRAW,0,0);
	Application = li->app ;
	Tfrmteachersearch* frm = new Tfrmteachersearch(Application);
	frm->init(li);
	frm->Show();
	SendMessage(MainHandle,WM_SETREDRAW,1,0);
	RedrawWindow(MainHandle,NULL,0,RDW_FRAME|RDW_INVALIDATE | RDW_ALLCHILDREN|RDW_NOINTERNALPAINT);


}

