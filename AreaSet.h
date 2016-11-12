//---------------------------------------------------------------------------

#ifndef AreaSetH
#define AreaSetH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include <ADODB.hpp>
#include <ComCtrls.hpp>
#include <DB.hpp>
#include "global.h"
//---------------------------------------------------------------------------
class TMemberAreaSet : public TForm
{
__published:	// IDE-managed Components
	TImageList *ilArea;
	TRzToolbar *RzToolbar1;
	TRzToolButton *BtnNew;
	TRzToolButton *BtnChangeOptions;
	TRzToolButton *BtnDelete;
	TRzToolButton *BtnExit;
	TADOQuery *quArea;
	TEdit *edAreaId;
	TRzToolButton *BtnSave;
	TRzToolButton *BtnAlignBottom;
	TEdit *edName;
	TLabel *Label1;
	TLabel *Label2;
	TTreeView *tvArea;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall BtnNewClick(TObject *Sender);
	void __fastcall BtnChangeOptionsClick(TObject *Sender);
	void __fastcall BtnDeleteClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall tvAreaClick(TObject *Sender);
	void __fastcall BtnSaveClick(TObject *Sender);
	void __fastcall Newsava();
	void __fastcall Changesava();
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);

private:	// User declarations
	TTreeNode * Root;
	int savamodle;
        int fstgid;
public:		// User declarations
	__fastcall TMemberAreaSet(TComponent* Owner,TADOConnection *cnn,int stgid);
        void __fastcall WndProc(TMessage &Msg);
};
//---------------------------------------------------------------------------
extern PACKAGE TMemberAreaSet *MemberAreaSet;
//---------------------------------------------------------------------------
#endif
