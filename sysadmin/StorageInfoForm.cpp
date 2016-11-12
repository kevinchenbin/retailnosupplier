//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "StorageInfoForm.h"
#include "Addstorge.h"
#include "Masterset.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "MDIChild"
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma resource "*.dfm"
TfrmStorageInfo *frmStorageInfo;
//---------------------------------------------------------------------------
__fastcall TfrmStorageInfo::TfrmStorageInfo(TComponent* Owner)
	: TfrmMDIChild(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageInfo::RzToolButton5Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void TfrmStorageInfo::Init(TADOConnection* con)
{
	query->Connection = con;
	fcon = con;
	AnsiString sql;
	sql = "select ID,Name,Tel,printtitle,Contact,Address,case when Master = 1 then '总店' else '分店' end as Master,case when id = " + IntToStr(storageid) + " then '√' else '' end as dangqian, case shendai when 1 then '是' else '否' end as shendai from SYS_StorageInfo ";
	/*if (!master) {
		sql = sql + " where id = " + IntToStr(storageid);
	}  */
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	if (!master) {
		BtnNew->Enabled = false;
		BtnAlignNone->Enabled = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageInfo::FormClose(TObject *Sender,
      TCloseAction &Action)
{
	Action = caFree;
}
//---------------------------------------------------------------------------


void __fastcall TfrmStorageInfo::RzToolButton1Click(TObject *Sender)
{
	if (query->IsEmpty() ) {
		return;
	}
	if (!master && storageid != query->FieldByName("ID")->AsInteger ) {
		ShowMsg(this->Handle,"当前店不是本店，无法进行此操作!",3);
		return;
	}
	TfrmAddstorge * frm = new TfrmAddstorge(Application,query,2);
	frm->userid = userid ;
	frm->storageid = storageid ;
	frm->ShowModal() ;
	delete frm;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageInfo::BtnNewClick(TObject *Sender)
{
	if (!master) {
		ShowMsg(this->Handle,"当前店不是本店，无法进行此操作!",3);
		return;
	}
	TfrmAddstorge * frm = new TfrmAddstorge(Application,query,1);
	frm->userid = userid ;
	frm->storageid = storageid ;
	frm->ShowModal();
	delete frm;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageInfo::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageInfo::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	//ShowMessage(Key);
	if (Key == 113 ) {    //添加
		BtnNew->Click();
	}
	if (Key ==114) {   //修改
		RzToolButton1->Click();
	}
	if (Key ==115) {   //设置总店
		BtnAlignNone->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 81 ) {    //退出
		RzToolButton2->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==90) {   //恢复窗口
		WindowState = wsNormal  ;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageInfo::BtnAlignNoneClick(TObject *Sender)
{
	if (query->IsEmpty() ) {
		return;
	}
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	AnsiString sql;
	sql = "select * from SYS_StorageInfo where master <> 1 ";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	if (aq->RecordCount == 0) {
		ShowMsg(this->Handle,"只有当前一个店铺，不能进行总店设置!",3);
		return;
	}
	TfrmMasterset *frm = new TfrmMasterset(Application,fcon);
	frm->ShowModal();
	delete frm;
	query->Active = false;
	query->Active = true;
        delete aq;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageInfo::dbGridCustCellClick(TColumn *Column)
{
	if (query->IsEmpty() ) {
		return;
	}
	if (!master && storageid != query->FieldByName("ID")->AsInteger ) {
		RzToolButton1->Enabled = false;
	}
	else
	{
		RzToolButton1->Enabled = true;
	}
}
//---------------------------------------------------------------------------




void __fastcall TfrmStorageInfo::rztoolshendaiClick(TObject *Sender)
{
//
  AnsiString sql ;

  if (query->FieldByName("shendai")->AsAnsiString =="是") {
    sql = "update SYS_StorageInfo set shendai =0 where id = "+query->FieldByName("id")->AsAnsiString ;
  }else sql = "update SYS_StorageInfo set shendai =1 where id = "+query->FieldByName("id")->AsAnsiString ;
    TADOQuery *aq = new TADOQuery(this);
    aq->Connection = fcon;
    aq->Close();
    aq->SQL->Clear();
    aq->SQL->Add(sql);
    aq->ExecSQL();


	sql = "select ID,Name,Tel,printtitle,Contact,Address,case when Master = 1 then '总店' else '分店' end as Master,case when id = " + IntToStr(storageid) + " then '√' else '' end as dangqian, case shendai when 1 then '是' else '否' end as shendai from SYS_StorageInfo ";
	/*if (!master) {
		sql = sql + " where id = " + IntToStr(storageid);
	}  */
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	if (!master) {
		BtnNew->Enabled = false;
		BtnAlignNone->Enabled = false;
	}




    delete aq;



}
//---------------------------------------------------------------------------

