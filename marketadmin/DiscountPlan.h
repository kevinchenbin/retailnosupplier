//---------------------------------------------------------------------------

#ifndef DiscountPlanH
#define DiscountPlanH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include "RzCmboBx.hpp"
#include "RzRadChk.hpp"
#include "RzEdit.hpp"
#include <Mask.hpp>
#include "RzDTP.hpp"
#include <ComCtrls.hpp>
#include "RzDBGrid.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
struct Nodedata
{
	int ID;
	int PrentID;
	AnsiString Name;
	AnsiString code;
	AnsiString bk;
	int state;
};
class TFormDiscount : public TForm
{
__published:	// IDE-managed Components
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnExit;
	TDataSource *ds1;
	TADOQuery *querydetail;
	TADOQuery *query;
	TPopupMenu *PopupMenu;
	TMenuItem *Ndelete;
	TRzToolButton *BtnAlignBottom;
	TComboBox *cbstgid;
	TRzDBGrid *dbgdiscount;
	TLabel *Label10;
	TTreeView *tvbookclass;
	TEdit *edtypename;
	TLabel *Labelname;
	TLabel *Label4;
	TLabel *Label9;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label5;
	TEdit *eddiscount;
	TDateTimePicker *dtpstart;
	TDateTimePicker *dtpend;
	TComboBox *cbmembertype;
	TRzButton *RzButton1;
	TRzButton *RzButton2;
	TMenuItem *N1;
	void __fastcall dbgdiscountCellClick(TColumn *Column);
	void __fastcall NdeleteClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall eddiscountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall cbstgidSelect(TObject *Sender);
	void __fastcall RzButton2Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall tvbookclassMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall tvbookclassMouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall RzButton1Click(TObject *Sender);
	void __fastcall edtypenameKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall RzButton1KeyPress(TObject *Sender, wchar_t &Key);

private:	// User declarations
	int correntdiscount;
	int type;
	int fstgid;

	TStringList *ClassType;
	TStringList *TypeName;
   	TStringList *TypeCode;

public:		// User declarations
	__fastcall TFormDiscount(TComponent* Owner);
	void Init(TApplication* app, TADOConnection* con,int stgid);
	TADOConnection *cn;
	void __fastcall disable();
	TTreeNode *ClickNode;
	bool NodeChecked;
	bool GetNodeChecked(TTreeNode *ANode);
	void SetChildChecked(TTreeNode *ANode,bool yn);
	void SetNodeChecked(TTreeNode *ANode,bool IsSetToChecked);
	void GetData();
};
//---------------------------------------------------------------------------
extern PACKAGE TFormDiscount *FormDiscount;
//---------------------------------------------------------------------------
#endif
