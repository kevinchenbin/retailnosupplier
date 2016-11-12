//---------------------------------------------------------------------------

#ifndef CoustomerImportH
#define CoustomerImportH
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
//---------------------------------------------------------------------------
class TFormCousImport : public TForm
{
__published:	// IDE-managed Components
	TRzGroupBox *RzGroupBox1;
	TRzCheckBox *cbtype;
	TRzCheckBox *cbname;
	TRzCheckBox *cbaddress;
	TRzCheckBox *cbcode;
	TRzCheckBox *cbtelphone;
	TRzCheckBox *cbfax;
	TRzCheckBox *cbcontex;
	TRzCheckBox *cbdate;
	TRzCheckBox *chsaleman;
	TRzCheckBox *cbbalance;
	TRzCheckBox *cbarea;
	TRzCheckBox *cbBsLessBus;
	TRzCheckBox *cbBusLessBs;
	TLabel *Label1;
	TEdit *edtExcelPath;
	TRzButton *btselectpath;
	TLabel *lblExcel;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *lbnow;
	TLabel *lbsum;
	TRzProgressBar *prgrsbrExcelImport;
	TRzOpenDialog *opndlgExcelPath;
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnImport;
	TRzToolButton *BtnExit;
	TADOConnection *con1;
	TADOQuery *qry1;
	TDataSource *ds1;
	TADOQuery *aqdetail;
	void __fastcall btselectpathClick(TObject *Sender);
	void __fastcall BtnImportClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
private:	// User declarations
	bool Import;
	int Type;
	TADOQuery * dsdg;
public:		// User declarations
	__fastcall TFormCousImport(TComponent* Owner,TADOQuery * query,int type);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormCousImport *FormCousImport;
//---------------------------------------------------------------------------
#endif
