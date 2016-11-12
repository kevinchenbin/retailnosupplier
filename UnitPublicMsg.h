//---------------------------------------------------------------------------

#ifndef UnitPublicMsgH
#define UnitPublicMsgH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "RzDBGrid.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <ImgList.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TfrmpublicMsg : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TRzDBGrid *rdb;
	TDataSource *ds;
	TADOQuery *aq;
	TImageList *ImageList1;
	TGroupBox *GroupBox1;
	TDateTimePicker *btd;
	TDateTimePicker *endtd;
	TCheckBox *cbstg;
	TComboBox *cbstorage;
	TCheckBox *cbend;
	TCheckBox *cbbegin;
	TCheckBox *cbmsg;
	TComboBox *cbmsgtype;
	TCheckBox *cbmsgcontent;
	TEdit *edcontent;
	TSpeedButton *sbsearch;
	TCheckBox *cbhistory;

	void __fastcall rdbDblClick(TObject *Sender);
	void __fastcall sbsearchClick(TObject *Sender);
	void __fastcall edcontentChange(TObject *Sender);
	void __fastcall cbmsgtypeChange(TObject *Sender);
private:	// User declarations
        TADOConnection *fcn;
        int fstgid ;
        int fuserid;
        void __fastcall WndProc(TMessage &Msg);
public:		// User declarations
	__fastcall TfrmpublicMsg(TComponent* Owner);
        void init(TADOConnection *cn,int stgid,int userid);
        void LoadData();
        AnsiString DanHao;
        AnsiString type1;
        AnsiString ID;
        AnsiString IDstr;
        AnsiString MsgType;
		AnsiString sqlbase;
			void __fastcall rdbDrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol,
		  TColumn *Column, Grids::TGridDrawState State);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmpublicMsg *frmpublicMsg;
//---------------------------------------------------------------------------
#endif
