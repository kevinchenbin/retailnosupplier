//---------------------------------------------------------------------------

#ifndef localadjustH
#define localadjustH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzDBGrid.hpp"
#include <ComCtrls.hpp>
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include "RzPanel.hpp"
#include <ImgList.hpp>
#include "RzButton.hpp"
#include <Menus.hpp>
#include "pdtypes.h"
#include "NoteCode.h"
#include "checkselbook.h"
#include <ADODB.hpp>
#include <DB.hpp>
#include "pdtypes.h"
#include "pdutil.h"
#include <DBCtrls.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class Tfrmadjust : public TForm
{
__published:	// IDE-managed Components
	TImageList *ImageList1;
	TRzToolbar *RzToolbar1;
	TRzToolButton *BtnNew;
	TRzToolButton *BtnPrint;
	TRzToolButton *BtnExit;
	TPopupMenu *pm;
	TMenuItem *N4;
	TMenuItem *N2;
	TMenuItem *N3;
	TMenuItem *ISBN1;
	TADOQuery *aquery;
	TADOStoredProc *adosp;
	TADOTable *atable;
	TDataSource *ds;
	TRzToolButton *BtnPreviewNextPage;
	TRzToolButton *BtnSave;
	TRzToolButton *BtnDelete;
	TADOQuery *aqueryupdate;
	TRzToolButton *BtnAlignBottom;
	TRzToolButton *BtnOK;
	TDataSource *dsheader;
	TADOQuery *aqheader;
	TRzToolButton *BtnView;
	TMenuItem *N1;
	TSaveDialog *savedlg;
	TRzDBGrid *dgbook;
	TGroupBox *GroupBox1;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label11;
	TLabel *lbsearch;
	TLabel *Label10;
	TLabel *Label3;
	TLabel *Label2;
	TLabel *Label12;
	TEdit *edtnum;
	TDateTimePicker *dtpdate;
	TEdit *edtcheckinfo;
	TComboBox *cblocalin;
	TEdit *edtnumber;
	TEdit *edtemploy;
	TEdit *edstate;
	TMemo *membk;
	TDBNavigator *DBNavigator1;
	TLabel *Label1;
	TLabel *labtitle;
	void __fastcall edtcheckinfoKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall N4Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall N3Click(TObject *Sender);
	void __fastcall ISBN1Click(TObject *Sender);
	void __fastcall BtnNewClick(TObject *Sender);
	void __fastcall BtnSaveClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall edtnumberKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall lbsearchMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall BtnDeleteClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall BtnOKClick(TObject *Sender);
	void __fastcall DBNavigator1Click(TObject *Sender, TNavigateBtn Button);
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall cblocalinKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cblocalinExit(TObject *Sender);
	void __fastcall dgbookCellClick(TColumn *Column);
	void __fastcall BtnPreviewNextPageClick(TObject *Sender);

private:	// User declarations
	TStringList *Store;
	TStringList *Local;
	String Code;
	int m_storageID;
	LandInfo checkli;
	int CatalogSearchMode;
	int m_local;
	AnsiString LockLocalID;    //被销售的库位ID列表
	void DisableInput(int Modal);
	TADOConnection *fcon;
public:		// User declarations
	__fastcall Tfrmadjust(TComponent* Owner,TADOConnection* con,LandInfo* li);
	void readyData(TADOQuery * aquery);
	void DelNtHeader();
	void ChangeCatalogSearchMode();
	void Refrsh();
	bool DbgridToExcel(TRzDBGrid* dbg);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmadjust *frmadjust;
//---------------------------------------------------------------------------
#endif
