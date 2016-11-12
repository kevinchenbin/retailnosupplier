//---------------------------------------------------------------------------

#ifndef bookQueryH
#define bookQueryH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include "RzEdit.hpp"
#include "RzLabel.hpp"
#include <Mask.hpp>
#include <Menus.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <Buttons.hpp>
#include "global.h"
//---------------------------------------------------------------------------
class Tfrmbookquery : public TForm
{
__published:	// IDE-managed Components
	TImageList *ImageList1;
	TPopupMenu *pm;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TMenuItem *N4;
	TDataSource *ds;
	TADOQuery *aq;
	TMenuItem *N5;
	TADOQuery *query;
	TDBGrid *DBGrid1;
	TGroupBox *GroupBox1;
	TSpeedButton *SpeedButton1;
	TCheckBox *chother;
	TCheckBox *chisbn;
	TRzEdit *edisbn;
	TCheckBox *chname;
	TRzEdit *edname;
	TCheckBox *chuserdefcode;
	TRzEdit *eduserdefcode;
	TCheckBox *chauthor;
	TRzEdit *edauthor;
	TCheckBox *chprice;
	TRzEdit *edprice;
	TCheckBox *chtype;
	TRzEdit *edtype;
	TCheckBox *chpress;
	TRzEdit *edpress;
	TComboBox *cbpress;
	TSpeedButton *SpeedButton2;
	TEdit *edtyname;
	TADOConnection *fcon;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall edpriceKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtypeKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edpressKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edisbnChange(TObject *Sender);
	void __fastcall edisbnKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall ednameKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall ednameChange(TObject *Sender);
	void __fastcall eduserdefcodeChange(TObject *Sender);
	void __fastcall eduserdefcodeKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edpriceChange(TObject *Sender);
	void __fastcall edauthorChange(TObject *Sender);
	void __fastcall edauthorKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbpressChange(TObject *Sender);
	void __fastcall cbpressKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall SpeedButton2Click(TObject *Sender);
	void __fastcall edtynameChange(TObject *Sender);
private:	// User declarations
	int m_catalogSearchMode,m_storageID;
public:		// User declarations
	__fastcall Tfrmbookquery(TComponent* Owner,TADOConnection *cn,int stgid);
	int TypeID;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmbookquery *frmbookquery;
//---------------------------------------------------------------------------
#endif
