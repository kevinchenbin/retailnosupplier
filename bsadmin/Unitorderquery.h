//---------------------------------------------------------------------------

#ifndef UnitorderqueryH
#define UnitorderqueryH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include "global.h"
#include <Menus.hpp>
//---------------------------------------------------------------------------
class Tfrmorderquery : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TDateTimePicker *dtpstart;
	TCheckBox *chstart;
	TDateTimePicker *dtpend;
	TCheckBox *chend;
	TCheckBox *chclient;
	TEdit *edclient;
	TCheckBox *chcode;
	TEdit *edcode;
	TADOConnection *fcon;
	TDBGrid *DBGrid1;
	TDataSource *ds;
	TADOQuery *query;
	TButton *Button1;
	TButton *Button2;
	TCheckBox *chinorder;
	TComboBox *cbclient;
	TCheckBox *cbshenghe;
	TCheckBox *cbweisheng;
	TEdit *editcode2;
	TLabel *Label1;
	TComboBox *cbfahuofashi;
	TCheckBox *checkfahuofashi;
	TPopupMenu *PopupMenu1;
	TMenuItem *A1;
	TMenuItem *P1;
	TCheckBox *cbchao;
	TComboBox *cboperator;
	TMenuItem *N1;
	TMenuItem *N2;
	TEdit *editorderbk;
	TCheckBox *cborderbk;
	void __fastcall edclientKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall DBGrid1DblClick(TObject *Sender);
	void __fastcall DBGrid1KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dtpstartChange(TObject *Sender);
	void __fastcall dtpendChange(TObject *Sender);
	void __fastcall edcodeChange(TObject *Sender);
	void __fastcall cbclientClick(TObject *Sender);
	void __fastcall cbclientChange(TObject *Sender);
	void __fastcall cbfahuofashiChange(TObject *Sender);
	void __fastcall A1Click(TObject *Sender);
	void __fastcall P1Click(TObject *Sender);
	void __fastcall cboperatorChange(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall editorderbkChange(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
        TADOConnection *acon;
public:		// User declarations
	__fastcall Tfrmorderquery(TComponent* Owner,TADOConnection *con,int stgid,int modle,int tuihuo,AnsiString UserName,bool qufengclient);
	int fstgid,ftuihuo,fmodle; //1为订单，2为发货单
        AnsiString fusername;
	int  ClientID;
	AnsiString GetNoteCode();
	bool ChangeDisplay;
	AnsiString sqlwhere;
	AnsiString GetWhere();
        void enableshenghe();
        void enablefahuofangshi();
        TBookmark bm;
        AnsiString clientname,headerid;
        bool printnow;
        int fversion;
        bool qfclient;

};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmorderquery *frmorderquery;
//---------------------------------------------------------------------------
#endif
