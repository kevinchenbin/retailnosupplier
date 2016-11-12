//---------------------------------------------------------------------------

#ifndef RecMoneyFormH
#define RecMoneyFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ModalDialog.h"
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include "RzLabel.hpp"
#include "RzEdit.hpp"
#include <Mask.hpp>
//---------------------------------------------------------------------------
class TfrmRecMoney : public TfrmModalDialog
{
__published:	// IDE-managed Components
	TRzGroupBox *grpbx1;
	TRzLabel *lbl1;
	TRzLabel *lbl2;
	TRzLabel *lbl3;
	TRzNumericEdit *numedtChecked;
	TRzNumericEdit *numedtReceive;
	TRzNumericEdit *numedtUnchecked;
	TRzLabel *RzLabel1;
	TRzNumericEdit *numedtshoud;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall numedtReceiveKeyPress(TObject *Sender, wchar_t &Key);
private:	// User declarations
	double m_checked;//已结
	double m_receive;//收款
	double m_discountedPrice;//总额
	double m_unchecked; //未结
public:		// User declarations
	__fastcall TfrmRecMoney(TComponent* Owner);
	void SetChecked(double checked);
	void SetDiscountedPrice(double discountedPrice);
	float GetReceived();
	AnsiString format;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmRecMoney *frmRecMoney;
//---------------------------------------------------------------------------
#endif
