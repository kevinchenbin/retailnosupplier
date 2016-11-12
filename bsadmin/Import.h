//---------------------------------------------------------------------------

#ifndef ImportH
#define ImportH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzDBEdit.hpp"
#include "RzDBGrid.hpp"
#include "RzEdit.hpp"
#include "RzPanel.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Mask.hpp>
#include "RzRadChk.hpp"
#include "RzRadGrp.hpp"
#include "RzShellDialogs.hpp"
#include "RzPrgres.hpp"
//#include "SelectBookTypeForm.h"
#include <Buttons.hpp>
#include <ImgList.hpp>
#include "RzCmboBx.hpp"
#include "ModalDialog.h"
//---------------------------------------------------------------------------
class TfrmImport : public TForm
{
__published:	// IDE-managed Components
	TRzOpenDialog *opndlgExcelPath;
	TADODataSet *dset;
	TADOConnection *con1;
	TRzToolbar *RzToolbar1;
	TRzToolButton *BtnImport;
	TRzToolButton *BtnExit;
	TADOQuery *aq;
	TADOQuery *qry;
	TDataSource *ds;
	TADOQuery *query;
	TRzEdit *edtExcelPath;
	TLabel *lbl3;
	TCheckBox *chisbn;
	TSpeedButton *spselectpath;
	TCheckBox *chname;
	TCheckBox *chprice;
	TCheckBox *chpress;
	TCheckBox *chpresscount;
	TCheckBox *chauthor;
	TCheckBox *chtishi;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TADOCommand *comAddcatalog;
	TADOCommand *comaddnote;
	TPanel *Panel1;
	TADOConnection *cn;
	TCheckBox *cbselfma;
	TRadioGroup *radiogroup;
	void __fastcall spselectpathClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall BtnImportClick(TObject *Sender);
	void __fastcall radiogroupClick(TObject *Sender);
private:	// User declarations
	bool Import;
	TADOQuery * dsdg;             //
public:		// User declarations
	__fastcall TfrmImport(TComponent* Owner,TADOConnection *con,int headid,int userid,int stgid);
	int headerid;
	int fuserid,fstgid,mode; //mode 1Èë¿â 2·¢»õ
        AnsiString stackname;
	AnsiString GetNum(AnsiString Anstr);
        AnsiString GetSelfCode(AnsiString bookname);
        char GetPYIndexChar(char *str);
        void qingchuangExcel();
        void xianxingze();
        void yihuadaoru();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmImport *frmImport;
//---------------------------------------------------------------------------
#endif
