//---------------------------------------------------------------------------

#ifndef UnitmuilprintH
#define UnitmuilprintH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Unitorderquery.h"
#include <ADODB.hpp>
#include <ComCtrls.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class Tfrmorderquery1 : public Tfrmorderquery
{
__published:	// IDE-managed Components
	TButton *Button3;
	TEdit *edittotal;
	TLabel *Label2;
	TLabel *Label3;
	TEdit *editshe;
	TLabel *Label4;
	TEdit *editzhi;
	TLabel *Label5;

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
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmorderquery1(TComponent* Owner,TADOConnection *con,int stgid,int modle,int tuihuo,AnsiString ausername,bool qfclient);
        	int fstgid,ftuihuo,fmodle; //1为订单，2为发货单
	int  ClientID;
	AnsiString GetNoteCode();
	bool ChangeDisplay;
	AnsiString sqlwhere;
	AnsiString GetWhere();
        void enableshenghe();
        void enablefahuofangshi();
        TBookmark bm;
        AnsiString clientname,headerid,fusername;
        bool printnow;
        int version;
        bool fqfclient;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmorderquery1 *frmorderquery1;
//---------------------------------------------------------------------------
#endif
