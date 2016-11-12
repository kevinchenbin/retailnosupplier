//---------------------------------------------------------------------------

#ifndef UnitnewfileH
#define UnitnewfileH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class Tfrmnewfile : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TEdit *editfoldername;
	TButton *Button1;
	TButton *Button2;
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmnewfile(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmnewfile *frmnewfile;
//---------------------------------------------------------------------------
#endif
