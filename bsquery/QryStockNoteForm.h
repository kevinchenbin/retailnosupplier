//---------------------------------------------------------------------------

#ifndef QryStockNoteFormH
#define QryStockNoteFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "MDIChild.h"
#include <ADODB.hpp>
#include <DB.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include "RzEdit.hpp"
#include "RzRadChk.hpp"
#include <Mask.hpp>
#include "RzDBCmbo.hpp"
#include "RzLine.hpp"
#include <DBCtrls.hpp>
#include "RzTabs.hpp"
#include "RzDBGrid.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include "RzCmboBx.hpp"
#include <Buttons.hpp>
#include <ImgList.hpp>
#include <Dialogs.hpp>
#include "DBGridEh.hpp"
#include "GridsEh.hpp"
#include "RzDTP.hpp"
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmQryCheckNote : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TRzToolbar *rztlbr1;
	TRzToolButton *tlbtnQry;
	TRzToolButton *tlbtnExport;
	TRzToolButton *tlbtnExit;
	TADODataSet *dsetByNtHeader;
	TDataSource *dsrcByNtHeader;
	TADODataSet *dsetByNote;
	TDataSource *dsrcByNote;
	TADODataSet *dsetByCustomer;
	TDataSource *dsrcByCustomer;
	TADODataSet *dsetByBktype;
	TDataSource *dsrcByBktype;
	TDataSource *dsrcByPress;
	TADOStoredProc *spQryNote;
	TADODataSet *dsetCustomer;
	TDataSource *dsrcCustomer;
	TDataSource *dsrcPress;
	TADODataSet *dsetBookType;
	TDataSource *dsrcBookType;
	TDataSource *dsrcStorage;
	TADODataSet *dsetStorage;
	TDataSource *dsrcBookstack;
	TADODataSet *dsetBookstack;

	TADOQuery *qryItems;
	TImageList *ImageList1;
	TADODataSet *dsetPress;
	TADODataSet *dsetByPress;
	TRzToolButton *BtnAlignBottom;
	TSaveDialog *savedlg;
	TRzGroupBox *grpbx1;
	TLabel *lbl1;
	TLabel *lbl2;
	TLabel *lbl3;
	TLabel *lbl4;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label10;
	TRzCheckBox *chckbxStartTime;
	TRzCheckBox *chckbxEndTime;
	TRzCheckBox *chckbxBookName;
	TRzCheckBox *chckbxISBN;
	TRzCheckBox *chckbxCustomer;
	TRzCheckBox *chckbxBkstack;
	TRzCheckBox *chckbxUserDefNum;
	TRzCheckBox *chckbxPrice;
	TRzCheckBox *chckbxAuthor;
	TRzCheckBox *chckbxAmount;
	TRzCheckBox *chckbxPress;
	TRzCheckBox *chckbxType;
	TRzCheckBox *chckbxRemarks;
	TRzCheckBox *chckbxStorage;
	TRzEdit *edtBookName;
	TRzEdit *edtISBN;
	TRzEdit *edtUserDefNum;
	TRzEdit *edtAuthor;
	TRzEdit *edtPress;
	TRzEdit *edtRemarks;
	TRzEdit *edtCustomer;
	TRzNumericEdit *numedtMinPrice;
	TRzNumericEdit *numedtMinAmount;
	TRzNumericEdit *numedtMaxPrice;
	TRzNumericEdit *numedtMaxAmount;
	TRzDBLookupComboBox *dblkpcbbPress;
	TRzDBLookupComboBox *dblkpcbbCustomer;
	TRzDBLookupComboBox *dblkpcbbStorage;
	TRzDBLookupComboBox *dblkpcbbBookstack;
	TCheckBox *chstaff;
	TComboBox *cbstaff;
	TCheckBox *cbdamage;
	TRzNumericEdit *minnu;
	TRzNumericEdit *maxnu;
	TCheckBox *chchayi;
	TCheckBox *chyingkui;
	TRzNumericEdit *numykmax;
	TRzNumericEdit *numykmin;
	TRadioGroup *rgtype;
	TRzCheckBox *chdanhao;
	TRzEdit *eddanhao;
	TRzPageControl *pgcntrlResult;
	TRzTabSheet *tbshtByNtHeader;
	TDBGridEh *dbgrdByNtHeader;
	TRzTabSheet *tbshtByNote;
	TDBGridEh *dbgrdByNote;
	TRzTabSheet *tbshtByBktype;
	TDBGridEh *dbgrdByBktype;
	TRzTabSheet *tbshtByPress;
	TDBGridEh *dbgrdByPress;
	TSpeedButton *SpeedButton1;
	TEdit *edtyname;
	TEdit *edpyquery;
	TDateTimePicker *dtedtStart;
	TDateTimePicker *dtedtEnd;
	void __fastcall tlbtnQryClick(TObject *Sender);
	void __fastcall chckbxBkstackClick(TObject *Sender);
	void __fastcall tlbtnExportClick(TObject *Sender);
	void __fastcall tlbtnExitClick(TObject *Sender);
	void __fastcall edtPressKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall edtBookNameChange(TObject *Sender);
	void __fastcall edtUserDefNumChange(TObject *Sender);
	void __fastcall edtISBNChange(TObject *Sender);
	void __fastcall numedtMinPriceChange(TObject *Sender);
	void __fastcall numedtMaxPriceChange(TObject *Sender);
	void __fastcall numedtMinAmountChange(TObject *Sender);
	void __fastcall numedtMaxAmountChange(TObject *Sender);
	void __fastcall edtAuthorChange(TObject *Sender);
	void __fastcall edtRemarksChange(TObject *Sender);
	void __fastcall dblkpcbbPressClick(TObject *Sender);
	void __fastcall dblkpcbbBookstackClick(TObject *Sender);
	void __fastcall dblkpcbbStorageClick(TObject *Sender);
	void __fastcall dblkpcbbCustomerClick(TObject *Sender);
	void __fastcall dbgrdByNtHeader1TitleClick(TColumn *Column);
	void __fastcall dbgrdByCustomerTitleClick(TColumn *Column);
	void __fastcall cbstaffClick(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall dbgrdByNtHeaderDblClick(TObject *Sender);
	void __fastcall dbgrdByNtHeaderTitleClick(TColumnEh *Column);
	void __fastcall dbgrdByNoteTitleClick(TColumnEh *Column);
	void __fastcall dbgrdByBktypeTitleClick(TColumnEh *Column);
	void __fastcall dbgrdByPressTitleClick(TColumnEh *Column);
	void __fastcall eddanhaoChange(TObject *Sender);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall edpyqueryKeyPress(TObject *Sender, wchar_t &Key);

private:	// User declarations
	void Query();
	String QueryDesic();
	String Desic,Desic1;
public:		// User declarations
	__fastcall TfrmQryCheckNote(TComponent* Owner);
	bool __fastcall DbgridToExcel(TDBGridEh* dbg);
	virtual void Init(LandInfo* li);

	TADOConnection *fcon;
	int TypeID;
        bool qfsupplier;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmQryCheckNote *frmQryCheckNote;
//---------------------------------------------------------------------------
#endif
