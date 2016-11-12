//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unitfahuocode.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma resource "*.dfm"
Tfrmfahuocode *frmfahuocode;
//---------------------------------------------------------------------------
__fastcall Tfrmfahuocode::Tfrmfahuocode(TComponent* Owner,TADOQuery *query)
	: TForm(Owner)
{
	aquery = query;
	ds->DataSet = aquery;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmfahuocode::RzButton2Click(TObject *Sender)
{
	newid = 1;
	ModalResult = mrOk ;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmfahuocode::RzButton1Click(TObject *Sender)
{
	newid = 0;
	wsheadid = aquery->FieldByName("id")->AsInteger ;
	ModalResult = mrOk ;
}
//---------------------------------------------------------------------------
