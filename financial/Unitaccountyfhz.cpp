//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unitaccountyfhz.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "RpBase"
#pragma link "RpCon"
#pragma link "RpConDS"
#pragma link "RpDefine"
#pragma link "RpRave"
#pragma link "RpSystem"
#pragma resource "*.dfm"
Taccountyfhz *accountyfhz;
//---------------------------------------------------------------------------
__fastcall Taccountyfhz::Taccountyfhz(TComponent* Owner,int Type,TADOConnection *cn,int stgid)
	: TForm(Owner)
{
  	type = Type;
	fcon = cn;
        fstgid = stgid;
	aqcustom->Connection = cn;
	aquery->Connection = cn;
	if (type == 1) {
	   this->Caption = "应付汇总";
	}

	Disc = "###,###,##0.00";
	DTPstart->Date = Date();
	DTPend->Date = Date();
}
//---------------------------------------------------------------------------
void __fastcall Taccountyfhz::FormShow(TObject *Sender)
{
	 	AnsiString sql ;
	if (type == 1) {
		sql = "select ID,Name from CUST_CustomerInfo where Type = 1 and name <> ''  and customerstate=1 and stgid="+IntToStr(fstgid)+ " order by name";
	}
	else
	{
		sql = "select ID,Name from CUST_CustomerInfo where Type in(2,3) and name <> ''  and customerstate=1 and stgid="+IntToStr(fstgid)+" order by name";
	}
	aqcustom->Close();
	aqcustom->SQL->Clear();
	aqcustom->SQL->Add(sql);
	aqcustom->Open();
	aqcustom->First();
	while (!aqcustom->Eof ) {
		cbCusName->AddItem(aqcustom->FieldByName("Name")->AsString ,(TObject*)aqcustom->FieldByName("ID")->AsInteger);
		aqcustom->Next();
	}

	edquery->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall Taccountyfhz::BtnViewClick(TObject *Sender)
{
   	AnsiString sql ,sqlwhere,sqladd;
	int clientid;

	if (type == 1) {
		sql = "select cast(rank() over(order by CUST_CustomerInfo.ID) as nvarchar(10)) as xuhao,sum(BS_StorageNoteHeader.TotalFixedPrice) as sumFixedPrice,sum(BS_StorageNoteHeader.TotalDiscountedPrice) as sumDiscountedPrice, "
				" sum(BS_StorageNoteHeader.TotalAmount) as sumTotalAmount,sum(BS_StorageNoteHeader.AddCosts) as sumAddCosts,sum(BS_StorageNoteHeader.AddCosts + BS_StorageNoteHeader.TotalDiscountedPrice) as totalyingfu, "
				" sum(BS_StorageNoteHeader.Checked) as sumChecked,sum(BS_StorageNoteHeader.Nochecked) as sumNochecked, "
				" case when sum(BS_StorageNoteHeader.TotalFixedPrice) <> 0 then sum(BS_StorageNoteHeader.TotalDiscountedPrice)*100/sum(BS_StorageNoteHeader.TotalFixedPrice) else 0 end as discount, "
				" CUST_CustomerInfo.name as clientname,CuST_CustomerInfo.ID,(CUST_CustomerStartMoney.balance + CUST_CustomerStartMoney.totalyue) as totalyue,0 as profite  from BS_StorageNoteHeader inner join CUST_CustomerInfo "
				" on BS_StorageNoteHeader.SupplierID = CUST_CustomerInfo.ID "
				" left join CUST_CustomerStartMoney on BS_StorageNoteHeader.SupplierID = CUST_CustomerStartMoney.CustomerID ";
		 sqlwhere = " where CUST_CustomerInfo.Type = 1 and CUST_CustomerInfo.customerstate=1 and CUST_CustomerInfo.stgid="+IntToStr(fstgid);
	}
	else
	{
		if (chhuizong->Checked ) {
			sql = "select cast(rank() over(order by CUST_CustomerInfo.PrentID) as nvarchar(10)) as xuhao,CUST_CustomerInfo.PrentID as id ,dbo.uf_bs_getclientname(CuST_CustomerInfo.PrentID) as clientname,";
		}
		else
		{
			sql = "select cast(rank() over(order by CUST_CustomerInfo.ID) as nvarchar(10)) as xuhao,CuST_CustomerInfo.ID ,dbo.uf_bs_getclientname(CuST_CustomerInfo.ID) as clientname,";
		}
		sql = sql + " sum(BS_WsaleNoteHeader.FixedPrice) as sumFixedPrice, "
				" sum(BS_WsaleNoteHeader.DiscountedPrice) as sumDiscountedPrice,sum(BS_WsaleNoteHeader.TotalAmount) as sumTotalAmount, "
				" sum(BS_WsaleNoteHeader.AddCosts) as sumAddCosts,sum(BS_WsaleNoteHeader.AddCosts) + sum(BS_WsaleNoteHeader.DiscountedPrice) as totalyingfu,sum(BS_WsaleNoteHeader.Checked) as sumChecked, "
				" sum(BS_WsaleNoteHeader.Nochecked) as sumNochecked,(CUST_CustomerStartMoney.balance + CUST_CustomerStartMoney.totalyue) as totalyue , ";
		if (chprofite->Checked) {
			sql = sql + " sum(dbo.UF_BS_Getwsaleprofite(BS_WsaleNoteHeader.id)) as profite,sum(BS_WsaleNoteHeader.DiscountedPrice - dbo.UF_BS_Getwsaleprofite(BS_WsaleNoteHeader.id)) as cbprice, ";
		}
		else
		{
			sql = sql + " 0 as profite,0 as cbprice, ";
		}
		sql = sql + " 0 as discount from BS_WsaleNoteHeader inner join CUST_CustomerInfo   on BS_WsaleNoteHeader.VendorID = CUST_CustomerInfo.ID  "
				" left join CUST_CustomerStartMoney on BS_WsaleNoteHeader.VendorID = CUST_CustomerStartMoney.CustomerID  " ;
		sqlwhere = " where CUST_CustomerInfo.Type in(2,3) and CUST_CustomerInfo.customerstate=1 and CUST_CustomerInfo.stgid="+IntToStr(fstgid);
	}

		if (chname->Checked && cbCusName->Text != "") {
			try {
				clientid = (int)cbCusName->Items->Objects[cbCusName->ItemIndex];
			} catch (...) {

                                ShowMsg(Handle ,"请选择正确的单位！",3);
				return;
			}
			sqlwhere = sqlwhere + " and CUST_CustomerInfo.ID in (select ID from GetChild(" + IntToStr(clientid) + "))";
		}

	if (type == 1) {
		if (CBstart->Checked ) {
			sqlwhere = sqlwhere + " and BS_StorageNoteHeader.HdTime >='" + DateToStr(DTPstart->Date) + " 0:00:00'";
		}
		if (CBend->Checked ) {
			sqlwhere = sqlwhere + " and BS_StorageNoteHeader.HdTime <='" + DateToStr(DTPend->Date) + " 23:59:59'" ;
		}
		if (cbInOut->Text == "进货") {
			sqlwhere = sqlwhere + " and BS_StorageNoteHeader.TotalAmount>=0 ";
		}
		if (cbInOut->Text == "退货") {
			sqlwhere = sqlwhere + " and BS_StorageNoteHeader.TotalAmount<0 " ;
		}
	}
	else
	{
		if (CBstart->Checked ) {
			sqlwhere = sqlwhere +   " and BS_WsaleNoteHeader.HdTime >='" + DateToStr(DTPstart->Date) + " 0:00:00'";
		}
		if (CBend->Checked ) {
			sqlwhere = sqlwhere + " and BS_WsaleNoteHeader.HdTime <='" + DateToStr(DTPend->Date) + " 23:59:59'" ;
		}
		if (cbInOut->Text == "进货") {
			sqlwhere = sqlwhere + " and BS_WsaleNoteHeader.TotalAmount>=0 ";
		}
		if (cbInOut->Text == "退货") {
			sqlwhere = sqlwhere + " and BS_WsaleNoteHeader.TotalAmount<0 " ;
		}
	}
	if (chhuizong->Checked ) {
		sql = sql +  sqlwhere + " group by CUST_CustomerInfo.PrentID,CUST_CustomerStartMoney.balance, CUST_CustomerStartMoney.totalyue ";
	}
	else
	{
		sql = sql +  sqlwhere + " group by CUST_CustomerInfo.name,CUST_CustomerInfo.ID,CUST_CustomerStartMoney.balance, CUST_CustomerStartMoney.totalyue ";
	}
	/*if (type == 1 ) {
		sql = sql + " union "
					" select '合计',sum(BS_StorageNoteHeader.TotalFixedPrice) as sumFixedPrice,sum(BS_StorageNoteHeader.TotalDiscountedPrice) as sumDiscountedPrice, "
					" sum(BS_StorageNoteHeader.TotalAmount) as sumTotalAmount,sum(BS_StorageNoteHeader.AddCosts) as sumAddCosts,sum(BS_StorageNoteHeader.AddCosts) + sum(BS_StorageNoteHeader.TotalDiscountedPrice) as totalyingfu, "
					" sum(BS_StorageNoteHeader.Checked) as sumChecked,sum(BS_StorageNoteHeader.Nochecked) as sumNochecked, "
					" case when sum(BS_StorageNoteHeader.TotalFixedPrice) <> 0 then sum(BS_StorageNoteHeader.TotalDiscountedPrice)*100/sum(BS_StorageNoteHeader.TotalFixedPrice) else 0 end as discount, "
					" null,999999999,sum(CUST_CustomerStartMoney.balance + CUST_CustomerStartMoney.totalyue) as totalyue from BS_StorageNoteHeader inner join CUST_CustomerInfo "
					" on BS_StorageNoteHeader.SupplierID = CUST_CustomerInfo.ID "
					" left join CUST_CustomerStartMoney on BS_StorageNoteHeader.SupplierID = CUST_CustomerStartMoney.CustomerID " ;
	}
	else
	{
		sql = sql + " union "
					" select '合计',999999999,null,sum(BS_WsaleNoteHeader.FixedPrice) as sumFixedPrice, "
					" sum(BS_WsaleNoteHeader.DiscountedPrice) as sumDiscountedPrice,sum(BS_WsaleNoteHeader.TotalAmount) as sumTotalAmount, "
					" sum(BS_WsaleNoteHeader.AddCosts) as sumAddCosts,sum(BS_WsaleNoteHeader.AddCosts) + sum(BS_WsaleNoteHeader.DiscountedPrice) as totalyinghu,sum(BS_WsaleNoteHeader.Checked) as sumChecked, "
					" sum(BS_WsaleNoteHeader.Nochecked) as sumNochecked,sum(CUST_CustomerStartMoney.balance + CUST_CustomerStartMoney.totalyue) as totalyue , " ;
		if (chprofite->Checked ) {
			sql = sql + " sum(dbo.UF_BS_Getwsaleprofite(BS_WsaleNoteHeader.id)) as profite,sum(BS_WsaleNoteHeader.DiscountedPrice - dbo.UF_BS_Getwsaleprofite(BS_WsaleNoteHeader.id)) as cbprice ";
			DBGridtotal->Columns->Items[10]->Visible = true;
			DBGridtotal->Columns->Items[11]->Visible = true;
		}
		else
		{
			sql = sql + " 0 as profite,0 as cbprice ";
			DBGridtotal->Columns->Items[10]->Visible = false;
			DBGridtotal->Columns->Items[11]->Visible = false;
		}
		sql = sql + " from BS_WsaleNoteHeader inner join CUST_CustomerInfo   on BS_WsaleNoteHeader.VendorID = CUST_CustomerInfo.ID "
					" left join CUST_CustomerStartMoney on BS_WsaleNoteHeader.VendorID = CUST_CustomerStartMoney.CustomerID ";
	}  */
	sql = sql + " order by id asc";
	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Open();
       //	((TFloatField *)DBGridtotal->DataSource->DataSet->FieldByName("totalyue"))->DisplayFormat = Disc;
	((TFloatField *)DBGridtotal->DataSource->DataSet->FieldByName("sumFixedPrice"))->DisplayFormat = Disc;
	((TFloatField *)DBGridtotal->DataSource->DataSet->FieldByName("sumDiscountedPrice"))->DisplayFormat = Disc;
	((TFloatField *)DBGridtotal->DataSource->DataSet->FieldByName("totalyingfu"))->DisplayFormat = Disc;
	((TFloatField *)DBGridtotal->DataSource->DataSet->FieldByName("sumAddCosts"))->DisplayFormat = Disc;
	((TFloatField *)DBGridtotal->DataSource->DataSet->FieldByName("sumChecked"))->DisplayFormat = Disc;
	((TFloatField *)DBGridtotal->DataSource->DataSet->FieldByName("sumNochecked"))->DisplayFormat = Disc;
	((TFloatField *)DBGridtotal->DataSource->DataSet->FieldByName("sumTotalAmount"))->DisplayFormat = "###,###,##0";
	if (type == 1) {
		((TFloatField *)DBGridtotal->DataSource->DataSet->FieldByName("discount"))->DisplayFormat = Disc+"%";
	}
	else
	{
		((TFloatField *)DBGridtotal->DataSource->DataSet->FieldByName("cbprice"))->DisplayFormat = Disc;
		((TFloatField *)DBGridtotal->DataSource->DataSet->FieldByName("profite"))->DisplayFormat = Disc;
	}
}
//---------------------------------------------------------------------------
void __fastcall Taccountyfhz::BtnExportClick(TObject *Sender)
{
   	if (aquery->IsEmpty() ) {
		return;
	}
	DbgridToExcel(DBGridtotal);
}
//---------------------------------------------------------------------------
void __fastcall Taccountyfhz::BtnPrintPreviewClick(TObject *Sender)
{
	if (aquery->IsEmpty() ) {
		return;
	}

       //	RvSystem1->SystemSetups >>ssAllowSetup;
       //	RvSystem1->SystemSetups >>ssAllowDestPreview;
       //	RvSystem1->SystemSetups >>ssAllowDestPrinter;
       //	RvSystem1->SystemSetups >>ssAllowPrinterSetup;
	RvSystem1->SystemSetups >>ssAllowDestFile;
	RvSystem1->DefaultDest  = rdPreview ;
	RvSystem1->SystemSetups<<ssAllowDestPreview;

	if (type == 1) {
		RvProject1->ProjectFile = ExtractFilePath(Application->ExeName) + "accoutnsdue.rav";
	}
	else
	{
		RvProject1->ProjectFile = ExtractFilePath(Application->ExeName) + "accoutnsdueclient.rav";
	}
	RvProject1->Open();
	AnsiString str =  this->Caption;
	str = stogName + str;
	RvProject1->SetParam("title",str);

	RvProject1->SetParam("suppliername",cbCusName->Text);

	if (CBstart->Checked) {
		RvProject1->SetParam("starttime",DateToStr(DTPstart->Date));
	}
	if (CBend->Checked) {
		RvProject1->SetParam("endtime",DateToStr(DTPend->Date));
	}
	RvProject1->SetParam("jingchu",cbInOut->Text);
	RvProject1->SetParam("user",username);
	RvProject1->SetParam("Name","供应商名称");
	RvProject1->Execute();
	RvProject1->Close();
}
//---------------------------------------------------------------------------
void __fastcall Taccountyfhz::BtnPrintClick(TObject *Sender)
{
	if (aquery->IsEmpty() ) {
		return;
	}


	RvSystem1->SystemSetups >>ssAllowSetup;
	RvSystem1->SystemSetups >>ssAllowDestPreview;
	RvSystem1->SystemSetups >>ssAllowDestPrinter;
	RvSystem1->SystemSetups >>ssAllowPrinterSetup;
	RvSystem1->SystemSetups >>ssAllowDestFile;
	RvSystem1->DefaultDest  = rdPrinter ;
	RvSystem1->SystemSetups<<ssAllowDestPreview;
	if (type == 1) {
		RvProject1->ProjectFile = ExtractFilePath(Application->ExeName) + "accoutnsdue.rav";
	}
	else
	{
		RvProject1->ProjectFile = ExtractFilePath(Application->ExeName) + "accoutnsdueclient.rav";
	}
	RvProject1->Open();
	String str =  stogName + this->Caption;
	RvProject1->SetParam("title",str);

	RvProject1->SetParam("suppliername",cbCusName->Text);


	//RvProject1->SetParam("suppliername",cbCusName->Text);
	if (CBstart->Checked) {
		RvProject1->SetParam("starttime",DateToStr(DTPstart->Date));
	}
	if (CBend->Checked) {
		RvProject1->SetParam("endtime",DateToStr(DTPend->Date));
	}
	RvProject1->SetParam("jingchu",cbInOut->Text);
	RvProject1->SetParam("user",username);
	RvProject1->SetParam("Name","供应商名称");
	RvProject1->Execute();
	RvProject1->Close();
}
//---------------------------------------------------------------------------
void __fastcall Taccountyfhz::BtnExitClick(TObject *Sender)
{
      	Close();
}
bool __fastcall Taccountyfhz::DbgridToExcel(TDBGridEh* dbg)
{
   	AnsiString temptext,path;
	savedlg->FileName = this->Caption;
	if (savedlg->Execute())
	{
		String DBPath,Name;
		DBPath = ExtractFilePath(savedlg->FileName .c_str()  );
		Name = ExtractFileName(savedlg->FileName .c_str() );
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

	aquery->DisableControls();
	dbg->DataSource ->DataSet ->First();
	while(!dbg->DataSource ->DataSet->Eof)
	{
		temptext = "\n";
		for(int j=1;j<dbg->Columns ->Count+1  ;j++)
		{
			if (dbg->Columns->Items[j-1]->Visible == true) {
				temptext = temptext + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
			}
		}
		iFileLength   =   FileSeek(iFileHandle,0,2);
		FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
		dbg->DataSource ->DataSet ->Next() ;
	}
	aquery->EnableControls();

	FileClose(iFileHandle);


        ShowMsg(Handle ,"导出完毕！",3);
	return false;

}
//---------------------------------------------------------------------------

void __fastcall Taccountyfhz::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F6 ) {    //导入
		BtnExport->Click();
	}
	if (Key == VK_F7 ) {    //预览
		BtnPrintPreview->Click();
	}
	if (Key == VK_F8 ) {    //打印
		BtnPrint->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 70 ) {    //查询
		BtnView->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 78 ) {    //最小化
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 81 ) {    //退出
		BtnExit->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==90) {   //恢复窗口
		WindowState = wsNormal  ;
	}
}
//---------------------------------------------------------------------------
void __fastcall Taccountyfhz::DTPstartClick(TObject *Sender)
{
CBstart->Checked = true;
}
//---------------------------------------------------------------------------
void __fastcall Taccountyfhz::DTPendClick(TObject *Sender)
{
CBend->Checked = true;
}
//---------------------------------------------------------------------------
void __fastcall Taccountyfhz::DBGridtotalTitleClick(TColumnEh *Column)
{
    if (aquery->IsEmpty() ) {
    	return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (aquery->Sort == "") {
		aquery->Sort =  Column->FieldName + " ASC";
	}
	else if (aquery->Sort == qusort) {
		aquery->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		aquery->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------

void __fastcall Taccountyfhz::BtnAlignBottomClick(TObject *Sender)
{
WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall Taccountyfhz::edqueryKeyPress(TObject *Sender, wchar_t &Key)
{
              if (Key == '\r') {
		AnsiString sql;
		if (type == 1) {
			sql = "select ID,Name from CUST_CustomerInfo where type = 1  and customerstate=1  and stgid="+IntToStr(fstgid)+" and Name like '%" + edquery->Text + "%' and name <> '' ";
        	aqcustom->Close();
			aqcustom->SQL->Clear();
			aqcustom->SQL->Add(sql);
			aqcustom->Open();
			cbCusName->Clear();
			while (!aqcustom->Eof )
			{
				cbCusName->AddItem(aqcustom->FieldByName("Name")->AsString ,(TObject*)aqcustom->FieldByName("ID")->AsInteger);
				aqcustom->Next();
			}
			aqcustom->First();
			cbCusName->ItemIndex = cbCusName->Items->IndexOfObject((TObject*)aqcustom->FieldByName("ID")->AsInteger);
		}
		else
		{
			sql = "select ID,Name from CUST_CustomerInfo where type in(2,3)  and customerstate=1 and stgid="+IntToStr(fstgid)+" and Name like '%" + edquery->Text + "%' and name <> '' ";
        	aqcustom->Close();
			aqcustom->SQL->Clear();
			aqcustom->SQL->Add(sql);
			aqcustom->Open();
			cbCusName->Clear();
			while (!aqcustom->Eof )
			{
				cbCusName->AddItem(aqcustom->FieldByName("Name")->AsString ,(TObject*)aqcustom->FieldByName("ID")->AsInteger);
				aqcustom->Next();
			}
			aqcustom->First();
			cbCusName->ItemIndex = cbCusName->Items->IndexOfObject((TObject*)aqcustom->FieldByName("ID")->AsInteger);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall Taccountyfhz::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------


