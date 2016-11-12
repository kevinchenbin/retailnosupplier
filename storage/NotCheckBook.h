//---------------------------------------------------------------------------

#ifndef NotCheckBookH
#define NotCheckBookH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include "RzDBGrid.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "global.h"
//---------------------------------------------------------------------------
class TfrmNotCheckBook : public TForm
{
__published:	// IDE-managed Components
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnExit;
	TRzToolButton *BtnPreviewNextPage;
	TRzToolButton *BtnImport;
	TADOQuery *ADOQuery1;
	TDataSource *ds;
	TRzDBGrid *RzDBGrid1;
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall BtnImportClick(TObject *Sender);
	void __fastcall BtnPreviewNextPageClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmNotCheckBook(TComponent* Owner,TADOQuery *aquery);
	bool __fastcall DbgridToExcel(TRzDBGrid* dbg);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmNotCheckBook *frmNotCheckBook;
//---------------------------------------------------------------------------
#endif
