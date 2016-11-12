//---------------------------------------------------------------------------

#ifndef UnitaddclientH
#define UnitaddclientH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class Tfrmaddclient : public TForm
{
__published:	// IDE-managed Components
	TEdit *edclient;
	TComboBox *cbclient;
	TLabel *Label1;
	TButton *Button1;
	TButton *Button2;
	TADOConnection *ADOConnection1;
	TADOQuery *aq;
	void __fastcall edclientKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbclientKeyPress(TObject *Sender, wchar_t &Key);
private:	// User declarations
TADOConnection *fcon;
int fstgid;
public:		// User declarations
	__fastcall Tfrmaddclient(TComponent* Owner,TADOConnection *con,int stgid);
        int getselectclient();


};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmaddclient *frmaddclient;
//---------------------------------------------------------------------------
#endif
