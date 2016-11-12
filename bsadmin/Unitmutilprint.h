//---------------------------------------------------------------------------

#ifndef UnitmutilprintH
#define UnitmutilprintH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "RzButton.hpp"
#include "RzDBGrid.hpp"
#include "RzPanel.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ComCtrls.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class Tfrmmembersearch : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TRzDBGrid *dbgrid;
	TDateTimePicker *dtpstart;
	TCheckBox *chstart;
	TDateTimePicker *dtpend;
	TCheckBox *chend;
	TCheckBox *chclient;
	TEdit *edclient;
	TCheckBox *chcode;
	TEdit *edcode;
	TButton *Button1;
	TButton *Button2;
	TComboBox *cbsupplier;
	TEdit *encodeend;
	TLabel *Label1;
	TADOQuery *aqquery;
	TDataSource *ds;
	TADOConnection *fcn;
	void __fastcall edclientKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall dbgridDblClick(TObject *Sender);
	void __fastcall dtpstartChange(TObject *Sender);
	void __fastcall dtpendChange(TObject *Sender);
	void __fastcall edclientChange(TObject *Sender);
	void __fastcall edcodeChange(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmmembersearch(TComponent* Owner,TADOConnection *con,int stgid);
        AnsiString Getsql();
        AnsiString  sql;
	AnsiString sqlwhere;
        AnsiString GetNoteCode();

        int fstgid;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmmembersearch *frmmembersearch;
//---------------------------------------------------------------------------
#endif
