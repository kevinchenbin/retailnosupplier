//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MixedRecMoneyForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ModalDialog"
#pragma link "RzButton"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzPanel"
#pragma link "RzDBEdit"
#pragma link "RzLine"
#pragma resource "*.dfm"
TfrmMixedRecMoney *frmMixedRecMoney;
//---------------------------------------------------------------------------
__fastcall TfrmMixedRecMoney::TfrmMixedRecMoney(TComponent* Owner)
	: TfrmModalDialog(Owner)
	, m_mustRec(0)
	, m_cardRec(0)
	, m_cashRec(0)
	, m_cardRemain(0)
{
}
//---------------------------------------------------------------------------

void TfrmMixedRecMoney::SetMustRec(float mustrec)
{
	m_mustRec = mustrec;
}

void TfrmMixedRecMoney::SetCardRemain(float remain)
{
	m_cardRemain = remain;
}

void TfrmMixedRecMoney::GetRecMoney(float& card,float& cash,float& poscard,float& youhuiquan,float& wexi,float& m_zfb)
{
	card = numedtCard->Value ;
	cash = numedtCash->Value ;
	poscard = numedtposcard->Value ;
	youhuiquan = numedtyouhui->Value ;
	wexi=weixin->Value ;
	m_zfb=zifubao->Value;
}

void __fastcall TfrmMixedRecMoney::numedtCardKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r')
	{

	   /*	if (numedtCard->Value > m_mustRec - numedtyouhui->Value - numedtposcard->Value )//���������ڱ��ս��
			numedtCard->Value = m_mustRec - numedtyouhui->Value - numedtposcard->Value ;

		if (numedtCard->Value > m_cardRemain)//���������ڿ������
			numedtCard->Value = m_cardRemain;

		if (numedtCard->Value < 0)
			numedtCard->Value = 0;

	   //	numedtCash->Value = m_mustRec - numedtCard->Value - numedtyouhui->Value - numedtposcard->Value;
             */


		btnOk->Enabled=checkyingShouIsOK();
		 if (btnOk->Enabled) {
			btnOk->SetFocus();
		 }else 	numedtyouhui->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMixedRecMoney::FormShow(TObject *Sender)
{
	numedtMustRecMoney->Value = m_mustRec;

	numedtCard->Value = m_cardRec;
	numedtCash->Value = m_cashRec;
	numedtRemain->Value = m_cardRemain;
	if (numedtCard->Enabled ) {
		numedtCard->SetFocus();
	}
	else
	{
    	numedtyouhui->SetFocus();
	}

}
//---------------------------------------------------------------------------

void __fastcall TfrmMixedRecMoney::numedtCashKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r')
	{

					 btnOk->Enabled=checkyingShouIsOK();
		 if (btnOk->Enabled) {
			btnOk->SetFocus();
		 }

	}
}
//---------------------------------------------------------------------------

void TfrmMixedRecMoney::SetRecCard(float card)
{
	m_cardRec = card;
}

void TfrmMixedRecMoney::SetRecCash(float cash)
{
	m_cashRec = cash;
}

void __fastcall TfrmMixedRecMoney::numedtCardExit(TObject *Sender)
{
	//
	  ssje->Value = numedtCard->Value + numedtyouhui->Value+numedtposcard->Value+zifubao->Value+weixin->Value+numedtCash->Value;


}
//---------------------------------------------------------------------------



void __fastcall TfrmMixedRecMoney::numedtyouhuiKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
				btnOk->Enabled=checkyingShouIsOK();
		 if (btnOk->Enabled) {
			btnOk->SetFocus();
		 }else numedtposcard->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMixedRecMoney::numedtposcardKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {

			btnOk->Enabled=checkyingShouIsOK();
		 if (btnOk->Enabled) {
			btnOk->SetFocus();
		 }else
		 zifubao->SetFocus();

	}
}
//---------------------------------------------------------------------------



void __fastcall TfrmMixedRecMoney::numedtyouhuiExit(TObject *Sender)
{
	  /*	if (numedtyouhui->Value > m_mustRec - numedtCard->Value - numedtposcard->Value )
			numedtyouhui->Value = m_mustRec - numedtCard->Value - numedtposcard->Value ;

		if (numedtyouhui->Value < 0)
			numedtyouhui->Value = 0;

		numedtCash->Value = m_mustRec - numedtCard->Value - numedtyouhui->Value - numedtposcard->Value  ; */
}
//---------------------------------------------------------------------------

void __fastcall TfrmMixedRecMoney::t(TObject *Sender)
{
	 /*	if (numedtposcard->Value > m_mustRec - numedtCard->Value - numedtyouhui->Value )
			numedtposcard->Value = m_mustRec - numedtCard->Value - numedtyouhui->Value ;

		if (numedtposcard->Value < 0)
			numedtposcard->Value = 0;

		numedtCash->Value = m_mustRec - numedtCard->Value - numedtyouhui->Value - numedtposcard->Value  ;   */
}
//---------------------------------------------------------------------------

void __fastcall TfrmMixedRecMoney::numedtCashClick(TObject *Sender)
{
 //	numedtCash->Value = m_mustRec - numedtCard->Value - numedtyouhui->Value - numedtposcard->Value ;
}
//---------------------------------------------------------------------------


void __fastcall TfrmMixedRecMoney::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Shift.Contains(ssAlt)&& Key ==65) {   //��ֵ��
		numedtCard->SetFocus();
	}
	if (Shift.Contains(ssAlt)&& Key ==83) {    //�Ż�ȯ
		numedtyouhui->SetFocus();
	}
	if (Shift.Contains(ssAlt)&& Key ==90) {   //���п�
		numedtposcard->SetFocus();
	}
	if (Shift.Contains(ssAlt)&& Key == 88) {    //�ֽ�
		numedtCash->SetFocus();
	}
}
//---------------------------------------------------------------------------


boolean TfrmMixedRecMoney::checkyingShouIsOK()
{
	float yishou;
	yishou = numedtCard->Value + numedtyouhui->Value+numedtposcard->Value+zifubao->Value+weixin->Value+numedtCash->Value;
	if (m_mustRec!=yishou) {
	return false;
	} else return true;
}



void __fastcall TfrmMixedRecMoney::zifubaoKeyPress(TObject *Sender, wchar_t &Key)

{
if (Key == '\r') {

		btnOk->Enabled=checkyingShouIsOK();
		 if (btnOk->Enabled) {
			btnOk->SetFocus();
		 }else
		 weixin->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMixedRecMoney::weixinKeyPress(TObject *Sender, wchar_t &Key)
{
	 if (Key == '\r') {

		btnOk->Enabled=checkyingShouIsOK();
		 if (btnOk->Enabled) {
			btnOk->SetFocus();
		 }else
		 numedtCash->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMixedRecMoney::numedtposcardExit(TObject *Sender)
{
/*  	if (numedtposcard->Value > m_mustRec - numedtCard->Value - numedtposcard->Value )
			numedtyouhui->Value = m_mustRec - numedtCard->Value - numedtposcard->Value ;

		if (numedtyouhui->Value < 0)
			numedtyouhui->Value = 0;

		numedtCash->Value = m_mustRec - numedtCard->Value - numedtyouhui->Value - numedtposcard->Value  ; */
}
//---------------------------------------------------------------------------



