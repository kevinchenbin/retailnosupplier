//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unitautojie.h"
#include "global.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma resource "*.dfm"
Tfrmautojieshuan *frmautojieshuan;
//---------------------------------------------------------------------------
__fastcall Tfrmautojieshuan::Tfrmautojieshuan(TComponent* Owner)
	: TForm(Owner)
{
	yuhukuan = false;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmautojieshuan::editshijieKeyPress(TObject *Sender, wchar_t &Key)
          
{
	if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key !='.')&&(Key!='\b')) {
	  	Key = NULL;
	}
	if (Key == VK_RETURN) {
		FLOAT yihu,shi;
		AnsiString syinhu,sshijie;
		syinhu = StringReplace(edityinhu->Text,",","",TReplaceFlags()<<rfReplaceAll);
		sshijie =StringReplace(editshijie->Text,",","",TReplaceFlags()<<rfReplaceAll);
		yihu = StrToFloat(syinhu);
		shi = StrToFloat(sshijie);
		if (yihu < 0.00 && shi > 0.00) {
			editshijie->Text = "-" + editshijie->Text;
		}
		RzButton2->SetFocus() ;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmautojieshuan::RzButton2Click(TObject *Sender)
{
	FLOAT yihu,shi;
	AnsiString syinhu,sshijie;

	syinhu = StringReplace(edityinhu->Text,",","",TReplaceFlags()<<rfReplaceAll);
	yihu = StrToFloat(syinhu);
	sshijie =StringReplace(editshijie->Text,",","",TReplaceFlags()<<rfReplaceAll);
	shi = StrToFloat(sshijie);
	if (yihu < 0 && shi > 0) {
    	editshijie->Text = "-" + editshijie->Text ;
	}
	if (yue > 0 && shi > yue) {
		if (ShowMsg(this->Handle,"实结金额大于余额，是否继续按实结金额结算？",1) != 1) {
        	editshijie->Text = "0.00";
			editshijie->SetFocus();
			return;
		}
	}
	if (yihu < 0 && shi < yihu) {
		AnsiString msg;
		msg = Label1->Caption + "金额为负时，实结金额不能小于" + Label1->Caption + "金额！";
		ShowMsg(this->Handle,msg.c_str(),3);
		editshijie->Text = "0.00";
		editshijie->SetFocus();
		return;
	}
	if (shi>yihu) {
    	AnsiString msg;
		msg = Label1->Caption.SubString(2,2);
		msg = "是否将余额转入预" + msg + "款？";
		if (ShowMsg(this->Handle,msg.c_str(),1) == 1) {
			yuhukuan = true;
			editshijie->Text = StringReplace(editshijie->Text,",","",TReplaceFlags()<<rfReplaceAll);
			ModalResult = mrOk ;
		}
		else
		{
			if (yihu > 0) {
            	editshijie->Text = "0.00";
				editshijie->SetFocus();
			}
			else
			{
				yuhukuan = false;
				editshijie->Text = StringReplace(editshijie->Text,",","",TReplaceFlags()<<rfReplaceAll);
				ModalResult = mrOk ;
			}
		}
	}
	editshijie->Text = StringReplace(editshijie->Text,",","",TReplaceFlags()<<rfReplaceAll);
	ModalResult = mrOk ;
}
//---------------------------------------------------------------------------


void __fastcall Tfrmautojieshuan::RzButton1Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

