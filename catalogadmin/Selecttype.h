//---------------------------------------------------------------------------

#ifndef SelecttypeH
#define SelecttypeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <ImgList.hpp>
//---------------------------------------------------------------------------
struct Node
{
  int ID;
  int PrentID;
  AnsiString Name;
};
class Tfrmselecttype : public TForm
{
__published:	// IDE-managed Components
	TADOQuery *ADOQuery1;
	TImageList *ImageList1;
	TTreeView *tvclient;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall tvclientMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall tvclientDblClick(TObject *Sender);
	void __fastcall tvclientKeyPress(TObject *Sender, wchar_t &Key);
private:	// User declarations
	TADOConnection *fcon;
	AnsiString SelectClientName;
	int Typeid;
	TTreeNode *ClickNode; // ������еĽڵ�;
public:		// User declarations
	__fastcall Tfrmselecttype(TComponent* Owner,TADOConnection *con,AnsiString sqlwhere);
	void ShowClient();
	AnsiString GetSelect();
	AnsiString where;
	int GetSelectID();
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmselecttype *frmselecttype;
//---------------------------------------------------------------------------
#endif
