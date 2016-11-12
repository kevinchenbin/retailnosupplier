//---------------------------------------------------------------------------

#ifndef procuresetH
#define procuresetH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ADODB.hpp>
#include <Buttons.hpp>
#include <DB.hpp>
#include "pdtypes.h"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include "RzCmboBx.hpp"
#include "global.h"
//---------------------------------------------------------------------------
class Tfrmprocureset : public TForm
{
__published:	// IDE-managed Components
	TADOQuery *aquery;
	TADOQuery *qryretairange;
	TDataSource *dsrcretairange;
	TSpeedButton *sbcancel;
	TSpeedButton *sbok;
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TCheckBox *chprocurefindpwd;
	TCheckBox *chprocuredeletepwd;
	TCheckBox *chznprocurefindpwd;
	TCheckBox *chznprocuredeletepwd;
	TEdit *edday;
	void __fastcall sbokClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall sbcancelClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmprocureset(TComponent* Owner,TADOConnection* con);
	void Readydata();
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmprocureset *frmprocureset;
//---------------------------------------------------------------------------
#endif
