//---------------------------------------------------------------------------

#ifndef BooKTypeAdminFormH
#define BooKTypeAdminFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzLstBox.hpp"
#include "RzTreeVw.hpp"
#include <ComCtrls.hpp>
#include "RzListVw.hpp"
#include "RzDBList.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "RzButton.hpp"
#include "RzDBEdit.hpp"
#include "RzEdit.hpp"
#include <Mask.hpp>
#include "RzDBGrid.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include "RpCon.hpp"
#include "RpConDS.hpp"
#include "RpDefine.hpp"
#include "RpRave.hpp"
#include "pdutil.h"
#include "MDIChild.h"
#include <ImgList.hpp>
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
class TfrmBookTypeAdmin : public TForm//TfrmMDIChild
{
__published:	// IDE-managed Components
	TRzToolbar *rztlbr2;
	TRzToolButton *btnExit1;
	TRzToolButton *btnExit2;
	TRzToolButton *btnExit3;
	TRzToolButton *RzToolButton1;
	TDataSource *dsource;
	TADODataSet *dsetBookType;
	TImageList *ImageList1;
	TRzToolButton *rtbmodify;
	TRzToolButton *BtnSave;
	TADOQuery *aqbookclass;
	TADOQuery *aquery;
	TADOStoredProc *dsp;
	TRzToolButton *BtnAlignBottom;
	TSplitter *Splitter1;
	TTreeView *tvbookclass;
	TLabel *lbl2;
	TLabel *Label1;
	TLabel *Label2;
	TEdit *edtback;
	TEdit *edtname;
	TEdit *ettypenum;
	TLabel *Label3;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall btn6Click(TObject *Sender);
	void __fastcall btnExit1Click(TObject *Sender);
	void __fastcall btnExit2Click(TObject *Sender);
	void __fastcall btnExit3Click(TObject *Sender);
	void __fastcall btn1Click(TObject *Sender);
	void __fastcall dbedtCodeKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dbedtTypeNameKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall RzToolButton1Click(TObject *Sender);
	void __fastcall BtnSaveClick(TObject *Sender);
	void __fastcall rtbmodifyClick(TObject *Sender);
	void __fastcall tvbookclassClick(TObject *Sender);
	void __fastcall edtnameKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);

private:	// User declarations
void OnHotKeyPress(DWORD vkCode);
   int Modal;
   TStringList *ClassType;
   TStringList *TypeName;
   TStringList *TypeCode;

public:		// User declarations
	__fastcall TfrmBookTypeAdmin(TComponent* Owner);
	void Init(TApplication* app, TADOConnection* con);
	void Query(String condition);
        bool isSameIDorName(AnsiString str,int type);    //¼ì²éÃû×Ö type = 1
        void ModifyInfo(AnsiString oldstr,AnsiString newstr,int type,int Operation);
        int GetSelecedNodeID();

};
//---------------------------------------------------------------------------
extern PACKAGE TfrmBookTypeAdmin *frmBookTypeAdmin;
//---------------------------------------------------------------------------
#endif
