//---------------------------------------------------------------------------

#ifndef WholesaleMngFormH
#define WholesaleMngFormH
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
#include <dblookup.hpp>
#include <DBTables.hpp>
#include "DBCtrlsEh.hpp"
#include "DBGridEh.hpp"
#include "DBLookupEh.hpp"
//---------------------------------------------------------------------------
class TfrmWholesaleMng : public TfrmMDIChild
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
	TLabel *Label7;
	TRzDBNumericEdit *dbnbedt5;
	TLabel *Label8;
	TRzDBNumericEdit *dbnbedt6;
	TDataSource *DBSource;
        TADOQuery *querydan;
	TEdit *edtotamount;
	TLabel *Label10;
	TRzToolButton *BtnAlignBottom;
	TLabel *Label9;
	TRzDBNumericEdit *RzDBNumericEdit1;
	TPopupMenu *pmprint;
	TMenuItem *N10;
	TMenuItem *N13;
	TSaveDialog *savedlg;
	TADOStoredProc *adospcopy;
	TADOStoredProc *spcopy;
	TGroupBox *GroupBox2;
	TCheckBox *chfoceset;
	TCheckBox *chfsluru;
	TCheckBox *chfsamount;
	TCheckBox *chfsdiscount;
	TMenuItem *N14;
	TRzToolButton *BtnViewList;
	TPopupMenu *pmpreview;
	TRzToolButton *BtnBringtoFront;
	TPopupMenu *pmprintbag;
	TMenuItem *N15;
	TMenuItem *N16;
	TMenuItem *N17;
	TMenuItem *N18;
	TMenuItem *N19;
	TADOStoredProc *sphunhedabao;
	TADOQuery *aqhunhedabao;
	TMenuItem *N20;
	TDataSource *dsGetTotal;
	TADODataSet *dtGetTotal;
	TDataSource *dsstkamount;
	TADODataSet *dsetstkamount;
	TCheckBox *chfajia;
	TADOCommand *cmdUpdataamount;
	TGroupBox *grpbxNote;
	TLabel *Label1;
	TRzLabel *lbl8;
	TRzLabel *lbl9;
	TRzLabel *lblCatalog;
	TLabel *Label5;
	TSpeedButton *SpeedButton1;
	TSpeedButton *SpeedButton2;
	TLabel *Label11;
	TRzEdit *edtCatalog;
	TEdit *editprice;
	TRzNumericEdit *dbnbedtAmount;
	TRzNumericEdit *dbnbedtDiscount;
	TRzDBGrid *dbgrdNote;
	TLabel *Label2;
	TImage *Image1;
	TRzDBGrid *dgrecord;
	TLabel *labtitle;
	TCheckBox *CheckBox1;
	TGroupBox *grpbxNtHeader;
	TRzLabel *lbl1;
	TRzLabel *lbl2;
	TRzLabel *lbl3;
	TRzLabel *lbl4;
	TRzLabel *lbl6;
	TRzLabel *lbl7;
	TSpeedButton *spnew;
	TRzLabel *RzLabel2;
	TRzEdit *edtQryVendor;
	TRzDBEdit *dbedtWsaleNtCode;
	TRzDBLookupComboBox *dblkpcbbVendorID;
	TRzDBNumericEdit *dbnbedtAddCosts;
	TDateTimePicker *dtpdate;
	TDBNavigator *DBNav;
	TEdit *editdanhao;
	TMemo *membk;
	TEdit *ednocheck;
	TEdit *edcredit;
	TRzLabel *RzLabel3;
	TEdit *edchecked;
	TEdit *edbond;
	TLabel *Label4;
	TLabel *Label3;
	TRzDBNumericEdit *dbnbedtTotalAmount;
	TRzLabel *RzLabel5;
	TComboBox *cbtype;
	TEdit *ednocheck1;
	TComboBox *dblkpcbbStaffID;
	TRzToolButton *RzToolButton3;
	TPopupMenu *PopupMenu3;
	TPopupMenu *PopupMenu4;
	TMenuItem *A41;
	TMenuItem *N21A41;
	TMenuItem *A42;
	TMenuItem *N21A42;
	TRzToolButton *muilprintbutton;
	TPopupMenu *PopupMenu5;
	TMenuItem *A43;
	TMenuItem *N21A43;
	TRzLabel *RzLabel1;
	TRzNumericEdit *netotalyingfu;
	TLabel *Label6;
	TMenuItem *N23;
	TMenuItem *N24;
	TMenuItem *N25;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall tlbtn1Click(TObject *Sender);
	void __fastcall tlbtn7Click(TObject *Sender);
	void __fastcall edtQryVendorKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtCatalogKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall mniBsNoteSendbackClick(TObject *Sender);
	void __fastcall tlbtn4Click(TObject *Sender);
	void __fastcall dblkpcbbBkstackIDKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dbl(TObject *Sender, wchar_t &Key);
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
	void __fastcall cbbkstackIDExit(TObject *Sender);
	void __fastcall cbbkstackIDKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall tlbtnAddNoteClick(TObject *Sender);
	void __fastcall dbgrdNoteMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall N8Click(TObject *Sender);
	void __fastcall N9Click(TObject *Sender);
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall cbclientExit(TObject *Sender);
	void __fastcall BtnSaveClick(TObject *Sender);
	void __fastcall dbnbedtAddCostsExit(TObject *Sender);
	void __fastcall dbnbedtAddCostsKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall DBNavClick(TObject *Sender, TNavigateBtn Button);
	void __fastcall dbnbedtDiscountExit(TObject *Sender);
	void __fastcall spnewClick(TObject *Sender);
	void __fastcall cbclientClick(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall dbgrdNoteTitleClick(TColumn *Column);
	void __fastcall edtclientKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall N10Click(TObject *Sender);
	void __fastcall N13Click(TObject *Sender);
	void __fastcall membkKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall N14Click(TObject *Sender);
	void __fastcall chfsluruClick(TObject *Sender);
	void __fastcall editpriceKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnViewListClick(TObject *Sender);
	void __fastcall dbgrdNoteDblClick(TObject *Sender);
	void __fastcall BtnBringtoFrontClick(TObject *Sender);
	void __fastcall N19Click(TObject *Sender);
	void __fastcall SpeedButton2Click(TObject *Sender);
	void __fastcall N20Click(TObject *Sender);
	void __fastcall dblkpcbbVendorID1KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dblkpcbbVendorID1Click(TObject *Sender);
	void __fastcall dblkpcbbVendorIDClick(TObject *Sender, bool &Handled);
	void __fastcall dblkpcbbVendorIDKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall CheckBox1Click(TObject *Sender);
	void __fastcall dsetNoteBeforeScroll(TDataSet *DataSet);
	void __fastcall dsrcNoteDataChange(TObject *Sender, TField *Field);

	void __fastcall cbtypeSelect(TObject *Sender);
	void __fastcall dblkpcbbStaffIDChange(TObject *Sender);
	void __fastcall RzToolButton3Click(TObject *Sender);
	void __fastcall N23Click(TObject *Sender);
	void __fastcall N24Click(TObject *Sender);
	void __fastcall A41Click(TObject *Sender);
	void __fastcall N21A41Click(TObject *Sender);
	void __fastcall A42Click(TObject *Sender);
	void __fastcall N21A42Click(TObject *Sender);
	void __fastcall muilprintbuttonClick(TObject *Sender);
	void __fastcall A43Click(TObject *Sender);
	void __fastcall N25Click(TObject *Sender);



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

	void DelNtHeader();//删除单头
	void UpdateNtHeader();//更新单头

	void UpdateNote();//更新单
	void DelNote();//删除单
	void BatchSetNotes(int amount, float discount, int mode);
	void QryBkstack();
	void DelInvalidNtHeader();
	//void ResetNtHeader();
	int addnotereturnvalue;
	String MaxNote;
	int ClientID;
	int Type;//1为批销员调用，2为零售员调用
	String format;
	bool blSelect;   //按shift多选
	TBookmark BookMark;
	bool SaveOrNot;
	bool SaveWsale(int mode);
	float bakdot;
	bool ChangeDisplay;
	bool allclient,deletedetail,find,changepassword,sametishi;

public:		// User declarations
	__fastcall TfrmWholesaleMng(TComponent* Owner,int type);
	virtual void Init(LandInfo* li);
	void QryNtHeader(int id, bool qrybkstack = false);//查询单头
	bool __fastcall DbgridToExcel(TRzDBGrid* dbg);
	bool AddNote(int supplierID, int catalogID,int bkinfoid,int mod);//添加单     mod 0 添加后查询，1添加后不查询
	void FindNote(String code);
	void historyview();
	bool checkedview(int modle);
	//bool retailreturn(int catalogID);
        HWND MainHandle;
      void GetHtHeaderTotal();

	void ModifyEnable();
	void ReadClient();
	bool bsetpixiaodiscount,localstack;
	bool saleenable(int stkid);
	float pixiaodiscount;
	bool  discountcatch(int stkid);
	LandInfo linfo;
	void Backdot(float discount);
	int huanhuo;
	int wosaleday;
	AnsiString pxbk,logmessage,printtitle,contact,tel,address;
	bool tuihuo;
	bool SaveOK();
	int changehead,printmodle;  // printmodle 为0学校，1书店模式
	void FormView();
	void localnum(int amount);
	void operterview(int operterid);
	void __fastcall MyClick(TObject *Sender);
	void __fastcall MyClickPreview(TObject *Sender);
	void  Print(int modle,int type,int printid);
	void hunhedabao();
	int printbagtype;
	void PrintAdd();
	int scroll;
	AnsiString BkcatalogID;
	void UpdateAmount(int amount) ;
        void SearchDanHao(AnsiString awhere);
		bool complierDateTime();
        void muilprint(AnsiString HeaderID,int type,bool xiaopiao);
        void A4muilprint(AnsiString HeaderID,int type);
        int version;
        bool qfclient;
		void __fastcall dbgrdNoteDrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol,
		  TColumn *Column, Grids::TGridDrawState State);
};

//---------------------------------------------------------------------------
extern PACKAGE TfrmWholesaleMng *frmWholesaleMng;
//---------------------------------------------------------------------------
#endif
