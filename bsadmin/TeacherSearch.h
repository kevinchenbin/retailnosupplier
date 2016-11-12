//---------------------------------------------------------------------------

#ifndef TeacherSearchH
#define TeacherSearchH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "DBGridEh.hpp"
#include "GridsEh.hpp"

#include <ADODB.hpp>
#include <DB.hpp>
#include "pdtypes.h"
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class Tfrmteachersearch : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TRzToolbar *RzToolbar1;
	TRzToolButton *BtnExit;
	TRzToolButton *Btn;
	TRzToolButton *RzToolButton2;
	TComboBoxEx *cbteacher;
	TEdit *editname;
	TLabel *Label4;
	TDateTimePicker *dtpbegin;
	TDateTimePicker *dtpend;
	TCheckBox *cteacher;
	TCheckBox *CheckBox2;
	TDBGridEh *dbgrid;
	TADOQuery *aq;
	TDataSource *DataSource1;
	TSaveDialog *sd;
	TADOQuery *aqq;
	TADODataSet *ADODataSet1;
	TADOStoredProc *adosp;
	void __fastcall editnameKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall RzToolButton2Click(TObject *Sender);
	void __fastcall dbgridDblClick(TObject *Sender);
private:	// User declarations
		TADOConnection *fcon;
	int UserID,Stgid,username;
	int supplierID,catalogID;
public:		// User declarations
void init(LandInfo *li);
void Search();
void LoadData(AnsiString aname);
int getteacherid(AnsiString name);
	__fastcall Tfrmteachersearch(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmteachersearch *frmteachersearch;
//---------------------------------------------------------------------------
#endif
