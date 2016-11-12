//---------------------------------------------------------------------------

#ifndef unitinorderfenfaH
#define unitinorderfenfaH
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
#include "RzPanel.hpp"
#include <ImgList.hpp>
#include "RzButton.hpp"
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class Tfrmunitinorder : public TForm
{
__published:	// IDE-managed Components
	TADOConnection *fcon;
	TDataSource *ds;
	TADOQuery *query;
	TImageList *ImageList1;
	TADOCommand *cmdAddNote;
	TSaveDialog *savedlg;
	TDBGrid *DBGrid1;
	TRzToolbar *RzToolbar1;
	TRzToolButton *BtnLastRecord;
	TRzToolButton *BtnSave;
	TRzToolButton *BtnDeleteRecord;
	TRzToolButton *BtnDelete;

	void __fastcall BtnLastRecordClick(TObject *Sender);
	void __fastcall BtnExportClick(TObject *Sender);
	void __fastcall BtnSaveClick(TObject *Sender);
	void __fastcall BtnDeleteClick(TObject *Sender);
	void __fastcall BtnDeleteRecordClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmunitinorder(TComponent* Owner,TADOConnection *con,int headerid,int stgid);
	int fstgid,userid,hdid,sgfirsthid;
	AnsiString returncode,sgheaderid,rkcode;
	bool DbgridToExcel(TDBGrid* dbg);
	void __fastcall DBGrid1DrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol,
		  TColumn *Column, Grids::TGridDrawState State);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmunitinorder *frmunitinorder;
//---------------------------------------------------------------------------
#endif
