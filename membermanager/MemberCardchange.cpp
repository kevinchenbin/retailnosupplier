//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MemberCardchange.h"
#include "Addsyslog.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma resource "*.dfm"
TfrmMemberCardChange *frmMemberCardChange;
//---------------------------------------------------------------------------
__fastcall TfrmMemberCardChange::TfrmMemberCardChange(TComponent* Owner,TADOConnection *cn,int memberid)
	: TForm(Owner)
{
	id =  memberid;
	aq->Connection = cn;
	fcon = cn;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMemberCardChange::Button1Click(TObject *Sender)
{
	if (ShowMsg(Handle ,"ȷ���޸���֤�룿",1)!=1) {
    	return;
	}
	if (ednew->Text != edconfirm->Text ) {

                ShowMsg(Handle ,"����������֤�벻һ�£���ȷ�ϣ�",3);
		return;
	}
	AnsiString sql;
	sql = "update CUST_MemberInfo set PassWord = '" + ednew->Text.Trim() + "' where id = " + IntToStr(id);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	logmessage = "�Ի�Ա��" +  logmessage + "��������֤��";
	AddEvent(1,"�޸ģ����ã���֤�봰��",userid,fstgid,logmessage,fcon);
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberCardChange::Button2Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMemberCardChange::FormClose(TObject *Sender, TCloseAction &Action)

{
	Action = caFree ;
}
//---------------------------------------------------------------------------
