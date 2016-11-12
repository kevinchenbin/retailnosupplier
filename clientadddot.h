//---------------------------------------------------------------------------

#ifndef clientadddotH
#define clientadddotH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzCmboBx.hpp"
#include <Buttons.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class Tfrmclientadddot : public TForm
{
__published:	// IDE-managed Components
	TDBGrid *DBGrid1;
	TEdit *edname;
	TLabel *Label2;
	TEdit *eddot;
	TLabel *Label3;
	TADOConnection *fcon;
	TDataSource *ds;
	TADOQuery *query;
	TButton *Button1;
	TPopupMenu *PopupMenu1;
	TMenuItem *N1;
	TComboBox *cmtype;
	TButton *Button2;
	TDBGrid *DBGrid2;
	TDataSource *ds1;
	TADOQuery *aq1;
	TCheckBox *chname;
	TCheckBox *chtype;
	TPopupMenu *PopupMenu2;
	TMenuItem *MenuItem1;
	TMenuItem *N2;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall ednameChange(TObject *Sender);
	void __fastcall cmtypeChange(TObject *Sender);
	void __fastcall MenuItem1Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall DBGrid2CellClick(TColumn *Column);
private:	// User declarations
       int fstgid;
public:		// User declarations
	__fastcall Tfrmclientadddot(TComponent* Owner,TADOConnection *con,int stgid);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmclientadddot *frmclientadddot;
//---------------------------------------------------------------------------
#endif
