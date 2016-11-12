//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Syspwdchange.h"
#include "Addsyslog.h"
#include "global.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrmsyspwdchange *frmsyspwdchange;
//---------------------------------------------------------------------------
__fastcall Tfrmsyspwdchange::Tfrmsyspwdchange(TComponent* Owner,TADOConnection *con)
	: TForm(Owner)
{
	aq->Connection = con;
	fcon = con;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsyspwdchange::btOKClick(TObject *Sender)
{
	AnsiString sql,pwd;
	sql = "select bk from sys_bsset where name ='changeDanHaoDisplay'";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	pwd = aq->FieldByName("bk")->AsString ;
	if (pwd != edoldpwd->Text ) {
		AddEvent(3,"������ʾ���������޸Ĵ���",userid,storageid,"�����������",fcon);
		ShowMsg(this->Handle,"�����������",3);
		return;
	}
	if (ednewpwd->Text != edpwdagain->Text ) {
		AddEvent(2,"������ʾ���������޸Ĵ���",userid,storageid,"�����������벻һ��",fcon);
		ShowMsg(this->Handle,"�����������벻һ�£�",3);
		return;
	}
	sql = "update sys_bsset set bk = '" + ednewpwd->Text.Trim() + "' where name = 'changeDanHaoDisplay'";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	try {
		aq->ExecSQL();
		AddEvent(1,"������ʾ���������޸Ĵ���",userid,storageid,"������ĳɹ�",fcon);
                  ShowMsg(Handle ,"������ĳɹ���",3);
		Close();
	} catch (...) {
		AddEvent(3,"������ʾ���������޸Ĵ���",userid,storageid,"������ĳ���",fcon);
                ShowMsg(Handle ,"�����޸�ʧ�ܣ�",3);
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsyspwdchange::FormClose(TObject *Sender, TCloseAction &Action)

{
	Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsyspwdchange::btConcelClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
