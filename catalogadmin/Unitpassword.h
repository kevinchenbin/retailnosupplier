//---------------------------------------------------------------------------

#ifndef UnitpasswordH
#define UnitpasswordH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class Tfrmpassword : public TForm
{
__published:	// IDE-managed Components
	TEdit *editpassword;
	TLabel *Label1;
	TButton *Button1;
	TButton *Button2;
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmpassword(TComponent* Owner);
        AnsiString password;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmpassword *frmpassword;
//---------------------------------------------------------------------------
#endif
