//---------------------------------------------------------------------------

#ifndef bookhistoryH
#define bookhistoryH
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
#include <ADODB.hpp>
#include <DB.hpp>
#include "DBGridEh.hpp"
#include "GridsEh.hpp"
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ImgList.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class Tfrmbookhistory : public TForm
{
__published:	// IDE-managed Components
	TADOConnection *fcon;
	TDataSource *ds1;
	TADOQuery *aq1;
	TDataSource *ds2;
	TADOQuery *aq2;
	TImageList *ImageList1;
	TSaveDialog *savedlg;
	TDBGridEh *dg1;
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TCheckBox *chstart;
	TDateTimePicker *dtpstart;
	TCheckBox *chend;
	TDateTimePicker *dtpend;
	TRadioGroup *rg;
	TEdit *edamount;
	TLabel *Label2;
	TComboBox *cbwangqi;
	TCheckBox *cbsupplier;
	TCheckBox *cbclient;
	TEdit *edsupplier;
	TEdit *edclient;
	TComboBox *cbboxclient;
	TComboBox *cbboxsupplier;
	TLabel *lbcurrentstg;
	TEdit *editcurrent;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall rgClick(TObject *Sender);
	void __fastcall cbwangqiChange(TObject *Sender);
	void __fastcall edsupplierKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edclientKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbsupplierClick(TObject *Sender);
	void __fastcall cbclientClick(TObject *Sender);
	void __fastcall cbboxclientChange(TObject *Sender);
	void __fastcall cbboxsupplierChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmbookhistory(TComponent* Owner,TADOConnection *con,int stgid,int catalogid );
	int m_catalogSearchMode,bkcatalogid,fstgid,fuserid;
	void Query();
	bool ChangeDisplay;
	AnsiString bookname;
        AnsiString GetExtr(AnsiString context);
        bool qikan;
        void ReadData();
        bool version;
        bool qfclient;
        bool qfsupplier;

};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmbookhistory *frmbookhistory;
//---------------------------------------------------------------------------
#endif
