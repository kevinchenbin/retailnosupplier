//---------------------------------------------------------------------------

#ifndef UnitdocumentH
#define UnitdocumentH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzListVw.hpp"
#include "RzPanel.hpp"
#include "RzTreeVw.hpp"
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include <Menus.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <pngimage.hpp>
#include "RzShellDialogs.hpp"
#include <Dialogs.hpp>
#include "global.h"
//---------------------------------------------------------------------------
struct Nodefolder
{
  int ID;
  int PrentID;
  AnsiString Name;

};
class Tfrmdocument : public TForm
{
__published:	// IDE-managed Components
	TRzToolbar *RzToolbar1;
	TRzToolButton *Btn1;
	TRzToolButton *Btn2;
	TRzToolButton *BtnExit;
	TRzToolButton *BtnAlignBottom;
	TPanel *Panel1;
	TImageList *ImageList1;
	TTreeView *tvpurview;
	TSplitter *Splitter1;
	TListView *lvfile;
	TPopupMenu *newfolder;
	TPopupMenu *newfile;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TMenuItem *N4;
	TADOConnection *ADOConnection1;
	TImageList *ImageList2;
	TRzOpenDialog *openfile;
	TADOStoredProc *adosp;
	TMenuItem *N5;
	TMenuItem *N7;
	TSaveDialog *savefile;
	void __fastcall tvpurviewMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall N3Click(TObject *Sender);
	void __fastcall Btn1Click(TObject *Sender);
	void __fastcall Btn2Click(TObject *Sender);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall lvfileMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall N5Click(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall N4Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
        TADOConnection *fcon;
        int fuserid;
        int fstgid;
        int fdocumentid;
        	 TTreeNode *ClickNode; // 保存点中的节点
	TTreeNode * GroupNode;
        TListItem *lsitem;
        AnsiString displayText;
        int ffolderid;
        int foldertype;
public:		// User declarations
	__fastcall Tfrmdocument(TComponent* Owner);
        void init(TADOConnection *con,int userid,int stgid);
	void readdata(int type);
        void ReadyData(int foldertype);
        void ShowFile(int folderid);
        int getFix(AnsiString ext);

};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmdocument *frmdocument;
//---------------------------------------------------------------------------
#endif
