//---------------------------------------------------------------------------

#ifndef UnittuihuosetH
#define UnittuihuosetH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzDBGrid.hpp"
#include "RzTabs.hpp"
#include <Buttons.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class Tfrmtuihuoset : public TForm
{
__published:	// IDE-managed Components
	TRzPageControl *RzPageControl1;
	TRzTabSheet *TabSheet1;
	TRzTabSheet *TabSheet2;
	TSpeedButton *SpeedButton1;
	TEdit *editsupplier;
	TComboBox *cbsupplier;
	TRzDBGrid *RzDBGrid1;
	TEdit *editzhouqi;
	TLabel *Label1;
	TSpeedButton *SpeedButton2;
	TEdit *editclass;
	TComboBox *cbsupplier2;
	TRzDBGrid *RzDBGrid2;
	TEdit *editzhouqi2;
	TLabel *Label2;
	TDataSource *dsclass;
	TADOTable *adotablesupplier;
	TADOTable *adotableclass;
	TDataSource *dssupplier;
	TADOConnection *ado;
	TPopupMenu *PopupMenu1;
	TPopupMenu *PopupMenu2;
	TMenuItem *N1;
	TMenuItem *D1;
	TLabel *Label3;
	TLabel *Label4;
	void __fastcall editsupplierKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editclassKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall SpeedButton2Click(TObject *Sender);
	void __fastcall RzDBGrid1CellClick(TColumn *Column);
	void __fastcall RzDBGrid2CellClick(TColumn *Column);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall D1Click(TObject *Sender);

private:	// User declarations
TADOConnection *fcon;
int fstgid;
public:		// User declarations
	__fastcall Tfrmtuihuoset(TComponent* Owner,TADOConnection* con,int stgid);
        void ReadyData();
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmtuihuoset *frmtuihuoset;
//---------------------------------------------------------------------------
#endif
