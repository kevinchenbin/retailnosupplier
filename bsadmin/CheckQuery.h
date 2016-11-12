//---------------------------------------------------------------------------

#ifndef CheckQueryH
#define CheckQueryH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "cspin.h"
#include "MDIChild.h"
#include "pdutil.cpp"
//#include "Dbgrid2Excel.h"
//#include " NoteCode.h"
#include "RzButton.hpp"
#include "RzEdit.hpp"
#include "RzPanel.hpp"
#include "RzRadChk.hpp"
#include <DBCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Mask.hpp>
#include "RzDBGrid.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include "RzDTP.hpp"
#include <ComCtrls.hpp>
#include "RzLine.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include "RzDBEdit.hpp"
#include "RzDBCmbo.hpp"
#include <ImgList.hpp>
#include "RpBase.hpp"
#include "RpDefine.hpp"
#include "RpRave.hpp"
#include "RpSystem.hpp"
//---------------------------------------------------------------------------
class TfrmCheckQuery : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TRzToolbar *rztlbr1;
	TRzToolButton *btnExit1;
	TRzToolButton *btnExit3;
	TRzToolButton *btnExit4;
	TRzToolButton *btnExit2;
	TADOQuery *qry1;
	TDataSource *ds1;
	TDataSource *ds2;
	TRzDBGrid *dbgrdCheck;
	TADODataSet *dsetCheck;
	TDataSource *ds4;
	TADODataSet *dset1;
	TADOConnection *con1;
	TImageList *ImageList1;
	TADOQuery *qusale;
	TADOQuery *quhuiyuan;
	TRzToolButton *BtnAlignBottom;
	TLabel *labstorage;
	TLabel *Label3;
	TGroupBox *GroupBox1;
	TLabel *lbl3;
	TLabel *lbl1;
	TLabel *Label5;
	TRzDBLookupComboBox *cbb1;
	TRzDateTimePicker *dtpstart;
	TRzDateTimePicker *dtmpckrSetEndTime;
	TRzDateTimePicker *dtmpckrSetStartTime;
	TRzDateTimePicker *dtpend;
	TGroupBox *GroupBox2;
	TLabel *lbl13;
	TLabel *lbl14;
	TLabel *lbl15;
	TLabel *lbl16;
	TLabel *lbl20;
	TLabel *lbl21;
	TLabel *lbl22;
	TLabel *lbl23;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *lbl19;
	TLabel *lbl5;
	TLabel *lbl6;
	TLabel *Label4;
	TLabel *Label6;
	TLabel *Label7;
	TRzEdit *edtposAmount;
	TRzEdit *edtposTotalDiscountedPrice;
	TRzEdit *edtposTotalFixedPrice;
	TRzEdit *edtDiscountedPrice;
	TRzEdit *edtnegAmount;
	TRzEdit *edtnegTotalDiscountedPrice;
	TRzEdit *edtnegTotalFixedPrice;
	TRzEdit *edtAfterDiscountedMoney;
	TRzEdit *edtwsaleTotalDiscountedPrice;
	TRzEdit *edtwsaleTotalFixedPrice;
	TRzEdit *edtRecCash;
	TRzEdit *edtRecCardMoney;
	TRzEdit *edtReceivedMoney;
	TGroupBox *GroupBox3;
	TGroupBox *GroupBox4;
	TEdit *edhycongzhi;
	TRzEdit *edtRecPostCard;
	TRzEdit *edtRecYouhuiquan;
	TRvProject *prjretail;
	TRvSystem *RvSystem1;
	TLabel *Label8;
	TRzEdit *editorder;
	TComboBox *cbuser;
	TLabel *Label9;
	TLabel *fff;
	TRzEdit *editweixi;
	TRzEdit *editzfb;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall btnExit1Click(TObject *Sender);
	void __fastcall btnExit3Click(TObject *Sender);
	void __fastcall btnExit2Click(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall btnExit4Click(TObject *Sender);
private:	// User declarations
String m_sql;
void OnHotKeyPress(DWORD vkCode);
public:		// User declarations
	__fastcall TfrmCheckQuery(TComponent* Owner);
	void Init(TApplication* app, TADOConnection* con);
	String TfrmCheckQuery::QueryCom();
	void Query();
	bool __fastcall DbgridToExcel(TRzDBGrid* dbg);
	int stgid;
        AnsiString alluserid;
        String operatorID ;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCheckQuery *frmCheckQuery;
//---------------------------------------------------------------------------
#endif
