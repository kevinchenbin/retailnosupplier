//---------------------------------------------------------------------------

#ifndef ClientDisforbookH
#define ClientDisforbookH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "RzButton.hpp"
#include "RzDBGrid.hpp"
#include "RzEdit.hpp"
#include "RzLabel.hpp"
#include "RzPanel.hpp"
#include <ComCtrls.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <Mask.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class Tfrmclientdisforbook : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TRzToolbar *RzToolbar1;
	TRzToolButton *BtnExit;
	TRzToolButton *BtnSave;
	TRzToolButton *BtnAlignBottom;
	TRzDBGrid *dbgdiscount;
	TRzGroupBox *rgbdiscountplan;
	TRzLabel *lblCatalog;
	TLabel *Label7;
	TRzEdit *edtCatalog;
	TDBGrid *DBGrid1;
	TGroupBox *GroupBox2;
	TLabel *Label4;
	TLabel *Label9;
	TLabel *Label6;
	TEdit *eddiscount;
	TEdit *edprice;
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TLabel *Label5;
	TComboBox *cbstorage;
	TComboBox *cbCusName;
	TADOQuery *aqcustom;
	TPopupMenu *pm;
	TMenuItem *N1;
	TMenuItem *N3;
	TMenuItem *N2;
	TMenuItem *N4;
	TADOQuery *querydetail;
	TDataSource *ds2;
	TADOQuery *query;
	TADOQuery *aq;
	TDataSource *ds1;
	TPopupMenu *pm1;
	TMenuItem *N5;
	TMenuItem *N7;
	TEdit *edquery;
	TPopupMenu *pmdel;
	TMenuItem *MenuItem1;
	void __fastcall edqueryKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall lblCatalogMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall edtCatalogKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbstorageSelect(TObject *Sender);
	void __fastcall DBGrid1CellClick(TColumn *Column);
	void __fastcall BtnSaveClick(TObject *Sender);
	void __fastcall dbgdiscountCellClick(TColumn *Column);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall eddiscountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall N5Click(TObject *Sender);
	void __fastcall N7Click(TObject *Sender);
	void __fastcall MenuItem1Click(TObject *Sender);
private:	// User declarations
        TADOConnection *fcon;
        int m_catalogSearchMode;
	int stgid;
public:		// User declarations
        void init(TADOConnection *con, int stgida);
        	void ChangeCatalogSearchMode();
	void Query();
        void __fastcall disable();
	__fastcall Tfrmclientdisforbook(TComponent* Owner);
        	void excuit();
	bool modify;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmclientdisforbook *frmclientdisforbook;
//---------------------------------------------------------------------------
#endif
