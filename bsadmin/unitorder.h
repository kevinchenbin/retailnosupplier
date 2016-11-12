//---------------------------------------------------------------------------

#ifndef unitorderH
#define unitorderH
#include "pdtypes.h"
#include "MDIChild.h"
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ImgList.hpp>
//---------------------------------------------------------------------------
class Tfrmunitorder : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TDBGrid *DBGrid1;
	TADOConnection *fcon;
	TDataSource *ds;
	TADOQuery *query;
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnOK;
	TADOCommand *cmdAddNote;
	TADOQuery *aq;
	TADOQuery *adoexec;
	TRzToolButton *BtnNew;
	TRzToolButton *BtnNew1;
	TRzToolButton *BtnNew2;
	TRzToolButton *BtnNew3;

	void __fastcall BtnOKClick(TObject *Sender);
	void __fastcall BtnNewClick(TObject *Sender);
	void __fastcall BtnNew1Click(TObject *Sender);
	void __fastcall BtnNew2Click(TObject *Sender);
	void __fastcall BtnNew3Click(TObject *Sender);
        void __fastcall WndProc(TMessage &Msg);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations

public:		// User declarations
	__fastcall Tfrmunitorder(TComponent* Owner,TADOConnection *con,int headerid,int flag);
	AnsiString rkcode;
        int fstgid,fuserid;
        int danid;
        bool createproc();
        AnsiString returncode,returncodeint,oldcode;
        int sgfirsthid,sgheaderid;
        void init(LandInfo* li);
        LandInfo linfo;
        int aflag;
     	void __fastcall DBGrid1DrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol,
          TColumn *Column, Grids::TGridDrawState State);

};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmunitorder *frmunitorder;
//---------------------------------------------------------------------------
#endif
