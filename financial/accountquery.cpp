//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "accountquery.h"
#include "..\bsadmin\UnitSelectClient.h"
#include "global.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma link "RzButton"
#pragma link "RzEdit"
#pragma link "RzCmboBx"
#pragma link "RzRadChk"
#pragma link "RzDBGrid"
#pragma link "frxClass"
#pragma link "frxDBSet"
#pragma resource "*.dfm"
TAccQuery *AccQuery;
//---------------------------------------------------------------------------
__fastcall TAccQuery::TAccQuery(TComponent* Owner,int Type,TADOConnection *cn,int stgid,bool master)
	: TForm(Owner)
{
	type = Type;
	fstgid = stgid;
	fmaster = master;
	if (type == 2) {
		this->Caption = "�ͻ������ѯ";

	}
	adoquery1->Connection = cn;
	adoquery2->Connection = cn;
	aquery->Connection  = cn;
	fcon = cn;
	Disc = "0.00";
	AnsiString sql;
   sql = "select value from sys_bsset where name = 'changeDanHaoDisplay'";
   TADOQuery *aq1 = new TADOQuery(NULL);
   aq1->Connection = cn;
   aq1->SQL->Clear();
   aq1->SQL->Add(sql);
   aq1->Open();
   ChangeDisplay = aq1->FieldByName("value")->AsBoolean;

	if (type == 1) {
		aq1->Close();
		aq1->SQL->Clear();
		aq1->SQL->Add("select * from sys_bsset where name ='xiaoshudian'");
		aq1->Open();
		Disc =  "###,###,##" + aq1->FieldByName("bk")->AsAnsiString ;
	}
	else
	{
    	aq1->Close();
		aq1->SQL->Clear();
		aq1->SQL->Add("select * from sys_bsset where name ='salexiaoshudian'");
		aq1->Open();
		Disc =  "###,###,##" + aq1->FieldByName("bk")->AsAnsiString ;
	}
   delete aq1;
   if (ChangeDisplay) {
		RzDBGrid2->Columns->Items[0]->Visible = false;
		RzDBGrid2->Columns->Items[1]->Visible = true;
   }
   else
   {
		RzDBGrid2->Columns->Items[0]->Visible = true;
		RzDBGrid2->Columns->Items[1]->Visible = false;
   }
   DTPstart->Date = Date();
   DTPend->Date = Date();
   ClientID = -1;

      sql ="select name from dbo.SYS_StorageInfo where id = "+IntToStr(fstgid);
        TADOQuery *aq = new TADOQuery(Application);
        aq->Connection = fcon;
        aq->Close();
        aq->SQL->Clear();
        aq->SQL->Add(sql);
        aq->Open();
        stgname = aq->FieldByName("name")->AsAnsiString;
        delete aq;

}
//---------------------------------------------------------------------------

void __fastcall TAccQuery::FormShow(TObject *Sender)
{
	CBstyle->Text = "ȫ��";
	CBstyle->Add("ȫ��");
	if (type == 1) {
		Label1->Caption = "��Ӧ��";
		CBcustom->Text = "ȫ����Ӧ��";
		RzDBGrid1->Columns->Items[0]->Title->Caption  = "��Ӧ������";
		RzDBGrid1->Columns->Items[1]->Title->Caption  = "����";
		RzDBGrid1->Columns->Items[7]->Title->Caption  = "ʵ�ʸ���";
		RzDBGrid2->Columns->Items[0]->Title->Caption  = "��ⵥ��";
		RzDBGrid2->Columns->Items[1]->Title->Caption  = "��ⵥ��";
		CBstyle->Add("�����˿�");
		CBstyle->Add("����");
		CBstyle->Add("Ԥ����");
		CBstyle->Add("�����Գ�");
		CBstyle->Add("����˿�");
		CBstyle->Add("�ֳ�����");
	}
	if (type == 2) {
		Label1->Caption = "�ͻ�";
		CBcustom->Text = "ȫ���ͻ�";
		RzDBGrid1->Columns->Items[0]->Title->Caption  = "�ͻ�����";
		RzDBGrid1->Columns->Items[1]->Title->Caption  = "�տ��";
		RzDBGrid1->Columns->Items[7]->Title->Caption  = "ʵ���տ�";
		RzDBGrid1->Columns->Items[9]->Title->Caption  = "Ԥ�տ�";
		RzDBGrid1->Columns->Items[10]->Title->Caption  = "����տ�";
		//RzDBGrid1->Columns->Items[11]->Title->Caption  = "ҵ��Ա";
		RzDBGrid2->Columns->Items[0]->Title->Caption  = "��������";
		RzDBGrid2->Columns->Items[1]->Title->Caption  = "��������";
		RzDBGrid2->Columns->Items[7]->Title->Caption  = "��Ӧ�տ�";
		CBstyle->Add("�տ��˿�");
		CBstyle->Add("����տ�");
		CBstyle->Add("Ԥ�տ�");
		CBstyle->Add("�����Գ�");
		CBstyle->Add("����˿�");
		CBstyle->Add("�ֳ��տ�");
	}

	CBclass->Text = "ȫ��";
	CBclass->Add("ȫ��");
	CBclass->Add("���");
	CBclass->Add("����");
	CBclass->Add("�ֽ�");
	CBclass->Add("ת��");
	CBaudit->Text = "ȫ��";
	CBaudit->Add("ȫ��");
	CBaudit->Add("δ���");
	CBaudit->Add("���");
	AnsiString sql;
	if (type == 1) {
		sql = "select ID,Name from CUST_CustomerInfo where Type = 1  and name <> '' and customerstate=1 order by name";
	}
	else
	{
		sql = "select ID,Name from CUST_CustomerInfo where Type in(2,3)  and customerstate=1 order by name";
	}
	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Open();
	while (!aquery->Eof )
	{
		CBcustom->AddItem(aquery->FieldByName("Name")->AsAnsiString,(TObject*)aquery->FieldByName("ID")->AsInteger);
		aquery->Next();
	}
	edquery->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TAccQuery::BtnViewClick(TObject *Sender)
{
	AnsiString sql,sqlwhere;

	sql="select MoneyCode,CUST_CustomerInfo.name as CustmerName,Payment,ClearingType,Convert(varchar(20),FN_CUSEndMoneyDocuments.date,111) as date,Convert(varchar(20),paymentdate,111) as paymentdate,Remarks,FN_CUSEndMoneyDocuments.Salesman,yuhu,sum(FN_CUSEndMoneyDtails.thistime) as thistime,sum(FN_CUSEndMoneyDtails.hongcong) as hongcong,sum(FN_CUSEndMoneyDtails.thistime-FN_CUSEndMoneyDtails.hongcong)-FN_CUSEndMoneyDocuments.overage as shifu,"
			"Clearingstyle,CASE State WHEN 1 THEN '���' WHEN 0 THEN 'δ���' END  as State,fapiao,FN_CUSEndMoneyDocuments.overage,jiespz "
			"from FN_CUSEndMoneyDocuments join CUST_CustomerInfo on FN_CUSEndMoneyDocuments.cusid = CUST_CustomerInfo.id left join FN_CUSEndMoneyDtails on FN_CUSEndMoneyDocuments.MoneyCode = FN_CUSEndMoneyDtails.EndMoneyDocumentID where FN_CUSEndMoneyDocuments.type = " + IntToStr(type) ;
	if (type == 1) {
		if (CBcustom->Text != "ȫ����Ӧ��") {
			sqlwhere = " and FN_CUSEndMoneyDocuments.cusid = " + IntToStr((int)(CBcustom->Items->Objects[CBcustom->ItemIndex]));
		}
	}
	if (type == 2) {
		if (CBcustom->Text != "ȫ���ͻ�") {
			sqlwhere = " and FN_CUSEndMoneyDocuments.cusid = " + IntToStr((int)(CBcustom->Items->Objects[CBcustom->ItemIndex]));
		}
	}
	if (CBstart->Checked ) {
		sqlwhere = sqlwhere + " and paymentdate >= '" + DateToStr(DTPstart->Date) + " 0:00:00'";
	}
	if (CBend->Checked ) {
		sqlwhere = sqlwhere + " and paymentdate <= '" + DateToStr(DTPend->Date) + " 23:59:59'";
	}
	if (CBstyle->Text != "ȫ��" && CBstyle->Text != "") {
		sqlwhere = sqlwhere + " and ClearingType = '" + CBstyle->Text + "'";
	}
	if (CBclass->Text != "ȫ��" && CBclass->Text != "") {
		sqlwhere = sqlwhere + " and Clearingstyle = '" + CBclass->Text + "'";
	}
	if (CBaudit->Text != "ȫ��" && CBaudit->Text != "") {
		if (CBaudit->Text == "δ���") {
			sqlwhere = sqlwhere + " and State = 0";
		}
		if (CBaudit->Text == "���") {
			sqlwhere = sqlwhere + " and State = 1";
		}
	}
	if (!fmaster) {
        sqlwhere = sqlwhere + " and FN_CUSEndMoneyDocuments.stgid = " + IntToStr(fstgid);
	}

	sql = sql + sqlwhere;
	sql = sql + " group by MoneyCode,CUST_CustomerInfo.name,Payment,ClearingType,FN_CUSEndMoneyDocuments.date,paymentdate,Remarks,FN_CUSEndMoneyDocuments.Salesman,yuhu,Clearingstyle,State,fapiao,FN_CUSEndMoneyDocuments.overage,jiespz order by custmername";
	adoquery1->Close();
	adoquery1->SQL->Clear();
	adoquery1->SQL->Add(sql);
	adoquery1->Open();

	((TFloatField *)RzDBGrid1->DataSource->DataSet->FieldByName("Payment"))->DisplayFormat = Disc;
	((TFloatField *)RzDBGrid1->DataSource->DataSet->FieldByName("yuhu"))->DisplayFormat = Disc;
	((TFloatField *)RzDBGrid1->DataSource->DataSet->FieldByName("thistime"))->DisplayFormat = Disc;

	((TFloatField *)RzDBGrid1->DataSource->DataSet->FieldByName("shifu"))->DisplayFormat = Disc;
	((TFloatField *)RzDBGrid1->DataSource->DataSet->FieldByName("overage"))->DisplayFormat = Disc;
	((TFloatField *)RzDBGrid1->DataSource->DataSet->FieldByName("hongcong"))->DisplayFormat = Disc;
	adoquery2->Close();
}
//---------------------------------------------------------------------------

void __fastcall TAccQuery::RzDBGrid1CellClick(TColumn *Column)
{
	AnsiString sql;
	if (adoquery1->IsEmpty() ) {
    	return;
	}
	if (type == 1) {
		sql="select BS_StorageNoteHeader.StgNtCode as NtCode,StgNtCodeStr as CodeStr,BS_StorageNoteHeader.TotalFixedPrice as FixedPrice,BS_StorageNoteHeader.TotalDiscountedPrice as DiscountedPrice,FN_CUSEndMoneyDtails.thistime,"
			"BS_StorageNoteHeader.TotalAmount,BS_StorageNoteHeader.AddCosts,BS_StorageNoteHeader.AddCosts + BS_StorageNoteHeader.TotalDiscountedPrice as totalyingfu,BS_StorageNoteHeader.Checked,BS_StorageNoteHeader.NoChecked,Convert(varchar(20),BS_StorageNoteHeader.HdTime,111) as HdTime,Remarks from BS_StorageNoteHeader "
			"left join FN_CUSEndMoneyDtails on BS_StorageNoteHeader.StgNtcode=FN_CUSEndMoneyDtails.stgntcode where EndMoneyDocumentID="+adoquery1->FieldByName("MoneyCode")->AsString;
	}
	if (type == 2) {
		sql="select WsaleNtCode as NtCode,WsaleNtCodeStr as CodeStr,FixedPrice,DiscountedPrice,FN_CUSEndMoneyDtails.thistime,"
			"BS_WsaleNoteHeader.TotalAmount,BS_WsaleNoteHeader.AddCosts,BS_WsaleNoteHeader.AddCosts + DiscountedPrice as totalyingfu, BS_WsaleNoteHeader.Checked,BS_WsaleNoteHeader.NoChecked,Convert(varchar(20),BS_WsaleNoteHeader.HdTime,111) as HdTime,Remarks from BS_WsaleNoteHeader "
			"left join FN_CUSEndMoneyDtails on WsaleNtCode=stgntcode where  EndMoneyDocumentID="+adoquery1->FieldByName("MoneyCode")->AsString;
	}
	if (adoquery1->RecordCount > 0) {
    	adoquery2->Close();
		adoquery2->SQL->Clear();
		adoquery2->SQL->Add(sql);
		adoquery2->Open();
		/*RzDBGrid2->Columns->Items[0]->Width = 84;
		RzDBGrid2->Columns->Items[1]->Width = 84;
		RzDBGrid2->Columns->Items[2]->Width = 64;
		RzDBGrid2->Columns->Items[3]->Width = 64;
		RzDBGrid2->Columns->Items[4]->Width = 64;
		RzDBGrid2->Columns->Items[5]->Width = 64;
		RzDBGrid2->Columns->Items[6]->Width = 64;
		RzDBGrid2->Columns->Items[7]->Width = 64;
		RzDBGrid2->Columns->Items[8]->Width = 80;
		RzDBGrid2->Columns->Items[9]->Width = 64;  */
		((TFloatField *)RzDBGrid2->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = Disc;
		((TFloatField *)RzDBGrid2->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = Disc;
		((TFloatField *)RzDBGrid2->DataSource->DataSet->FieldByName("AddCosts"))->DisplayFormat = Disc;
		((TFloatField *)RzDBGrid2->DataSource->DataSet->FieldByName("Checked"))->DisplayFormat = Disc;
		((TFloatField *)RzDBGrid2->DataSource->DataSet->FieldByName("NoChecked"))->DisplayFormat = Disc;
		((TFloatField *)RzDBGrid2->DataSource->DataSet->FieldByName("totalyingfu"))->DisplayFormat = Disc;
		((TFloatField *)RzDBGrid2->DataSource->DataSet->FieldByName("TotalAmount"))->DisplayFormat = "###,###,##0";
		((TFloatField *)RzDBGrid2->DataSource->DataSet->FieldByName("thistime"))->DisplayFormat = Disc;
	}
}
//---------------------------------------------------------------------------

void __fastcall TAccQuery::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TAccQuery::FormClose(TObject *Sender, TCloseAction &Action)
{
	 Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall TAccQuery::edqueryKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		AnsiString sql;
		if (type == 1) {
			sql = "select ID,Name from CUST_CustomerInfo where type = 1 and customerstate=1 and Name like '%" + edquery->Text + "%' and name <> ''";
        	aquery->Close();
			aquery->SQL->Clear();
			aquery->SQL->Add(sql);
			aquery->Open();
			CBcustom->Clear();
			while (!aquery->Eof )
			{
				CBcustom->AddItem(aquery->FieldByName("Name")->AsString,(TObject*)aquery->FieldByName("ID")->AsInteger );
				aquery->Next();
			}
			aquery->First();
			CBcustom->ItemIndex = CBcustom->Items->IndexOfObject((TObject*)aquery->FieldByName("ID")->AsInteger );
		}
		else
		{
			sql = "select ID,Name from CUST_CustomerInfo where type in(2,3) and customerstate=1 and Name like '%" + edquery->Text + "%' and name <> ''";
        	aquery->Close();
			aquery->SQL->Clear();
			aquery->SQL->Add(sql);
			aquery->Open();
			CBcustom->Clear();
			while (!aquery->Eof )
			{
				CBcustom->AddItem(aquery->FieldByName("Name")->AsString,(TObject*)aquery->FieldByName("ID")->AsInteger );
				aquery->Next();
			}
			aquery->First();
			CBcustom->ItemIndex = CBcustom->Items->IndexOfObject((TObject*)aquery->FieldByName("ID")->AsInteger );
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TAccQuery::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Shift.Contains(ssCtrl)&& Key == 70 ) {    //��ѯ
		BtnView->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 78 ) {    //��С��
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 81 ) {    //�˳�
		BtnExit->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==90) {   //�ָ�����
		WindowState = wsNormal  ;
	}
	if (Key == VK_F4) {   //����
		BtnExport->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall TAccQuery::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall TAccQuery::BtnExportClick(TObject *Sender)
{
	if (adoquery1->IsEmpty() ) {
		return;
	}
	DbgridToExcel(RzDBGrid1);
}
//---------------------------------------------------------------------------
bool TAccQuery::DbgridToExcel(TRzDBGrid* dbg)
{
	AnsiString temptext,path;
	savedlg->FileName = CBcustom->Text + "(" + this->Caption + ")";

	if (savedlg->Execute())
	{
		String DBPath,Name;
		DBPath = Sysutils::ExtractFilePath(savedlg->FileName.c_str());
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
	AnsiString sql;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;

	dbg->DataSource ->DataSet ->First();
	dbg->DataSource ->DataSet->DisableControls();


        temptext = "\n";
		for(int q=0;q<dbg->FieldCount ;++q)
		{
			if (dbg->Columns->Items[q]->Visible == true) {
                             if ((dbg->Columns ->Items [q]->Title ->Caption=="��������")||(dbg->Columns ->Items [q]->Title ->Caption=="����")||(dbg->Columns ->Items [q]->Title ->Caption=="����")||(
                             dbg->Columns ->Items [q]->Title ->Caption=="ʵ��")||(dbg->Columns ->Items [q]->Title ->Caption=="����")||(dbg->Columns ->Items [q]->Title ->Caption=="��ע")) {
                             	t1++;
				temptext = temptext + dbg->Columns ->Items [q]->Title ->Caption + ",";
                             }

			}
		}
		iFileLength   =   FileSeek(iFileHandle,0,2);
		FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());


	while(!dbg->DataSource ->DataSet->Eof)
	{

		temptext = "\n";
		for(int j=1;j<dbg->Columns ->Count+1  ;j++)
		{
			if (dbg->Columns->Items[j-1]->Visible == true) {
				if (dbg->Columns ->Items [j-1]->FieldName == "MoneyCode" ) {
					temptext = temptext + "'"+ dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
				}
				else
				{
					temptext = temptext + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
				}
			}
		}
		FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

		if (type == 1) {
			sql="select BS_StorageNoteHeader.StgNtCode as NtCode,StgNtCodeStr as CodeStr,BS_StorageNoteHeader.TotalFixedPrice as FixedPrice,BS_StorageNoteHeader.TotalDiscountedPrice as DiscountedPrice,FN_CUSEndMoneyDtails.thistime,"
				"BS_StorageNoteHeader.TotalAmount,BS_StorageNoteHeader.AddCosts,BS_StorageNoteHeader.Checked,BS_StorageNoteHeader.AddCosts + BS_StorageNoteHeader.TotalDiscountedPrice as totalyingfu,BS_StorageNoteHeader.NoChecked,Convert(varchar(20),BS_StorageNoteHeader.HdTime,111) as HdTime,Remarks from BS_StorageNoteHeader "
				"left join FN_CUSEndMoneyDtails on BS_StorageNoteHeader.StgNtcode=FN_CUSEndMoneyDtails.stgntcode where EndMoneyDocumentID="+adoquery1->FieldByName("MoneyCode")->AsString;
		}
		if (type == 2) {
			sql="select WsaleNtCode as NtCode,WsaleNtCodeStr as CodeStr,FixedPrice,DiscountedPrice,FN_CUSEndMoneyDtails.thistime,"
				"BS_WsaleNoteHeader.TotalAmount,BS_WsaleNoteHeader.AddCosts + DiscountedPrice as totalyingfu,BS_WsaleNoteHeader.AddCosts,BS_WsaleNoteHeader.Checked,BS_WsaleNoteHeader.NoChecked,Convert(varchar(20),BS_WsaleNoteHeader.HdTime,111) as HdTime,Remarks from BS_WsaleNoteHeader "
				"left join FN_CUSEndMoneyDtails on WsaleNtCode=stgntcode where  EndMoneyDocumentID="+adoquery1->FieldByName("MoneyCode")->AsString;
		}
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		temptext = "\n";
		if (aq->RecordCount > 0) {
			for(int q=0;q<RzDBGrid2->FieldCount ;++q)
			{
				if (RzDBGrid2->Columns->Items[q]->Visible == true) {
					temptext = temptext + RzDBGrid2->Columns ->Items [q]->Title ->Caption + ",";
				}
			}
			FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

			aq->First();
			while (!aq->Eof)
			{
				temptext = "\n";
				for(int j=1;j<RzDBGrid2->Columns ->Count+1;j++)
				{
					if (RzDBGrid2->Columns->Items[j-1]->Visible == true) {
						if (RzDBGrid2->Columns ->Items [j-1]->FieldName == "NtCode" || RzDBGrid2->Columns ->Items [j-1]->FieldName == "CodeStr") {
							temptext = temptext + "'"+ aq ->FieldByName(RzDBGrid2->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
						}
						else
						{
							temptext = temptext + aq->FieldByName(RzDBGrid2->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
						}
					}
				}
				FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
				aq->Next();
			}
		}

        temptext = "\n";
		FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
		dbg->DataSource ->DataSet ->Next() ;
	}
	dbg->DataSource ->DataSet->EnableControls();
    delete aq;

	FileClose(iFileHandle);

	ShowMsg(this->Handle,"������ϣ�",3);
	return false;
}



//---------------------------------------------------------------------------

void __fastcall TAccQuery::DTPstartChange(TObject *Sender)
{
	CBstart->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TAccQuery::DTPendChange(TObject *Sender)
{
	CBend->Checked = true;
}
void TAccQuery::print(int i)
{
     adoquery1->DisableControls();
       if (adoquery1->IsEmpty() ) {
		return;
	}
         report->LoadFromFile(Sysutils::ExtractFilePath(Application->ExeName) + "jiestj.fr3");
		report->PrepareReport(true);

            	if (i == 0) {
			report->PrintOptions->ShowDialog = false;
			report->Print();
		}
		else
		{
			report->ShowPreparedReport();
		}
		report->Free();

   adoquery1->EnableControls();



}
//---------------------------------------------------------------------------



void __fastcall TAccQuery::reportGetValue(const UnicodeString VarName, Variant &Value)

{
	if (CompareText(VarName,"\"title\"")==0 ) {
		  Value = stgname+this->Caption;
	}
	if (CompareText(VarName,"\"begindate\"")==0 ) {
		  Value ="2013-03-02";//FormatFloat("��0.00",fandian);
	}
	if (CompareText(VarName,"\"enddate\"")==0 ) {
		  Value = "2013-03-02";;
	}
}
//---------------------------------------------------------------------------

void __fastcall TAccQuery::RzToolButton1Click(TObject *Sender)
{
print(1);
}
//---------------------------------------------------------------------------

void __fastcall TAccQuery::RzToolButton2Click(TObject *Sender)
{
print(1);
}
//---------------------------------------------------------------------------

void __fastcall TAccQuery::RzDBGrid1TitleClick(TColumn *Column)
{
	 	AnsiString qusort;
	if (adoquery1->IsEmpty() ) {
		return;
	}
	qusort =  Column->FieldName + " ASC";
	if (adoquery1->Sort == "") {
		adoquery1->Sort =  Column->FieldName + " ASC";
	}
	else if (adoquery1->Sort == qusort) {
		adoquery1->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		adoquery1->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------
