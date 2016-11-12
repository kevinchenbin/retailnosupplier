//---------------------------------------------------------------------------

#ifndef storagelocalH
#define storagelocalH
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
#include "pdtypes.h"
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class Tfrmstorelocal : public TForm
{
__published:	// IDE-managed Components
	TImageList *ImageList1;
	TADOQuery *aquery;
	TADOQuery *aquerylocal;
	TADOStoredProc *adosp;
	TRzToolbar *RzToolbar1;
	TRzToolButton *BtnNew;
	TRzToolButton *BtnDelete;
	TRzToolButton *BtnSave;
	TRzToolButton *BtnExit;
	TRzToolButton *Btnmodify;
	TRzToolButton *BtnAlignBottom;
	TTreeView *tvlocal;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TEdit *edtcode;
	TEdit *edtname;
	TEdit *edtbk;
	void __fastcall BtnNewClick(TObject *Sender);
	void __fastcall BtnSaveClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall tvlocalClick(TObject *Sender);
	void __fastcall BtnmodifyClick(TObject *Sender);
	void __fastcall BtnDeleteClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
	LandInfo  userInfo;
	int OperModal;
public:		// User declarations
	__fastcall Tfrmstorelocal(TComponent* Owner,TADOConnection* con,LandInfo* li);
};
typedef struct NodeData
{
   int SID;
   int LID;
   AnsiString LName,Lbk;
}LNodeData;

typedef struct TNodeData
{
   int SID;
   AnsiString SName;
}SNodeData;

//---------------------------------------------------------------------------
extern PACKAGE Tfrmstorelocal *frmstorelocal;
//---------------------------------------------------------------------------
#endif
