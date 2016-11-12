//---------------------------------------------------------------------------

#ifndef UnitjizhangH
#define UnitjizhangH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzGrids.hpp"
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "RzTabs.hpp"
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include "RzDTP.hpp"
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include "frxClass.hpp"
#include "frxCross.hpp"
#include "DBGridEh.hpp"
#include "GridsEh.hpp"
#include "frxDBSet.hpp"
#include "RzDBGrid.hpp"
#include <DBGrids.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
struct savecells
{
   AnsiString titleid;
   int x,y;
   AnsiString valuestr;
   AnsiString valuebk;

};
class Tfrmjizhang : public TForm
{
__published:	// IDE-managed Components
	TADOConnection *ADOConnection1;
	TADOQuery *aq1;
	TRzPageControl *RzPageControl1;
	TRzTabSheet *TabSheet1;
	TRzTabSheet *TabSheet2;
	TRzToolbar *RzToolbar1;
	TRzToolButton *BtnNew;
	TRzToolButton *BtnExit;
	TRzToolButton *BtnAlignBottom;
	TADOQuery *aq2;
	TRzDateTimePicker *dtpdate;
	TLabel *Label1;
	TSpeedButton *sbsearch;
	TADOQuery *aqb;
	TfrxReport *frxjizhang;
	TfrxCrossObject *frxCrossObject1;
	TRzToolButton *RzToolButton1;
	TDataSource *dsa;
	TDataSource *dsb;
	TADOQuery *aqa;
	TRzToolButton *RzToolButton2;
	TRzDBGrid *dg;
	TLabel *Label2;
	TEdit *editheji;
	TRzDBGrid *dgb;
	TLabel *Label3;
	TEdit *Edit1;
	TPopupMenu *PopupMenu1;
	TMenuItem *D1;
	TfrxDBDataset *frxdb;
	void __fastcall BtnNewClick(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall sbsearchClick(TObject *Sender);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall RzToolButton1Click(TObject *Sender);
	void __fastcall frxjizhangGetValue(const UnicodeString VarName, Variant &Value);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall RzPageControl1Change(TObject *Sender);
	void __fastcall RzToolButton2Click(TObject *Sender);
	void __fastcall D1Click(TObject *Sender);
	void __fastcall dgKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dgbKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dgColExit(TObject *Sender);
	void __fastcall dgbColExit(TObject *Sender);

private:	// User declarations
TADOConnection  *fcon;
 int fstorageid,fuserid;
 int jizhangid;
     struct savecells *shouru;
     struct savecells *zhichu;
     int shouruint,zhichuint;
     double hejistg;
     int m_CurrentCol,m_CurrentRow;
     int master;
     AnsiString titleshouru;
     void print(int type);


public:		// User declarations
	__fastcall Tfrmjizhang(TComponent* Owner);
        void init(TADOConnection *Acon,int AStorageID,int AUserID);
        void DataRead();
        void DataRead1();
        void DateTotalReade();
        AnsiString Astgid;
        AnsiString stgname;
        AnsiString Ausername;
         void search();
         void SaveData();

};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmjizhang *frmjizhang;
//---------------------------------------------------------------------------
#endif
