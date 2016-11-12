//---------------------------------------------------------------------------

#ifndef UnitBIOrderH
#define UnitBIOrderH
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
#include <DBCtrls.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <Mask.hpp>
#include <Buttons.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "pdtypes.h"
#include "RzLabel.hpp"
#include <Menus.hpp>
#include "RzDBEdit.hpp"
#include "RzEdit.hpp"
#include "RzDBGrid.hpp"
#include <Dialogs.hpp>
#include <Graphics.hpp>
#include "MDIChild.h"
//---------------------------------------------------------------------------

class TfrmBIorder : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TImageList *ImageList1;
	TRzToolbar *RzToolbar1;
	TRzToolButton *BtnNew;
	TRzToolButton *BtnDelete;
	TRzToolButton *BtnChangeOptions;
	TRzToolButton *BtnImport;
	TRzToolButton *BtnExport;
	TRzToolButton *BtnExit;
	TRzToolButton *BtnPrint;
	TRzToolButton *BtnClear;
	TRzToolButton *BtnOK;
	TADOQuery *aqupdatehead;
	TADOStoredProc *adospaddhead;
	TDataSource *dshead;
	TPopupMenu *pm;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TMenuItem *N4;
	TADOQuery *aqorderdetail;
	TDataSource *dsdetail;
	TRzToolButton *BtnView;
	TDataSource *dshd;
	TADOQuery *aqhd;
	TRzToolButton *BtnAlignBottom;
	TPopupMenu *pm1;
	TMenuItem *N5;
	TRzToolButton *BtnView1;
	TADOQuery *query;
	TMenuItem *N6;
	TMenuItem *N7;
	TMenuItem *N8;
	TRzToolButton *BtnOK1;
	TMenuItem *N9;
	TMenuItem *N10;
	TSaveDialog *savedlg;
	TMenuItem *N11;
	TMenuItem *N12;
	TADOQuery *querypress;
	TADOStoredProc *adospcopy;
	TADOQuery *aquery;
	TRzToolButton *BtnProperties;
	TMenuItem *N13;
	TRzToolButton *BtnCancel;
	TRzToolButton *BtnFinish;
	TMenuItem *N14;
	TRzToolButton *BtnLastRecord;
	TDBGrid *dgdetail;
	TRzStatusBar *RzStatusBar1;
	TLabel *Label16;
	TLabel *Label18;
	TLabel *Label19;
	TLabel *Label22;
	TLabel *Label23;
	TRzLabel *lbl11;
	TRzLabel *lblOpName;
	TRzDBNumericEdit *RzDBNumericEdit1;
	TRzDBNumericEdit *RzDBNumericEdit2;
	TRzDBNumericEdit *RzDBNumericEdit3;
	TRzDBNumericEdit *RzDBNumericEdit4;
	TEdit *edpress;
	TGroupBox *GroupBox1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *label5;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label15;
	TSpeedButton *SpeedButton2;
	TComboBox *cbvendor;
	TDateTimePicker *dtpdate;
	TDBEdit *dbeditdanhao;
	TDateTimePicker *dtpfahuo;
	TDBEdit *dbeditaddcost;
	TComboBox *cbstate;
	TComboBox *cbtype;
	TComboBox *cbclient;
	TEdit *edclient;
	TMemo *membk;
	TGroupBox *GroupBox2;
	TLabel *Label11;
	TLabel *Label12;
	TLabel *Label13;
	TRzLabel *lblCatalog;
	TLabel *Label10;
	TLabel *Label20;
	TSpeedButton *spnewbook;
	TSpeedButton *SpeedButton3;
	TEdit *edtCatalog;
	TEdit *editamount;
	TEdit *editdiscount;
	TEdit *Edit1;
	TEdit *editdetailbk;
	TGroupBox *GroupBox3;
	TCheckBox *chfsluru;
	TCheckBox *chfsamount;
	TCheckBox *chfsdiscount;
	TCheckBox *chfoceset;
	TSpeedButton *SpeedButton1;
	TLabel *Label1;
	TDBNavigator *dbn;
	TLabel *labtitle;
	TMenuItem *N15;
	TMenuItem *N16;
	TMenuItem *N17;
	TRichEdit *Richcopy;
	TRzToolButton *toolshowmainmenu;
	void __fastcall BtnNewClick(TObject *Sender);
	void __fastcall BtnOKClick(TObject *Sender);
	void __fastcall dbnClick(TObject *Sender, TNavigateBtn Button);
	void __fastcall lblCatalogMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall N3Click(TObject *Sender);
	void __fastcall N4Click(TObject *Sender);
	void __fastcall edtCatalogKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editamountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editdiscountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editdetailbkKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnDeleteClick(TObject *Sender);
	void __fastcall BtnChangeOptionsClick(TObject *Sender);
	void __fastcall SpeedButton2Click(TObject *Sender);
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall BtnClearClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall edclientKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbclientKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dgdetail1CellClick(TColumn *Column);
	void __fastcall BtnPrintClick(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall N5Click(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall cbclientClick(TObject *Sender);
	void __fastcall BtnView1Click(TObject *Sender);
	void __fastcall dbeditaddcostKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall spnewbookClick(TObject *Sender);
	void __fastcall BtnImportClick(TObject *Sender);
	void __fastcall edtclientKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dgdetail1DblClick(TObject *Sender);
	void __fastcall N6Click(TObject *Sender);
	void __fastcall N7Click(TObject *Sender);
	void __fastcall N8Click(TObject *Sender);
	void __fastcall BtnOK1Click(TObject *Sender);

	void __fastcall dgdetailCellClick(TColumn *Column);
	void __fastcall dgdetailDblClick(TObject *Sender);

	void __fastcall N12Click(TObject *Sender);
	void __fastcall BtnPropertiesClick(TObject *Sender);
	void __fastcall dgdetailTitleClick(TColumn *Column);
	void __fastcall membkKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall SpeedButton3Click(TObject *Sender);
	void __fastcall N13Click(TObject *Sender);
	void __fastcall chfsluruClick(TObject *Sender);
	void __fastcall BtnCancelClick(TObject *Sender);
	void __fastcall cbtypeChange(TObject *Sender);
	void __fastcall BtnFinishClick(TObject *Sender);
	void __fastcall N14Click(TObject *Sender);
	void __fastcall BtnLastRecordClick(TObject *Sender);
	void __fastcall aqorderdetailBeforeScroll(TDataSet *DataSet);
	void __fastcall dsdetailDataChange(TObject *Sender, TField *Field);
	void __fastcall BtnExportClick(TObject *Sender);
	void __fastcall N16Click(TObject *Sender);
	void __fastcall N17Click(TObject *Sender);
	void __fastcall toolshowmainmenuClick(TObject *Sender);
private:	// User declarations
	TADOConnection *fcon;
	int UserID;
	AnsiString UserName;
	int StgID;
	AnsiString Danhao,logmessage;
	int ClientID;
	int m_catalogSearchMode;
	int HeaderRec;
public:		// User declarations
	__fastcall TfrmBIorder(TComponent* Owner);

	void __fastcall dgdetail1DrawColumnCell(TObject *Sender, const TRect &Rect,
		  int DataCol, TColumn *Column, Grids::TGridDrawState State);

        bool DbgridToExcel(TDBGrid* dbg);
	void init(LandInfo* li);
	void init(LandInfo*li,AnsiString Danhao);
	void ReadyDate();
	void AddNewHead();
	AnsiString GetField(AnsiString sql,AnsiString Field);
	void ExecSQL(AnsiString sql);
	BOOL UpdateHead();
	void RefreshHead();
	void AddNote(int SupplierID,int CatalogID);
	void RefreshDetail();
	void BatchSetNotes(int amount, float discount, int mode);

	void ChangeCatalogSearchMode();
	void edclientview();
	void RefreshHead(int headerid);
	void RefreshHead(AnsiString headerCode);//采购时调用的
	void DelInvalidNtHeader();
	void DelNtHeader();
	bool chongfutishi(int catalogid);
	int headid,type;
	bool lastdiscount,ordertishi,orderfind,orderchange,orderviewclass;
	AnsiString month,printtitle,contact,tel,address,printbk;
	bool Master;
	int scroll;
        bool qfclietn;

};
//---------------------------------------------------------------------------
extern PACKAGE TfrmBIorder *frmBIorder;
//---------------------------------------------------------------------------
#endif
