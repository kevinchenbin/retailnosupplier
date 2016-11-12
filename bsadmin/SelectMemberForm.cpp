//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SelectMemberForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ModalDialog"
#pragma link "RzButton"
#pragma link "RzLabel"
#pragma link "RzEdit"
#pragma link "RzLine"
#pragma link "RzDBEdit"
#pragma resource "*.dfm"
TfrmSelectMember *frmSelectMember;
//---------------------------------------------------------------------------
__fastcall TfrmSelectMember::TfrmSelectMember(TComponent* Owner)
	: TfrmModalDialog(Owner)
	, m_memberID(-1)
{
	enterflag = 0;
}
//---------------------------------------------------------------------------
void TfrmSelectMember::Init(LandInfo* li)
{
	TfrmModalDialog::Init(li);
	m_memberID = 0;
	dsetMember->Connection = m_con;
	aq->Connection = m_con;
}
//---------------------------------------------------------------------------
int TfrmSelectMember::GetMemberID()
{
	return m_memberID;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSelectMember::edtMemberKeyPress(TObject *Sender, wchar_t &Key)
{
	//
	if (Key == '\r')
	{
		if (edtMember->Text == "") {
			if (lbl1->Caption == "��Ա����") {
				lbl1->Caption = "���֤��";
			}
			else
			{
				lbl1->Caption = "��Ա����";
			}
			return;
		}
		if (lbl1->Caption == "��Ա����"){
			String sql = "select PassWord,Available,datediff(d,getdate(),youxiaodate) as t  from CUST_MemberInfo where CardID = '" + edtMember->Text .Trim() + "'";
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();
			if (aq->IsEmpty() ) {
				ShowMsg(Handle ,"�޴˻�Ա�����ʵ��",3);
				return;
			}
			//�ж��Ƿ�����Ч����
			if (aq->FieldByName("t")->AsInteger < 0 ) {
				sql = "update CUST_MemberInfo set Available = 0 where CardID = '" + edtMember->Text .Trim() + "'";
				aq->Close();
				aq->SQL->Clear();
				aq->SQL->Add(sql);
				aq->ExecSQL();
				ShowMsg(Handle ,"�û�Ա���ѹ��ڣ������º˷���",3);
				return;
			}

			if (!aq->FieldByName("Available")->AsBoolean ) {
				ShowMsg(Handle ,"�û�Ա�����˿��������ټ���ʹ�ã�",3);
				return;
			}
			if (aq->FieldByName("PassWord")->AsString == "" ) {
				Label1->Visible = false;
				edpassword->Visible = false;
				if (enterflag == 0) {
					enterflag = 1;
					dsetMember->Active = false;
					dsetMember->CommandText = "select ID,Name,CardSN,Balance,Discount"
						" from CUST_MemberInfo left join CUST_MemberType"
						" on CUST_MemberInfo.MemberType=CUST_MemberType.IDType"
						" where CardID='" + edtMember->Text + "'";
					dsetMember->Active = true;
					if (dsetMember->RecordCount >= 1)
					{
						m_memberID = dsetMember->FieldByName("ID")->AsInteger;
						Key = 0;
						Perform(WM_NEXTDLGCTL, 0, 0);
					}
					else
						m_memberID = 0;
				}
				else
				{
					btnOk->Click();
				}
			}
			else
			{
				Label1->Visible = true;
				edpassword->Visible = true;
				edpassword->SetFocus();
			}
		}
		else
		{
			String sql = "select Available from CUST_MemberInfo where bircard = '" + edtMember->Text .Trim() + "'";
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();
			if (aq->IsEmpty() ) {
				ShowMsg(Handle ,"�޴˻�Ա�����ʵ��",3);
				return;
			}
			if (!aq->FieldByName("Available")->AsBoolean ) {
				ShowMsg(Handle ,"�û�Ա�����˿��������ټ���ʹ�ã�",3);
				return;
			}
			if (enterflag == 0) {
				enterflag = 1;
				dsetMember->Active = false;
				dsetMember->CommandText = "select ID,Name,CardSN,Balance,Discount"
					" from CUST_MemberInfo left join CUST_MemberType"
					" on CUST_MemberInfo.MemberType=CUST_MemberType.IDType"
					" where bircard='" + edtMember->Text + "'";
				dsetMember->Active = true;
				if (dsetMember->RecordCount >= 1)
				{
					m_memberID = dsetMember->FieldByName("ID")->AsInteger;
					Key = 0;
					Perform(WM_NEXTDLGCTL, 0, 0);
				}
				else
					m_memberID = 0;
			}
			else
			{
				btnOk->Click();
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmSelectMember::btnCancelClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmSelectMember::dbedtCardSNKeyPress(TObject *Sender, wchar_t &Key)

{
  if (Key = VK_RETURN) {
      btnOk->SetFocus();
  }
}
//---------------------------------------------------------------------------


void __fastcall TfrmSelectMember::edpasswordKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		if (enterflag == 0) {
			if (aq->FieldByName("PassWord")->AsString != edpassword->Text) {

                ShowMsg(Handle ,"��֤�����������ȷ�ϣ�",3);
				return;
			}
			enterflag = 1;
			dsetMember->Active = false;
			dsetMember->CommandText = "select ID,Name,CardSN,Balance,Discount"
				" from CUST_MemberInfo left join CUST_MemberType"
				" on CUST_MemberInfo.MemberType=CUST_MemberType.IDType"
				" where CardID='" + edtMember->Text + "'";
			dsetMember->Active = true;
			if (dsetMember->RecordCount >= 1)
			{
				m_memberID = dsetMember->FieldByName("ID")->AsInteger;
				Key = 0;
				Perform(WM_NEXTDLGCTL, 0, 0);
			}
			else
				m_memberID = 0;
		}
		else
		{
			btnOk->Click();
		}
	}
}
//---------------------------------------------------------------------------




