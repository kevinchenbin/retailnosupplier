//---------------------------------------------------------------------------

#ifndef UnittongyidiscountH
#define UnittongyidiscountH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include "RzEdit.hpp"
#include <Mask.hpp>
#include "RzButton.hpp"
//---------------------------------------------------------------------------
class Tfrmtongyidiscount : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TRzNumericEdit *nedit;
	TRzButton *sbok;
	TRzButton *sbcancel;
	TComboBox *cbfahuofangshi;
	TCheckBox *CheckBox1;
	TCheckBox *CheckBox2;
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmtongyidiscount(TComponent* Owner);
        float getdiscount();
        AnsiString getfahuofangshi();
        bool actionex;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmtongyidiscount *frmtongyidiscount;
//---------------------------------------------------------------------------
#endif
