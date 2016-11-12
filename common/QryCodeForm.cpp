//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "QryCodeForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma resource "*.dfm"
TfrmQryCode *frmQryCode;
//---------------------------------------------------------------------------
__fastcall TfrmQryCode::TfrmQryCode(TComponent* Owner,TADOConnection *con,int stgid,int mode,int type)
	: TForm(Owner)
{
	fcon = con;
	ftype = type;
	fstgid = stgid;
	query->Connection = con;
	fmode = mode;
	dtp1->Date = Date();
	dtp2->Date = Date();
}
//---------------------------------------------------------------------------
void __fastcall TfrmQryCode::RzButton1Click(TObject *Sender)
{
	AnsiString sql;
	if (ftype == 0) { //ÁãÊÛ
    	sql = "select hdtime,retailntcode as code from BS_RetailNoteHeader ";
		sqlwhere = " where stgid = " + IntToStr(fstgid);
		if (fmode == 0) {
			sqlwhere = sqlwhere + " and TotalAmount >= 0";
		}
		else
		{
			sqlwhere = sqlwhere + " and TotalAmount < 0";
		}
		if (ch1->Checked ) {
			sqlwhere = sqlwhere + " and datediff(day,hdtime,'" + DateToStr(dtp1->Date) + "') <= 0";
		}
		if (ch2->Checked ) {
			sqlwhere = sqlwhere + " and datediff(day,hdtime,'" + DateToStr(dtp2->Date) + "') >= 0";
		}
		sql = sql + sqlwhere;
                sql = sql + " and retailntcode <>0 ";
	}
	else
	{
		sql = "select adjustdate as hdtime,adjustheaderid as code from STK_AdjustHeader ";
		sqlwhere = " where stgid = " + IntToStr(fstgid);
		if (ch1->Checked ) {
			sqlwhere = sqlwhere + " and datediff(day,adjustdate,'" + DateToStr(dtp1->Date) + "') <= 0";
		}
		if (ch2->Checked ) {
			sqlwhere = sqlwhere + " and datediff(day,adjustdate,'" + DateToStr(dtp2->Date) + "') >= 0";
		}
		sql = sql + sqlwhere;
	}
          // sql = sql + " and retailntcode <>0 order by id desc";
   sql = sql + "  order by id desc";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
}
//---------------------------------------------------------------------------
void __fastcall TfrmQryCode::DBGrid1DblClick(TObject *Sender)
{
	if (query->IsEmpty() ) {
		return;
	}
	ModalResult = mrOk ;
}
//---------------------------------------------------------------------------
void __fastcall TfrmQryCode::DBGrid1KeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		if (query->IsEmpty() ) {
			return;
		}
		ModalResult = mrOk ;
	}
}
//---------------------------------------------------------------------------
AnsiString TfrmQryCode::GetNoteCode()
{
	AnsiString code;
	code = query->FieldByName("code")->AsAnsiString ;
	return code;
}
//---------------------------------------------------------------------------
void __fastcall TfrmQryCode::dtp1Change(TObject *Sender)
{
	ch1->Checked = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmQryCode::dtp2Change(TObject *Sender)
{
	ch2->Checked = true;
}
//---------------------------------------------------------------------------
