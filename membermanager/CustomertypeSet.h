//---------------------------------------------------------------------------

#ifndef CustomertypeSetH
#define CustomertypeSetH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "global.h"
//---------------------------------------------------------------------------
class Tfrmcustomertype : public TForm
{
__published:	// IDE-managed Components
	TRzToolbar *RzToolbar1;
	TImageList *imagelistmemcardclass;
	TRzToolButton *BtnAdd;
	TRzToolButton *BtnDelete;
	TRzToolButton *BtnExit;
	TADOQuery *quMemberType;
	TRzToolButton *BtnChangeOptions;
	TRzToolButton *BtnSave;
	TSplitter *Splitter1;
	TTreeView *tvMemberType;
	TLabel *Label1;
	TLabel *Label4;
	TEdit *edTypeName;
	TEdit *edMemberID;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall BtnAddClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall BtnDeleteClick(TObject *Sender);
	void __fastcall tvMemberTypeClick(TObject *Sender);
	void __fastcall BtnChangeOptionsClick(TObject *Sender);
	void __fastcall BtnSaveClick(TObject *Sender);
	void __fastcall Changesave();
	void __fastcall Addsave();
	void __fastcall edTypeNameKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);


private:	// User declarations
	TTreeNode * Root;
	int savemodle;
	int type;
        int fstgid;

public:		// User declarations
	__fastcall Tfrmcustomertype(TComponent* Owner,TADOConnection *cnn,int Type,int stgid);
	TStringList * sg;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmcustomertype *frmcustomertype;
//---------------------------------------------------------------------------
#endif
