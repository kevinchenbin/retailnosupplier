//---------------------------------------------------------------------------

#ifndef UnitInputmessageH
#define UnitInputmessageH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class Tfrminputmessage : public TForm
{
__published:	// IDE-managed Components
	TMemo *meminfor;
	TButton *Button1;
	TButton *Button2;
	TLabel *Label1;
	void __fastcall meminforKeyPress(TObject *Sender, wchar_t &Key);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrminputmessage(TComponent* Owner);
        void settitle(AnsiString capt1,AnsiString capt2);
        AnsiString GetInfor();
        void SetDisplayInfo(AnsiString msg);

};
//---------------------------------------------------------------------------
extern PACKAGE Tfrminputmessage *frminputmessage;
//---------------------------------------------------------------------------
#endif
