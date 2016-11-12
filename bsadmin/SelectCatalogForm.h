//---------------------------------------------------------------------------

#ifndef SelectCatalogFormH
#define SelectCatalogFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ModalDialog.h"
#include "RzButton.hpp"
#include "RzLabel.hpp"
#include "RzDBGrid.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include "RzEdit.hpp"
#include <Mask.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <ExtCtrls.hpp>
#include "RzPanel.hpp"
#include <ImgList.hpp>
#include "RetailMngForm.h"
#include "WholesaleMngForm.h"
#include "StorageMngForm.h"
#include "ProcureMng.h"
#include "WholesaleMngReturnForm.h"
#include "RetailReturnMngForm.h"
#include "StorageReturnMngForm.h"
#include "StockAdjust.h"
//#include "Stockcheckxuyi.h"
#include "UnitBIOrder.h"
#include "Ysbooksale.h"
#include "MemberOrder.h"
#include "TeacherFD.h"

//---------------------------------------------------------------------------
class TfrmSelectCatalog : public TfrmModalDialog
{
__published:	// IDE-managed Components
	TDataSource *dsrcQry;
	TADODataSet *dsetQry;
	TADOQuery *aquery;
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnProperties;
	TRzToolButton *Btnselectall;
	TRzToolButton *BtnExit;
	TRzToolButton *BtnWeekView;
	TCheckBox *chauthor;
	TCheckBox *chkemu;
	TCheckBox *chnianji;
	TCheckBox *chprice;
	TCheckBox *chuserdef;
	TRzDBGrid *dbgrdQry;
	TEdit *edauthor;
	TEdit *edprice;
	TEdit *eduserdef;
	TRadioGroup *rg1;
	TRadioGroup *rg2;
	void __fastcall dbgrdQryKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dsetQryAfterScroll(TDataSet *DataSet);
	void __fastcall dsetQryAfterOpen(TDataSet *DataSet);
	void __fastcall edtSearchKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall BtnselectallClick(TObject *Sender);
	void __fastcall BtnPropertiesClick(TObject *Sender);
	void __fastcall dbgrdQryDblClick(TObject *Sender);
	void __fastcall BtnWeekViewClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall rg1Click(TObject *Sender);
	void __fastcall rg2Click(TObject *Sender);
	void __fastcall chnianjiClick(TObject *Sender);
	void __fastcall chkemuClick(TObject *Sender);
	void __fastcall eduserdefChange(TObject *Sender);
	void __fastcall edpriceChange(TObject *Sender);
	void __fastcall edauthorChange(TObject *Sender);
	void __fastcall edpriceKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edauthorKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dbgrdQryTitleClick(TColumn *Column);
	void __fastcall eduserdefKeyPress(TObject *Sender, wchar_t &Key);
private:	// User declarations
	int m_catalogID;
	int m_searchMode;
	int m_bkinfoid;


	AnsiString SearchCont;
	BOOL MutilSelectModal;//是否为多选模式
public:		// User declarations
	__fastcall TfrmSelectCatalog(TComponent* Owner,TADOConnection* con);
	void SetSearchMode(int searchMode, String text);
	void Init(LandInfo* li);
	void GetSelectResult(int& SupplierID, int& BkcatalogID);
	int *SupplierID, *BkcatalogiD, *BKSKid,*stkbkid,*skAmount;
	bool SelectAll;
	int lengthint;
	bool findbook;
	AnsiString Supplier;
	int DoModalType;//1为零售调用 2.批销调用3入库调用
	TfrmRetailMng *Retailfrm;
    TfrmStorageReturnMng * StorageReturnfrm;
  	TfrmStorageMng * Storagefrm;
	TfrmWholesaleMng *Wholefrm;
	TfrmProcureMng *Procurefrm;
	TfrmWholesaleReturnMng *WholeReturnfrm;
	TfrmRetailReturnMng *RetailReturnfrm;
	TfrmStockAdjust *StockAdjust;
	TfrmBIorder *order;
        Tfrmmemberorder *memberorder;
	//TfrmStockcheckxuyi *stockcheckxuyi;

	TfrmYsbooksale *Ysbooksale;
	bool m_ok,nobkinforsale,addbkinfo,nokucpxth,nowsreturn,rktuihuoguanli;
	bool Display,Mutisupplier;
	int BSKid;
	int BKinfoid;
	int Amount;
	int m_supplierID;
	AnsiString sql1,sql2;
	void Qry();
	AnsiString sql;
	void fiter();
        void QryBkInfo();
        bool qikan;
		int findbooks;
	AnsiString qikanhao;
        bool shuzhi(AnsiString context);
		void disableduoxuan();
		bool searchmohu;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmSelectCatalog *frmSelectCatalog;
//---------------------------------------------------------------------------
#endif
