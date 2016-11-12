//---------------------------------------------------------------------------

#ifndef RetailNoteFormH
#define RetailNoteFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzChkLst.hpp"
#include "RzDBEdit.hpp"
#include "RzDBList.hpp"
#include "RzEdit.hpp"
#include "RzLabel.hpp"
#include "RzLstBox.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <Mask.hpp>
#include "RzLine.hpp"
#include "RzCmboBx.hpp"
#include "RzDBCmbo.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include "RzButton.hpp"
#include "RzDBChk.hpp"
#include "RzRadChk.hpp"
#include <ComCtrls.hpp>
#include <Grids.hpp>
#include "MDIChild.h"
#include "RzBckgnd.hpp"
#include "frxClass.hpp"
//---------------------------------------------------------------------------
class TfrmRetailNote : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TADOQuery *qryRetailNoteName;
	TDataSource *Ds1;
	TDataSource *dsNotePrint;
	TADODataSet *dsetRetailNote;
	TDataSource *ds2;
	TADODataSet *dsPrint;
	TADODataSet *dsretail;
	TDataSource *ds4;
	TADOConnection *con;
	TLabel *Label3;
	TLabel *labstorage;
	TRzGroupBox *RzGroupBox4;
	TRzLabel *RzLabel1;
	TRzLabel *RzLabel3;
	TRzLabel *RzLabel4;
	TRzLabel *RzLabel5;
	TRzLine *RzLine1;
	TRzLabel *RzLabel6;
	TRzLabel *RzLabel7;
	TRzLabel *lbl1;
	TRzDBEdit *dbedtWelcomeMessage;
	TRzDBEdit *dbedtAddress;
	TRzDBEdit *dbedtTel;
	TRzDBEdit *dbedtRemarks;
	TRzDBCheckBox *CHKPrice;
	TRzDBCheckBox *CHKBookName;
	TRzDBCheckBox *CHKDiscount;
	TButton *btn1;
	TButton *btn2;
	TRzDBCheckBox *CHKtotalamount;
	TRzDBCheckBox *CHKjine;
	TRzDBCheckBox *CHKCardrec;
	TRzDBCheckBox *CHKtotalhang;
	TButton *Button2;
	TComboBox *dbcbbPort;
	TRzDBCheckBox *chprintmayang;
	TRzDBCheckBox *chprintdiscount;
	TRzDBCheckBox *chkpostcard;
	TRzDBCheckBox *chkyouhuiquan;
	TRadioGroup *rgtype;
	TRzDBCheckBox *chprintjifen;
	TRzDBCheckBox *chprintcard;
	TRzDBCheckBox *chprintname;
	TRzDBCheckBox *chjiaojieprint;
	TRzDBCheckBox *chprint;
	TButton *btn3;
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TLabel *Label2;
	TRadioGroup *rg1;
	TButton *Button3;
	TComboBox *cbcomnum;
	TCheckBox *ch1;
	TEdit *edtest;
	TCheckBox *chyuying;
	TfrxReport *frxretail;
	TGroupBox *GroupBox2;
	TComboBox *cbmoneybox;
	TLabel *Label4;
	TLabel *Label5;
	TButton *Button1;
	TComboBox *cbinterfacetype;
	TCheckBox *cbopenmoneybox;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall btn1Click(TObject *Sender);
	void __fastcall btn2Cick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall cbcomnumChange(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall btn3Click(TObject *Sender);
	void __fastcall cbmoneyboxChange(TObject *Sender);



private:	// User declarations
              TStringList *strlistusb;
public:		// User declarations
	__fastcall TfrmRetailNote(TComponent* Owner);
		void Init(TApplication* app, TADOConnection* cn);
		void print();
                AnsiString printcount;
                AnsiString aGetUSBInfos();
                void OpenMoneyBoxUSB(AnsiString USBInfoOpenBOX);
             //   void __fastcall WndProc(TMessage &Msg);
   int stgid;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmRetailNote *frmRetailNote;
//---------------------------------------------------------------------------
#endif
