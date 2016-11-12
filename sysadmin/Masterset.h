//---------------------------------------------------------------------------

#ifndef MastersetH
#define MastersetH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "DBGridEh.hpp"
#include "GridsEh.hpp"
#include "RzButton.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class TfrmMasterset : public TForm
{
__published:	// IDE-managed Components
	TPanel *pan1;
	TRzButton *btok;
	TRzButton *btconcel;
	TADOConnection *cn;
	TDataSource *ds;
	TADOQuery *aq;
	TADOQuery *query;
	TLabel *label1;
	TEdit *edname;
	TLabel *Label2;
	TComboBox *cbname;
	void __fastcall btokClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall btconcelClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmMasterset(TComponent* Owner,TADOConnection *con);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMasterset *frmMasterset;
//---------------------------------------------------------------------------
#endif
