//---------------------------------------------------------------------------

#ifndef StockalarmSetH
#define StockalarmSetH
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
#include <Menus.hpp>
#include "RzDBGrid.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <Mask.hpp>
#include "global.h"
//---------------------------------------------------------------------------
class TfrmalarmSet : public TForm
{
__published:	// IDE-managed Components
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnExit;
	TDataSource *ds;
	TADOQuery *aquery;
	TADOQuery *aquerydisplay;
	TADOStoredProc *adosp;
	TRzToolButton *BtnAlignBottom;
	TRzToolButton *BtnView;
	TRzDBGrid *dgalarmlist;
	TGroupBox *GroupBox3;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label9;
	TCheckBox *chisbn;
	TMaskEdit *edtmax;
	TMaskEdit *edtmin;
	TCheckBox *cball;
	TGroupBox *GroupBox2;
	TCheckBox *chname;
	TCheckBox *chtype;
	TCheckBox *chpress;
	TCheckBox *chsupplier;
	TEdit *edtisbn;
	TEdit *edname;
	TEdit *edtype;
	TEdit *edsupplier;
	TEdit *edpress;
	TEdit *Edit6;
	TEdit *Edit1;
	TEdit *Edit2;
	TComboBox *cbtype;
	TComboBox *cbpress;
	TComboBox *cbsupplier;
	TRzButton *RzButton2;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall dgalarmlistCellClick(TColumn *Column);
	void __fastcall edtminKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall edtmaxKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall RzButton2Click(TObject *Sender);
	void __fastcall edtisbnChange(TObject *Sender);
	void __fastcall edtisbnKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall ednameChange(TObject *Sender);
	void __fastcall ednameKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtypeKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edsupplierKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edpressKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbtypeChange(TObject *Sender);
	void __fastcall cbtypeKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbpressChange(TObject *Sender);
	void __fastcall cbpressKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbsupplierChange(TObject *Sender);
	void __fastcall cbsupplierKeyPress(TObject *Sender, wchar_t &Key);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmalarmSet(TComponent* Owner,TADOConnection* con,int stgid,int userid);
	int fstgid;
	void search();
	void ReadyData();
	AnsiString sqlwhere;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmalarmSet *frmalarmSet;
//---------------------------------------------------------------------------
#endif
