//---------------------------------------------------------------------------

#ifndef stackqueryH
#define stackqueryH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "MDIChild.h"
#include "RzLabel.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include "RzButton.hpp"
#include "RzRadChk.hpp"
#include "RzDBEdit.hpp"
#include "RzDBGrid.hpp"
#include "RzEdit.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <Mask.hpp>
#include "RzDBDTP.hpp"
#include "RzDTP.hpp"
#include <ComCtrls.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "RzDBCmbo.hpp"
#include <DBCtrls.hpp>
#include <ImgList.hpp>


#include "DBGridEh.hpp"
#include "GridsEh.hpp"
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class Tfrmstackquery : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TRzToolbar *rztlbr1;
	TRzToolButton *btnExit1;
	TRzToolButton *btnExit2;
	TRzToolButton *btnExit3;
	TRzToolButton *btnExit4;
	TRzGroupBox *rzgrpbx4;
	TRzCheckBox *chckbxBookName;
	TRzCheckBox *chckbxISBN;
	TRzCheckBox *chckbxSupplier;
	TRzCheckBox *chckbxUserDefNum;
	TRzCheckBox *chckbxPrice;
	TRzCheckBox *chckbxAuthor;
	TRzCheckBox *chckbxPressCount;
	TRzCheckBox *chckbxType;
	TRzCheckBox *chckbxShopNum;
	TRzEdit *edtBookName;
	TRzEdit *edtISBN;
	TRzEdit *edtSupplier1;
	TRzEdit *edtUserDefNum;
	TRzEdit *edtPrice;
	TRzEdit *edtAuthor;
	TRzEdit *edtPressCount1;
	TRzEdit *edtShopNum;
	TADOQuery *qry1;
	TDataSource *ds1;
	TADOTable *tbl2supplier;
	TADOTable *tbl1supplier;
	TDataSource *ds2supplier;
	TDataSource *ds3supplier;
	TRzDBLookupComboBox *edtSupplier;
	TADODataSet *dsetCatlog;
	TADOTable *tblPress;
	TADOTable *tblCatalogType;
	TDataSource *dsrcPress;
	TDataSource *dsCatlog;
	TDataSource *dsrcCatalogType;
	TADOQuery *aquery;
	TADOTable *tblStore;
	TDataSource *dsstore;
	TRzDBLookupComboBox *edtstore;
	TRzCheckBox *rzlocal;
	TADOTable *tbllocal;
	TDataSource *dslocal;
	TRzDBLookupComboBox *edtlocal;
	TImageList *ImageList1;
	TDBGridEh *DBGridEh1;
	TRzToolButton *BtnAlignBottom;
	TRzDBLookupComboBox *edtPressCount;
	TRzDBLookupComboBox *edtType;
	TADOQuery *aq1supplier;
	TADOQuery *aqpress;
	TSaveDialog *savedlg;
	TRzCheckBox *chckbxStartTime;
	TRzDateTimeEdit *dtedtStart;
	TRzCheckBox *chckbxEndTime;
	TRzDateTimeEdit *dtedtEnd;
	TCheckBox *chstaff;
	TComboBox *cbstaff;
	TRzDBLookupComboBox *edintlocal;
	TRzCheckBox *chinlocal;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall btnExit4Click(TObject *Sender);
	void __fastcall btnExit1Click(TObject *Sender);
	void __fastcall edtISBNKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall btnExit2Click(TObject *Sender);
	void __fastcall edtBookNameChange(TObject *Sender);
	void __fastcall edtPriceChange(TObject *Sender);
	void __fastcall edtPressCountClick(TObject *Sender);
	void __fastcall edtstoreClick(TObject *Sender);
	void __fastcall edtISBNChange(TObject *Sender);
	void __fastcall edtAuthorChange(TObject *Sender);
	void __fastcall edtlocalClick(TObject *Sender);
	void __fastcall edtSupplierClick(TObject *Sender);
	void __fastcall edtTypeClick(TObject *Sender);
	void __fastcall edtUserDefNumChange(TObject *Sender);
	void __fastcall DBGridEh1TitleClick(TColumnEh *Column);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edtSupplier1KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtPressCount1KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtPriceKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbstaffChange(TObject *Sender);
	void __fastcall edintlocalClick(TObject *Sender);

private:	// User declarations
	String m_sql;
public:		// User declarations
	__fastcall Tfrmstackquery(TComponent* Owner);
	void Init(LandInfo* li);
	String QueryCom();
	void Query();
	String QueryDesic();
	String Desic;
   //	void  RPGrid(TRzDBGrid *dg,TQRPGrid *PRdg );
	bool __fastcall DbgridToExcel(TDBGridEh* dbg);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmstackquery *frmstackquery;
//---------------------------------------------------------------------------
#endif
