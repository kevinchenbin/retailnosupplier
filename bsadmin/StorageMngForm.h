//---------------------------------------------------------------------------

#ifndef StorageMngFormH
#define StorageMngFormH
//---------------------------------------------------------------------------

#include "RzButton.hpp"
#include "RzCmboBx.hpp"
#include "RzDBCmbo.hpp"
#include "RzDBEdit.hpp"
#include "RzDBGrid.hpp"
#include "RzDBLbl.hpp"
#include "RzDBSpin.hpp"
#include "RzEdit.hpp"
#include "RzLabel.hpp"
#include "RzPanel.hpp"
#include "RzSpnEdt.hpp"
#include <ADODB.hpp>
#include <Buttons.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Mask.hpp>
#include <Menus.hpp>
#include <StdCtrls.hpp>
#include <DBCtrls.hpp>
#include "RzCommon.hpp"
#include "RzDBLook.hpp"
#include "pdutil.h"
#include "MDIChild.h"
#include "RzRadChk.hpp"
#include <ImgList.hpp>

#include "bsprint.h"
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <Graphics.hpp>
#include "RzDTP.hpp"
#include "RzDBDTP.hpp"
#include <jpeg.hpp>
#include <pngimage.hpp>
#include <ToolWin.hpp>
#include "frxClass.hpp"
#include "frxDBSet.hpp"
//---------------------------------------------------------------------------
class TfrmStorageMng : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TRzStatusBar *RzStatusBar1;
	TRzLabel *lbl7;
	TRzLabel *lbl8;
	TRzDBNumericEdit *RzDBNumericEdit2;
	TRzLabel *lbl9;
	TRzLabel *lbl10;
	TRzDBNumericEdit *RzDBNumericEdit3;
	TRzDBNumericEdit *RzDBNumericEdit4;
	TDataSource *dsrcSupplier;
	TDataSource *dsrcStaff;
	TADODataSet *dsetSupplier;
	TADODataSet *dsetStaff;
	TADOStoredProc *spQryNtHeader;
	TADOCommand *cmdUpdateNtHeader;
	TADOStoredProc *spQryNtHeader1;
	TADODataSet *dsetNtHeader;
	TDataSource *dsrcNtHeader;
	TADODataSet *dsetNote;
	TDataSource *dsrcNote;
	TADOCommand *cmdAddNote;
	TADOCommand *cmdUpdateNote;
	TADOCommand *cmdDelNote;
	TADOCommand *cmdDelNtHeader;
	TADOCommand *cmdBatchUpdateNote;
	TADOCommand *cmdBatchDelNote;
	TADOCommand *cmdAddNtHeader;
	TRzLabel *lblOpName;
	TADOCommand *cmdResetNtHeader;
	TImageList *ImageListMenu;
	TPopupMenu *PM;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TADOQuery *query;
	TDataSource *dsrcdetail;
	TADOQuery *qudetail;
	TADOQuery *qrystorge;
	TPopupMenu *selectmenu;
	TMenuItem *N4;
	TMenuItem *N5;
	TPopupMenu *pmBsmode;
	TMenuItem *mniBsNote;
	TMenuItem *mniBsNoteSendback;
	TMenuItem *N6;
	TGroupBox *grpbxNote;
	TComboBox *cbbkstackID;
	TRzDBLookupComboBox *dblkpcbbBkstackID;
	TRzDBNumericEdit *dbnbedt1;
	TRzEdit *edtCatalog;
	TLabel *Label1;
	TRzLabel *lbl4;
	TRzLabel *lbl5;
	TRzLabel *lbl6;
	TRzLabel *lblAmount;
	TRzLabel *lblCatalog;
	TSpeedButton *spnewbook;
	TLabel *Label3;
	TEdit *editjingjiaprice;
	TLabel *Label4;
	TEdit *editpxprice;
	TLabel *Label6;
	TEdit *editpxdiscount;
	TLabel *Label5;
	TADOStoredProc *adospupdatewsaleprice;
	TEdit *editque;
	TLabel *Label8;
	TEdit *editshun;
	TCheckBox *cbreturn;
	TMenuItem *N7;
	TMenuItem *N8;
	TMenuItem *N9;
	TADOStoredProc *spsave;
	TDataSource *DBSource;
	TADOQuery *querydan;
	TRzDBGrid *dbgrdNote;
	TRzDBGrid *dgdetail;
	TEdit *edtotamount;
	TLabel *Label10;
	TLabel *Label11;
	TLabel *Label12;
	TLabel *Label13;
	TEdit *edtlsprice;
	TEdit *edlsdiscount;
	TRzLabel *RzLabel1;
	TRzDBNumericEdit *RzDBNumericEdit1;
	TSaveDialog *savedlg;
	TADOStoredProc *adospcopy;
	TSpeedButton *SpeedButton1;
	TMenuItem *N10;
	TPopupMenu *pmprint;
	TMenuItem *N11;
	TMenuItem *N12;
	TLabel *Label7;
	TDateTimePicker *dtpbackdate;
	TLabel *Label14;
	TDataSource *dsGetHtHeaderTotal;
	TADODataSet *dsetGetHtHeaderTotal;
	TDataSource *dsStkAmount;
	TADODataSet *dssetStkAmount;
	TRzNumericEdit *dbnbedtAmount;
	TRzNumericEdit *dbnbedtDiscount;
	TMenuItem *N13;
	TMenuItem *N14;
	TCheckBox *CheckBox1;
	TGroupBox *GroupBox1;
	TCheckBox *chfoceset;
	TCheckBox *chfsluru;
	TCheckBox *chfsamount;
	TCheckBox *chfsdiscount;
	TCheckBox *chpxdiscount;
	TCheckBox *chpxprice;
	TCheckBox *chlsdiscount;
	TCheckBox *chlsprice;
	TCheckBox *chjinjia;
	TImage *Image1;
	TLabel *lbcaption;
	TLabel *labtitle;
	TRzToolbar *RzToolbar1;
	TRzToolButton *BtnView;
	TRzToolButton *BtnNew;
	TRzToolButton *BtnSave;
	TRzToolButton *BtnChangeOptions;
	TRzToolButton *RzToolButton2;
	TRzToolButton *RzToolButton3;
	TRzToolButton *BtnReminder;
	TRzToolButton *RzToolButton6;
	TRzToolButton *RzToolButton8;
	TRzToolButton *BtnClear;
	TRzToolButton *BtnSetTabs;
	TRzToolButton *RzToolButton19;
	TRzToolButton *BtnTile;
	TRzToolButton *BtnView1;
	TRzToolButton *RzToolButton22;
	TRzToolButton *RzToolButton5;
	TGroupBox *GroupBox2;
	TRzLabel *lblHdTime;
	TRzLabel *lblSupplier;
	TRzLabel *RzLabel3;
	TRzLabel *RzLabel4;
	TRzLabel *RzLabel6;
	TSpeedButton *sbnewcustomer;
	TLabel *Label9;
	TLabel *Label15;
	TRzLabel *RzLabel7;
	TRzLabel *RzLabel5;
	TRzDBEdit *dbedtStgNtCode;
	TRzDBEdit *dbedtSupplySN;
	TRzDBLookupComboBox *dblkpcbbSupplierID;
	TRzDBNumericEdit *dbnbedtAddCosts;
	TRzEdit *RzEdit1;
	TEdit *editdanhao;
	TDBNavigator *DBNav;
	TMemo *membk;
	TRzDBDateTimePicker *RzDBDateTimePicker1;
	TEdit *edkcedu;
	TEdit *edxyedu;
	TEdit *edbond;
	TComboBox *cbtype;
	TLabel *Label2;
	TLabel *Label16;
	TADOStoredProc *adostorecaigou;
	TRzToolButton *RzToolButton1;
	TLabel *lbcaigoutishi;
	TRzToolButton *RzToolButton4;
	TPopupMenu *pmprint2;
	TPopupMenu *pmpriver;
	TMenuItem *N15;
	TMenuItem *N16;
	TMenuItem *A41;
	TMenuItem *A42;
	TADOQuery *storageqmuilhead;
	TfrxDBDataset *frxstoragemuildetail;
	TfrxDBDataset *frxstoragemuilhead;
	TADOQuery *storageqmuildetail;
	TfrxReport *frxstoragexiaopiao;
	TMenuItem *N17;
	TRzLabel *RzLabel2;
	TRzDBDateTimePicker *suppliertime;
	TLabel *Label17;
	TLabel *Label18;
	TEdit *huiyuan;
	TLabel *Label19;
	TLabel *Label20;
	TEdit *editzhuidi;
	TLabel *Label21;
	TLabel *Label22;
	void __fastcall edtCatalogKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtQrySupplierKeyPress(TObject *Sender, wchar_t &Key);
    void __fastcall dblkpcbbStaffIDKeyPress(TObject *Sender, wchar_t &Key);
  //	void __fastcall RzToolButton5Click(TObject *Sender);
	void __fastcall dbedtSupplySNKeyPress(TObject *Sender, wchar_t &Key);

	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);

	void __fastcall sbnewcustomerClick(TObject *Sender);
	void __fastcall spnewbookClick(TObject *Sender);
	void __fastcall lblCatalogMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall N3Click(TObject *Sender);
	void __fastcall dblkpcbbSupplierIDKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dbgrdNoteDblClick(TObject *Sender);
	void __fastcall dbgrdNoteCellClick(TColumn *Column);
	void __fastcall N5Click(TObject *Sender);
	void __fastcall N6Click(TObject *Sender);
	void __fastcall editpxdiscountExit(TObject *Sender);
	void __fastcall dbnbedtDiscountExit(TObject *Sender);
	void __fastcall editjingjiapriceExit(TObject *Sender);
	void __fastcall editjingjiapriceKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editpxdiscountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editpxpriceExit(TObject *Sender);
	void __fastcall editpxpriceKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editshunExit(TObject *Sender);
	void __fastcall editqueExit(TObject *Sender);
	void __fastcall editqueKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editshunKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbreturnExit(TObject *Sender);
	void __fastcall cbbkstackIDSelect(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall dbgrdNoteMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall N9Click(TObject *Sender);
	void __fastcall N8Click(TObject *Sender);
	void __fastcall dbedtSupplySNExit(TObject *Sender);
	void __fastcall RzEdit1KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dbnbedtAddCostsExit(TObject *Sender);
	void __fastcall dbnbedtAddCostsKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall DBNavClick(TObject *Sender, TNavigateBtn Button);
	void __fastcall dbgrdNoteTitleClick(TColumn *Column);
	void __fastcall edlsdiscountExit(TObject *Sender);
	void __fastcall dbnbedtDiscountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall membkKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall chfsluruClick(TObject *Sender);
	void __fastcall N10Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall edlsdiscountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtlspriceKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnBulletsClick(TObject *Sender);
	void __fastcall N11Click(TObject *Sender);

	void __fastcall N12Click(TObject *Sender);
	void __fastcall dtpbackdateCloseUp(TObject *Sender);
	void __fastcall dblkpcbbStaffIDExit(TObject *Sender);
	void __fastcall neamountExit(TObject *Sender);
	void __fastcall nediscountExit(TObject *Sender);
	void __fastcall neamountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall nediscountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtlspriceExit(TObject *Sender);
	void __fastcall N13Click(TObject *Sender);
	void __fastcall CheckBox1Click(TObject *Sender);
	void __fastcall dsetNoteBeforeScroll(TDataSet *DataSet);
	void __fastcall dsrcNoteDataChange(TObject *Sender, TField *Field);
	void __fastcall dblkpcbbSupplierIDClick(TObject *Sender);
	void __fastcall cbtypeSelect(TObject *Sender);
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall BtnNewClick(TObject *Sender);
	void __fastcall RzToolButton10Click(TObject *Sender);
	void __fastcall RzToolButton11Click(TObject *Sender);
	void __fastcall RzToolButton12Click(TObject *Sender);
	void __fastcall RzToolButton3Click(TObject *Sender);
	void __fastcall BtnReminderClick(TObject *Sender);
	void __fastcall RzToolButton6Click(TObject *Sender);
	void __fastcall RzToolButton8Click(TObject *Sender);
	void __fastcall BtnClearClick(TObject *Sender);
	void __fastcall BtnSetTabsClick(TObject *Sender);
	void __fastcall BtnTileClick(TObject *Sender);
	void __fastcall BtnView1Click(TObject *Sender);
	void __fastcall RzToolButton22Click(TObject *Sender);
	void __fastcall RzToolButton5Click(TObject *Sender);
	void __fastcall RzToolButton19Click(TObject *Sender);
	void __fastcall RzToolButton1Click(TObject *Sender);
	void __fastcall RzToolButton4Click(TObject *Sender);
	void __fastcall N15Click(TObject *Sender);
	void __fastcall N16Click(TObject *Sender);
	void __fastcall N17Click(TObject *Sender);
	void __fastcall huiyuanExit(TObject *Sender);
	void __fastcall editzhuidiExit(TObject *Sender);
	void __fastcall huiyuanKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editzhuidiKeyPress(TObject *Sender, wchar_t &Key);





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
	String m_findCode;//将要查询的单号
	int m_catalogSearchMode;//1为书号 2为自编码 3为书名
	OPMode m_opmode;//1为查单模式 2为添加单头模式 3为删除单头模式 4为添加单模式 5为删除单模式 6为统一模式 7为现场收款模式
	BSMode m_bsmode;//1为批销单模式 2为退货单模式
	void ChangeOpmode(OPMode opmode);
	void AddNtHeader();//添加单头
	void QryNtHeader(String code, bool qrybkstack = false);//查询单头
	void QryNtHeader(bool qrybkstack = false);//查询单头

	void DelNtHeader();//删除单头
	void UpdateNtHeader();//更新单头



	void DelNote();//删除单
	void BatchSetNotes(int amount, float discount, int mode);
	void QryBkstack();
	//bool IsOverlapCatalog(int headerid, int catalogid, int supplierid);
	void DelInvalidNtHeader();
	void ResetNtHeader();
	void GetBkStackInfo();
	void UpdateWsaleDiscout(int mode);//更新批销折扣，价格等
	void BatchsetWsaleDiscout(float pidiscount); //统一更新批销折扣
	String MaxNote;
	bool stackchange;
	String format;
	bool autologout;
	bool blSelect;   //按shift多选
	TBookmark BookMark;
	bool lastjypxdiscount,addnote;
	int storageday;
	AnsiString yjpxkind;

	bool ChangeDisplay,allsupplier,findpassword,deletepassword,changepassword,sameid,sameinput;
public:		// User declarations
	__fastcall TfrmStorageMng(TComponent* Owner);
	bool __fastcall DbgridToExcel(TRzDBGrid* dbg);
	void Init(LandInfo* li);
   //	bool AddNote(int id);//添加单
        void GetHtHeaderTotal();
		bool AddNote(int supplierID, int catalogID);//添加单
		bool AddNote(int id);
		void FindNote(String code);
		void historyview();
		void addwsalediscount();
		void ModifyEnable();
			void UpdateNote();//更新单
			void  AutologProA(); //自动注销采购记录作废
			void  AutologProS(int supplier,int BkcatalogID);//自动注销采购记录
			void  AutologPro();
			void  UpdateProHeader();
			void changeInputMode();
			bool bsetpixiaodiscount;
			bool bsetlsdiscount;
                        bool caigourukutishi;
		float pixiaodiscount,lsdiscount;
		void lastyjpxdiscount();
		//void yjpxdiscount();
		LandInfo linfo;
		bool SaveStorage(int mode);
		AnsiString rkbk,logmessage,beforesuppliername,printtitle,contact,tel,address;
		bool SaveOK();
		bool SaveOrNot,userbarcode;
		void ChangeSupplier();
		int beforesupplier;
		void QryNtHeader(int id, bool qrybkstack = false);//查询单头
		void BatchsetLsDiscout(float lsdiscount);
		void FormView();
		void grdCellClick();
		void  operterview(int operterid);
		TStringList *strlist;
		AnsiString catalogidlist;
		int scroll;
		bool inpulimit(AnsiString checkstr);
		bool SupplierCreit(int modle);
				bool complierDateTime();
                bool fqfsupplier;
			  void  storageprintxiaopiao(AnsiString ID,int type,int printorpre);
				void __fastcall dbgrdNoteDrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol,
		  TColumn *Column, Grids::TGridDrawState State);
		  bool lshuiyuan,zuidizk,lszk;
		  AnsiString lsadddont,zhuidizkadd,lszkadd;
		  void updatelsdiscount(float rkzk);
		  AnsiString GetSelectRowID();

		  };
//---------------------------------------------------------------------------
extern PACKAGE TfrmStorageMng *frmStorageMng;
//---------------------------------------------------------------------------
#endif
