//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "retailbookup.h"
#include "hoistoryview.h"
#include "bookhistory.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "RzDBEdit"
#pragma link "RzEdit"
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma resource "*.dfm"
Tfrmretailbookup *frmretailbookup;
//---------------------------------------------------------------------------
__fastcall Tfrmretailbookup::Tfrmretailbookup(TComponent* Owner,TADOConnection *con,int stgid)
	: TForm(Owner)
{
dgdetail->OnDrawColumnCell= dgdetailDrawColumnCell;

	fcon = con;
	fstgid = stgid;
	qudetail->Connection = con;
        aq->Connection = con;
        cmdAddNote->Connection=con;
	dtpbegin->Date = Date();
	dtpend->Date = Date();
	chbegin->Checked = true;
	chend->Checked = true;

	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = con;
	AnsiString sql1;
	sql1 = "select ID,Name from SYS_StorageInfo where id = " + IntToStr(stgid);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql1);
	aq->Open();
	Edit1->Text = IntToStr(stgid);
	Edit2->Text = aq->FieldByName("Name")->AsAnsiString ;

	sql1 = "select ID,Name from SYS_StorageInfo " ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql1);
	aq->Open();
	while (!aq->Eof )
	{
		if (sqlstorage == "") {
			sqlstorage = "[" + aq->FieldByName("ID")->AsAnsiString + "]";
		}
		else
		{
			sqlstorage = sqlstorage + ",[" + aq->FieldByName("ID")->AsAnsiString + "]";
		}

		aq->Next();
	}

	sql1 = "select id,AbbreviatedName from BS_PressInfo";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql1);
	aq->Open();
	while (!aq->Eof )
	{
		cbpress->AddItem(aq->FieldByName("AbbreviatedName")->AsAnsiString ,(TObject*)aq->FieldByName("id")->AsInteger );
		aq->Next();
	}

	sql1 = "select id,name from CUST_CustomerInfo where type = 1 and customerstate=1 ";;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql1);
	aq->Open();
	while (!aq->Eof )
	{
		cbsupplier->AddItem(aq->FieldByName("name")->AsAnsiString ,(TObject*)aq->FieldByName("id")->AsInteger );
		aq->Next();
	}
	delete aq;
    strlist = NULL;
	strlist =new TStringList();
	ssbkid = "-1";
	BtnView->Click();
        showsiyang();
		iscaigou=false;


}
//---------------------------------------------------------------------------
void __fastcall Tfrmretailbookup::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmretailbookup::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmretailbookup::BtnExportClick(TObject *Sender)
{
	if (qudetail->IsEmpty() ) {
		return;
	}
	if (qudetail->Active && qudetail->RecordCount > 0) {
		DbgridToExcel(dgdetail);
	}
}
//---------------------------------------------------------------------------
//Excel导出函数
bool __fastcall Tfrmretailbookup::DbgridToExcel(TDBGrid* dbg)
{
	AnsiString sql1;
	AnsiString temptext,path,DBPath;
	int  iFileHandle;
	int  iFileLength;

	sql1 = " select distinct F.name ";
	if (rb1->Checked) {
		sql1 = sql1 + " from (select id,bkcatalogid,amount,supplierid from stk_bookinfo where stgid = " + IntToStr(fstgid) + ") as D left join BS_BookCatalog A on D.bkcatalogid = A.id ";
	}
	else
	{
		sql1 = sql1 + " from (select min(stk_bookinfo.id) as id,bkcatalogid,supplierid,sum(amount) as amount from stk_bookinfo group by bkcatalogid,supplierid) as D left join BS_BookCatalog A on D.bkcatalogid = A.id ";
	}
	sql1 = sql1 + " left join BS_PressInfo B on A.pressid = B.id "

			" left join (select bkcatalogid,sum(amount) as amount from stk_bookinfo ";
	if (rb1->Checked) {
		sql1= sql1 + " where stgid = " + IntToStr(fstgid) ;
	}
	 if (rb2->Checked) {
	   sql1= sql1 + " where 1 = 1 " ;
	}






	sql1 = sql1 + " group by bkcatalogid) K ON D.bkcatalogid = K.bkcatalogid "
			" left join (select  STK_bookinfo.bkcatalogid,sum(E.amount) as retailamount, "
			" sum(E.FixedPrice) AS RetailFixedPrice,sum(E.DiscountedPrice) as RetailDiscountedPrice "
			" from BS_RetailNoteHeader join BS_RetailNote E ON BS_RetailNoteHeader.ID = E.RetailNtHeaderID join stk_bookinfo on E.bkinfoid = stk_bookinfo.id ";
	if (rb1->Checked ) {
		sql1 = sql1 + " where BS_RetailNoteHeader.stgid = " + IntToStr(fstgid);
	}
	else
	{
		sql1 = sql1 + " where 1= 1 " ;
	}
	sql1 = sql1 + sqltime +
			" group by STK_bookinfo.bkcatalogid ) H on A.id = H.bkcatalogid "
			" left join (select STK_bookinfo.bkcatalogid,sum(E.amount) as wsaleamount, "
			" sum(E.FixedPrice) AS WsaleFixedPrice,sum(E.DiscountedPrice) as WsaleDiscountedPrice "
			" from BS_WsaleNoteHeader join BS_WsaleNote E ON BS_WsaleNoteHeader.ID = E.WsaleNtHeaderID join stk_bookinfo on E.bkinfoid = stk_bookinfo.id ";
	if (rb1->Checked ) {
		sql1 = sql1 + " where BS_WsaleNoteHeader.stgid = " + IntToStr(fstgid);
	}
	else
	{
		sql1 = sql1 + " where 1= 1" ;
	}
	sql1 = sql1 + sqltime +
			" group by STK_bookinfo.bkcatalogid ) I on A.id = I.bkcatalogid left join "
			" (select bkcatalogid ," + sqlstorage +
			" from (select bkcatalogid,amount,stgid from stk_bookinfo ) as SourceTable "
			" pivot(sum(amount) for stgid in(" + sqlstorage + ")) as PivotTable) J on D.BkcatalogID = J.bkcatalogid"
			" WHERE (I.wsaleamount > 0 or H.retailamount > 0) " + sqlwhere ;

	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;

	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql1);
	aq->Open();
	savedlg->FileName = aq->FieldByName("name")->AsAnsiString.Trim() ;
	TADOQuery *aq1 = new TADOQuery(this);
	aq1->Connection = fcon;
	if (savedlg->Execute())
	{
		String Name;
		DBPath = Sysutils::ExtractFilePath(savedlg->FileName .c_str()  );
		path = DBPath + Sysutils::ExtractFileName(savedlg->FileName .c_str() ) + ".csv";
	}
	else
	{
		return false;
	}

	aq->First();
	while (!aq->Eof )
	{
		path = DBPath + aq->FieldByName("name")->AsAnsiString.Trim() + ".csv";
		if(FileExists(path))
			if (DeleteFileA(path))
				iFileHandle = FileCreate(path.c_str());
			else
				return false;
		else
		iFileHandle = FileCreate(path.c_str());
        temptext = "";
		for(int q=1;q<dbg->FieldCount ;++q)
		{
			if (dbg->Columns->Items[q]->Visible == true) {
				temptext = temptext + dbg->Columns ->Items [q]->Title ->Caption + ",";
			}
		}
		iFileLength   =   FileSeek(iFileHandle,0,2);
		FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
		sql1 = sql + " and F.Name = '" + aq->FieldByName("name")->AsString.Trim() + "'";
		aq1->Close();
		aq1->SQL->Clear();
		aq1->SQL->Add(sql1);
		aq1->Open();
		aq1->First();
		while (!aq1->Eof )
		{
			temptext = "\n";
			for(int j=2;j<dbg->Columns ->Count+1;j++)
			{
				if (dbg->Columns->Items[j-1]->Visible == true) {
					if (dbg->Columns ->Items [j-1]->FieldName == "Name") {
						AnsiString bookname;
						bookname = aq1->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
						bookname = StringReplace(bookname , ",",".",TReplaceFlags()<<rfReplaceAll);
						temptext = temptext + bookname + ",";
					}
					else
					{
						temptext = temptext + aq1->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
					}
				}
			}
			iFileLength   =   FileSeek(iFileHandle,0,2);
			FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
			aq1->Next();
		}
		FileClose(iFileHandle);
		aq->Next();
	}
	delete aq;
	delete aq1;

        ShowMsg(Handle ,"导出完毕！",3);
	return false;
}

//---------------------------------------------------------------------------

void __fastcall Tfrmretailbookup::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F6) {
		BtnExport->Click();
	}
	if (Key == VK_F7) {
		BtnExport1->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 70 ) {    //查询
		BtnView->Click();
	}

	if (Shift.Contains(ssCtrl)&& Key == 81 ) {    //退出
		BtnExit->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==90) {   //恢复窗口
		WindowState = wsNormal  ;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmretailbookup::BtnViewClick(TObject *Sender)
{
	sqlwhere = "";
	sqltime = "";
	sqlls = "";
	sqlws = "";
	if (chbegin->Checked ) {
		sqltime =  " and datediff(day,'" + DateToStr(dtpbegin->Date) + "',HdTime) >= 0 ";
	}
	if (chend->Checked ) {
		sqltime = sqltime + " and datediff(day,'" + DateToStr(dtpend->Date) + "',HdTime) <= 0 ";
	}
	if (chbkinfo->Checked ) {
		if (edmin->Text != "") {
			sqlwhere = sqlwhere + " and K.amount >= " + edmin->Text ;
		}
		if (edmax->Text != "") {
            sqlwhere = sqlwhere + " and K.amount <= " + edmax->Text ;
		}
	}
	if (chpress->Checked && cbpress->Text != "") {
		sqlwhere = sqlwhere + " and B.AbbreviatedName = '" + cbpress->Text.Trim() + "'";
	}

	if (chsupplier->Checked && cbsupplier->Text != "") {

		try {
			supplieridaa = (int)(cbsupplier->Items->Objects[cbsupplier->ItemIndex]);
		} catch (...) {
			return;
		}
	      //	sqlwhere = sqlwhere + " and D.supplierid = " + IntToStr(supplierid);
		//sqlwhere = sqlwhere + " and F.name = '" + cbsupplier->Text.Trim() + "'";
	}
	if (chbox2->Checked ) {     //不包含退货记录
		sqlwhere = sqlwhere + " and A.id not in(select stk_bookinfo.bkcatalogid from stk_bookinfo LEFT JOIN BS_StorageNote ON BS_StorageNote.Bkinfoid = stk_bookinfo.id join BS_StorageNoteHeader on BS_StorageNote.StgNtHeaderID = BS_StorageNoteHeader.id "
			" where BS_StorageNote.amount < 0 " + sqltime ;
		if (rb1->Checked ) {
			sqlwhere = sqlwhere + " and BS_StorageNoteHeader.stgid = " + IntToStr(fstgid);
		}
		sqlwhere = sqlwhere + ")";
	}
	if (chls->Checked) {
		/*if (edlsmin->Text != "") {
			sqlls = " having sum(E.amount) >= " + edlsmin->Text ;
		}
		if (edlsmax->Text != "") {
			if (sqlls == "") {
				sqlls = " having sum(E.amount) <= " + edlsmax->Text ;
			}
			else
			{
				sqlls = sqlls + " and sum(E.amount) <= " + edlsmax->Text ;
			}
		}  */
		if (edlsmin->Text != "") {
			sqlwhere = sqlwhere + " and H.retailamount >= " + edlsmin->Text ;
		}
		if (edlsmax->Text != "") {
			sqlwhere = sqlwhere + " and H.retailamount <= " + edlsmax->Text ;
		}
	}
	if (chws->Checked ) {
		/*if (edwsmin->Text != "") {
			sqlws = " having sum(E.amount) >= " + edwsmin->Text ;
		}
		if (edwsmax->Text != "") {
			if (sqlws == "") {
				sqlws = " having sum(E.amount) <= " + edwsmax->Text ;
			}
			else
			{
				sqlws = sqlws + " and sum(E.amount) <= " + edwsmax->Text ;
			}
		}  */
		if (edwsmin->Text != "") {
			sqlwhere = sqlwhere + " and I.wsaleamount >= " + edwsmin->Text ;
		}
		if (edwsmax->Text != "") {
			sqlwhere = sqlwhere + " and I.wsaleamount >= " + edwsmax->Text ;
		}
	}
	//H零售数据，I发货数据
        if (chsupplier->Checked && cbsupplier->Text != "")
        {
          sql="; WITH TT as ( ";
        }else sql=" ";

	sql =sql+ " select distinct rank() over (order by A.id) as xuhao,D.id,A.id as bkcatalogid,A.ISBN,A.name,A.Price,B.AbbreviatedName,C.Name as typename,K.amount as totalamount,D.amount,"
			" H.retailamount,H.RetailFixedPrice,H.RetailDiscountedPrice,I.wsaleamount,I.WsaleFixedPrice,I.WsaleDiscountedPrice ," + sqlstorage ;

	if (rb1->Checked) {
		sql = sql + " from (select id,bkcatalogid,amount,supplierid from stk_bookinfo where stgid = " + IntToStr(fstgid) + ") as D left join BS_BookCatalog A on D.bkcatalogid = A.id ";
	}
	else
	{
		sql = sql + " from (select min(stk_bookinfo.id) as id,bkcatalogid,supplierid,sum(amount) as amount from stk_bookinfo group by bkcatalogid,supplierid) as D left join BS_BookCatalog A on D.bkcatalogid = A.id ";
	}
	sql = sql + " left join BS_PressInfo B on A.pressid = B.id "
			" left join BS_BookType C on A.smallBookTypeID = C.id "
			" left join CUST_CustomerInfo F ON D.supplierid = F.ID "
			" left join (select bkcatalogid,sum(amount) as amount from stk_bookinfo ";
	if (rb1->Checked) {
		sql= sql + " where stgid = " + IntToStr(fstgid) ;
	}
	sql = sql + " group by bkcatalogid) K ON D.bkcatalogid = K.bkcatalogid "
			" left join (select sum(E.amount) as retailamount, "
			" sum(E.FixedPrice) AS RetailFixedPrice,sum(E.DiscountedPrice) as RetailDiscountedPrice,STK_bookinfo.bkcatalogid "
			" from BS_RetailNoteHeader join BS_RetailNote E ON BS_RetailNoteHeader.ID = E.RetailNtHeaderID join stk_bookinfo on E.bkinfoid = stk_bookinfo.id ";
	if (rb1->Checked ) {
		sql = sql + " where BS_RetailNoteHeader.stgid = " + IntToStr(fstgid);
	}
	else
	{
		sql = sql + " where 1= 1 " ;
	}
	sql = sql + sqltime +
			" group by STK_bookinfo.bkcatalogid ) H on D.bkcatalogid = H.bkcatalogid  "
			" left join (select STK_bookinfo.bkcatalogid,sum(E.amount) as wsaleamount, "
			" sum(E.FixedPrice) AS WsaleFixedPrice,sum(E.DiscountedPrice) as WsaleDiscountedPrice "
			" from BS_WsaleNoteHeader join BS_WsaleNote E ON BS_WsaleNoteHeader.ID = E.WsaleNtHeaderID join stk_bookinfo on E.bkinfoid = stk_bookinfo.id ";
	if (rb1->Checked ) {
		sql = sql + " where BS_WsaleNoteHeader.stgid = " + IntToStr(fstgid);
	}
	else
	{
		sql = sql + " where 1= 1" ;
	}
	sql = sql + sqltime +
			" group by STK_bookinfo.bkcatalogid) I on D.bkcatalogid = I.bkcatalogid left join "
			" (select bkcatalogid ," + sqlstorage +
			" from (select bkcatalogid,amount,stgid from stk_bookinfo ) as SourceTable "
			" pivot(sum(amount) for stgid in(" + sqlstorage + ")) as PivotTable) J on D.BkcatalogID = J.bkcatalogid"
			" WHERE (I.wsaleamount > 0 or H.retailamount > 0) " + sqlwhere ;

	   //  if (chsupplier->Checked && cbsupplier->Text != "")
	  //  {
	   //   sql=sql+" ) select * from TT where supplierid= "+IntToStr(supplieridaa);
	  //  }


	qudetail->Close();
	qudetail->SQL->Clear();
	qudetail->SQL->Add(sql);
	qudetail->Open();
    TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	AnsiString sql1;
	sql1 = "select ID,Name from SYS_StorageInfo where id <> " + IntToStr(fstgid)  ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql1);
	aq->Open();
	AnsiString ss = IntToStr(fstgid);
	dgdetail->Columns->Items[14]->Field = qudetail->FieldByName(ss);
	int i = 1;
	while (!aq->Eof && i <= 10 )
	{
		ss = aq->FieldByName("ID")->AsAnsiString ;
		dgdetail->Columns->Items[14+i]->Field = qudetail->FieldByName(ss);
		dgdetail->Columns->Items[14+i]->Visible = true;
		dgdetail->Columns->Items[14+i]->Title->Caption = aq->FieldByName("Name")->AsString ;

		aq->Next();
		i++;
	}



	maxlen = 14 + i;
	delete aq;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmretailbookup::dtpbeginChange(TObject *Sender)
{
	chbegin->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmretailbookup::dtpendChange(TObject *Sender)
{
	chend->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmretailbookup::BtnExport1Click(TObject *Sender)
{

	AnsiString sql1;
	AnsiString temptext,path,DBPath;
	int iFileHandle;
	int	iFileLength;

         //导出选中的
       if (dgdetail->SelectedRows->Count > 0)
	{
		qudetail->Bookmark = dgdetail->SelectedRows->Items[0];
		ssbkid = ssbkid + "," + qudetail->FieldByName("id")->AsAnsiString ;
		strlist->AddObject(qudetail->FieldByName("id")->AsAnsiString,(TObject*)qudetail->FieldByName("id")->AsInteger);
		for (int i=1; i < dgdetail->SelectedRows->Count; i++)
		{
			qudetail->Bookmark = dgdetail->SelectedRows->Items[i];
			ssbkid = ssbkid + "," + qudetail->FieldByName("id")->AsAnsiString ;
			strlist->AddObject(qudetail->FieldByName("id")->AsAnsiString,(TObject*)qudetail->FieldByName("id")->AsInteger);
		}
	}else
        {


          ShowMsg(Handle ,"请先选中需要导出的书目！",3);
           return;

        }

	sql1 = " select distinct F.name "
			" from  stk_bookinfo D left join CUST_CustomerInfo F ON D.supplierid = F.ID "
			" where D.id in("  + ssbkid + ")";
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql1);
	aq->Open();
	savedlg->FileName = aq->FieldByName("name")->AsAnsiString.Trim() ;
	TADOQuery *aq1 = new TADOQuery(this);
	aq1->Connection = fcon;
	if (savedlg->Execute())
	{
		String Name;
		DBPath = Sysutils::ExtractFilePath(savedlg->FileName .c_str()  );
		//path = DBPath + Sysutils::ExtractFileName(savedlg->FileName .c_str() );
	}
	else
	{
		return ;
	}

	aq->First();
	while (!aq->Eof )
	{
		path = DBPath + aq->FieldByName("name")->AsAnsiString.Trim() + ".csv";
		if(FileExists(path))
			if (DeleteFileA(path))
				iFileHandle = FileCreate(path.c_str());
			else
				return ;
		else
		iFileHandle = FileCreate(path.c_str());
        temptext = "";
		for(int q=1;q<dgdetail->FieldCount ;++q)
		{
			if (dgdetail->Columns->Items[q]->Visible == true) {
				temptext = temptext + dgdetail->Columns ->Items [q]->Title ->Caption + ",";
			}
		}
		iFileLength   =   FileSeek(iFileHandle,0,2);
		FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
               if (chsupplier->Checked && cbsupplier->Text != "") {
                 	sql1 = sql + " and TT.id in(" + ssbkid + ")";
               }else
		sql1 = sql + " and F.Name = '" + aq->FieldByName("name")->AsString + "' and D.id in(" + ssbkid + ")";
                //  sql1 = sql +" and D.id in(" + ssbkid + ")";
		/*sql1 = " select distinct rank() over (order by D.id) as xuhao,D.id,A.ISBN,A.name,A.Price,B.AbbreviatedName,C.Name as typename,F.id as supplierid,F.name as suppliername,K.amount as totalamount, "
			" H.retailamount,H.RetailFixedPrice,H.RetailDiscountedPrice,I.wsaleamount,I.WsaleFixedPrice,I.WsaleDiscountedPrice ," + sqlstorage +
			" from  (select min(id) as id,bkcatalogid,supplierid from stk_bookinfo "
			" group by bkcatalogid,supplierid ) D left join BS_BookCatalog A on D.bkcatalogid = A.id "
			" left join BS_PressInfo B on A.pressid = B.id "
			" left join BS_BookType C on A.smallBookTypeID = C.id "
			" left join CUST_CustomerInfo F ON D.supplierid = F.ID "
			" left join (select bkcatalogid,supplierid,sum(amount) as amount from stk_bookinfo group by bkcatalogid,supplierid) K ON D.bkcatalogid = K.bkcatalogid and D.supplierid = K.supplierid "
			" left join (select  STK_bookinfo.bkcatalogid,sum(E.amount) as retailamount, "
			" sum(E.FixedPrice) AS RetailFixedPrice,sum(E.DiscountedPrice) as RetailDiscountedPrice "
			" from BS_RetailNoteHeader join BS_RetailNote E ON BS_RetailNoteHeader.ID = E.RetailNtHeaderID join stk_bookinfo on E.bkinfoid = stk_bookinfo.id "
			" where 1=1 " + sqltime +
			" group by STK_bookinfo.bkcatalogid ) H on A.id = H.bkcatalogid "
			" left join (select STK_bookinfo.bkcatalogid,sum(E.amount) as wsaleamount, "
			" sum(E.FixedPrice) AS WsaleFixedPrice,sum(E.DiscountedPrice) as WsaleDiscountedPrice "
			" from BS_WsaleNoteHeader join BS_WsaleNote E ON BS_WsaleNoteHeader.ID = E.WsaleNtHeaderID join stk_bookinfo on E.bkinfoid = stk_bookinfo.id "
			" where 1=1 " + sqltime +
			" group by STK_bookinfo.bkcatalogid ) I on A.id = I.bkcatalogid left join "
			" (select bkcatalogid ,supplierid," + sqlstorage +
			" from (select bkcatalogid,supplierid,amount,stgid from stk_bookinfo ) as SourceTable "
			" pivot(sum(amount) for stgid in(" + sqlstorage + ")) as PivotTable) J on D.BkcatalogID = J.bkcatalogid and D.supplierid = J.supplierid "
			" WHERE (I.wsaleamount > 0 or H.retailamount > 0) " + sqlwhere + " and F.Name = '" + aq->FieldByName("name")->AsString + "' and D.id in(" + ssbkid + ")";
		*/
		aq1->Close();
		aq1->SQL->Clear();
		aq1->SQL->Add(sql1);
		aq1->Open();
		while (!aq1->Eof )
		{
            temptext = "\n";
			for(int j=2;j<dgdetail->Columns ->Count+1;j++)
			{
				if (dgdetail->Columns->Items[j-1]->Visible == true) {
					if (dgdetail->Columns ->Items [j-1]->FieldName == "Name") {
						AnsiString bookname;
						bookname = aq1->FieldByName(dgdetail->Columns ->Items [j-1]->FieldName )->AsAnsiString;
						bookname = StringReplace(bookname , ",",".",TReplaceFlags()<<rfReplaceAll);
						temptext = temptext + bookname + ",";
					}
					else
					{
						temptext = temptext + aq1->FieldByName(dgdetail->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
					}
				}
			}
			iFileLength   =   FileSeek(iFileHandle,0,2);
			FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
			aq1->Next();
		}
		FileClose(iFileHandle);
		aq->Next();
	}
	delete aq;
	delete aq1;

        ShowMsg(Handle ,"导出完毕！",3);
	return ;
}
//---------------------------------------------------------------------------


void __fastcall Tfrmretailbookup::edminChange(TObject *Sender)
{
	if (edmin->Text != "") {
		chbkinfo->Checked = true;
	}
	else if (edmax->Text != "") {
		chbkinfo->Checked = true;
	}
	else
	{
		chbkinfo->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmretailbookup::edlsminChange(TObject *Sender)
{
	if (edlsmin->Text != "") {
		chls->Checked = true;
	}
	else if (edlsmax->Text != "") {
		chls->Checked = true;
	}
	else
	{
		chls->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmretailbookup::edwsminChange(TObject *Sender)
{
	if (edwsmin->Text != "") {
		chws->Checked = true;
	}
	else if (edwsmax->Text != "") {
		chws->Checked = true;
	}
	else
	{
		chws->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmretailbookup::edpressKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r' && edpress->Text != "") {
		TADOQuery *aq = new TADOQuery(this);
		aq->Connection = fcon;
		AnsiString sql;
		sql = "select id,AbbreviatedName from BS_PressInfo where AbbreviatedName like '%" + edpress->Text.Trim() + "%'" ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		cbpress->Clear();
		while (!aq->Eof )
		{
			cbpress->AddItem(aq->FieldByName("AbbreviatedName")->AsAnsiString ,(TObject*)aq->FieldByName("id")->AsInteger );
			aq->Next();
		}
		aq->First();
		cbpress->ItemIndex = cbpress->Items->IndexOfObject((TObject*)aq->FieldByName("id")->AsInteger );
		delete aq;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmretailbookup::CheckBox1Click(TObject *Sender)
{
	if (rb2->Checked ) {
		for (int i = 15; i <= maxlen; i++) {
			dgdetail->Columns->Items[i]->Visible = true;
		}
	}
	else
	{
		dgdetail->Columns->Items[15]->Visible = false;
		dgdetail->Columns->Items[16]->Visible = false;
		dgdetail->Columns->Items[17]->Visible = false;
		dgdetail->Columns->Items[18]->Visible = false;
		dgdetail->Columns->Items[19]->Visible = false;
		dgdetail->Columns->Items[20]->Visible = false;
		dgdetail->Columns->Items[21]->Visible = false;
		dgdetail->Columns->Items[22]->Visible = false;
		dgdetail->Columns->Items[23]->Visible = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmretailbookup::N1Click(TObject *Sender)
{
	if (qudetail->IsEmpty() ) {
        return;
	}
	Tfrmbookhistory *frm = new Tfrmbookhistory(Application,fcon,fstgid,qudetail->FieldByName("bkcatalogid")->AsInteger );
	frm->Show();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmretailbookup::edsupplierKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r' && edsupplier->Text != "") {
		TADOQuery *aq = new TADOQuery(this);
		aq->Connection = fcon;
		AnsiString sql;                                                 // stgid="+IntToStr(fstgid)+"
		sql = "select id,name from CUST_CustomerInfo where  customerstate=1 and  name like '%" + edsupplier->Text.Trim() + "%' and type = 1 " ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		cbsupplier->Clear();
		while (!aq->Eof )
		{
			cbsupplier->AddItem(aq->FieldByName("name")->AsAnsiString ,(TObject*)aq->FieldByName("id")->AsInteger );
			aq->Next();
		}
		aq->First();
		cbsupplier->ItemIndex = cbsupplier->Items->IndexOfObject((TObject*)aq->FieldByName("id")->AsInteger );
		delete aq;
	}
}
//---------------------------------------------------------------------------


void __fastcall Tfrmretailbookup::dgdetailDblClick(TObject *Sender)
{
	if (qudetail->IsEmpty() ) {
    	return;
	}
	if (modle == 1) {
		Ord->AddNote(0,qudetail->FieldByName("bkcatalogid")->AsInteger );
	}
	if (modle == 2) {

	       	Diaobo->AddNote(qudetail->FieldByName("bkcatalogid")->AsInteger,qudetail->FieldByName("supplierid")->AsInteger);
	}
	if (modle == 3) {
	      //	Pro->AddNote(0 ,qudetail->FieldByName("bkcatalogid")->AsInteger );
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmretailbookup::dgdetailTitleClick(TColumn *Column)
{
	if (qudetail->RecordCount > 0) {
    	AnsiString qusort;
		qusort =  Column->FieldName + " ASC";
		if (qudetail->Sort == "") {
			qudetail->Sort =  Column->FieldName + " ASC";
		}
		else if (qudetail->Sort == qusort) {
			qudetail->Sort =  Column->FieldName + " DESC";
		}
		else
		{
			qudetail->Sort =  Column->FieldName + " ASC";
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmretailbookup::N2Click(TObject *Sender)
{
	if (qudetail->IsEmpty() || qudetail->RecordCount == 0 ) {
    	return;
	}
       try {

	if (dgdetail->SelectedRows->Count == 0)
	{
		ssbkid = ssbkid + "," + qudetail->FieldByName("id")->AsAnsiString ;
		strlist->AddObject(qudetail->FieldByName("id")->AsAnsiString,(TObject*)qudetail->FieldByName("id")->AsInteger);
	}
	else if (dgdetail->SelectedRows->Count > 0)
	{
		qudetail->Bookmark = dgdetail->SelectedRows->Items[0];
		ssbkid = ssbkid + "," + qudetail->FieldByName("id")->AsAnsiString ;
		strlist->AddObject(qudetail->FieldByName("id")->AsAnsiString,(TObject*)qudetail->FieldByName("id")->AsInteger);
		for (int i=1; i < dgdetail->SelectedRows->Count; i++)
		{
			qudetail->Bookmark = dgdetail->SelectedRows->Items[i];
			ssbkid = ssbkid + "," + qudetail->FieldByName("id")->AsAnsiString ;
			strlist->AddObject(qudetail->FieldByName("id")->AsAnsiString,(TObject*)qudetail->FieldByName("id")->AsInteger);
		}
	}
	else
		return;

	       //	qudetail->Refresh();
    } catch (...) {
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmretailbookup::dgdetailDrawColumnCell(TObject *Sender, const TRect &Rect,
          int DataCol, TColumn *Column, Grids::TGridDrawState State)
{
	if (strlist->IndexOf(dgdetail->DataSource->DataSet->FieldByName("id")->AsString) != -1) {
		dgdetail->Canvas->Font->Color = clRed ;
		dgdetail->Canvas->FillRect(Rect);
		dgdetail->DefaultDrawColumnCell(Rect,DataCol,Column,State);
	}
	else
	{
		dgdetail->DefaultDrawColumnCell(Rect,DataCol,Column,State);
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmretailbookup::N3Click(TObject *Sender)
{
	if (qudetail->IsEmpty() || qudetail->RecordCount == 0 ) {
    	return;
	}

	if (dgdetail->SelectedRows->Count == 0)
	{
		int e = strlist->IndexOf(qudetail->FieldByName("id")->AsAnsiString);
		if (e!= -1) {
			strlist->Delete(e);
			AnsiString ss;
			ss = "," + qudetail->FieldByName("id")->AsAnsiString;
			int d = ssbkid.Pos(ss);
			ssbkid = ssbkid.Delete(d,ss.Length());
		}
	}
	else if (dgdetail->SelectedRows->Count > 0)
	{
		qudetail->Bookmark = dgdetail->SelectedRows->Items[0];
		int e = strlist->IndexOf(qudetail->FieldByName("id")->AsAnsiString);
		if (e!= -1) {
			strlist->Delete(e);
			AnsiString ss;
			ss = "," + qudetail->FieldByName("id")->AsAnsiString;
			int d = ssbkid.Pos(ss);
			ssbkid = ssbkid.Delete(d,ss.Length());
		}
		for (int i=1; i < dgdetail->SelectedRows->Count; i++)
		{
			qudetail->Bookmark = dgdetail->SelectedRows->Items[i];
			int e = strlist->IndexOf(qudetail->FieldByName("id")->AsAnsiString);
			if (e!= -1) {
				strlist->Delete(e);
				AnsiString ss;
				ss = "," + qudetail->FieldByName("id")->AsAnsiString;
				int d = ssbkid.Pos(ss);
				ssbkid = ssbkid.Delete(d,ss.Length());
			}
		}
	}
	else
		return;
	try {
	       //	qudetail->Refresh();
    } catch (...) {
	}
}
//---------------------------------------------------------------------------


void __fastcall Tfrmretailbookup::N4Click(TObject *Sender)
{
	if (qudetail->RecordCount > 0) {
    	Tfrmhistoryview *frm = new Tfrmhistoryview(Application,fcon,qudetail->FieldByName("bkcatalogid")->AsInteger );
		frm->ShowModal();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmretailbookup::N5Click(TObject *Sender)
{



         if (qudetail->IsEmpty() || qudetail->RecordCount == 0 ) {
    	return;
	}
        dgdetail->DataSource->DataSet->DisableControls();
         while(!dgdetail->DataSource->DataSet->Eof)
         {
            dgdetail->SelectedRows->CurrentRowSelected = true;
            dgdetail->DataSource->DataSet->Next();
         }
        dgdetail->DataSource->DataSet->EnableControls();


       /*	if (qudetail->IsEmpty() || qudetail->RecordCount == 0 ) {
    	return;
	}

	if (dgdetail->SelectedRows->Count == 0)
	{
		ssbkid = ssbkid + "," + qudetail->FieldByName("id")->AsAnsiString ;
		strlist->AddObject(qudetail->FieldByName("id")->AsAnsiString,(TObject*)qudetail->FieldByName("id")->AsInteger);
	}
	else if (dgdetail->SelectedRows->Count > 0)
	{
		qudetail->Bookmark = dgdetail->SelectedRows->Items[0];
		ssbkid = ssbkid + "," + qudetail->FieldByName("id")->AsAnsiString ;
		strlist->AddObject(qudetail->FieldByName("id")->AsAnsiString,(TObject*)qudetail->FieldByName("id")->AsInteger);
		for (int i=1; i < dgdetail->SelectedRows->Count; i++)
		{
			qudetail->Bookmark = dgdetail->SelectedRows->Items[i];
			ssbkid = ssbkid + "," + qudetail->FieldByName("id")->AsAnsiString ;
			strlist->AddObject(qudetail->FieldByName("id")->AsAnsiString,(TObject*)qudetail->FieldByName("id")->AsInteger);
		}
	}
	else
		return;
	try {
		qudetail->Refresh();
    } catch (...) {
	}      */
}
//---------------------------------------------------------------------------


void __fastcall Tfrmretailbookup::N6Click(TObject *Sender)
{
	if (qudetail->IsEmpty() ) {
        return;
	}
         if (qudetail->IsEmpty() || qudetail->RecordCount == 0 ) {
    	return;
	}
        dgdetail->DataSource->DataSet->DisableControls();
         while(!dgdetail->DataSource->DataSet->Eof)
         {
            dgdetail->SelectedRows->CurrentRowSelected = false;
            dgdetail->DataSource->DataSet->Next();
         }
         dgdetail->DataSource->DataSet->EnableControls();
        /*
	AnsiString sql1 ;
	sql1 = sql = "update stk_bookinfo set selected = 0 where stgid = " + IntToStr(fstgid);

	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql1);
	aq->ExecSQL();
	delete aq;

	qudetail->Active = false;
	qudetail->Active = true;    */
}
//---------------------------------------------------------------------------

void __fastcall Tfrmretailbookup::chmaysyClick(TObject *Sender)
{
        showsiyang();
}
void Tfrmretailbookup::showsiyang()
{
   	if (chmaysy->Checked ) {
		dgdetail->Columns->Items[7]->Visible = true;
		dgdetail->Columns->Items[8]->Visible = true;
		dgdetail->Columns->Items[10]->Visible = true;
		dgdetail->Columns->Items[11]->Visible = true;
	}
	else
	{
		dgdetail->Columns->Items[7]->Visible = false;
		dgdetail->Columns->Items[8]->Visible = false;
		dgdetail->Columns->Items[10]->Visible = false;
		dgdetail->Columns->Items[11]->Visible = false;
	}

}

//---------------------------------------------------------------------------

void __fastcall Tfrmretailbookup::RzToolButton1Click(TObject *Sender)

{
//选中生成采购单
   if (qudetail->IsEmpty()) {
          return;
       }
   	AnsiString sql ;
	TBookmark bm;
	Screen->Cursor = crHourGlass ;
	sql = "delete BS_Temp_Caigou where  userid = " + IntToStr(fuserid);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
       bool tt= false;
       sql= "select * from BS_Temp_Caigou where 1=2";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	TLocateOptions   Opts;
	Opts.Clear();
	Opts   <<   loPartialKey;
	String   str ;
        TStringList *IDstr;
        IDstr = new TStringList(Null);
        IDstr->DelimitedText = ssbkid;
        IDstr->Delimiter=',';



	try
	{
           if (dgdetail->SelectedRows->Count==0) {
                MessageBox(NULL,"请先选择书目！","提示",MB_OK|MB_ICONINFORMATION);
		Screen->Cursor = crDefault ;
		return;
             }
		dgdetail->DataSource->DataSet->DisableControls();
	       	for (int i = 0 ; i < dgdetail->SelectedRows->Count ; i++) {

	       	 dgdetail->DataSource->DataSet->Bookmark = dgdetail->SelectedRows->Items[i];
	       	 bm = dgdetail->DataSource->DataSet->GetBookmark();
	       	 dgdetail->DataSource->DataSet->GotoBookmark(bm);


              //  AnsiString localid = IDstr->Strings[i];
              //  if (localid=="-1") {
              ///       continue;
              //  }
              // TLocateOptions  Opts;
             //  Opts.Clear();
              // Opts   <<   loPartialKey;
             //  dgdetail->DataSource->DataSet->Locate("id",localid,Opts);



                 //  tt =true;

			int cc = 0;

			if (aq->State != dsInsert) {
				aq->Append();
			}

			aq->FieldByName("supplierid")->AsInteger =dgdetail->DataSource->DataSet->FieldByName("supplierid")->AsInteger;;
			aq->FieldByName("bkcatalogid")->AsInteger = dgdetail->DataSource->DataSet->FieldByName("bkcatalogid")->AsInteger;
			
                        aq->FieldByName("amount")->AsInteger = dgdetail->DataSource->DataSet->FieldByName("retailamount")->AsInteger+dgdetail->DataSource->DataSet->FieldByName("wsaleamount")->AsInteger;
			aq->FieldByName("discount")->AsInteger =100;
                       // dgdetail->DataSource->DataSet->FieldByName("needprocurenum")->AsInteger;



			aq->FieldByName("userid")->AsInteger = fuserid;
			aq->Post();
                        dgdetail->DataSource->DataSet->Next();
		 }
	//}
	dgdetail->DataSource->DataSet->EnableControls() ;
	}catch(...)
	{
		MessageBox(NULL,"生成采购单失败！","提示",MB_OK|MB_ICONINFORMATION);
		Screen->Cursor = crDefault ;
		return;
	}


         if (!tt) {
           Screen->Cursor = crDefault ;
          // return;
        }

        ///////////////////////////////////////////////////开始生成导出单///////////////////////

         createproc();
         Screen->Cursor = crDefault;
         AnsiString caigoudanstr;
          caigoudanstr = "已成功生成"+returncode+"采购单！";
         MessageBox(NULL, caigoudanstr.c_str(),"先行者软件提醒",MB_OK|MB_ICONINFORMATION);
        Close();

}

 int Tfrmretailbookup::AddCaigou()
 {
           cmdAddNote->Parameters->ParamByName("@OperatorID")->Value = fuserid;
	cmdAddNote->Parameters->ParamByName("@StgID")->Value = fstgid;
	cmdAddNote->Parameters->ParamByName("@CODEMODE")->Value = 0;
	cmdAddNote->Parameters->ParamByName("@groupid")->Value = 0;
         cmdAddNote->Parameters->ParamByName("@ReturnCode")->Value =0;
	 cmdAddNote->Parameters->ParamByName("@Returnint")->Value=0 ;
	 cmdAddNote->Parameters->ParamByName("@return_value")->Value=0;
          cmdAddNote->Parameters->ParamByName("@ReturnCodeint")->Value=0;
	cmdAddNote->Execute();
	try
	{
		returncode =  cmdAddNote->Parameters->ParamByName("@ReturnCode")->Value ;
		sgfirsthid =  cmdAddNote->Parameters->ParamByName("@Returnint")->Value ;
		sgheaderid =  cmdAddNote->Parameters->ParamByName("@return_value")->Value;
                returncodeint = cmdAddNote->Parameters->ParamByName("@ReturnCodeint")->Value;
		return 1;
	}
	catch(...)
	{
		return 0;
	}
 }
 void Tfrmretailbookup::createproc()
 {

        	if (AddCaigou()!=1) {
		return;
	}
	AnsiString sql;
	sql = "select id from BS_ProcureNoteHeader where procureid in(" + returncodeint + ")" ;
               // pro->DelInvalidNtHeader();
		pro->QryNtHeader(sgfirsthid);
		pro->DBNavigator1->Enabled = true;
		pro->aqheader->Close();
		pro->aqheader->SQL->Clear();
		pro->aqheader->SQL->Add(sql);
		pro->aqheader->Open();

 }
//---------------------------------------------------------------------------

void __fastcall Tfrmretailbookup::FormShow(TObject *Sender)
{
 if (iscaigou) {
    RzToolButton1->Enabled=true;
 }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmretailbookup::edsupplierChange(TObject *Sender)

{
      	if (edsupplier->Text != "") {
		chsupplier->Checked = true;
	}
	else if (edsupplier->Text != "") {
		chsupplier->Checked = true;
	}
	else
	{
		chsupplier->Checked = false;
	}
}
//---------------------------------------------------------------------------


