//---------------------------------------------------------------------------

#ifndef MemberImportH
#define MemberImportH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzRadChk.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include "RzPrgres.hpp"
#include "RzShellDialogs.hpp"
#include <ImgList.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TFormMemImport : public TForm
{
__published:	// IDE-managed Components
	TLabel *lblExcel;
	TRzOpenDialog *opndlgExcelPath;
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnImport;
	TRzToolButton *BtnExit;
	TADOQuery *qry1;
	TDataSource *ds1;
	TADOQuery *aq;
	TLabel *Label1;
	TLabel *lbnow;
	TRzGroupBox *RzGroupBox1;
	TRzCheckBox *cbtype;
	TRzCheckBox *cbname;
	TRzCheckBox *cbaddress;
	TRzCheckBox *cbcode;
	TRzCheckBox *cbmobile;
	TRzCheckBox *cbtelphone;
	TRzCheckBox *cbsex;
	TRzCheckBox *cbcardid;
	TRzCheckBox *chtotalcons;
	TRzCheckBox *cbbalance;
	TRzCheckBox *cbbirthday;
	TRzCheckBox *cballcheck;
	TEdit *edtExcelPath;
	TRzButton *btselectpath;
	TADOConnection *con1;
	TADOTable *adotable;
	TProgressBar *pb;
	TRzCheckBox *chjifen;
	TRzCheckBox *chyxdate;
	void __fastcall btselectpathClick(TObject *Sender);
	void __fastcall BtnImportClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall cballcheckClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
private:	// User declarations
	bool Import;
	TADOQuery * dsdg;
public:		// User declarations
	__fastcall TFormMemImport(TComponent* Owner,TADOQuery * query);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMemImport *FormMemImport;
//---------------------------------------------------------------------------
#endif
