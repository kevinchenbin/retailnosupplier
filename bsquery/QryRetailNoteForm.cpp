
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "QryRetailNoteForm.h"
#include "global.h"
#include "Selecttype.h"
#include "bookhistory.h"
#include "Notedetail.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "QryStorageNoteForm"
#pragma link "RzButton"
#pragma link "RzDBCmbo"
#pragma link "RzDBGrid"
#pragma link "RzEdit"
#pragma link "RzLine"
#pragma link "RzPanel"
#pragma link "RzRadChk"
#pragma link "RzTabs"
#pragma link "RzDTP"
#pragma resource "*.dfm"
TfrmQryRetailNote *frmQryRetailNote;
//---------------------------------------------------------------------------
__fastcall TfrmQryRetailNote::TfrmQryRetailNote(TComponent* Owner)
	: TfrmQryStorageNote(Owner)
{
  dtedtStart->Date = Now();
  dtedtEnd->Date = Now();
  cbinstorage->Caption = "����";
  chnocheck->Visible = false;
  chcheckpart->Visible = false;
  chchecked->Visible = false;
}
//---------------------------------------------------------------------------
String TfrmQryRetailNote::QueryDesic()
{
	 TADOQuery * aq;
   aq = new TADOQuery(this);
   aq->Connection = m_con ;
   aq->Close();
   aq->SQL->Clear();
   aq->SQL->Add("select bk from sys_bsset where name ='retailxiaoshudian'");
   aq->Open();
   Desic1 =  aq->FieldByName("bk")->AsAnsiString;
   return "��"+ aq->FieldByName("bk")->AsAnsiString ;
   delete aq;

}
//---------------------------------------------------------------------------
void TfrmQryRetailNote::Query()
{
     Desic = QueryDesic();
	 long double   TotalMan=0.0000,TotalShi=0.0000,TotalShiji = 0.0000,Totalprofite = 0.0000;
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

	if (chckbxStartTime->Checked) //��ʼʱ��
		spQryNote->Parameters->ParamByName("@Start")->Value = dtedtStart->Date;

	if (chckbxEndTime->Checked) //����ʱ��
		spQryNote->Parameters->ParamByName("@End")->Value = dtedtEnd->Date;

    if (chckbxBookName->Checked && edtBookName->Text != "") //����
		spQryNote->Parameters->ParamByName("@Name")->Value = "%" + edtBookName->Text + "%";

	if (chckbxUserDefNum->Checked && edtUserDefNum->Text != "") //�Ա���
		spQryNote->Parameters->ParamByName("@UserDefCode")->Value = "%" + edtUserDefNum->Text + "%";

	if (chckbxPress->Checked && dblkpcbbPress->Text != "") //������
		spQryNote->Parameters->ParamByName("@PressID")->Value = dsetPress->FieldByName("ID")->AsInteger;

	if (chckbxISBN->Checked && edtISBN->Text != "") //ISBN
          if (isbn.Length()>13) {
               spQryNote->Parameters->ParamByName("@ISBN")->Value = isbn;
         }else
         {
               spQryNote->Parameters->ParamByName("@ISBN")->Value =  isbn ;
         }


	if (chckbxPrice->Checked && numedtMinPrice->Text != "") //����
		spQryNote->Parameters->ParamByName("@MinPrice")->Value = numedtMinPrice->Value;

	if (chckbxPrice->Checked && numedtMaxPrice->Text != "") //����
		spQryNote->Parameters->ParamByName("@MaxPrice")->Value = numedtMaxPrice->Value;

	if (chckbxType->Checked && edtyname->Text != "") //��Ŀ����
		spQryNote->Parameters->ParamByName("@BktypeID")->Value = TypeID;

	if (chckbxCustomer->Checked) //�ͻ�
		spQryNote->Parameters->ParamByName("@CustomerID")->Value = dsetCustomer->FieldByName("ID")->AsInteger;

	if (chckbxAuthor->Checked && edtAuthor->Text != "") //����
		spQryNote->Parameters->ParamByName("@Author")->Value = "%" + edtAuthor->Text + "%";

	if (chckbxRemarks->Checked && edtRemarks->Text != "") //��ע
		spQryNote->Parameters->ParamByName("@Remarks")->Value = "%" + edtRemarks->Text + "%";

	if (chckbxBkstack->Checked) //��λ
		spQryNote->Parameters->ParamByName("@BkstackID")->Value = dsetBookstack->FieldByName("ID")->AsInteger;

	if (chckbxAmount->Checked && numedtMinAmount->Text != "") //���
		spQryNote->Parameters->ParamByName("@MinAmount")->Value = numedtMinAmount->IntValue;

	if (chckbxAmount->Checked && numedtMaxAmount->Text != "") //���
		spQryNote->Parameters->ParamByName("@MaxAmount")->Value = numedtMaxAmount->IntValue;

	if (chckbxStorage->Checked) //��
		//spQryNote->Parameters->ParamByName("@StgID")->Value = dsetInit->FieldByName("StorageID")->AsInteger;
		spQryNote->Parameters->ParamByName("@StgID")->Value = dsetStorage->FieldByName("ID")->AsInteger;
	if (cbinstorage->Checked && !cboutstorage->Checked ) {
		spQryNote->Parameters->ParamByName("@type")->Value = 1;// ������ʾ����
	}
	if (cboutstorage->Checked && !cbinstorage->Checked ) {
		spQryNote->Parameters->ParamByName("@type")->Value = -1;// ������ʾ�˻�
	}
	if (chstaff->Checked ) {    //����Ա
		spQryNote->Parameters->ParamByName("@staff")->Value = int(cbstaff->Items->Objects[cbstaff->ItemIndex]);
	}
	if (chdiscount->Checked && edmindiscount->Text != "") {   //��С�ۿ�
		spQryNote->Parameters->ParamByName("@mindiscount")->Value = StrToFloat(edmindiscount->Text);
	}
	if (chdiscount->Checked && edmaxdiscount->Text != "") {   //����ۿ�
		spQryNote->Parameters->ParamByName("@maxdiscount")->Value =  StrToFloat(edmaxdiscount->Text);
	}
	if (chckbx1->Checked ) {
		spQryNote->Parameters->ParamByName("@SupplierID")->Value = dsetSupplier->FieldByName("ID")->AsInteger;
	}
    if (chjytype->Checked ) {
		spQryNote->Parameters->ParamByName("@BKJYtype")->Value = cbjytype->ItemIndex ;
	}
	if (chdanhao->Checked && eddanhao->Text != "") {
		spQryNote->Parameters->ParamByName("@NoteCode")->Value = eddanhao->Text .Trim();
	}
	spQryNote->Parameters->ParamByName("@Bsmode")->Value = 3;//���۵���ѯģʽ
	spQryNote->Parameters->ParamByName("@SearchMode")->Value = pgcntrlResult->ActivePage->Tag;

			//ͳ�ƻ���


	try
	{
		spQryNote->Active = true;
		
		switch (pgcntrlResult->ActivePage->Tag)
		{
		case 1:
			dsrcByNtHeader->DataSet = NULL;
			dsetByNtHeader->Recordset = spQryNote->Recordset;
			dsrcByNtHeader->DataSet = dsetByNtHeader;
			break;
		case 2:
			dsrcByNote->DataSet = NULL;
			dsetByNote->Recordset = spQryNote->Recordset;
			dsrcByNote->DataSet = dsetByNote;
        	break;
		case 3:
			dsrcByCustomer->DataSet = NULL;
			dsetByCustomer->Recordset = spQryNote->Recordset;
			dsrcByCustomer->DataSet = dsetByCustomer;
        	break;
		case 4:
			dsrcByBktype->DataSet = NULL;
			dsetByBktype->Recordset = spQryNote->Recordset;
			dsrcByBktype->DataSet = dsetByBktype;
        	break;
		case 5:
			dsrcByPress->DataSet = NULL;
			dsetByPress->Recordset = spQryNote->Recordset;
			dsrcByPress->DataSet = dsetByPress;
        	break;
		default:
			break;
		}
	}
	catch(...)
	{
        //
    }
}
void __fastcall TfrmQryRetailNote::tlbtnQryClick(TObject *Sender)
{
	Query();
	switch (pgcntrlResult->ActivePage->Tag) {
		case 1:
			((TFloatField *)dbgrdByNtHeader->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = Desic;
			((TFloatField *)dbgrdByNtHeader->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = Desic;
			((TFloatField *)dbgrdByNtHeader->DataSource->DataSet->FieldByName("sijidiscountprice"))->DisplayFormat = Desic;
			((TFloatField *)dbgrdByNtHeader->DataSource->DataSet->FieldByName("profite"))->DisplayFormat = Desic;
			((TFloatField *)dbgrdByNtHeader->DataSource->DataSet->FieldByName("salecbprice"))->DisplayFormat = Desic;

			break;
		case 2:
			((TFloatField *)dbgrdByNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = Desic;
			((TFloatField *)dbgrdByNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = Desic;
			((TFloatField *)dbgrdByNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0%";
			((TFloatField *)dbgrdByNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = Desic;
			((TFloatField *)dbgrdByNote->DataSource->DataSet->FieldByName("profite"))->DisplayFormat = Desic;
			((TFloatField *)dbgrdByNote->DataSource->DataSet->FieldByName("salecbprice"))->DisplayFormat = Desic;
			 ((TFloatField *)dbgrdByNote->DataSource->DataSet->FieldByName("FD"))->DisplayFormat = Desic;
			break;
		case 3:
			((TFloatField *)dbgrdByCustomer->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = Desic;
			((TFloatField *)dbgrdByCustomer->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = Desic;
			((TFloatField *)dbgrdByCustomer->DataSource->DataSet->FieldByName("profite"))->DisplayFormat = Desic;
			((TFloatField *)dbgrdByCustomer->DataSource->DataSet->FieldByName("salecbprice"))->DisplayFormat = Desic;
			break;
		case 4:
			((TFloatField *)dbgrdByBktype->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = Desic;
			((TFloatField *)dbgrdByBktype->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = Desic;
			((TFloatField *)dbgrdByBktype->DataSource->DataSet->FieldByName("profite"))->DisplayFormat = Desic;
			((TFloatField *)dbgrdByBktype->DataSource->DataSet->FieldByName("salecbprice"))->DisplayFormat = Desic;
			break;
		case 5:
			((TFloatField *)dbgrdByPress->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = Desic;
			((TFloatField *)dbgrdByPress->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = Desic;
			((TFloatField *)dbgrdByPress->DataSource->DataSet->FieldByName("profite"))->DisplayFormat = Desic;
			((TFloatField *)dbgrdByPress->DataSource->DataSet->FieldByName("salecbprice"))->DisplayFormat = Desic;
			break;
    default:
        ;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryRetailNote::edtPressKeyPress(TObject *Sender, wchar_t &Key)
{
	//
	if (Key == '\r')
	{
		String sql = "select * from BS_PressInfo where AbbreviatedName like '%";
		sql = sql + edtPress->Text + "%'";
		dsetPress->Active = false;
		dsetPress->CommandText = sql;
		dsetPress->Active = true;
		if (dsetPress->RecordCount >= 1)
		{
			dsetPress->First();
			dblkpcbbPress->KeyValue = dsetPress->FieldByName("ID")->AsInteger ;
		}
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmQryRetailNote::tlbtnExportClick(TObject *Sender)
{
	//Excel����
	switch (pgcntrlResult->ActivePage->Tag)
		{
		case 1:
			if (dsetByNtHeader->Active && dsetByNtHeader->RecordCount > 0) {
				DbgridToExcel(dbgrdByNtHeader);
			}
			break;
		case 2:
			if (dsetByNote->Active && dsetByNote->RecordCount > 0) {
				DbgridToExcel(dbgrdByNote);
			}
			break;
		case 3:
			if (dsetByCustomer->Active && dsetByCustomer->RecordCount > 0) {
				DbgridToExcel(dbgrdByCustomer);
			}
			break;
		case 4:
			if (dsetByBktype->Active && dsetByBktype->RecordCount > 0) {
				DbgridToExcel(dbgrdByBktype);
			}
			break;
		case 5:
			if (dsetByPress->Active && dsetByPress->RecordCount > 0) {
				DbgridToExcel(dbgrdByPress);
			}
			break;
		default:
			break;
		}
}
//---------------------------------------------------------------------------
//Excel��������
bool __fastcall TfrmQryRetailNote::DbgridToExcel(TDBGridEh* dbg)
{
	AnsiString temptext,path;
                        TDateTime t=   Date();
	savedlg->FileName = "���۲�ѯ"+t.DateString();

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
				if (dbg->Columns ->Items [j-1]->FieldName == "BookName") {
					AnsiString bookname;
					bookname = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					bookname = StringReplace(bookname , ",",".",TReplaceFlags()<<rfReplaceAll);
					bookname = StringReplace(bookname , '\n',"",TReplaceFlags()<<rfReplaceAll);
					bookname = StringReplace(bookname , '\r',"",TReplaceFlags()<<rfReplaceAll);
					temptext = temptext + bookname + ",";
				}
				else if (dbg->Columns ->Items [j-1]->FieldName == "FixedPrice" || dbg->Columns ->Items [j-1]->FieldName == "DiscountedPrice" || dbg->Columns ->Items [j-1]->FieldName == "sijidiscountprice" || dbg->Columns ->Items [j-1]->FieldName == "salecbprice" || dbg->Columns ->Items [j-1]->FieldName == "profite") {
					temptext = temptext + FormatFloat(Desic1,dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsFloat) + ",";
				}
				else
				{
                               //  ShowMessage(dbg->DataSource ->DataSet ->FieldByName("remarks")->AsAnsiString);
					temptext = temptext + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
				}
			}
		}
		FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
		dbg->DataSource ->DataSet ->Next() ;
	}
	dbg->DataSource ->DataSet->EnableControls();


	temptext = "\n�ϼ�,";
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
	ShowMsg(this->Handle,"������ϣ�",3);
	return false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryRetailNote::dbgrdByNtHeaderTitleClick(TColumnEh *Column)
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

void __fastcall TfrmQryRetailNote::dbgrdByNoteTitleClick(TColumnEh *Column)
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

void __fastcall TfrmQryRetailNote::dbgrdByCustomerTitleClick(TColumnEh *Column)
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

void __fastcall TfrmQryRetailNote::dbgrdByBktypeTitleClick(TColumnEh *Column)
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

void __fastcall TfrmQryRetailNote::dbgrdByPressTitleClick(TColumnEh *Column)
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

void __fastcall TfrmQryRetailNote::edsuplierKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		AnsiString sql;

                if (qfsupplier) {
                   sql = "select ID,Name from CUST_CustomerInfo where type = 1 and customerstate=1 and stgid="+IntToStr(m_storageID)+" and Name like '%" +  edsuplier->Text + "%'";
                }else sql = "select ID,Name from CUST_CustomerInfo where type = 1 and customerstate=1  and Name like '%" +  edsuplier->Text + "%'";


		dsetSupplier->Active = false;
		dsetSupplier->CommandText = sql;
		dsetSupplier->Active = true;
		dsetSupplier->First();
		dblkpcbbSupplierID->KeyValue = dsetSupplier->FieldByName("ID")->AsInteger;
	}
}
//---------------------------------------------------------------------------

void TfrmQryRetailNote::Init(LandInfo* li)
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
	dsetCustomer->Active = true;

	dsetBookstack->Connection = m_con;
	dsetBookstack->Active = true;
	qryItems->Connection = m_con;


        qfsupplier = li->qfsupply;

	dsetSupplier->Connection = m_con;
        if (qfsupplier) {
         dsetSupplier->CommandText="select ID, Name from CUST_CustomerInfo where  Type in(1) and customerstate=1 and stgid="+IntToStr(m_storageID)+" order by name";
        }else dsetSupplier->CommandText="select ID, Name from CUST_CustomerInfo where  Type in(1) and customerstate=1  order by name";

	dsetSupplier->Active = true;
	numedtMinPrice->Text = "";
	numedtMaxPrice->Text = "";
	numedtMinAmount->Text = "";
	numedtMaxAmount->Text = "";
	//dsetInit->Edit();
	//dsetInit->FieldByName("StorageID")->AsInteger = m_storageID ;
	//dsetInit->Post();
	dblkpcbbStorage->KeyValue = m_storageID ;
	chckbxStorage->Checked = true;
    TADOQuery * aq;
   aq = new TADOQuery(this);
   aq->Connection = m_con ;
   AnsiString sql;


   	sql = "select * from SYS_BSSET where name = 'changeDanHaoDisplay'";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	danhaodisplay = aq->FieldByName("value")->AsBoolean ;
	sql = "select Master from SYS_StorageInfo where id = " + IntToStr(m_storageID);
    aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
        masterstg = aq->FieldByName("Master")->AsBoolean;
	if (aq->FieldByName("Master")->AsBoolean) {
		chckbxStorage->Enabled = true;
		dblkpcbbStorage->Enabled = true;
	}
	else
	{
		chckbxStorage->Enabled = false;
		sql = "select * from BS_StoToSto where ystgid = " + IntToStr(m_storageID) + " and retail = 1";
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

        if (masterstg) {
           sql = "select id,Name,stgid from SYS_User ";
        }else  sql = "select * from SYS_User where stgid =  "+IntToStr(m_storageID);

   aq->Close();
   aq->SQL->Clear();
   aq->SQL->Add(sql);
   aq->Open();
   while (!aq->Eof )
   {
		cbstaff->AddItem(aq->FieldByName("stgid")->AsString + "��" + aq->FieldByName("Name")->AsString ,(TObject*)aq->FieldByName("ID")->AsInteger );
		aq->Next();
   }

	sql = "select ReadPurview from SYS_GroupAction left join SYS_UserGroup on SYS_GroupAction.GroupID = SYS_UserGroup.GroupID "
			" left join sys_action A1 on SYS_GroupAction.actionid = A1.Code "
			" left join sys_action A2 ON A2.CODE = A1.parent "
			" where A1.ActionName = '�ɱ���ѯ' "
			" and A2.ActionName = 'POS���۲�ѯ' "
			" and SYS_UserGroup.Userid = " + IntToStr(m_userID);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	cbpr = aq->FieldByName("ReadPurview")->AsBoolean ;

	sql = "select ReadPurview from SYS_GroupAction left join SYS_UserGroup on SYS_GroupAction.GroupID = SYS_UserGroup.GroupID "
			" left join sys_action A1 on SYS_GroupAction.actionid = A1.Code "
			" left join sys_action A2 ON A2.CODE = A1.parent "
			" where A1.ActionName = 'ë����ѯ' "
			" and A2.ActionName = 'POS���۲�ѯ' "
			" and SYS_UserGroup.Userid = " + IntToStr(m_userID);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	prf = aq->FieldByName("ReadPurview")->AsBoolean ;


   	delete aq;
	Desic = QueryDesic();
	View();
}

//---------------------------------------------------------------------------
void TfrmQryRetailNote::View()
{

	//������ʾ
	/*if (danhaodisplay) {
		dbgrdByNtHeader->Columns->Items[1]->Visible = false;
		dbgrdByNtHeader->Columns->Items[2]->Visible = true;
		dbgrdByNote->Columns->Items[7]->Visible = false;
		dbgrdByNote->Columns->Items[8]->Visible = true;
	}
	else
	{
		dbgrdByNtHeader->Columns->Items[1]->Visible = true;
		dbgrdByNtHeader->Columns->Items[2]->Visible = false;
		dbgrdByNote->Columns->Items[7]->Visible = true;
		dbgrdByNote->Columns->Items[8]->Visible = false;
	} */
	if (!prf) {
	  //	dbgrdByNtHeader->Columns->Items[6]->Visible = false;
	  //	dbgrdByNtHeader->Columns->Items[7]->Visible = false;
		dbgrdByNtHeader->Columns->Items[8]->Visible = false;
		dbgrdByNtHeader->Columns->Items[9]->Visible = false;
		dbgrdByNtHeader->Columns->Items[10]->Visible = false;
		dbgrdByNtHeader->Columns->Items[11]->Visible = false;
		 dbgrdByNtHeader->Columns->Items[12]->Visible = false;
		dbgrdByNtHeader->Columns->Items[13]->Visible = false;
		 dbgrdByNtHeader->Columns->Items[14]->Visible = false;
		 dbgrdByNtHeader->Columns->Items[16]->Visible = false;
		 dbgrdByNtHeader->Columns->Items[15]->Visible = false;


	  //	dbgrdByNote->Columns->Items[11]->Visible = false;
	  //	dbgrdByNote->Columns->Items[12]->Visible = false;
		dbgrdByNote->Columns->Items[13]->Visible = false;
			dbgrdByNote->Columns->Items[14]->Visible = false;
		dbgrdByNote->Columns->Items[15]->Visible = false;


	  //	  dbgrdByCustomer->Columns->Items[3]->Visible = false;
	  //	 dbgrdByCustomer->Columns->Items[4]->Visible = false;
		dbgrdByCustomer->Columns->Items[5]->Visible = false;
		dbgrdByCustomer->Columns->Items[6]->Visible = false;

	  //	dbgrdByBktype->Columns->Items[2]->Visible = false;
	 //	dbgrdByBktype->Columns->Items[3]->Visible = false;
		dbgrdByBktype->Columns->Items[4]->Visible = false;
		 dbgrdByBktype->Columns->Items[5]->Visible = false;

	  //	dbgrdByPress->Columns->Items[2]->Visible = false;
	  //		dbgrdByPress->Columns->Items[3]->Visible = false;
				dbgrdByPress->Columns->Items[4]->Visible = false;
					dbgrdByPress->Columns->Items[5]->Visible = false;
	}
  /*	if (!cbpr) {
		dbgrdByNtHeader->Columns->Items[8]->Visible = false;
        dbgrdByNtHeader->Columns->Items[9]->Visible = false;
		dbgrdByNtHeader->Columns->Items[10]->Visible = false;
		dbgrdByNtHeader->Columns->Items[11]->Visible = false;
		 dbgrdByNtHeader->Columns->Items[12]->Visible = false;
		dbgrdByNtHeader->Columns->Items[13]->Visible = false;
		 dbgrdByNtHeader->Columns->Items[14]->Visible = false;
		 dbgrdByNtHeader->Columns->Items[16]->Visible = false;
		 dbgrdByNtHeader->Columns->Items[15]->Visible = false;

		dbgrdByNote->Columns->Items[12]->Visible = false;
		dbgrdByCustomer->Columns->Items[5]->Visible = false;
		dbgrdByBktype->Columns->Items[4]->Visible = false;
		dbgrdByPress->Columns->Items[4]->Visible = false;
	}   */
}

//---------------------------------------------------------------------------

void __fastcall TfrmQryRetailNote::edtCustomerKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r')
	{
		String sql = "select ID,CardSN from CUST_MemberInfo where CardSN like '%";
		sql = sql + edtCustomer->Text + "%'";
		dsetCustomer->Active = false;
		dsetCustomer->CommandText = sql;
		dsetCustomer->Active = true;
		dsetCustomer->First();
		dblkpcbbCustomer->KeyValue = dsetCustomer->FieldByName("ID")->AsInteger;
	}
}
//---------------------------------------------------------------------------




void __fastcall TfrmQryRetailNote::SpeedButton1Click(TObject *Sender)
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

void __fastcall TfrmQryRetailNote::edpyqueryKeyPress(TObject *Sender, wchar_t &Key)

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

void __fastcall TfrmQryRetailNote::N2Click(TObject *Sender)
{
       //��ʷ��ϸ
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



void __fastcall TfrmQryRetailNote::dblkpcbbSupplierIDClick(TObject *Sender)
{
       	if (dblkpcbbSupplierID->Text != "") {
		chckbx1->Checked = true;
	       //	edtCustomer->Text = dsetCustomer->FieldByName("ID")->AsString ;
	}

}
//---------------------------------------------------------------------------



void __fastcall TfrmQryRetailNote::dbgrdByNtHeaderDblClick(TObject *Sender)
{
	if (dsetByNtHeader->IsEmpty() ) {
		return;
	}
	if (dsetByNtHeader->RecordCount > 0) {
		TfrmNotedetail *frm = new TfrmNotedetail(Application,dsetByNtHeader->FieldByName("Code")->AsString,9,fcon,0);
		frm->ShowModal();
		delete frm;
	}
}
//---------------------------------------------------------------------------
