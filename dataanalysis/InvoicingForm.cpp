//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "InvoicingForm.h"
#include "Selecttype.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "MDIChild"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzButton"
#pragma link "RzDBGrid"
#pragma link "RzPanel"
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma resource "*.dfm"
TfrmInvoicing *frmInvoicing;
//---------------------------------------------------------------------------
__fastcall TfrmInvoicing::TfrmInvoicing(TComponent* Owner)
	: TfrmMDIChild(Owner)
{             m_module = MTData;
	dtp1->Date=dtp1->Date .CurrentDate();
	dtp2->Date=dtp2->Date .CurrentDate();
	this->WindowState = wsMaximized ;
}
//---------------------------------------------------------------------------

void TfrmInvoicing::Init(TApplication* app, TADOConnection* con)
{
	TfrmMDIChild::Init(app, con);
	dsquery->Connection=con;
	storcquery->Connection = con;
	fcon = con;
	TADOQuery * aq;
	String sql;
	aq = new TADOQuery(this);
	aq->Connection = con;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add("select * from sys_bsset where name ='xiaoshudian'");
	aq->Open();
	storageformat =  "￥###,###,##" + aq->FieldByName("bk")->AsAnsiString ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add("select * from sys_bsset where name ='retailxiaoshudian'");
	aq->Open();
	retaiformat =  "￥###,###,##" + aq->FieldByName("bk")->AsAnsiString ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add("select * from sys_bsset where name ='salexiaoshudian'");
	aq->Open();
	saleformat =  "￥###,###,##" + aq->FieldByName("bk")->AsAnsiString ;
	sql = "select ID,Name from CUST_CustomerInfo where Type = 1 order by name";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof )
	{
		cbsupplier->AddItem(aq->FieldByName("Name")->AsString ,(TObject*)aq->FieldByName("ID")->AsInteger );
		aq->Next();
	}
	sql = "select ID,PresentNum,AbbreviatedName from BS_PressInfo";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof )
	{
		cbpress->AddItem(aq->FieldByName("AbbreviatedName")->AsString ,(TObject*)aq->FieldByName("ID")->AsInteger );
		aq->Next();
	}

	sql = "select ID,Name from SYS_StorageInfo ";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof )
	{
		cbstorage->AddItem(aq->FieldByName("Name")->AsString ,(TObject*)aq->FieldByName("ID")->AsInteger );
		aq->Next();
	}
	cbstorage->ItemIndex = cbstorage->Items->IndexOfObject((TObject*)stgid);
	sql = "select Master from SYS_StorageInfo where id = " + IntToStr(stgid);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	if (aq->FieldByName("Master")->AsBoolean ) {
		chstorage->Enabled = true;
		cbstorage->Enabled = true;
	}
	else
	{
		chstorage->Enabled = false;
		cbstorage->Enabled = false;
	}

	delete aq;
	DBGridEh1->Columns->Items[4]->DisplayFormat = storageformat;
	DBGridEh1->Columns->Items[7]->DisplayFormat = storageformat;
	DBGridEh1->Columns->Items[8]->DisplayFormat = storageformat;

	DBGridEh1->Columns->Items[10]->DisplayFormat = retaiformat;
	DBGridEh1->Columns->Items[11]->DisplayFormat = retaiformat;
	DBGridEh1->Columns->Items[13]->DisplayFormat = retaiformat;
	DBGridEh1->Columns->Items[14]->DisplayFormat = retaiformat;

	DBGridEh1->Columns->Items[15]->DisplayFormat = saleformat;
	DBGridEh1->Columns->Items[16]->DisplayFormat = saleformat;
	DBGridEh1->Columns->Items[18]->DisplayFormat = saleformat;
	DBGridEh1->Columns->Items[19]->DisplayFormat = saleformat;

	DBGridEh1->Columns->Items[7]->Footer->DisplayFormat = storageformat;
	DBGridEh1->Columns->Items[8]->Footer->DisplayFormat = storageformat;

	DBGridEh1->Columns->Items[10]->Footer->DisplayFormat = retaiformat;
	DBGridEh1->Columns->Items[11]->Footer->DisplayFormat = retaiformat;
	DBGridEh1->Columns->Items[13]->Footer->DisplayFormat = retaiformat;
	DBGridEh1->Columns->Items[14]->Footer->DisplayFormat = retaiformat;

	DBGridEh1->Columns->Items[15]->Footer->DisplayFormat = saleformat;
	DBGridEh1->Columns->Items[16]->Footer->DisplayFormat = saleformat;
	DBGridEh1->Columns->Items[18]->Footer->DisplayFormat = saleformat;
	DBGridEh1->Columns->Items[19]->Footer->DisplayFormat = saleformat;
}
//---------------------------------------------------------------------------
void __fastcall TfrmInvoicing::RzToolButton1Click(TObject *Sender)
{
	storcquery->Close();
	AnsiString sql;
	sql = "exec USP_BS_Qry_DataInvoicing ";

	//起始时间
	if (cbstart->Checked) {
		sql = sql + "'" + DateToStr(dtp1->Date).Trim() + "'";
	}
	else
	{
		sql = sql + "'1901-01-01'";
	}
    //结束时间
	if (cbend->Checked ) {
		sql = sql + ",'" + DateToStr(dtp2->Date).Trim() + "'";
	}
	else
	{
		sql = sql + ",'4000-01-01'";
	}
	if (chk1->Checked==true && edisbn->Text!="") {   //书号
		sql = sql + ",'%" + edisbn->Text.Trim() + "%'" ;
	}
	else
	{
		sql = sql + ",''" ;
	}
	if (chk6->Checked==true && edname->Text!="") {  //书名
		sql = sql + ",'%" + edname->Text.Trim() + "%'" ;
	}
	else
	{
		sql = sql + ",''" ;
	}
	if (chprice->Checked && edprice->Text != "") {    //定价
		try {
			StrToFloat(edprice->Text);
		} catch (...) {
             ShowMsg(Handle ,"请输入正确的定价！",3);
			return;
		}
		sql = sql + "," + edprice->Text ;
	}
	else
	{
    	sql = sql + ",null";
	}

	if (chauthor->Checked && edauthor->Text != "") {  //作者
		sql = sql + ",'%" + edname->Text.Trim() + "'";
	}
	else
	{
		sql = sql + ",''";
	}
	if (chk4->Checked==true&&cbsupplier->Text!="") {   //供应商
		sql = sql + ",'%" + cbsupplier->Text.Trim() + "%'";
	}
	else
	{
		sql = sql + ",''";
	}

	if (chk5->Checked==true&&cbpress->Text!="") {  //出版社
		sql = sql + ",'" +  cbpress->Text.Trim() + "'";
	}
	else
	{
		sql = sql + ",''";
	}
	if (chtype->Checked==true&&edtyname->Text!="") { //类别
		sql = sql + "," + IntToStr(TypeID)  ;
	}
	else
	{
		sql = sql + ",-1";
	}

	if (chstorage->Checked) {
		int fstgid;
		try {
			fstgid = (int)cbstorage->Items->Objects[cbstorage->ItemIndex];
		} catch (...) {

                        ShowMsg(Handle ,"请选择正确的店号！",3);
			return;
		}
		sql = sql + "," + IntToStr(fstgid);
	}
	else
	{
    	sql = sql + ",-1";
	}
	dsquery->Active = false;
	dsquery->CommandText = sql;
	dsquery->Active = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmInvoicing::cbbTypeSelect(TObject *Sender)
{
	edisbn->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TfrmInvoicing::FormClose(TObject *Sender, TCloseAction &Action)
{
 	dsquery->Active=false;
	Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TfrmInvoicing::RzToolButton3Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmInvoicing::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Shift.Contains(ssCtrl)&& Key == 70 ) {    //查询
		RzToolButton1->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 78 ) {    //最小化
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 81 ) {    //退出
		RzToolButton3->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==90) {   //恢复窗口
		WindowState = wsNormal  ;
	}
	if (Key == VK_F4) {   //恢复窗口
		BtnExport->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmInvoicing::DBGridEh1TitleClick(TColumnEh *Column)
{
	if (dsquery->IsEmpty() ) {
    	return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (dsquery->Sort == "") {
		dsquery->Sort =  Column->FieldName + " ASC";
	}
	else if (dsquery->Sort == qusort) {
		dsquery->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		dsquery->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmInvoicing::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmInvoicing::ch1Click(TObject *Sender)
{
	if (ch1->Checked ) {
		DBGridEh1->Columns->Items[7]->Visible = true;
		DBGridEh1->Columns->Items[8]->Visible = true;
		DBGridEh1->Columns->Items[9]->Visible = true;
	}
	else
	{
		DBGridEh1->Columns->Items[7]->Visible = false;
		DBGridEh1->Columns->Items[8]->Visible = false;
		DBGridEh1->Columns->Items[9]->Visible = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmInvoicing::ch2Click(TObject *Sender)
{
	if (ch2->Checked ) {
		DBGridEh1->Columns->Items[14]->Visible = true;
		DBGridEh1->Columns->Items[10]->Visible = true;
		DBGridEh1->Columns->Items[11]->Visible = true;
		DBGridEh1->Columns->Items[12]->Visible = true;
		DBGridEh1->Columns->Items[13]->Visible = true;
	}
	else
	{
		DBGridEh1->Columns->Items[14]->Visible = false;
		DBGridEh1->Columns->Items[10]->Visible = false;
		DBGridEh1->Columns->Items[11]->Visible = false;
		DBGridEh1->Columns->Items[12]->Visible = false;
		DBGridEh1->Columns->Items[13]->Visible = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmInvoicing::ch3Click(TObject *Sender)
{
	if (ch3->Checked ) {
		DBGridEh1->Columns->Items[19]->Visible = true;
		DBGridEh1->Columns->Items[15]->Visible = true;
		DBGridEh1->Columns->Items[16]->Visible = true;
		DBGridEh1->Columns->Items[17]->Visible = true;
		DBGridEh1->Columns->Items[18]->Visible = true;
	}
	else
	{
		DBGridEh1->Columns->Items[19]->Visible = false;
		DBGridEh1->Columns->Items[15]->Visible = false;
		DBGridEh1->Columns->Items[16]->Visible = false;
		DBGridEh1->Columns->Items[17]->Visible = false;
		DBGridEh1->Columns->Items[18]->Visible = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmInvoicing::BtnExportClick(TObject *Sender)
{
	if (dsquery->IsEmpty() ) {
		return;
	}
	DbgridToExcel(DBGridEh1);
}
//---------------------------------------------------------------------------
//Excel导出函数
bool TfrmInvoicing::DbgridToExcel(TDBGridEh* dbg)
{
	if (dbg->DataSource ->DataSet->IsEmpty() ) {
        return false;
	}
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
	int  iFileLength;
	if(FileExists(path))
	   if (DeleteFileA(path))
			iFileHandle = FileCreate(path.c_str());
	   else
			return false;
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
				else if (dbg->Columns ->Items [j-1]->FieldName == "BookName") {
					AnsiString bookname;
					int len;
					bookname = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					bookname = StringReplace(bookname , ",",".",TReplaceFlags()<<rfReplaceAll);
					temptext = temptext + bookname + ",";
				}
				else
				{
					temptext = temptext + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
				}
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
			temptext = temptext + dbg->GetFooterValue(0,dbg->Columns ->Items[q]) +",";//dbg->Columns ->Items[q]->Footer->Value + ",";
		}
	}
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	FileClose(iFileHandle);


        ShowMsg(Handle ,"导出完毕！",3);
	return false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmInvoicing::edsupplierKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		if (edsupplier->Text == "") {
            return;
		}
		TADOQuery * aq = new TADOQuery(this);
		String sql;
		aq->Connection =fcon;

		sql = "select ID,Name from CUST_CustomerInfo where Type = 1 and Name like '%" + edsupplier->Text.Trim() + "%'";
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		cbsupplier->Items->Clear();
		while (!aq->Eof )
		{
			cbsupplier->AddItem(aq->FieldByName("Name")->AsString ,(TObject*)aq->FieldByName("ID")->AsInteger );
			aq->Next();
		}
		aq->First();
		cbsupplier->ItemIndex = cbsupplier->Items->IndexOfObject((TObject*)aq->FieldByName("ID")->AsInteger );
		delete aq;
		cbsupplier->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmInvoicing::edtypeKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		Tfrmselecttype * frm = new Tfrmselecttype(Application,fcon,edtype->Text);
		if (mrOk == frm->ShowModal())
		{
			TypeID = frm->GetSelectID();
			edtyname->Text = frm->GetSelect();
		}
		delete frm;
		edpress->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmInvoicing::edpressKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		if (edpress->Text == "") {
            return;
		}
		TADOQuery * aq = new TADOQuery(this);
		String sql;
		aq->Connection =fcon;

		sql = "select ID,PresentNum,AbbreviatedName from BS_PressInfo where AbbreviatedName like '%" + edpress->Text.Trim() + "%'" ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		while (!aq->Eof )
		{
			cbpress->AddItem(aq->FieldByName("AbbreviatedName")->AsString ,(TObject*)aq->FieldByName("ID")->AsInteger );
			aq->Next();
		}
        aq->First();
		cbpress->ItemIndex = cbpress->Items->IndexOfObject((TObject*)aq->FieldByName("ID")->AsInteger );
		delete aq;
		cbpress->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmInvoicing::dtp1Change(TObject *Sender)
{
	cbstart->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmInvoicing::dtp1KeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        dtp2->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmInvoicing::dtp2Change(TObject *Sender)
{
	cbend->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmInvoicing::RzEdit5KeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        edsupplier->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmInvoicing::cbsupplierChange(TObject *Sender)
{
	if (cbsupplier->Text != "") {
		chk4->Checked = true;
	}
	else
	{
    	chk4->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmInvoicing::cbsupplierKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        edtype->SetFocus();
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmInvoicing::cbpressChange(TObject *Sender)
{
	if (cbpress->Text != "") {
		chk5->Checked = true;
	}
	else
	{
    	chk5->Checked =- false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmInvoicing::cbpressKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        RzToolButton1->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmInvoicing::edisbnChange(TObject *Sender)
{
	if (edisbn->Text != "") {
		chk1->Checked = true;
	}
	else
	{
    	chk1->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmInvoicing::ednameChange(TObject *Sender)
{
	if (edname->Text != "") {
		chk6->Checked = true;
	}
	else
	{
		chk6->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmInvoicing::edpriceChange(TObject *Sender)
{
	if (edprice->Text != "") {
		chprice->Checked = true;
	}
	else
	{
		chprice->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmInvoicing::edauthorChange(TObject *Sender)
{
	if (edauthor->Text != "") {
		chauthor->Checked = true;
	}
	else
	{
		chauthor->Checked = false;
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmInvoicing::SpeedButton1Click(TObject *Sender)
{
	Tfrmselecttype * frm = new Tfrmselecttype(Application,fcon,"");
	if (mrOk == frm->ShowModal())
	{
		TypeID = frm->GetSelectID();
		edtyname->Text = frm->GetSelect();
	}
	delete frm;
}
//---------------------------------------------------------------------------

void __fastcall TfrmInvoicing::edtynameChange(TObject *Sender)
{
	if (edtyname->Text != "") {
		chtype->Checked = true;
	}
	else
	{
    	chtype->Checked = false;
	}
}
//---------------------------------------------------------------------------

