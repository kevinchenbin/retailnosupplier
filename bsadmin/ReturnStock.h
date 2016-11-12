//---------------------------------------------------------------------------

#ifndef ReturnStockH
#define ReturnStockH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "RzButton.hpp"
#include "RzDBCmbo.hpp"
#include "RzEdit.hpp"
#include "RzPanel.hpp"
#include "RzRadChk.hpp"
#include <DBCtrls.hpp>
#include <Mask.hpp>
#include <ImgList.hpp>
#include "DBGridEh.hpp"
#include "GridsEh.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include <ComCtrls.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <Menus.hpp>
#include <FMTBcd.hpp>
#include <SqlExpr.hpp>
#include "MDIChild.h"
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TfrmReturnStock : public TForm
{
__published:	// IDE-managed Components
	TImageList *ImageList1;
	TDataSource *dssupplier;
	TADOQuery *aqsupplier;
	TDataSource *dspress;
	TADOQuery *aqpress;
	TADOConnection *fcon;
	TDataSource *ds;
	TADOQuery *query;
	TPopupMenu *PopupMenu1;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TADOQuery *querybk;
	TADOStoredProc *stops;
	TADOStoredProc *stotk;
	TRzToolbar *RzToolbar1;
	TRzToolButton *BtnView;
	TRzToolButton *BtnFastForward;
	TRzToolButton *BtnExit;
	TRzToolButton *BtnLastRecord;
	TRzToolButton *BtnAlignBottom;
	TRzToolButton *RzToolButton1;
	TSaveDialog *savedlg;
	TMenuItem *N4;
	TMenuItem *N5;
	TDBGrid *DBGrid1;
	TPageControl *pc;
	TTabSheet *Tab1;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TDateTimePicker *dtpstart;
	TDateTimePicker *dtpend;
	TRzCheckBox *chrktime;
	TEdit *edbook;
	TComboBox *cbtype1;
	TComboBox *cbsupplier;
	TComboBox *cbstate1;
	TComboBox *cbstorage1;
	TCheckBox *chstorage;
	TCheckBox *chisbn;
	TEdit *edname;
	TCheckBox *chname;
	TCheckBox *chtype;
	TCheckBox *chstate1;
	TCheckBox *chsupplier;
	TEdit *edsupplier;
	TDateTimePicker *dtpls1;
	TDateTimePicker *dtpls2;
	TRzCheckBox *chlstime;
	TDateTimePicker *dtp3;
	TDateTimePicker *dtp4;
	TRzCheckBox *chwstime;
	TRzCheckBox *chlsnum;
	TEdit *edlsnum;
	TRzCheckBox *chwsnum;
	TEdit *edwsnum;
	TTabSheet *Tab2;
	TLabel *Label2;
	TLabel *Label1;
	TLabel *Label3;
	TRzCheckBox *chckbxSupplier;
	TRzCheckBox *chckbxAmount;
	TRzCheckBox *chckbxPressCount;
	TRzCheckBox *chckbxType;
	TRzCheckBox *chckbxShopNum;
	TRzEdit *edtSupplier1;
	TRzEdit *edtPressCount1;
	TRzDBLookupComboBox *edtSupplier2;
	TRzDBLookupComboBox *edtPress2;
	TEdit *edtAmountLow;
	TCheckBox *chbackdate;
	TDateTimePicker *dtp1;
	TDateTimePicker *dtp2;
	TEdit *edtAmountHigh;
	TRzCheckBox *chstate;
	TComboBox *cbstate2;
	TComboBox *cbstorage;
	TComboBox *cbtype;
	TDateTimePicker *dtprk1;
	TDateTimePicker *dtprk2;
	TRzCheckBox *chrk;
	TDateTimePicker *dtpjiezhi;
	TRzCheckBox *cbjiezhi;
	TRzCheckBox *cbtuihuo;
	TRzEdit *edittianshu;
	TLabel *Label4;
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall dtp2Change(TObject *Sender);
	void __fastcall dtp1Change(TObject *Sender);
	void __fastcall edtAmountLowChange(TObject *Sender);
	void __fastcall edtSupplier2Click(TObject *Sender);
	void __fastcall edtPress2Click(TObject *Sender);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);

	void __fastcall N3Click(TObject *Sender);
	void __fastcall BtnFastForwardClick(TObject *Sender);
	void __fastcall BtnLastRecordClick(TObject *Sender);
	void __fastcall cbstate2Change(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall DBGrid1TitleClick(TColumn *Column);
	void __fastcall cbtypeChange(TObject *Sender);
	void __fastcall RzToolButton1Click(TObject *Sender);
	void __fastcall edtSupplier1KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtPressCount1KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dtpstartChange(TObject *Sender);
	void __fastcall dtpls1Change(TObject *Sender);
	void __fastcall dtp3Change(TObject *Sender);
	void __fastcall edbookChange(TObject *Sender);
	void __fastcall ednameChange(TObject *Sender);
	void __fastcall cbstate1Change(TObject *Sender);
	void __fastcall edlsnumChange(TObject *Sender);
	void __fastcall edwsnumChange(TObject *Sender);
	void __fastcall cbtype1Change(TObject *Sender);
	void __fastcall cbsupplierChange(TObject *Sender);
	void __fastcall edsupplierKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall N4Click(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edtAmountHighKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtAmountLowKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall pcChange(TObject *Sender);
	void __fastcall N6Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmReturnStock(TComponent* Owner,TADOConnection *con,int userid,int stgid);
	int fstgid,fuserid;
	LandInfo linfo;
	AnsiString sqlstorage,returncode;
	bool DbgridToExcel(TDBGrid* dbg);
		void __fastcall DBGrid1DrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol,
          TColumn *Column, Grids::TGridDrawState State);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmReturnStock *frmReturnStock;
//---------------------------------------------------------------------------
#endif
