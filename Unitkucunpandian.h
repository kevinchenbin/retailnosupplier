//---------------------------------------------------------------------------

#ifndef UnitkucunpandianH
#define UnitkucunpandianH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <DB.hpp>
#include <ADODB.hpp>
//---------------------------------------------------------------------------
class Tfrmkucunpandian : public TForm
{
__published:	// IDE-managed Components
	TDataSource *ds;
	TADOQuery *query;
	TDBGrid *DBGrid1;
	void __fastcall DBGrid1DblClick(TObject *Sender);
	void __fastcall DBGrid1KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmkucunpandian(TComponent* Owner,TADOQuery *aq);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmkucunpandian *frmkucunpandian;
//---------------------------------------------------------------------------
#endif
