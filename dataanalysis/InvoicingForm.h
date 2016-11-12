//---------------------------------------------------------------------------

#ifndef InvoicingFormH
#define InvoicingFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "MDIChild.h"
#include "RzEdit.hpp"
#include "RzLabel.hpp"
#include <ComCtrls.hpp>
#include <Mask.hpp>
#include "RzButton.hpp"
#include "RzDBGrid.hpp"
#include "RzPanel.hpp"
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "DBGridEh.hpp"
#include "GridsEh.hpp"
#include <ImgList.hpp>
#include <Dialogs.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TfrmInvoicing : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TRzToolbar *rztlbr1;
	TRzToolButton *RzToolButton3;
	TRzToolButton *RzToolButton1;
	TADODataSet *dsquery;
	TDataSource *ds1;
	TADOCommand *querycom;
	TADOStoredProc *storcquery;
	TImageList *ImageList1;
	TRzToolButton *BtnAlignBottom;
	TRzToolButton *BtnExport;
	TSaveDialog *savedlg;
	TADOConnection *fcon;
	TDBGridEh *DBGridEh1;
	TGroupBox *GroupBox1;
	TCheckBox *chk6;
	TCheckBox *chk1;
	TCheckBox *chk4;
	TCheckBox *chk5;
	TDateTimePicker *dtp1;
	TDateTimePicker *dtp2;
	TComboBox *cbsupplier;
	TCheckBox *chtype;
	TCheckBox *cbstart;
	TCheckBox *cbend;
	TComboBox *cbpress;
	TCheckBox *chstorage;
	TComboBox *cbstorage;
	TCheckBox *ch1;
	TCheckBox *ch2;
	TCheckBox *ch3;
	TEdit *edsupplier;
	TEdit *edtype;
	TEdit *edpress;
	TEdit *edisbn;
	TEdit *edname;
	TCheckBox *chauthor;
	TCheckBox *chprice;
	TEdit *edprice;
	TEdit *edauthor;
	TSpeedButton *SpeedButton1;
	TEdit *edtyname;
	void __fastcall RzToolButton1Click(TObject *Sender);
	void __fastcall cbbTypeSelect(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall RzToolButton3Click(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall DBGridEh1TitleClick(TColumnEh *Column);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall ch1Click(TObject *Sender);
	void __fastcall ch2Click(TObject *Sender);
	void __fastcall ch3Click(TObject *Sender);
	void __fastcall BtnExportClick(TObject *Sender);
	void __fastcall edsupplierKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtypeKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edpressKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dtp1Change(TObject *Sender);
	void __fastcall dtp1KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dtp2Change(TObject *Sender);
	void __fastcall RzEdit5KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbsupplierChange(TObject *Sender);
	void __fastcall cbsupplierKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbpressChange(TObject *Sender);
	void __fastcall cbpressKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edisbnChange(TObject *Sender);
	void __fastcall ednameChange(TObject *Sender);
	void __fastcall edpriceChange(TObject *Sender);
	void __fastcall edauthorChange(TObject *Sender);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall edtynameChange(TObject *Sender);
private:	// User declarations
		TObject *Sender1;
		String storageformat,retaiformat,saleformat;
public:		// User declarations
	__fastcall TfrmInvoicing(TComponent* Owner);
	int stgid,TypeID;
	void  Init(TApplication* app, TADOConnection* con);
	bool DbgridToExcel(TDBGridEh* dbg);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmInvoicing *frmInvoicing;
//---------------------------------------------------------------------------
#endif
