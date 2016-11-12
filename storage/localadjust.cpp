//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "localadjust.h"
#include "QryNoteCodeForm.h"
#include "global.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzDBGrid"
#pragma link "RzPanel"
#pragma link "RzButton"
#pragma resource "*.dfm"
Tfrmadjust *frmadjust;
//---------------------------------------------------------------------------
__fastcall Tfrmadjust::Tfrmadjust(TComponent* Owner,TADOConnection* con,LandInfo* li)
	: TForm(Owner)
{
	li->con = con;
	fcon = con;
	checkli = *li;
	aquery->Connection = con;
	m_storageID = li->storageID ;
	edtemploy->Text = li->UserName ;
	atable->Connection = con;
	adosp->Connection = con;
	aqueryupdate->Connection = con;
	aqheader->Connection = con;
	CatalogSearchMode = 1;//
	m_storageID = checkli.storageID ;
	dtpdate->Date = Date();
	AnsiString sql;
	sql = "select * from STK_stackAdjustHead ";
	aqheader->Close();
	aqheader->SQL->Clear();
	aqheader->SQL->Add(sql);
	aqheader->Open();
}
void Tfrmadjust::readyData(TADOQuery * aquery)
{
    Store = new TStringList();
	Local = new TStringList();
	AnsiString value;
	AnsiString sql ;
	AnsiString Note="";

	int LocalID;
	int StorgeID;
	sql = "select name from SYS_StorageInfo where id = " + IntToStr(m_storageID);
    aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Open();
	labtitle->Caption = aquery->FieldByName("name")->AsAnsiString.Trim();

	sql = "select ID,Name from STK_Bookstackinfo where stgid = " + IntToStr(m_storageID);
	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Open();

	while(!aquery->Eof)
	{
	   cblocalin->Items->AddObject(aquery->FieldByName("Name")->AsAnsiString ,(TObject*)aquery->FieldByName("ID")->AsInteger );
	   aquery->Next();
	}
	cblocalin->ItemIndex = 0;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmadjust::edtcheckinfoKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r')                //int m_catalogSearchMode;//1���� 2Ϊ�Ա��� 3Ϊ����  4 ISBN 5 ����
	{
		if (edtcheckinfo->Text == "") {
            ChangeCatalogSearchMode();
			return;
		}

		if (edtnum->Text == "") {

                     ShowMsg(Handle ,"������ӿ�λ��������",3);
			return;
		}
		//�����Ƿ�������ȷ
		if (CatalogSearchMode == 4) {
			try {
				float pice = StrToFloat(edtcheckinfo->Text);
			} catch (...) {

                                ShowMsg(Handle ,"��¼����ȷ�Ķ��ۣ�",3);
				return;
			}
		}
		AnsiString sql;
		AnsiString NowLocal;
		int adjust;

		//1���� 2Ϊ�Ա��� 3Ϊ����  4 ISBN 5 ����

		sql = "select STK_BookInfo.id as bkinfoid,BS_BookCatalog.ID,STK_BookInfo.SupplierID,BS_BookCatalog.Name,BS_BookCatalog.Barcode,"
			"BS_BookCatalog.UserDefCode,BS_BookCatalog.ISBN,CUST_CustomerInfo.Name as SupplierName,BS_BookCatalog.ID  as STK_BookinfoID,"
			"STK_BookInfo.Amount,STK_BookstackInfo.Name as BkstackName,BS_BookCatalog.Price ,BS_PressInfo.AbbreviatedName ,STK_BookstackInfo.name LocalName, "
			"STK_BookInfo.BKstackID "
			"from STK_BookInfo left join BS_BookCatalog on STK_BookInfo.BkcatalogID=BS_BookCatalog.ID "
			"left join CUST_CustomerInfo on STK_BookInfo.SupplierID=CUST_CustomerInfo.ID "
			"left join STK_BookstackInfo on STK_BookInfo.BkstackID=STK_BookstackInfo.ID "
			"left join BS_PressInfo ON BS_BookCatalog.PressID = BS_PressInfo.ID "
			"where STK_BookstackInfo.StgID=" + IntToStr(m_storageID);
		   //	+ " and  STK_BookstackInfo.id = " + IntToStr(m_local);
		AnsiString ISBN = "",Presscount = "";
		switch (CatalogSearchMode)
		{
		case 1://����
			if (edtcheckinfo->Text.Length() > 13 ) {
				ISBN =  edtcheckinfo->Text.SubString(1,13);
				Presscount = edtcheckinfo->Text.SubString(14,2);
			}
			else
			{
				ISBN =  edtcheckinfo->Text.Trim();
			}
			sql = sql + " and BS_BookCatalog.Unavailable=1 and (BS_BookCatalog.Barcode like '%" + ISBN  + "%' or BS_BookCatalog.ISBN like '%" + ISBN + "%') ";
			sql = sql + " and BS_BookCatalog.PressCount like '%" + Presscount + "%' ";
			break;
		case 2://�Ա���
			sql = sql + " and BS_BookCatalog.Unavailable=1 and BS_BookCatalog.UserDefCode like '%" + edtcheckinfo->Text.Trim() + "%'";
			break;
		case 3://����
			sql = sql + " and BS_BookCatalog.Unavailable=1 and BS_BookCatalog.Name like '%" + edtcheckinfo->Text.Trim() + "%'";
			break;
		case 4: //����
			sql = sql + " and BS_BookCatalog.Unavailable=1 and BS_BookCatalog.Price = " + edtcheckinfo->Text.Trim() ;
			break;
		case 5://����
			sql = sql + " and BS_BookCatalog.Unavailable=1 and BS_BookCatalog.Author like '%" + edtcheckinfo->Text.Trim() + "%'";
			break;
		default:
			break;
		}

		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		try {
			aquery->Open();
		} catch (...) {
			ShowMsg(this->Handle,"������������Ƿ���ȷ��",3);
			return;
		}

		if (aquery->RecordCount == 0 ) {
			ShowMsg(this->Handle,"û�и����¼��",3);
			return;
		}
		if (aquery->RecordCount > 1) {   //������¼
			Tfrmcatalogselect *frm  = new Tfrmcatalogselect(Application, checkli.con , aquery);
			if (mrOk==frm->ShowModal()) {
				TADOQuery * aq =  new TADOQuery(NULL);
				aq->Connection = fcon;
				sql = "select * from STK_StockInventories where states = 0 and STK_bookInfoID = " +  aquery->FieldByName("bkinfoid")->AsAnsiString ;
				aq->Close();
				aq->SQL->Clear();
				aq->SQL->Add(sql);
				aq->Open();
				if (aq->RecordCount > 0) {
					ShowMsg(this->Handle,"���������̵㣡",3);
					return;
				}
				sql = "insert into STK_stackAdjustNote(STK_bookInfoID,actualamount,NoteCode,bkcatalogid,supplierid,local) values(" + aquery->FieldByName("bkinfoid")->AsAnsiString + "," + aquery->FieldByName("Amount")->AsAnsiString + "," + edtnum->Text + "," + aquery->FieldByName("ID")->AsAnsiString + "," + aquery->FieldByName("SupplierID")->AsAnsiString + "," + aquery->FieldByName("BkstackID")->AsAnsiString + ")";
                aq->Close();
				aq->SQL->Clear();
				aq->SQL->Add(sql);
				aq->ExecSQL();
				delete aq;
				aqueryupdate->Active = false;
				aqueryupdate->Active = true;
				aqueryupdate->Last();
				cblocalin->SetFocus();
			}
		}
		if (aquery->RecordCount == 1) {    //ֻ��һ����¼
			TADOQuery * aq =  new TADOQuery(NULL);
			aq->Connection = fcon ;
			sql = "select ID from STK_StockInventories where states = 0 and STK_bookInfoID = " +  aquery->FieldByName("bkinfoid")->AsAnsiString ;
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();
			if (aq->RecordCount > 0) {
				ShowMsg(this->Handle,"���������̵㣡",3);
				return;
			}

			sql = "insert into STK_stackAdjustNote(STK_bookInfoID,actualamount,NoteCode,bkcatalogid,supplierid,local) values(" + aquery->FieldByName("bkinfoid")->AsAnsiString + "," + aquery->FieldByName("Amount")->AsAnsiString + "," + edtnum->Text + "," + aquery->FieldByName("ID")->AsAnsiString + "," + aquery->FieldByName("SupplierID")->AsAnsiString + "," + aquery->FieldByName("BkstackID")->AsAnsiString + ")";
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->ExecSQL();
			delete aq;
			aqueryupdate->Active = false;
			aqueryupdate->Active = true;
			aqueryupdate->Last();

			cblocalin->SetFocus();
		}
	}
}

//---------------------------------------------------------------------------

void __fastcall Tfrmadjust::N4Click(TObject *Sender)
{
	CatalogSearchMode = 2;
	lbsearch->Caption = "�Ա���";
}
//---------------------------------------------------------------------------

void __fastcall Tfrmadjust::N2Click(TObject *Sender)
{
	CatalogSearchMode = 3;
	lbsearch->Caption = "����";
}
//---------------------------------------------------------------------------

void __fastcall Tfrmadjust::N3Click(TObject *Sender)
{
	CatalogSearchMode= 5;
	lbsearch->Caption = "����";
}
//---------------------------------------------------------------------------

void __fastcall Tfrmadjust::ISBN1Click(TObject *Sender)
{
	CatalogSearchMode = 1 ;
	lbsearch->Caption = "���";
}
//---------------------------------------------------------------------------

void __fastcall Tfrmadjust::BtnNewClick(TObject *Sender)
{
	BtnNew->Enabled = false;
	BtnSave->Enabled = true;
	DBNavigator1->Enabled = false;
	AnsiString sql;
	Code = NoteCode::BuildCode(aquery,GetDBTime(aquery),m_storageID,"STK_stackAdjustHead","number");
	sql = "insert into STK_stackAdjustHead(number,adjustdate,employ)"
		 " values("+ Code +",'" + DateTimeToStr(dtpdate->DateTime )+"','"
		  + checkli.userID + "')";
	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->ExecSQL();

	membk->Text = "";
	edstate->Text = "δȷ�ϵ���";
	dtpdate->Date = Date();
	edtnum->Text = Code;

	aqueryupdate->Parameters->ParamByName("code")->Value = edtnum->Text;
	aqueryupdate->Active = false;
	aqueryupdate->Active = true;
	aqheader->Active = false;
	aqheader->Active = true;

	DisableInput(1);
}
//---------------------------------------------------------------------------

void __fastcall Tfrmadjust::BtnSaveClick(TObject *Sender)
{
	if (edtnum->Text == "") {
		return;
	}
	BtnSave->Enabled = false;

	AnsiString sql;

	//������
	sql = "update STK_stackAdjustHead set adjustdate = '" + DateTimeToStr(dtpdate->DateTime )
			+ "',bk = '" + membk->Text  + "' where Number = " + edtnum->Text ;

	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->ExecSQL();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmadjust::FormCreate(TObject *Sender)
{
	readyData(aquery);
	BtnNew->Click();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmadjust::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmadjust::edtnumberKeyPress(TObject *Sender, wchar_t &Key)
{
	int actualamount;
	if (Key == '\r')
	{
		if (edtnumber->Text == "") {

                      ShowMsg(Handle ,"���������������",3);
			return;
		}
		if (StrToInt(edtnumber->Text)<0) {

                        ShowMsg(Handle ,"�������븺ֵ��",3);
			edtnumber->Text = "";
			edtnumber->SetFocus();
			return;
		}
		actualamount = aqueryupdate->FieldByName("actualamount")->AsInteger;
		if (actualamount-StrToInt(edtnumber->Text) < 0) {

                        ShowMsg(Handle ,"�����������뵱ǰ�������",3);
			edtnumber->Text = "";
			edtnumber->SetFocus();
			return;
		}

		aqueryupdate->Edit();
		aqueryupdate->FieldByName("amount")->AsInteger  = StrToInt(edtnumber->Text);
		aqueryupdate->UpdateBatch(arAll);

		aqueryupdate->Active = false;
		aqueryupdate->Active = true;
		aqueryupdate->Last();

		edtcheckinfo->Text = "";
		edtnumber->Text = "";
    	edtcheckinfo->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmadjust::lbsearchMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	if (Button == mbLeft ) {
		TPoint  pt;
		GetCursorPos(&pt);
		pm->Popup(pt.x,pt.y);
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmadjust::BtnDeleteClick(TObject *Sender)
{
	if (aqueryupdate->IsEmpty() || aqueryupdate->RecordCount == 0 ) {
		return;
	}
	if (edstate->Text == "��ȷ�ϵ���") {

                ShowMsg(Handle ,"��ȷ�ϵ���������ɾ����",3);
		return;
	}
	if (ShowMsg(Handle ,"ȷ��Ҫɾ����",1)== 1){
		TADOQuery * aq =  new TADOQuery(NULL);
		AnsiString sql;
		aq->Connection = fcon;
		sql = "delete from STK_stackAdjustNote where id = " + aqueryupdate->FieldByName("id")->AsAnsiString ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->ExecSQL();
		delete aq;
		aqueryupdate->Active = false;
		aqueryupdate->Active = true;
	}
}

//---------------------------------------------------------------------------
void Tfrmadjust::DisableInput(int Modal)
{
	if (Modal == 0) {
		membk->Enabled = false;
		edtcheckinfo->Enabled = false;
		edtnumber->Enabled = false;
		cblocalin->Enabled = false;
		BtnDelete->Enabled = false;
		BtnOK->Enabled = false;
	}  else if (Modal == 1) {
		membk->Enabled = true;
		edtcheckinfo->Enabled = true;
		edtnumber->Enabled = true;
		cblocalin->Enabled = true;
		BtnDelete->Enabled = true;
		BtnOK->Enabled = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmadjust::FormClose(TObject *Sender, TCloseAction &Action)
{
  	Action = caFree ;
}
//---------------------------------------------------------------------------


void __fastcall Tfrmadjust::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F1 && BtnView->Enabled && BtnView->Visible ) {     //�鵥
		BtnView->Click();
	}
	if (Key == VK_F2 && BtnNew->Enabled && BtnNew->Visible) {     //��
		BtnNew->Click();
	}
	if (Key == VK_F3 && BtnSave->Enabled && BtnSave->Visible) {     //����
		BtnSave->Click();
	}
	if (Key == VK_F5 && BtnDelete->Enabled && BtnDelete->Visible) {     //ɾ��
		BtnDelete->Click();
	}
	if (Key == VK_F7 && BtnOK->Enabled && BtnOK->Visible) {     //ȷ��
		BtnOK->Click();
	}
	/*if (Key == VK_F8) {     //����
		BtnDelete->Click();
	}
	if (Key == VK_F10) {     //��ӡ
		BtnDelete->Click();
	} */
	if (Shift.Contains(ssCtrl)&& Key == 78 ) {    //��С��
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 81 ) {    //�˳�
		BtnExit->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==90) {   //�ָ�����
		WindowState = wsNormal  ;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmadjust::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmadjust::BtnOKClick(TObject *Sender)
{
	if (aqueryupdate->IsEmpty() || aqueryupdate->RecordCount == 0 ) {
        return;
	}

	AnsiString sql;

	sql = "select ID from STK_stackAdjustNote where (inputlocal is null or Amount is null) and NoteCode = " + edtnum->Text ;
    aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Open();
	if (aquery->RecordCount > 0) {

             ShowMsg(Handle ,"�е����λ������û¼�룬����¼����ڽ��е���!",3);
		return;
	}

	//���µ�������

	sql = "exec updateadjust " + edtnum->Text.Trim();
    aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->ExecSQL();

	//���µ�����״̬
	sql = "update STK_stackAdjustHead set state = 1 where Number = " + edtnum->Text ;

	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->ExecSQL();


        ShowMsg(Handle ,"��λ�����ɹ���",3);
	BtnOK->Enabled = false;
	edstate->Text = "��ȷ�ϵ���";
	DisableInput(0);
}
//---------------------------------------------------------------------------

void __fastcall Tfrmadjust::DBNavigator1Click(TObject *Sender, TNavigateBtn Button)

{
    DelNtHeader();
	if (aqheader->FieldByName("state")->AsInteger == 1 ) {
		edstate->Text = "��ȷ�ϵ���";
		DisableInput(0);
	}
	else
	{
		edstate->Text = "δȷ�ϵ���";
		DisableInput(1);
	}
	edtnum->Text = aqheader->FieldByName("number")->AsAnsiString ;
	dtpdate->Date = aqheader->FieldByName("adjustDate")->AsDateTime ;

	aqueryupdate->Parameters->ParamByName("code")->Value = edtnum->Text;
	aqueryupdate->Active = false;
	aqueryupdate->Active = true;
	BtnNew->Enabled = true;
}
//---------------------------------------------------------------------------

void Tfrmadjust::DelNtHeader()
{
	if (aqueryupdate->IsEmpty() && edtnum->Text != "" ) {
		AnsiString sql;
		sql = "delete from  STK_stackAdjustHead where Number = " + edtnum->Text + " and Number not in(select NoteCode from STK_stackAdjustNote)";

		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->ExecSQL();
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmadjust::BtnViewClick(TObject *Sender)
{
	TfrmQryNoteCode *frm = new TfrmQryNoteCode(Application,0);
	frm->SetstgID(m_storageID);

	if (frm->ShowModal() == mrOk) {
		DBNavigator1->Enabled = true;
		DelNtHeader();

		AnsiString Code = frm->GetNoteCode();
		delete frm;

		AnsiString sql;
		sql = "select * from STK_stackAdjustHead where Number = " + Code;
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->Open();
		if (aquery->RecordCount==0 ) {
			return;
		}

		TLocateOptions Opts;
		Opts.Clear();
		Opts << loPartialKey;
		aqheader->Locate("id", aquery->FieldByName("id")->AsAnsiString, Opts);

		if (aquery->FieldByName("state")->AsInteger == 1 ) {
			edstate->Text = "��ȷ�Ͽ��";
			DisableInput(0);
		}
		else
		{
			edstate->Text = "δȷ�Ͽ��";
			DisableInput(1);
		}
		edtnum->Text = aquery->FieldByName("number")->AsAnsiString ;
		dtpdate->Date = aquery->FieldByName("adjustDate")->AsDateTime ;

		aqueryupdate->Parameters->ParamByName("code")->Value = edtnum->Text;
		aqueryupdate->Active = false;
		aqueryupdate->Active = true;
		BtnNew->Enabled = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmadjust::N1Click(TObject *Sender)
{
	CatalogSearchMode= 4;
	lbsearch->Caption = "����";
}
//---------------------------------------------------------------------------

void Tfrmadjust::ChangeCatalogSearchMode()
{
	CatalogSearchMode++;
	if (CatalogSearchMode >= 6)
	{
		CatalogSearchMode = 1;
	}

	switch (CatalogSearchMode)
	{
	case 1:
		edtcheckinfo->MaxLength = 15;
        lbsearch->Caption = "���";
		lbsearch->Tag = 1;
		break;
	case 2:
		edtcheckinfo->MaxLength = 0;
		lbsearch->Caption = "�Ա���";
		break;
	case 3:
		edtcheckinfo->MaxLength = 0;
		lbsearch->Caption = "����";
		break;
	case 4:
		edtcheckinfo->MaxLength = 0;
		lbsearch->Caption = "����";
		break;
	case 5:
		edtcheckinfo->MaxLength = 0;
		lbsearch->Caption = "����";
		break;
	default:
		break;
	}
}
//---------------------------------------------------------------------------

void  Tfrmadjust::Refrsh()
{
	TLocateOptions Opts;
	Opts.Clear();
	Opts  <<  loPartialKey;
	AnsiString str = aqueryupdate->FieldByName("id")->AsAnsiString;
	aqueryupdate->Active = false;
	aqueryupdate->Active = true;

	aqueryupdate->Locate("id",str,Opts);
}
//---------------------------------------------------------------------------

void __fastcall Tfrmadjust::cblocalinKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        if (aqueryupdate->IsEmpty() && aqueryupdate->RecordCount == 0) {
			return;
		}
		int inlocal;
		try {
			inlocal = (int)cblocalin->Items->Objects[cblocalin->ItemIndex];
		} catch (...) {

                        ShowMsg(Handle ,"��ѡ����ȷ�Ŀ�λ��",3);
			return;
		}
		if (inlocal == aqueryupdate->FieldByName("local")->AsInteger ) {

                        ShowMsg(Handle ,"ͬ��λ���ܵ�����",3);
			return;
		}

		AnsiString sql;
		sql = "update STK_stackAdjustNote set inputlocal = " + IntToStr(inlocal) + " where id = " + aqueryupdate->FieldByName("id")->AsAnsiString ;
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->ExecSQL();

		Refrsh();
		edtnumber->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmadjust::cblocalinExit(TObject *Sender)
{
	if (aqueryupdate->IsEmpty() && aqueryupdate->RecordCount == 0) {
		return;
	}
	int inlocal;
	try {
		inlocal = (int)cblocalin->Items->Objects[cblocalin->ItemIndex];
	} catch (...) {

                ShowMsg(Handle ,"��ѡ����ȷ�Ŀ�λ��",3);
		return;
	}
	if (inlocal == aqueryupdate->FieldByName("local")->AsInteger ) {

                 ShowMsg(Handle ,"ͬ��λ���ܵ�����",3);
		return;
	}

	AnsiString sql;
	sql = "update STK_stackAdjustNote set inputlocal = " + IntToStr(inlocal) + " where id = " + aqueryupdate->FieldByName("id")->AsAnsiString ;
	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->ExecSQL();

	Refrsh();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmadjust::dgbookCellClick(TColumn *Column)
{
	if (aqueryupdate->IsEmpty() && aqueryupdate->RecordCount == 0) {
		return;
	}
	cblocalin->ItemIndex = cblocalin->Items->IndexOfObject((TObject*)aqueryupdate->FieldByName("inputlocal")->AsInteger);
	edtnumber->Text =  aqueryupdate->FieldByName("Amount")->AsAnsiString ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmadjust::BtnPreviewNextPageClick(TObject *Sender)
{
	if (aqueryupdate->IsEmpty() ) {
		return;
	}
	DbgridToExcel(dgbook);
}
//---------------------------------------------------------------------------

bool Tfrmadjust::DbgridToExcel(TRzDBGrid* dbg)
{
   	AnsiString temptext,path;
	int k = dbg->DataSource ->DataSet ->RecordCount ,n=0;

	savedlg->FileName = "��λ����" + edtnum->Text ;
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

	int t2 = dbg->DataSource ->DataSet ->RecordCount ;
	aqueryupdate->DisableControls();
	dbg->DataSource ->DataSet ->First();
	for(int i=2+n;i<=t2+1+n ;i++)
	{
		t1=0;
		temptext = "\n";
		for(int j=1;j<=dbg->Columns ->Count  ;j++)
		{
			if (dbg->Columns->Items[j-1]->Visible == true) {
				if (dbg->Columns ->Items [j-1]->FieldName == "ISBN") {
					t1++;
					temptext = temptext + "'" + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
				}
				else if (dbg->Columns ->Items [j-1]->FieldName == "Name") {
					t1++;
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
	aqueryupdate->EnableControls();

	FileClose(iFileHandle);


        ShowMsg(Handle ,"������ϣ�",3);
	return false;
}
//---------------------------------------------------------------------------

