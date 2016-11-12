//---------------------------------------------------------------------------

#ifndef MemberOrderH
#define MemberOrderH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzDBEdit.hpp"
#include "RzDBGrid.hpp"
#include "RzEdit.hpp"
#include "RzLabel.hpp"
#include "RzPanel.hpp"
#include "RzRadChk.hpp"
#include <Buttons.hpp>
#include <DBCtrls.hpp>
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Mask.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <Menus.hpp>
#include "frxClass.hpp"
#include "frxDBSet.hpp"
//---------------------------------------------------------------------------
class Tfrmmemberorder : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TRzToolbar *rztlbr1;
	TRzToolButton *tlbtn8;
	TRzToolButton *tlbtn1;
	TRzToolButton *tlbtn2;
	TRzToolButton *tlbtn3;
	TRzToolButton *tlbtn7;
	TRzToolButton *BtnNew;
	TRzToolButton *BtnView;
	TRzToolButton *BtnAttachFiles;
	TRzToolButton *BtnAlignBottom;
	TRzToolButton *BtnPrint;
	TGroupBox *grpbxNtHeader;
	TRzLabel *lbl2;
	TRzLabel *lbl4;
	TSpeedButton *RzButton1;
	TRzLabel *RzLabel3;
	TRzLabel *RzLabel8;
	TRzLabel *RzLabel9;
	TRzLabel *RzLabel11;
	TRzLabel *RzLabel12;
	TRzLabel *RzLabel13;
	TRzDBEdit *dbedtRetailNtCode;
	TEdit *edname;
	TEdit *edyue;
	TDBNavigator *dbhd;
	TEdit *edcard;
	TEdit *edtype;
	TEdit *edjifen;
	TEdit *edTotalConsumption;
	TEdit *edyouxiaodate;
	TRzDBGrid *dbgrdNote;
	TLabel *Label1;
	TRzLabel *lbl8;
	TRzLabel *lbl9;
	TRzLabel *lblCatalog;
	TRzEdit *edtCatalog;
	TCheckBox *chdingwei;
	TLabel *Label2;
	TLabel *Label4;
	TADOConnection *adocon;
	TDataSource *ds;
	TADOQuery *aq;
	TDataSource *dsourceheader;
	TRzNumericEdit *numorder;
	TADOStoredProc *adosp;
	TADOQuery *adoaqnote;
	TPopupMenu *pm;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TMenuItem *N4;
	TMenuItem *N13;
	TADOQuery *aqheader;
	TEdit *dbnbedtAmount;
	TEdit *dbnbedtDiscount;
	TMemo *membk;
	TRzToolButton *RzToolButton1;
	TEdit *Edit1;
	TLabel *Label3;
	TfrxReport *frxmemberorder;
	TfrxDBDataset *frxdetail;
	TRzToolButton *RzToolButton2;
	TRzNumericEdit *Edit2;
	TRzNumericEdit *Edit3;
	void __fastcall edcardKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall tlbtn1Click(TObject *Sender);
	void __fastcall edtCatalogKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall lblCatalogMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall N3Click(TObject *Sender);
	void __fastcall N4Click(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall tlbtn7Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall BtnNewClick(TObject *Sender);
	void __fastcall dbnbedtAmountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dbnbedtDiscountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dbgrdNoteCellClick(TColumn *Column);
	void __fastcall tlbtn2Click(TObject *Sender);
	void __fastcall BtnAttachFilesClick(TObject *Sender);
	void __fastcall RzButton1Click(TObject *Sender);
	void __fastcall tlbtn3Click(TObject *Sender);
	void __fastcall tlbtn8Click(TObject *Sender);
	void __fastcall dbhdClick(TObject *Sender, TNavigateBtn Button);
	void __fastcall numorderKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall RzToolButton1Click(TObject *Sender);
	void __fastcall BtnPrintClick(TObject *Sender);
	void __fastcall frxmemberorderGetValue(const UnicodeString VarName, Variant &Value);
	void __fastcall RzToolButton2Click(TObject *Sender);
	void __fastcall BtnViewClick(TObject *Sender);

private:	// User declarations
       int MemberID ;
       int StgID;
       int UserID;
       int m_catalogSearchMode;
       TADOConnection *fcn;
       float olderordermondy;

public:		// User declarations
	__fastcall Tfrmmemberorder(TComponent* Owner);

        void AddNote(int ai,int bkcatalogid);
        void RefreshDetail();
        void init(TADOConnection *cn,int auserid,int astgid);
        void ChangeCatalogSearchMode();
        void UpdateNote(int amount,int discount);
        void BatchSetNotes(int amount,float discount,int type,AnsiString strid );
        void refreshmember();
        void buttonstate(int type);
        bool modyoradd;
        AnsiString pxbk,printtitle,contact,tel,address,riqi;
        void print(int type);
        void GetTotal();

};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmmemberorder *frmmemberorder;
//---------------------------------------------------------------------------
#endif
