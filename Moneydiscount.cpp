//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Moneydiscount.h"
#include "global.h"
#include "Selecttype.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma link "RzButton"
#pragma resource "*.dfm"
TfrmMonerydiscount *frmMonerydiscount;
//---------------------------------------------------------------------------
__fastcall TfrmMonerydiscount::TfrmMonerydiscount(TComponent* Owner,TADOConnection *con,int stgid)
	: TForm(Owner)
{
    fstgid = stgid;
	aq->Connection = con;
	query1->Connection = con;
	query2->Connection = con;
	fcon = con;
	AnsiString sql ;
	sql = "select ID,Name from CUST_CustomerInfo where Type = 1 and  customerstate=1 and stgid="+IntToStr(fstgid);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof)
	{
		cbsupplier->AddItem(aq->FieldByName("Name")->AsAnsiString.Trim(),(TObject*)aq->FieldByName("ID")->AsInteger );
		aq->Next();
	}

	sql = "select ID,Name from SYS_StorageInfo";
    aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof)
	{
    	cbstorage->AddItem(aq->FieldByName("Name")->AsString,(TObject*)aq->FieldByName("ID")->AsInteger);
		aq->Next();
	}
	cbstorage->ItemIndex = cbstorage->Items->IndexOfObject((TObject*)fstgid);
	sql = "select Master from SYS_StorageInfo where id = " + IntToStr(fstgid);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	if (aq->FieldByName("Master")->AsBoolean) {
		cbstorage->Enabled = true;
	}
	else
	{
    	cbstorage->Enabled = false;
	}

	dtpstart->Date = Date();
	dtpend->Date = Date();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMonerydiscount::SpeedButton1Click(TObject *Sender)
{
	String sql;
	if (dtpstart->Date > dtpend->Date ) {
		ShowMsg(this->Handle,"有效结束时间应该大于有效起始时间！",3);
		return;
	}
	if (query1->RecordCount > 0) {
		sql = "select * from Money_Discount where Money = " + edmoney->Text + " and BCatalogid = " + query1->FieldByName("bcid")->AsString + " and Supplierid = " + query1->FieldByName("custid")->AsString + " and StgID = " + IntToStr(fstgid) ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		if (aq->RecordCount > 0) {
			sql = "update Money_Discount set Amount = Amount + 1,startdate = '" + DateToStr(dtpstart->Date) +"',enddate = '" + DateToStr(dtpend->Date) + "' where ID = " + aq->FieldByName("ID")->AsString ;
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->ExecSQL();
		}
		else
		{
			sql = "insert into Money_Discount(Money,BCatalogid,Supplierid,startdate,enddate,StgID) values (" + edmoney->Text + "," + query1->FieldByName("bcid")->AsString + "," + query1->FieldByName("custid")->AsString + ",'" + DateToStr(dtpstart->Date) + "','" + DateToStr(dtpend->Date) + "'," + IntToStr(fstgid) +")";
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->ExecSQL();
		}
		query2->Active = false;
		query2->Active = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMonerydiscount::Query()
{
	String sql;
	try {
		fstgid =  (int)cbstorage->Items->Objects[cbstorage->ItemIndex];
	} catch (...) {

                ShowMsg(Handle ,"请选择正确的店名！",3);
		return;
	}

	sql = "select Money_Discount.id,Money_Discount.Money,Money_Discount.Amount,convert(char(10),Money_Discount.startdate,20) as startdate,convert(char(10),Money_Discount.enddate,20) as enddate,BS_BookCatalog.Name as bookname,BS_BookCatalog.price,CUST_CustomerInfo.name as suppliername from "
		  "Money_Discount left join BS_BookCatalog on Money_Discount.BCatalogid = BS_BookCatalog.id "
		  "left join CUST_CustomerInfo on Money_Discount.Supplierid = CUST_CustomerInfo.id "
		  "where Money_Discount.Money = " + edmoney->Text + " and Money_Discount.StgID = " + IntToStr(fstgid) ;
	query2->Close();
	query2->SQL->Clear();
	query2->SQL->Add(sql);
	query2->Open();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMonerydiscount::edmoneyExit(TObject *Sender)
{
	if (edmoney->Text != "") {
        Query();
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmMonerydiscount::SpeedButton2Click(TObject *Sender)
{
	AnsiString sql;
	if (query2->IsEmpty() ) {
        return;
	}
	if (DBGrid2->SelectedRows->Count == 0) {
		if (query2->FieldByName("Amount")->AsInteger > 1 ) {
			sql = "update Money_Discount set Amount = Amount - 1 where id = " + query2->FieldByName("id")->AsString ;
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->ExecSQL();
		}
		else
		{
			sql = "delete from Money_Discount where id = " + query2->FieldByName("id")->AsString ;
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->ExecSQL();
		}
	}
	else if (DBGrid2->SelectedRows->Count > 0) {
		query2->Bookmark = DBGrid2->SelectedRows->Items[0];
		if (query2->FieldByName("Amount")->AsInteger > 1 ) {
			sql = "update Money_Discount set Amount = Amount - 1 where id = " + query2->FieldByName("id")->AsString ;
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->ExecSQL();
		}
		else
		{
			sql = "delete from Money_Discount where id = " + query2->FieldByName("id")->AsString ;
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->ExecSQL();
		}
		for (int i=1; i < DBGrid2->SelectedRows->Count; i++)
		{
			query2->Bookmark = DBGrid2->SelectedRows->Items[i];
			if (query2->FieldByName("Amount")->AsInteger > 1 ) {
				sql = "update Money_Discount set Amount = Amount - 1 where id = " + query2->FieldByName("id")->AsString ;
				aq->Close();
				aq->SQL->Clear();
				aq->SQL->Add(sql);
				aq->ExecSQL();
			}
			else
			{
				sql = "delete from Money_Discount where id = " + query2->FieldByName("id")->AsString ;
				aq->Close();
				aq->SQL->Clear();
				aq->SQL->Add(sql);
				aq->ExecSQL();
			}
		}
	}
   	query2->Active = false;
	query2->Active = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMonerydiscount::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMonerydiscount::FormClose(TObject *Sender, TCloseAction &Action)

{
	Action = caFree ;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMonerydiscount::edmoneyKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
        dtpstart->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMonerydiscount::dtpstartKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
        dtpend->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMonerydiscount::dtpendKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
        cbcondition->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMonerydiscount::cbconditionKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift)
{
	if (Key == VK_RETURN) {
    	edcondition->SetFocus();
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmMonerydiscount::cbsupplierKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift)
{
	if (Key == VK_RETURN) {
		edpyquery->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMonerydiscount::cbtypeKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
        btquery->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMonerydiscount::btquerydiscountClick(TObject *Sender)
{
	String sql;
	try {
		fstgid =  (int)cbstorage->Items->Objects[cbstorage->ItemIndex];
	} catch (...) {
                ShowMsg(Handle ,"请选择正确的店名！",3);
		return;
	}
	sql = "select Money_Discount.id,Money_Discount.Money,Money_Discount.Amount,convert(char(10),Money_Discount.startdate,20) as startdate,convert(char(10),Money_Discount.enddate,20) as enddate,BS_BookCatalog.Name as bookname,BS_BookCatalog.price,CUST_CustomerInfo.name as suppliername from "
		  "Money_Discount left join BS_BookCatalog on Money_Discount.BCatalogid = BS_BookCatalog.id "
		  "left join CUST_CustomerInfo on Money_Discount.Supplierid = CUST_CustomerInfo.id where Money_Discount.StgID = " + IntToStr(fstgid) + " order by Money_Discount.Money" ;
	query2->Close();
	query2->SQL->Clear();
	query2->SQL->Add(sql);
	query2->Open();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMonerydiscount::edconditionKeyPress(TObject *Sender, wchar_t &Key)

{
	if (cbcondition->Text == "定价") {
        if ((Key < '0' || Key > '9') && (Key != '\b') && (Key != '.') && (Key != '\r') ) {
			Key = NULL;
		}
	}
	if (Key == VK_RETURN) {
		cbsupplier->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMonerydiscount::btqueryClick(TObject *Sender)
{
	String sql ;
	try {
		fstgid =  (int)cbstorage->Items->Objects[cbstorage->ItemIndex];
	} catch (...) {
		ShowMsg(Handle ,"请选择正确的店名！",3);
		return;
	}
	sql = "select BS_BookCatalog.id as bcid,BS_BookCatalog.Name,BS_BookCatalog.ISBN,BS_BookCatalog.Price,CUST_CustomerInfo.id as custid,CUST_CustomerInfo.Name as custname,BS_BookType.Name as typename from "
		  "BS_BookCatalog left join STK_BookInfo on STK_BookInfo.BkcatalogID = BS_BookCatalog.id "
		  "left join CUST_CustomerInfo on CUST_CustomerInfo.id = STK_BookInfo.SupplierID "
		  "left join BS_BookType on BS_BookType.id = BS_BookCatalog.smallBookTypeID "
		  "left join STK_BookstackInfo on STK_BookInfo.BkstackID = STK_BookstackInfo.id "
		  "where CUST_CustomerInfo.Type = 1 and STK_BookstackInfo.StgID = " + IntToStr(fstgid) ;
	if (edcondition->Text != "") {
		switch (cbcondition->ItemIndex) {
			case 0:
				sql = sql + " and BS_BookCatalog.Name like '%" +  edcondition->Text + "%'";
				break;
			case 1:
				sql = sql + " and (BS_BookCatalog.ISBN like '%" +  edcondition->Text + "%' or barcode like '%" + edcondition->Text + "%')" ;
				break;
			case 2:
				sql = sql + " and BS_BookCatalog.Price = " +  edcondition->Text;
				break;
		default:
			;
		}
	}
	if (cbsupplier->Text != "") {
		try {
			sql = sql + " and CUST_CustomerInfo.id = " + IntToStr((int)cbsupplier->Items->Objects[cbsupplier->ItemIndex]);
		} catch (...) {
			ShowMsg(this->Handle,"请选择正确的供应商！",3);
			return;
		}
	}
	if (edtyname->Text != "") {
		sql = sql + " and BS_BookCatalog.smallBookTypeID in (select id from dbo.GetTypeChild(" + IntToStr(TypeID) + ")) ";
	}
	query1->Close();
	query1->SQL->Clear();
	query1->SQL->Add(sql);
	query1->Open();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMonerydiscount::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMonerydiscount::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Shift.Contains(ssCtrl)&& Key == 78 ) {    //最小化
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 81 ) {    //退出
		BtnExit->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==90) {   //恢复窗口
		WindowState = wsNormal  ;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMonerydiscount::cbstorageSelect(TObject *Sender)
{
	String sql;
	try {
		fstgid =  (int)cbstorage->Items->Objects[cbstorage->ItemIndex];
	} catch (...) {
                ShowMsg(Handle ,"请选择正确的店名！",3);
		return;
	}
	sql = "select Money_Discount.id,Money_Discount.Money,Money_Discount.Amount,convert(char(10),Money_Discount.startdate,20) as startdate,convert(char(10),Money_Discount.enddate,20) as enddate,BS_BookCatalog.Name as bookname,CUST_CustomerInfo.name as suppliername from "
		  "Money_Discount left join BS_BookCatalog on Money_Discount.BCatalogid = BS_BookCatalog.id "
		  "left join CUST_CustomerInfo on Money_Discount.Supplierid = CUST_CustomerInfo.id where Money_Discount.StgID = " + IntToStr(fstgid) + " order by Money_Discount.Money" ;
	query2->Close();
	query2->SQL->Clear();
	query2->SQL->Add(sql);
	query2->Open();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMonerydiscount::edsupplierKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        AnsiString sql ;
		sql = "select ID,Name from CUST_CustomerInfo where Type = 1 and name like '%" + edsupplier->Text.Trim() + "%'";
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		cbsupplier->Clear();
		while (!aq->Eof)
		{
			cbsupplier->AddItem(aq->FieldByName("Name")->AsAnsiString.Trim(),(TObject*)aq->FieldByName("ID")->AsInteger );
			aq->Next();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMonerydiscount::SpeedButton3Click(TObject *Sender)
{
	Tfrmselecttype * frm = new Tfrmselecttype(Application,fcon,"");
	if (mrOk == frm->ShowModal())
	{
		TypeID = frm->GetSelectID();
		edtyname->Text = frm->GetSelect();
	}
	delete frm;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMonerydiscount::edpyqueryKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		Tfrmselecttype * frm = new Tfrmselecttype(Application,fcon,edpyquery->Text);
		if (mrOk == frm->ShowModal())
		{
			TypeID = frm->GetSelectID();
			edtyname->Text = frm->GetSelect();
		}
		delete frm;
	}
}
//---------------------------------------------------------------------------

