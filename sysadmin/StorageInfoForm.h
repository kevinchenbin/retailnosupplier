//---------------------------------------------------------------------------

#ifndef StorageInfoFormH
#define StorageInfoFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <ExtCtrls.hpp>
#include <Mask.hpp>
#include "MDIChild.h"
#include <ImgList.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TfrmStorageInfo : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TDataSource *dsStorageInfo;
	TRzToolbar *rztlbr1;
	TRzToolButton *rztoolshendai;
	TRzToolButton *RzToolButton1;
	TImageList *ImageList1;
	TRzToolButton *BtnNew;
	TADOQuery *query;
	TRzToolButton *BtnAlignNone;
	TADOConnection *fcon;
	TDBGrid *dbGridCust;
	TRzToolButton *RzToolButton2;
	void __fastcall RzToolButton5Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall RzToolButton1Click(TObject *Sender);
	void __fastcall BtnNewClick(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnAlignNoneClick(TObject *Sender);
	void __fastcall dbGridCustCellClick(TColumn *Column);
	void __fastcall rztoolshendaiClick(TObject *Sender);
private:	// User declarations
	int modle;
public:		// User declarations
	__fastcall TfrmStorageInfo(TComponent* Owner);
	int userid,storageid;
	bool master;
        int version;
	void Init(TADOConnection* con);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmStorageInfo *frmStorageInfo;
//---------------------------------------------------------------------------
#endif
