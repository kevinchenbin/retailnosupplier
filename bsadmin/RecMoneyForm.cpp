//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "RecMoneyForm.h"
#include   <math.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ModalDialog"
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "RzLabel"
#pragma link "RzEdit"
#pragma resource "*.dfm"

TfrmRecMoney *frmRecMoney;
//---------------------------------------------------------------------------
__fastcall TfrmRecMoney::TfrmRecMoney(TComponent* Owner)
	: TfrmModalDialog(Owner)
	, m_checked(0)
	, m_receive(0)
	, m_discountedPrice(0)
{
}
//---------------------------------------------------------------------------
void TfrmRecMoney::SetChecked(double checked)
{
	m_checked = checked;
}
//---------------------------------------------------------------------------
void TfrmRecMoney::SetDiscountedPrice(double discountedPrice)
{
	m_discountedPrice = discountedPrice;
}

//---------------------------------------------------------------------------
void __fastcall TfrmRecMoney::FormShow(TObject *Sender)
{
	numedtChecked->Value = m_checked;
	numedtReceive->Value = m_receive;
	numedtUnchecked->Value = m_discountedPrice - m_checked;

	numedtshoud->Value =  m_discountedPrice;
	numedtshoud->DisplayFormat = format;
	numedtChecked->DisplayFormat = format;
	numedtReceive->DisplayFormat = format;
	numedtUnchecked->DisplayFormat = format;
        numedtReceive->SelectAll();
        numedtReceive->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TfrmRecMoney::numedtReceiveKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r')
	{
        if (m_discountedPrice > 0) {
			numedtReceive->Value = fabs(numedtReceive->Value);
		}
		if (m_discountedPrice < 0) {
			numedtReceive->Value = -fabs(numedtReceive->Value);
		}
		if (numedtReceive->Value > m_discountedPrice - m_checked && m_discountedPrice > 0)
		{
			numedtReceive->Value = m_discountedPrice - m_checked;
		}
		if (numedtReceive->Value < m_discountedPrice - m_checked && m_discountedPrice < 0)
		{
			numedtReceive->Value = m_discountedPrice - m_checked;
		}
		m_unchecked = m_discountedPrice - m_checked - numedtReceive->Value;
		numedtUnchecked->Value = StrToFloat(FormatFloat("0.00",m_unchecked));

		m_receive = numedtReceive->Value;

		btnOk->SetFocus();
	}
}
//---------------------------------------------------------------------------

float TfrmRecMoney::GetReceived()
{
 	return m_receive;
}
//---------------------------------------------------------------------------

