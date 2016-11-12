//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "stackquery.h"
#include "pdutil.h"
#include "global.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "MDIChild"
#pragma link "RzLabel"
#pragma link "RzPanel"
#pragma link "RzButton"
#pragma link "RzRadChk"
#pragma link "RzDBEdit"
#pragma link "RzDBGrid"
#pragma link "RzEdit"
#pragma link "RzDBDTP"
#pragma link "RzDTP"
#pragma link "RzDBCmbo"
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma resource "*.dfm"
Tfrmstackquery *frmstackquery;
//---------------------------------------------------------------------------
__fastcall Tfrmstackquery::Tfrmstackquery(TComponent* Owner)
	: TfrmMDIChild(Owner)
	,m_sql("")
{
	m_module = MTBsqry;
}
//---------------------------------------------------------------------------
void Tfrmstackquery::Init(LandInfo* li)
{
	TfrmMDIChild::Init(li);
	this->WindowState = wsMaximized ;
	qry1->Connection = m_con;
	tblPress->Connection = m_con;
	dsetCatlog->Connection = m_con;
	tblCatalogType->Connection = m_con;
	tbl1supplier->Connection = m_con;
	tbl2supplier->Connection = m_con;
    tblStore ->Connection = m_con;
	aquery->Connection = m_con;
	tbllocal->Connection = m_con;
	aq1supplier->Connection = m_con;
	aq1supplier->Active = true;
	tbllocal->Active = true;
	aqpress->Connection = m_con ;
	aqpress->Active = true;
	//-------------------
	tbllocal->Filtered = false;
	tbllocal->Filter = "stgid ="+IntToStr(m_storageID);
    tbllocal->Filtered = true;

    tblStore->Active = true;
	tblCatalogType->Active = true;
	edtstore->KeyValue = m_storageID ;
	chckbxShopNum->Checked = true;
	TADOQuery * aq;
	AnsiString sql;
	sql = "select Master from SYS_StorageInfo where id = " + IntToStr(m_storageID);
	aq = new TADOQuery(this);
	aq->Connection = m_con ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	if (aq->FieldByName("Master")->AsBoolean) {
		chckbxShopNum->Enabled = true;
		edtstore->Enabled = true;
	}
	else
	{
		chckbxShopNum->Enabled = false;
		edtstore->Enabled = false;
	}
	sql = "select ID,Name from sys_user where stgid = " + IntToStr(m_storageID);
    aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof )
	{
		cbstaff->AddItem(aq->FieldByName("Name")->AsAnsiString ,(TObject*)aq->FieldByName("ID")->AsInteger );
		aq->Next();
	}
	delete aq;
	Desic = QueryDesic();
	DBGridEh1->Columns->Items[14]->DisplayFormat = Desic;
	DBGridEh1->Columns->Items[15]->DisplayFormat = Desic;
	DBGridEh1->Columns->Items[14]->Footer->DisplayFormat = Desic;
	DBGridEh1->Columns->Items[15]->Footer->DisplayFormat = Desic;
}
void __fastcall Tfrmstackquery::FormClose(TObject *Sender, TCloseAction &Action)

{
	Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmstackquery::btnExit4Click(TObject *Sender)
{
	Close();
}
//------------------------------------------------
 String Tfrmstackquery::QueryDesic()
 {
	TADOQuery * aq;
	aq = new TADOQuery(this);
	aq->Connection = m_con ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add("select bk from sys_bsset where name ='xiaoshudian'");
	aq->Open();
	return "￥###,###,##" + aq->FieldByName("bk")->AsAnsiString ;
	delete aq;
 }
//---------------------------------

String Tfrmstackquery::QueryCom()
{
	String tmpsql="";

	if (chckbxStartTime ->Checked ) {
		tmpsql = tmpsql + " and datediff(day,H.adjustDate,'" + DateToStr(dtedtStart->Date)  + "') >= 0" ;
	}
	if (chckbxEndTime ->Checked ) {
		tmpsql = tmpsql + " and datediff(day,H.adjustDate,'" + DateToStr(dtedtEnd->Date)  + "') <= 0" ;
	}
	if (chckbxBookName->Checked )
	{
		tmpsql = tmpsql + " and C.Name like '%" + edtBookName->Text + "%'" ;
	}
	if (chckbxISBN->Checked )
	{
		tmpsql = tmpsql + " and C.ISBN like '%" + edtISBN->Text + "%'" ;
	}
	if (chckbxSupplier->Checked )
	{
		tmpsql = tmpsql + " and CUST_CustomerInfo.Name = '" + edtSupplier->Text +"'";
	}
	if (chckbxUserDefNum->Checked)
	{
		tmpsql = tmpsql + " and C.userdefcode like '%" + edtUserDefNum->Text +"%'";
	}
	if (chckbxPrice->Checked )
	{
		if(edtPrice->Text == "" )
		{}
		else
		{
			tmpsql = tmpsql + " and C.price = " + edtPrice->Text ;
		}
	}
	if (chckbxAuthor->Checked )
	{
		tmpsql = tmpsql + " and C.Author like '%"+ edtAuthor->Text +"%')";
	}
	if (chckbxPressCount->Checked )
	{
		tmpsql = tmpsql + " and D.AbbreviatedName = '" + edtPressCount->Text +"'";
	}
	if (chckbxType->Checked )
	{
		tmpsql = tmpsql + " and E.Name = '"+ edtType->Text +"'";
	}

	if (chckbxShopNum->Checked )
	{   edtShopNum->Text= edtstore->Text;
		if (edtShopNum->Text == "")
		{}
		else
		{
			tmpsql = tmpsql + " and G.Name = '"+ edtstore->Text +"'";
		}
	}
	if (rzlocal->Checked ) {
		if (edtlocal->Text =="") {

		}else
		{
			String local = edtlocal->Text ;
			tmpsql = tmpsql + " and A.LocalName = '" +  edtlocal->Text +"'";
		}
	}
	if (chstaff->Checked && cbstaff->Text != "") {
		tmpsql = tmpsql + " and I.Name = '" +  cbstaff->Text +"'";
	}
	if (chinlocal->Checked && edintlocal->Text != "") {
		tmpsql = tmpsql + " and A.InputLocalname = '" +  edintlocal->Text +"'";
	}

	return  tmpsql;
}
//---------------------------------
void __fastcall Tfrmstackquery::btnExit1Click(TObject *Sender)
{
	Query();
}
//---------------------------------------------------------------------------

void Tfrmstackquery::Query()
{
	AnsiString sql;
	sql = "select A.Supplier as suppliername,A.NoteCode as code,A.Amount,A.actualamount as ykamount,A.LocalName,A.InputLocalname, "
			" A.Amount*C.Price as adjustmayang,B.Cbprice*A.Amount as asjusetshiyang,C.ISBN,C.name,C.price,C.Author,C.userdefcode, "
			" D.AbbreviatedName,E.Name AS typename,G.Name as storagename,I.name as Adjustemployee "
			" from STK_stackAdjustNote A left join STK_BookInfo B on A.STK_bookInfoID = B.id "
			" left join BS_BookCatalog C on B.bkcatalogID = C.id "
			" left join BS_PressInfo D ON C.PressID = D.id "
			" left join BS_BookType E ON C.smallBookTypeID = E.id "
			" left join SYS_StorageInfo G ON B.stgid = G.id "
			" left join STK_stackAdjustHead H on A.NoteCode = H.number "
			" left join sys_user I on H.employ = I.id where 1 = 1 ";
	sql = sql + QueryCom();

	qry1->Active = false;
	qry1->SQL ->Clear();
	qry1->SQL ->Add(sql);
	try
	{
		qry1->Active = true;
	} catch (...)
	{
		//ShowMessage("出错！");
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmstackquery::edtISBNKeyPress(TObject *Sender, wchar_t &Key)
{
	if(Key == VK_RETURN)
	{
		if(chckbxISBN->Checked )
		{
			if(edtISBN->Text .Length() != 13 )
			{
				ShowMessage("位数不正确！");
				return;
			}
			for(int i=1;i<edtISBN->Text .Length();i++ )
			if(edtISBN->Text .SubString(i,1)>='0'&&edtISBN->Text .SubString(i,1)<='9'  )
			continue;
			else
			{
				ShowMessage("请输入数字！");
				return;
			}
		}
	}

}
//---------------------------------------------------------------------------


void __fastcall Tfrmstackquery::btnExit2Click(TObject *Sender)
{
		//Excel导出
	if (qry1->Active  && qry1->RecordCount >= 1)
	{
		DbgridToExcel(DBGridEh1);
	}
}
//---------------------------------------------------------------------------
//Excel导出函数
bool __fastcall Tfrmstackquery::DbgridToExcel(TDBGridEh* dbg)
{
	AnsiString temptext,path;
	int k = dbg->DataSource ->DataSet ->RecordCount ,n=0;

	if (savedlg->Execute())
	{
		String DBPath,Name;
		DBPath = ExtractFilePath(savedlg->FileName .c_str()  );
		Name = ExtractFileName(savedlg->FileName .c_str() );
		DBPath = DBPath + Name + ".csv";
		path =  DBPath;
	}else return false;
	int  iFileHandle;
	int   iFileLength;
	if(FileExists(path))
	   iFileHandle = FileOpen(path.c_str() ,fmOpenReadWrite);
	else
		iFileHandle = FileCreate(path.c_str());

	for(int q=0;q<dbg->FieldCount ;++q)
	{
		if (dbg->Columns->Items[q]->Visible == true) {
			temptext = temptext + dbg->Columns ->Items [q]->Title ->Caption + ",";
		}
	}

	iFileLength   =   FileSeek(iFileHandle,0,2);
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	int t2 = dbg->DataSource ->DataSet ->RecordCount ;

	dbg->DataSource ->DataSet ->First();
	dbg->DataSource ->DataSet->DisableControls();
	for(int   i=2+n;i<=t2+1+n ;i++)
	{
		temptext = "\n";
		for(int j=1;j<dbg->Columns ->Count+1  ;j++)
		{
			if (dbg->Columns->Items[j-1]->Visible == true) {
				temptext = temptext + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->DisplayText+ "," ;
			}
		}
		iFileLength   =   FileSeek(iFileHandle,0,2);
		FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
		dbg->DataSource ->DataSet ->Next() ;
	}
    dbg->DataSource ->DataSet->EnableControls();

	temptext = "\n";
	for(int q=0;q<dbg->FieldCount ;++q)
	{
		if (dbg->Columns->Items[q]->Visible == true) {
			temptext = temptext + dbg->GetFooterValue(0,dbg->Columns->Items[q]) + ",";
		}
	}
	iFileLength   =   FileSeek(iFileHandle,0,2);
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	FileClose(iFileHandle);
	ShowMsg(this->Handle,"导出完毕！",3);
	return false;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmstackquery::edtBookNameChange(TObject *Sender)
{
	if (edtBookName->Text != "") {
		chckbxBookName->Checked = true;
	}
	else
	{
    	chckbxBookName->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmstackquery::edtPriceChange(TObject *Sender)
{
	if (edtPrice->Text != "") {
		chckbxPrice->Checked = true;
	}
	else
	{
		chckbxPrice->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmstackquery::edtPressCountClick(TObject *Sender)
{
	if (edtPressCount->Text != "") {
		chckbxPressCount->Checked = true;
	}
	else
	{
		chckbxPressCount->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmstackquery::edtstoreClick(TObject *Sender)
{
	if (edtstore->Text != "") {
		chckbxShopNum->Checked = true;
		int storage = tblStore->FieldByName("ID")->AsInteger ;
		tbllocal->Active = false;
		tbllocal->Filtered = true;
		tbllocal->Filter = "StgID = " + IntToStr(storage);
		tbllocal->Active = true;

		TADOQuery *aq = new TADOQuery(this);
		aq->Connection = m_con ;
		AnsiString sql;
		sql = "select ID,Name from sys_user where stgid = " + IntToStr(storage);
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		cbstaff->Items ->Clear();
		while (!aq->Eof )
		{
			cbstaff->AddItem(aq->FieldByName("Name")->AsAnsiString ,(TObject*)aq->FieldByName("ID")->AsInteger );
			aq->Next();
		}
		delete aq;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmstackquery::edtISBNChange(TObject *Sender)
{
	if (edtISBN->Text != "") {
		chckbxISBN->Checked = true;
	}
	else
	{
		chckbxISBN->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmstackquery::edtAuthorChange(TObject *Sender)
{
	if (edtAuthor->Text != "") {
		chckbxAuthor->Checked = true;
	}
	else
	{
		chckbxAuthor->Checked = false;
	}
}
//---------------------------------------------------------------------------



void __fastcall Tfrmstackquery::edtlocalClick(TObject *Sender)
{
	if (edtlocal->Text != "") {
		rzlocal->Checked = true;
	}
	else
	{
		rzlocal->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmstackquery::edtSupplierClick(TObject *Sender)
{
	if (edtSupplier->Text != "") {
		chckbxSupplier->Checked = true;
	}
	else
	{
		chckbxSupplier->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmstackquery::edtTypeClick(TObject *Sender)
{
	if (edtType->Text != "") {
		chckbxType->Checked = true;
	}
	else
	{
		chckbxType->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmstackquery::edtUserDefNumChange(TObject *Sender)
{
	if (edtUserDefNum->Text != "") {
		chckbxUserDefNum->Checked = true;
	}
	else
	{
		chckbxUserDefNum->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmstackquery::DBGridEh1TitleClick(TColumnEh *Column)
{
	if (qry1->IsEmpty() ) {
		return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (qry1->Sort == "") {
		qry1->Sort =  Column->FieldName + " ASC";
	}
	else if (qry1->Sort == qusort) {
		qry1->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		qry1->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmstackquery::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmstackquery::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F6) {      //导出
		btnExit2->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 70 ) {    //查询
		btnExit1->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 78 ) {    //最小化
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 81 ) {    //退出
		btnExit4->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==90) {   //恢复窗口
		WindowState = wsNormal  ;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmstackquery::edtSupplier1KeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == VK_RETURN) {
		String sql = "select ID,Name from CUST_CustomerInfo where type = 1 and stgid="+IntToStr(m_storageID)+" and Name like '%" + edtSupplier1->Text + "%'";
		aq1supplier->Close();
		aq1supplier->SQL->Clear();
		aq1supplier->SQL->Add(sql);
		aq1supplier->Open();
		aq1supplier->First();
		edtSupplier->KeyValue = aq1supplier->FieldByName("ID")->AsInteger ;
		//tbl1supplier->Edit();
		//tbl1supplier->FieldByName("SupplierID")->AsInteger = aq1supplier->FieldByName("ID")->AsInteger;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmstackquery::edtPressCount1KeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == VK_RETURN) {
		String sql = "select ID,PresentNum,AbbreviatedName from BS_PressInfo where AbbreviatedName like '%" + edtPressCount1->Text + "%'";
		aqpress->Close();
		aqpress->SQL->Clear();
		aqpress->SQL->Add(sql);
		aqpress->Open();
		aqpress->First();
		edtPressCount->KeyValue = aqpress->FieldByName("ID")->AsInteger ;
		//dsetCatlog->Edit();
		//dsetCatlog->FieldByName("PressID")->AsInteger = aqpress->FieldByName("ID")->AsInteger;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmstackquery::edtPriceKeyPress(TObject *Sender, wchar_t &Key)

{
	if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key !='.')&&(Key != '\b')) {
	  	Key = NULL;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmstackquery::cbstaffChange(TObject *Sender)
{
	if (cbstaff->Text != "") {
		chstaff->Checked = true;
	}
	else
	{
    	chstaff->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmstackquery::edintlocalClick(TObject *Sender)
{
	if (edintlocal->Text != "") {
		chinlocal->Checked = true;
	}
	else
	{
		chinlocal->Checked = false;
	}
}
//---------------------------------------------------------------------------

