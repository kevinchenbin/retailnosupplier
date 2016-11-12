//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "global.h"
#include "ClientDisforbook.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzDBGrid"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzPanel"
#pragma resource "*.dfm"
Tfrmclientdisforbook *frmclientdisforbook;
//---------------------------------------------------------------------------
__fastcall Tfrmclientdisforbook::Tfrmclientdisforbook(TComponent* Owner)
	: TForm(Owner)
{

}
void Tfrmclientdisforbook::init(TADOConnection *con, int stgida)
{
      fcon=con;
      AnsiString sql ;
      	query->Connection = con;
	aq->Connection = con;
	querydetail->Connection = con;
        stgid = stgida;
      sql = "select ID,Name from CUST_CustomerInfo where Type in(2,3) and name <> ''  and customerstate=1 and stgid="+IntToStr(stgid)+" order by name";
      aqcustom->Connection = fcon;

      TADOQuery *aq = new TADOQuery(NULL);
      aq->Connection = fcon;
      aq->Close();
      aq->SQL->Clear();
      aq->SQL->Add(sql);
      aq->Open();
        aq->First();
        while (!aq->Eof ) {
                cbCusName->AddItem(aq->FieldByName("Name")->AsString ,(TObject*)aq->FieldByName("ID")->AsInteger);
                aq->Next();
        }
        sql = "select id,name from dbo.SYS_StorageInfo";
        aq->Close();
        aq->SQL->Clear();
        aq->SQL->Add(sql);
        aq->Open();
        aq->First();
        while (!aq->Eof ) {
            cbstorage->AddItem(aq->FieldByName("Name")->AsString ,(TObject*)aq->FieldByName("ID")->AsInteger);
            aq->Next();
        }
      cbstorage->ItemIndex = cbstorage->Items->IndexOfObject((TObject*)stgid);

	sql = "select Master from SYS_StorageInfo where id = " + IntToStr(stgid);
    query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	if (query->FieldByName("Master")->AsBoolean ) {
		cbstorage->Enabled = true;
	}
	else
	{
    	cbstorage->Enabled = false;
	}

        	//打折方案初始显示
	sql = "select BS_ClientBookDiscount.*,CUST_CustomerInfo.name as clientname,BS_BookCatalog.Name,BS_BookCatalog.ISBN,BS_BookCatalog.Price,BS_PressInfo.AbbreviatedName,BS_BookCatalog.Price*BS_ClientBookDiscount.Discount/100 as dprice "
		  "from BS_ClientBookDiscount left join BS_BookCatalog on BS_ClientBookDiscount.BookCatalogID = BS_BookCatalog.ID left join CUST_CustomerInfo on CUST_CustomerInfo.id = BS_ClientBookDiscount.client "
		  "left join BS_PressInfo on BS_BookCatalog.PressID = BS_PressInfo.id left join STK_BookInfo on BS_ClientBookDiscount.BookInfoID = STK_BookInfo.ID left join STK_BookstackInfo on STK_BookInfo.BkstackID = STK_BookstackInfo.id where STK_BookstackInfo.StgID = " + IntToStr(stgid);
	querydetail->Close();
	querydetail->SQL->Clear();
	querydetail->SQL->Add(sql);
	querydetail->Open();
	((TFloatField *)querydetail->FieldByName("dprice"))->DisplayFormat = "##0.00";
	((TFloatField *)querydetail->FieldByName("Discount"))->DisplayFormat = "##0.00%";
	disable();
	modify = false;
       modify = false;
      m_catalogSearchMode = 1;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmclientdisforbook::edqueryKeyPress(TObject *Sender, wchar_t &Key)
{
        if (Key == '\r')
        {       AnsiString sql;
          	sql = "select ID,Name from CUST_CustomerInfo where type in(2,3)  and customerstate=1 and stgid="+IntToStr(stgid)+" and Name like '%" + edquery->Text + "%' and name <> '' ";
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
//---------------------------------------------------------------------------
void __fastcall Tfrmclientdisforbook::lblCatalogMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
if (Button == mbLeft ) {
		TPoint  pt;
		GetCursorPos(&pt);
		pm->Popup(pt.x,pt.y);
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmclientdisforbook::edtCatalogKeyPress(TObject *Sender, wchar_t &Key)

{
if (Key == VK_RETURN) {
    	if (edtCatalog->Text == "") {
			ChangeCatalogSearchMode();
		}
		else
		{
        	Query();
		}
	}
}
void  Tfrmclientdisforbook::ChangeCatalogSearchMode()
{
if (m_catalogSearchMode==4) {
		m_catalogSearchMode=1;
	}else
	{
	m_catalogSearchMode++;  }
	if (m_catalogSearchMode >= 5)
	{
		m_catalogSearchMode = 1;
	}

	switch (m_catalogSearchMode)
	{
	case 1:
		edtCatalog->MaxLength = 13;
		lblCatalog->Caption = "书号";
		break;
	case 2:
		edtCatalog->MaxLength = 0;
		lblCatalog->Caption = "书名";
		break;
	case 3:
		edtCatalog->MaxLength = 0;
		lblCatalog->Caption = "自编码";
		break;
	case 4:
		edtCatalog->MaxLength = 0;
		lblCatalog->Caption = "定价";
		break;
    default:
        break;
	}
}
void  Tfrmclientdisforbook::Query()
{
    String sql,sql1;
	int stgid = (int)cbstorage->Items->Objects[cbstorage->ItemIndex];
	sql = "select BS_BookCatalog.ID,STK_BookInfo.ID as BKID,STK_BookInfo.SupplierID,BS_BookCatalog.Name,BS_BookCatalog.Barcode,"
			"BS_BookCatalog.UserDefCode,BS_BookCatalog.ISBN,CUST_CustomerInfo.Name as SupplierName,STK_BookInfo.ID as STK_BookinfoID,"
			"STK_BookInfo.Amount,STK_BookstackInfo.Name as BkstackName,BS_BookCatalog.Price ,BS_PressInfo.AbbreviatedName ,STK_BookstackInfo.name LocalName "
			"from STK_BookInfo  join BS_BookCatalog on STK_BookInfo.BkcatalogID=BS_BookCatalog.ID "
			"left join CUST_CustomerInfo on STK_BookInfo.SupplierID=CUST_CustomerInfo.ID "
			"left join STK_BookstackInfo on STK_BookInfo.BkstackID=STK_BookstackInfo.ID "
			"left join BS_PressInfo ON BS_BookCatalog.PressID = BS_PressInfo.ID "
			"where STK_BookstackInfo.StgID=" + IntToStr(stgid);

     sql1= " select BS_ClientBookDiscount.*,CUST_CustomerInfo.name as clientname,BS_BookCatalog.Name, "
           " BS_BookCatalog.ISBN,BS_BookCatalog.Price,BS_PressInfo.AbbreviatedName, "
           " BS_BookCatalog.Price*BS_ClientBookDiscount.Discount/100 as dprice "
           " from BS_ClientBookDiscount left join BS_BookCatalog on BS_ClientBookDiscount.BookCatalogID = BS_BookCatalog.ID"
          "  left join CUST_CustomerInfo on BS_ClientBookDiscount.Client = CUST_CustomerInfo.id "
          "  left join BS_PressInfo on BS_BookCatalog.PressID = BS_PressInfo.id "
          "  left join STK_BookInfo on BS_ClientBookDiscount.BookInfoID = STK_BookInfo.ID "
          "  left join STK_BookstackInfo on STK_BookInfo.BkstackID = STK_BookstackInfo.id  "
          "  where STK_BookstackInfo.StgID =" + IntToStr(stgid);



	switch (m_catalogSearchMode) {
		case 1:  //书号
			sql1 = sql1 + " and BS_BookCatalog.Unavailable=1 and (BS_BookCatalog.Barcode like '%" + edtCatalog->Text.Trim()  + "%' or BS_BookCatalog.ISBN like '%"+ edtCatalog->Text.Trim() + "%')";
			sql = sql + " and BS_BookCatalog.Unavailable=1 and (BS_BookCatalog.Barcode like '%" + edtCatalog->Text.Trim()  + "%' or BS_BookCatalog.ISBN like '%"+ edtCatalog->Text.Trim() + "%')";
		break;
		case 3:  //自编码
			sql1 = sql1 + " and BS_BookCatalog.Unavailable=1 and BS_BookCatalog.UserDefCode like '%" + edtCatalog->Text.Trim()  + "%'";
			sql = sql + " and BS_BookCatalog.Unavailable=1 and BS_BookCatalog.UserDefCode like '%" + edtCatalog->Text.Trim()  + "%'";
		break;
		case 2:  //书名
			sql1 = sql1 + " and BS_BookCatalog.Unavailable=1 and BS_BookCatalog.Name like '%" + edtCatalog->Text.Trim()  + "%'";
			sql = sql + " and BS_BookCatalog.Unavailable=1 and BS_BookCatalog.Name like '%" + edtCatalog->Text.Trim()  + "%'";
		break;
		case 4:  //定价
			sql1 = sql1 + " and BS_BookCatalog.Unavailable=1 and BS_BookCatalog.Price =" + edtCatalog->Text.Trim();
			sql = sql + " and BS_BookCatalog.Unavailable=1 and BS_BookCatalog.Price =" + edtCatalog->Text.Trim();
		break;
    default:
        ;
	}
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	querydetail->Close();
	querydetail->SQL->Clear();
	querydetail->SQL->Add(sql1);
	querydetail->Open();
	disable();
}
void __fastcall Tfrmclientdisforbook::disable()
{
          	if (querydetail->IsEmpty() ) {
		eddiscount->Text = "" ;
		edprice->Text = "";
	       //	dtpstart->Date = Date();
	       //	dtpend->Date = Date();
	}
	else
	{
		edprice->Text = FormatFloat("##0.00",querydetail->FieldByName("dprice")->AsFloat);
		eddiscount->Text = FormatFloat("##0.00",querydetail->FieldByName("Discount")->AsFloat);
	       //	dtpstart->Date = querydetail->FieldByName("Starttime")->AsDateTime ;
	       //	dtpend->Date = querydetail->FieldByName("Endtime")->AsDateTime ;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmclientdisforbook::cbstorageSelect(TObject *Sender)
{
	try {
		stgid =  (int)cbstorage->Items->Objects[cbstorage->ItemIndex];
	} catch (...) {

                ShowMsg(Handle ,"请选择正确的店名！",3);
		return;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmclientdisforbook::DBGrid1CellClick(TColumn *Column)
{
     modify = false;
	if (aq->IsEmpty() ) {
        return;
	}
		int memtype ;
		try {
			memtype = (int)cbCusName->Items->Objects[cbCusName->ItemIndex];
		} catch (...) {

                        ShowMsg(Handle ,"请选择正确的会员类型！",3);
			return;
		}
		AnsiString sql;
		sql = "select BS_ClientBookDiscount.*,Discount*BS_BookCatalog.price/100 as dprice from BS_ClientBookDiscount "
				" left join BS_BookCatalog on BS_ClientBookDiscount.bookcatalogid = BS_BookCatalog.id where BookInfoID = " + aq->FieldByName("BKID")->AsString + " and Client = " + IntToStr(memtype);
			query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->Open();
			if (query->RecordCount > 0) {
				edprice->Text = FormatFloat("##0.00",query->FieldByName("dprice")->AsFloat);
				eddiscount->Text = FormatFloat("##0.00",query->FieldByName("Discount")->AsFloat);
			     //	dtpstart->Date = querydetail->FieldByName("Starttime")->AsDateTime ;
			      //	dtpend->Date = querydetail->FieldByName("Endtime")->AsDateTime ;
			}
			else
			{
				eddiscount->Text = "" ;
                                 edprice->Text = "";
			       //	dtpstart->Date = Date();
			       //	dtpend->Date = Date();
			}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmclientdisforbook::BtnSaveClick(TObject *Sender)
{
	if (modify && !querydetail->IsEmpty()) {
		excuit();
	}
	else
	{
		if (aq->IsEmpty() ) {
			return;
		}
		if (eddiscount->Text == "") {

                        ShowMsg(Handle ,"折扣不能为空！",3);
			return;
		}
		float  discount;
		try {
			discount =  StrToFloat(eddiscount->Text);
		} catch (...) {

                        ShowMsg(Handle ,"请输入正确的折扣！",3);
			return;
		}

		if (discount < 0) {

                        ShowMsg(Handle ,"折扣不能小于0！",3);
			return;
		}
		if (discount > 100) {

                         ShowMsg(Handle ,"折扣不能大于100！",3);
			return;
		}
		if (DBGrid1->SelectedRows->Count == 0) {
			excuit();
		}
		else
		{
			for (int i = 0; i < DBGrid1->SelectedRows->Count ; i++) {
				aq->Bookmark =  DBGrid1->SelectedRows->Items[i];
				excuit();
			}
		}
	}

	querydetail->Active = false;
	querydetail->Active = true;
	((TFloatField *)querydetail->FieldByName("dprice"))->DisplayFormat = "##0.00";
	((TFloatField *)querydetail->FieldByName("Discount"))->DisplayFormat = "##0.00%";
	disable();
}
void Tfrmclientdisforbook::excuit()
{
   	AnsiString sql;
	int memtype, stgid;
	try {
		memtype = (int)cbCusName->Items->Objects[cbCusName->ItemIndex];
	} catch (...) {

                 ShowMsg(Handle ,"请选择正确的会员类型！",3);
		return;
	}
	try {
		stgid = (int)cbstorage->Items->Objects[cbstorage->ItemIndex];
	} catch (...) {

         ShowMsg(Handle ,"请选择正确的店名！",3);
		return;
	}
	if (modify) {
    	sql = "update BS_ClientBookDiscount set Discount = " + eddiscount->Text ;
		sql = sql + " where ID = " + querydetail->FieldByName("id")->AsString ;
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->ExecSQL();
		modify = false;
		return;
	}

	sql = "select * from BS_ClientBookDiscount where BookInfoID = " + aq->FieldByName("BKID")->AsString + " and client = " + IntToStr(memtype) + " and StgID = " + IntToStr(stgid)  ;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	if (query->RecordCount > 0) {    //修改
		sql = "update BS_ClientBookDiscount set Discount = " + eddiscount->Text ;
		sql = sql + " where ID = " + query->FieldByName("ID")->AsString ;
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->ExecSQL();
	}
	else  //添加
	{
    	if (querydetail->State != dsInsert) {
			querydetail->Append();
		}
		querydetail->FieldByName("StgID")->AsInteger = stgid;
		querydetail->FieldByName("Client")->AsInteger = memtype;
		querydetail->FieldByName("Discount")->AsString = eddiscount->Text;
		querydetail->FieldByName("BookCatalogID")->AsInteger = aq->FieldByName("ID")->AsInteger ;
		querydetail->FieldByName("BookInfoID")->AsInteger = aq->FieldByName("BKID")->AsInteger ;
		querydetail->UpdateBatch(arAll);
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmclientdisforbook::dbgdiscountCellClick(TColumn *Column)
{
  modify = true;
	disable();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmclientdisforbook::BtnAlignBottomClick(TObject *Sender)
{
WindowState = wsMinimized;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmclientdisforbook::BtnExitClick(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmclientdisforbook::FormClose(TObject *Sender, TCloseAction &Action)

{
Action = caFree ;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmclientdisforbook::eddiscountKeyPress(TObject *Sender, wchar_t &Key)

{
       if ((Key < '0' || Key > '9') && (Key != '\b') && (Key != '.') && (Key != '\r') ) {
    	Key = NULL;
	}
	if (Key == '\r') {
		if (modify) {
			if (querydetail->IsEmpty() ) {
				return;
			}
            float discount;
			try {
				discount = StrToFloat(eddiscount->Text);
			} catch (...) {
				return;
			}
			edprice->Text = FormatFloat("##0.00",querydetail->FieldByName("Price")->AsFloat*discount/100);
		}
		else
		{
        	if (aq->IsEmpty() ) {
				return;
			}
			float discount;
			try {
				discount = StrToFloat(eddiscount->Text);
			} catch (...) {
				return;
			}
			edprice->Text = FormatFloat("##0.00",aq->FieldByName("Price")->AsFloat*discount/100);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmclientdisforbook::N5Click(TObject *Sender)
{
	if (aq->IsEmpty() ) {
        return;
	}
	for (int i = 1; i <= aq->RecordCount; i++) {
		DBGrid1->DataSource->DataSet->RecNo = i;
		DBGrid1->SelectedRows->CurrentRowSelected = true;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmclientdisforbook::N7Click(TObject *Sender)
{
 BtnSave->Click();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmclientdisforbook::MenuItem1Click(TObject *Sender)
{
//
  AnsiString sql;
  if (ShowMsg(Handle,"是否要删除?",1)==1) {
    sql = "delete BS_ClientBookDiscount where id  ="+querydetail->FieldByName("id")->AsAnsiString ;
   TADOQuery *aq=new TADOQuery(Application);
      aq->Connection = fcon;
      aq->Close();
      aq->SQL->Clear();
      aq->SQL->Add(sql);
      aq->ExecSQL();
      	querydetail->Active = false;
	querydetail->Active = true;
  }
 
}
//---------------------------------------------------------------------------
