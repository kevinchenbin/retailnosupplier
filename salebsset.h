//---------------------------------------------------------------------------

#ifndef salebssetH
#define salebssetH
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
#include "RzCmboBx.hpp"
//---------------------------------------------------------------------------
class Tfrmsalebsset : public TForm
{
__published:	// IDE-managed Components
	TADOQuery *aquery;
	TADOQuery *qryretairange;
	TDataSource *dsrcretairange;
	TGroupBox *GroupBox1;
	TLabel *Label3;
	TLabel *Label10;
	TRadioGroup *RadioGroup1;
	TCheckBox *cbpxdefaultdiscount;
	TCheckBox *chpxlastdiscount;
	TCheckBox *cbwsaledisscountchange;
	TEdit *eddefaultdiscount;
	TComboBox *cb1;
	TComboBox *cb2;
	TComboBox *cb3;
	TComboBox *cb4;
	TSpeedButton *sbcancel;
	TSpeedButton *sbok;
	TGroupBox *销售业务;
	TLabel *Label23;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label11;
	TLabel *Label12;
	TCheckBox *cbbear;
	TCheckBox *cbwosalehistory;
	TEdit *edwosaleday;
	TCheckBox *cbcheckedview;
	TCheckBox *cbwosalereturn;
	TCheckBox *cblowcostalter;
	TCheckBox *cblownormalalter;
	TCheckBox *cblownormalenable;
	TCheckBox *cblowcostenable;
	TEdit *etdot;
	TCheckBox *cbpxtuihuocatch;
	TCheckBox *chxianchangrecive;
	TCheckBox *cbpxallclientdetail;
	TCheckBox *cbpxdeleteusepassword;
	TCheckBox *cbpxnobkinfosale;
	TCheckBox *cbpxnobkinfotuihuo;
	TCheckBox *cbpxfindusepassword;
	TCheckBox *cbpxtuihuousepassword;
	TCheckBox *chnokucunpxth;
	TEdit *edmonth;
	TCheckBox *chpxusechange;
	TCheckBox *chwsalesametishi;
	TComboBox *cb5;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TCheckBox *chpxclientadddot;
	TCheckBox *chpxrkyjdiscount;
	TCheckBox *chpxaddcost;
	TComboBox *cb6;
	TLabel *Label9;
	TCheckBox *cbpxtuihuo;
	void __fastcall sbokClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall sbcancelClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall eddefaultdiscountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbpxtuihuocatchClick(TObject *Sender);
	void __fastcall etdotExit(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmsalebsset(TComponent* Owner,TADOConnection* con);
	void Readydata();
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmsalebsset *frmsalebsset;
//---------------------------------------------------------------------------
#endif
