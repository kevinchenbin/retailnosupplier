//---------------------------------------------------------------------------

#ifndef UnitGroupH
#define UnitGroupH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include "RzButton.hpp"
#include "RzDBGrid.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class Tfrmgroup : public TForm
{
__published:	// IDE-managed Components
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnNew;
	TRzToolButton *BtnDelete;
	TADOQuery *aqgroup;
	TDataSource *ds;
	TPopupMenu *PopupMenu1;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TMenuItem *N4;
	TRzToolButton *BtnAlignBottom;
	TRzToolButton *BtnExit;
	TRzDBGrid *dg;
	void __fastcall BtnNewClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall N3Click(TObject *Sender);

	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall BtnDeleteClick(TObject *Sender);
	void __fastcall dgDblClick(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
private:	// User declarations
	TADOConnection *fcon;
	int fstgid,userid;
public:		// User declarations
	__fastcall Tfrmgroup(TComponent* Owner,TADOConnection *cn,int stgid,int sid);
	void ReadyData();
	AnsiString logmessage;
		void __fastcall dgDrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol,
		  TColumn *Column, Grids::TGridDrawState State);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmgroup *frmgroup;
//---------------------------------------------------------------------------
#endif
