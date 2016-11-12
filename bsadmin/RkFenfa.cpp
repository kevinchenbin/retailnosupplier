//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "RkFenfa.h"
#include "UnitDiaobo.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma resource "*.dfm"
TfrmRkFenfa *frmRkFenfa;
//---------------------------------------------------------------------------
__fastcall TfrmRkFenfa::TfrmRkFenfa(TComponent* Owner,TADOConnection *con,int userid,int stgid)
	: TForm(Owner)
{
	fcon = con;
	AnsiString sql;
	fuserid = userid;
	fstgid = stgid;
	cmdAddNote->Connection = con;

	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	sql = "select ID,Name from SYS_StorageInfo where id <> " + IntToStr(fstgid)  ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	AnsiString ss,s1,s2;
	stkstgstr = "[-" + IntToStr(fstgid) + "]";
	s1 = "[" + IntToStr(fstgid) + "]";
	s2 = "[" + IntToStr(fstgid) + "] as [-" + IntToStr(fstgid) + "]" ;
	while (!aq->Eof)
	{
		stgstr = stgstr + "-[" + aq->FieldByName("ID")->AsAnsiString + "]";
		stkstgstr = stkstgstr + ",[-" + aq->FieldByName("ID")->AsAnsiString + "]";
		s1 = s1 + ",[" + aq->FieldByName("ID")->AsAnsiString + "]";
		s2 = s2 + ",[" + aq->FieldByName("ID")->AsAnsiString + "] as [-" + aq->FieldByName("ID")->AsAnsiString + "]";
		aq->Next();
	}

	sql = "select BS_BookCatalog.ISBN,BS_BookCatalog.Name,BS_BookCatalog.UserDefCode,BS_BookCatalog.Price,BS_BookCatalog.Author," + stkstgstr + "," +
			" BS_PressInfo.AbbreviatedName,SYS_StorageInfo.name as stgname,BS_StorageFenfa.*,BS_StorageFenfa.stkamount" + stgstr +
			" as remainamount from BS_StorageFenfa join stk_bookinfo on BS_StorageFenfa.bkinfoid = stk_bookinfo.id "
			" join BS_BookCatalog on stk_bookinfo.bkcatalogid = BS_BookCatalog.id "
			" join SYS_StorageInfo on BS_StorageFenfa.outstgid = SYS_StorageInfo.id "
			" left join (select bkcatalogid," + s2 +
			" from (select bkcatalogid,amount,stgid from stk_bookinfo ) as SourceTable "
			" pivot(sum(amount) for stgid in(" + s1 + ")) as PivotTable) J ON stk_bookinfo.bkcatalogid = J.bkcatalogid"
			" left join BS_PressInfo on BS_BookCatalog.pressid = BS_PressInfo.id where BS_StorageFenfa.userid = " + IntToStr(userid);
	query->Connection = fcon;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();

	aq->First();
	while (!aq->Eof)
	{
		ss = aq->FieldByName("ID")->AsAnsiString ;
		TColumn * col ;
		col = DBGrid1->Columns->Add();
		col->Field = query->FieldByName(ss);
		col->Title->Caption = aq->FieldByName("Name")->AsString ;
		col->Width = 70;

		col = DBGrid1->Columns->Add();
		ss = "-" + ss;
		col->Field = query->FieldByName(ss);
		col->Title->Caption = aq->FieldByName("Name")->AsString+"库存" ;
		col->Width = 70;

		cbstorage->AddItem(aq->FieldByName("Name")->AsAnsiString,(TObject*)aq->FieldByName("ID")->AsInteger);
		aq->Next();
	}
	delete aq;
}
//---------------------------------------------------------------------------
void __fastcall TfrmRkFenfa::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmRkFenfa::BtnSaveClick(TObject *Sender)
{
	if (query->IsEmpty() ) {
		return;
	}

	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	AnsiString sql;
	sql = "select * from BS_StorageFenfa where BS_StorageFenfa.userid = " + IntToStr(fuserid) +
			" and BS_StorageFenfa.stkamount" + stgstr + " < 0 and BS_StorageFenfa.stkamount" + stgstr + " < BS_StorageFenfa.stkamount ";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	if (aq->RecordCount > 0) {
		ShowMsg(Handle ,"有分发数量大于当前库存数量，请确认后在分发！",3);
		delete aq;
		return;
	}
	else
	{
    	delete aq;
	}
	if (query->State == dsEdit ) {
		query->Post();
	}
	ShowMsg(Handle ,"分发数量已确定！",3);
}
//---------------------------------------------------------------------------

void __fastcall TfrmRkFenfa::edamountKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		if (query->IsEmpty() ) {
            return;
		}
		int instgid = (int)cbstorage->Items->Objects[cbstorage->ItemIndex];
		AnsiString sql;
		if (edamount->Text != "") {
			String ids = "";
			if (DBGrid1->SelectedRows->Count > 1)
			{
				query->Bookmark = DBGrid1->SelectedRows->Items[0];
				ids = query->FieldByName("ID")->AsString;
				for (int i=1; i < DBGrid1->SelectedRows->Count; i++)
				{
					query->Bookmark = DBGrid1->SelectedRows->Items[i];
					ids = ids + "," + query->FieldByName("ID")->AsString;
				}
			}
			if (ids == "") {
				sql =  "update BS_StorageFenfa set [" + IntToStr(instgid) + "] = " + edamount->Text + " where userid = " + IntToStr(fuserid) ;
			}
			else
			{
				sql =  "update BS_StorageFenfa set [" + IntToStr(instgid) + "] = " + edamount->Text + " where id in(" + ids + ")";
			}
			TADOQuery *aq = new TADOQuery(this);
			aq->Connection = fcon;
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->ExecSQL();
			delete aq;
			query->Active = false;
			query->Active = true;
		}
        cbstorage->SetFocus();
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmRkFenfa::BtnLastRecordClick(TObject *Sender)
{
	if (query->IsEmpty() ) {
        return;
	}

	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	AnsiString sql;
	sql = "select * from BS_StorageFenfa where BS_StorageFenfa.userid = " + IntToStr(fuserid) +
			" and BS_StorageFenfa.stkamount " + stgstr + " < 0 and BS_StorageFenfa.stkamount " + stgstr + " < BS_StorageFenfa.stkamount ";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	if (aq->RecordCount > 0) {
		ShowMsg(Handle ,"有分发数量大于当前库存数量，请确认后在分发！",3);
		delete aq;
		return;
	}
	else
	{
    	delete aq;
	}

	AnsiString returncode;
	int sgfirsthid;
	cmdAddNote->Parameters->ParamByName("@StgID")->Value = fstgid;
	cmdAddNote->Parameters->ParamByName("@user")->Value = fuserid;
	cmdAddNote->Parameters->ParamByName("@CodeStr")->Value = CodeStr;
	cmdAddNote->Execute();
	returncode =  cmdAddNote->Parameters->ParamByName("@ReturnCode")->Value ;
    if (returncode == "") {
		return;
	}
	sgfirsthid =  cmdAddNote->Parameters->ParamByName("@Returnint")->Value ;

	AnsiString returncode1 = "已生成配送单：\n" + returncode + "\n是否查看？";

	if (ShowMsg(Handle ,returncode1.c_str(),1)==1)
	{
	//转配送查询
		AnsiString sql = "select * from BS_ZN_DiaoNoteHeader where ZNDiaoNtCode in (" + returncode + ")";
		Tfrmdiaobo * frm = new Tfrmdiaobo(Application,fcon,fstgid,fuserid,1);
		frm->aqhd->Close();
		frm->aqhd->SQL->Clear();
		frm->aqhd->SQL->Add(sql);
		frm->aqhd->Open();
		frm->DBNavigator1->Enabled = true;
		frm->QryNtHeader(sgfirsthid);
		//frm->cbinstorage->Enabled = false;
		//frm->BtnSaveAll->Enabled = false;
		//frm->membk->Enabled = false;
		//frm->DBNavigator1->Enabled = true;
		//frm->BtnOK->Visible = false;

		//frm->Btn->Enabled = false;
		//frm->BtnCancel->Enabled = true;
		//frm->BtnDelete ->Enabled = false;
		//frm->BtnJumptoLine->Enabled =false;
	}
    Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmRkFenfa::cbstorageSelect(TObject *Sender)
{
	edamount->Text = "0";
	edamount->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TfrmRkFenfa::queryAfterPost(TDataSet *DataSet)
{
    TLocateOptions   Opts;
	Opts.Clear();
	Opts   <<   loPartialKey;
	String   str   = AnsiString(query->FieldByName("ID")->AsAnsiString );
	query->Active = false;
	query->Active = true;
	query->Locate("ID",str,Opts);
	/*if (query->FieldByName("remainamount")->AsInteger < 0 ) {
		Abort();
	} */
}
//---------------------------------------------------------------------------

void __fastcall TfrmRkFenfa::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F3) {   // 确认分发数量
		BtnSave->Click();
	}
	if (Key == VK_F4) {   // 生成配送
		BtnLastRecord->Click();
	}
	if (Shift.Contains(ssAlt) && Key ==81  ) {   //退出
		BtnExit->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmRkFenfa::BtnNewClick(TObject *Sender)
{
WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmRkFenfa::FormClose(TObject *Sender, TCloseAction &Action)
{
Action =  caFree;
}
//---------------------------------------------------------------------------

