//---------------------------------------------------------------------------

#ifndef catalognewandrecH
#define catalognewandrecH
#include "pdtypes.h"
#include "MDIChild.h"
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
#include "RzDBGrid.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include "RzDTP.hpp"
#include <ComCtrls.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class Tfrmcatalogneworrec : public TForm
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
	TRzDBGrid *RzDBGrid1;
	TCheckBox *cbruku;
	TRzDateTimePicker *dtpbegin;
	TLabel *Label2;
	TRzDateTimePicker *dtpend;
	TGroupBox *GroupBox2;
	TSpeedButton *sbcreatewsale;
	TLabel *Label3;
	TADOQuery *adoexec;
	TEdit *editclientname;
	TComboBox *cbclient;
	TPopupMenu *PopupMenu1;
	TMenuItem *N1;
	TMenuItem *N2;
	TCheckBox *cbbufahuo;
	TLabel *Label4;
	TCheckBox *cbkuchen;
	TEdit *edit1;
	TEdit *edit2;
	TLabel *Label5;
	TCheckBox *cbbk;
	TEdit *editbk;
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
	void __fastcall sbcreatewsaleClick(TObject *Sender);
	void __fastcall editclientnameKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall cbclientChange(TObject *Sender);
	void __fastcall rgClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
 bool createproc();
       LandInfo linfo;
public:		// User declarations
	__fastcall Tfrmcatalogneworrec(TComponent* Owner,TADOConnection *con);
	void  Query();
	bool DbgridToExcel(TRzDBGrid* dbg);
	int TypeID;
        void ReadyData();
          int fstgid,fuserid,clientid;
          AnsiString returncode,returncodeint,oldcode;

          void init(LandInfo* li);

};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmcatalogneworrec *frmcatalogneworrec;
//---------------------------------------------------------------------------
#endif
