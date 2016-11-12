//---------------------------------------------------------------------------

#ifndef UnitjizhangsearchH
#define UnitjizhangsearchH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "DBGridEh.hpp"
#include "GridsEh.hpp"
#include "RzDTP.hpp"
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include "frxClass.hpp"
#include "frxDBSet.hpp"
//---------------------------------------------------------------------------
class Tfrmsearch : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TDBGridEh *dg;
	TSpeedButton *SpeedButton1;
	TLabel *Label2;
	TLabel *Label3;
	TRzDateTimePicker *dtpend;
	TRzDateTimePicker *dtpbegin;
	TCheckBox *cbbumen;
	TCheckBox *cbkemu;
	TComboBox *cbstg;
	TComboBox *cbkemus;
	TADOConnection *con;
	TADOQuery *aq;
	TDataSource *ds;
	TRzToolbar *RzToolbar1;
	TRzToolButton *BtnExit;
	TRzToolButton *RzToolButton1;
	TRzToolButton *RzToolButton2;
	TfrxReport *frxjizhang;
	TfrxDBDataset *frxdb;
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall frxjizhangGetValue(const UnicodeString VarName, Variant &Value);
	void __fastcall RzToolButton1Click(TObject *Sender);
	void __fastcall RzToolButton2Click(TObject *Sender);

private:	// User declarations
          TADOConnection *fcon;
          int fuserid,fstorageid;

public:		// User declarations
	__fastcall Tfrmsearch(TComponent* Owner);
          void init(TADOConnection *Acon,int AStorageID,int AUserID);
        void DataRead();
        void DataRead1();
        AnsiString fusername;
        AnsiString titleshouru;
        AnsiString stgname;
        void print(int type);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmsearch *frmsearch;
//---------------------------------------------------------------------------
#endif
