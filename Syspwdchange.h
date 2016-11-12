//---------------------------------------------------------------------------

#ifndef SyspwdchangeH
#define SyspwdchangeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "global.h"
//---------------------------------------------------------------------------
class Tfrmsyspwdchange : public TForm
{
__published:	// IDE-managed Components
	TADOConnection *fcon;
	TADOQuery *aq;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TEdit *edoldpwd;
	TEdit *ednewpwd;
	TEdit *edpwdagain;
	TButton *btOK;
	TButton *btConcel;
	void __fastcall btOKClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall btConcelClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmsyspwdchange(TComponent* Owner,TADOConnection *con);
	int userid,storageid;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmsyspwdchange *frmsyspwdchange;
//---------------------------------------------------------------------------
#endif
