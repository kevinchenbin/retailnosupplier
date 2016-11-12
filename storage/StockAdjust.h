//---------------------------------------------------------------------------

#ifndef StockAdjustH
#define StockAdjustH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <Mask.hpp>
#include <Menus.hpp>
#include "RzLabel.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include "pdtypes.h"
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ImgList.hpp>
#include <DBCtrls.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TfrmStockAdjust : public TForm
{
__published:	// IDE-managed Components
	TPopupMenu *PM;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TMenuItem *N6;
	TADOQuery *aqdetail;
	TImageList *ImageList1;
	TADOQuery *aq;
	TDataSource *ds;
	TADOQuery *aqhead;
	TDataSource *dshead;
	TSaveDialog *savedlg;
	TMenuItem *N4;
	TRzToolbar *RzToolbar1;
	TRzToolButton *BtnNew;
	TRzToolButton *BtnSave;
	TRzToolButton *BtnExit;
	TRzToolButton *BtnOK;
	TRzToolButton *BtnAlignBottom;
	TRzToolButton *BtnExport;
	TRzToolButton *BtnView;
	TRzToolButton *BtnDelete;
	TDBGrid *dg;
	TGroupBox *调整单信息;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label10;
	TLabel *Label6;
	TLabel *Label7;
	TRzLabel *lblCatalog;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label11;
	TEdit *editnum;
	TDateTimePicker *dtpdate;
	TEdit *editusername;
	TEdit *Edit1;
	TEdit *Edit2;
	TEdit *edstate;
	TDBNavigator *DBN;
	TEdit *edtCatalog;
	TEdit *editadjust;
	TEdit *editamount;
	TEdit *edsamount;
	TEdit *edbak;
	TMemo *membk;
	void __fastcall lblCatalogMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall N3Click(TObject *Sender);
	void __fastcall N6Click(TObject *Sender);
	void __fastcall edtCatalogKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnNewClick(TObject *Sender);
	void __fastcall dgCellClick(TColumn *Column);
	void __fastcall editadjustKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnOKClick(TObject *Sender);
	void __fastcall DBNClick(TObject *Sender, TNavigateBtn Button);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edsamountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edbakExit(TObject *Sender);
	void __fastcall edsamountClick(TObject *Sender);
	void __fastcall BtnExportClick(TObject *Sender);
	void __fastcall N4Click(TObject *Sender);
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall membkExit(TObject *Sender);
	void __fastcall BtnDeleteClick(TObject *Sender);
private:	// User declarations
	TADOConnection *fcon;
	int UserID,Stgid,username;
	int supplierID,catalogID;
public:		// User declarations
	__fastcall TfrmStockAdjust(TComponent* Owner);
	void AddNote(int supplierID,int CatalogId,int bkinfoid,int amount);
	int m_catalogSearchMode;
	void init(LandInfo *li);
	void ExecSQL(AnsiString sql);
	void RefreshDetail();
	bool DbgridToExcel(TDBGrid* dbg);
	void Deletenote();
	void ChangeCatalogSearchMode();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmStockAdjust *frmStockAdjust;
//---------------------------------------------------------------------------
#endif
