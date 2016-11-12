//---------------------------------------------------------------------------

#ifndef ClearingProvidFormH
#define ClearingProvidFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "MDIChild.h"
#include "RzButton.hpp"
#include "RzGrids.hpp"
#include "RzLabel.hpp"
#include "RzPanel.hpp"
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <ImgList.hpp>
#include <Buttons.hpp>
#include "DBGridEh.hpp"
#include "GridsEh.hpp"
//---------------------------------------------------------------------------
class TfrmClearingProvid : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TRzToolbar *rztlbr1;
	TRzToolButton *RzToolButton3;
	TRzToolButton *RzToolButton1;
	TImageList *ImageList1;
	TRzToolButton *BtnAlignBottom;
	TADOConnection *fcon;
	TDataSource *ds;
	TADOQuery *query;
	TDBGridEh *DBGridEh1;
	TGroupBox *GroupBox1;
	TRzLabel *lbl3;
	TSpeedButton *SpeedButton1;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TComboBox *cbbType;
	TCheckBox *cbstart;
	TDateTimePicker *dtp1;
	TDateTimePicker *dtp2;
	TCheckBox *chstorage;
	TComboBox *cbstorage;
	TCheckBox *cb1;
	TDateTimePicker *dtp3;
	TDateTimePicker *dtp4;
	TCheckBox *cb2;
	TDateTimePicker *dtp5;
	TDateTimePicker *dtp6;
	void __fastcall RzToolButton1Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall RzToolButton3Click(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall DBGridEh1TitleClick(TColumnEh *Column);
	void __fastcall dtp1Change(TObject *Sender);
private:	// User declarations
	String storageformat,retaiformat,saleformat;
public:		// User declarations
	__fastcall TfrmClearingProvid(TComponent* Owner);
		void   Init(TApplication* app, TADOConnection* con);
	int type,stgid;
	void Query(int supplierid);
	void Query();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmClearingProvid *frmClearingProvid;
//---------------------------------------------------------------------------
#endif
