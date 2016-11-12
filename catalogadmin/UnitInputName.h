//---------------------------------------------------------------------------

#ifndef UnitInputNameH
#define UnitInputNameH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class Tfrminput : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TEdit *editname;
	TBitBtn *BitBtn1;
	void __fastcall BitBtn1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrminput(TComponent* Owner);
        AnsiString aname;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrminput *frminput;
//---------------------------------------------------------------------------
#endif
