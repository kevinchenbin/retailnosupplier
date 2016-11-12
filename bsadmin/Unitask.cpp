//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unitask.h"
#include "UnitSelectClient.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma link "RzButton"
#pragma resource "*.dfm"
Tfrmorderask *frmorderask;
//---------------------------------------------------------------------------
__fastcall Tfrmorderask::Tfrmorderask(TComponent* Owner,TADOConnection *con,int stgid,int userid)
	: TForm(Owner)
{
	fstgid = stgid;
	fuserid = userid;
	fcon = con;
	query->Connection = con;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = con;
	AnsiString sql;
	sql = "select ID,AbbreviatedName from BS_PressInfo";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof)
	{
		cbpress->AddItem(aq->FieldByName("AbbreviatedName")->AsString ,(TObject*)aq->FieldByName("ID")->AsInteger );
		aq->Next();
	}

	sql = "select Name from SYS_StorageInfo where id = " + IntToStr(stgid) ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	storagename = aq->FieldByName("Name")->AsAnsiString ;
	delete aq;
	ClientID = -1;
	dtpstart->Date = Date();
	dtpend->Date = Date();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmorderask::edpressKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
    	TADOQuery *aq = new TADOQuery(this);
		aq->Connection = fcon;
		AnsiString sql;
		sql = "select ID,AbbreviatedName from BS_PressInfo where AbbreviatedName like '%" + edpress->Text + "%'";
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		cbpress->Clear();
		while (!aq->Eof)
		{
			cbpress->AddItem(aq->FieldByName("AbbreviatedName")->AsString ,(TObject*)aq->FieldByName("ID")->AsInteger );
			aq->Next();
		}
		delete aq;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmorderask::spselectClientClick(TObject *Sender)
{
	TfrmselectClient * frm = new TfrmselectClient(Application,fcon,"",fstgid);
	if (mrOk == frm->ShowModal())
	{
		ClientID = frm->GetSelectID();
		ClientView();
	}
	delete frm;
}
//---------------------------------------------------------------------------
void Tfrmorderask::ClientView()
{
	if (ClientID == -1) {
		return;
	}
	String sql;
	TADOQuery * aq = new TADOQuery(NULL);
	aq->Connection = fcon;
	sql = "exec USP_BS_Client_View 0," + IntToStr(ClientID)  ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	edtclient->Text = aq->FieldByName("Name")->AsAnsiString ;
	delete aq;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmorderask::edclientKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		TfrmselectClient * frm = new TfrmselectClient(Application,fcon,edclient->Text,fstgid);
	   if (mrOk == frm->ShowModal())
	   {
			ClientID = frm->GetSelectID();
			ClientView();
	   }
	   delete frm;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmorderask::BtnViewClick(TObject *Sender)
{
	AnsiString sql,sqlwhere,sqlfrom;
	sql = "select RANK() OVER(order by BS_BookCatalog.id ) as xuhao,BS_BookCatalog.ISBN,BS_BookCatalog.Name,BS_BookCatalog.UserDefCode,BS_BookCatalog.Price,BS_BookCatalog.Author,"
			" BS_PressInfo.AbbreviatedName,BS_BookCatalog.PressCount ,sum(BS_OrderNote.Amount) as Amount,";
	sqlpress = "select distinct BS_PressInfo.AbbreviatedName ";
	sqldaochu = "select BS_BookCatalog.ISBN,BS_BookCatalog.Name as '����',convert(nvarchar(10),BS_BookCatalog.Price) as '����',BS_BookCatalog.Author as '����',"
			" BS_PressInfo.AbbreviatedName as '������',BS_BookCatalog.PressCount as '���',";
	if (chuseamount->Checked ) {
		sql = sql + " sum(BS_OrderNote.Amount) as caigouamount,";
		sqldaochu = sqldaochu + " sum(BS_OrderNote.Amount) as '�ɹ�����',";
		sqltiaojian = " having sum(BS_OrderNote.Amount) > 0 ";
		checked = true;
	}
	else
	{
		sql = sql + " case when sum(BS_OrderNote.Amount)-Order_lock.usableamount > 0 then sum(BS_OrderNote.Amount)-Order_lock.usableamount else 0 end as caigouamount ,";
		sqldaochu = sqldaochu + " case when sum(BS_OrderNote.Amount)-Order_lock.usableamount > 0 then sum(BS_OrderNote.Amount)-Order_lock.usableamount else 0 end as '�ɹ�����',";
		sqltiaojian = " having sum(BS_OrderNote.Amount) > Order_lock.usableamount ";
    	checked = false;
	}
	sql = sql + " Order_lock.usableamount,dbo.UF_BS_GetOrderCode(BS_OrderNote.BkcatalogID) as OrderCode ";
	sqldaochu = sqldaochu + " dbo.UF_BS_GetOrderCode(BS_OrderNote.BkcatalogID) as '������' ";
	sqlfrom = " from BS_OrderNoteHeader left join BS_OrderNote on BS_OrderNoteHeader.id = BS_OrderNote.OrderNtHeaderID "
			" left join Order_lock on  BS_OrderNote.BkcatalogID = Order_lock.BkcatalogID "
			" left join BS_BookCatalog on BS_OrderNote.BkcatalogID = BS_BookCatalog.id "
			" left join BS_PressInfo on BS_BookCatalog.PressID = BS_PressInfo.id "
			" where BS_OrderNoteHeader.state in (0,1) and BS_OrderNoteHeader.shenheistate = 0 "
			" and BS_OrderNote.state = 0";
	if (chstart->Checked ) {
		sqlwhere = sqlwhere + " and datediff(day,'" + DateToStr(dtpstart->Date) + "',BS_OrderNoteHeader.HdTime) >= 0";
	}
	if (chend->Checked ) {
		sqlwhere = sqlwhere + " and datediff(day,'" + DateToStr(dtpend->Date) + "',BS_OrderNoteHeader.HdTime) <= 0";
	}
	if (chpress->Checked && cbpress->Text != "") {
		sqlwhere = sqlwhere + " and BS_PressInfo.AbbreviatedName = '" + cbpress->Text + "'";
	}
	if (chclient->Checked && edtclient->Text != "") {
		sqlwhere = sqlwhere + " and BS_OrderNoteHeader.VendorID = " + IntToStr(ClientID) ;
	}
	sqlgroup = " group by BS_BookCatalog.id,BS_BookCatalog.ISBN,BS_BookCatalog.Name,BS_BookCatalog.UserDefCode,BS_BookCatalog.Price,BS_BookCatalog.Author,"
			 " BS_PressInfo.AbbreviatedName,BS_BookCatalog.PressCount,Order_lock.usableamount,BS_OrderNote.BkcatalogID ";
	sql = sql + sqlfrom + sqlwhere + sqlgroup;
	sql = sql + " order by BS_PressInfo.AbbreviatedName";
	sqlpress = sqlpress + sqlfrom + sqlwhere + " group by BS_PressInfo.AbbreviatedName";
	if (!chuseamount->Checked) {
		sqlpress =  sqlpress + ",Order_lock.usableamount";
	}
	sqlpress = sqlpress + sqltiaojian;
	sqldaochu = sqldaochu + sqlfrom + sqlwhere ;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmorderask::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmorderask::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F5) {   //��˱���
		BtnExport->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 78 ) {    //��С��
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 70 ) {   //����
	   BtnView->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 81 ) {    //�˳�
		BtnExit->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==90) {   //�ָ�����
		WindowState = wsNormal  ;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmorderask::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

bool Tfrmorderask::DbgridToExcel()
{
	query->First();
	AnsiString temptext,failename,DBPath,path,Name;
	failename = query->FieldByName("AbbreviatedName")->AsAnsiString ;
	if (failename == "") {
		savedlg->FileName = "�����粻��";
	}
	else
	{
		savedlg->FileName = failename;
	}
	if (savedlg->Execute())
	{
		DBPath = ExtractFilePath(savedlg->FileName .c_str());
		Name = ExtractFileName(savedlg->FileName .c_str());
		path = DBPath + Name + "("+ storagename + DateToStr(Date()) + ").csv";
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
	temptext = "ISBN,����,�Ա���,����,����,������,���,�ɹ�����,������";
	iFileLength   =   FileSeek(iFileHandle,0,2);
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
	temptext = "\n'";
	query->DisableControls();
	while (!query->Eof)
	{
		if (query->Fields->Fields[9]->AsInteger > 0) {
			if (query->FieldByName("AbbreviatedName")->AsAnsiString == failename ) {
				for (int i = 1; i < 8; i++) {
					if (i == 2 || i == 5) {
						AnsiString text;
						text = query->Fields->Fields[i]->AsAnsiString;
						text = StringReplace(text , ",",".",TReplaceFlags()<<rfReplaceAll);
						temptext = temptext + text + ",";
					}
					else
					{
						temptext = temptext + query->Fields->Fields[i]->AsAnsiString + ",";
					}
				}
				temptext = temptext + query->Fields->Fields[9]->AsAnsiString + ",";
				temptext =  temptext + "'"+ query->Fields->Fields[11]->AsAnsiString;
				FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
				temptext = "\n'";
			}
			else
			{
				FileClose(iFileHandle);
				failename = query->FieldByName("AbbreviatedName")->AsAnsiString;
				if (failename == "") {
					path = DBPath + "�����粻��("+ storagename + DateToStr(Date()) + ").csv";
				}
				else
				{
					path = DBPath + failename + "("+ storagename + DateToStr(Date()) + ").csv";
				}
				if(FileExists(path))
					if (DeleteFileA(path))
						iFileHandle = FileCreate(path.c_str());
					else
						return false;
				else
					iFileHandle = FileCreate(path.c_str());
				temptext = "ISBN,����,�Ա���,����,����,������,���,�ɹ�����,������";
				iFileLength   =   FileSeek(iFileHandle,0,2);
				FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
				temptext = "\n'";

				for (int i = 1; i < 8; i++) {
					if (i == 2 || i == 5) {
						AnsiString text;
						text = query->Fields->Fields[i]->AsAnsiString;
						text = StringReplace(text , ",",".",TReplaceFlags()<<rfReplaceAll);
						temptext = temptext + text + ",";
					}
					else
					{
						temptext = temptext + query->Fields->Fields[i]->AsAnsiString + ",";
					}
				}
				temptext = temptext + query->Fields->Fields[9]->AsAnsiString + ",";
				temptext =  temptext + "'"+ query->Fields->Fields[11]->AsAnsiString;
				FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
				temptext = "\n'";
			}
		}
		query->Next();
	}
	query->EnableControls();
	try {
		FileClose(iFileHandle);
	} catch (...) {
	}

          ShowMsg(Handle ,"������ϣ�",3);
	return false;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmorderask::BtnExportClick(TObject *Sender)
{
	if (query->IsEmpty() ) {
		return;
	}
	//DbgridToExcel();
	DbgridToExcel1();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmorderask::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmorderask::DBGrid1TitleClick(TColumn *Column)
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

bool Tfrmorderask::DbgridToExcel1()
{
	TADOQuery *aqpress = new TADOQuery(this);
	TADOQuery *aq = new TADOQuery(this);
	aqpress->Connection = fcon;
	aq->Connection = fcon;
	aqpress->Close();
	aqpress->SQL->Clear();
	aqpress->SQL->Add(sqlpress);
	aqpress->Open();
	Variant   WB,WS;
	Variant xWorkbook,Workbooks,vSheet,R,QueryTables,Table;
	Variant app;
	Variant   V;
	AnsiString temptext,failename,DBPath,path,Name,sql,username,usertel;

	sql = "select Name,tel from sys_user where id = " + IntToStr(fuserid) ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	username = aq->FieldByName("Name")->AsAnsiString ;
	usertel = aq->FieldByName("tel")->AsAnsiString ;


	AnsiString orderbook[5];
	sql = "select bk from sys_bsset where name = 'orderaskbook' order by id asc";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	int t = -1;
	while (!aq->Eof )
	{
		t++;
        orderbook[t] = aq->FieldByName("bk")->AsAnsiString ;
		aq->Next();
	}

	failename = aqpress->FieldByName("AbbreviatedName")->AsAnsiString ;
	if (failename == "") {
		savedlg->FileName = "�����粻��";
	}
	else
	{
		savedlg->FileName = failename;
	}
	if (savedlg->Execute())
	{
		DBPath = ExtractFilePath(savedlg->FileName .c_str());
		Name = ExtractFileName(savedlg->FileName .c_str());
		path = DBPath + Name + "("+ storagename + DateToStr(Date()) + ").xls";
	}
	else
	{
		return false;
	}
	int t1 = 0,t2 = 0;
	query->DisableControls();
	while (!aqpress->Eof )
	{
		t2++;
		sql = sqldaochu;
		if (aqpress->FieldByName("AbbreviatedName")->AsAnsiString != "" ) {
			sql = sql + " and BS_PressInfo.AbbreviatedName = '" + aqpress->FieldByName("AbbreviatedName")->AsAnsiString + "' ";
			//path = DBPath + IntToStr(t2) +".xlsx";
			path = DBPath + aqpress->FieldByName("AbbreviatedName")->AsAnsiString + "("+ storagename + DateToStr(Date()) + ").xls";
		}
		else
		{
			sql = sql + " and (BS_BookCatalog.PressID = '' or BS_BookCatalog.PressID is null) ";
			//path = DBPath + IntToStr(t2) +".xlsx";
			path = DBPath + "�����粻��("+ storagename + DateToStr(Date()) + ").xls";
		}
		if (FileExists(path) ) {
			try {

            } catch (...) {
			}
		}
		sql = sql + sqlgroup + sqltiaojian;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		V     =   Variant::CreateObject( "Excel.Application");
		V.OlePropertySet("Visible",false);
		V.OlePropertySet("DisplayAlerts",false);
		V.OlePropertyGet("WorkBooks").OleFunction("Add",1);
		xWorkbook = V.OlePropertyGet("ActiveWorkBook");
		vSheet =  xWorkbook.OlePropertyGet("ActiveSheet");


		temptext = orderbook[0];
		V.OlePropertyGet("Cells",1,1).OlePropertySet("Value",temptext .c_str() );


		temptext = "�������ڣ�" + DateToStr(Date()) ;
		V.OlePropertyGet("Cells",2,1).OlePropertySet("Value",temptext .c_str() );
		R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",2,1),vSheet.OlePropertyGet("Cells",2,8)); //ȡ�úϲ�������
		R.OlePropertyGet("Borders",4).OlePropertySet("linestyle",1);

		R.OleProcedure("Merge");
		R.OlePropertySet("HorizontalAlignment",4);

		temptext = "��Ӧ��" ;
		V.OlePropertyGet("Cells",3,1).OlePropertySet("Value",temptext .c_str() );
		vSheet.OlePropertyGet("Cells",3,1).OlePropertyGet("Font").OlePropertySet("Bold",true);
		temptext = aqpress->FieldByName("AbbreviatedName")->AsAnsiString;
		V.OlePropertyGet("Cells",3,2).OlePropertySet("Value",temptext .c_str() );
		temptext = "�ɹ���λ";
		vSheet.OlePropertyGet("Cells",3,3).OlePropertyGet("Font").OlePropertySet("Bold",true);
		V.OlePropertyGet("Cells",3,3).OlePropertySet("Value",temptext .c_str() );
		temptext = orderbook[1];
		V.OlePropertyGet("Cells",3,4).OlePropertySet("Value",temptext .c_str() );
		R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",3,4),vSheet.OlePropertyGet("Cells",3,8)); //ȡ�úϲ�������
		R.OlePropertyGet("Cells").OlePropertyGet("Font").OlePropertySet("Bold",true);

		R.OleProcedure("Merge");
		R.OlePropertySet("HorizontalAlignment",3);

		temptext = "��ϵ��" ;
		V.OlePropertyGet("Cells",4,1).OlePropertySet("Value",temptext .c_str() );
		V.OlePropertyGet("Cells",4,3).OlePropertySet("Value",temptext .c_str() );
		vSheet.OlePropertyGet("Cells",4,1).OlePropertyGet("Font").OlePropertySet("Bold",true);
		vSheet.OlePropertyGet("Cells",4,3).OlePropertyGet("Font").OlePropertySet("Bold",true);
		temptext = username;
		V.OlePropertyGet("Cells",4,4).OlePropertySet("Value",temptext .c_str() );
		R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",4,4),vSheet.OlePropertyGet("Cells",4,8)); //ȡ�úϲ�������

		R.OleProcedure("Merge");
		R.OlePropertySet("HorizontalAlignment",3);

		temptext = "��ϵ�绰" ;
		V.OlePropertyGet("Cells",5,1).OlePropertySet("Value",temptext .c_str() );
		V.OlePropertyGet("Cells",5,3).OlePropertySet("Value",temptext .c_str() );
		vSheet.OlePropertyGet("Cells",5,1).OlePropertyGet("Font").OlePropertySet("Bold",true);
		vSheet.OlePropertyGet("Cells",5,3).OlePropertyGet("Font").OlePropertySet("Bold",true);
		temptext = usertel;
		V.OlePropertyGet("Cells",5,4).OlePropertySet("Value",temptext .c_str() );
		R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",5,4),vSheet.OlePropertyGet("Cells",5,8)); //ȡ�úϲ�������

		R.OleProcedure("Merge");
		R.OlePropertySet("HorizontalAlignment",3);

		temptext = "����" ;
		V.OlePropertyGet("Cells",6,1).OlePropertySet("Value",temptext .c_str() );
		V.OlePropertyGet("Cells",6,3).OlePropertySet("Value",temptext .c_str() );
		vSheet.OlePropertyGet("Cells",6,1).OlePropertyGet("Font").OlePropertySet("Bold",true);
		vSheet.OlePropertyGet("Cells",6,3).OlePropertyGet("Font").OlePropertySet("Bold",true);
		temptext = orderbook[4];
		V.OlePropertyGet("Cells",6,4).OlePropertySet("Value",temptext .c_str() );
		R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",6,4),vSheet.OlePropertyGet("Cells",6,8)); //ȡ�úϲ�������

		R.OleProcedure("Merge");
		R.OlePropertySet("HorizontalAlignment",3);

		int h = aq->RecordCount ;
		QueryTables   =   vSheet.OlePropertyGet("QueryTables");

		R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",7,1),vSheet.OlePropertyGet("Cells",7+h,8)); //ȡ�úϲ�������
		Table   =   QueryTables.OleFunction("Add",aq->Recordset,R);
		Table.OlePropertySet("FieldNames",   true);
		Table.OleProcedure("Refresh",   true);

		V.OlePropertyGet("Columns",1).OlePropertySet("ColumnWidth",11.38);
		V.OlePropertyGet("Columns",3).OlePropertySet("ColumnWidth",6.75);
		V.OlePropertyGet("Columns",4).OlePropertySet("ColumnWidth",4.88);
		V.OlePropertyGet("Columns",5).OlePropertySet("ColumnWidth",6.38);
		V.OlePropertyGet("Columns",6).OlePropertySet("ColumnWidth",3.25);
		V.OlePropertyGet("Columns",7).OlePropertySet("ColumnWidth",6.63);
		V.OlePropertyGet("Columns",2).OlePropertySet("ColumnWidth",26.5);
		V.OlePropertyGet("Columns",2).OlePropertySet("WrapText",true);
		V.OlePropertyGet("Columns",8).OlePropertySet("ColumnWidth",12.4);
		V.OlePropertyGet("Columns",8).OlePropertySet("WrapText",true);
		/*R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",8,2),vSheet.OlePropertyGet("Cells",8+h,2)); //ȡ�úϲ�������
		R.OlePropertySet("WrapText", true);//����ָ�����������еĵ�Ԫ���е��ı��Զ�����

		R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",8,8),vSheet.OlePropertyGet("Cells",8+h,8)); //ȡ�úϲ�������
		R.OlePropertySet("WrapText", true);//����ָ�����������еĵ�Ԫ���е��ı��Զ�����
		*/
		if (h > 18) {
			R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",3,1),vSheet.OlePropertyGet("Cells",7+h,8)); //ȡ�úϲ�������
		}
		else
		{
			R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",3,1),vSheet.OlePropertyGet("Cells",25,8)); //ȡ�úϲ�������
		}

		R.OlePropertyGet("Borders",2).OlePropertySet("linestyle",1);
		R.OlePropertyGet("Borders",4).OlePropertySet("linestyle",1);


		//R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",3,1),vSheet.OlePropertyGet("Cells",24,1)); //ȡ�úϲ�������
		//R.OlePropertyGet("Borders",1).OlePropertySet("linestyle",1);
		V.OlePropertyGet("Rows",26).OleProcedure("Insert");
		temptext = "��ע�������鼮���в������뾡������ظ棬лл!" ;
		V.OlePropertyGet("Cells",26,1).OlePropertySet("Value",temptext .c_str() );
		R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",26,1),vSheet.OlePropertyGet("Cells",26,8)); //ȡ�úϲ�������

		R.OleProcedure("Merge");
		R.OlePropertyGet("Borders",2).OlePropertySet("linestyle",1);

		V.OlePropertyGet("Rows",27).OleProcedure("Insert");
		temptext = "�緢����뾡�촫����Ʊ!!!" ;
		V.OlePropertyGet("Cells",27,1).OlePropertySet("Value",temptext .c_str() );
		R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",27,1),vSheet.OlePropertyGet("Cells",27,8)); //ȡ�úϲ�������

		R.OleProcedure("Merge");
		R.OlePropertyGet("Cells").OlePropertyGet("Font").OlePropertySet("Bold",true);
		R.OlePropertyGet("Borders",2).OlePropertySet("linestyle",1);

		V.OlePropertyGet("Rows",28).OleProcedure("Insert");
		R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",28,1),vSheet.OlePropertyGet("Cells",28,8)); //ȡ�úϲ�������

		R.OleProcedure("Merge");
		R.OlePropertyGet("Borders",2).OlePropertySet("linestyle",1);


		/*temptext = "�ҹ�˾�¿�Ʊ��˰��Ϣ���£�";
		V.OlePropertyGet("Cells",28,1).OlePropertySet("Value",temptext .c_str() );
		temptext = "��        �ƣ����������Ļ����������������ι�˾";
		V.OlePropertyGet("Cells",29,1).OlePropertySet("Value",temptext .c_str() );
		temptext = "��˰��ʶ��ţ�500112736590015";
		V.OlePropertyGet("Cells",30,1).OlePropertySet("Value",temptext .c_str() );
		temptext = "�� ַ���� �����������山������·38����ס¥3¥ 023-62905966";
		V.OlePropertyGet("Cells",31,1).OlePropertySet("Value",temptext .c_str() );
		temptext = "�����м��˺ţ��й����������������֧�� 1108014210008385";
		V.OlePropertyGet("Cells",32,1).OlePropertySet("Value",temptext .c_str() );
		temptext = "�ջ���ַ�������ϰ���ѧ�����37������̿�Ժ����ʵ��ѧУ";
		V.OlePropertyGet("Cells",33,1).OlePropertySet("Value",temptext .c_str() ); */

		V.OlePropertyGet("Rows",28).OleProcedure("Insert");
		V.OlePropertyGet("Rows",28).OleProcedure("Insert");
		V.OlePropertyGet("Rows",28).OleProcedure("Insert");
		R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",28,1),vSheet.OlePropertyGet("Cells",31,8)); //ȡ�úϲ�������

		R.OleProcedure("Merge");
		R.OlePropertyGet("Cells").OlePropertyGet("Font").OlePropertySet("Bold",false);
		temptext = "�ҹ�˾�¿�Ʊ��˰��Ϣ���£�\n"
				"��        �ƣ����������Ļ����������������ι�˾\n"
				"��˰��ʶ��ţ�500112736590015\n"
				"�� ַ���� �����������山������·38����ס¥3¥ 023-62905966\n"
				"�����м��˺ţ��й����������������֧�� 1108014210008385\n"
				"�ջ���ַ�������ϰ���ѧ�����37������̿�Ժ����ʵ��ѧУ";
		V.OlePropertyGet("Cells",28,1).OlePropertySet("Value",temptext .c_str() );

		R.OlePropertyGet("Borders",2).OlePropertySet("linestyle",1);
		R.OlePropertyGet("Borders",4).OlePropertySet("linestyle",1);

		if (h > 18) {
			R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",3,1),vSheet.OlePropertyGet("Cells",7+h,1)); //ȡ�úϲ�������
		}
		else
		{
			R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",3,1),vSheet.OlePropertyGet("Cells",31,1)); //ȡ�úϲ�������
		}

		R.OlePropertyGet("Borders",1).OlePropertySet("linestyle",1);
		V.OlePropertyGet("Rows").OlePropertySet("RowHeight",23);
		V.OlePropertyGet("Cells").OlePropertyGet("Font").OlePropertySet("Size",10);

		R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",1,1),vSheet.OlePropertyGet("Cells",1,8)); //ȡ�úϲ�������
		R.OleProcedure("Merge");
		vSheet.OlePropertyGet("Cells",1,1).OlePropertyGet("Font").OlePropertySet("Name","����");   //����
		R.OlePropertyGet("Cells").OlePropertyGet("Font").OlePropertySet("Bold",true);
		vSheet.OlePropertyGet("Cells",1,1).OlePropertyGet("Font").OlePropertySet("size",16);
		R.OlePropertySet("HorizontalAlignment",3);

		try {
			xWorkbook.OleFunction("SaveAs",path.c_str());
		} catch (...) {
		}

		V.OleFunction("Quit");
		V = Unassigned;

		aqpress->Next();
	}
	query->EnableControls();
	delete aq;
	delete aqpress;


        ShowMsg(Handle ,"������ϣ�",3);
	return false;
}
//---------------------------------------------------------------------------