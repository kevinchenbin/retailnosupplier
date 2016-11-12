//---------------------------------------------------------------------------

#ifndef catalognewandrecH
#define catalognewandrecH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include "RzButton.hpp"
#include "DBGridEh.hpp"
#include "GridsEh.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include <Dialogs.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class Tfrmcatalognewrecoment : public TForm
{
__published:	// IDE-managed Components
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnView;
	TRzToolButton *BtnExit;
	TADOQuery *aq;
	TADOQuery *query;
	TDataSource *ds;
	TRzToolButton *BtnExport;
	TRzToolButton *BtnAlignBottom;
	TSaveDialog *savedlg;
	TRzToolButton *BtnSave;
	TADOConnection *fcon;
	TDBGridEh *DBGridEh1;
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TRadioGroup *rg;
	TCheckBox *chisbn;
	TEdit *edisbn;
	TCheckBox *chname;
	TEdit *edname;
	TCheckBox *chuserdef;
	TCheckBox *chauthor;
	TCheckBox *chprice;
	TEdit *edauthor;
	TEdit *edminprice;
	TEdit *edmaxprice;
	TEdit *eduserdef;
	TCheckBox *chtype;
	TCheckBox *chpress;
	TComboBox *cbpress;
	TEdit *edquery;
	TCheckBox *chbookinfo;
	TSpeedButton *SpeedButton1;
	TEdit *edtyname;
	TEdit *edpyquery;
	TCheckBox *cboxshengdai;
	TComboBox *cbshendai;
	TCheckBox *cbbeizhu;
	TEdit *editbk;
	TCheckBox *cbname;
	TComboBox *cbjianshuo;
	TRzToolButton *RzToolButton1;
	void __fastcall edqueryKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall edminpriceKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edmaxpriceKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall BtnExportClick(TObject *Sender);
	void __fastcall edisbnChange(TObject *Sender);
	void __fastcall edauthorChange(TObject *Sender);
	void __fastcall ednameChange(TObject *Sender);
	void __fastcall eduserdefChange(TObject *Sender);
	void __fastcall cbpressChange(TObject *Sender);
	void __fastcall edminpriceChange(TObject *Sender);
	void __fastcall edmaxpriceChange(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnSaveClick(TObject *Sender);
	void __fastcall DBGridEh1TitleClick(TColumnEh *Column);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall edpyqueryKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall RzToolButton1Click(TObject *Sender);
	void __fastcall cbjianshuoChange(TObject *Sender);
private:	// User declarations
        AnsiString fname;
public:		// User declarations
	__fastcall Tfrmcatalognewrecoment(TComponent* Owner,TADOConnection *con);
	void  Query();
	bool DbgridToExcel(TDBGridEh* dbg);
        bool newDbgridToExcel(TDBGridEh* dbg);
	int TypeID;
        int fstgid;
        int fuserid;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmcatalognewrecoment *frmcatalognewrecoment;
//---------------------------------------------------------------------------
#endif
