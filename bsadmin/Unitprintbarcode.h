//---------------------------------------------------------------------------

#ifndef UnitprintbarcodeH
#define UnitprintbarcodeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include "RzPanel.hpp"
#include <ImgList.hpp>
#include "RzButton.hpp"
#include <Buttons.hpp>
#include "RpCon.hpp"
#include "RpConDS.hpp"
#include "RpDefine.hpp"
#include "RpRave.hpp"
#include "RpBase.hpp"
#include "RpSystem.hpp"
#include "frxClass.hpp"
#include "frxDBSet.hpp"
#include "frxBarcode.hpp"
//---------------------------------------------------------------------------
class Tfrmprintbarcode : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TADOConnection *fcon;
	TDBGrid *DBGrid1;
	TADOQuery *query;
	TDataSource *ds;
	TRzButton *RzButton1;
	TRzButton *RzButton2;
	TRzButton *RzButton3;
	TRzButton *RzButton4;
	TADOStoredProc *spdabao;
	TADOQuery *querydabao;
	TfrxDBDataset *frxdbpbag;
	TfrxReport *frxpbag;
	TfrxBarCodeObject *frxBarCodeObject1;
	TRzButton *RzButton5;
	TADOQuery *createbarcode;
	void __fastcall RzButton2Click(TObject *Sender);
	void __fastcall RzButton1Click(TObject *Sender);
	void __fastcall RzButton3Click(TObject *Sender);
	void __fastcall RzButton5Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	AnsiString xuhao;
	int stgid;
	int userid;
	int headid;
	AnsiString bkcatalogid,wsids;

	__fastcall Tfrmprintbarcode(TComponent* Owner,TADOConnection *con,int user);

        AnsiString CheckSumModulo10(AnsiString data);
        };
//---------------------------------------------------------------------------
extern PACKAGE Tfrmprintbarcode *frmprintbarcode;
//---------------------------------------------------------------------------
#endif
