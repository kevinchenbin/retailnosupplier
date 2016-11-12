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

                ShowMsg(Handle ,"��������ȷ�ĳ�ֵ��",3);
		return;
	}
	AnsiString sdf;
	sdf =  "��ȷ�϶Ի�Ա��"+edname->Text.Trim() +"�޸ĳ�ֵ���" + edyuan->Text + "Ϊ" + ednow->Text+"Ԫ��";

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
