//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unitchangeaddvalue.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma resource "*.dfm"
Tfrmchangeaddvalue *frmchangeaddvalue;
//---------------------------------------------------------------------------
__fastcall Tfrmchangeaddvalue::Tfrmchangeaddvalue(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tfrmchangeaddvalue::RzButton2Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmchangeaddvalue::RzButton1Click(TObject *Sender)
{
	if (ednow->Text == "") {
		return;
	}
	try {
		StrToFloat(ednow->Text);
	} catch (...) {

                ShowMsg(Handle ,"请输入正确的充值金额！",3);
		return;
	}
	AnsiString sdf;
	sdf =  "您确认对会员："+edname->Text.Trim() +"修改充值金额" + edyuan->Text + "为" + ednow->Text+"元吗？";

	if(ShowMsg(Handle ,sdf.c_str(),1)==1)
	{
		ModalResult = mrOk ;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmchangeaddvalue::FormClose(TObject *Sender, TCloseAction &Action)

{
	Action = caFree ;
}
//---------------------------------------------------------------------------
float Tfrmchangeaddvalue::getValue()

{
	float value;
	value = StrToFloat(ednow->Text);
	return value;
}
//---------------------------------------------------------------------------
