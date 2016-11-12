//---------------------------------------------------------------------------

#ifndef WholesaleMngReturnFormH
#define WholesaleMngReturnFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "MDIChild.h"
#include "RzButton.hpp"
#include "RzDBCmbo.hpp"
#include "RzDBEdit.hpp"
#include "RzEdit.hpp"
#include "RzLabel.hpp"
#include "RzPanel.hpp"
#include <Buttons.hpp>
#include <DBCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Mask.hpp>
#include <Menus.hpp>
#include "RzDBGrid.hpp"
#include "RzDBLbl.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <DBAdapt.hpp>
#include <WebAdapt.hpp>
#include <WebComp.hpp>
#include <FMTBcd.hpp>
#include <SqlExpr.hpp>
#include "RzCommon.hpp"
#include "RzDBLook.hpp"
#include "RzRadGrp.hpp"
#include "pdutil.h"
#include "RzRadChk.hpp"
#include <ImgList.hpp>
#include "bsadmin.h"
#include "bsprint.h"
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <Graphics.hpp>
#include "RzDBDTP.hpp"
#include "RzDTP.hpp"

//---------------------------------------------------------------------------
class TfrmWholesaleReturnMng : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TRzToolbar *rztlbr1;
	TRzToolButton *RzToolButton1;
	TPopupMenu *pm1;
	TMenuItem *mniBsNote;
	TMenuItem *mniBsNoteSendback;
	TRzStatusBar *RzStatusBar1;
	TRzLabel *lbl11;
	TRzLabel *lbl12;
	TRzLabel *lbl13;
	TRzLabel *lbl14;
	TRzDBNumericEdit *dbnbedt2;
	TRzDBNumericEdit *dbnbedt3;
	TRzDBNumericEdit *dbnbedt4;
	TDataSource *dsrcNtHeader;
	TADODataSet *dsetNtHeader;
	TDataSource *dsrcNote;
	TADODataSet *dsetNote;
	TADODataSet *dsetVendor;
	TDataSource *dsrcVendor;
	TDataSource *dsrcStaff;
	TADODataSet *dsetStaff;
	TADODataSet *dsetBkstack;
	TDataSource *dsrcBkstack;
	TRzDBLookupDialog *dblkpdlgVendor;
	TADODataSet *dsetLkpVendor;
	TADOCommand *cmdUpdateNtHeader;
	TADOStoredProc *spQryNtHeader;
	TADOStoredProc *spQryNtHeader1;
	TADOCommand *cmdDelNtHeader;
	TADOCommand *cmdAddNote;
	TADOCommand *cmdUpdateNote;
	TADOCommand *cmdDelNote;
	TADOCommand *cmdBatchUpdateNote;
	TADOCommand *cmdBatchDelNote;
	TRzToolButton *tlbtn1;
	TRzToolButton *tlbtnAddNote;
	TRzToolButton *tlbtn2;
	TRzToolButton *tlbtn3;
	TRzToolButton *RzToolButton2;
	TRzToolButton *tlbtn4;
	TRzToolButton *tlbtn5;
	TRzToolButton *tlbtn7;
	TADOCommand *cmdAddNtHeader;
	TRzLabel *lblOpName;
	TADOCommand *cmdResetNtHeader;
	TImageList *ImageList1;
	TPopupMenu *pm;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TPopupMenu *PopupMenu1;
	TMenuItem *N11;
	TMenuItem *N21;
	TRzToolButton *BtnClear;
	TPopupMenu *PopupMenu2;
	TMenuItem *N12;
	TMenuItem *N22;
	TADODataSet *bearsaledataset;
	TMenuItem *N4;
	TADOQuery *query;
	TPopupMenu *selectmenu;
	TMenuItem *N5;
	TMenuItem *N6;
	TDataSource *dsrcrecord;
	TADOQuery *qryrecord;
	TRzToolButton *BtnNew;
	TMenuItem *N7;
	TMenuItem *N8;
	TMenuItem *N9;
	TRzToolButton *BtnView;
	TRzToolButton *BtnSave;
	TADOStoredProc *spsave;
	TDataSource *DBSource;
	TADOQuery *querydan;
	TGroupBox *grpbxNtHeader;
	TRzLabel *lbl1;
	TRzLabel *lbl2;
	TRzLabel *lbl3;
	TRzLabel *lbl4;
	TRzLabel *lbl7;
	TSpeedButton *RzButton1;
	TRzEdit *edtQryVendor;
	TRzDBEdit *dbedtWsaleNtCode;
	TRzDBLookupComboBox *dblkpcbbVendorID;
	TRzDBNumericEdit *dbnbedtAddCosts;
	TDBNavigator *DBNav;
	TGroupBox *grpbxNote;
	TLabel *Label1;
	TRzLabel *lbl5;
	TRzLabel *lbl8;
	TRzLabel *lbl9;
	TRzLabel *lblCatalog;
	TLabel *Label5;
	TRzDBNumericEdit *dbnbedtTotalAmount;
	TRzEdit *edtCatalog;
	TEdit *editprice;
	TRzDBGrid *dbgrdNote;
	TRzDBGrid *dgrecord;
	TEdit *editdanhao;
	TLabel *Label10;
	TRzToolButton *BtnAlignBottom;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TEdit *editlv1;
	TEdit *editallyear;
	TADOStoredProc *sptuihuo1;
	TSaveDialog *savedlg;
	TPopupMenu *pmprint;
	TMenuItem *N10;
	TMenuItem *N13;
	TADOStoredProc *adospcopy;
	TADOStoredProc *spcopy;
	TImage *Image1;
	TMemo *membk;
	TGroupBox *GroupBox1;
	TCheckBox *chfoceset;
	TCheckBox *chfsluru;
	TCheckBox *chfsamount;
	TCheckBox *chfsdiscount;
	TSpeedButton *SpeedButton1;
	TMenuItem *N14;
	TPopupMenu *pmpreview;
	TMenuItem *N15;
	TADODataSet *dtGetTotal;
	TDataSource *dsGetTotal;
	TDataSource *dsstkamount;
	TADODataSet *dsetstkamount;
	TRzDBNumericEdit *fahuototal;
	TRzDBNumericEdit *tuihuototal;
	TRzNumericEdit *dbnbedtAmount;
	TRzNumericEdit *dbnbedtDiscount;
	TCheckBox *CheckBox1;
	TADOCommand *cmdUpdataamount;
	TRzDBNumericEdit *edtotalamount;
	TRzLabel *RzLabel1;
	TEdit *edcredit;
	TEdit *ednocheck;
	TLabel *Label2;
	TLabel *labtitle;
	TLabel *Label3;
	TLabel *Label4;
	TEdit *edchecked;
	TEdit *edbond;
	TRzLabel *RzLabel2;
	TRzLabel *RzLabel3;
	TDateTimePicker *dbdtedtHdTime;
	TComboBox *dblkpcbbStaffID;
	TRzToolButton *RzToolButton3;
	TPopupMenu *PopupMenu3;
	TMenuItem *A41;
	TMenuItem *N21A41;
	TPopupMenu *PopupMenu4;
	TMenuItem *A42;
	TMenuItem *N21A42;
	TPopupMenu *PopupMenu5;
	TMenuItem *A43;
	TMenuItem *N21A43;
	TRzToolButton *muilprintbutton;
	TLabel *Label6;
	TRzNumericEdit *totalyingshou;
	TMenuItem *N16;
	TMenuItem *N17;
	TMenuItem *N18;
	TRzToolButton *RzToolButton4;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall tlbtn1Click(TObject *Sender);
	void __fastcall tlbtn7Click(TObject *Sender);
	void __fastcall edtQryVendorKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtCatalogKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall mniBsNoteSendbackClick(TObject *Sender);
	void __fastcall tlbtn4Click(TObject *Sender);
	void __fastcall dblkpcbbBkstackIDKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dblkpcbbStaffIDExit(TObject *Sender);
	void __fastcall dbnbedtAmountExit(TObject *Sender);
	void __fastcall tlbtn5Click(TObject *Sender);
	void __fastcall dsetNoteAfterScroll(TDataSet *DataSet);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall N3Click(TObject *Sender);
	void __fastcall lblCatalogMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall N11Click(TObject *Sender);
	void __fastcall N21Click(TObject *Sender);
	void __fastcall BtnClearClick(TObject *Sender);
	void __fastcall N22Click(TObject *Sender);
	void __fastcall N12Click(TObject *Sender);
	void __fastcall dbnbedtDiscountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall N4Click(TObject *Sender);
	void __fastcall dbnbedtTotalAmountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall N6Click(TObject *Sender);
	void __fastcall dbgrdNoteCellClick(TColumn *Column);
	void __fastcall BtnNewClick(TObject *Sender);
	void __fastcall cbbkstackIDKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbbkstackIDExit(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall tlbtnAddNoteClick(TObject *Sender);
	void __fastcall dbgrdNoteMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall N8Click(TObject *Sender);
	void __fastcall N9Click(TObject *Sender);
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall cbclientExit(TObject *Sender);
	void __fastcall BtnSaveClick(TObject *Sender);
	void __fastcall cbclientDropDown(TObject *Sender);
	void __fastcall dbnbedtAddCostsExit(TObject *Sender);
	void __fastcall dbnbedtAddCostsKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall DBNavClick(TObject *Sender, TNavigateBtn Button);
	void __fastcall RzButton1Click(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall dbgrdNoteTitleClick(TColumn *Column);
	void __fastcall N10Click(TObject *Sender);
	void __fastcall N13Click(TObject *Sender);
	void __fastcall membkKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall N14Click(TObject *Sender);
	void __fastcall chfsluruClick(TObject *Sender);
	void __fastcall editpriceKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall N15Click(TObject *Sender);
	void __fastcall dbnbedtAmountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dblkpcbbVendorIDKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dblkpcbbVendorIDClick(TObject *Sender);
	void __fastcall dbnbedtDiscountExit(TObject *Sender);
	void __fastcall CheckBox1Click(TObject *Sender);
	void __fastcall dsrcNoteDataChange(TObject *Sender, TField *Field);
	void __fastcall dsetNoteBeforeScroll(TDataSet *DataSet);
	void __fastcall rztlbr1Click(TObject *Sender);
	void __fastcall RzToolButton3Click(TObject *Sender);
	void __fastcall A41Click(TObject *Sender);
	void __fastcall N21A41Click(TObject *Sender);
	void __fastcall A42Click(TObject *Sender);
	void __fastcall N21A42Click(TObject *Sender);
	void __fastcall A43Click(TObject *Sender);
	void __fastcall N21A43Click(TObject *Sender);
	void __fastcall N16Click(TObject *Sender);
	void __fastcall N17Click(TObject *Sender);
	void __fastcall N18Click(TObject *Sender);
	void __fastcall RzToolButton4Click(TObject *Sender);


private:	// User declarations
	typedef enum
	{
		OPUnknown = 0,
		OPFind = 1,
		OPAddNtHeader,
		OPDelNtHeader,
		OPAddNote,
		OPDelNote,
		OPSetNotes,
		OPRecCash
	}OPMode;
	int m_supplierID;
	int m_catalogSearchMode;//1为书号 2为自编码 3为书名
	OPMode m_opmode;//1为查单模式 2为添加单头模式 3为删除单头模式 4为添加单模式 5为删除单模式 6为统一模式 7为现场收款模式
	BSMode m_bsmode;//1为批销单模式 2为退货单模式
	void ChangeCatalogSearchMode();
	//void ChangeBsmode(BSMode bsmode);
	void ChangeOpmode(OPMode opmode);
	void AddNtHeader();//添加单头
	void QryNtHeader(String code, bool qrybkstack = false);//查询单头
	void QryNtHeader(bool qrybkstack = false);//查询单头
	void QryNtHeader(int id, bool qrybkstack = false);//查询单头
	void DelNtHeader();//删除单头
	void UpdateNtHeader();//更新单头

	void UpdateNote();//更新单
	void DelNote();//删除单
	void BatchSetNotes(int amount, float discount, int mode);
	//void QryBkstack();
	void DelInvalidNtHeader();
	void ResetNtHeader();
	int addnotereturnvalue;
	String MaxNote;
	int ClientID;
	String format;
		bool blSelect;   //按shift多选
	TBookmark BookMark;
	bool SaveOrNot;
	bool ChangeDisplay;
	bool allclient,deletedetail,find,tuihuo,changepassword,sametishi;
public:		// User declarations
	__fastcall TfrmWholesaleReturnMng(TComponent* Owner);
	virtual void Init(LandInfo* li);
	bool __fastcall DbgridToExcel(TRzDBGrid* dbg);
	void GetHtHeaderTotal();
	bool AddNote(int supplierID, int catalogID,int stkid,int mod);//添加单
	void FindNote(String code);
	void historyview();
	void checkedview();
	bool retailreturn(int catalogID);
	void ModifyEnable();
	void ReadClient();
	bool saleenable(int stkid);
	LandInfo linfo;
	 bool SaveWsale(int mode);
	 AnsiString pxbk,logmessage,printtitle,contact,tel,address;
	 bool SaveOK();
	 int changehead,printmodle;
	 void FormView();
	 void ClientTuiHuo();
	 void  operterview(int operterid);
	 void __fastcall MyClickPreview(TObject *Sender);
	 void __fastcall MyClick(TObject *Sender);
	 void Print(int modle,int type,int printid);
	 bool tuihuocatch(int amount,int bkcatalogid);
	 void UpdateAmount(int amount);
	 int scroll;
         bool qfclient;
          void muilprint(AnsiString HeaderID,int type,bool xiaopiao=false);
          void A4muilprint(AnsiString HeaderID,int type);
};

//---------------------------------------------------------------------------
extern PACKAGE TfrmWholesaleReturnMng *frmWholesaleReturnMng;
//---------------------------------------------------------------------------
#endif
