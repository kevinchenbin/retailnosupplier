//---------------------------------------------------------------------------

#ifndef diaobosetH
#define diaobosetH
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
#include "RzButton.hpp"
//---------------------------------------------------------------------------
class Tfrmdiaoboset : public TForm
{
__published:	// IDE-managed Components
	TADOQuery *aquery;
	TADOQuery *qryretairange;
	TDataSource *dsrcretairange;
	TLabel *Label3;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label4;
	TRadioGroup *RadioGroup1;
	TEdit *edadddiscount;
	TEdit *eddefaultdiscount;
	TRzButton *RzButton1;
	TRzButton *RzButton2;
	TCheckBox *chpeisongsametishi;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall edadddiscountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall RzButton1Click(TObject *Sender);
	void __fastcall RzButton2Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmdiaoboset(TComponent* Owner,TADOConnection* con);
	void Readydata();
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmdiaoboset *frmdiaoboset;
//---------------------------------------------------------------------------
#endif
