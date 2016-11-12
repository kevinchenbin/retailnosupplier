//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "bookQuery.h"
#include "Selecttype.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma resource "*.dfm"
Tfrmbookquery *frmbookquery;
//---------------------------------------------------------------------------
__fastcall Tfrmbookquery::Tfrmbookquery(TComponent* Owner,TADOConnection *cn,int stgid)
	: TForm(Owner)
{
	aq->Connection = cn;
	query->Connection = cn;
	fcon = cn;
	m_storageID = stgid;
	AnsiString sql;

	sql = "select ID,AbbreviatedName from BS_PressInfo";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	while (!query->Eof )
	{
		cbpress->AddItem(query->FieldByName("AbbreviatedName")->AsAnsiString ,(TObject*)query->FieldByName("ID")->AsInteger );
		query->Next();
	}

}
//---------------------------------------------------------------------------

void __fastcall Tfrmbookquery::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbookquery::SpeedButton1Click(TObject *Sender)
{
	float price;
	if (chprice->Checked && edprice != "") {
		try {
			price = StrToFloat(edprice->Text.Trim());
		} catch (...) {

                        ShowMsg(Handle ,"请输入正确的定价！",3);
			return;
		}
	}
	
	String sql;
	sql = "select BS_BookCatalog.ID,STK_BookInfo.SupplierID,BS_BookCatalog.Name,BS_BookCatalog.Barcode,BS_BookCatalog.Author,BS_BookType.Name as typename,"
			"BS_BookCatalog.UserDefCode,BS_BookCatalog.ISBN,CUST_CustomerInfo.Name as SupplierName,STK_BookInfo.ID as STK_BookinfoID,"
			"STK_BookInfo.Amount,STK_BookstackInfo.Name as BkstackName,BS_BookCatalog.Price ,BS_PressInfo.AbbreviatedName ,STK_BookstackInfo.name LocalName,SYS_StorageInfo.Name as storagename "
			"from STK_BookInfo  join BS_BookCatalog on STK_BookInfo.BkcatalogID=BS_BookCatalog.ID "
			"left join CUST_CustomerInfo on STK_BookInfo.SupplierID=CUST_CustomerInfo.ID "
			"left join STK_BookstackInfo on STK_BookInfo.BkstackID=STK_BookstackInfo.ID "
			"left join SYS_StorageInfo on STK_BookstackInfo.StgID = SYS_StorageInfo.id "
			"left join BS_BookType on BS_BookCatalog.smallBookTypeID = BS_BookType.id "
			"left join BS_PressInfo ON BS_BookCatalog.PressID = BS_PressInfo.ID " ;
	if (chother->Checked ) {
		sql = sql + "where BS_BookCatalog.Unavailable=1 and STK_BookstackInfo.StgID in(select mstgid from BS_StoToSto where ystgid = " + IntToStr(m_storageID) + " and stkbook = 1 union select " + IntToStr(m_storageID) + ") ";
	}
	else
	{
		sql = sql + "where BS_BookCatalog.Unavailable=1 and STK_BookstackInfo.StgID=" + IntToStr(m_storageID);
	}
	if (chisbn->Checked && edisbn->Text != "") {
             if (edisbn->Text.Trim().Length()>13) {   //期刊
                sql = sql + " and (BS_BookCatalog.Barcode like '%" + edisbn->Text.Trim().SubString(0,13)  + "%' or BS_BookCatalog.ISBN like '%" + edisbn->Text.Trim().SubString(0,13) + "%') ";
                sql = sql + " and BS_BookCatalog.presscount="+edisbn->Text.Trim().SubString(14,edisbn->Text.Trim().Length()-13);
             }else
             {
		sql = sql + " and (BS_BookCatalog.Barcode like '%" + edisbn->Text.Trim()  + "%' or BS_BookCatalog.ISBN like '%" + edisbn->Text.Trim() + "%') ";
             }
	}
	if (chname->Checked && edname->Text != "") {
		sql = sql + " and BS_BookCatalog.Name like '%" + edname->Text.Trim()  + "%'";
	}
	if (chuserdefcode->Checked && eduserdefcode->Text != "") {
		sql = sql + " and BS_BookCatalog.UserDefCode like '%" + eduserdefcode->Text.Trim()  + "%'";
	}
	if (chprice->Checked && edprice->Text != "") {
		sql = sql + " and BS_BookCatalog.Price =" + edprice->Text.Trim();
	}
	if (chauthor->Checked && edauthor->Text != "") {
		sql = sql + " and BS_BookCatalog.Author like '%" + edauthor->Text.Trim() + "%'";
	}
	if (chpress->Checked && cbpress->Text != "") {
		sql = sql + " and BS_PressInfo.AbbreviatedName = '" + cbpress->Text.Trim() + "'";
	}
	if (chtype->Checked && edtyname->Text != "") {
		sql = sql + " and BS_BookType.id in(select id from dbo.GetTypeChild(" + IntToStr(TypeID) + "))";
	}
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbookquery::edpriceKeyPress(TObject *Sender, wchar_t &Key)
{
	if ((Key < '0' || Key > '9') && (Key != '\b') && (Key != '.') && (Key != '\r') ) {
    	 Key = NULL;
	}
	if (Key == '\r') {
        edauthor->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbookquery::edtypeKeyPress(TObject *Sender, wchar_t &Key)
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

void __fastcall Tfrmbookquery::edpressKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		if (edpress->Text == "") {
			return;
		}
		AnsiString sql;
		sql = "select ID,AbbreviatedName from BS_PressInfo where AbbreviatedName like '%" + edpress->Text.Trim() + "%'" ;
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->Open();
		cbpress->Items->Clear();
		while (!query->Eof )
		{
			cbpress->AddItem(query->FieldByName("AbbreviatedName")->AsAnsiString ,(TObject*)query->FieldByName("ID")->AsInteger );
			query->Next();
		}
		query->First();
		cbpress->ItemIndex = cbpress->Items->IndexOfObject((TObject*)query->FieldByName("ID")->AsInteger );
		cbpress->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbookquery::edisbnChange(TObject *Sender)
{
	if (edisbn->Text != "") {
		chisbn->Checked = true;
	}
	else
	{
    	chisbn->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbookquery::edisbnKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        edname->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbookquery::ednameKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        eduserdefcode->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbookquery::ednameChange(TObject *Sender)
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

void __fastcall Tfrmbookquery::eduserdefcodeChange(TObject *Sender)
{
	if (eduserdefcode->Text != "") {
		chuserdefcode->Checked = true;
	}
	else
	{
    	chuserdefcode->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbookquery::eduserdefcodeKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        edprice->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbookquery::edpriceChange(TObject *Sender)
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

void __fastcall Tfrmbookquery::edauthorChange(TObject *Sender)
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

void __fastcall Tfrmbookquery::edauthorKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        edtype->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbookquery::cbpressChange(TObject *Sender)
{
	if (cbpress->Text != "") {
		chpress->Checked = true;
	}
	else
	{
    	chpress->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbookquery::cbpressKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        SpeedButton1->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbookquery::SpeedButton2Click(TObject *Sender)
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

void __fastcall Tfrmbookquery::edtynameChange(TObject *Sender)
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

