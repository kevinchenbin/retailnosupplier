//---------------------------------------------------------------------------

#ifndef retailbookupH
#define retailbookupH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include <ComCtrls.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
#include <Buttons.hpp>
#include "RzDBEdit.hpp"
#include "RzEdit.hpp"
#include <Mask.hpp>
#include "DBGridEh.hpp"
#include "GridsEh.hpp"
#include "UnitBIOrder.h"
#include "UnitDiaobo.h"
#include "ProcureMng.h"
//---------------------------------------------------------------------------
class Tfrmretailbookup : public TForm
{
__published:	// IDE-managed Components
	TImageList *ImageList1;
	TRzToolbar *RzToolbar1;
	TRzToolButton *BtnExport;
	TRzToolButton *BtnExit;
	TADOConnection *fcon;
	TRzToolButton *BtnView;
	TDataSource *dsdetail;
	TADOQuery *qudetail;
	TSaveDialog *savedlg;
	TRzToolButton *BtnExport1;
	TPopupMenu *pm;
	TMenuItem *N1;
	TDBGrid *dgdetail;
	TMenuItem *N4;
	TMenuItem *N5;
	TMenuItem *N6;
	TGroupBox *书目检索条件;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label1;
	TDateTimePicker *dtpbegin;
	TCheckBox *chbegin;
	TDateTimePicker *dtpend;
	TCheckBox *chend;
	TCheckBox *chpress;
	TEdit *edpress;
	TCheckBox *chbkinfo;
	TComboBox *cbpress;
	TEdit *edmin;
	TEdit *edmax;
	TCheckBox *chls;
	TEdit *edlsmin;
	TEdit *edlsmax;
	TCheckBox *chws;
	TEdit *edwsmin;
	TEdit *edwsmax;
	TComboBox *cbsupplier;
	TEdit *edsupplier;
	TCheckBox *chsupplier;
	TCheckBox *chbox2;
	TEdit *Edit1;
	TEdit *Edit2;
	TCheckBox *chmaysy;
	TRzToolButton *RzToolButton1;
	TADOCommand *cmdAddNote;
	TADOQuery *aq;
	TMenuItem *N2;
	TMenuItem *N3;
	TMenuItem *N7;
	TMenuItem *N8;
	TMenuItem *N9;
	TRadioButton *rb1;
	TRadioButton *rb2;
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall BtnExportClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall dtpbeginChange(TObject *Sender);
	void __fastcall dtpendChange(TObject *Sender);
	void __fastcall BtnExport1Click(TObject *Sender);
	void __fastcall edminChange(TObject *Sender);
	void __fastcall edlsminChange(TObject *Sender);
	void __fastcall edwsminChange(TObject *Sender);
	void __fastcall edpressKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall CheckBox1Click(TObject *Sender);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall edsupplierKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dgdetailDblClick(TObject *Sender);
	void __fastcall dgdetailTitleClick(TColumn *Column);
	void __fastcall N2Click(TObject *Sender);

	void __fastcall N3Click(TObject *Sender);
	void __fastcall N4Click(TObject *Sender);
	void __fastcall N5Click(TObject *Sender);
	void __fastcall N6Click(TObject *Sender);
	void __fastcall chmaysyClick(TObject *Sender);
	void __fastcall RzToolButton1Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall edsupplierChange(TObject *Sender);

private:	// User declarations
	int  supplierid ;
        	int supplieridaa;
public:		// User declarations
	__fastcall Tfrmretailbookup(TComponent* Owner,TADOConnection *con,int stgid);
	bool __fastcall DbgridToExcel(TDBGrid* dbg);
	int fstgid,fuserid,maxlen,sgfirsthid,sgheaderid ;
        TfrmProcureMng *pro;
	int modle;//1为订单，2为调拨
	AnsiString sqlwhere,sqltime,sqlws,sqlls,sqlstorage,ssbkid,sql ;
	TfrmBIorder *Ord;
	Tfrmdiaobo *Diaobo;
	//TfrmProcureMng *Pro;
	TStringList *strlist;
        AnsiString returncode,returncodeint;
        int AddCaigou();
        void createproc();
        void showsiyang();
        bool iscaigou;

  	void __fastcall dgdetailDrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol,
		  TColumn *Column, Grids::TGridDrawState State);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmretailbookup *frmretailbookup;
//---------------------------------------------------------------------------
#endif
