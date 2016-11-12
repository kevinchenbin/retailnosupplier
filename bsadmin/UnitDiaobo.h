//---------------------------------------------------------------------------

#ifndef UnitDiaoboH
#define UnitDiaoboH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include <DBCtrls.hpp>
#include <ComCtrls.hpp>
#include "RzDBGrid.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "NoteCode.h"
#include "pdutil.h"
#include <Mask.hpp>
#include "RzDBEdit.hpp"
#include "RzEdit.hpp"
#include <Menus.hpp>
#include "RpBase.hpp"
#include "RpCon.hpp"
#include "RpConDS.hpp"
#include "RpDefine.hpp"
#include "RpRave.hpp"
#include "RpSystem.hpp"
#include <Dialogs.hpp>
#include "frxClass.hpp"
#include "frxDBSet.hpp"
#include <Buttons.hpp>
#include "MDIChild.h"
//---------------------------------------------------------------------------

class Tfrmdiaobo : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TRzToolbar *RzToolbar1;
	TRzToolButton *BtnView;
	TRzToolButton *BtnNew;
	TRzToolButton *BtnSaveAll;
	TRzToolButton *BtnPrintPreview;
	TRzToolButton *BtnPrint;
	TRzToolButton *BtnExit;
	TRzToolButton *Btn;
	TRzToolButton *Btn1;
	TRzToolButton *BtnDelete;
	TADOConnection *con;
	TADOQuery *aq;
	TDataSource *ds;
	TADOQuery *aquery;
	TADOStoredProc *spqryntheader1;
	TADOStoredProc *spqryntheader;
	TPopupMenu *pm;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TMenuItem *N4;
	TADOStoredProc *cmdaddnote;
	TADODataSet *dsetNtHeader;
	TDataSource *dsheader;
	TADOCommand *cmdDelNote;
	TADOCommand *cmdBatchDelNote;
	TADOCommand *cmdUpdateNote;
	TADOCommand *cmdshenhe;
	TRzToolButton *BtnJumptoLine;
	TADOCommand *cmdBatchUpdateNote;
	TPopupMenu *selectmenu;
	TMenuItem *N5;
	TMenuItem *N6;
	TRvProject *RvProject1;
	TRvSystem *RvSystem1;
	TRvDataSetConnection *rvdatacondiaobo;
	TDataSource *dshd;
	TADOQuery *aqhd;
	TRzToolButton *BtnAlignBottom;
	TRzToolButton *BtnView1;
	TMenuItem *N7;
	TMenuItem *N8;
	TADOStoredProc *adospcopy;
	TSaveDialog *savedlg;
	TRzToolButton *BtnFinish;
	TRzToolButton *BtnCancel;
	TRzToolButton *BtnCancel1;
	TRzToolButton *BtnOK;
	TADOQuery *query;
	TRzToolButton *BtnBullets;
	TADOQuery *aqprint;
	TfrxDBDataset *frxDBdiaobo;
	TLabel *Label14;
	TLabel *Label15;
	TLabel *Label16;
	TRzDBNumericEdit *dbtotalamount;
	TRzDBNumericEdit *dbtotalmayang;
	TRzDBNumericEdit *dntotalshiyang;
	TRzDBGrid *DBGrid1;
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label8;
	TLabel *Label17;
	TLabel *Label2;
	TEdit *diaobocode;
	TDateTimePicker *dtpdata;
	TComboBox *cboutstorage;
	TComboBox *cbinstorage;
	TMemo *membk;
	TEdit *edcheckuser;
	TEdit *edstate;
	TGroupBox *GroupBox3;
	TCheckBox *chfoceset;
	TCheckBox *chfsluru;
	TCheckBox *chfsamount;
	TCheckBox *chfsdiscount;
	TLabel *Label18;
	TDBNavigator *DBNavigator1;
	TLabel *labtitle;
	TImageList *ImageList2;
	TADOStoredProc *spnewdanhao;
	TGroupBox *GroupBox2;
	TLabel *Label7;
	TLabel *Label10;
	TLabel *Label11;
	TLabel *Label12;
	TLabel *Label13;
	TLabel *Label6;
	TSpeedButton *SpeedButton1;
	TComboBox *cbinbkstack;
	TEdit *edcatalog;
	TRzDBNumericEdit *dbnumamount;
	TRzDBNumericEdit *dbnumdiscount;
	TRzDBNumericEdit *dbamountbk;
	TfrxReport *frxdiaobo;
	TLabel *Label19;
	TEdit *edopname;
	TLabel *Label9;
	TRzToolButton *toolshowmainmenu;
	TRzToolButton *RzToolButton1;
	void __fastcall BtnSaveAllClick(TObject *Sender);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall N3Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall N4Click(TObject *Sender);
	void __fastcall edcatalogKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall cbinstorageChange(TObject *Sender);
	void __fastcall BtnNewClick(TObject *Sender);
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall BtnDeleteClick(TObject *Sender);
	void __fastcall dbnumamountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dbnumdiscountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnClick(TObject *Sender);
	void __fastcall Btn1Click(TObject *Sender);
	void __fastcall BtnJumptoLineClick(TObject *Sender);
	void __fastcall N6Click(TObject *Sender);
	void __fastcall Label10MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall BtnPrintPreviewClick(TObject *Sender);
	void __fastcall BtnPrintClick(TObject *Sender);
	void __fastcall DBNavigator1Click(TObject *Sender, TNavigateBtn Button);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall BtnView1Click(TObject *Sender);
	void __fastcall N7Click(TObject *Sender);
	void __fastcall N8Click(TObject *Sender);
	void __fastcall cboutstorageChange(TObject *Sender);
	void __fastcall BtnExportClick(TObject *Sender);
	void __fastcall cbinbkstackClick(TObject *Sender);
	void __fastcall BtnFinishClick(TObject *Sender);
	void __fastcall DBGrid1CellClick(TColumn *Column);
	void __fastcall BtnCancelClick(TObject *Sender);
	void __fastcall BtnCancel1Click(TObject *Sender);
	void __fastcall BtnOKClick(TObject *Sender);
	void __fastcall dbamountbkKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnBulletsClick(TObject *Sender);
	void __fastcall membkKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall frxdiaoboGetValue(const UnicodeString VarName, Variant &Value);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall chfsluruClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall dbnumamountExit(TObject *Sender);
	void __fastcall toolshowmainmenuClick(TObject *Sender);
	void __fastcall RzToolButton1Click(TObject *Sender);

private:	// User declarations
	typedef enum
	{
		OPUnknown = 0,
		OPFind = 1,
		OPAddNtHeader,
		OPDelNtHeader,
		OPAddNote,
		OPDelNote,
		OPSetNotes,
		OPRecCash
	}OPMode;
	String m_findCode;//将要查询的单号
      //	int m_catalogSearchMode;//1为书号 2为自编码 3为书名
	OPMode m_opmode;//1为查单模式 2为添加单头模式 3为删除单头模式 4为添加单模式 5为删除单模式 6为统一模式 7为现场收款模式
	BSMode m_bsmode;//1为批销单模式 2为退货单模式
public:		// User declarations
	__fastcall Tfrmdiaobo(TComponent* Owner,TADOConnection *cn,int stgid,int userid,int type);

	void ReadData();
	void ReadDateWhenClick(int ins , int outs);
	void ReadinData();
	int fstgid,instorage,fuserid,outstorage;
	void QryNtHeader(String code);
	void QryNtHeader(int id);
	int m_catalogSearchMode;
	void ChangeCatalogSearchMode();
	bool AddNote(int bkinfoid);
	bool AddNote(int catalogID,int supplierid);
	void DelNote();
	void UpdateNote();
	void QryNtHeader();
	void BatchSetNotes(int amount, float discount, int mode);
	void PrintPreview(int mode);
	AnsiString stogName,username,logmessage;
	void Query(AnsiString Code);
	int ftype;   //1主动配送,2申请配送
	void ExcelExport(TRzDBGrid* dbg);
	int bkchange;
	void UpdateNote1();
	bool sametishi;
        int operationstateA;
        int operationstateB;
        bool ispowertozuofei;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmdiaobo *frmdiaobo;
//---------------------------------------------------------------------------
#endif
