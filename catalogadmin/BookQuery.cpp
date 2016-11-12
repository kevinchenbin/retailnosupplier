//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "BookQuery.h"
#include "Selecttype.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzCmboBx"
#pragma link "RzEdit"
#pragma link "ModalDialog"
#pragma link "RzButton"
#pragma resource "*.dfm"
TfrmBookQuery *frmBookQuery;
//---------------------------------------------------------------------------
__fastcall TfrmBookQuery::TfrmBookQuery(TComponent* Owner,TADOConnection *con)
	: TForm(Owner)
{
	fcon = con;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = con;
	AnsiString sql;
	sql = "select ID,AbbreviatedName FROM BS_PressInfo";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof )
	{
		cbpress->AddItem(aq->FieldByName("AbbreviatedName")->AsAnsiString ,(TObject*)aq->FieldByName("ID")->AsInteger );
		aq->Next();
	}
	delete aq;
}
//---------------------------------------------------------------------------

void __fastcall TfrmBookQuery::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmBookQuery::btOKClick(TObject *Sender)
{
	ModalResult = mrOk ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmBookQuery::RzButton1Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------


void __fastcall TfrmBookQuery::edpressKeyPress(TObject *Sender, wchar_t &Key)
{
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	AnsiString sql;
	sql = "select ID,AbbreviatedName FROM BS_PressInfo where AbbreviatedName like '%" + edpress->Text.Trim() + "%'";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	cbpress->Items->Clear();
	while (!aq->Eof )
	{
		cbpress->AddItem(aq->FieldByName("AbbreviatedName")->AsAnsiString ,(TObject*)aq->FieldByName("ID")->AsInteger );
		aq->Next();
	}
	aq->First();
	cbpress->ItemIndex = cbpress->Items->IndexOfObject((TObject*)aq->FieldByName("ID")->AsInteger );
	delete aq;
	cbpress->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TfrmBookQuery::cbtypeKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        btOK->SetFocus();
	}
}
//---------------------------------------------------------------------------

AnsiString TfrmBookQuery::getcontion()
{
	AnsiString contion;
	contion = " where 1 = 1";
	if (chisbn->Checked && edisbn->Text != "") {
		contion = contion + " and (A.isbn like '%" + edisbn->Text.Trim() + "%' or A.Barcode like '%" + edisbn->Text.Trim() + "%')";
	}
	if (chname->Checked && edname->Text != "") {
		contion = contion + " and A.name like '%" + edname->Text.Trim() + "%'";
	}
	if (chprice->Checked && edprice->Text != "") {
		try {
			StrToFloat(edprice->Text);
		} catch (...) {
			return contion;
		}
		contion = contion + " and A.price = " + edprice->Text;
	}
	if (chauthor->Checked && edauthor->Text != "") {
		contion = contion + " and A.author like '%" + edauthor->Text.Trim() + "%'";
	}
	if (chpress->Checked && cbpress->Text != "") {
		contion = contion + " and B.AbbreviatedName = '" + cbpress->Text + "'";
	}
	if (chtype->Checked && edtyname->Text != "") {
		contion = contion + " and C.id in(select id from dbo.GetTypeChild(" + IntToStr(TypeID) + ")) ";
	}
        if (cbselftcode->Checked && editselfcode->Text!="") {
              contion = contion + " and A.UserDefCode like '%" + editselfcode->Text.Trim() + "%'";
        }
	return  contion;
}
//---------------------------------------------------------------------------

void __fastcall TfrmBookQuery::edisbnChange(TObject *Sender)
{
	if (edisbn->Text != "") {
		chisbn->Checked = true;
	}
	else
	{
    	chisbn->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmBookQuery::ednameChange(TObject *Sender)
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

void __fastcall TfrmBookQuery::edpriceChange(TObject *Sender)
{
	if (edprice->Text != "") {
		chprice->Checked = true;
	}
	else
	{
    	chprice->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmBookQuery::edauthorChange(TObject *Sender)
{
	if (edauthor->Text != "") {
		chauthor->Checked = true;
	}
	else
	{
    	chauthor->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmBookQuery::cbpressChange(TObject *Sender)
{
	if (cbpress->Text != "") {
		chpress->Checked = true;
	}
	else
	{
    	chpress->Checked = false;
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmBookQuery::SpeedButton1Click(TObject *Sender)
{
	Tfrmselecttype * frm = new Tfrmselecttype(Application,fcon,"");
	if (mrOk == frm->ShowModal())
	{
		TypeID = frm->GetSelectID();
		edtyname->Text = frm->GetSelect();
		chtype->Checked = true;
	}
	delete frm;
}
//---------------------------------------------------------------------------

void __fastcall TfrmBookQuery::edpyqueryKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		Tfrmselecttype * frm = new Tfrmselecttype(Application,fcon,edpyquery->Text);
		if (mrOk == frm->ShowModal())
		{
			TypeID = frm->GetSelectID();
			edtyname->Text = frm->GetSelect();
			chtype->Checked = true;
		}
		delete frm;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmBookQuery::editselfcodeChange(TObject *Sender)
{
	if (editselfcode->Text != "") {
		cbselftcode->Checked = true;
	}
	else
	{
    	cbselftcode->Checked = false;
	}
}
//---------------------------------------------------------------------------

