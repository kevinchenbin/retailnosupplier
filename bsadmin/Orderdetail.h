//---------------------------------------------------------------------------

#ifndef OrderdetailH
#define OrderdetailH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "RzButton.hpp"
#include "global.h"
//---------------------------------------------------------------------------
class TfrmOrderdetail : public TForm
{
__published:	// IDE-managed Components
	TDataSource *ds;
	TADOQuery *aq;
	TADOConnection *fcon;
	TDBGrid *DBGrid1;
	TRzButton *RzButton1;
	void __fastcall RzButton1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmOrderdetail(TComponent* Owner,TADOConnection *cn,int bkcatalogid,int stgid);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmOrderdetail *frmOrderdetail;
//---------------------------------------------------------------------------
#endif
