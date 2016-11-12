//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitOrdertofahuo.h"
#include "UnitSelectClient.h"
#include "NoteCode.h"
#include "Unitorder_stk.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzEdit"
#pragma link "RzSpnEdt"
#pragma resource "*.dfm"
TfrmOrdertoFahuo *frmOrdertoFahuo;
//---------------------------------------------------------------------------
__fastcall TfrmOrdertoFahuo::TfrmOrdertoFahuo(TComponent* Owner,TADOConnection *cn,int stgid,int userid,int gid)
	: TForm(Owner)
{
	con = cn;
	fstgid = stgid;
	fuserid = userid;
	ClientID = -1;
	query->Connection = cn;
	dtpstart->Date = Date();
	dtpend->Date = Date();
	groupid = gid;
	dtedtDate->Date = Date();
	chordercode->Checked = false;
	TADOQuery * aq = new TADOQuery(NULL);
	aq->Connection = con;
	AnsiString sql;
	sql = "select ID,Name from CUST_CustomerInfo where type in (2,3)";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof )
	{
		cbclient->AddItem(aq->FieldByName("Name")->AsAnsiString ,(TObject*)aq->FieldByName("ID")->AsInteger );
		aq->Next();
	}
	delete aq;
}
//---------------------------------------------------------------------------
void __fastcall TfrmOrdertoFahuo::edclientKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		if (edclient->Text == "") {
            return;
		}
		TADOQuery * aq = new TADOQuery(NULL);
		aq->Connection = con;
		AnsiString sql;
		sql = "select ID,Name from CUST_CustomerInfo where type in (2,3) and name like '%" + edclient->Text + "%'";
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		cbclient->Clear();
		while (!aq->Eof )
		{
			cbclient->AddItem(aq->FieldByName("Name")->AsAnsiString ,(TObject*)aq->FieldByName("ID")->AsInteger );
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
void TfrmOrdertoFahuo::ClientView()
{
	if (ClientID == -1) {
		return;
	}
	String sql;
	TADOQuery * aq = new TADOQuery(NULL);
	aq->Connection = con;


	sql = "select distinct BS_OrderNote.xiaoqu from BS_OrderNote left join BS_OrderNoteHeader "
			" on BS_OrderNote.OrderNtHeaderID = BS_OrderNoteHeader.id where BS_OrderNoteHeader.VendorID = " + IntToStr(ClientID) + " and xiaoqu is not null and xiaoqu <> '' " ;
	if (chordercode->Checked && edordercode->Text != "") {
		sql = sql + " and BS_OrderNoteHeader.OrderNtCode = " + edordercode->Text ;
	}
	else
	{
		sql = sql +  " union "
			" select distinct name from CUST_CustomerInfo where PrentID = " + IntToStr(ClientID) + " and id <> " + IntToStr(ClientID);
	}

	cbxiaoqu->Clear();
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof)
	{
		cbxiaoqu->AddItem(aq->FieldByName("xiaoqu")->AsAnsiString ,(TObject*)1);
		aq->Next();
	}
	sql = "select distinct BS_OrderNote.xueyuan from BS_OrderNote left join BS_OrderNoteHeader "
			" on BS_OrderNote.OrderNtHeaderID = BS_OrderNoteHeader.id where BS_OrderNoteHeader.VendorID = " + IntToStr(ClientID) + " and xueyuan is not null and xueyuan <> '' " ;
	if (chordercode->Checked && edordercode->Text != "") {
		sql = sql + " and BS_OrderNoteHeader.OrderNtCode = " + edordercode->Text ;
	}
	else
	{
		sql = sql +  " union "
			" select distinct name from CUST_CustomerInfo where PrentID = " + IntToStr(ClientID) + " and id <> " + IntToStr(ClientID);
	}
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	cbxueyuan->Clear();
	while (!aq->Eof)
	{
		cbxueyuan->AddItem(aq->FieldByName("xueyuan")->AsAnsiString ,(TObject*)1);
		aq->Next();
	}

	delete aq;
}
//---------------------------------------------------------------------------
void __fastcall TfrmOrdertoFahuo::RzButton1Click(TObject *Sender)
{
	AnsiString sql;

	sql = "select distinct BS_OrderNoteHeader.OrderNtCode,dbo.UF_BS_GetClientName(BS_OrderNoteHeader.VendorID) as ClientName,BS_OrderNoteHeader.id,convert(nvarchar(10),BS_OrderNoteHeader.HdTime,120) as HdTime, "
			" BS_OrderNoteHeader.Remarks,BS_OrderNote.xiaoqu,BS_OrderNote.xueyuan,BS_OrderNote.class,bs_bookcatalog.isbn,bs_bookcatalog.name,BS_OrderNote.incode,BS_OrderNote.id as noteid,BS_OrderNote.amount,Order_lock.stkamount "
			" from BS_OrderNoteHeader left join BS_OrderNote on BS_OrderNote.OrderNtHeaderID = BS_OrderNoteHeader.id "
			" left join bs_bookcatalog on  bs_bookcatalog.id = BS_OrderNote.BkcatalogID "
			" left join Order_lock on Order_lock.bkcatalogid = BS_OrderNote.bkcatalogid and Order_lock.stgid = BS_OrderNoteHeader.stgid ";

	sqlwhere = " where  BS_OrderNote.UnsendAmount > 0 and BS_OrderNote.state = 0 and BS_OrderNoteHeader.state in (0,1) and BS_OrderNoteHeader.shenheistate = 1 and BS_OrderNoteHeader.StgID = " + IntToStr(fstgid) ;
	if (chordercode->Checked && edordercode->Text != "") {
		sqlwhere = sqlwhere + " and BS_OrderNoteHeader.OrderNtCode = " + edordercode->Text ;
	}
	if (chstart->Checked ) {
		sqlwhere = sqlwhere + " and datediff(day,'" + DateToStr(dtpstart->Date) + "',BS_OrderNoteHeader.HdTime) >= 0 ";
	}
	if (chend->Checked ) {
		sqlwhere = sqlwhere + " and datediff(day,'" + DateToStr(dtpend->Date) + "',BS_OrderNoteHeader.HdTime) <= 0 ";
	}
	if (chclient->Checked && cbclient->Text != "") {
		sqlwhere = sqlwhere + " and BS_OrderNoteHeader.VendorID in (select id from dbo.GetChild(" + IntToStr(ClientID) + ")) ";
	}
	if (chxiaoqu->Checked && cbxiaoqu->Text != "") {
		sqlwhere = sqlwhere + " and BS_OrderNote.xiaoqu = '" + cbxiaoqu->Text.Trim() + "'";
	}
	if (chxueyuan->Checked && cbxueyuan->Text != "") {
		sqlwhere = sqlwhere + " and BS_OrderNote.xueyuan = '" + cbxueyuan->Text.Trim() + "'";
	}
	if (chclass->Checked && cbclass->Text != "") {
		sqlwhere = sqlwhere + " and BS_OrderNote.class like '%" + cbclass->Text.Trim() + "%'";
	}
	if (chall->Checked )
	{
		sqlwhere = sqlwhere + " and Order_lock.stkamount > 0 ";
	}



	/*sql = "select distinct BS_OrderNoteHeader.OrderNtCode,dbo.UF_BS_GetClientName(BS_OrderNoteHeader.VendorID) as ClientName,BS_OrderNoteHeader.id,convert(nvarchar(10),BS_OrderNoteHeader.HdTime,120) as HdTime, "
			" BS_OrderNoteHeader.Remarks,BS_OrderNote.xiaoqu,BS_OrderNote.xueyuan,BS_OrderNote.class,bs_bookcatalog.isbn,bs_bookcatalog.name,BS_OrderNote.incode "
			" from BS_OrderNoteHeader left join BS_OrderNote on BS_OrderNote.OrderNtHeaderID = BS_OrderNoteHeader.id "
			" left join bs_bookcatalog on  bs_bookcatalog.id = BS_OrderNote.BkcatalogID ";

	sqlwhere = " where BS_OrderNote.yufa = 0 and BS_OrderNote.UnsendAmount > 0 and BS_OrderNote.state = 0 and BS_OrderNoteHeader.state in (0,1) and BS_OrderNoteHeader.shenheistate = 1 and StgID = " + IntToStr(fstgid) ;
	if (chordercode->Checked && edordercode->Text != "") {
		sqlwhere = sqlwhere + " and BS_OrderNoteHeader.OrderNtCode = " + edordercode->Text ;
	}
	if (chstart->Checked ) {
		sqlwhere = sqlwhere + " and datediff(day,'" + DateToStr(dtpstart->Date) + "',BS_OrderNoteHeader.HdTime) >= 0 ";
	}
	if (chend->Checked ) {
		sqlwhere = sqlwhere + " and datediff(day,'" + DateToStr(dtpend->Date) + "',BS_OrderNoteHeader.HdTime) <= 0 ";
	}
	if (chclient->Checked && cbclient->Text != "") {
		sqlwhere = sqlwhere + " and BS_OrderNoteHeader.VendorID in (select id from dbo.GetChild(" + IntToStr(ClientID) + ")) ";
	}
	if (chxiaoqu->Checked && cbxiaoqu->Text != "") {
		sqlwhere = sqlwhere + " and BS_OrderNote.xiaoqu = '" + cbxiaoqu->Text.Trim() + "'";
	}
	if (chxueyuan->Checked && cbxueyuan->Text != "") {
		sqlwhere = sqlwhere + " and BS_OrderNote.xueyuan = '" + cbxueyuan->Text.Trim() + "'";
	}
	if (chclass->Checked && cbclass->Text != "") {
		sqlwhere = sqlwhere + " and BS_OrderNote.class like '%" + cbclass->Text.Trim() + "%'";
	} */
	sql = sql + sqlwhere;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
}
//---------------------------------------------------------------------------

void __fastcall TfrmOrdertoFahuo::RzButton3Click(TObject *Sender)
{
	if (!query->IsEmpty() ) {
    	//IntoTmporder();
		ModalResult = mrOk ;
	}
}
//---------------------------------------------------------------------------
void TfrmOrdertoFahuo::IntoTmporder()
{
	AnsiString sql;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = con;
	sql = "delete from BS_Tmporder where groupid = " + IntToStr(groupid) + " and modle = 0";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	sql = "insert into BS_Tmpheader(groupid,type,headtime,state,stgid,yufacode,userid) select " + IntToStr(groupid) + ",1,getdate(),0," + IntToStr(fstgid) + ",dbo.UF_BS_BuildNtCode(" + IntToStr(fstgid) + ", getdate(), 7,0)," + IntToStr(fuserid);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	sql = "insert into BS_Tmporder(groupid,orderheaderid,OrderNtCode,bkcatalogid,Clientid,ordernoteid,discount,amount,modle) "
				"select " + IntToStr(groupid) + ",BS_OrderNoteHeader.id,BS_OrderNoteHeader.OrderNtCode,BS_OrderNote.BkcatalogID,BS_OrderNoteHeader.VendorID,BS_OrderNote.id,BS_OrderNote.discount,"
				"case when (BS_OrderNote.localnum + Order_lock.usableamount) > BS_OrderNote.UnsendAmount then BS_OrderNote.UnsendAmount else BS_OrderNote.localnum + Order_lock.usableamount end as amount,0 "
				"from BS_OrderNote left join BS_OrderNoteHeader on BS_OrderNoteHeader.id = BS_OrderNote.OrderNtHeaderID "
				"left join Order_lock on BS_OrderNote.Bkcatalogid = Order_lock.bkcatalogid " ;
	sql = sql + sqlwhere ;
	if (chall->Checked ) {
		sql = sql + " and BS_OrderNote.localnum + Order_lock.usableamount > 0";
	}
	sql = sql + " and Order_lock.stgid = " + IntToStr(fstgid);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	delete aq;
}
//---------------------------------------------------------------------------


void __fastcall TfrmOrdertoFahuo::dtpstartChange(TObject *Sender)
{
	chstart->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmOrdertoFahuo::dtpendChange(TObject *Sender)
{
	chend->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmOrdertoFahuo::cbclassChange(TObject *Sender)
{
	if (cbclass->Text != "") {
		chclass->Checked = true;
	}
	else
	{
    	chclass->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmOrdertoFahuo::cbxueyuanChange(TObject *Sender)
{
	if (cbxueyuan->Text != "") {
		chxueyuan->Checked = true;
	}
	else
	{
    	chxueyuan->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmOrdertoFahuo::cbxiaoquChange(TObject *Sender)
{
	if (cbxiaoqu->Text != "") {
		chxiaoqu->Checked = true;
        if (ClientID > -1) {
			TADOQuery *aq = new TADOQuery(this);
			aq->Connection = con;
			AnsiString sql;
			sql = "select distinct BS_OrderNote.xueyuan from BS_OrderNote left join BS_OrderNoteHeader "
					" on BS_OrderNote.OrderNtHeaderID = BS_OrderNoteHeader.id where BS_OrderNoteHeader.VendorID = " + IntToStr(ClientID) + " and xueyuan is not null and xueyuan <> '' and xiaoqu = '" + cbxiaoqu->Text + "' ";
			if (chordercode->Checked && edordercode->Text != "") {
				sql = sql + " and BS_OrderNoteHeader.OrderNtCode = " + edordercode->Text ;
			}
			else
			{
				sql = sql +  " union "
					" select distinct name from CUST_CustomerInfo where PrentID in (select id from CUST_CustomerInfo where PrentID = " + IntToStr(ClientID) + " and id name = '" + cbxiaoqu->Text + "') ";
			}

			while (!aq->Eof)
			{
				cbxueyuan->AddItem(aq->FieldByName("xueyuan")->AsAnsiString ,(TObject*)1);
				aq->Next();
			}
			delete aq;
		}
	}
	else
	{
		chxiaoqu->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmOrdertoFahuo::dtedtDateChange(TObject *Sender)
{
	NoteCode nc(dtedtDate->Date, fstgid, spedtID->IntValue);
	edordercode->Text = nc.AsString();
}
//---------------------------------------------------------------------------

void __fastcall TfrmOrdertoFahuo::spedtIDChange(TObject *Sender)
{
	if (spedtID->IntValue < 0 || spedtID->IntValue > 99999)
	{
		ShowMessage("单号错误!");
		return;
	}
	NoteCode nc(dtedtDate->Date, fstgid, spedtID->IntValue);
	edordercode->Text = nc.AsString();
}
//---------------------------------------------------------------------------

void __fastcall TfrmOrdertoFahuo::edordercodeChange(TObject *Sender)
{
	if (edordercode->Text != "") {
		chordercode->Checked = true;
	}
	else
	{
    	chordercode->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmOrdertoFahuo::cbclientClick(TObject *Sender)
{
	try {
		ClientID = (int)(cbclient->Items->Objects[cbclient->ItemIndex]);
	} catch (...) {

                 ShowMsg(Handle ,"请选择正确的客户！",3);
		return;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmOrdertoFahuo::cbclientKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
    	ClientView();
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmOrdertoFahuo::cbclientChange(TObject *Sender)
{
	if (cbclient->Text != "") {
		chclient->Checked = true;
	}
	else
	{
		chclient->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmOrdertoFahuo::RzButton2Click(TObject *Sender)
{
	if (query->IsEmpty() ) {
		return;
	}
	if (DBGrid1->SelectedRows->Count == 0) {
		AddTmporder(query->FieldByName("noteid")->AsInteger );
	}
	else
	{
		query->DisableControls();
		for (int i =0; i < DBGrid1->SelectedRows->Count ; i++) {
			query->GotoBookmark(DBGrid1->SelectedRows->Items[i]);
			AddTmporder(query->FieldByName("noteid")->AsInteger );
		}
		query->EnableControls();
	}
}
//---------------------------------------------------------------------------

void TfrmOrdertoFahuo::AddTmporder(int id)
{
	AnsiString sql;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = con;
	sql = "select * from BS_Tmpheader where groupid = " + IntToStr(groupid);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	if (aq->IsEmpty() ) {
    	sql = "insert into BS_Tmpheader(groupid,type,headtime,state,stgid,yufacode,userid) select " + IntToStr(groupid) + ",1,getdate(),0," + IntToStr(fstgid) + ",dbo.UF_BS_BuildNtCode(" + IntToStr(fstgid) + ", getdate(), 7,0)," + IntToStr(fuserid);
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->ExecSQL();
	}
	sql = "select * from BS_Tmporder where groupid = " + IntToStr(groupid) + " and ordernoteid = " + IntToStr(id);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	if (!aq->IsEmpty() ) {

                ShowMsg(Handle ,"已添加该书到预发单！",3);
		delete aq;
		return;
	}
	sql = "SELECT ISBN FROM BS_OrderNote LEFT JOIN BS_BookCatalog ON BS_OrderNote.BkcatalogID = BS_BookCatalog.ID WHERE BS_OrderNote.ID = " + IntToStr(id);
    aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	AnsiString isbn;
	isbn = aq->FieldByName("ISBN")->AsString ;
	if (isbn.Length()==10 || isbn.Length()==13 ) {
		isbn = isbn.Delete(isbn.Length(),1);
	}
	sql = "select DISTINCT BS_BookCatalog.ID,BS_BookCatalog.ISBN,BS_BookCatalog.Name,BS_BookCatalog.price,BS_BookCatalog.author,BS_BookCatalog.PressCount,BS_PressInfo.AbbreviatedName,stk_bookinfo.amount from stk_bookinfo "
			" left join BS_BookCatalog on stk_bookinfo.BkcatalogID = BS_BookCatalog.id "
			" left join BS_PressInfo on BS_BookCatalog.pressid = BS_PressInfo.id "
			" where BS_BookCatalog.ISBN LIKE '%" + isbn + "%' or BS_BookCatalog.Barcode like '%" + isbn + "%'";
    aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	if (aq->RecordCount == 1) {
		sql = "update BS_OrderNote set BkcatalogID = " + aq->FieldByName("ID")->AsAnsiString + " where id = " + IntToStr(id);
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->ExecSQL();
	}
	else if (aq->RecordCount > 1) {
		Tfrmorder_stk *frms = new Tfrmorder_stk(Application,aq);
		frms->isbn = query->FieldByName("isbn")->AsAnsiString ;
		frms->name = query->FieldByName("name")->AsAnsiString ;
		frms->amount = query->FieldByName("amount")->AsAnsiString ;
		if (frms->ShowModal() == mrOk  ) {

        	sql = "update BS_OrderNote set BkcatalogID = " + aq->FieldByName("ID")->AsAnsiString + " where id = " + IntToStr(id);
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->ExecSQL();
		}
		delete frms;
	}
	else
	{

                 ShowMsg(Handle ,"没有匹配到与该书书号相符的库存记录！",3);
		delete aq;
		return;
	}

	sql = "insert into BS_Tmporder(groupid,orderheaderid,OrderNtCode,bkcatalogid,Clientid,ordernoteid,discount,amount,modle) "
				"select " + IntToStr(groupid) + ",BS_OrderNoteHeader.id,BS_OrderNoteHeader.OrderNtCode,BS_OrderNote.BkcatalogID,BS_OrderNoteHeader.VendorID,BS_OrderNote.id,BS_OrderNote.discount,"
				"case when (BS_OrderNote.localnum + Order_lock.usableamount) > BS_OrderNote.UnsendAmount then BS_OrderNote.UnsendAmount else BS_OrderNote.localnum + Order_lock.usableamount end as amount,0 "
				"from BS_OrderNote left join BS_OrderNoteHeader on BS_OrderNoteHeader.id = BS_OrderNote.OrderNtHeaderID "
				"left join Order_lock on BS_OrderNote.Bkcatalogid = Order_lock.bkcatalogid " ;

	sql = sql + " where BS_OrderNote.id = " + IntToStr(id) + " and Order_lock.stgid = " + IntToStr(fstgid);

	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	delete aq;
}
//---------------------------------------------------------------------------

