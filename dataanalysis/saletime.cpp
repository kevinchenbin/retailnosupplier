//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "saletime.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "RzRadChk"
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma link "frxClass"
#pragma link "frxDBSet"
#pragma resource "*.dfm"
Tfrmsaletime *frmsaletime;
//---------------------------------------------------------------------------
__fastcall Tfrmsaletime::Tfrmsaletime(TComponent* Owner,TADOConnection *cn,int stgid)
	: TForm(Owner)
{
  query->Connection = cn;
  aqprint->Connection=cn;
  dtpstart->Date = Date();
  dtpend->Date = Date();
  TADOQuery * aq;

  String sql;
  aq = new TADOQuery(this);
  aq->Connection = cn;
  aq->Close();
  aq->SQL->Clear();
  aq->SQL->Add("select * from sys_bsset where name ='retailxiaoshudian'");
  aq->Open();
  retaiformat =  "��###,###,##" + aq->FieldByName("bk")->AsAnsiString ;
  aq->Close();
  aq->SQL->Clear();
  aq->SQL->Add("select * from sys_bsset where name ='salexiaoshudian'");
  aq->Open();
  saleformat =  "��###,###,##" + aq->FieldByName("bk")->AsAnsiString ;

  sql = "select ID,Name  from SYS_StorageInfo";
  aq->Close();
  aq->SQL->Clear();
  aq->SQL->Add(sql);
  aq->Open();
  while (!aq->Eof)
  {
		cbstorage->AddItem(aq->FieldByName("Name")->AsString,(TObject*)aq->FieldByName("ID")->AsInteger);
		aq->Next();
  }
  cbstorage->ItemIndex = cbstorage->Items->IndexOfObject((TObject*)stgid);
  sql = "select Master from SYS_StorageInfo where id = " + IntToStr(stgid);
  aq->Close();
  aq->SQL->Clear();
  aq->SQL->Add(sql);
  aq->Open();
  if (aq->FieldByName("Master")->AsBoolean ) {
		cbstorage->Enabled = true;
		chstorage->Enabled = true;
  }
  else
  {
  		cbstorage->Enabled = false;
		chstorage->Enabled = false;
  }
// DBGridEh2->Columns->Items[0]->Visible = false;



  delete aq;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsaletime::BtnViewClick(TObject *Sender)
{
	AnsiString  sqlwhere,sql;
	sql = " exec [USP_BS_Saletime] ";
	if (chstorage->Checked ) {
		int fstgid;
		try {
			fstgid = (int)cbstorage->Items->Objects[cbstorage->ItemIndex];
		} catch (...) {

                      ShowMsg(Handle ,"��ѡ����ȷ�ĵ�ţ�",3);
			return;
		}
		sql = sql + IntToStr(fstgid);
	}
	else
	{
		sql = sql + "null";
	}
	if (cbstart->Checked) {
		sql = sql + ",'" + DateToStr(dtpstart->Date) + "'";
	}
	else
	{
		sql = sql + ",null";
	}
	if (cbend->Checked) {
		sql = sql + ",'" + DateToStr(dtpend->Date) + "'";
	}
	else
	{
		sql = sql + ",null";
	}
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();

}
//---------------------------------------------------------------------------
void __fastcall Tfrmsaletime::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsaletime::BtnExportClick(TObject *Sender)
{

	if (query->Active && query->RecordCount > 0) {
         // ShowMessage(dg->Columns ->Items[2]->Footer->Value);
		DbgridToExcel(dg);
	}
}
//---------------------------------------------------------------------------

//Excel��������
bool __fastcall Tfrmsaletime::DbgridToExcel(TDBGridEh* dbg)
{
	if (dbg->DataSource ->DataSet->IsEmpty() ) {
		return false;
	}
	AnsiString temptext,path;
      TDateTime t=   Date();//

                               //           Now()
	savedlg->FileName = this->Caption+t.DateString();
	if (savedlg->Execute())
	{
		String DBPath,Name;
		DBPath = Sysutils::ExtractFilePath(savedlg->FileName .c_str()  );
		Name = Sysutils::ExtractFileName(savedlg->FileName .c_str() );
		DBPath = DBPath + Name + ".csv";
		path =  DBPath;
	}
	else
	{
		return false;
	}
	int  iFileHandle;
	int  iFileLength;
	if(FileExists(path))
	   if (DeleteFileA(path))
			iFileHandle = FileCreate(path.c_str());
	   else
			return false;
	else
		iFileHandle = FileCreate(path.c_str());


	temptext= dbg->Columns ->Items [0]->Title ->Caption+','+dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [0]->FieldName )->AsAnsiString;
		temptext=temptext+","+"����,"+DateToStr(dtpstart->Date)+",��,"+DateToStr(dtpend->Date);
	iFileLength   =   FileSeek(iFileHandle,0,2);
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
		temptext = "\n";
	for(int q=1;q<8 ;++q)
	{
		if (dbg->Columns->Items[q]->Visible == true) {
			temptext = temptext + dbg->Columns ->Items [q]->Title ->Caption + ",";
		}
	}
	iFileLength   =   FileSeek(iFileHandle,0,2);
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	//����

		dbg->DataSource ->DataSet->DisableControls();
	dbg->DataSource ->DataSet ->First();
	while(!dbg->DataSource ->DataSet->Eof)
	{
		temptext = "\n";
		for(int j=2;j<9  ;j++)
		{
			if (dbg->Columns->Items[j-1]->Visible == true) {
					temptext = temptext + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
				}
		}
		iFileLength   =   FileSeek(iFileHandle,0,2);
		FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
		dbg->DataSource ->DataSet ->Next() ;
	}
	dbg->DataSource ->DataSet->EnableControls();


	//����
	temptext = "\n";
		for(int q=8;q<15 ;++q)
	{
		if (dbg->Columns->Items[q]->Visible == true) {
			temptext = temptext + dbg->Columns ->Items [q]->Title ->Caption + ",";
		}
	}
	iFileLength   =   FileSeek(iFileHandle,0,2);
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());


		//����

		dbg->DataSource ->DataSet->DisableControls();
	dbg->DataSource ->DataSet ->First();
	while(!dbg->DataSource ->DataSet->Eof)
	{
		temptext = "\n";
		for(int j=9;j<15  ;j++)
		{
			if (dbg->Columns->Items[j-1]->Visible == true) {
					temptext = temptext + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
				}
		}
		iFileLength   =   FileSeek(iFileHandle,0,2);
		FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
		dbg->DataSource ->DataSet ->Next() ;
	}
	dbg->DataSource ->DataSet->EnableControls();

   /*
	dbg->DataSource ->DataSet ->First();
	while(!dbg->DataSource ->DataSet->Eof)
	{
		temptext = "\n";
		for(int j=1;j<dbg->Columns ->Count+1  ;j++)
		{
			if (dbg->Columns->Items[j-1]->Visible == true) {
			if (j==5) {
				temptext = "\n";
			}
					temptext = temptext + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
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
			temptext = temptext + dbg->GetFooterValue(0,dbg->Columns ->Items[q])+ ",";// dbg->Columns ->Items[q]->Footer->Value + ",";
		}
	}
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());  */
	FileClose(iFileHandle);
	ShowMsg(Handle ,"������ϣ�",3);
	return false;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsaletime::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsaletime::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F1) {
		BtnView->Click();
	}
	if (Key == VK_F10) {
		BtnPrint->Click();
	}
	if (Key == VK_F8) {
		BtnExport->Click();
	}

	if (Shift.Contains(ssCtrl)&& Key ==90) {
		WindowState = wsNormal  ;
	}
	if (Shift.Contains(ssCtrl)&& Key ==81  ) {
		BtnExit->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 78 ) {
		BtnAlignBottom->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsaletime::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized   ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsaletime::dtpstartChange(TObject *Sender)
{
	cbstart->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsaletime::dtpendChange(TObject *Sender)
{
	cbend->Checked = true;
}
//---------------------------------------------------------------------------

void Tfrmsaletime::init()
{
                if (!searchPower) {

         dg->Columns->Items[4]->Visible = false;
         dg->Columns->Items[5]->Visible = false;
          dg->Columns->Items[9]->Visible = false;
         dg->Columns->Items[10]->Visible = false;
         dg->Columns->Items[13]->Visible = false;
        dg->Columns->Items[14]->Visible = false;

  }
  }
//---------------------------------------------------------------------------


void __fastcall Tfrmsaletime::SpeedButton1Click(TObject *Sender)
{

AnsiString sql;
sql = "select '����' R0, sum(BS_RetailNoteHeader.TotalDiscountedprice) as R1 ,sum(BS_RetailNoteHeader.TotalFixedprice) as R2,sum(BS_RetailNoteHeader.Totalamount) as R3,sum((CASE WHEN dbo.BS_RetailNoteHeader.TotalDiscountedPrice > (RecCash + RecCardMoney) ";
sql =sql + " THEN (RecCash + RecCardMoney) ELSE dbo.BS_RetailNoteHeader.TotalDiscountedPrice END)) as R4,sum(BS_RetailNoteHeader.nochecked) R5 ";
sql =sql +  " from BS_RetailNoteHeader	where('"+DateToStr(dtpstart->Date)+"' is null or datediff(day,'"+DateToStr(dtpstart->Date)+"',HdTime) >= 0)	and ('"+DateToStr(dtpend->Date)+"' is null or datediff(day,'"+DateToStr(dtpend->Date)+"',HdTime) <= 0) ";
sql =sql + " union all ";
sql =sql + " select '����' R0 ,sum(BS_WsaleNoteHeader.Checked) as R4 , sum(BS_WsaleNoteHeader.Nochecked) as R5,sum(BS_WsaleNoteHeader.totalamount) as R3,sum(BS_WsaleNoteHeader.discountedprice) as R1,sum(BS_WsaleNoteHeader.fixedprice) as R2  ";
  sql =sql +  " FROM  BS_WsaleNoteHeader	where ('"+DateToStr(dtpstart->Date)+"' is null or datediff(day,'"+DateToStr(dtpstart->Date)+"',HdTime) >= 0) and ('"+DateToStr(dtpend->Date)+"' is null or datediff(day,'"+DateToStr(dtpend->Date)+"',HdTime) <= 0)";
sql=sql+" union all ";
sql=sql+"    select '��������' R0,sum(nochecked) R5,sum(totalfixedprice) R2,sum(totalamount) R3,sum(totaldiscountedprice) R1,sum(thistime) R4  from dbo.FN_CUSEndMoneyDocuments a join FN_CUSEndMoneyDtails b on ";
sql=sql+" b.endmoneydocumentid= a.moneycode ";
sql=sql +" where a.state = 1 and clearingtype <>'�ֳ��տ�' and ('"+DateToStr(dtpstart->Date)+"' is null or datediff(day,'"+DateToStr(dtpstart->Date)+"',date) >= 0) and ('"+DateToStr(dtpend->Date)+"' is null or datediff(day,'"+DateToStr(dtpend->Date)+"',date) <= 0)";

 //sql=Format(sql,[DateToStr(dtpstart->Date),DateToStr(dtpstart->Date),DateToStr(dtpend->Date),DateToStr(dtpend->Date),[DateToStr(dtpstart->Date),DateToStr(dtpstart->Date),DateToStr(dtpend->Date),DateToStr(dtpend->Date)]);
		aqprint->Close();
		aqprint->SQL->Clear();
		aqprint->SQL->Add(sql);
		aqprint->Open();

	 AnsiString path;
	 path = ExtractFilePath(Application->ExeName) +"salehuizhong.fr3";
	 frx->LoadFromFile(path);
	 frx->PrepareReport(true);


			frx->ShowPreparedReport();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsaletime::frxGetValue(const UnicodeString VarName, Variant &Value)

{

	if (CompareText(VarName,"\"datestr\"")==0 ) {
		  Value = DateToStr(dtpstart->Date)+"��"+DateToStr(dtpend->Date);;
	}
   if (CompareText(VarName,"\"dianming\"")==0 ) {
		  Value = cbstorage->Text;
	}


}
//---------------------------------------------------------------------------

