//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ReturnStock.h"
#include "StorageReturnMngForm.h"
#include "global.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzDBCmbo"
#pragma link "RzEdit"
#pragma link "RzPanel"
#pragma link "RzRadChk"
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma resource "*.dfm"
TfrmReturnStock *frmReturnStock;
//---------------------------------------------------------------------------
__fastcall TfrmReturnStock::TfrmReturnStock(TComponent* Owner,TADOConnection *con,int userid,int stgid)
	: TForm(Owner)
{
	fuserid = userid;
	fstgid = stgid;
	fcon = con;
	query->Connection = fcon;
	aqsupplier->Connection = fcon;
	stops->Connection = fcon;
	stotk->Connection = fcon;

	linfo.app = Application ;
	linfo.con = fcon ;
	linfo.userID = fuserid ;
	linfo.storageID = fstgid ;

	aqsupplier->Active = true;
	while (!aqsupplier->Eof)
	{
		cbsupplier->AddItem(aqsupplier->FieldByName("Name")->AsAnsiString,(TObject*)aqsupplier->FieldByName("ID")->AsInteger );
		aqsupplier->Next();
	}
	aqsupplier->First();
	aqpress->Connection = fcon;
	aqpress->Active = true;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	AnsiString sql;
	sql = "select ID,Name from BS_BookType";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof)
	{
		cbtype->AddItem(aq->FieldByName("Name")->AsAnsiString,(TObject*)aq->FieldByName("ID")->AsInteger );
		cbtype1->AddItem(aq->FieldByName("Name")->AsAnsiString,(TObject*)aq->FieldByName("ID")->AsInteger );
		aq->Next();
	}
	sql = "select ID,Name from SYS_StorageInfo ";
    aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();

	while (!aq->Eof)
	{
		cbstorage->AddItem(aq->FieldByName("Name")->AsAnsiString,(TObject*)aq->FieldByName("ID")->AsInteger );
		cbstorage1->AddItem(aq->FieldByName("Name")->AsAnsiString,(TObject*)aq->FieldByName("ID")->AsInteger );
		sqlstorage = sqlstorage + "[" + aq->FieldByName("ID")->AsAnsiString + "],";
		aq->Next();
	}
    sqlstorage = sqlstorage.SubString(0,sqlstorage.Length()-1);
	cbstorage->ItemIndex = cbstorage->Items->IndexOfObject((TObject*)fstgid);
	cbstorage1->ItemIndex = cbstorage->Items->IndexOfObject((TObject*)fstgid);
	dtp1->Date = Date();
	dtp2->Date = Date();
	dtprk1->Date = Date();
	dtprk2->Date = Date();

	dtpstart->Date = Date();
	dtpend->Date = Date();
	dtpls1->Date = Date();
	dtpls2->Date = Date();
	dtp3->Date = Date();
    dtp4->Date = Date();
	delete aq;
	Tab1->Caption = "未动库存分析";
	DBGrid1->OnDrawColumnCell=DBGrid1DrawColumnCell;

}
//---------------------------------------------------------------------------

void __fastcall TfrmReturnStock::BtnViewClick(TObject *Sender)
{
	AnsiString sql;
        bool searched;
        searched = false;

	if (pc->TabIndex == 0) {
		sql = "exec USP_BS_UnSaleStock ";
		//店号
		if (chstorage->Checked && cbstorage1->Text != "") {
                searched = true;
			int ffstgid;
			try {
				ffstgid = (int)cbstorage1->Items->Objects[cbstorage1->ItemIndex];
				sql = sql + IntToStr(ffstgid) + ",";
			} catch (...) {

                                ShowMsg(Handle ,"请选择正确的店号！",3);
				return;
			}
		}
		else
		{
			sql = sql + "null,";
		}
		//状态
		if (chstate1->Checked && cbstate1->Text != "") {
                searched = true;
			int stateid;
			try {
				stateid = cbstate1->ItemIndex;
				sql = sql + IntToStr(stateid) + ",";
			} catch (...) {

                                ShowMsg(Handle ,"请选择正确的状态！",3);
				return;
			}
		}
		else
		{
			sql = sql + "null,";
		}
		//入库时间
		if (chrktime->Checked ) {
                searched = true;
			sql = sql + "'" + DateToStr(dtpstart->Date) + "','" + DateToStr(dtpend->Date) + "',";
		}
		else
		{
			sql = sql + "null,null,";
		}
		//零售时间
		if (chlstime->Checked ) {
                searched = true;
			sql = sql + "'" + DateToStr(dtpls1->Date) + "','" + DateToStr(dtpls2->Date) + "',";
		}
		else
		{
			sql = sql + "null,null,";
		}
		//发货时间
		if (chlstime->Checked ) {
                searched = true;
			sql = sql + "'" + DateToStr(dtp3->Date) + "','" + DateToStr(dtp4->Date) + "',";
		}
		else
		{
			sql = sql + "null,null,";
		}
		//零售数量
		if (chlsnum->Checked && edlsnum->Text != "") {
                searched = true;
			sql = sql + edlsnum->Text.Trim() + ",";
		}
		else
		{
			sql = sql + "null,";
		}
		//发货数量
		if (chwsnum->Checked && edwsnum->Text != "") {
                searched = true;
			sql = sql + edwsnum->Text.Trim() + ",";
		}
		else
		{
			sql = sql + "null,";
		}
		//ISBN
		if (chisbn->Checked && edbook->Text != "") {
                searched = true;
			sql = sql + edbook->Text.Trim() + ",";
		}
		else
		{
			sql = sql + "null,";
		}
		//书名
		if (chname->Checked && edname->Text != "") {
                        searched = true;
			sql = sql + edname->Text.Trim() + ",";
		}
		else
		{
			sql = sql + "null,";
		}
		//类别
		if (chtype->Checked && cbtype1->Text != "") {
                        searched = true;
			int type;
			try {
				type = (int)cbtype1->Items->Objects[cbtype1->ItemIndex];
				sql = sql + IntToStr(type) + ",";
			} catch (...) {

                                ShowMsg(Handle ,"请选择正确的类别！",3);
				return;
			}
		}
		else
		{
			sql = sql + "null,";
		}
		//供应商
		if (chsupplier->Checked && cbsupplier->Text != "") {
                        searched = true;
			int supplierid;
			try {
				supplierid = (int)cbsupplier->Items->Objects[cbsupplier->ItemIndex];
				sql = sql + IntToStr(supplierid);
			} catch (...) {

                                 ShowMsg(Handle ,"请选择正确的供应商！",3);
				return;
			}
		}
		else
		{
			sql = sql + "null";
		}
		sql = sql + ",'" + sqlstorage + "'";
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->Open();
		DBGrid1->Columns->Items[11]->Visible = false;
		DBGrid1->Columns->Items[12]->Visible = true;
		DBGrid1->Columns->Items[13]->Visible = true;
		DBGrid1->Columns->Items[14]->Visible = true;
	}
	else
	{
		sql = "select distinct dense_rank() over(order by D.id) as xuhao,D.id,A.id as bkcatalogid,A.Barcode,A.ISBN,A.price,A.name as bookname,A.userdefcode,A.author,A.presscount,convert(varchar(10),A.pressdate,120) as pressdate,"
				" B.AbbreviatedName,C.Name as typename,D.amount,D.amount*A.price as mayang,D.shiyang,convert(nvarchar(10),E.returndate,120) as returndate,D.back, "
				" F.name as suppliername,case D.back when 1 then '待通知' when 2 then '已通知' when 3 then '确定退货' when 4 then '已调回' end as state," + sqlstorage +
				" from bs_storagenote E left join BS_StorageNoteHeader G ON E.StgNtHeaderID = G.id "
				" join (select min(id) as id,sum(amount) as amount,supplierid,bkcatalogid,sum(amount * Cbprice) as shiyang,back from STK_BookInfo ";
		 if (chckbxShopNum->Checked ) {
                 searched = true;
			sql = sql + " where stgid = " + IntToStr(fstgid) ;
		 }

		 sql = sql + " group by supplierid,bkcatalogid,back)D on E.bkcatalogid = D.bkcatalogid and G.supplierid = D.supplierid "
				" left join BS_BookCatalog A on A.id = D.BkcatalogID "
				" left join BS_PressInfo B on A.pressid = B.id "
				" left join BS_BookType C on A.smallBookTypeID = C.id "
				" left join CUST_CustomerInfo F on D.Supplierid = F.id "
				" left join (select bkcatalogid ,supplierid," + sqlstorage +
				" from (select bkcatalogid,supplierid,amount,stgid from stk_bookinfo ) as SourceTable "
				" pivot(sum(amount) for stgid in(" + sqlstorage + ")) as PivotTable) J on D.BkcatalogID = J.bkcatalogid and D.supplierid = J.supplierid ";

		sql = sql + " where E.returndate is not null ";

		if (chckbxSupplier->Checked && edtSupplier2->Text != "" )
		{
                searched = true;
			sql = sql + " and F.name = '" + edtSupplier2->Text.Trim() + "'";
		}
		if (chckbxAmount->Checked )
		{      searched = true;
			if (edtAmountLow->Text != "") {
				try {
					StrToInt(edtAmountLow->Text);
				} catch (...) {

                                          ShowMsg(Handle ,"请输入正确的数量！",3);
					return;
				}
				sql = sql + " and D.amount >= " + edtAmountLow->Text;
			}
			if (edtAmountHigh->Text != "") {
				try {
					StrToInt(edtAmountHigh->Text);
				} catch (...) {

                                            ShowMsg(Handle ,"请输入正确的数量！",3);
					return;
				}
				sql = sql + " and D.amount <= " + edtAmountHigh->Text;
			}
		}
		if (chckbxPressCount->Checked && edtPress2->Text != "")
		{   searched = true;
			sql = sql + " and B.AbbreviatedName = '" + edtPress2->Text.Trim() + "'";
		}
		if (chckbxType->Checked )
		{    searched = true;
			sql = sql + " and C.name = '" + cbtype->Text.Trim() + "'";
		}

		/*if (chckbxShopNum->Checked && cbstorage->Text != "")
		{
			sql = sql + " and D.stgid = " + IntToStr(fstgid);
		}  */
		if (chbackdate->Checked ) {
                searched = true;
			sql = sql + " and datediff(day,'" + DateToStr(dtp1->Date) + "',E.returndate) >= 0 ";
			sql = sql + " and datediff(day,'" + DateToStr(dtp2->Date) + "',E.returndate) <= 0 ";
		}
		if (chrk->Checked ) {
                searched = true;
			sql = sql + " and datediff(day,'" + DateToStr(dtprk1->Date) + "',G.HdTime) >= 0 ";
			sql = sql + " and datediff(day,'" + DateToStr(dtprk2->Date) + "',G.HdTime) <= 0 ";
		}
		if (chstate->Checked && cbstate2->Text != "") {
                searched = true;
			sql = sql + " and D.back = " + IntToStr(cbstate2->ItemIndex);
		}

                if ( cbjiezhi->Checked) {
                searched = true;
                     sql = sql + " and datediff(day,'" + DateToStr(dtpjiezhi->Date) + "',G.hdtime) >= 0 ";
                }
                if (cbtuihuo->Checked) {
                searched = true;
                   sql = sql + " and datediff(day,getdate(),dateadd(d,"+edittianshu->Text.Trim()+",G.hdtime)) >=0 ";
                }
               
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->Open();
		DBGrid1->Columns->Items[11]->Visible = true;
		DBGrid1->Columns->Items[12]->Visible = false;
		DBGrid1->Columns->Items[13]->Visible = false;
		DBGrid1->Columns->Items[14]->Visible = false;
	}
	((TFloatField *)DBGrid1->DataSource->DataSet->FieldByName("mayang"))->DisplayFormat = "##0.00";
	((TFloatField *)DBGrid1->DataSource->DataSet->FieldByName("shiyang"))->DisplayFormat = "##0.00";

	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	sql = "select ID,Name from SYS_StorageInfo ";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	AnsiString ss = IntToStr(fstgid);
	int i = 0;
	while (!aq->Eof)
	{
		ss = aq->FieldByName("ID")->AsAnsiString ;
		try {
			DBGrid1->Columns->Items[16+i]->Field = query->FieldByName(ss);
			DBGrid1->Columns->Items[16+i]->Visible = true;
			DBGrid1->Columns->Items[16+i]->Title->Caption = aq->FieldByName("Name")->AsString ;
			aq->Next();
			i++;
		} catch (...) {
			aq->Next();
			i++;
		}
	}
	delete aq;
}
//---------------------------------------------------------------------------

void __fastcall TfrmReturnStock::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmReturnStock::FormClose(TObject *Sender, TCloseAction &Action)

{
	/*TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add("update stk_bookinfo set back = 0 where back = 1");
	aq->ExecSQL();
	delete aq;  */
	Action = caFree ;
}
//---------------------------------------------------------------------------


void __fastcall TfrmReturnStock::dtp2Change(TObject *Sender)
{
	chbackdate->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmReturnStock::dtp1Change(TObject *Sender)
{
	chbackdate->Checked = true;
}
//---------------------------------------------------------------------------


void __fastcall TfrmReturnStock::edtAmountLowChange(TObject *Sender)
{
	if (edtAmountLow->Text != "") {
		chckbxAmount->Checked = true;
	}
	else if (edtAmountHigh->Text != "") {
		chckbxAmount->Checked = true;
	}
	else
	{
		chckbxAmount->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmReturnStock::edtSupplier2Click(TObject *Sender)
{
	if (edtSupplier2->Text != "") {
		chckbxSupplier->Checked = true;
	}
	else
	{
    	chckbxSupplier->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmReturnStock::edtPress2Click(TObject *Sender)
{
	if (edtPress2->Text != "") {
		chckbxPressCount->Checked = true;
	}
	else
	{
    	chckbxPressCount->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmReturnStock::N1Click(TObject *Sender)
{
	if (query->IsEmpty() ) {
		return;
	}
	for (int i = 1; i <= query->RecordCount; i++) {
		DBGrid1->DataSource->DataSet->RecNo = i;
		DBGrid1->SelectedRows->CurrentRowSelected = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmReturnStock::N2Click(TObject *Sender)
{
	if (query->IsEmpty() )
	{
		return;
	}
	AnsiString sql;
	TLocateOptions   Opts;
	Opts.Clear();
	Opts   <<   loPartialKey;
	String   str   = query->FieldByName("ID")->AsAnsiString ;
	String ids = "";
	if (DBGrid1->SelectedRows->Count == 0)
	{
		ids = ids + query->FieldByName("ID")->AsString;
	}
	else if (DBGrid1->SelectedRows->Count > 0)
	{
		query->Bookmark = DBGrid1->SelectedRows->Items[0];
		ids = query->FieldByName("ID")->AsString;
		for (int i=1; i < DBGrid1->SelectedRows->Count; i++)
		{
			query->Bookmark = DBGrid1->SelectedRows->Items[i];
			ids = ids + "," + query->FieldByName("ID")->AsString;
		}
	}
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon ;
	sql = "update stk_bookinfo set back = 1 where id in (" + ids + ")";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	delete aq;
	query->Active = false;
	query->Active = true;
	query->Locate("ID",str,Opts);

}
//---------------------------------------------------------------------------

void __fastcall TfrmReturnStock::DBGrid1DrawColumnCell(TObject *Sender, const TRect &Rect,
		  int DataCol, TColumn *Column, Grids::TGridDrawState State)
{
	if (query->FieldByName("back")->AsInteger == 3 ) {
		DBGrid1->Canvas->FillRect(Rect);
		DBGrid1->Canvas->Font->Color  = clRed;
		DBGrid1->DefaultDrawColumnCell(Rect,DataCol,Column,State);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmReturnStock::N3Click(TObject *Sender)
{
	if (query->IsEmpty() )
	{
		return;
	}
	AnsiString sql;
	TLocateOptions   Opts;
	Opts.Clear();
	Opts   <<   loPartialKey;
	String   str   = query->FieldByName("ID")->AsAnsiString ;
	String ids = "";
	if (DBGrid1->SelectedRows->Count == 0)
	{
		ids = ids + query->FieldByName("ID")->AsString;
	}
	else if (DBGrid1->SelectedRows->Count > 0)
	{
		query->Bookmark = DBGrid1->SelectedRows->Items[0];
		ids = query->FieldByName("ID")->AsString;
		for (int i=1; i < DBGrid1->SelectedRows->Count; i++)
		{
			query->Bookmark = DBGrid1->SelectedRows->Items[i];
			ids = ids + "," + query->FieldByName("ID")->AsString;
		}
	}
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon ;
	sql = "update stk_bookinfo set back = 0 where id in (" + ids + ")";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	delete aq;
	query->Active = false;
	query->Active = true;
	query->Locate("ID",str,Opts);
}
//---------------------------------------------------------------------------

void __fastcall TfrmReturnStock::BtnFastForwardClick(TObject *Sender)
{
	if (query->IsEmpty() ) {
		return;
	}
	AnsiString sql;
	TLocateOptions   Opts;
	Opts.Clear();
	Opts   <<   loPartialKey;
	String   str   = query->FieldByName("ID")->AsAnsiString ;
	int sgfirsthid;
	returncode = "";
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	sql = " select * from stk_bookinfo join (select distinct bkcatalogid,supplierid from stk_bookinfo where back = 1) A"
		" on  stk_bookinfo.bkcatalogid = A.bkcatalogid and stk_bookinfo.supplierid = A.supplierid "
		" where stk_bookinfo.stgid <> " + IntToStr(fstgid) + " and stk_bookinfo.amount > 0 ";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	if (aq->IsEmpty()) {
		ShowMsg(this->Handle,"所有需要退货的库存都在本店，不需调回！",3);
		sql = "update stk_bookinfo set back = 0 where back = 1";
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->ExecSQL();
		delete aq;
		query->Active = false;
		query->Active = true;
		query->Locate("ID",str,Opts);
		return;
	}
	delete aq;

	stops->Parameters->ParamByName("@stgid")->Value = fstgid;
	stops->Parameters->ParamByName("@userid")->Value = fuserid;
	stops->Parameters->ParamByName("@ReturnCode")->Value = "";
	stops->Parameters->ParamByName("@Returnint")->Value = "0";
	stops->ExecProc();

	AnsiString returncode = stops->Parameters->ParamByName("@ReturnCode")->Value;
	if (returncode == "") {
		ShowMsg(Handle ,"所有需要退货的库存都在本店，不需调回！",3);
	}
	else
	{
		ShowMsg(Handle ,"已通知各店进行调回！",3);
	}

	query->Active = false;
	query->Active = true;
	query->Locate("ID",str,Opts);
}
//---------------------------------------------------------------------------

void __fastcall TfrmReturnStock::BtnLastRecordClick(TObject *Sender)
{
	AnsiString sql;
	int sgfirstid,sgheaderid;
	returncode = "";
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	sql = "select * from stk_bookinfo where back = 3 and amount > 0";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	if (aq->IsEmpty() ) {
		delete aq;
		return;
	}

	if (MessageBoxA(0,"确认退货？","询问",MB_ICONQUESTION|MB_OKCANCEL)!=1 )
	{
		return;
    }

	stotk->Parameters->ParamByName("@userid")->Value = fuserid;
	stotk->Parameters->ParamByName("@StgID")->Value = fstgid;
	stotk->Parameters->ParamByName("@ReturnCode")->Value = "";
	stotk->Parameters->ParamByName("@Returnint")->Value = -1;
	stotk->ExecProc();
	returncode =  stotk->Parameters->ParamByName("@ReturnCode")->Value ;
	sgfirstid =  stotk->Parameters->ParamByName("@Returnint")->Value ;
	sgheaderid =  stotk->Parameters->ParamByName("@return_value")->Value;

	delete aq;

	returncode = "已生成入库退货单：\n" + returncode + "\n是否查看？";
	sql = "select * from BS_StorageNoteHeader where id >= " + IntToStr(sgfirstid) + " and id <= " + IntToStr(sgheaderid) ;
	if (MessageBoxA(0,returncode.c_str(),"询问",MB_ICONQUESTION|MB_OKCANCEL)==1 )
	{
	//转入库单查询
		TfrmStorageReturnMng * frm = new TfrmStorageReturnMng(Application);
		frm->Init(&linfo);
		frm->QryNtHeader(sgfirstid);
		frm->editdanhao->Text = frm->dsetNtHeader->FieldByName("StgNtCodeStr")->AsAnsiString ;
		frm->SaveOrNot = true;
		frm->BtnSave->Enabled = false;
		frm->dbnbedtAddCosts->Enabled = false;
		frm->membk->Enabled = false;
		frm->dblkpcbbSupplierID->Enabled = false;
		frm->sbnewcustomer->Enabled = false;
		frm->querydan->Connection = linfo.con;
		frm->querydan->Close();
		frm->querydan->SQL->Clear();
		frm->querydan->SQL->Add(sql);
		frm->querydan->Open();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmReturnStock::cbstate2Change(TObject *Sender)
{
	if (cbstate2->Text == "") {
		chstate->Checked = false;
	}
	else
	{
    	chstate->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmReturnStock::BtnAlignBottomClick(TObject *Sender)
{
    WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmReturnStock::DBGrid1TitleClick(TColumn *Column)
{
	if (query->IsEmpty() ) {
    	return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (query->Sort == "") {
		query->Sort =  Column->FieldName + " ASC";
	}
	else if (query->Sort == qusort) {
		query->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		query->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmReturnStock::cbtypeChange(TObject *Sender)
{
	if (cbtype->Text != "") {
		chckbxType->Checked = true;
	}
	else
	{
		chckbxType->Checked = false;
	}
}
//---------------------------------------------------------------------------
//Excel导出函数
bool TfrmReturnStock::DbgridToExcel(TDBGrid* dbg)
{
	if (dbg->DataSource ->DataSet->IsEmpty() ) {
        return false;
	}
	AnsiString temptext,path;
	int k = dbg->DataSource ->DataSet ->RecordCount ,n=0;

	savedlg->FileName = this->Caption;
	if (savedlg->Execute())
	{
		String DBPath,Name;
		DBPath = Sysutils::ExtractFilePath(savedlg->FileName .c_str());
		Name = Sysutils::ExtractFileName(savedlg->FileName .c_str() );
		DBPath = DBPath + Name + ".csv";
		path =  DBPath;
	}
	else
	{
		return false;
	}
	int  iFileHandle;
	int   iFileLength;
	if(FileExists(path))
	   if (DeleteFileA(path))
			iFileHandle = FileCreate(path.c_str());
	   else
			return false;
	else
		iFileHandle = FileCreate(path.c_str());

	int t1= 0;
	for(int q=0;q<dbg->FieldCount ;++q)
	{
		if (dbg->Columns->Items[q]->Visible == true) {
			t1++;
			temptext = temptext + dbg->Columns ->Items [q]->Title ->Caption + ",";
		}
	}
	iFileLength   =   FileSeek(iFileHandle,0,2);
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	dbg->DataSource ->DataSet->DisableControls();
	dbg->DataSource ->DataSet ->First();
	while(!dbg->DataSource ->DataSet->Eof)
	{
		temptext = "\n";
		for(int j=1;j<dbg->Columns ->Count+1  ;j++)
		{
			if (dbg->Columns->Items[j-1]->Visible == true) {
				if (dbg->Columns ->Items [j-1]->FieldName == "ISBN") {
					if (dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString != "") {
						temptext = temptext + "'" + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
					}
					else
					{
                    	temptext = temptext + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
					}
				}
				else if (dbg->Columns ->Items [j-1]->FieldName == "Name2") {
					AnsiString bookname;
					int len;
					bookname = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					bookname = StringReplace(bookname , ",",".",TReplaceFlags()<<rfReplaceAll);
					temptext = temptext + bookname + ",";
				}
				else
				{
                	t1++;
					temptext = temptext + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
				}
			}
		}
		iFileLength   =   FileSeek(iFileHandle,0,2);
		FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
		dbg->DataSource ->DataSet ->Next() ;
	}
	dbg->DataSource ->DataSet->EnableControls();

	FileClose(iFileHandle);


         ShowMsg(Handle ,"导出完毕！",3);
	return false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmReturnStock::RzToolButton1Click(TObject *Sender)
{
	if (query->IsEmpty() ) {
    	return;
	}
	DbgridToExcel(DBGrid1);
}
//---------------------------------------------------------------------------

void __fastcall TfrmReturnStock::edtSupplier1KeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		if (edtSupplier1->Text != "") {
			AnsiString sql;
			sql = "select ID,Name from CUST_CustomerInfo where type = 1 and customerstate=1 and stgid="+IntToStr(fstgid)+" and name like '%" + edtSupplier1->Text.Trim() + "%'";
			aqsupplier->Close();
			aqsupplier->SQL->Clear();
			aqsupplier->SQL->Add(sql);
			aqsupplier->Open();
			if (aqsupplier->RecordCount > 0) {
            	aqsupplier->First();
				edtSupplier2->KeyValue = aqsupplier->FieldByName("ID")->AsInteger ;
				chckbxSupplier->Checked = true;
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmReturnStock::edtPressCount1KeyPress(TObject *Sender, wchar_t &Key)

{
	if ((Key < '0' || Key > '9')&&(Key !='.')&&(Key != '\b')) {
		Key = NULL;
	}
	if (Key == '\r') {
		if (edtPressCount1->Text != "") {
			AnsiString sql;
			sql = "select ID,AbbreviatedName from BS_PressInfo where AbbreviatedName like '%" + edtPressCount1->Text.Trim() + "%'";
			aqpress->Close();
			aqpress->SQL->Clear();
			aqpress->SQL->Add(sql);
			aqpress->Open();
			if (aqpress->RecordCount > 0) {
				aqpress->First();
				edtPress2->KeyValue = aqpress->FieldByName("ID")->AsInteger ;
				chckbxPressCount->Checked = true;
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmReturnStock::dtpstartChange(TObject *Sender)
{
	chrktime->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmReturnStock::dtpls1Change(TObject *Sender)
{
	chlstime->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmReturnStock::dtp3Change(TObject *Sender)
{
	chwstime->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmReturnStock::edbookChange(TObject *Sender)
{
	if (edbook->Text == "") {
		chisbn->Checked = false;
	}
	else
	{
		chisbn->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmReturnStock::ednameChange(TObject *Sender)
{
	if (edname->Text != "") {
		chname->Checked = true;
	}
	else
	{
		chname->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmReturnStock::cbstate1Change(TObject *Sender)
{
	if (cbstate1->Text != "") {
		chstate1->Checked = true;
	}
	else
	{
    	chstate1->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmReturnStock::edlsnumChange(TObject *Sender)
{
	if (edlsnum->Text != "") {
		chlsnum->Checked = true;
	}
	else
	{
    	chlsnum->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmReturnStock::edwsnumChange(TObject *Sender)
{
	if (edwsnum->Text != "") {
		chwsnum->Checked = true;
	}
	else
	{
    	chwsnum->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmReturnStock::cbtype1Change(TObject *Sender)
{
	if (cbtype1->Text != "") {
		chtype->Checked = true;
	}
	else
	{
    	chtype->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmReturnStock::cbsupplierChange(TObject *Sender)
{
	if (cbsupplier->Text != "") {
		chsupplier->Checked = true;
	}
	else
	{
    	chsupplier->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmReturnStock::edsupplierKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		if (edsupplier->Text == "") {
            return;
		}
        TADOQuery *aq = new TADOQuery(this);
		aq->Connection = fcon;
		AnsiString sql;
		sql = "select ID,Name from CUST_CustomerInfo where type = 1  and customerstate=1 and stgid="+IntToStr(fstgid)+" and name like '%" + edsupplier->Text.Trim() + "%'";
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
        cbsupplier->Clear();
		while (!aq->Eof)
		{
			cbsupplier->AddItem(aq->FieldByName("Name")->AsAnsiString,(TObject*)aq->FieldByName("ID")->AsInteger );
			aq->Next();
		}
		if (aq->RecordCount > 0) {
        	aq->First();
			cbsupplier->ItemIndex = cbsupplier->Items->IndexOfObject((TObject*)aq->FieldByName("ID")->AsInteger);
        	chsupplier->Checked = true;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmReturnStock::N4Click(TObject *Sender)
{
	if (query->IsEmpty() )
	{
		return;
	}
	AnsiString sql;
	TLocateOptions   Opts;
	Opts.Clear();
	Opts   <<   loPartialKey;
	String   str   = query->FieldByName("ID")->AsAnsiString ;
	String ids = "";
	if (DBGrid1->SelectedRows->Count == 0)
	{
		ids = ids + query->FieldByName("ID")->AsString;
	}
	else if (DBGrid1->SelectedRows->Count > 0)
	{
		query->Bookmark = DBGrid1->SelectedRows->Items[0];
		ids = query->FieldByName("ID")->AsString;
		for (int i=1; i < DBGrid1->SelectedRows->Count; i++)
		{
			query->Bookmark = DBGrid1->SelectedRows->Items[i];
			ids = ids + "," + query->FieldByName("ID")->AsString;
		}
	}
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon ;
	sql = "update stk_bookinfo set back = 3 where id in (" + ids + ") and amount > 0";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	delete aq;
	query->Active = false;
	query->Active = true ;
	query->Locate("ID",str,Opts);
}
//---------------------------------------------------------------------------

void __fastcall TfrmReturnStock::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F1)  //查询
	{
		if (!BtnView->Enabled ) {
			return;
		}
		BtnView->Click();
	}
	if (Key == VK_F2) {   //导出
		if (!RzToolButton1->Enabled ) {
			return;
		}
		RzToolButton1->Click();
	}
	if (Key == VK_F3) {   //通知各店
		if (!BtnFastForward->Enabled ) {
			return;
		}
		BtnFastForward->Click();
	}
	if (Key == VK_F4) {   //生成退货单
		if (!BtnLastRecord->Enabled ) {
			return;
		}
		BtnLastRecord->Click();
	}

	if (Shift.Contains(ssAlt)&& Key ==81  ) {
		BtnExit->Click();
	}
	if (Shift.Contains(ssAlt)&& Key ==78  ) {
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssAlt)&& Key ==90) {
		WindowState = wsNormal  ;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmReturnStock::edtAmountHighKeyPress(TObject *Sender, wchar_t &Key)

{
if ((Key < '0' || Key > '9')&&(Key !='.')&&(Key != '\b')) {
		Key = NULL;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmReturnStock::edtAmountLowKeyPress(TObject *Sender, wchar_t &Key)

{
if ((Key < '0' || Key > '9')&&(Key !='.')&&(Key != '\b')) {
		Key = NULL;
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmReturnStock::pcChange(TObject *Sender)
{
     //
     BtnView->Click();
}
//---------------------------------------------------------------------------

void __fastcall TfrmReturnStock::N6Click(TObject *Sender)
{
    //
    //DBGrid1->DataSource->DataSet->
    //  query->DataSource->DataSet->Delete();

}
//---------------------------------------------------------------------------

