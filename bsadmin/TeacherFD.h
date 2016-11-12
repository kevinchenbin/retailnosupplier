//---------------------------------------------------------------------------

#ifndef TeacherFDH
#define TeacherFDH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <Menus.hpp>
#include "SelectCatalogForm.h"
#include "QryNoteCodeForm.h"
#include "QryCodeForm.h"
#include <ADODB.hpp>
#include <DB.hpp>
#include "SelectCatalogForm.h"
#include "pdtypes.h"
#include "RzEdit.hpp"
#include <Mask.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
//---------------------------------------------------------------------------
class TfrmteacherFD : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TLabel *Label1;
	TEdit *editname;
	TComboBoxEx *cbteacher;
	TDBGrid *DBGrid1;
	TLabel *l1;
	TLabel *Label3;
	TDateTimePicker *dtpbegin;
	TDateTimePicker *dtpend;
	TLabel *Label2;
	TLabel *Label4;
	TEdit *edtCatalog;
	TPopupMenu *PM;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TMenuItem *N6;
	TMenuItem *N4;
	TLabel *lblCatalog;
	TADOQuery *aq;
	TADOQuery *dbgridadoquery;
	TDataSource *DataSource1;
	TRzNumericEdit *numerfd;
	TRzNumericEdit *numerfdje;
	TPopupMenu *PopupMenu1;
	TMenuItem *D1;
	TLabel *Label5;
	TRzToolbar *RzToolbar1;
	TRzToolButton *Btn;
	TRzToolButton *RzToolButton2;
	void __fastcall edtCatalogKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall N3Click(TObject *Sender);
	void __fastcall N6Click(TObject *Sender);
	void __fastcall N4Click(TObject *Sender);
	void __fastcall editnameKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall cbteacherChange(TObject *Sender);
	void __fastcall numerfdKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall numerfdjeKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall D1Click(TObject *Sender);
	void __fastcall DBGrid1CellClick(TColumn *Column);
	void __fastcall BtnClick(TObject *Sender);
	void __fastcall RzToolButton2Click(TObject *Sender);
private:	// User declarations
	int m_catalogSearchMode;
		TADOConnection *fcon;
	int UserID,Stgid,username;
	int supplierID,catalogID;
public:		// User declarations
	__fastcall TfrmteacherFD(TComponent* Owner);
	void init(LandInfo *li);
	void AddNote(int supplierID,int CatalogId,int bkinfoid,int amount);
	bool DbgridToExcel(TDBGrid* dbg);
	void Deletenote();
	void ExecSQL(AnsiString sql);
	void ChangeCatalogSearchMode();
	void LoadData(AnsiString aname);
	void refreshdbgrid(int tearcher);
	int getteacherid(AnsiString name);
	int teacherid;
	int currentbookid;
	void UpdateValue(double value,int atype, int id);

};
//---------------------------------------------------------------------------
extern PACKAGE TfrmteacherFD *frmteacherFD;
//---------------------------------------------------------------------------
#endif
