//---------------------------------------------------------------------------

#ifndef UnitchongfuorderH
#define UnitchongfuorderH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <DB.hpp>
#include <ADODB.hpp>
#include "RzButton.hpp"
//---------------------------------------------------------------------------
class Tfrmchongfuorder : public TForm
{
__published:	// IDE-managed Components
	TDataSource *ds;
	TADOQuery *query;
	TDBGrid *DBGrid1;
	TRzButton *RzButton1;
	TRzButton *quit;
	void __fastcall quitClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall RzButton1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmchongfuorder(TComponent* Owner,TADOQuery *aq);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmchongfuorder *frmchongfuorder;
//---------------------------------------------------------------------------
#endif
