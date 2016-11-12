//---------------------------------------------------------------------------

#ifndef storagebssetH
#define storagebssetH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ADODB.hpp>
#include <Buttons.hpp>
#include <DB.hpp>
#include "pdtypes.h"
#include <DBGrids.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class Tfrmstoragebsset : public TForm
{
__published:	// IDE-managed Components
	TADOQuery *aquery;
	TADOQuery *qryretairange;
	TDataSource *dsrcretairange;
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *½øÍË»õÃ÷Ï¸;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label8;
	TCheckBox *cbsameid;
	TCheckBox *cborder;
	TCheckBox *cbauto;
	TCheckBox *cbtrace;
	TEdit *etdot;
	TCheckBox *cbstoragehistory;
	TEdit *edstorageday;
	TCheckBox *cbadddotenable;
	TCheckBox *cblastyjpxdiscount;
	TCheckBox *cblastyjpx;
	TCheckBox *cbadddot;
	TCheckBox *cbrkallsupplier;
	TCheckBox *cbrkusefind;
	TCheckBox *cbrkusedelete;
	TCheckBox *cbrkusetuihuo;
	TCheckBox *chmutisupplier;
	TCheckBox *chdeletestack;
	TEdit *edmonth;
	TGroupBox *GroupBox4;
	TGroupBox *GroupBox5;
	TCheckBox *cbrkusechange;
	TGroupBox *GroupBox3;
	TCheckBox *cblastyjlsdiscount;
	TCheckBox *chstoragesametishi;
	TCheckBox *chrktuihuoguanli;
	TEdit *edtkmouth;
	TGroupBox *GroupBox2;
	TRadioGroup *rg;
	TCheckBox *chcrtuserbarcode;
	TSpeedButton *sbcancel;
	TSpeedButton *sbok;
	TComboBox *cbtuihuo;
	TComboBox *cbyouxian;
	TSpeedButton *sbsettuihuozhouqi;
	TSpeedButton *sbset;
	TCheckBox *cbcaigoucayi;
	TCheckBox *cbsamerkyx;
	TCheckBox *cbsamerkts;
	TCheckBox *cbcaigoudiscount;
	TCheckBox *cbrukufeishendaicaigou;
	TCheckBox *cbqfsupplier;
	TCheckBox *cbqfclient;
	void __fastcall sbokClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall sbcancelClick(TObject *Sender);
	void __fastcall cblastyjpxClick(TObject *Sender);
	void __fastcall cbadddotClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall sbsettuihuozhouqiClick(TObject *Sender);
	void __fastcall sbsetClick(TObject *Sender);
private:	// User declarations
TADOConnection* fcon;
int fstgid;
public:		// User declarations
	__fastcall Tfrmstoragebsset(TComponent* Owner,TADOConnection* con,int stgid);
	void Readydata();
        int version;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmstoragebsset *frmstoragebsset;
//---------------------------------------------------------------------------
#endif
