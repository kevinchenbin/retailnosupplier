//---------------------------------------------------------------------------

#ifndef suppmanageH
#define suppmanageH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include "RzButton.hpp"
#include "RzEdit.hpp"
#include "RzLabel.hpp"
#include <Mask.hpp>
#include "RzCmboBx.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include "RzDBGrid.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include "global.h"
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TSuppMana : public TForm
{
__published:	// IDE-managed Components
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnNew;
	TRzToolButton *BtnFinish;
	TRzToolButton *BtnDelete;
	TRzToolButton *BtnExit;
	TRzToolButton *BtnView;
	TADOQuery *aqinit;
	TADOQuery *aqrecord;
	TDataSource *ds;
	TRzToolButton *BtnExport;
	TADOQuery *query;
	TRzToolButton *BtnImport;
	TRzToolButton *BtnAlignBottom;
	TRzDBGrid *DBGridrecord;
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TRzLabel *RzLabel1;
	TRzEdit *etcontax;
	TEdit *edquery;
	TComboBox *cbsale;
	TComboBox *cblocal;
	TPopupMenu *PopupMenu1;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TComboBox *cbstates;
	TLabel *Label4;
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall BtnNewClick(TObject *Sender);
	void __fastcall BtnFinishClick(TObject *Sender);
	void __fastcall BtnDeleteClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall BtnExportClick(TObject *Sender);
	void __fastcall etcontaxKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnImportClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edqueryKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall cbsaleKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall cblocalKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall DBGridrecordTitleClick(TColumn *Column);

	void __fastcall PopupMenu1Popup(TObject *Sender);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);

private:	// User declarations
	int type;
	TADOConnection *cn;
        void updatestate(int type);
        int fstgid;

public:		// User declarations
	__fastcall TSuppMana(TComponent* Owner,int Type,TADOConnection *cnn,int stgid,bool sup,bool client);
	bool __fastcall DbgridToExcel(TRzDBGrid* dbg);
	void Initsalesman();
	void InitLocalinfo();
        bool Supplierpower;
        bool Clientpower;
        bool qfsupplier;
        bool qfclient;

	int StgID;
   	void __fastcall DBGridrecordDrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol,
		  TColumn *Column, Grids::TGridDrawState State);
		  int getsalemanid(AnsiString name);
};
//---------------------------------------------------------------------------
extern PACKAGE TSuppMana *SuppMana;
//---------------------------------------------------------------------------
#endif
