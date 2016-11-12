//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Addstorge.h"
#include "Addsyslog.h"
#include "global.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma link "RzButton"
#pragma resource "*.dfm"
TfrmAddstorge *frmAddstorge;
//---------------------------------------------------------------------------
__fastcall TfrmAddstorge::TfrmAddstorge(TComponent* Owner,TADOQuery *aquery,int modle)
	: TForm(Owner)
{
	query = aquery;
	querymod->Connection = aquery->Connection ;
	Modle = modle;
	con = aquery->Connection ;
}
//---------------------------------------------------------------------------
void __fastcall TfrmAddstorge::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmAddstorge::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmAddstorge::BtnSaveClick(TObject *Sender)
{
	String sql;
	if (edname->Text == "") {
		ShowMsg(this->Handle,"��ֵ����ֲ���Ϊ��!",3);
		return;
	}
	if (Modle == 1) {  //  ���
		sql = "select count(*) as count from SYS_StorageInfo where Name = '" + edname->Text + "'" ;
		querymod->Close();
		querymod->SQL->Clear();
		querymod->SQL->Add(sql);
		querymod->Open();
		if (querymod->FieldByName("count")->AsInteger > 0) {
			ShowMsg(this->Handle,"�õ���Ѵ��ڣ�",3);
			return;
		}
		if (ShowMsg(this->Handle,"ȷ����ӵ�֣�",1) == 1) {
			sql = "insert into SYS_StorageInfo(Name,Address,Contact,Tel,printtitle) values('" + edname->Text.Trim() + "','" + edaddress->Text.Trim() + "','" + edcontact->Text.Trim() + "','" + edtel->Text.Trim() + "','" + edprinttitle->Text.Trim() + "')";
			querymod->Close();
			querymod->SQL->Clear();
                        querymod->SQL->Add("declare @idd int;");
			querymod->SQL->Add(sql);

                        querymod->SQL->Add("set @idd = SCOPE_IDENTITY();");

                          querymod->SQL->Add("insert into CUST_CustomerInfo(type,name,stgid)values(1,'��ͨ��Ӧ��',@idd);");
                         querymod->SQL->Add("insert into CUST_CustomerInfo(type,name,stgid)values(2,'��ͨ�ͻ�',@idd);");



			querymod->ExecSQL();




			logmessage = "��ӵ��" + edname->Text ;
			AddEvent(1,"��ӵ��",userid,storageid,logmessage,con);
			query->Active = false;
			query->Active = true;
			Close();
		}
	}
	else    //   �޸�
	{
		sql = "select count(*) as count from SYS_StorageInfo where Name = '" + edname->Text + "' and ID <> " + query->FieldByName("ID")->AsString;
		querymod->Close();
		querymod->SQL->Clear();
		querymod->SQL->Add(sql);
		querymod->Open();
		if (querymod->FieldByName("count")->AsInteger > 0) {
			ShowMsg(this->Handle,"�õ���Ѵ��ڣ�",3);
			return;
		}
		if (ShowMsg(this->Handle,"ȷ���޸ĸõ�֣�",1) == 1) {
			sql = "update SYS_StorageInfo set Name = '" + edname->Text.Trim() + "',Tel = '" + edtel->Text.Trim();
			sql = sql + "',Contact = '" + edcontact->Text.Trim() + "',Address = '" + edaddress->Text.Trim() + "',printtitle = '" + edprinttitle->Text.Trim() ;
			sql = sql + "' where ID = " + query->FieldByName("ID")->AsString ;
			querymod->Close();
			querymod->SQL->Clear();
			querymod->SQL->Add(sql);
			querymod->ExecSQL();
			query->Refresh();
            Close();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmAddstorge::FormShow(TObject *Sender)
{
	if (Modle == 2) {
		this->Caption = "�޸ĵ��";
		edname->Text = query->FieldByName("Name")->AsString ;
		edtel->Text = query->FieldByName("Tel")->AsString ;
		edcontact->Text = query->FieldByName("Contact")->AsString ;
		edaddress->Text = query->FieldByName("Address")->AsString ;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmAddstorge::ednameKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
        edtel->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmAddstorge::edtelKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
        edcontact->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmAddstorge::edcontactKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
        edaddress->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmAddstorge::edaddressKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
        BtnSave->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmAddstorge::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmAddstorge::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key ==115) {   //����
		BtnSave->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 81 ) {    //�˳�
		BtnExit->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==90) {   //�ָ�����
		WindowState = wsNormal  ;
	}
}
//---------------------------------------------------------------------------

