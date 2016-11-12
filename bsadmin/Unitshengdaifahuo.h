//---------------------------------------------------------------------------

#ifndef UnitshengdaifahuoH
#define UnitshengdaifahuoH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzDBGrid.hpp"
#include "RzDTP.hpp"
#include <ComCtrls.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <Buttons.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include "pdtypes.h"
#include "MDIChild.h"
#include <Menus.hpp>
//---------------------------------------------------------------------------
class Tfrmshengdaifahuo : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TEdit *edname;
	TCheckBox *cbruku;
	TEdit *eduserdef;
	TEdit *edauthor;
	TCheckBox *chauthor;
	TCheckBox *chuserdef;
	TCheckBox *chname;
	TEdit *edisbn;
	TCheckBox *chisbn;
	TLabel *Label2;
	TRzDBGrid *RzDBGrid1;
	TCheckBox *cbfahuofanshi;
	TComboBox *cbfahuo;
	TSpeedButton *sbsearch;
	TDataSource *ds;
	TADOQuery *aqnote;
	TSpeedButton *SpeedButton1;
	TADOConnection *ado;
	TRzToolbar *rztlbr1;
	TRzToolButton *tlbtn8;
	TRzToolButton *tlbtn1;
	TRzToolButton *tlbtn7;
	TRzToolButton *BtnNew;
	TRzToolButton *BtnView;
	TRzToolButton *BtnAlignBottom;
	TRzToolButton *BtnPrint;
	TADOQuery *aq;
	TADOQuery *adoexec;
	TEdit *editfahuo;
	TLabel *Label1;
	TPopupMenu *PopupMenu1;
	TMenuItem *N1;
	TLabel *Label3;
	TCheckBox *cbrukuselect;
	TDateTimePicker *dtpend;
	TDateTimePicker *dtpstart;
	TDateTimePicker *dtrukubegin;
	TDateTimePicker *rukudateend;
	TRzToolButton *toolshowmainmenu;
	TEdit *editcaigoutotal;
	TEdit *editfahuototal;
	void __fastcall sbsearchClick(TObject *Sender);
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall tlbtn7Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall BtnNewClick(TObject *Sender);
	void __fastcall edisbnChange(TObject *Sender);
	void __fastcall ednameChange(TObject *Sender);
	void __fastcall edauthorChange(TObject *Sender);
	void __fastcall eduserdefChange(TObject *Sender);
	void __fastcall cbfahuoChange(TObject *Sender);
	void __fastcall editfahuoKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall RzDBGrid1CellClick(TColumn *Column);
	void __fastcall tlbtn8Click(TObject *Sender);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall toolshowmainmenuClick(TObject *Sender);
private:	// User declarations
  int StgID;
    LandInfo linfo;
       int UserID;
       int SelectBkCatalogid;
       AnsiString returncode,returncodeint,oldcode;
       TADOConnection *fcn;
public:		// User declarations
	__fastcall Tfrmshengdaifahuo(TComponent* Owner);
        void init(LandInfo* li);
        bool createproc();
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmshengdaifahuo *frmshengdaifahuo;
//---------------------------------------------------------------------------
#endif
