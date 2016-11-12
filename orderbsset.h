//---------------------------------------------------------------------------

#ifndef orderbssetH
#define orderbssetH
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
//---------------------------------------------------------------------------
class Tfrmorderbsset : public TForm
{
__published:	// IDE-managed Components
	TADOQuery *aquery;
	TADOQuery *qryretairange;
	TDataSource *dsrcretairange;
	TGroupBox *GroupBox3;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TCheckBox *cbautolocalstockbyOrder;
	TEdit *edday;
	TCheckBox *chlastorderdiscount;
	TCheckBox *chchongfuordertishi;
	TEdit *edmonth;
	TCheckBox *chorderfind;
	TCheckBox *chorderchange;
	TSpeedButton *sbcancel;
	TSpeedButton *sbok;
	void __fastcall sbokClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall sbcancelClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmorderbsset(TComponent* Owner,TADOConnection* con);
	void Readydata();
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmorderbsset *frmorderbsset;
//---------------------------------------------------------------------------
#endif
