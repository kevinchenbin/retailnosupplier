//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unitprintbag.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma link "RzButton"
#pragma link "RpCon"
#pragma link "RpConDS"
#pragma link "RpDefine"
#pragma link "RpRave"
#pragma link "RpBase"
#pragma link "RpSystem"
#pragma resource "*.dfm"
Tfrmprintbag *frmprintbag;
//---------------------------------------------------------------------------
__fastcall Tfrmprintbag::Tfrmprintbag(TComponent* Owner,TADOConnection *con,AnsiString ids)
	: TForm(Owner)
{
	AnsiString sql;
	query->Connection = con;
	fcon = con;
	sql = "select A.id,A.name,A.BookWords,B.printbag,B.Amount from BS_WsaleNote B left join stk_bookinfo on B.BkInfoID = stk_bookinfo.id left join BS_BookCatalog A on stk_bookinfo.BkcatalogID = A.id where B.id in " + ids;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	spdabao->Connection = con;
	querydabao->Connection = con;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmprintbag::RzButton2Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmprintbag::RzButton1Click(TObject *Sender)
{
	//ModalResult = mrOk ;
	if (query->State == dsEdit  ) {
		query->Post();
	}

}
//---------------------------------------------------------------------------
void __fastcall Tfrmprintbag::RzButton3Click(TObject *Sender)
{
	AnsiString sql ;
	sql = "delete sys_dabaoA where stgid =" + IntToStr(stgid);
	sql = sql + " and userid =" + IntToStr(userid);

	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	delete aq;

	spdabao->Parameters->ParamByName("@DanHaoID")->Value = headid ;
	spdabao->Parameters->ParamByName("@CatalogiD")->Value = bkcatalogid;
	spdabao->Parameters->ParamByName("@xuhaostr")->Value =  xuhao;
	spdabao->Parameters->ParamByName("@userid")->Value = userid;
	spdabao->Parameters->ParamByName("@stgid")->Value = stgid;
	spdabao->ExecProc();

	sql = "select * from sys_dabaoA where stgid =" + IntToStr(stgid) + " and userid =" +IntToStr(userid) ;
	querydabao->Close();
    querydabao->SQL->Clear();
	querydabao->SQL->Add(sql);
 	querydabao->Open();

	rs->SystemSetups >>ssAllowSetup;
	rs->SystemSetups >>ssAllowDestPreview;
	rs->SystemSetups >>ssAllowDestPrinter;
	rs->SystemSetups >>ssAllowPrinterSetup;
	rs->SystemSetups >>ssAllowDestFile;


	if (((TRzButton*)(Sender))->Tag==1) {
		rs->DefaultDest   = rdPreview ;
	}else
	{
		rs->DefaultDest   = rdPrinter  ;
	}

	rp->ProjectFile  = ExtractFilePath(Application->ExeName)+"DabaoA.rav";
	rp->Open();
	rp->Execute();
	rp->Close() ;
}
//---------------------------------------------------------------------------


