//---------------------------------------------------------------------------

#ifndef UnitkemusetH
#define UnitkemusetH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class Tfrmkemuset : public TForm
{
__published:	// IDE-managed Components
	TDBGrid *DBGrid1;
	TRzToolbar *RzToolbar1;
	TRzToolButton *BtnNew;
	TRzToolButton *BtnExit;
	TRzToolButton *BtnAlignBottom;
	TEdit *editkemuname;
	TLabel *Label1;
	TLabel *Label2;
	TComboBox *cbtype;
	TADOQuery *aq;
	TDataSource *DataSource1;
	TADOQuery *aq1;
	TRzToolButton *RzToolButton1;
	void __fastcall BtnNewClick(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall DBGrid1CellClick(TColumn *Column);
	void __fastcall RzToolButton1Click(TObject *Sender);
private:	// User declarations
       int saveflag;
       TADOConnection *fcon;
public:		// User declarations
	__fastcall Tfrmkemuset(TComponent* Owner);
        void init(TADOConnection *Acon);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmkemuset *frmkemuset;
//---------------------------------------------------------------------------
#endif
