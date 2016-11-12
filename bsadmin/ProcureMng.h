//---------------------------------------------------------------------------

#ifndef ProcureMngH
#define ProcureMngH
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
#include "PwdForm.h"
#include <Dialogs.hpp>
#include <ComCtrls.hpp>
#include "RzDBDTP.hpp"
#include "RzDTP.hpp"
//---------------------------------------------------------------------------
class TfrmProcureMng : public TfrmMDIChild
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
	TRzToolButton *BtnAlignBottom;
	TRzToolButton *mtbbtnAddNtHeader;
	TRzToolButton *BtnView;
	TDataSource *ds2;
	TADOQuery *aq2;
	TRzLabel *RzLabel1;
	TRzDBNumericEdit *RzDBNumericEdit1;
	TDBNavigator *DBNavigator1;
	TDataSource *dsheader;
	TADOQuery *aqheader;
	TSaveDialog *savedlg;
	TRzToolButton *BtnSave;
	TRzToolButton *BtnProperties;
	TMenuItem *N7;
	TRzToolButton *BtnWeekView;
	TMenuItem *N8;
	TRzToolButton *BtnFinish;
	TLabel *Label2;
	TGroupBox *GroupBox1;
	TRzLabel *lbl2;
	TRzLabel *lbl3;
	TRzLabel *lbl4;
	TRzLabel *lbl7;
	TRzLabel *lbl1;
	TSpeedButton *RzButton1;
	TRzLabel *RzLabel2;
	TRzLabel *RzLabel5;
	TRzEdit *edtQryVendor;
	TRzDBNumericEdit *dbnbedtAddCosts;
	TRzDBEdit *dbedtWsaleNtCode;
	TRzDBLookupComboBox *dblkpcbbVendorID;
	TRzDBLookupComboBox *dblkpcbbStaffID;
	TMemo *membk;
	TGroupBox *GroupBox3;
	TCheckBox *chfoceset;
	TCheckBox *chfsluru;
	TCheckBox *chfsamount;
	TCheckBox *chfsdiscount;
	TGroupBox *GroupBox2;
	TRzLabel *lblCatalog;
	TRzLabel *lbl8;
	TRzLabel *lbl9;
	TLabel *Label1;
	TSpeedButton *spnewbook;
	TSpeedButton *SpeedButton1;
	TRzLabel *RzLabel3;
	TLabel *Label8;
	TRzDBNumericEdit *dbnbedtAmount;
	TRzEdit *edtCatalog;
	TRzDBNumericEdit *dbnbedtDiscount;
	TEdit *editdetailbk;
	TEdit *editjingjia;
	TCheckBox *CheckBox1;
	TRzDBGrid *dgdetail;
	TRzDBGrid *dbgrdNote;
	TLabel *labtitle;
	TDateTimePicker *dbdtedtHdTime;
	TDateTimePicker *dbdtedtHdyujiTime;
	TRzToolButton *toolshowmainmenu;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall tlbtn1Click(TObject *Sender);
	void __fastcall tlbtn7Click(TObject *Sender);
	void __fastcall edtQryVendorKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtCatalogKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall mniBsNoteSendbackClick(TObject *Sender);
	void __fastcall tlbtn4Click(TObject *Sender);
	void __fastcall dblkpcbbVendorIDKeyPress(TObject *Sender, wchar_t &Key);
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
	void __fastcall N4Click(TObject *Sender);
	void __fastcall dbnbedtTotalAmountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbstateChange(TObject *Sender);
	void __fastcall N6Click(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall dbnbedtAmountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall RzButton1Click(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall spnewbookClick(TObject *Sender);
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall dbgrdNoteCellClick(TColumn *Column);
	void __fastcall DBNavigator1Click(TObject *Sender, TNavigateBtn Button);
	void __fastcall membkExit(TObject *Sender);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall BtnPropertiesClick(TObject *Sender);
	void __fastcall BtnSaveClick(TObject *Sender);
	void __fastcall chfsluruClick(TObject *Sender);
	void __fastcall N7Click(TObject *Sender);
	void __fastcall BtnWeekViewClick(TObject *Sender);
	void __fastcall dbgrdNoteDblClick(TObject *Sender);
	void __fastcall N8Click(TObject *Sender);
	void __fastcall BtnFinishClick(TObject *Sender);
	void __fastcall editdetailbkKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dbnbedtDiscountExit(TObject *Sender);
	void __fastcall editjingjiaExit(TObject *Sender);
	void __fastcall editjingjiaKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall CheckBox1Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall membkKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall toolshowmainmenuClick(TObject *Sender);
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
	int m_catalogSearchMode;//1Ϊ��� 2Ϊ�Ա��� 3Ϊ����
	OPMode m_opmode;//1Ϊ�鵥ģʽ 2Ϊ��ӵ�ͷģʽ 3Ϊɾ����ͷģʽ 4Ϊ��ӵ�ģʽ 5Ϊɾ����ģʽ 6Ϊͳһģʽ 7Ϊ�ֳ��տ�ģʽ
	BSMode m_bsmode;//1Ϊ������ģʽ 2Ϊ�˻���ģʽ
	void ChangeCatalogSearchMode();
	void ChangeBsmode(BSMode bsmode);
	void ChangeOpmode(OPMode opmode);

	void QryNtHeader(String code, bool qrybkstack = false);//��ѯ��ͷ

	void DelNtHeader();//ɾ����ͷ

	void DelNote();//ɾ����
	void BatchSetNotes(int amount, float discount, int mode);
	void QryBkstack();
	void DelInvalidNtHeader();
	void ResetNtHeader();
        int GetTotalNum(int ID);
	int addnotereturnvalue;
	String MaxNote,logmessage;
	virtual void __fastcall CreateParams(TCreateParams & Param);
public:		// User declarations
	__fastcall TfrmProcureMng(TComponent* Owner);
	void QryNtHeader(int id, bool qrybkstack = false);//��ѯ��ͷ
	void QryNtHeader(bool qrybkstack = false);//��ѯ��ͷ
	virtual void Init(LandInfo* li);
	bool __fastcall DbgridToExcel(TRzDBGrid* dbg);
		int AddNote(int modle, int catalogID);//��ӵ�
		void FindNote(String code);
		void AddNtHeader();//��ӵ�ͷ
		void UpdateNote();//���µ�
		 void UpdateNtHeader();//���µ�ͷ
                 void UpdateNtHeader(int mode);
		 void VendorView();
		 bool findpwd,deletepwd;
	int userid,stgid;
	void historyview();
	void  operterview(int operterid);
	AnsiString printtitle,contact,tel,address,printbk,shaddress,shtel,shcontact,usertel;
        bool fqfsupplier;
};

//---------------------------------------------------------------------------
extern PACKAGE TfrmProcureMng *frmProcureMng;
//---------------------------------------------------------------------------
#endif
