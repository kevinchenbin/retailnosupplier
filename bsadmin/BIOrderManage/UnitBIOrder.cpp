//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitBIOrder.h"
#include "UnitSelectClient.h"
#include "SelectCatalogForm.h"
#include "SetNotesForm.h"
#include "UnitClient.h"
#include "QryNoteCodeForm.h"
#include "..\..\supplier\detailemessage.h"
#include "Addsyslog.h"
#include "NewBookinput.h"
#include "bookQuery.h"
#include "UnitSelectClient.h"
#include "orderExcelImport.h"
#include "UnitClient.h"
#include "NewBookModify.h"
//#include "Ordermodify.h"
#include "Unitchongfuorder.h"
#include "Unitorderquery.h"
#include "Unitfindbook.h"
#include "Unitgenhuanselect.h"
#include "NewBookinput1.h"
#include "retailbookup.h"
#include "bookhistory.h"
#include "..\bsadmin\bookQuery.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "RzLabel"
#pragma link "RzDBEdit"
#pragma link "RzEdit"
#pragma link "RzDBGrid"
#pragma resource "*.dfm"
TfrmBIorder *frmBIorder;
//---------------------------------------------------------------------------
__fastcall TfrmBIorder::TfrmBIorder(TComponent* Owner)
	: TfrmMDIChild(Owner)
{
	m_module = MTOrder;
	ClientID = -1;
	m_catalogSearchMode = 1;
	edtCatalog->MaxLength = 20;
	dtpdate->Date = Date();
	dtpfahuo->Date = Date();
	WindowState = wsMaximized ;
	scroll = 0;
}
void TfrmBIorder::init(LandInfo* li)
{
	TfrmMDIChild::Init(li);
	UserID = li->userID ;
	UserName =  li->UserName ;
	StgID = li->storageID ;
	fcon = li->con ;
          QFClientTiaoJian=" 1=1 ";
        QFSupplierTiaoJian=" 1=1 ";

        if (li->qfclient) {
           QFClientTiaoJian=" stgid="+IntToStr(m_storageID);
        }
         qfclietn= li->qfclient;

	query->Connection = li->con;
	querypress->Connection = fcon;
	TADOQuery *aq = new TADOQuery(NULL);
	aq->Connection = fcon;
	AnsiString sql;
	sql = "select ID,Name,Master from SYS_StorageInfo where id = " + IntToStr(StgID);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	labtitle->Caption = aq->FieldByName("Name")->AsString.Trim();
	Master = aq->FieldByName("Master")->AsBoolean ;


	sql = "select orprinttitle,orcontact,ortel,oraddress,orprintbk from sys_printtitle where stgid = " + IntToStr(m_storageID);
    query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();

	printbk = query->FieldByName("orprintbk")->AsAnsiString ;
	printtitle = query->FieldByName("orprinttitle")->AsAnsiString ;
	contact = query->FieldByName("orcontact")->AsAnsiString ;
	tel = query->FieldByName("ortel")->AsAnsiString ;
	address = query->FieldByName("oraddress")->AsAnsiString ;

	delete aq;
	aqupdatehead->Connection = fcon;
	try
	{
		aqhd->Connection = fcon;
		aqhd->Active = false;
		aqhd->Parameters->ParamByName("stgid")->Value = StgID;
		aqhd->Parameters->ParamByName("type")->Value = type;
		aqhd->Active = true;
	}
	catch(Exception &E)
	{
	  	ShowMessage(E.Message);
	}

	//SAddHead->Connection = fcon;
	ReadyDate();
	//RefreshHead();
	if (type == 0) {
		//cbtype->ItemIndex = 0;
		BtnNew->Click();
		/*if (!Master) {
			cbtype->ItemIndex = 1;
            BtnImport->Enabled = false;
		}   */
	}
	else if (type == 2) {
		//dbn->BtnClick(3);
		aqhd->Last();
		RefreshHead(aqhd->FieldByName("ID")->AsInteger );
		BtnNew->Visible = false;
		Label1->Caption = "网 上 订 单";
		cbtype->ItemIndex = 1;
	}

	edclient->SetFocus();
}
void TfrmBIorder::init(LandInfo*li,AnsiString Danhao)
{
    TfrmMDIChild::Init(li);
	type = 2;
	UserID = li->userID ;
	UserName =  li->UserName ;
	StgID = li->storageID ;
	fcon = li->con ;
	querypress->Connection = fcon;
	query->Connection =fcon;
	TADOQuery *aq = new TADOQuery(NULL);
	aq->Connection = fcon;
	AnsiString sql;
	sql = "select ID,Name,Master from SYS_StorageInfo where id = " + IntToStr(StgID);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	labtitle->Caption = aq->FieldByName("Name")->AsString.Trim();
	Master = aq->FieldByName("Master")->AsBoolean ;

	sql = "select orprinttitle,orcontact,ortel,oraddress,orprintbk from sys_printtitle where stgid = " + IntToStr(m_storageID);
    query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();

	printbk = query->FieldByName("orprintbk")->AsAnsiString ;
	printtitle = query->FieldByName("orprinttitle")->AsAnsiString ;
	contact = query->FieldByName("orcontact")->AsAnsiString ;
	tel = query->FieldByName("ortel")->AsAnsiString ;
	address = query->FieldByName("oraddress")->AsAnsiString ;


	aqupdatehead->Connection = fcon;
	if (StgID == 0) {
		cbtype->ItemIndex = 0;
		//cbtype->Enabled = false;
	}
	try
	{

		sql = " select A.*,S.ID as Sid,C.Name as Clientname,S.Name as StgName,U.ID,U.name as OpName from BS_OrderNoteHeader A "
			   " left join SYS_StorageInfo S ON A.stgID = S.ID "
			   " left join SYS_User U ON A.operatorID = U.ID left join CUST_customerinfo C ON C.ID = A.vendorID  where C.stgid="+IntToStr(StgID);
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
	}
	catch(Exception &E)
	{
		ShowMessage(E.Message);
	}
	//SAddHead->Connection = fcon;
	ReadyDate();
   //	RefreshHead();
	if (Danhao == "") {
		return;
	}
	TLocateOptions Opts;
	Opts.Clear();
	Opts << loPartialKey;

	if(aq->Locate("OrderNtCode", Variant(Danhao), Opts))
	{
		RefreshHead(aq->FieldByName("ID")->AsInteger );
	}
  //	Label1->Caption = "网 上 订 单";
	BtnNew->Visible = false;
	//edclient->SetFocus();
		delete aq;
}
void TfrmBIorder::ReadyDate()
{
	AnsiString sql = "select * from SYS_StaffInfo ";// where ID = " + IntToStr((int)(ccbclient->Items->Objects[ccbclient->ItemIndex])) ;
	TADOQuery *aq = new TADOQuery(NULL);
	aq->Connection = fcon;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	cbvendor->Items->Clear();
	while(!aq->Eof)
	{
	   cbvendor->Items->AddObject(aq->FieldByName("name")->AsAnsiString ,(TObject*)aq->FieldByName("ID")->AsInteger);
	   aq->Next();
	}
        cbvendor->ItemIndex=-1;
	sql = "select ID,Name from CUST_CustomerInfo where type in(2,3) and customerstate=1 and "+QFClientTiaoJian+"  order by name";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof )
	{
		cbclient->AddItem(aq->FieldByName("Name")->AsString ,(TObject*)aq->FieldByName("ID")->AsInteger );
		aq->Next();
	}

	sql = "select value from sys_bsset where name = 'lastorderdiscount'";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
    lastdiscount = aq->FieldByName("value")->AsBoolean ;

	sql = "select value,bk from sys_bsset where name = 'chongfuordertishi'";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	ordertishi = aq->FieldByName("value")->AsBoolean ;
	month = aq->FieldByName("bk")->AsString ;

	sql = "select value from sys_bsset where name = 'orderfind'";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	orderfind = aq->FieldByName("value")->AsBoolean ;

	sql = "select value from sys_bsset where name = 'orderchange'";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	orderchange = aq->FieldByName("value")->AsBoolean ;

	delete aq;
	ClientID = 1;

	cbclient->ItemIndex = cbclient->Items->IndexOfObject((TObject*)1);

}
void TfrmBIorder::AddNewHead()
{
	int ret;
	adospaddhead->Connection = fcon;
	adospaddhead->Parameters->ParamByName("@CustomerID")->Value  = 1;
	adospaddhead->Parameters->ParamByName("@type")->Value  = 0;
	adospaddhead->Parameters->ParamByName("@Bsmode")->Value  = 4;
	adospaddhead->Parameters->ParamByName("@OperatorID")->Value  = UserID ;
	adospaddhead->Parameters->ParamByName("@StgID")->Value  = StgID ;
	adospaddhead->ExecProc();
	ret =   adospaddhead->Parameters->ParamByName("@RETURN_VALUE")->Value;
	if (ret < 0 ) {

                ShowMsg(Handle ,"添加订单错误！",3);
	}else
	{
	   headid = ret;
	   RefreshHead(headid);
	   aqorderdetail->Active = false;
	   aqorderdetail->Parameters->ParamByName("ID")->Value = ret ;
	   aqorderdetail->Connection = fcon;
	   aqorderdetail->Active = true;
	   cbclient->Enabled = true;
	   SpeedButton2->Enabled = true;
	   aqhd->Active = false;
	   aqhd->Active = true;
	   logmessage = "添加一般订单" + aqupdatehead->FieldByName("OrderNtCode")->AsString ;
	   AddEvent(1,"一般订单窗口",UserID,StgID,logmessage,fcon);
	}
   // adospaddhead->Last();
}
AnsiString TfrmBIorder::GetField(AnsiString sql,AnsiString Field)
{
	TADOQuery * aq = new TADOQuery(NULL);
	aq->Connection = fcon;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	return	aq->FieldByName(Field)->AsAnsiString ;
	delete aq;
}
//---------------------------------------------------------------------------
void TfrmBIorder::ExecSQL(AnsiString sql)
{  	TADOQuery * aq = new TADOQuery(NULL);
	aq->Connection = fcon;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	delete aq;
}
//---------------------------------------------------------------------------
BOOL TfrmBIorder::UpdateHead()
{
	if (!aqupdatehead->Active) {
		  return false;
	}
	if (cbclient->Text == "" ) {

                ShowMsg(Handle ,"请选择客户！",3);
		return false;
	}

	aqupdatehead->Edit();
	aqupdatehead->FieldByName("state")->AsInteger = cbstate->ItemIndex;
	aqupdatehead ->FieldByName("type")->AsInteger = 	cbtype->ItemIndex ;
	aqupdatehead->FieldByName("hdtime")->AsDateTime = dtpdate->Date ;
	aqupdatehead->FieldByName("arravaldate")->AsDateTime = dtpfahuo->Date ;
	aqupdatehead->FieldByName("Remarks")->AsAnsiString  = membk->Text ;

	if (cbvendor->ItemIndex == -1) {
	  aqupdatehead->FieldByName("staffid")->AsInteger = -1;
	} else
	{
     	  aqupdatehead->FieldByName("staffid")->AsInteger = (int)(cbvendor->Items->Objects[cbvendor->ItemIndex]);
	}
	if (ClientID != -1 )
	{
	   aqupdatehead->FieldByName("vendorID")->AsInteger =  ClientID;
	}
	aqupdatehead->UpdateBatch(arCurrent);

	if (dbeditdanhao->Text == "") {
    	AnsiString sql;
	       //	sql = "update BS_OrderNoteHeader set OrderNtCode = dbo.UF_BS_BuildNtCode(" + IntToStr(m_storageID) + ", getdate(), 4,0) where id = " + aqupdatehead->FieldByName("id")->AsAnsiString ;
                sql = "exec NewOrder "+aqupdatehead->FieldByName("id")->AsAnsiString+","+ IntToStr(m_storageID) ;
		TADOQuery *aq = new TADOQuery(this);
		aq->Connection = fcon;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->ExecSQL();
		delete aq;
	}
	RefreshHead(aqupdatehead->FieldByName("id")->AsInteger);
	return true;
	//dbeditdanhao->Text = aqupdatehead->FieldByName("OrderNtCode")->AsAnsiString ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorder::BtnNewClick(TObject *Sender)
{
	DelInvalidNtHeader();
	edclientview();
	cbclient->ItemIndex = cbclient->Items->IndexOfObject((TObject*)1);
	ClientID = 1;
	dbn->Enabled = false;
	if (!Master) {
		cbtype->ItemIndex = 0;
      //  BtnImport->Enabled = false;
	}
	AddNewHead();
	if (!Master) {
		cbtype->ItemIndex = 0;
        //BtnImport->Enabled = false;
	}
	//dbn->BtnClick(3);   //最后一个
	edtCatalog->Text = "";
	editamount->Text = "0";
	editdiscount->Text = "100";
	editdetailbk->Text = "";
	cbtype->Enabled = true;
        BtnOK->Enabled = true;
}
//---------------------------------------------------------------------------
void TfrmBIorder::RefreshHead()
{
	int vendor;
	AnsiString sql;
	sql = "select A.*,S.ID,C.Name as Clientname,S.Name as StgName,U.ID,U.name as OpName from BS_OrderNoteHeader A "
			"left join SYS_StorageInfo S ON A.stgID = S.ID "
			"left join SYS_User U ON A.operatorID = U.ID "
			"left join CUST_customerinfo C ON C.ID = A.vendorID where A.StgID = " + IntToStr(StgID) + " and A.type = " + IntToStr(type) ;
	aqupdatehead->Close();
	aqupdatehead->SQL->Clear();
	aqupdatehead->SQL->Add(sql);
	aqupdatehead->Open();
	((TFloatField *)dshead->DataSet->FieldByName("addcosts"))->DisplayFormat = "￥0.00";
	cbclient->ItemIndex = cbclient->Items->IndexOfObject((TObject*)aqupdatehead->FieldByName("vendorID")->AsInteger );
	ClientID = aqupdatehead->FieldByName("vendorID")->AsInteger;
	cbstate->ItemIndex = aqupdatehead->FieldByName("state")->AsInteger ;
	cbtype->ItemIndex = aqupdatehead ->FieldByName("type")->AsInteger ;
	dtpdate->Date = aqupdatehead->FieldByName("hdtime")->AsDateTime ;
	dtpfahuo->Date  = aqupdatehead->FieldByName("arravaldate")->AsDateTime ;
	vendor = aqupdatehead->FieldByName("staffid")->AsInteger;
	lblOpName->Caption =  aqupdatehead->FieldByName("OpName")->AsString;
	membk->Text =  aqupdatehead->FieldByName("Remarks")->AsString;
	for (int i =0; i < cbvendor->Items->Count ; i++) {
	  if ((int)(cbvendor->Items->Objects[i])== vendor) {
		  cbvendor->ItemIndex = i;
		  break;
	  }
	}         //更新明细
	RefreshDetail();

	if (aqupdatehead->FieldByName("shenheistate")->AsInteger == 1) {
		BtnOK1->Enabled = false;
		BtnCancel->Enabled = true;
		BtnOK->Enabled = false;
		BtnProperties->Enabled = false;
		BtnDelete->Enabled = false;
		BtnChangeOptions->Enabled = false;
		SpeedButton1->Visible = true;
		edtCatalog->Enabled = false;
		editamount->Enabled = false;
		editdiscount->Enabled = false;
		//GroupBox2->Enabled = false;
	}
	else
	{
		BtnOK1->Enabled = true;
		BtnCancel->Enabled = false;
		BtnOK->Enabled = true;
		BtnProperties->Enabled = true;
		BtnDelete->Enabled = true;
		BtnChangeOptions->Enabled = true;
		SpeedButton1->Visible = false;
		edtCatalog->Enabled = true;
		editamount->Enabled = true;
		editdiscount->Enabled = true;
		//GroupBox2->Enabled = true;
	}
	if (cbtype->Text == "内部订单") {
		if (Master) {
			BtnLastRecord->Enabled = true;
		}
		else
		{
			BtnLastRecord->Enabled = false;
		}
		dgdetail->Columns->Items[16]->Field = aqorderdetail->FieldByName("prostate");
	}
	else
	{
		BtnLastRecord->Enabled = false;
		dgdetail->Columns->Items[16]->Field = aqorderdetail->FieldByName("needprocurenum");
	}
}
//---------------------------------------------------------------------------
void TfrmBIorder::RefreshHead(AnsiString headerCode)
{
	int vendor;
	edclientview();
	AnsiString sql;
	scroll = 1;
	sql = "select A.*,S.ID,C.Name as Clientname,S.Name as StgName,U.ID,U.name as OpName from BS_OrderNoteHeader A "
			"left join SYS_StorageInfo S ON A.stgID = S.ID "
			"left join SYS_User U ON A.operatorID = U.ID "
			"left join CUST_customerinfo C ON C.ID = A.vendorID where A.orderNtCode = " + headerCode + " and A.type =1 ";
	aqupdatehead->Close();
	aqupdatehead->SQL->Clear();
	aqupdatehead->SQL->Add(sql);
	aqupdatehead->Open();
	((TFloatField *)dshead->DataSet->FieldByName("addcosts"))->DisplayFormat = "￥0.00";
	cbclient->ItemIndex = cbclient->Items->IndexOfObject((TObject*)aqupdatehead->FieldByName("vendorID")->AsInteger );
    ClientID = aqupdatehead->FieldByName("vendorID")->AsInteger;
	cbstate->ItemIndex = aqupdatehead->FieldByName("state")->AsInteger ;
	cbtype->ItemIndex = aqupdatehead ->FieldByName("type")->AsInteger ;
	dtpdate->Date = aqupdatehead->FieldByName("hdtime")->AsDateTime ;
	dtpfahuo->Date  = aqupdatehead->FieldByName("arravaldate")->AsDateTime ;
	vendor = aqupdatehead->FieldByName("staffid")->AsInteger;
	lblOpName->Caption =  aqupdatehead->FieldByName("OpName")->AsString;
	membk->Text =  aqupdatehead->FieldByName("Remarks")->AsString;
	for (int i =0; i < cbvendor->Items->Count ; i++) {
	  if ((int)(cbvendor->Items->Objects[i])== vendor) {
		  cbvendor->ItemIndex = i;
		  break;
	  }
	}         //更新明细

	RefreshDetail();
	if (aqupdatehead->FieldByName("shenheistate")->AsInteger == 1) {
		BtnOK1->Enabled = false;
		BtnCancel->Enabled = true;
		BtnOK->Enabled = false;
		BtnProperties->Enabled = false;
		BtnDelete->Enabled = false;
		BtnChangeOptions->Enabled = false;
		SpeedButton1->Visible = true;
		edtCatalog->Enabled = false;
		editamount->Enabled = false;
		editdiscount->Enabled = false;
	   //	GroupBox2->Enabled = false;
	  //	cbtype->Enabled = false;
	}
	else
	{
		BtnOK1->Enabled = true;
		BtnCancel->Enabled = false;
		BtnOK->Enabled = true;
		BtnProperties->Enabled = true;
		BtnDelete->Enabled = true;
		BtnChangeOptions->Enabled = true;
		SpeedButton1->Visible = false;
		edtCatalog->Enabled = true;
		editamount->Enabled = true;
		editdiscount->Enabled = true;
	  //	GroupBox2->Enabled = true;
	  //	cbtype->Enabled = false;
	}
	if (cbtype->Text == "内部订单") {
		if (Master) {
			BtnLastRecord->Enabled = true;
		}
		else
		{
			BtnLastRecord->Enabled = false;
		}
		dgdetail->Columns->Items[16]->Field = aqorderdetail->FieldByName("prostate");
	}
	else
	{
		BtnLastRecord->Enabled = false;
		dgdetail->Columns->Items[16]->Field = aqorderdetail->FieldByName("needprocurenum");
	}
}
void TfrmBIorder::RefreshHead(int headerid)
{
	int vendor;
	edclientview();
	AnsiString sql;
	sql = "select A.*,S.ID,C.Name as Clientname,S.Name as StgName,U.ID,U.name as OpName from BS_OrderNoteHeader A "
			"left join SYS_StorageInfo S ON A.stgID = S.ID "
			"left join SYS_User U ON A.operatorID = U.ID "
			"left join CUST_customerinfo C ON C.ID = A.vendorID where A.id = " + IntToStr(headerid) ;
	aqupdatehead->Close();
	aqupdatehead->SQL->Clear();
	aqupdatehead->SQL->Add(sql);
	aqupdatehead->Open();
	scroll = 1;
	((TFloatField *)dshead->DataSet->FieldByName("addcosts"))->DisplayFormat = "￥0.00";
	cbclient->ItemIndex = cbclient->Items->IndexOfObject((TObject*)aqupdatehead->FieldByName("vendorID")->AsInteger );
    ClientID = aqupdatehead->FieldByName("vendorID")->AsInteger;
	cbstate->ItemIndex = aqupdatehead->FieldByName("state")->AsInteger ;
	cbtype->ItemIndex = aqupdatehead ->FieldByName("type")->AsInteger ;
	dtpdate->Date = aqupdatehead->FieldByName("hdtime")->AsDateTime ;
	dtpfahuo->Date  = aqupdatehead->FieldByName("arravaldate")->AsDateTime ;
	vendor = aqupdatehead->FieldByName("staffid")->AsInteger;
	lblOpName->Caption =  aqupdatehead->FieldByName("OpName")->AsString;
	membk->Text =  aqupdatehead->FieldByName("Remarks")->AsString;
	for (int i =0; i < cbvendor->Items->Count ; i++) {
	  if ((int)(cbvendor->Items->Objects[i])== vendor) {
		  cbvendor->ItemIndex = i;
		  break;
	  }
	}         //更新明细

	RefreshDetail();
	if (aqupdatehead->FieldByName("shenheistate")->AsInteger == 1) {
		BtnOK1->Enabled = false;
		BtnCancel->Enabled = true;
		BtnOK->Enabled = false;
		BtnProperties->Enabled = false;
		BtnDelete->Enabled = false;
		BtnChangeOptions->Enabled = false;
		SpeedButton1->Visible = true;
		edtCatalog->Enabled = false;
		editamount->Enabled = false;
		editdiscount->Enabled = false;
	  //	GroupBox2->Enabled = false;
	   //	cbtype->Enabled = false; //订单类型不能改
	}
	else
	{
		BtnOK1->Enabled = true;
		BtnCancel->Enabled = false;
		BtnOK->Enabled = true;
		BtnProperties->Enabled = true;
		BtnDelete->Enabled = true;
		BtnChangeOptions->Enabled = true;
		SpeedButton1->Visible = false;
		edtCatalog->Enabled = true;
		editamount->Enabled = true;
		editdiscount->Enabled = true;
	  //	GroupBox2->Enabled = true;
	   //	cbtype->Enabled = false;
	}
	if (cbtype->Text == "内部订单") {
		if (Master) {
			BtnLastRecord->Enabled = true;
		}
		else
		{
			BtnLastRecord->Enabled = false;
		}
		dgdetail->Columns->Items[16]->Field = aqorderdetail->FieldByName("prostate");
	}
	else
	{
		BtnLastRecord->Enabled = false;
		dgdetail->Columns->Items[16]->Field = aqorderdetail->FieldByName("needprocurenum");
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorder::BtnOKClick(TObject *Sender)
{
	if (!GroupBox1->Enabled) {
		return;
	}
	try
	{
		HeaderRec = aqupdatehead->RecNo;
		if (!UpdateHead())
		{
			return ;
	   	}
	}
	catch(...)
	{
		ShowMsg(Handle ,"保存失败，请重试！",3);
		return;
	}
	//MessageBoxA(0,"保存成功!","提示",MB_ICONWARNING);
	//GroupBox1->Enabled = false;

	edclient->Enabled = false;
	cbclient->Enabled = false;
	SpeedButton2->Enabled = false;
	dtpdate->Enabled = false;
	dtpfahuo->Enabled = false;

	cbtype->Enabled = false;
	cbvendor->Enabled = false;
	dbeditaddcost->Enabled = false;

        BtnOK->Enabled = false;
	GroupBox2->Enabled = true;
	edtCatalog->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorder::dbnClick(TObject *Sender, TNavigateBtn Button)
{
	DelInvalidNtHeader();
	edclientview();
	int  vendor;

	RefreshHead(aqhd->FieldByName("ID")->AsInteger );
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorder::lblCatalogMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	if (Button == mbLeft ) {
		TPoint  pt;
		GetCursorPos(&pt);
		pm->Popup(pt.x,pt.y);

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorder::N1Click(TObject *Sender)
{
	lblCatalog->Caption = "书号";
	m_catalogSearchMode=1;
	edtCatalog->MaxLength = 15;
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorder::N2Click(TObject *Sender)
{
	lblCatalog->Caption = "自编码";
	m_catalogSearchMode=2;
	edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorder::N3Click(TObject *Sender)
{
	lblCatalog->Caption = "书名";
	m_catalogSearchMode=3;
	edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorder::N4Click(TObject *Sender)
{
	lblCatalog->Caption = "定价";
	m_catalogSearchMode=6;
	edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorder::edtCatalogKeyPress(TObject *Sender, wchar_t &Key)
{
	if (m_catalogSearchMode == 6) {
		if ((Key < '0' || Key > '9') && (Key != '\b') && (Key != '.') && (Key != '\r') ) {
            Key = NULL;
		}
	}

	if (Key == '\r')
	{
		if (edtCatalog->Text == "") {
			ChangeCatalogSearchMode();
		}
		else
		{
			float price;
			if (m_catalogSearchMode == 6) {
			try {
					price = StrToFloat(edtCatalog->Text.Trim());
				} catch (...) {
					ShowMsg(Handle ,"请输入正确的定价！",3);
					return;
				}
			}
			int results;

			TfrmSelectCatalog* frm = new TfrmSelectCatalog(Application,fcon);
			LandInfo li;
			li.app = Application;
			li.con = fcon;
			li.userID = UserID ;
			li.storageID = StgID ;
			frm->Init(&li);
			frm->DoModalType = 4;
			frm->order  = this;
			frm->SetSearchMode(m_catalogSearchMode, edtCatalog->Text);
			frm->SelectAll = false;

                        //期刊处理
                        if (edtCatalog->Text.Trim().Length()>13) {

                           frm->qikan= true;
                           frm->qikanhao =edtCatalog->Text.SubString(14,edtCatalog->Text.Trim().Length()-13) ;
                        }

			frm->QryBkInfo();
			if (frm->findbooks == 3) {
				results= frm->ShowModal();
			}else if (frm->findbooks==1) {
				results = 1;
			}else if ((frm->findbooks==0)||(frm->findbooks==-1)) {
				results = -1 ;
			}

			if (mrOk == results)
			{
				int bkinfoid = -1,catalogID = -1;
				if (frm->SelectAll) {
					 for (int i = 0; i < frm->lengthint; i++) {
						 if (chongfutishi(frm->BkcatalogiD[i])) {
							AddNote(1,frm->BkcatalogiD[i]);
						 }
					 }
                     RefreshDetail();
				}else
				{
					frm->GetSelectResult(bkinfoid,catalogID);
					if (catalogID >= 0)
					{
						TLocateOptions   Opts;
						Opts.Clear();
						Opts   <<   loPartialKey;
						String   str   = AnsiString(catalogID);
						if ( !aqorderdetail->Locate("bkcatalogid",str,Opts))
						{
							if (chongfutishi(catalogID)) {
								AddNote(0, catalogID);
								editamount->Enabled = true;
								editdiscount->Enabled = true;
								edtCatalog->Text  = "";

								if (chfoceset->Checked) {
									if (chfsamount->Checked ) {
										Perform(WM_NEXTDLGCTL, 0, 0);
									}
									else if (chfsdiscount->Checked ) {
										editdiscount->SetFocus();
									}
									else if (chfsluru->Checked) {
										edtCatalog->SetFocus();
									}
								}
								else
								{
									Perform(WM_NEXTDLGCTL, 0, 0);
								}
							}
							else
							{
								edtCatalog->Text  = "";
								edtCatalog->SetFocus();
							}
						}
						else
						{
                            ShowMsg(Handle ,"有相同记录请核实！",3);
							dgdetail->SetFocus();
							dgdetail->SelectedRows->CurrentRowSelected = true;
							edtCatalog->Text  = "";
							editamount->SetFocus();
						}
					}
				}
			}
			else
			{
				if (!frm->findbook) {     //产生新书
					if (aqupdatehead->Active && aqupdatehead->RecordCount >= 1)
					{
						Tfrmnewbook1 *frma = new Tfrmnewbook1(Application,fcon);
						frma->BIorder = this;
						frma->modle = 4;

						frma->editcode->Text = edtCatalog->Text ;
                                                //处理期刊新书
                                                if ( edtCatalog->Text.Trim().Length()>13) {
                                                         frma->cbsaletype->Text = "期刊";
                                                         frma->editqikanmao->Text =edtCatalog->Text.Trim();
                                                         frma->cbsaletypeChange(this);
                                                         PostMessage(frma->editqikanmao->Handle, WM_KEYDOWN,VK_RETURN,0);
                                                }

						if (mbOK == frma->ShowModal())
						{

						}
						delete frma;
                                                editamount->Enabled= true;
                                                editdiscount->Enabled = true;
						editamount->SetFocus();
					}
				}
			}
			delete frm;
		}
	}
}

//---------------------------------------------------------------------------

void TfrmBIorder::ChangeCatalogSearchMode()
{
	if (m_catalogSearchMode==3) {
		m_catalogSearchMode=5;
	}else
	{
	m_catalogSearchMode++;  }
	if (m_catalogSearchMode >= 7)
	{
		m_catalogSearchMode = 1;
	}

	switch (m_catalogSearchMode)
	{
	case 1:
		edtCatalog->MaxLength = 15;
		lblCatalog->Caption = "书号";
		break;
	case 2:
		edtCatalog->MaxLength = 0;
		lblCatalog->Caption = "自编码";
		break;
	case 3:
		edtCatalog->MaxLength = 0;
		lblCatalog->Caption = "书名";
		break;
	case 5:
		edtCatalog->MaxLength = 0;
		lblCatalog->Caption = "作者";
		break;
	case 6:
		edtCatalog->MaxLength = 0;
		lblCatalog->Caption = "定价";
		break;
    default:
        break;
	}
}
//---------------------------------------------------------------------------

void TfrmBIorder::AddNote(int modle,int CatalogID)
{
	if (!aqupdatehead->Active) {
		return;
	}
	TLocateOptions Opts;
	Opts.Clear();
	Opts   <<   loPartialKey;
	String   str   = AnsiString(CatalogID);
	if ( !aqorderdetail->Locate("bkcatalogid",str,Opts))
	{
		editamount->Text = "0";
		editdiscount->Text = "100";
		editdetailbk->Text = "";
		aqorderdetail->Append();
		AnsiString sql;
		if (lastdiscount) {
			sql = "select top 1 BS_OrderNote.discount from BS_OrderNote left join BS_OrderNoteHeader on BS_OrderNote.OrderNtHeaderID = BS_OrderNoteHeader.id where BS_OrderNote.BkcatalogID = " + IntToStr(CatalogID) + " and BS_OrderNoteHeader.VendorID = " + IntToStr(ClientID) + " and BS_OrderNote.state = 0 order by BS_OrderNote.id desc";
			query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->Open();
			if (query->RecordCount > 0) {
				aqorderdetail->FieldByName("Discount")->AsFloat = query->FieldByName("discount")->AsFloat ;
				editdiscount->Text = query->FieldByName("discount")->AsAnsiString ;
                                editamount->Text = "0";
			}else
                        {
                          editamount->Text = "0";
                          editdiscount->Text = "100";
                        }
		}

		aqorderdetail->FieldByName("OrderNtHeaderID")->AsInteger = aqupdatehead->FieldByName("ID")->AsInteger ;
		aqorderdetail->FieldByName("bkcatalogid")->AsInteger = CatalogID;
		aqorderdetail->UpdateBatch(arCurrent);
		if (modle == 0) {
        	RefreshDetail();
		}
	}
	else
	{
   	}
}
//---------------------------------------------------------------------------

void TfrmBIorder::RefreshDetail()
{
	querypress->Active = false;
	querypress->Parameters->ParamByName("ID")->Value = aqupdatehead->FieldByName("ID")->AsInteger ;
	querypress->Active = true;
	edpress->Text = querypress->FieldByName("presscount")->AsAnsiString ;
	aqorderdetail->Active = false;
	aqorderdetail->Parameters->ParamByName("ID")->Value = aqupdatehead->FieldByName("ID")->AsInteger ;
	aqorderdetail->Connection = fcon;
	aqorderdetail->Active = true;
	if (aqupdatehead->FieldByName("OrderNtCode")->AsAnsiString != "0") {
		GroupBox2->Enabled = true;
		//GroupBox1->Enabled = false;

		edclient->Enabled = false;
		cbclient->Enabled = false;
		SpeedButton2->Enabled = false;
		dbeditaddcost->Enabled = false;
		dtpdate->Enabled = false;
		dtpfahuo->Enabled = false;
		cbtype->Enabled = false;
		cbvendor->Enabled = false;
		//membk->Enabled = false;

		((TFloatField *)dgdetail->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00%";
		((TFloatField *)dgdetail->DataSource->DataSet->FieldByName("price"))->DisplayFormat = "￥0.00";
		((TFloatField *)dgdetail->DataSource->DataSet->FieldByName("fixedPrice"))->DisplayFormat = "￥###,###,##0.00";
		((TFloatField *)dgdetail->DataSource->DataSet->FieldByName("Discountedprice"))->DisplayFormat = "￥###,###,##0.00";
	}
	else
	{
		GroupBox2->Enabled = false;
		GroupBox1->Enabled = true;

		edclient->Enabled = true;
		cbclient->Enabled = true;
		SpeedButton2->Enabled = true;
		dbeditaddcost->Enabled = true;
		dtpdate->Enabled = true;
		dtpfahuo->Enabled = true;
		membk->Enabled = true;
		cbtype->Enabled = true;
		cbvendor->Enabled = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorder::editamountKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
		if (!aqupdatehead->Active) {
			return;
   		}
                if (editamount->Text.Trim()=="") {
                  return;
                }
	    AnsiString sql;
		TLocateOptions   Opts;
		Opts.Clear();
		Opts   <<   loPartialKey;
		AnsiString bkcatalogid;
		bkcatalogid = aqorderdetail->FieldByName("bkcatalogid")->AsString;
		//aqorderdetail->Locate("bkcatalogid",bkcatalogid,Opts);

              int amouttt;
              try
              {
                amouttt= StrToInt(editamount->Text.Trim());
              }catch(...)
              {
                return;
              }
	   aqorderdetail->Edit() ;
	   aqorderdetail->FieldByName("amount")->AsInteger = amouttt ;
	   aqorderdetail->UpdateBatch(arCurrent);
	   //aqupdatehead->Active = false;
	   //aqupdatehead->Active = true;
	   RefreshHead(aqupdatehead->FieldByName("ID")->AsInteger );

	   aqorderdetail->Locate("bkcatalogid",bkcatalogid,Opts);

	   if (chfoceset->Checked) {
			if (chfsdiscount->Checked) {
				Perform(WM_NEXTDLGCTL, 0, 0);
			}
			else if (chfsluru->Checked) {
				edtCatalog->SetFocus();
			}
			else if (chfsamount->Checked) {
				if (!aqorderdetail->Eof) {
					dgdetail->SetFocus();
					aqorderdetail->Next();
					dgdetail->SelectedRows->CurrentRowSelected = true;
					editamount->SetFocus();
				}
			}
		}
		else
		{
			Perform(WM_NEXTDLGCTL, 0, 0);
		}

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorder::editdiscountKeyPress(TObject *Sender, wchar_t &Key)
{
	if ((Key < '0' || Key > '9') && (Key != '\b') && (Key != '.') && (Key != '\r') ) {
    	Key = NULL;
	}
	if (Key == VK_RETURN) {
	 if (!aqupdatehead->Active) {
	   return;
   }
     if (editdiscount->Text.Trim()=="") {
         return;
     }
       AnsiString sql;
		TLocateOptions   Opts;
		Opts.Clear();
		Opts   <<   loPartialKey;
		AnsiString bkcatalogid;
		bkcatalogid = aqorderdetail->FieldByName("bkcatalogid")->AsString;
		//aqorderdetail->Locate("bkcatalogid",bkcatalogid,Opts);
	   aqorderdetail->Edit() ;
	   try {
			aqorderdetail->FieldByName("Discount")->AsFloat =  StrToFloat(editdiscount->Text);
	   } catch (...) {

                        ShowMsg(Handle ,"请输入正确的折扣！",3);
			return;
	   }
	   aqorderdetail->UpdateBatch(arCurrent);
	   //aqupdatehead->Active = false;
	   //aqupdatehead->Active = true;
	   RefreshHead(aqupdatehead->FieldByName("ID")->AsInteger );

	   aqorderdetail->Locate("bkcatalogid",bkcatalogid,Opts);

	   if (chfoceset->Checked) {
			if (chfsluru->Checked) {
				edtCatalog->SetFocus();
			}
			else if (chfsamount->Checked) {
				if (!aqorderdetail->Eof) {
					dgdetail->SetFocus();
					aqorderdetail->Next();
					dgdetail->SelectedRows->CurrentRowSelected = true;
					editamount->SetFocus();
				}
			}
			else if (chfsdiscount->Checked) {
				if (!aqorderdetail->Eof) {
					dgdetail->SetFocus();
					aqorderdetail->Next();
					dgdetail->SelectedRows->CurrentRowSelected = true;
					editdiscount->SetFocus();
				}
			}
		}
		else
		{       edtCatalog->SetFocus();
		       //	Perform(WM_NEXTDLGCTL, 0, 0);
		}

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorder::editdetailbkKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
		if (aqupdatehead->IsEmpty() ) {
			return;
		}
		if (aqorderdetail->IsEmpty() ) {
			return;
		}
		aqorderdetail->Edit() ;
		aqorderdetail->FieldByName("bk")->AsAnsiString  = editdetailbk->Text ;
		aqorderdetail->UpdateBatch(arCurrent);
		if (edtCatalog->Enabled ) {
			edtCatalog->SetFocus();
		}
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmBIorder::BtnDeleteClick(TObject *Sender)
{
	if (aqorderdetail->IsEmpty() ) {
		return;
	}
        AnsiString IDSTR,IDSTR2;
	if (ShowMsg(Handle ,"确定要删除该记录吗？",1)==1)
	{
	//aqorderdetail->Edit();
	//aqorderdetail->Delete();
		TADOQuery * aq = new TADOQuery(NULL);
		aq->Connection = fcon;
                aqorderdetail->Prior();
                IDSTR2 =  aqorderdetail->FieldByName("id")->AsString;
                aqorderdetail->Next();
		for (int i =0; i < dgdetail->SelectedRows->Count ; i++) {
			aqorderdetail->GotoBookmark(dgdetail->SelectedRows->Items[i]);
			logmessage = "删除订单" + aqupdatehead->FieldByName("OrderNtCode")->AsString + "的书目《" + aqorderdetail->FieldByName("bookname")->AsString + "》";
			AddEvent(1,"一般订单窗口",UserID,StgID,logmessage,fcon);
			AnsiString sql = "delete from BS_OrderNote where id = " + aqorderdetail->FieldByName("id")->AsString ;

			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->ExecSQL();
		}
                 aqorderdetail->Next();
                 IDSTR = aqorderdetail->FieldByName("id")->AsString;
		delete aq;
		aqorderdetail->Active = false;
		aqorderdetail->Active = true;

                    TLocateOptions Opts;
                    Opts.Clear();
                     Opts << loPartialKey;

                if(!aqorderdetail->Locate("id", Variant(IDSTR), Opts))
                {
                  aqorderdetail->Locate("id", Variant(IDSTR2), Opts);


                }



	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorder::BtnChangeOptionsClick(TObject *Sender)
{
			if (aqorderdetail->IsEmpty() ) {
            	return;
			}
			if (dgdetail->SelectedRows->Count == 0 || dgdetail->SelectedRows->Count == 1) {
				for (int i = 1; i <= aqorderdetail->RecordCount ; i++) {
					dgdetail->DataSource->DataSet->RecNo = i;
					dgdetail->SelectedRows->CurrentRowSelected = true;
				}
			}
			TfrmSetNotes* frm = new TfrmSetNotes(this);
			frm->ChangeBsmode(1);
			if (frm->ShowModal() == mrOk)
			{
				int amount = 0;
				float discount = 0;
				bool bsetAmount = frm->GetAmount(amount);
				bool bsetDiscount = frm->GetDiscount(discount);
				if (bsetAmount && bsetDiscount)
				{
					BatchSetNotes(amount, discount, 1);
				}
				else if (bsetAmount && !bsetDiscount)
				{
					BatchSetNotes(amount, discount, 2);
				}
				else if (!bsetAmount && bsetDiscount)
				{
                	BatchSetNotes(amount, discount, 3);
				}
				//RefreshDetail();
				RefreshHead(aqupdatehead->FieldByName("ID")->AsInteger );
			}
}
void TfrmBIorder::BatchSetNotes(int amount, float discount, int mode)
{
	if (aqorderdetail->IsEmpty() ) {
		return;
	}

		switch(mode)
		{
		case 1://两者均更新

			 for (int i =0; i < dgdetail->SelectedRows->Count ; i++) {
				aqorderdetail->GotoBookmark(dgdetail->SelectedRows->Items[i]);
				aqorderdetail->Edit();
				aqorderdetail->FieldByName("amount")->AsInteger = amount;
				aqorderdetail->FieldByName("Discount")->AsFloat  = discount;
                aqorderdetail->UpdateBatch(arCurrent);
			 }

			break;
		case 2://只更新Amount

			try
			{
				 for (int i =0; i < dgdetail->SelectedRows->Count ; i++) {
				aqorderdetail->GotoBookmark(dgdetail->SelectedRows->Items[i]);
				aqorderdetail->Edit();
				aqorderdetail->FieldByName("amount")->AsInteger = amount;
				aqorderdetail->UpdateBatch(arCurrent);
			 }
			}
			__finally
			{
				LockWindowUpdate(NULL);
			}
			break;
		case 3://只更新Discount

			try
			{
               	 for (int i =0; i < dgdetail->SelectedRows->Count ; i++) {
				aqorderdetail->GotoBookmark(dgdetail->SelectedRows->Items[i]);
				aqorderdetail->Edit();
				aqorderdetail->FieldByName("Discount")->AsFloat  = discount;
                aqorderdetail->UpdateBatch(arCurrent);
			 }
			}
			__finally
			{
				LockWindowUpdate(NULL);
			}
			break;
		default:
			break;
		}
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorder::SpeedButton2Click(TObject *Sender)
{
		AnsiString sql;
		TADOQuery * aq = new TADOQuery(NULL);
		aq->Connection = fcon;
		sql = "select * from cust_customerinfo where type in(2,3) and customerstate=1 and "+QFClientTiaoJian;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		int count1 = aq->RecordCount ;
		TDetaileForm * frm = new TDetaileForm(Application,2,1,0 ,fcon,StgID);
		frm->ShowModal();
		delete frm;
		sql = "select * from cust_customerinfo where type in(2,3) and customerstate=1 and "+QFClientTiaoJian;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
        cbclient->Clear();
		while (!aq->Eof)
		{
                        cbclient->AddItem(aq->FieldByName("Name")->AsString ,(TObject*)aq->FieldByName("ID")->AsInteger );
			aq->Next();
		}
		int count2 = aq->RecordCount ;
		if (count2 > count1) {
			sql = "select top 1 ID,Name from cust_customerinfo where customerstate=1 and "+QFClientTiaoJian+" order by ID desc ";
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();
			ClientID =	aq->FieldByName("ID")->AsInteger  ;
			cbclient->ItemIndex = cbclient->Items->IndexOfObject((TObject*)ClientID );
			cbclient->SetFocus();
		}
		delete aq;
}

//---------------------------------------------------------------------------

void __fastcall TfrmBIorder::BtnViewClick(TObject *Sender)
{
	if (orderfind) {
		if (!CheckOperateAuthority())
		return;
	}

		Tfrmorderquery *frm = new Tfrmorderquery(Application,fcon,StgID,1,0,UserName,qfclietn);
		if (Master) {
			frm->chinorder ->Visible = true;
		}
                frm->enableshenghe();

		if (frm->ShowModal()==mrOk ) {
        	edclientview();
        	DelInvalidNtHeader();
        	dbn->Enabled = true;
		   AnsiString code = frm->GetNoteCode();
		   AnsiString sqlwhere = frm->GetWhere();
		   AnsiString sql;
		   if (sqlwhere != "") {
			   sql = " select * from BS_OrderNoteHeader " + sqlwhere;
			   aqhd->Close();
			   aqhd->SQL->Clear();
			   aqhd->SQL->Add(sql);
			   aqhd->Open();
		   }
		 AnsiString str =  LeftBStr(code,2);
		   if (str == "00") {
			code = AnsiRightStr(code,code.Length()-2) ;

		}else
		   {
			  str = LeftBStr(code,1);
			  if (str == "0") {
						code = AnsiRightStr(code,code.Length()-1) ;
			  }

		   }

			TLocateOptions Opts;
			Opts.Clear();
			Opts << loPartialKey;
		   if(aqhd->Locate("OrderNtCode", Variant(code), Opts))
		   {
			RefreshHead(aqhd->FieldByName("ID")->AsInteger );
		   }else
		   {
				 ShowMsg(Handle ,"查询结果为空！",3);
		   }
		}
		/*TfrmQryNoteCode* frm = new TfrmQryNoteCode(this,0);
			LandInfo li;
			li.app = Application;
			li.con = fcon;
			li.userID = UserID ;
			li.storageID = StgID ;
			frm->Init(&li);
		if (frm->ShowModal()==mrOk ) {

		   AnsiString code = frm->GetNoteCode();

		 AnsiString str =  LeftBStr(code,2);
		   if (str == "00") {
			code = AnsiRightStr(code,code.Length()-2) ;

		}else
		   {
			  str = LeftBStr(code,1);
			  if (str == "0") {
						code = AnsiRightStr(code,code.Length()-1) ;
			  }

		   }

			TLocateOptions Opts;
			Opts.Clear();
			Opts << loPartialKey;
		   if(aqhd->Locate("OrderNtCode", Variant(code), Opts))
		   {
			RefreshHead(aqhd->FieldByName("ID")->AsInteger );
		   }else
		   {

			 MessageBoxA(0,"查询结果为空！","提示",MB_ICONWARNING);
		   }
		} */
}
//---------------------------------------------------------------------------



void __fastcall TfrmBIorder::BtnClearClick(TObject *Sender)
{
  if (aqupdatehead->Active) {


		Tfrmwsaleprinta* frm = new Tfrmwsaleprinta(this,fcon);
		::ShowWindow(frm->Handle, SW_HIDE);

		frm->PrintType = 1;//订单
		frm->InputPara(aqupdatehead->FieldByName("ID")->AsAnsiString );
		frm->ClientName = cbclient->Text ;
		frm->pxbk = printbk;
		frm->printtitle = printtitle;
		frm->contact = contact;
		frm->tel = tel;
		frm->address = address;

                try
                {
	     	frm->previewprint(1,3);
                }catch(...)
                {}
		frm->Close();
		delete frm;
		}

}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorder::FormClose(TObject *Sender, TCloseAction &Action)
{
    DelInvalidNtHeader();
	Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorder::BtnExitClick(TObject *Sender)
{
  Close();
  HANDLE hWindow = FindWindow("TfrmMain",NULL);
        SendMessage(hWindow ,WM_MYMESSAGE,0,0);
}
//---------------------------------------------------------------------------

//Excel导出函数
bool   TfrmBIorder::DbgridToExcel(TDBGrid* dbg)
{

	AnsiString temptext,path  ;
	int k = dbg->DataSource ->DataSet ->RecordCount ,n=0;

	savedlg->FileName = StringReplace(cbclient->Text.Trim() +dbeditdanhao->Text ,"\\","-",TReplaceFlags()<<rfReplaceAll) + "订单";
	if (savedlg->Execute())
	{
		String DBPath,Name;
		DBPath = Sysutils::ExtractFilePath(savedlg->FileName .c_str()  );
		Name = Sysutils::ExtractFileName(savedlg->FileName .c_str() );
		DBPath = DBPath + Name + ".xls";
		path =  DBPath;
	}
	else
	{
    	return false;
	}
	if(FileExists(path))
		try {
			DeleteFileA(path);
		} catch (...) {
        	return false;
		}
	Variant  v,vSheet,R,xWorkbook;
	v   =Variant::CreateObject("Excel.Application");
	v.OlePropertySet("Visible",false);
	v.OlePropertyGet("WorkBooks").OleFunction("Add");
	xWorkbook = v.OlePropertyGet("ActiveWorkBook");
	vSheet =  xWorkbook.OlePropertyGet("ActiveSheet");
//  在Excel中成字符串显示

	n=0;

	int t1= 0;
	temptext = "\n";
	for(int q=0;q<dbg->FieldCount-1 ;++q)
	{
		if (dbg->Columns->Items[q]->Visible == true) {
			t1++;
			temptext = dbg->Columns ->Items [q]->Title ->Caption;
			v.OlePropertyGet("Cells",1+n,(t1)).OlePropertySet("Value",temptext .c_str() );
			//temptext = temptext + dbg->Columns ->Items [q]->Title ->Caption + ",";
		}

	}
	int t2 = dbg->DataSource ->DataSet ->RecordCount ;
	dbg->DataSource ->DataSet ->First();
	dbg->DataSource ->DataSet->DisableControls();
	for(int   i=2+n;i<=t2+1+n ;i++)
	{
		t1=0;
		//temptext = "\n";
		for(int j=1;j<dbg->Columns ->Count;j++)
		{
			if (dbg->Columns->Items[j-1]->Visible == true) {
				if (dbg->Columns ->Items [j-1]->FieldName == "ISBN") {
                	t1++;
					temptext = "'"+ dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );
					//temptext = temptext + "'" + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
				}

				else if (dbg->Columns ->Items [j-1]->FieldName == "id"){

				}
				else
				{
                    t1++;
					temptext = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
					//temptext = temptext + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
				}
			}
		}
		//FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
		dbg->DataSource ->DataSet ->Next() ;
	}


	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",n+1,1),vSheet.OlePropertyGet("Cells",t2+n+2,t1)); //取得合并的区域
	R.OlePropertyGet("Borders",2).OlePropertySet("linestyle",1);
	R.OlePropertyGet("Borders",4).OlePropertySet("linestyle",1);

	v.OlePropertyGet("Cells",t2+2,1).OlePropertySet("Value","合计");

	temptext = RzDBNumericEdit2->Text ;
	v.OlePropertyGet("Cells",t2+2,7).OlePropertySet("Value",temptext .c_str() );

	temptext = RzDBNumericEdit3->Text ;
	v.OlePropertyGet("Cells",t2+2,9).OlePropertySet("Value",temptext .c_str() );

	temptext = RzDBNumericEdit4->Text ;
	v.OlePropertyGet("Cells",t2+2,10).OlePropertySet("Value",temptext .c_str() );
	dbg->DataSource ->DataSet->EnableControls();

	try {
                v.OlePropertyGet("ActiveWorkbook").OleFunction("SaveAs", path.c_str());
                //	xWorkbook.OleFunction("SaveAs",path.c_str());
                v.OleFunction("Quit");
              //  vSheet = Unassigned;
                v = Unassigned;
	} catch (...) {
        MessageBox(0, "订单导出失败!","Excel导出", MB_OK | MB_ICONINFORMATION);
           return false;
	}
      MessageBox(0, "订单导出完成!","Excel导出", MB_OK | MB_ICONINFORMATION);

}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorder::edclientKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		/*if (edclient->Text == "") {
            return;
		} */
		AnsiString sql;
		TADOQuery *aq = new TADOQuery(this);
		aq->Connection = fcon;
		sql = "select ID,Name from CUST_CustomerInfo where type in(2,3) and customerstate=1 and "+QFClientTiaoJian+" and name like '%" + edclient->Text.Trim() + "%' order by name";
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		cbclient->Clear();
		while (!aq->Eof )
		{
			cbclient->AddItem(aq->FieldByName("Name")->AsString ,(TObject*)aq->FieldByName("ID")->AsInteger );
			aq->Next();
		}
		aq->First();
		cbclient->ItemIndex = cbclient->Items->IndexOfObject((TObject*)aq->FieldByName("ID")->AsInteger );
		ClientID = aq->FieldByName("ID")->AsInteger;
		cbclient->SetFocus();
		delete aq;
	}
}

//---------------------------------------------------------------------------

void __fastcall TfrmBIorder::cbclientKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		try {
			ClientID = (int)(cbclient->Items->Objects[cbclient->ItemIndex]);
		} catch (...) {
			ShowMsg(Handle ,"请选择正确的客户！",3);
			return;
		}
		BtnOK->Click();
		//dbeditaddcost->SetFocus();
	}
}
//---------------------------------------------------------------------------

void TfrmBIorder::edclientview()
{
        edclient->Text = "";
		AnsiString sql;
		sql = "select ID,Name from CUST_CustomerInfo where type in (2,3) and customerstate=1 and "+QFClientTiaoJian+" order by Name";
		TADOQuery *aq = new TADOQuery(NULL);
		aq->Connection = fcon;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		cbclient->Clear();
		while (!aq->Eof)
		{
            cbclient->AddItem(aq->FieldByName("Name")->AsString ,(TObject*)aq->FieldByName("ID")->AsInteger );
			aq->Next();
		}
		delete aq;
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorder::dgdetail1CellClick(TColumn *Column)
{
	if (aqorderdetail->IsEmpty() ) {
	 return;
   }
   if (aqorderdetail->FieldByName("state1")->AsAnsiString == "有效") {
		editamount->Enabled = true;
		editdiscount->Enabled = true;
   }
   else
   {
    	editamount->Enabled = false;
		editdiscount->Enabled = false;
   }
   //edtCatalog->Text = aqorderdetail->FieldByName("ISBN")->AsAnsiString ;
   editamount->Text = aqorderdetail->FieldByName("amount")->AsAnsiString ;
   editdiscount->Text = aqorderdetail->FieldByName("Discount")->AsAnsiString ;
   editdetailbk->Text = aqorderdetail->FieldByName("bk")->AsAnsiString ;
}
//---------------------------------------------------------------------------



 void __fastcall TfrmBIorder::BtnPrintClick(TObject *Sender)
{
	  if (aqupdatehead->Active) {
		Tfrmwsaleprinta* frm = new Tfrmwsaleprinta(this,fcon);
		::ShowWindow(frm->Handle, SW_HIDE);
	  //	LandInfo li;
	  //	li.app = m_app;
	   //	li.con = m_con;
	   //	li.userID = m_userID;
	   //	li.storageID = m_storageID;
		frm->PrintType = 1;//订单
		frm->InputPara(aqupdatehead->FieldByName("ID")->AsAnsiString );

		frm->RvSystem1->SystemSetups >>ssAllowSetup;
		frm->RvSystem1->SystemSetups >>ssAllowDestPreview;
		frm->RvSystem1->SystemSetups >>ssAllowDestPrinter;
		frm->RvSystem1->SystemSetups >>ssAllowPrinterSetup;
		frm->RvSystem1->SystemSetups >>ssAllowDestFile;

		frm->RvSystem1->DefaultDest  = rdPrinter ;
		frm->RvSystem1->SystemSetups<<ssAllowDestPreview;
		frm->ClientName = cbclient->Text ;
		frm->pxbk = printbk;
		frm->printtitle = printtitle;
		frm->contact = contact;
		frm->tel = tel;
		frm->address = address;

		frm->previewprint(0,3);

		frm->Close();
		delete frm;

		int count = aqupdatehead->FieldByName("printcount")->AsInteger + 1;
		aqupdatehead->Edit();
		aqupdatehead->FieldByName("printcount")->AsInteger = count;
		aqupdatehead->UpdateBatch(arCurrent);
		RefreshHead(aqupdatehead->FieldByName("ID")->AsInteger );
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorder::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorder::N5Click(TObject *Sender)
{
	if (aqorderdetail->IsEmpty() ) {
		return;
	}
	for (int i = 1; i <= aqorderdetail->RecordCount; i++) {
		dgdetail->DataSource->DataSet->RecNo = i;
		dgdetail->SelectedRows->CurrentRowSelected = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorder::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	//ShowMessage(Key);
	if (Key == VK_F1) {   //查单
		if (!BtnView->Enabled ) {
			return;
		}
		BtnView->Click();
	}
	if (Key == VK_F2) {   //添单
		if (!BtnNew->Enabled ) {
			return;
		}
		BtnNew->Click();
	}
	if (Key == VK_F3) {   //保存
		if (!BtnOK->Enabled ) {
			return;
		}
		BtnOK->Click();
	}
	if (Key == VK_F4) {   //修改单头
		if (!BtnProperties->Enabled ) {
			return;
		}
		BtnProperties->Click();
	}
	if (Key == VK_F5) {   //删除
		if (!BtnDelete->Enabled ) {
			return;
		}
		BtnDelete->Click();
	}
	if (Key == VK_F6) {   //统一
		if (!BtnChangeOptions->Enabled ) {
			return;
		}
		BtnChangeOptions->Click();
	}
	if (Key == VK_F8) {   //导出
		if (!BtnExport->Enabled ) {
			return;
		}
		BtnExport->Click();
	}
	if (Key == VK_F10) {  //打印
		if (!BtnPrint->Enabled ) {
			return;
		}
		BtnPrint->Click();
	}
	if (Key == VK_F11) {   //预览
		if (!BtnClear->Enabled ) {
			return;
		}
		BtnClear->Click();
	}
	if (Key == VK_F12) {   //审核本单
		if (!BtnOK1->Enabled ) {
			return;
		}
		BtnOK1->Click();
	}
	if (Key == VK_F9) {   //反审核
		if (!BtnCancel->Enabled ) {
			return;
		}
		BtnCancel->Click();
	}
	if (Shift.Contains(ssAlt)&& Key == 67) {    //定位
		SpeedButton3->Click();
	}
	if (Shift.Contains(ssAlt)&& Key == 78 ) {    //最小化
		BtnAlignBottom->Click();
	}
   //	if (Shift.Contains(ssCtrl)&& Key == 70 ) {   //查书
  //	   BtnView1->Click();
  //	}
	if (Shift.Contains(ssAlt)&& Key == 81 ) {    //退出
		BtnExit->Click();
	}
	if (Shift.Contains(ssAlt)&& Key ==90) {   //恢复窗口
		WindowState = wsNormal;
	}
	if (Shift.Contains(ssCtrl)&&Key==70 ) {    //Ctrl + f 查书
		Tfrmfindorderbook *frm = new Tfrmfindorderbook(Application);
		frm->aq =aqorderdetail;

		if (mrOk == frm->ShowModal()){  ;    //查询条件
			AnsiString type,value;
			type = frm->type ;
			value = frm->value ;

			TLocateOptions   Opts;
			Opts.Clear();
			Opts   <<   loPartialKey;

			if ( !aqorderdetail->Locate(type,value,Opts))
			{

                                ShowMsg(Handle ,"没有找到查询的数据！",3);
			}else
			{
				dgdetail->SelectedRows->Clear();
				dgdetail->SelectedRows->CurrentRowSelected = true;
			}
		}
		delete frm;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorder::cbclientClick(TObject *Sender)
{
	try {
		ClientID = (int)(cbclient->Items->Objects[cbclient->ItemIndex]);
	} catch (...) {
		ShowMsg(Handle ,"请选择正确的客户！",3);
		return;
	}
	//dbeditaddcost->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorder::BtnView1Click(TObject *Sender)
{
	Tfrmbookquery * frm = new Tfrmbookquery(Application,fcon,StgID);
	frm->ShowModal();
	delete frm;
}
//---------------------------------------------------------------------------
void TfrmBIorder::DelInvalidNtHeader()
{
	if (aqupdatehead->Active && aqupdatehead->RecordCount >= 1
		&& aqorderdetail->Active && aqorderdetail->RecordCount < 1 && aqupdatehead->FieldByName("OrderNtCode")->AsAnsiString == "0" )
	{
		DelNtHeader();
	}
}
//---------------------------------------------------------------------------
void TfrmBIorder::DelNtHeader()
{
	if (aqupdatehead->IsEmpty() ) {
        return;
	}
	AnsiString sql;
	sql = "delete from BS_OrderNoteHeader where id = " + aqupdatehead->FieldByName("ID")->AsAnsiString ;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->ExecSQL();
	aqhd->Active = false;
	aqhd->Active = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorder::dbeditaddcostKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		membk->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorder::spnewbookClick(TObject *Sender)
{
	//新书目
	if (aqupdatehead->Active && aqupdatehead->RecordCount >= 1)
	{
	   Tfrmnewbook1 *frm = new Tfrmnewbook1(Application,fcon);
	   frm->BIorder = this;
	   frm->modle = 4;//订单

           //处理期刊新书
           if ( edtCatalog->Text.Trim().Length()>13) {
                frm->cbsaletype->Text = "期刊";
                frm->editqikanmao->Text =edtCatalog->Text.Trim();
                frm->cbsaletypeChange(this);
                PostMessage(frm->editqikanmao->Handle, WM_KEYDOWN,VK_RETURN,0);
           }


	   if (mbOK == frm->ShowModal())
	   {
			edtCatalog->Text  = "";
			editamount->Text = "0";
			editdiscount->Text = "100";
			editdetailbk->Text = "";
                        editamount->Enabled= true;
                        editdiscount->Enabled = true;
		      	editamount->SetFocus();
	   }else
	   {              editamount->Enabled= true;
                        editdiscount->Enabled = true;
		 	editamount->SetFocus();
	   }
	   delete frm;
	   return;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorder::BtnImportClick(TObject *Sender)
{
	/*if (cbclient->Enabled ) {
		MessageBoxA(0,"请先保存单头信息，再进行导入！","提示",MB_ICONERROR);
		return;
	}
	TfrmExcelImport *frm = new TfrmExcelImport(Application,fcon,aqupdatehead->FieldByName("ID")->AsInteger);
	//frm ->ShowModal();
	frm->fuserid = UserID;
	frm->fstgid = StgID;
	if (frm->ShowModal() == mrOk) {
		RefreshHead(aqupdatehead->FieldByName("ID")->AsInteger );
	} */
        	if (cbclient->Enabled ) {
		MessageBoxA(0,"请先保存单头信息，再进行导入！","提示",MB_ICONERROR);
		return;
	}
	TfrmExcelImport *frm = new TfrmExcelImport(Application,fcon,aqupdatehead->FieldByName("ID")->AsInteger);
	//frm ->ShowModal();
	frm->fuserid = UserID;
	frm->fstgid = StgID;
	if (frm->ShowModal() == mrOk  ) {
		RefreshHead(aqupdatehead->FieldByName("ID")->AsInteger );
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorder::edtclientKeyPress(TObject *Sender, wchar_t &Key)
{
	dbeditaddcost->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorder::dgdetail1DblClick(TObject *Sender)
{
	if (aqorderdetail->IsEmpty() ) {
		return;
	}
		TfrmNewBookModify * frm = new TfrmNewBookModify(Application,fcon,aqorderdetail->FieldByName("bkcatalogid")->AsInteger,m_storageID,m_userID);
		frm->ShowModal();
		delete frm;
		RefreshDetail();
}

//---------------------------------------------------------------------------

void __fastcall TfrmBIorder::N6Click(TObject *Sender)
{
	if (aqorderdetail->IsEmpty() ) {
		return;
	}
	else
	{
		AnsiString sql;
		int newcatalogid = -1;
		sql = "select BS_BookCatalog.ID,ISBN,Name,UserDefCode,Price,PressCount,Author,AbbreviatedName from BS_BookCatalog left join BS_PressInfo on BS_BookCatalog.PressID = BS_PressInfo.id where BS_BookCatalog.Name like '%" + aqorderdetail->FieldByName("bookname")->AsString + "%' and AbbreviatedName = '" + aqorderdetail->FieldByName("AbbreviatedName")->AsString + "'";
		aquery->Connection = fcon;
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->Open();
		if (aquery->RecordCount > 1) {
			Tfrmchangeselect *frm = new Tfrmchangeselect(Application,aquery);
			if (frm->ShowModal() == mrOk  ) {
				if (frm->continuechange == 1) {
					TfrmNewBookModify * frm1 = new TfrmNewBookModify(Application,fcon,aqorderdetail->FieldByName("bkcatalogid")->AsInteger,m_storageID,m_userID);
					frm1->newbook = 1;
					if (frm1->ShowModal() == mrOk) {
						newcatalogid = frm1->newcatalogid ;
					}
					delete frm1;
				}
				else
				{
					newcatalogid = aquery->FieldByName("ID")->AsInteger ;
				}
			}
		}
		else
		{
			TfrmNewBookModify * frm2 = new TfrmNewBookModify(Application,fcon,aqorderdetail->FieldByName("bkcatalogid")->AsInteger,m_storageID,m_userID);
			frm2->newbook = 1;
			if (frm2->ShowModal() == mrOk) {
				newcatalogid = frm2->newcatalogid ;
			}
			delete frm2;
		}

		if (newcatalogid > -1) {
        	sql = "update BS_OrderNote set state = 1,bk = '该书被更换' where id = " + aqorderdetail->FieldByName("id")->AsString ;
			TADOQuery *aq = new TADOQuery(this);
			aq->Connection = fcon;
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->ExecSQL() ;

			sql = "insert into BS_OrderNote(OrderNtHeaderID,Amount,Discount,FixedPrice,DiscountedPrice,UnsendAmount,BkcatalogID,bk) select OrderNtHeaderID,Amount,Discount,FixedPrice,DiscountedPrice,UnsendAmount," + IntToStr(newcatalogid) + ",'由《" + aqorderdetail->FieldByName("bookname")->AsString + "》换书而来' from BS_OrderNote where id = " + aqorderdetail->FieldByName("id")->AsString ;
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->ExecSQL() ;
			delete aq;
			//RefreshDetail();
			RefreshHead(aqupdatehead->FieldByName("ID")->AsInteger );
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorder::N7Click(TObject *Sender)
{
	if (aqorderdetail->	IsEmpty() ) {
		return;
	}
	AnsiString sql;
	TLocateOptions   Opts;
	Opts.Clear();
	Opts   <<   loPartialKey;
	AnsiString bkcatalogid;
	bkcatalogid = aqorderdetail->FieldByName("bkcatalogid")->AsString;

	sql = "update BS_OrderNote set state = 0 where id = " + aqorderdetail->FieldByName("id")->AsString ;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL() ;
	delete aq;
	//RefreshDetail();
	RefreshHead(aqupdatehead->FieldByName("ID")->AsInteger );

	aqorderdetail->Locate("bkcatalogid",bkcatalogid,Opts);
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorder::N8Click(TObject *Sender)
{
	if (aqorderdetail->	IsEmpty() ) {
		return;
	}
	AnsiString sql;
	TLocateOptions   Opts;
	Opts.Clear();
	Opts   <<   loPartialKey;
	AnsiString bkcatalogid;
	bkcatalogid = aqorderdetail->FieldByName("bkcatalogid")->AsString;

	sql = "update BS_OrderNote set state = 1,localnum = 0 where id = " + aqorderdetail->FieldByName("id")->AsString ;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL() ;
	delete aq;
	//RefreshDetail();
	RefreshHead(aqupdatehead->FieldByName("ID")->AsInteger );

	aqorderdetail->Locate("bkcatalogid",bkcatalogid,Opts);
	//if ( !query2->Locate("headerid",headid,Opts))
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorder::BtnOK1Click(TObject *Sender)
{
	if (aqorderdetail->IsEmpty() ) {
		return;
	}

	AnsiString sql = "exec USP_BS_Order_shenhei 0," + aqupdatehead->FieldByName("ID")->AsString  ;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	delete aq;
	RefreshDetail();
	BtnOK1->Enabled = false;
	BtnCancel->Enabled = true;
	SpeedButton1->Visible = true;
	GroupBox2->Enabled = false;

	BtnOK->Enabled = false;
	BtnProperties->Enabled = false;
	BtnDelete->Enabled = false;
	BtnChangeOptions->Enabled = false;

}
//---------------------------------------------------------------------------
bool TfrmBIorder::chongfutishi(int catalogid)
{
	if (ordertishi) {
    	AnsiString sql;
		TADOQuery *aq = new TADOQuery(this);
		aq->Connection = fcon;
		sql = "select BS_OrderNote.Amount,BS_OrderNote.SendAmount,BS_OrderNote.UnsendAmount,BS_OrderNote.BkcatalogID,BS_BookCatalog.ISBN,BS_BookCatalog.Name,"
				" BS_OrderNoteHeader.OrderNtCode,convert (char(10),BS_OrderNoteHeader.HdTime,120) as HdTime,dbo.UF_BS_GetClientName(BS_OrderNoteHeader.VendorID) as clientname "
				" from BS_OrderNote left join  BS_OrderNoteHeader on BS_OrderNote.OrderNtHeaderID = BS_OrderNoteHeader.id "
				" left join BS_BookCatalog on BS_OrderNote.BkcatalogID = BS_BookCatalog.id "
				" where BS_OrderNoteHeader.StgID = " + IntToStr(StgID) + " and BS_OrderNote.BkcatalogID = " + IntToStr(catalogid) + " and BS_OrderNoteHeader.VendorID = " + IntToStr(ClientID) + " and BS_OrderNoteHeader.state in (0,1) and BS_OrderNote.state = 0 and BS_OrderNoteHeader.HdTime > dateadd(month,-" + month + ",getdate())";
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		if (aq->RecordCount >= 1) {
			Tfrmchongfuorder * frm = new Tfrmchongfuorder(Application,aq);
			if (frm->ShowModal()== mrOk ) {
				delete aq;
				return true;
			}
			else
			{
            	delete aq;
				return false;
			}
		}
		else
		{
			delete aq;
			return true;
		}
	}
	else
	{
    	return true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorder::dgdetail1DrawColumnCell(TObject *Sender, const TRect &Rect,
		  int DataCol, TColumn *Column, Grids::TGridDrawState State)
{
	if (dgdetail->DataSource->DataSet->FieldByName("state1")->AsString  == "无效" ) {
		//DBGrid1->Canvas->Brush->Color = clBtnFace;
		dgdetail->Canvas->FillRect(Rect);
		dgdetail->Canvas->Font->Color  = clRed;
	   //	DBGrid1->Canvas->Font->Style =  TFontStyles()<<fsBold;  //>>fsBold ;
		dgdetail->DefaultDrawColumnCell(Rect,DataCol,Column,State);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorder::dgdetailCellClick(TColumn *Column)
{
	/*if (aqorderdetail->IsEmpty() ) {
		return;
	}
   if (aqorderdetail->FieldByName("state1")->AsAnsiString == "有效") {
		editamount->Enabled = true;
		editdiscount->Enabled = true;
   }
   else
   {
		editamount->Enabled = false;
		editdiscount->Enabled = false;
   }
   //edtCatalog->Text = aqorderdetail->FieldByName("ISBN")->AsAnsiString ;
   editamount->Text = aqorderdetail->FieldByName("amount")->AsAnsiString ;
   editdiscount->Text = aqorderdetail->FieldByName("Discount")->AsAnsiString ;
   editdetailbk->Text = aqorderdetail->FieldByName("bk")->AsAnsiString ;
   editstockamount->Text = aqorderdetail->FieldByName("bookamount")->AsAnsiString ; */
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorder::dgdetailDblClick(TObject *Sender)
{
	if (aqorderdetail->IsEmpty() ) {
		return;
	}
		TfrmNewBookModify * frm = new TfrmNewBookModify(Application,fcon,aqorderdetail->FieldByName("bkcatalogid")->AsInteger,m_storageID,m_userID);
		frm->ShowModal();
		delete frm;
		RefreshDetail();
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void __fastcall TfrmBIorder::N12Click(TObject *Sender)
{
	if (aqorderdetail->IsEmpty() ) {
		return;
	}
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	AnsiString sql;
	sql = "update BS_OrderNote set newbook = 0 where id = " + aqorderdetail->FieldByName("id")->AsAnsiString ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
    RefreshDetail();
	delete aq;
}

//---------------------------------------------------------------------------

void __fastcall TfrmBIorder::BtnPropertiesClick(TObject *Sender)
{
	if (orderchange) {
		if (!CheckOperateAuthority())
			return;
	}
	GroupBox1->Enabled = true;
	edclient->Enabled = true;
	cbclient->Enabled = true;
	SpeedButton2->Enabled = true;
	dbeditaddcost->Enabled = true;
	dtpdate->Enabled = true;
	dtpfahuo->Enabled = true;
	membk->Enabled = true;
	cbvendor->Enabled = true;
        BtnOK->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorder::dgdetailTitleClick(TColumn *Column)
{
	if (aqorderdetail->IsEmpty() ) {
    	return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (aqorderdetail->Sort == "") {
		aqorderdetail->Sort =  Column->FieldName + " ASC";
	}
	else if (aqorderdetail->Sort == qusort) {
		aqorderdetail->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		aqorderdetail->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorder::membkKeyPress(TObject *Sender, wchar_t &Key)
{
	/*if (Key == '\r') {
		BtnOK->Click();
	} */
	if (Key == '\r') {
		aqupdatehead->Edit();
		aqupdatehead->FieldByName("Remarks")->AsAnsiString = membk->Text ;
		aqupdatehead->UpdateBatch(arAll);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorder::SpeedButton3Click(TObject *Sender)
{
	if (GroupBox3->Visible) {
		GroupBox3->Visible = false;
	}
	else
	{
    	GroupBox3->Visible = true;
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmBIorder::N13Click(TObject *Sender)
{
	lblCatalog->Caption = "作者";
	m_catalogSearchMode=5;
	edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorder::chfsluruClick(TObject *Sender)
{
	if (chfsluru->Checked ) {
		chfoceset->Checked = true;
	}
	else if (chfsamount->Checked ) {
		chfoceset->Checked = true;
	}
	else if (chfsdiscount->Checked ) {
		chfoceset->Checked = true;
	}
	else
	{
		chfoceset->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorder::BtnCancelClick(TObject *Sender)
{
	if (aqorderdetail->IsEmpty() ) {
		return;
	}
	AnsiString sql = "exec USP_BS_Order_shenhei 1," + aqupdatehead->FieldByName("ID")->AsString  ;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	delete aq;

	RefreshDetail();
	BtnOK1->Enabled = true;
	BtnCancel->Enabled = false;
	SpeedButton1->Visible = false;
	GroupBox2->Enabled = true;

	BtnOK->Enabled = true;
	BtnProperties->Enabled = true;
	BtnDelete->Enabled = true;
	BtnChangeOptions->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorder::cbtypeChange(TObject *Sender)
{
	if (cbtype->ItemIndex == 1) {
           BtnImport->Enabled = true;
           BtnFinish->Enabled = true;

	}else
	{
            //BtnImport->Enabled = false;
            BtnFinish->Enabled = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorder::BtnFinishClick(TObject *Sender)
{
	Tfrmretailbookup *frm = new Tfrmretailbookup(Application,m_con,m_storageID);
	frm->Ord = this;
	frm->modle = 1;
	frm->ShowModal();
	delete frm;
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorder::N14Click(TObject *Sender)
{
	if (aqorderdetail->IsEmpty() ) {
        return;
	}
	Tfrmbookhistory *frm = new Tfrmbookhistory(Application,fcon,StgID,aqorderdetail->FieldByName("bkcatalogid")->AsInteger );
	frm->Show();

}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorder::BtnLastRecordClick(TObject *Sender)
{
	if (aqorderdetail->IsEmpty() ) {
    	return;
	}
	AnsiString sql;
	sql = "insert into SYS_InforMessage(state,Message,Type,Datetime,value,stgid,userid) values (1,'" + labtitle->Caption + "已回告内部订单"+ dbeditdanhao->Text +"',1,getdate(),'" + aqupdatehead->FieldByName("OrderNtCode")->AsString + "'," + aqupdatehead->FieldByName("StgID")->AsString + "," + IntToStr(UserID) + ")";
	ExecSQL(sql);
    ShowMsg(Handle ,"回告通知已发出！",3);
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorder::aqorderdetailBeforeScroll(TDataSet *DataSet)
{
	scroll = 1;
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorder::dsdetailDataChange(TObject *Sender, TField *Field)
{
	if (scroll == 1) {
		if (aqorderdetail->IsEmpty() ) {
			editamount->Text = "0";
			editdiscount->Text = "100";
			editdetailbk->Text = "";
			scroll = 0;
			return;
		}

		if (aqorderdetail->FieldByName("state1")->AsAnsiString == "有效") {
			editamount->Enabled = true;
			editdiscount->Enabled = true;
		}
		else
		{
			editamount->Enabled = false;
			editdiscount->Enabled = false;
		}

		editamount->Text = aqorderdetail->FieldByName("amount")->AsAnsiString ;
		editdiscount->Text = aqorderdetail->FieldByName("Discount")->AsAnsiString ;
		editdetailbk->Text = aqorderdetail->FieldByName("bk")->AsAnsiString ;
		scroll = 0;
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmBIorder::BtnExportClick(TObject *Sender)
{
	//Excel导出

	if (aqorderdetail->Active && aqorderdetail->RecordCount >= 1)
	{
		//DbgridToExcel(dgdetail,"一般订单");
		DbgridToExcel(dgdetail);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorder::N16Click(TObject *Sender)
{
//   复制
          AnsiString bkcatalogid;
   	if (aqorderdetail->IsEmpty() ) {
		return;
	}
         bkcatalogid="-1";
        aqorderdetail->DisableControls();
        	if (dgdetail->SelectedRows->Count > 0) {
    	for (int i=0; i < dgdetail->SelectedRows->Count; i++)
		{
			aqorderdetail->Bookmark = dgdetail->SelectedRows->Items[i];
			bkcatalogid = bkcatalogid + "," + aqorderdetail->FieldByName("id")->AsString;
		}
	}
	else
	{
		bkcatalogid = bkcatalogid + "," + aqorderdetail->FieldByName("id")->AsString;
	}
       aqorderdetail->EnableControls();

        TClipboard *pClipboard = new TClipboard();
        pClipboard->Clear();
    pClipboard->AsText = bkcatalogid;
    delete pClipboard;

   //    Richcopy->Text=bkcatalogid;
     //  Richcopy->CopyToClipboard();
     //  Richcopy->Text="";
}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorder::N17Click(TObject *Sender)
{
   //	粘贴
	 AnsiString bkcatalogid;
     Richcopy->Text="";
     Richcopy->PasteFromClipboard();
     bkcatalogid=Richcopy->Text ;
     AnsiString sql,orderheaderid;
     if((dbeditdanhao->Text!="")&&(dbeditdanhao->Enabled==false))
     {
         //是否已审核
       if (aqupdatehead->FieldByName("shenheistate")->AsInteger == 1)
       {

            ShowMsg(Handle ,"已审核的订单不能修改！",3);



       }else
       {
            orderheaderid = aqupdatehead->FieldByName("ID")->AsAnsiString ;

            sql ="exec StickdataToOrderNote "+orderheaderid+",'"+bkcatalogid+"'";
            TADOQuery *aqaa=new TADOQuery(Application);
            aqaa->Connection  = fcon;
             aqaa->Close();
            aqaa->SQL->Clear();
            aqaa->SQL->Add(sql);
            aqaa->ExecSQL();
             RefreshHead(aqupdatehead->FieldByName("ID")->AsInteger );

       }
     }




}
//---------------------------------------------------------------------------

void __fastcall TfrmBIorder::toolshowmainmenuClick(TObject *Sender)
{
    if (toolshowmainmenu->Caption =="显示\r主菜单")
    {

      HANDLE hWindow = FindWindow("TfrmMain",NULL);
      SendMessage(hWindow ,WM_MYMESSAGE,1,0);
      toolshowmainmenu->Caption ="隐藏\r主菜单";
    }else

    {
    HANDLE hWindow = FindWindow("TfrmMain",NULL);
    SendMessage(hWindow ,WM_MYMESSAGE,0,0);
      toolshowmainmenu->Caption ="显示\r主菜单";

    }
}
//---------------------------------------------------------------------------

