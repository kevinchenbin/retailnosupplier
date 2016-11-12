//---------------------------------------------------------------------------

#ifndef UnitdaixiaoH
#define UnitdaixiaoH
//---------------------------------------------------------------------------
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include "RzDBEdit.hpp"
#include "RzEdit.hpp"
#include "RzLabel.hpp"
#include <ComCtrls.hpp>
#include <DBCtrls.hpp>
#include <Mask.hpp>
#include "RzDBDTP.hpp"
#include "RzDTP.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include "RzDBGrid.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include "DBGridEh.hpp"
#include "GridsEh.hpp"
#include <Buttons.hpp>
#include <Menus.hpp>
#include <Classes.hpp>
#include <SysUtils.hpp>
#include "RzDBCmbo.hpp"
#include "RzCmboBx.hpp"
#include "frxClass.hpp"
#include "frxCross.hpp"
#include "frxDBSet.hpp"
//---------------------------------------------------------------------------
class Tfrmdaixiao : public TForm
{
__published:	// IDE-managed Components
	TRzToolbar *rztlbr1;
	TRzToolButton *tlbtn8;
	TRzToolButton *tlbtn1;
	TRzToolButton *tlbtn7;
	TRzToolButton *BtnNew;
	TRzToolButton *BtnView;
	TRzToolButton *BtnAlignBottom;
	TRzToolButton *BtnPrint;
	TGroupBox *grpbxNtHeader;
	TRzLabel *lblCatalog;
	TGroupBox *GroupBox1;
	TRzLabel *RzLabel2;
	TRzDBEdit *dbedtRetailNtCode;
	TDBNavigator *DBNavigator1;
	TLabel *Label3;
	TLabel *Label1;
	TEdit *edname;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TEdit *editselfcode;
	TEdit *editprice;
	TEdit *editpress;
	TEdit *edqihao;
	TDataSource *dsHeader;
	TADOQuery *aqHeader;
	TLabel *Label11;
	TComboBoxEx *cbwangqi;
	TSpeedButton *SpeedButton1;
	TPopupMenu *pm;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TMenuItem *N4;
	TMenuItem *N13;
	TRzEdit *edtCatalog;
	TDataSource *dsnote;
	TADOQuery *aqnote;
	TRzLabel *lbl2;
	TRzLabel *RzLabel5;
	TRzLabel *lbl7;
	TLabel *Label10;
	TComboBox *cbcaigou;
	TADODataSet *dsetVendor;
	TDataSource *dsrcVendor;
	TPopupMenu *PopupMenu1;
	TMenuItem *D1;
	TDateTimePicker *dbdate;
	TMemo *dm;
	TRzNumericEdit *dbnbedtAddCosts;
	TRzToolButton *RzToolButton1;
	TComboBox *cbclient;
	TLabel *Label2;
	TLabel *Label5;
	TfrxCrossObject *frxCrossObject1;
	TfrxDBDataset *frxdbcaigoushengdai;
	TADOQuery *adoreport;
	TRzToolButton *RzToolButton2;
	TEdit *edtQryVendor;
	TSpeedButton *sbnewcustomer;
	TRzToolButton *RzToolButton3;
	TRzToolButton *RzToolButton4;
	TRzDBGrid *dbgrid;
	TLabel *Label4;
	TEdit *editcaigou;
	TEdit *editorder;
	TEdit *editdaixiao;
	TEdit *editcaigoubeng;
	TADOQuery *aqtotalhuizhong;
	TMenuItem *N5;
	TLabel *lboperation;
	TSpeedButton *spnewbook;
	TRzToolButton *RzToolButton5;
	TMenuItem *N6;
	TRzToolButton *RzToolButton6;
	TfrxCrossObject *frxCrossObject2;
	TRzNumericEdit *nedaixiao;
	TRzNumericEdit *necaigou;
	TRzNumericEdit *neorder;
	TComboBox *cbzhuanfa;
	TEdit *editbk;
	TGroupBox *GroupBox2;
	TCheckBox *chfoceset;
	TCheckBox *chfsluru;
	TCheckBox *chfsamount;
	TCheckBox *chfsdiscount;
	TCheckBox *chjinjia;
	TSpeedButton *SpeedButton2;
	TRadioButton *rb1;
	TRadioButton *rb2;
	TCheckBox *cbautochang;
	TLabel *Label12;
	TLabel *Label13;
	TLabel *Label14;
	TLabel *Label15;
	TRzToolButton *toolshowmainmenu;
	TMenuItem *N7;
	TMenuItem *N8;
	TRzNumericEdit *editcaigoudiscount;
	TMenuItem *N9;
	TMenuItem *F1;
	TMenuItem *N10;
	TRichEdit *Richcopy;
	void __fastcall tlbtn7Click(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall N3Click(TObject *Sender);
	void __fastcall N4Click(TObject *Sender);
	void __fastcall lblCatalogMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall edtCatalogKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall tlbtn1Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall dbgridColumns5GetCellParams(TObject *Sender, bool EditMode, TColCellParamsEh *Params);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall dblkpcbbVendorIDKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtQryVendorKeyPress(TObject *Sender, wchar_t &Key);

	void __fastcall tlbtn8Click(TObject *Sender);
	void __fastcall DBNavigator1Click(TObject *Sender, TNavigateBtn Button);
	void __fastcall cbclient2KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall D1Click(TObject *Sender);
	void __fastcall BtnNewClick(TObject *Sender);
	void __fastcall RzToolButton1Click(TObject *Sender);
	void __fastcall BtnPrintClick(TObject *Sender);
	void __fastcall caigoureportGetValue(const UnicodeString VarName, Variant &Value);
	void __fastcall RzToolButton2Click(TObject *Sender);
	void __fastcall dbgridColumns5UpdateData(TObject *Sender, UnicodeString &Text, Variant &Value,
          bool &UseText, bool &Handled);
	void __fastcall cbcaigouKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editcaigoudiscountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dbnbedtAddCostsKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbclientKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall sbnewcustomerClick(TObject *Sender);
	void __fastcall RzToolButton4Click(TObject *Sender);
	void __fastcall dbgridColumns4UpdateData(TObject *Sender, UnicodeString &Text, Variant &Value,
          bool &UseText, bool &Handled);
	void __fastcall dsnoteDataChange(TObject *Sender, TField *Field);
	void __fastcall N5Click(TObject *Sender);
	void __fastcall spnewbookClick(TObject *Sender);
	void __fastcall RzToolButton5Click(TObject *Sender);
	void __fastcall N6Click(TObject *Sender);
	void __fastcall PopupMenu1Popup(TObject *Sender);
	void __fastcall RzToolButton6Click(TObject *Sender);
	void __fastcall caigoureportBeforePrint(TfrxReportComponent *Sender);
	void __fastcall nedaixiaoKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall necaigouKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall SpeedButton2Click(TObject *Sender);
	void __fastcall neorderKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editbkKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dbgridCellClick(TColumn *Column);
	void __fastcall cbzhuanfaKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dbgridTitleClick(TColumn *Column);
	void __fastcall toolshowmainmenuClick(TObject *Sender);
	void __fastcall N7Click(TObject *Sender);
	void __fastcall dbgridMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall nedaixiaoClick(TObject *Sender);
	void __fastcall necaigouClick(TObject *Sender);
	void __fastcall neorderClick(TObject *Sender);
	void __fastcall F1Click(TObject *Sender);
	void __fastcall N10Click(TObject *Sender);





private:	// User declarations
   int StgID;
       int UserID;
       int SelectBkCatalogid;
       int m_catalogSearchMode;
       TADOConnection *fcn;
       int fmodify;
       int amount;
       AnsiString ausername;
       AnsiString bookname;
       AnsiString remarks;
       AnsiString title;
       AnsiString format,format1;
       float totalshiyang,totalmayang;
       TStringList *deletesave;
       AnsiString logmessage;
       bool sel ;//判断是否处于选择状态
       TBookmark bookmark;//记录先前的位置
       int oldrec;
       int currrec;
public:		// User declarations
	__fastcall Tfrmdaixiao(TComponent* Owner);
          void init(TADOConnection *cn,int auserid,int astgid,AnsiString username);
           void ChangeCatalogSearchMode();
             void AddNote(int ai,int bkcatalogid);
             void RefreshDetail();
             void RefreshBook();
             void RefreshHeader();
             void print(int type);
             int newclientid;
             TBookmark bm;
             void refreshHuizhong();
             bool checknote();
             void focusset(int type);
             AnsiString checkstr;
            void AddEventfx(int type,AnsiString SourceFrom,int user,int Stg,AnsiString Mg);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmdaixiao *frmdaixiao;
//---------------------------------------------------------------------------
#endif
