//---------------------------------------------------------------------------

#ifndef QryCodeFormH
#define QryCodeFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include "RzButton.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class TfrmQryCode : public TForm
{
__published:	// IDE-managed Components
	TCheckBox *ch1;
	TCheckBox *ch2;
	TDateTimePicker *dtp1;
	TDateTimePicker *dtp2;
	TRzButton *RzButton1;
	TDBGrid *DBGrid1;
	TADOConnection *fcon;
	TDataSource *ds;
	TADOQuery *query;
	void __fastcall RzButton1Click(TObject *Sender);
	void __fastcall DBGrid1DblClick(TObject *Sender);
	void __fastcall DBGrid1KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dtp1Change(TObject *Sender);
	void __fastcall dtp2Change(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmQryCode(TComponent* Owner,TADOConnection *con,int stgid,int mode,int type);
	int fstgid,fmode,ftype;
	AnsiString sqlwhere;
	AnsiString GetNoteCode();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmQryCode *frmQryCode;
//---------------------------------------------------------------------------
#endif
