//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Masterset.h"
#include "global.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma link "RzButton"
#pragma resource "*.dfm"
TfrmMasterset *frmMasterset;
//---------------------------------------------------------------------------
__fastcall TfrmMasterset::TfrmMasterset(TComponent* Owner,TADOConnection *con)
	: TForm(Owner)
{
	aq->Connection = con;
	query->Connection = con;
	AnsiString sql ;
	sql = "select ID,Name,Master from SYS_StorageInfo where Master <> 1 ";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof )
	{
		cbname->AddItem(aq->FieldByName("Name")->AsAnsiString ,(TObject*)aq->FieldByName("ID")->AsInteger );
		aq->Next();
	}
	sql = "select ID,Name from SYS_StorageInfo where Master = 1 ";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	edname->Text = aq->FieldByName("Name")->AsAnsiString.Trim();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMasterset::btokClick(TObject *Sender)
{
	AnsiString sql;
	int stgid;
	try {
		stgid = (int)(cbname->Items->Objects[cbname->ItemIndex]);
	} catch (...) {
		ShowMsg(this->Handle,"请选择正确的店!",3);
		return;
	}
	sql = "update SYS_StorageInfo set master = 0 where id <> " + IntToStr(stgid);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	sql = "update SYS_StorageInfo set master = 1 where id = " + IntToStr(stgid);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	ShowMsg(this->Handle,"设置成功!",3);
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMasterset::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMasterset::btconcelClick(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------




