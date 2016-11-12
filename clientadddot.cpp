//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "clientadddot.h"
#include "global.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzCmboBx"
#pragma resource "*.dfm"
Tfrmclientadddot *frmclientadddot;
//---------------------------------------------------------------------------
__fastcall Tfrmclientadddot::Tfrmclientadddot(TComponent* Owner,TADOConnection *con,int stgid)
	: TForm(Owner)
{
	fcon = con;
        fstgid = stgid;
	query->Connection = con;
	aq1->Connection = con;
	AnsiString sql;
	sql = "select rank() over(order by clientid) as xuhao,clientid "
			",dbo.UF_BS_GetClientName(clientid) as clientname,adddot, "
			" CUST_Customertype.name as typename "
			" from BS_ClientAddDot left join CUST_CustomerInfo on BS_ClientAddDot.clientid = CUST_CustomerInfo.id "
			" left join CUST_Customertype on CUST_CustomerInfo.customertype = CUST_Customertype.id";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();

	sql = "select CUST_CustomerInfo.name as clientname,CUST_CustomerInfo.id,CUST_Customertype.name as typename "
		" from  CUST_CustomerInfo left join CUST_Customertype on CUST_CustomerInfo.customertype = CUST_Customertype.id";
	sql = sql + " where CUST_CustomerInfo.type in(2,3)  and customerstate=1 and CUST_CustomerInfo.stgid="+IntToStr(fstgid);
	aq1->Close();
	aq1->SQL->Clear();
	aq1->SQL->Add(sql);
	aq1->Open();

	TADOQuery * aq = new TADOQuery(NULL);
	aq->Connection = fcon;
	sql = "select * from CUST_Customertype where type = 2 " ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof )
	{
		cmtype->AddItem(aq->FieldByName("Name")->AsAnsiString,(TObject*)aq->FieldByName("ID")->AsInteger);
		aq->Next();
	}
	delete aq;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmclientadddot::Button1Click(TObject *Sender)
{
	if (aq1->IsEmpty() || eddot->Text == "")  {
		return;
	}
	try {
		StrToFloat(eddot->Text) ;
	} catch (...) {
		ShowMsg(this->Handle,"请输入正确的折扣加点数!",3);
		return;
	}
	AnsiString sql;
	TADOQuery * aq = new TADOQuery(NULL);
	aq->Connection = fcon;
	if (DBGrid1->SelectedRows->Count == 0) {
    	sql = "select * from BS_ClientAddDot where Clientid = " + aq1->FieldByName("ID")->AsAnsiString ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		if (aq->RecordCount > 0) {
			sql = "update BS_ClientAddDot set Adddot = " + eddot->Text + " where Clientid = " + aq1->FieldByName("ID")->AsAnsiString ;
		}
		else
		{
			sql = "insert into BS_ClientAddDot(Clientid,Adddot) values(" + aq1->FieldByName("ID")->AsAnsiString + "," + eddot->Text + ")";
		}
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->ExecSQL();
	}
	else if (DBGrid1->SelectedRows->Count > 0) {
		aq1->Bookmark = DBGrid1->SelectedRows->Items[0];
        sql = "select * from BS_ClientAddDot where Clientid = " + aq1->FieldByName("ID")->AsAnsiString ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		if (aq->RecordCount > 0) {
			sql = "update BS_ClientAddDot set Adddot = " + eddot->Text + " where Clientid = " + aq1->FieldByName("ID")->AsAnsiString ;
		}
		else
		{
			sql = "insert into BS_ClientAddDot(Clientid,Adddot) values(" + aq1->FieldByName("ID")->AsAnsiString + "," + eddot->Text + ")";
		}
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->ExecSQL();
		for (int i=1; i < DBGrid1->SelectedRows->Count; i++)
		{
			aq1->Bookmark = DBGrid1->SelectedRows->Items[i];
			sql = "select * from BS_ClientAddDot where Clientid = " + aq1->FieldByName("ID")->AsAnsiString ;
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();
			if (aq->RecordCount > 0) {
				sql = "update BS_ClientAddDot set Adddot = " + eddot->Text + " where Clientid = " + aq1->FieldByName("ID")->AsAnsiString ;
			}
			else
			{
				sql = "insert into BS_ClientAddDot(Clientid,Adddot) values(" + aq1->FieldByName("ID")->AsAnsiString + "," + eddot->Text + ")";
			}
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->ExecSQL();
		}
	}

	query->Close();
	query->Open();
	delete aq;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmclientadddot::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmclientadddot::N1Click(TObject *Sender)
{
	if (query->IsEmpty() ) {
		return;
	}
	AnsiString sql;
	TADOQuery * aq = new TADOQuery(NULL);
	aq->Connection = fcon;

	if (DBGrid2->SelectedRows->Count == 0) {
		sql = "delete from BS_ClientAddDot where Clientid = " + query->FieldByName("clientid")->AsAnsiString ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->ExecSQL();
	}
	else if (DBGrid2->SelectedRows->Count > 0) {
		query->Bookmark = DBGrid2->SelectedRows->Items[0];
		sql = "delete from BS_ClientAddDot where Clientid = " + query->FieldByName("clientid")->AsAnsiString ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->ExecSQL();
		for (int i=1; i < DBGrid2->SelectedRows->Count; i++)
		{
			query->Bookmark = DBGrid2->SelectedRows->Items[i];
			sql = "delete from BS_ClientAddDot where Clientid = " + query->FieldByName("clientid")->AsAnsiString ;
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->ExecSQL();
		}
	}
	query->Active = false;
	query->Active = true;

	delete aq;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmclientadddot::Button2Click(TObject *Sender)
{
	AnsiString sql;
	sql = "select CUST_CustomerInfo.name as clientname,CUST_CustomerInfo.id,CUST_Customertype.name as typename "
		" from  CUST_CustomerInfo left join CUST_Customertype on CUST_CustomerInfo.customertype = CUST_Customertype.id";
	sql = sql + " where CUST_CustomerInfo.type in(2,3) and customerstate=1 and CUST_CustomerInfo.stgid="+IntToStr(fstgid);
	if (chname->Checked && edname->Text != "") {
		sql = sql + " and CUST_CustomerInfo.name like '%" + edname->Text + "%'";
	}
	if (chtype->Checked && cmtype->Text != "") {
		int type;
		try {
			type = (int)(cmtype->Items->Objects[cmtype->ItemIndex]);
		} catch (...) {
			ShowMsg(this->Handle,"请选择正确的类别！",3);
			return;
		}
		sql = sql + " and CUST_CustomerInfo.customertype = " + IntToStr(type) ;
	}
	aq1->Close();
	aq1->SQL->Clear();
	aq1->SQL->Add(sql);
	aq1->Open();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmclientadddot::ednameChange(TObject *Sender)
{
	if (edname->Text != "") {
		chname->Checked = true;
	}
	else
	{
    	chname->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmclientadddot::cmtypeChange(TObject *Sender)
{
	if (cmtype->Text != "") {
		chtype->Checked = true;
	}
	else
	{
    	chtype->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmclientadddot::MenuItem1Click(TObject *Sender)
{
	if (aq1->IsEmpty() ) {
		return;
	}
	for (int i = 1; i <= aq1->RecordCount ; i++) {
		DBGrid1->DataSource->DataSet->RecNo = i;
		DBGrid1->SelectedRows->CurrentRowSelected = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmclientadddot::N2Click(TObject *Sender)
{
	if (query->IsEmpty() ) {
		return;
	}
	for (int i = 1; i <= query->RecordCount ; i++) {
		DBGrid2->DataSource->DataSet->RecNo = i;
		DBGrid2->SelectedRows->CurrentRowSelected = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmclientadddot::DBGrid2CellClick(TColumn *Column)
{
	if (query->IsEmpty() ) {
		return;
	}
	eddot->Text = query->FieldByName("adddot")->AsAnsiString ;
}
//---------------------------------------------------------------------------

