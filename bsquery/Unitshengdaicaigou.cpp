//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unitshengdaicaigou.h"
#include "pdutil.h"
#include "Notedetail.h"
#include "global.h"
#include "Selecttype.h"
#include "bookhistory.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma link "QryProcureNoteForm"
#pragma link "RzButton"
#pragma link "RzDBCmbo"
#pragma link "RzDTP"
#pragma link "RzEdit"
#pragma link "RzPanel"
#pragma link "RzRadChk"
#pragma link "RzTabs"
#pragma resource "*.dfm"
TfrmQryProcureNote1 *frmQryProcureNote1;
//---------------------------------------------------------------------------
__fastcall TfrmQryProcureNote1::TfrmQryProcureNote1(TComponent* Owner)
	: TfrmQryProcureNote(Owner)
{
}
//---------------------------------------------------------------------------
String TfrmQryProcureNote1::QueryDesic()
{
	 TADOQuery * aq;
   aq = new TADOQuery(this);
   aq->Connection = m_con ;
   aq->Close();
   aq->SQL->Clear();
   aq->SQL->Add("select bk from sys_bsset where name ='xiaoshudian'");
   aq->Open();
   Desic1 =  aq->FieldByName("bk")->AsAnsiString;
   return "￥###,###,##"+ aq->FieldByName("bk")->AsAnsiString ;
   delete aq;
}

void __fastcall TfrmQryProcureNote1::tlbtnQryClick(TObject *Sender)
{
	//查询
        try
        {
	Query();
        }catch(...)
        {};
	switch (pgcntrlResult->ActivePage->Tag) {
		case 1:
			((TFloatField *)dbgrdByNtHeader->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = Desic;
			((TFloatField *)dbgrdByNtHeader->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = Desic;
			break;
		case 2:
			((TFloatField *)dbgrdByNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00%";
			((TFloatField *)dbgrdByNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = Desic;
			((TFloatField *)dbgrdByNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = Desic;


			break;
		case 3:
			((TFloatField *)dbgrdByCustomer->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = Desic;
			((TFloatField *)dbgrdByCustomer->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = Desic;
			break;
		case 4:
			((TFloatField *)dbgrdByBktype->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = Desic;
			((TFloatField *)dbgrdByBktype->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = Desic;
			break;
		case 5:
			((TFloatField *)dbgrdByPress->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = Desic;
			((TFloatField *)dbgrdByPress->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = Desic;
			break;
    default:
        ;
	}
}

void TfrmQryProcureNote1::Query()
{
	long double   TotalMan=0.0000,TotalShi=0.0000;
	int TotalNum=0;
	AnsiString isbn;
	if (chckbxISBN->Checked && edtISBN->Text != "") {
		isbn = edtISBN->Text.Trim();
		if (isbn.Length() == 10 || isbn.Length() == 13  ) {
			isbn = isbn.Delete(isbn.Length(),1);
		}

	}
	spQryNote->Active = false;
	for (int i = 0; i < spQryNote->Parameters->Count; i++)
	{
        spQryNote->Parameters->operator [](i)->Value = System::Variant();
	}

	if (chckbxStartTime->Checked ) //开始时间
		spQryNote->Parameters->ParamByName("@Start")->Value = dtedtStart->Date;

	if (chckbxEndTime->Checked ) //结束时间
		spQryNote->Parameters->ParamByName("@End")->Value = dtedtEnd->Date;

    if (chckbxBookName->Checked && edtBookName->Text != "") //书名
		spQryNote->Parameters->ParamByName("@Name")->Value = "%" + edtBookName->Text + "%";

	if (chckbxUserDefNum->Checked && edtUserDefNum->Text != "") //自编码
		spQryNote->Parameters->ParamByName("@UserDefCode")->Value = "%" + edtUserDefNum->Text + "%";

	if (chckbxPress->Checked && dblkpcbbPress->Text != "") //出版社
		spQryNote->Parameters->ParamByName("@PressID")->Value = dsetPress->FieldByName("ID")->AsInteger;

	if (chckbxISBN->Checked && edtISBN->Text != "") //ISBN
        {
                if (isbn.Length()>13) {
               spQryNote->Parameters->ParamByName("@ISBN")->Value = isbn;
         }else
         {
               spQryNote->Parameters->ParamByName("@ISBN")->Value = isbn ;
         }
	       //	spQryNote->Parameters->ParamByName("@ISBN")->Value = "%" + isbn + "%";
         }
	if (chckbxPrice->Checked && numedtMinPrice->Text != "") //定价
		spQryNote->Parameters->ParamByName("@MinPrice")->Value = numedtMinPrice->Value;

	if (chckbxPrice->Checked && numedtMaxPrice->Text != "") //定价
		spQryNote->Parameters->ParamByName("@MaxPrice")->Value = numedtMaxPrice->Value;

	if (chckbxType->Checked && edtyname->Text != "") //书目类型
		spQryNote->Parameters->ParamByName("@BktypeID")->Value = TypeID;

	if (chckbxCustomer->Checked) //客户
		spQryNote->Parameters->ParamByName("@CustomerID")->Value = dsetCustomer->FieldByName("ID")->AsInteger;

	if (chckbxAuthor->Checked && edtAuthor->Text != "") //作者
		spQryNote->Parameters->ParamByName("@Author")->Value = "%" + edtAuthor->Text + "%";

	if (chckbxRemarks->Checked && edtRemarks->Text != "") //备注
		spQryNote->Parameters->ParamByName("@Remarks")->Value = "%" + edtRemarks->Text + "%";

	//if (chckbxBkstack->Checked) //库位
		//spQryNote->Parameters->ParamByName("@BkstackID")->Value = dsetBookstack->FieldByName("ID")->AsInteger;

	if (chckbxAmount->Checked && numedtMinAmount->Text != "") //库存
		spQryNote->Parameters->ParamByName("@MinAmount")->Value = numedtMinAmount->IntValue;

	if (chckbxAmount->Checked && numedtMaxAmount->Text != "") //库存
		spQryNote->Parameters->ParamByName("@MaxAmount")->Value = numedtMaxAmount->IntValue;

	if (chckbxStorage->Checked) //店
		//spQryNote->Parameters->ParamByName("@StgID")->Value = dsetInit->FieldByName("StorageID")->AsInteger;
		spQryNote->Parameters->ParamByName("@StgID")->Value = dsetStorage->FieldByName("ID")->AsInteger;
	if (chstaff->Checked ) {    //操作员
		spQryNote->Parameters->ParamByName("@staff")->Value = dsetstaff->FieldByName("ID")->AsInteger;
	}
	if (chdiscount->Checked && edmindiscount->Text != "") {   //最小折扣
		spQryNote->Parameters->ParamByName("@mindiscount")->Value = StrToFloat(edmindiscount->Text);
	}
	if (chdiscount->Checked && edmaxdiscount->Text != "") {   //最大折扣
		spQryNote->Parameters->ParamByName("@maxdiscount")->Value =  StrToFloat(edmaxdiscount->Text);
	}
	if (chnocheck->Checked ) {   //未结
		spQryNote->Parameters->ParamByName("@check")->Value = 1;
		spQryNote->Parameters->ParamByName("@nocheck")->Value = 1;
	}
	if (chcheckpart->Checked ) {   //已结部分
		spQryNote->Parameters->ParamByName("@check")->Value = 1;
		spQryNote->Parameters->ParamByName("@checkpart")->Value = 1;
	}
	if (chchecked->Checked ) {   //已经全部
		spQryNote->Parameters->ParamByName("@check")->Value = 1;
		spQryNote->Parameters->ParamByName("@checked")->Value = 1;
	}

	if (chdanhao->Checked && eddanhao->Text != "") {
    	spQryNote->Parameters->ParamByName("@NoteCode")->Value = eddanhao->Text .Trim() ;
	}


     spQryNote->Parameters->ParamByName("@Bsmode")->Value = 10;


	spQryNote->Parameters->ParamByName("@SearchMode")->Value = pgcntrlResult->ActivePage->Tag;

	try
	{
		spQryNote->Active = true;
		((TFloatField *)spQryNote->FieldByName("FixedPrice"))->DisplayFormat = Desic;
		((TFloatField *)spQryNote->FieldByName("DiscountedPrice"))->DisplayFormat = Desic ;

		switch (pgcntrlResult->ActivePage->Tag)
		{
		case 1:
			dsrcByNtHeader->DataSet = NULL;
			dsetByNtHeader->Recordset = spQryNote->Recordset;
			dsetByNtHeader->First();
			dsrcByNtHeader->DataSet = dsetByNtHeader;
			break;
		case 2:
			dsrcByNote->DataSet = NULL;
			dsetByNote->Recordset = spQryNote->Recordset;
            dsetByNote->First();
			dsrcByNote->DataSet = dsetByNote;
        	break;
		case 3:
			dsrcByCustomer->DataSet = NULL;
			dsetByCustomer->Recordset = spQryNote->Recordset;
			dsetByCustomer->First();
			dsrcByCustomer->DataSet = dsetByCustomer;
			break;
		case 4:
			dsrcByBktype->DataSet = NULL;
			dsetByBktype->Recordset = spQryNote->Recordset;
			dsetByBktype->First();
			dsrcByBktype->DataSet = dsetByBktype;
        	break;
		case 5:
			dsrcByPress->DataSet = NULL;
			dsetByPress->Recordset = spQryNote->Recordset;
			dsetByPress->First();
			dsrcByPress->DataSet = dsetByPress;
        	break;
		default:
			break;
		}
	}
	catch(...)
	{

    }
}

//---------------------------------------------------------------------------

void TfrmQryProcureNote1::Init(LandInfo* li)
{
	TfrmMDIChild::Init(li);
	//
	fcon = m_con;
	spQryNote->Connection = m_con;
	dsetPress->Connection = m_con;
	dsetPress->Active = true;
	dsetBookType->Connection = m_con;
	dsetBookType->Active = true;
	dsetStorage->Connection = m_con;
	dsetStorage->Active = true;
	dsetCustomer->Connection = m_con;
        dsetCustomer->CommandText=" select ID,Name from CUST_CustomerInfo where (ID=0 or (ID>0 and Type=1)) and customerstate=1 and stgid="+IntToStr(m_storageID);
	dsetCustomer->Active = true;
	dsetBookstack->Connection = m_con;
	dsetBookstack->Active = true;
	dsetstaff->Connection = m_con;
	dsetstaff->Active = true;
	qryItems->Connection = m_con;
	numedtMinPrice->Text = "";
	numedtMaxPrice->Text = "";
	numedtMinAmount->Text = "";
	numedtMaxAmount->Text = "";
	chckbxStorage->Checked = true;
	dblkpcbbStorage->KeyValue = m_storageID ;
	TADOQuery * aq;
   aq = new TADOQuery(this);
   aq->Connection = m_con ;
   AnsiString sql;




   sql = "select Master from SYS_StorageInfo where id = " + IntToStr(m_storageID);
   aq->Close();
   aq->SQL->Clear();
   aq->SQL->Add(sql);
   aq->Open();
   if (aq->FieldByName("Master")->AsBoolean ) {
		chckbxStorage->Enabled = true;
		dblkpcbbStorage->Enabled = true;
   }
   else
   {
        chckbxStorage->Enabled = false;
		sql = "select * from BS_StoToSto where ystgid = " + IntToStr(m_storageID) + " and procure = 1";
        aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		if (aq->RecordCount == 0) {
			dblkpcbbStorage->Enabled = false;
		}
		else
		{
			AnsiString ss ;
			ss = "ID = " + IntToStr(m_storageID);
			while (!aq->Eof )
			{
				ss = ss + " or ID = " + aq->FieldByName("mstgid")->AsString ;
				aq->Next();
			}
			dsetStorage->Filtered = false;
			dsetStorage->Filter = ss;
			dsetStorage->Filtered = true;
		}
   }

   delete aq;
	Desic = QueryDesic();
}



void __fastcall TfrmQryProcureNote1::tlbtnExportClick(TObject *Sender)
{
	//Excel导出
        savefilename = "省代采购查询";
	switch (pgcntrlResult->ActivePage->Tag)
	{
	case 1:
		if (dsetByNtHeader->Active && dsetByNtHeader->RecordCount > 0) {
                                    savefilename=savefilename+"按单";
				DbgridToExcel(dbgrdByNtHeader);
			}
		break;
	case 2:
		if (dsetByNote->Active && dsetByNote->RecordCount > 0) {
                savefilename=savefilename+"按明细";
				DbgridToExcel(dbgrdByNote);
			}
		break;
	case 3:
		if (dsetByCustomer->Active && dsetByCustomer->RecordCount > 0) {
                savefilename=savefilename+"按供应商";
				DbgridToExcel(dbgrdByCustomer);
			}
		break;
	case 4:
		if (dsetByBktype->Active && dsetByBktype->RecordCount > 0) {
                savefilename=savefilename+"按类别";
				DbgridToExcel(dbgrdByBktype);
			}
		break;
	case 5:
		if (dsetByPress->Active && dsetByPress->RecordCount > 0) {
                savefilename=savefilename+"按版别";
				DbgridToExcel(dbgrdByPress);
			}
		break;
	default:
		break;
	}
}
//---------------------------------------------------------------------------
bool __fastcall TfrmQryProcureNote1::DbgridToExcel(TDBGridEh* dbg)
{
	AnsiString temptext,path;
            TDateTime t=   Date();



             savedlg->FileName=savefilename;
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

	int k = dbg->DataSource ->DataSet ->RecordCount ,n=0;


	int t1= 0;
	for(int q=0;q<dbg->FieldCount ;++q)
	{
		if (dbg->Columns->Items[q]->Visible == true) {
			temptext = temptext + dbg->Columns ->Items [q]->Title ->Caption + ",";
		}
	}
    FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	int t2 = dbg->DataSource ->DataSet ->RecordCount ;

	dbg->DataSource ->DataSet ->First();
	dbg->DataSource ->DataSet->DisableControls();
	for(int   i=2+n;i<=t2+1+n ;i++)
	{
		t1=0;
		temptext = "\n";
		for(int j=1;j<dbg->Columns ->Count+1  ;j++)
		{
			if (dbg->Columns->Items[j-1]->Visible == true) {

				if (dbg->Columns ->Items [j-1]->FieldName == "BookName" || dbg->Columns ->Items [j-1]->FieldName == "ProcureNoteHeadeRemarks") {
					AnsiString bookname;
					bookname = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					bookname = StringReplace(bookname , ",",".",TReplaceFlags()<<rfReplaceAll);
					bookname = StringReplace(bookname , '\n',"",TReplaceFlags()<<rfReplaceAll);
					bookname = StringReplace(bookname , '\r',"",TReplaceFlags()<<rfReplaceAll);
					temptext = temptext + bookname + ",";
				}
				else if (dbg->Columns ->Items [j-1]->FieldName == "FixedPrice" || dbg->Columns ->Items [j-1]->FieldName == "DiscountedPrice" ) {
					temptext = temptext + FormatFloat(Desic1,dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsFloat) + ",";
				}
				else
				{
					temptext = temptext + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
				}
			}
		}
		FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
		dbg->DataSource ->DataSet ->Next() ;
	}
	dbg->DataSource ->DataSet->EnableControls();

	temptext = "\n合计,";
	AnsiString text;
	for(int q=1;q<dbg->FieldCount ;++q)
	{
		if (dbg->Columns->Items[q]->Visible == true) {
			text = dbg->GetFooterValue(q,dbg->Columns->Items [q]);
			text = StringReplace(text , ",","",TReplaceFlags()<<rfReplaceAll);
			text = StringReplace(text , "-","'-",TReplaceFlags()<<rfReplaceAll);
			temptext = temptext + text + ",";
		}
	}


	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
	FileClose(iFileHandle);
	ShowMsg(this->Handle,"导出完毕！",3);
	return false;
}
//---------------------------------------------------------------------------


void __fastcall TfrmQryProcureNote1::tlbtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryProcureNote1::edtPressKeyPress(TObject *Sender, wchar_t &Key)
{
	//
	if (Key == '\r')
	{
		TCustomEdit* edt = dynamic_cast<TCustomEdit*>(Sender);
		if (edt != NULL)
		{
			if (edt->Tag == 1)//版别
			{
				//查询版别
				String sql = "select * from BS_PressInfo where AbbreviatedName like '%";
				sql = sql + edt->Text + "%'";
				dsetPress->Active = false;
				dsetPress->CommandText = sql;
				dsetPress->Active = true;
				if (dsetPress->RecordCount >= 1)
				{
					dsetPress->First();
					dblkpcbbPress->KeyValue = dsetPress->FieldByName("ID")->AsInteger ;
				}
			}
			else if (edt->Tag == 2)//供应商
			{
				//查询供应商
				String sql = "select ID,Name from CUST_CustomerInfo where (ID=0 or (ID>0 and Type=1)) and customerstate=1 and stgid="+IntToStr(m_storageID)+" and Name like '%";
				sql = sql + edtCustomer->Text + "%'";

                dsetCustomer->Active = false;
				dsetCustomer->CommandText = sql;
				dsetCustomer->Active = true;
				dsetCustomer->First();
				dblkpcbbCustomer->KeyValue = dsetCustomer->FieldByName("ID")->AsInteger;
			}
			else
			{

            }
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmQryProcureNote1::FormClose(TObject *Sender, TCloseAction &Action)
{
	//
	spQryNote->Active = false;
	dsetPress->Active = false;
	dsetBookType->Active = false;
	dsetStorage->Active = false;
	dsetCustomer->Active = false;
	dsetBookstack->Active = false;
	qryItems->Active = false;
	dsetByNtHeader->Active = false;
	dsetByNote->Active = false;
	dsetByCustomer->Active = false;
	dsetByBktype->Active = false;
	dsetByPress->Active = false;
	TfrmMDIChild::FormClose(Sender, Action);
}
//---------------------------------------------------------------------------



void __fastcall TfrmQryProcureNote1::edtBookNameChange(TObject *Sender)
{
	if (edtBookName->Text != "") {
		chckbxBookName->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryProcureNote1::edtUserDefNumChange(TObject *Sender)
{
	if (edtUserDefNum->Text != "") {
        chckbxUserDefNum->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryProcureNote1::edtISBNChange(TObject *Sender)
{
	if (edtISBN->Text != "") {
        chckbxISBN->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryProcureNote1::numedtMinPriceChange(TObject *Sender)
{
	if (numedtMinPrice->Text != "") {
		chckbxPrice->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryProcureNote1::numedtMaxPriceChange(TObject *Sender)
{
	if (numedtMaxPrice->Text != "") {
        chckbxPrice->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryProcureNote1::numedtMinAmountChange(TObject *Sender)
{
	if (numedtMinAmount->Text != "") {
		chckbxAmount->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryProcureNote1::numedtMaxAmountChange(TObject *Sender)
{
	if (numedtMaxAmount->Text != "") {
        chckbxAmount->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryProcureNote1::edtAuthorChange(TObject *Sender)
{
	if (edtAuthor->Text != "") {
        chckbxAuthor->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryProcureNote1::edtRemarksChange(TObject *Sender)
{
	if (edtRemarks->Text != "") {
        chckbxRemarks->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryProcureNote1::dblkpcbbPressClick(TObject *Sender)
{
	if (dblkpcbbPress->Text != "") {
		chckbxPress->Checked = true;
		edtPress->Text = dsetPress->FieldByName("PresentNum")->AsString ;
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmQryProcureNote1::dblkpcbbStorageClick(TObject *Sender)
{
	if (dblkpcbbStorage->Text != "") {
		chckbxStorage->Checked = true;
		//dsetBookstack->Close();
		//dsetBookstack->CommandText = "select ID, Name from STK_BookstackInfo where StgID = " + dsetStorage->FieldByName("ID")->AsString ;
		//dsetBookstack->Active = false;
		//dsetBookstack->Active = true;

		dsetstaff->Close();
		dsetstaff->CommandText = "select cast(stgid as nvarchar(3)) + '店' + name as name,stgid,id from sys_user where StgID = " + dsetStorage->FieldByName("ID")->AsString ;
		dsetstaff->Active = false;
		dsetstaff->Active = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryProcureNote1::dblkpcbbCustomerClick(TObject *Sender)
{
	if (dblkpcbbCustomer->Text != "") {
		chckbxCustomer->Checked = true;
	       //	edtCustomer->Text = dsetCustomer->FieldByName("ID")->AsString ;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryProcureNote1::dbgrdByNote1TitleClick(TColumn *Column)
{
	if (dsetByNote->IsEmpty() ) {
		return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (dsetByNote->Sort == "") {
		dsetByNote->Sort =  Column->FieldName + " ASC";
	}
	else if (dsetByNote->Sort == qusort) {
		dsetByNote->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		dsetByNote->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryProcureNote1::edmindiscountChange(TObject *Sender)
{
	if (edmindiscount->Text != "") {
		chdiscount->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryProcureNote1::edmaxdiscountChange(TObject *Sender)
{
	if (edmaxdiscount->Text != "") {
    	chdiscount->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryProcureNote1::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryProcureNote1::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F6) {      //导出
		tlbtnExport->Click();
	}
	if (Shift.Contains(ssAlt)&& Key == 70 ) {    //查询
		tlbtnQry->Click();
	}
	if (Shift.Contains(ssAlt)&& Key == 78 ) {    //最小化
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssAlt)&& Key == 81 ) {    //退出
		tlbtnExit->Click();
	}
	if (Shift.Contains(ssAlt)&& Key ==90) {   //恢复窗口
		WindowState = wsNormal  ;
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmQryProcureNote1::dbgrdByNtHeaderDblClick(TObject *Sender)
{
	if (dsetByNtHeader->IsEmpty() ) {
		return;
	}
	if (dsetByNtHeader->RecordCount > 0) {
		TfrmNotedetail *frm = new TfrmNotedetail(Application,dsetByNtHeader->FieldByName("Code")->AsString,8,fcon,0);
		frm->ShowModal();
		delete frm;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryProcureNote1::dbgrdByNtHeaderTitleClick(TColumnEh *Column)
{
	if (dsetByNtHeader->IsEmpty() ) {
		return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (dsetByNtHeader->Sort == "") {
		dsetByNtHeader->Sort =  Column->FieldName + " ASC";
	}
	else if (dsetByNtHeader->Sort == qusort) {
		dsetByNtHeader->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		dsetByNtHeader->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryProcureNote1::dbgrdByCustomerTitleClick(TColumnEh *Column)
{
	if (dsetByCustomer->IsEmpty() ) {
		return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (dsetByCustomer->Sort == "") {
		dsetByCustomer->Sort =  Column->FieldName + " ASC";
	}
	else if (dsetByCustomer->Sort == qusort) {
		dsetByCustomer->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		dsetByCustomer->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryProcureNote1::dbgrdByBktypeTitleClick(TColumnEh *Column)
{
	if (dsetByBktype->IsEmpty() ) {
		return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (dsetByBktype->Sort == "") {
		dsetByBktype->Sort =  Column->FieldName + " ASC";
	}
	else if (dsetByBktype->Sort == qusort) {
		dsetByBktype->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		dsetByBktype->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryProcureNote1::dbgrdByPressTitleClick(TColumnEh *Column)
{
	if (dsetByPress->IsEmpty() ) {
		return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (dsetByPress->Sort == "") {
		dsetByPress->Sort =  Column->FieldName + " ASC";
	}
	else if (dsetByPress->Sort == qusort) {
		dsetByPress->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		dsetByPress->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryProcureNote1::dbgrdByNoteTitleClick(TColumnEh *Column)
{
	if (dsetByNote->IsEmpty() ) {
		return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (dsetByNote->Sort == "") {
		dsetByNote->Sort =  Column->FieldName + " ASC";
	}
	else if (dsetByNote->Sort == qusort) {
		dsetByNote->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		dsetByNote->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryProcureNote1::eddanhaoChange(TObject *Sender)
{
	if (eddanhao->Text != "") {
		chdanhao->Checked = true;
	}
	else
	{
    	chdanhao->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryProcureNote1::SpeedButton1Click(TObject *Sender)
{
	Tfrmselecttype * frm = new Tfrmselecttype(Application,fcon,"");
	if (mrOk == frm->ShowModal())
	{
		TypeID = frm->GetSelectID();
		edtyname->Text = frm->GetSelect();
		chckbxType->Checked = true;
	}
	delete frm;
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryProcureNote1::edpyqueryKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		Tfrmselecttype * frm = new Tfrmselecttype(Application,fcon,edpyquery->Text);
		if (mrOk == frm->ShowModal())
		{
			TypeID = frm->GetSelectID();
			edtyname->Text = frm->GetSelect();
			chckbxType->Checked = true;
		}
		delete frm;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryProcureNote1::N1Click(TObject *Sender)
{
   if (dsetByNote->IsEmpty() ) {
		return;
	}
	int fstgid;
	if (chckbxStorage->Checked ) {
		fstgid = dsetStorage->FieldByName("ID")->AsInteger ;
	}
	else
	{
		fstgid = -1;
	}
	Tfrmbookhistory *frm = new Tfrmbookhistory(Application,m_con,fstgid,dsetByNote->FieldByName("bookcatalogid")->AsInteger );
	frm->ShowModal();
	delete frm;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
