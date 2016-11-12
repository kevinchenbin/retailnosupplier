//---------------------------------------------------------------------------

#ifndef RkFenfaH
#define RkFenfaH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class TfrmRkFenfa : public TForm
{
__published:	// IDE-managed Components
	TImageList *ImageList1;
	TDataSource *ds;
	TADOConnection *fcon;
	TADOQuery *query;
	TRzToolbar *RzToolbar1;
	TRzToolButton *BtnSave;
	TRzToolButton *BtnLastRecord;
	TRzToolButton *BtnExit;
	TADOCommand *cmdAddNote;
	TComboBox *cbstorage;
	TDBGrid *DBGrid1;
	TEdit *edamount;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TRzToolButton *BtnNew;
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall BtnSaveClick(TObject *Sender);
	void __fastcall edamountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnLastRecordClick(TObject *Sender);
	void __fastcall cbstorageSelect(TObject *Sender);
	void __fastcall queryAfterPost(TDataSet *DataSet);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnNewClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);

private:	// User declarations
public:		// User declarations
	__fastcall TfrmRkFenfa(TComponent* Owner,TADOConnection *con,int userid,int stgid);
	int fuserid,fstgid;
	AnsiString CodeStr,stgstr,stkstgstr;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmRkFenfa *frmRkFenfa;
//---------------------------------------------------------------------------
#endif
