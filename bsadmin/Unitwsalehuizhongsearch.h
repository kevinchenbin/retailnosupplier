//---------------------------------------------------------------------------

#ifndef UnitwsalehuizhongsearchH
#define UnitwsalehuizhongsearchH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include "DBGridEh.hpp"
#include "GridsEh.hpp"
#include "RzDBGrid.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include "pdtypes.h"
#include "MDIChild.h"
#include <Grids.hpp>
#include "frxClass.hpp"
#include "frxDBSet.hpp"
#include "RzEdit.hpp"
#include <Mask.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class Tfrmwsalehuizhong : public TForm
{
__published:	// IDE-managed Components
	TRzToolbar *rztlbr1;
	TRzToolButton *tlbtn8;
	TRzToolButton *tlbtn7;
	TRzToolButton *BtnNew;
	TRzToolButton *BtnAlignBottom;
	TPanel *Panel1;
	TGroupBox *GroupBox1;
	TRzToolButton *RzToolButton1;
	TRzToolButton *RzToolButton2;
	TLabel *Label2;
	TCheckBox *cbruku;
	TCheckBox *cbstag;
	TDateTimePicker *dtpend;
	TDateTimePicker *dtpstart;
	TCheckBox *cbfahuofanshi;
	TComboBox *cbfahuo;
	TComboBox *cbstgcheck;
	TCheckBox *cbfahuocheck;
	TCheckBox *cbfahuotuihuo;
	TADOQuery *aqdetail;
	TDataSource *ds;
	TRzDBGrid *RzDBGrid1;
	TADOQuery *aqhead;
	TDataSource *dshead;
	TRzDBGrid *dbgrid1;
	TfrxReport *frxhuizhong;
	TfrxDBDataset *frxDBDataset1;
	TLabel *Label1;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TRzNumericEdit *RzNumericEdit1;
	TRzNumericEdit *RzNumericEdit2;
	TRzNumericEdit *RzNumericEdit3;
	TSaveDialog *savedlg;
	TRzToolButton *toolshowmainmenu;
	void __fastcall tlbtn8Click(TObject *Sender);
	void __fastcall cbstgcheckChange(TObject *Sender);
	void __fastcall cbfahuoChange(TObject *Sender);
	void __fastcall dtpstartChange(TObject *Sender);
	void __fastcall frxhuizhongGetValue(const UnicodeString VarName, Variant &Value);
	void __fastcall RzToolButton1Click(TObject *Sender);
	void __fastcall RzToolButton2Click(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall tlbtn7Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall BtnNewClick(TObject *Sender);
	void __fastcall dbgrid1CellClick(TColumn *Column);
	void __fastcall toolshowmainmenuClick(TObject *Sender);

private:	// User declarations
 int StgID;
    LandInfo linfo;
       int UserID;
       AnsiString username;
       AnsiString stgname;
       TADOConnection *fcn;
       int totalamount;
       float totaldis,totalfix;
       void print(int type);
     bool DbgridToExcel(TDBGrid *dbg);
public:		// User declarations
	__fastcall Tfrmwsalehuizhong(TComponent* Owner);
        void init(LandInfo* li);
        void GetTotal();
        void ShowHead();
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmwsalehuizhong *frmwsalehuizhong;
//---------------------------------------------------------------------------
#endif
