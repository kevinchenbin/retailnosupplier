//---------------------------------------------------------------------------

#ifndef NotedetailH
#define NotedetailH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TfrmNotedetail : public TForm
{
__published:	// IDE-managed Components
	TImageList *ImageList1;
	TRzToolbar *RzToolbar1;
	TRzToolButton *BtnExit;
	TDataSource *ds;
	TADOQuery *aq;
	TADOConnection *cn;
	TRzToolButton *BtnExport;
	TSaveDialog *savedlg;
	TDBGrid *DBGrid1;
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall BtnExportClick(TObject *Sender);
private:	// User declarations
	int type;//1Ϊ��⣬2Ϊ���� ,3Ϊ�̵�
public:		// User declarations
	__fastcall TfrmNotedetail(TComponent* Owner,String headercode,int Type,TADOConnection *con,int modle);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmNotedetail *frmNotedetail;
//---------------------------------------------------------------------------
#endif
