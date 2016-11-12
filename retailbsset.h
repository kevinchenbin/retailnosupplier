//---------------------------------------------------------------------------

#ifndef retailbssetH
#define retailbssetH
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
class Tfrmretailbsset : public TForm
{
__published:	// IDE-managed Components
	TADOQuery *aquery;
	TADOQuery *qryretairange;
	TDataSource *dsrcretairange;
	TGroupBox *GroupBox2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label10;
	TLabel *Label11;
	TLabel *Label12;
	TLabel *Label13;
	TLabel *Label14;
	TLabel *Label15;
	TLabel *Label16;
	TLabel *Label17;
	TLabel *Label18;
	TLabel *Label19;
	TLabel *Label20;
	TLabel *Label21;
	TLabel *Label22;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label23;
	TCheckBox *cbnosalereturn;
	TEdit *edmin1;
	TEdit *edmax1;
	TEdit *edlost1;
	TEdit *edlost2;
	TEdit *edmax2;
	TEdit *edmin2;
	TEdit *edlost3;
	TEdit *edmax3;
	TEdit *edmin3;
	TEdit *edlost4;
	TEdit *edmax4;
	TEdit *edmin4;
	TEdit *edlost5;
	TEdit *edmax5;
	TEdit *edmin5;
	TCheckBox *cbeffect1;
	TCheckBox *cbeffect2;
	TCheckBox *cbeffect3;
	TCheckBox *cbeffect4;
	TCheckBox *cbeffect5;
	TCheckBox *cbRetailDiscountChange;
	TEdit *etdot;
	TCheckBox *cblsusefind;
	TCheckBox *cblsusedelete;
	TCheckBox *cblsusetuihuo;
	TGroupBox *GroupBox1;
	TCheckBox *chrukuzhekou;
	TCheckBox *chretailbear;
	TCheckBox *chRetaiview;
	TCheckBox *chdanping;
	TCheckBox *chshumutype;
	TCheckBox *chguadan;
	TCheckBox *chretailtuihuan;
	TCheckBox *chretailprice;
	TCheckBox *chguadantishi;
	TCheckBox *chhuanjiapwd;
	TCheckBox *chhuankoupwd;
	TCheckBox *chminlsdiscount;
	TEdit *edlsdiscount;
	TCheckBox *chstorage;
	TSpeedButton *sbcancel;
	TSpeedButton *sbok;
	TComboBox *ch1;
	TComboBox *ch2;
	TComboBox *ch3;
	TComboBox *ch4;
	TLabel *Label24;
	TLabel *Label25;
	TLabel *Label26;
	TCheckBox *chyuying;
	TCheckBox *cbqikan;
	TEdit *editqikan;
	TCheckBox *cbmemberbirsday;
	TCheckBox *cbdiyuchenben;
	TEdit *editdiyuchenben;
	TLabel *Label27;
	TCheckBox *cbrkfj;
	TEdit *yjrkzk;
	TLabel *Label28;
	TCheckBox *cbnosale;
	TEdit *editnosale;
	TLabel *Label29;
	void __fastcall sbokClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall sbcancelClick(TObject *Sender);
	void __fastcall cbeffect1Click(TObject *Sender);
	void __fastcall cbeffect2Click(TObject *Sender);
	void __fastcall cbeffect3Click(TObject *Sender);
	void __fastcall cbeffect4Click(TObject *Sender);
	void __fastcall cbeffect5Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall chguadanClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmretailbsset(TComponent* Owner,TADOConnection* con);
	void Readydata();
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmretailbsset *frmretailbsset;
//---------------------------------------------------------------------------
#endif
