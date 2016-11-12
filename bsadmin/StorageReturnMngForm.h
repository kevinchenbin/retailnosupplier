//---------------------------------------------------------------------------

#ifndef StorageReturnMngFormH
#define StorageReturnMngFormH
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
#include "RzDBDTP.hpp"
#include "RzDTP.hpp"
#include <pngimage.hpp>
#include "frxClass.hpp"
#include "frxDBSet.hpp"
//---------------------------------------------------------------------------

class TfrmStorageReturnMng : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TRzToolbar *rztlbr1;
	TRzStatusBar *RzStatusBar1;
	TRzLabel *lbl7;
	TRzLabel *lbl8;
	TRzDBNumericEdit *RzDBNumericEdit2;
	TRzLabel *lbl9;
	TRzLabel *lbl10;
	TRzDBNumericEdit *RzDBNumericEdit3;
	TRzDBNumericEdit *RzDBNumericEdit4;
	TPopupMenu *pmBsmode;
	TMenuItem *mniBsNote;
	TMenuItem *mniBsNoteSendback;
	TRzToolButton *RzToolButton5;
	TRzToolButton *RzToolButton2;
	TRzToolButton *RzToolButton3;
	TDataSource *dsrcSupplier;
	TDataSource *dsrcStaff;
	TADODataSet *dsetSupplier;
	TADODataSet *dsetStaff;
	TADODataSet *dsetBkstack;
	TDataSource *dsrcBkstack;
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
	TRzToolButton *RzToolButton6;
	TRzToolButton *RzToolButton8;
	TADOCommand *cmdAddNtHeader;
	TRzLabel *lblOpName;
	TADOCommand *cmdResetNtHeader;
	TImageList *ImageListMenu;
	TRzToolButton *BtnView;
	TRzToolButton *BtnNew;
	TPopupMenu *PM;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TRzToolButton *BtnClear;
	TADOQuery *query;
	TDataSource *dsrcstorage;
	TDataSource *dsrcdetail;
	TADOQuery *qudetail;
	TADOQuery *qrystorge;
	TPopupMenu *selectmenu;
	TMenuItem *N4;
	TMenuItem *N5;
	TMenuItem *N6;
	TRzToolButton *BtnChangeOptions;
	TMenuItem *N7;
	TMenuItem *N8;
	TMenuItem *N9;
	TRzToolButton *BtnView1;
	TRzToolButton *BtnSave;
	TADOStoredProc *spsave;
	TRzToolButton *BtnReminder;
	TDataSource *DBSource;
	TADOQuery *querydan;
	TRzDBGrid *dbgrdNote;
	TRzDBGrid *dgdetail;
	TEdit *edtotamount;
	TLabel *Label10;
	TLabel *Label3;
	TEdit *editbenqi;
	TLabel *Label4;
	TEdit *edityear;
	TADOStoredProc *sptuihuo;
	TSaveDialog *savedlg;
	TADOStoredProc *adospcopy;
	TADOStoredProc *adospupdatewsaleprice;
	TImage *Image1;
	TGroupBox *GroupBox1;
	TCheckBox *chfoceset;
	TCheckBox *chfsluru;
	TCheckBox *chfsamount;
	TCheckBox *chfsdiscount;
	TMenuItem *N10;
	TMenuItem *N11;
	TADODataSet *adoGetHeadTotal;
	TDataSource *dsGetHeadTotal;
	TDataSource *dsStkAmount;
	TADODataSet *dssetStkAmount;
	TLabel *labtitle;
	TLabel *Label5;
	TGroupBox *GroupBox2;
	TRzLabel *lbl1;
	TRzLabel *lblHdTime;
	TRzLabel *lblSupplier;
	TRzLabel *RzLabel3;
	TRzLabel *RzLabel6;
	TSpeedButton *sbnewcustomer;
	TRzLabel *RzLabel1;
	TRzDBEdit *dbedtStgNtCode;
	TRzDBLookupComboBox *dblkpcbbSupplierID;
	TRzDBNumericEdit *dbnbedtAddCosts;
	TEdit *editdanhao;
	TEdit *edtQrySupplier;
	TDBNavigator *DBNav;
	TMemo *membk;
	TRzDBDateTimePicker *dbdtedtHdTime;
	TEdit *edxyedu;
	TEdit *edkcedu;
	TEdit *edbond;
	TGroupBox *grpbxNote;
	TLabel *Label1;
	TRzLabel *lbl4;
	TRzLabel *lbl5;
	TRzLabel *lbl6;
	TRzLabel *lblAmount;
	TRzLabel *lblCatalog;
	TLabel *Label8;
	TSpeedButton *SpeedButton1;
	TComboBox *cbbkstackID;
	TRzEdit *edtCatalog;
	TEdit *editshun;
	TRzDBNumericEdit *RzDBNumericEdit1;
	TRzNumericEdit *dbnbedtAmount;
	TRzNumericEdit *dbnbedtDiscount;
	TCheckBox *CheckBox1;
	TRzLabel *RzLabel2;
	TRzLabel *RzLabel4;
	TRzToolButton *BtnAlignBottom;
	TRzToolButton *RzToolButton9;
	TRzToolButton *RzToolButton1;
	TPopupMenu *pmprint2;
	TMenuItem *A41;
	TMenuItem *N15;
	TPopupMenu *pmpriver;
	TMenuItem *A42;
	TMenuItem *N16;
	TfrxReport *frxstoragexiaopiao;
	TfrxDBDataset *frxstoragemuilhead;
	TfrxDBDataset *frxstoragemuildetail;
	TADOQuery *storageqmuildetail;
	TADOQuery *storageqmuilhead;
	void __fastcall edtCatalogKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtQrySupplierKeyPress(TObject *Sender, wchar_t &Key);
    void __fastcall dblkpcbbStaffIDKeyPress(TObject *Sender, wchar_t &Key);
  //	void __fastcall RzToolButton5Click(TObject *Sender);
	void __fastcall dbedtSupplySNKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dbnbedtAmountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall RzToolButton9Click(TObject *Sender);
	void __fastcall RzToolButton8Click(TObject *Sender);
	void __fastcall RzToolButton6Click(TObject *Sender);
	void __fastcall dbnbedtAmountExit(TObject *Sender);
	void __fastcall sbnewcustomerClick(TObject *Sender);
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall lblCatalogMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall N3Click(TObject *Sender);
	void __fastcall BtnClearClick(TObject *Sender);
	void __fastcall RzToolButton3Click(TObject *Sender);
	void __fastcall RzToolButton5Click(TObject *Sender);
	void __fastcall RzToolButton2Click(TObject *Sender);
	void __fastcall dblkpcbbSupplierIDKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dbgrdNoteDblClick(TObject *Sender);
	void __fastcall dbgrdNoteCellClick(TColumn *Column);
	void __fastcall N5Click(TObject *Sender);
	void __fastcall N6Click(TObject *Sender);
	void __fastcall BtnNewClick(TObject *Sender);
	void __fastcall BtnChangeOptionsClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall N8Click(TObject *Sender);
	void __fastcall dbgrdNoteMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall N9Click(TObject *Sender);
	void __fastcall BtnView1Click(TObject *Sender);
	void __fastcall BtnSaveClick(TObject *Sender);
	void __fastcall dbnbedtAddCostsExit(TObject *Sender);
	void __fastcall dbnbedtAddCostsKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnReminderClick(TObject *Sender);
	void __fastcall DBNavClick(TObject *Sender, TNavigateBtn Button);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall dbgrdNoteTitleClick(TColumn *Column);
	void __fastcall dbnbedtDiscountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall N10Click(TObject *Sender);
	void __fastcall editshunExit(TObject *Sender);
	void __fastcall editshunKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall membkKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall chfsluruClick(TObject *Sender);
	void __fastcall N11Click(TObject *Sender);
	void __fastcall cbbkstackIDSelect(TObject *Sender);
	void __fastcall CheckBox1Click(TObject *Sender);
	void __fastcall dsrcNoteDataChange(TObject *Sender, TField *Field);
	void __fastcall dsetNoteBeforeScroll(TDataSet *DataSet);
	void __fastcall dblkpcbbSupplierIDClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall dbnbedtDiscountExit(TObject *Sender);
	void __fastcall RzToolButton1Click(TObject *Sender);
	void __fastcall N16Click(TObject *Sender);
	void __fastcall N15Click(TObject *Sender);



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
	String m_findCode;//��Ҫ��ѯ�ĵ���
	int m_catalogSearchMode;//1Ϊ��� 2Ϊ�Ա��� 3Ϊ����
	OPMode m_opmode;//1Ϊ�鵥ģʽ 2Ϊ��ӵ�ͷģʽ 3Ϊɾ����ͷģʽ 4Ϊ��ӵ�ģʽ 5Ϊɾ����ģʽ 6Ϊͳһģʽ 7Ϊ�ֳ��տ�ģʽ
	BSMode m_bsmode;//1Ϊ������ģʽ 2Ϊ�˻���ģʽ

   void GetHtHeaderTotal();
	void ChangeCatalogSearchMode();
	void ChangeBsmode(BSMode bsmode);
	void ChangeOpmode(OPMode opmode);
	void AddNtHeader();//��ӵ�ͷ
	void QryNtHeader(String code, bool qrybkstack = false);//��ѯ��ͷ
	void QryNtHeader(bool qrybkstack = false);//��ѯ��ͷ

	void DelNtHeader();//ɾ����ͷ
	void UpdateNtHeader();//���µ�ͷ


	void UpdateNote();//���µ�
	void UpdateNote1();//���µ���ˢ��
	void DelNote();//ɾ����
	void BatchSetNotes(int amount, float discount, int mode);
	void QryBkstack();
	//bool IsOverlapCatalog(int headerid, int catalogid, int supplierid);
	//void OnHotKeyPress(DWORD vkCode, bool ctrlpress);
	void DelInvalidNtHeader();
	//void ResetNtHeader();
	void GetBkStackInfo();
	String MaxNote;
	String format;
	bool blSelect;   //��shift��ѡ
	TBookmark BookMark;

	int supplierDI;
	bool ChangeDisplay,allsupplier,findpassword,deletepassword,tuihuopassword,changepassword,sameid,sametuiinput;
	TStringList *BSSET;
public:		// User declarations
	__fastcall TfrmStorageReturnMng(TComponent* Owner);
	void QryNtHeader(int id, bool qrybkstack = false);//��ѯ��ͷ
	bool SaveOrNot;
	bool __fastcall DbgridToExcel(TRzDBGrid* dbg);
	void Init(LandInfo* li);

	  //	SYSSet* GetBSsetByName(String Name);
   //	bool AddNote(int id);//��ӵ�
        int storageday;
		bool AddNote(int supplierID, int catalogID);//��ӵ�
		bool AddNote(int id);
		void FindNote(String code);
		void historyview();
		void ModifyEnable();
		void changeInputMode();
		bool bsetpixiaodiscount,rktuihuoguanli;
		float pixiaodiscount;
		LandInfo linfo;
		 bool SaveStorage(int mode);
		 AnsiString rkbk,logmessage,beforesuppliername,printtitle,contact,tel,address;
		 bool SaveOK();
		void ChangeSupplier();
		int beforesupplier;
		void FormView();
		void tuihuolv();
		bool stackchange;
		void UpdateWsaleDiscout(int mode);
		void  operterview(int operterid);
		int scroll;
		bool SupplierCreit();
                bool qfsupplier;
                void  storageprintxiaopiao(AnsiString ID,int type,int printorpre);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmStorageReturnMng *frmStorageReturnMng;
//---------------------------------------------------------------------------
#endif
