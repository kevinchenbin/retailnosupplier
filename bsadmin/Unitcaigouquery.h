//---------------------------------------------------------------------------

#ifndef UnitcaigouqueryH
#define UnitcaigouqueryH
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
#include <Menus.hpp>
//---------------------------------------------------------------------------
class Tfrmcaigouquery : public TForm
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
	TComboBox *cbsupplier;
	TCheckBox *cbyangshu;
	TComboBox *cbrukuleixing;
	TEdit *editbk;
	TCheckBox *cbrkbz;
	TEdit *editrkbk;
	TPopupMenu *PopupMenu1;
	TMenuItem *N1;
	void __fastcall edclientKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall DBGrid1DblClick(TObject *Sender);
	void __fastcall DBGrid1KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dtpstartChange(TObject *Sender);
	void __fastcall dtpendChange(TObject *Sender);
	void __fastcall cbsupplierChange(TObject *Sender);
	void __fastcall edcodeChange(TObject *Sender);
	void __fastcall cbrukuleixingChange(TObject *Sender);
	void __fastcall editbkChange(TObject *Sender);
	void __fastcall editrkbkChange(TObject *Sender);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmcaigouquery(TComponent* Owner,TADOConnection *con,int stgid,int modle,int tuihuo,bool qfsupplier);
	int fstgid,ftuihuo,fmodle;  //1为采购,2为入库
	int  ClientID;
	AnsiString GetNoteCode();
	bool ChangeDisplay;
	AnsiString GetWhere();
	AnsiString sqlwhere;
        void showstate();
        void disvialetype();
        void rkshowbeizhu();
        int version;
        bool fqfsupplier;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmcaigouquery *frmcaigouquery;
//---------------------------------------------------------------------------
#endif
