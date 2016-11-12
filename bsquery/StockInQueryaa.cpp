//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "StockInQueryaa.h"
#include "pdutil.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "MDIChild"
#pragma link "RzLabel"
#pragma link "RzPanel"
#pragma link "RzButton"
#pragma link "RzRadChk"
#pragma link "RzDBEdit"
#pragma link "RzDBGrid"
#pragma link "RzEdit"
#pragma link "RzDBDTP"
#pragma link "RzDTP"
#pragma link "RzDBCmbo"
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma resource "*.dfm"
TfrmStockInQueryaa *frmStockInQueryaa;
//---------------------------------------------------------------------------
__fastcall TfrmStockInQueryaa::TfrmStockInQueryaa(TComponent* Owner)
	: TfrmMDIChild(Owner)
	,m_sql("")
{
	m_module = MTBsqry;
}
//---------------------------------------------------------------------------
void TfrmStockInQueryaa::Init(TApplication* app, TADOConnection* con)
{
	 TfrmMDIChild::Init(app,con);
	 this->WindowState = wsMaximized ;
	 qry1->Connection = m_con;
	 tblPress->Connection = m_con;
	dsetCatlog->Connection = m_con;
	tblCatalogType->Connection = m_con;
	tbl1supplier->Connection = m_con;
	tbl2supplier->Connection = m_con;
    tblStore ->Connection = m_con;
	aquery->Connection = m_con;
	tbllocal->Connection = m_con;
	tbllocal->Active = true;
	//-------------------
	tbllocal->Filtered = false;
	tbllocal->Filter = "stgid ="+IntToStr(m_storageID);
    tbllocal->Filtered = true;
	//-------------------

	tbl1supplier->Active = true;
    tbl2supplier->Active = true;
	tblPress->Active = true;
    tblStore->Active = true;
	dsetCatlog->Active = true;
	tblCatalogType->Active = true;
	 //Formstrngrid();
	Desic = QueryDesic();
}
void __fastcall TfrmStockInQueryaa::FormClose(TObject *Sender, TCloseAction &Action)

{
	Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TfrmStockInQueryaa::btnExit4Click(TObject *Sender)
{
	Close();
}
//------------------------------------------------
 String TfrmStockInQueryaa::QueryDesic()
 {
   TADOQuery * aq;
   aq = new TADOQuery(this);
   aq->Connection = m_con ;
   aq->Close();
   aq->SQL->Clear();
   aq->SQL->Add("select bk from sys_bsset where name ='xiaoshudian'");
   aq->Open();
   return "￥" + aq->FieldByName("bk")->AsAnsiString ;
   delete aq;
 }
//---------------------------------
String TfrmStockInQueryaa::QuerySum()
{
   String tmpsql="";
   	if (chckbxBookName->Checked )
	{
		if (tmpsql=="")
		{
			String bookName = edtBookName->Text ;
			tmpsql = tmpsql + " (BS_BookCatalog.Name like '%" + bookName + "%')" ;
		}
		else
		{
			String bookName = edtBookName->Text ;
			tmpsql = tmpsql + " and (BS_BookCatalog.Name like '%" + bookName + "%')" ;
		}

	}
	if (chckbxISBN->Checked )
	{
		if (tmpsql=="")
		{
			String ISBN = edtISBN->Text ;
			if (ISBN.Length() == 13 )
			{
			  tmpsql = tmpsql + " (BS_BookCatalog.Barcode = '"+ ISBN +"')";
			}
			else
			{
				tmpsql = tmpsql + " (BS_BookCatalog.ISBN = '"+ ISBN +"')";
			}
		}
		else
		{
			String ISBN = edtISBN->Text ;
			if (ISBN.Length() == 13 )
			{
				tmpsql = tmpsql + " and (BS_BookCatalog.Barcode = '"+ ISBN +"')";
			}
			else
			{
				tmpsql = tmpsql + " and (BS_BookCatalog.ISBN = '"+ ISBN +"')";
			}
		}
	}
	if (chckbxSupplier->Checked )
	{
		if (tmpsql=="")
		{
            String supplier = edtSupplier->Text ;
			tmpsql = tmpsql + " (CUST_CustomerInfo_1.Name like '%" + supplier +"%')";
		}
		else
		{
			String supplier = edtSupplier->Text ;
			tmpsql = tmpsql + " and (CUST_CustomerInfo_1.Name like '%" + supplier +"%')";
		}

	}
	if (chckbxUserDefNum->Checked)
	{
		if (tmpsql=="")
		{
            String userdefnum = edtUserDefNum->Text ;
			tmpsql = tmpsql + " (BS_BookCatalog.UserDefCode like '%" + userdefnum +"%')";
		}
		else
		{
        	String userdefnum = edtUserDefNum->Text ;
			tmpsql = tmpsql + " and (BS_BookCatalog.UserDefCode like '%" + userdefnum +"%')";
		}

	}
	if (chckbxPrice->Checked )
	{
		if(edtPrice->Text == "" )
		{}
		else
		{
			if (tmpsql=="")
			{
				String  price = edtPrice->Text;
				tmpsql = tmpsql + " (BS_BookCatalog.Price = " + price + " )";
			}
			else
			{
				String  price = edtPrice->Text;
				tmpsql = tmpsql + " and (BS_BookCatalog.Price = " + price + " )";
			}
		}

	}
	if (chckbxAuthor->Checked )
	{
		if (tmpsql=="")
		{
			String author = edtAuthor->Text ;
			tmpsql = tmpsql + " (BS_BookCatalog.Author like '%"+ author +"%')";
		}
		else
		{
        	String author = edtAuthor->Text ;
			tmpsql = tmpsql + " and (BS_BookCatalog.Author like '%"+ author +"%')";
		}

	}
	if (chckbxAmount->Checked )
	{
		if (edtAmountHigh->Text == "" && edtAmountLow->Text != "")
		{
        	if (tmpsql=="")
			{
				int amountlow = edtAmountLow->Text .ToInt();
				tmpsql = tmpsql + " (STK_BookInfo.Amount >= '" + amountlow + "')";
			}
			else
			{
				int amountlow = edtAmountLow->Text .ToInt();
				int amounthigh = edtAmountHigh->Text .ToInt();
				tmpsql = tmpsql + " and (STK_BookInfo.Amount >= '" + amountlow + "')";
			}
		}
		else if (edtAmountHigh->Text != "" && edtAmountLow->Text == "") {
        	if (tmpsql=="")
			{
				int amounthigh = edtAmountHigh->Text .ToInt();
				tmpsql = tmpsql + " (STK_BookInfo.Amount <= '" + amounthigh + "')";
			}
			else
			{
				int amounthigh = edtAmountHigh->Text .ToInt();
				tmpsql = tmpsql + " and (STK_BookInfo.Amount <= '" + amounthigh + "')";
			}
		}
		else if (edtAmountHigh->Text != "" && edtAmountLow->Text != "")
		{
			if (tmpsql=="")
			{
				int amountlow = edtAmountLow->Text .ToInt();
				int amounthigh = edtAmountHigh->Text .ToInt();
				tmpsql = tmpsql + " (STK_BookInfo.Amount >= '" + amountlow + "')";
				tmpsql = tmpsql + " and (STK_BookInfo.Amount <= '" + amounthigh + "')";
			}
			else
			{
				int amountlow = edtAmountLow->Text .ToInt();
				int amounthigh = edtAmountHigh->Text .ToInt();
				tmpsql = tmpsql + " and (STK_BookInfo.Amount >= '" + amountlow + "')";
				tmpsql = tmpsql + " and (STK_BookInfo.Amount <= '" + amounthigh + "')";
			}
		}

	}
	if (chckbxPressCount->Checked )
	{
		if (tmpsql=="")
		{
			String presscount = edtPressCount->Text ;
			tmpsql = tmpsql + " (BS_PressInfo.AbbreviatedName like '" + presscount +"')";
		}
		else
		{
			String presscount = edtPressCount->Text ;
			tmpsql = tmpsql + " and (BS_PressInfo.AbbreviatedName like '" + presscount +"')";
		}

	}
	if (chckbxType->Checked )
	{
		if (tmpsql=="")
		{
            String type = edtType->Text ;
			tmpsql = tmpsql + " (BS_BookType.Name like '%"+ type +"%')";
		}
		else
		{
        	String type = edtType->Text ;
			tmpsql = tmpsql + " and (BS_BookType.Name like '%"+ type +"%')";
		}

	}

	if (chckbxShopNum->Checked )
	{   edtShopNum->Text= edtstore->Text;
		if (edtShopNum->Text == "")
		{}
		else
		{
			if (tmpsql=="")
			{
				String shopnum = edtstore->Text  ;
				tmpsql = tmpsql + " (SYS_StorageInfo.Name = '"+ shopnum +"')";
			}
			else
			{
				String shopnum = edtstore->Text ;
				tmpsql = tmpsql + " and (SYS_StorageInfo.Name = '"+ shopnum +"')";
			}
		}

	}
	else
	{
			if (tmpsql=="")
			{
				tmpsql = tmpsql + " (SYS_StorageInfo.id = "+ IntToStr(m_storageID)  +")";
			}
			else
			{
				tmpsql = tmpsql + " and (SYS_StorageInfo.id = "+ IntToStr(m_storageID) +")";
			}
	}


	if (rzlocal->Checked ) {
	  if (edtlocal->Text =="") {

	  }else
	  {
		 if (tmpsql =="") {
			  String local = edtlocal->Text ;
			  tmpsql = tmpsql + " ( STK_BookstackInfo.Name = '" +  local+"')";
		 }  else
		 {
			 String local = edtlocal->Text ;
			  tmpsql = tmpsql + " and ( STK_BookstackInfo.Name = '" +  local+"')";
		 }

	  }

	}

	return  tmpsql;




}
String TfrmStockInQueryaa::QueryCom()
{
	String tmpsql="";

	if (chckbxBookName->Checked )
	{
		if (tmpsql=="")
		{
			String bookName = edtBookName->Text ;
			tmpsql = tmpsql + " (BookCatalogName like '%" + bookName + "%')" ;
		}
		else
		{
			String bookName = edtBookName->Text ;
			tmpsql = tmpsql + " and (BookCatalogName like '%" + bookName + "%')" ;
		}

	}
	if (chckbxISBN->Checked )
	{
		if (tmpsql=="")
		{
			String ISBN = edtISBN->Text ;
			if (ISBN.Length() == 13 )
			{
			  tmpsql = tmpsql + " (BookCatalogBarcode = '"+ ISBN +"')";
			}
			else
			{
				tmpsql = tmpsql + " (BookCatalogISBN = '"+ ISBN +"')";
			}
		}
		else
		{
			String ISBN = edtISBN->Text ;
			if (ISBN.Length() == 13 )
			{
				tmpsql = tmpsql + " and (BookCatalogBarcode = '"+ ISBN +"')";
			}
			else
			{
				tmpsql = tmpsql + " and (BookCatalogISBN = '"+ ISBN +"')";
			}
		}

	}
	if (chckbxSupplier->Checked )
	{
		if (tmpsql=="")
		{
            String supplier = edtSupplier->Text ;
			tmpsql = tmpsql + " (CustomerInfoName like '%" + supplier +"%')";
		}
		else
		{
			String supplier = edtSupplier->Text ;
			tmpsql = tmpsql + " and (CustomerInfoName like '%" + supplier +"%')";
		}

	}
	if (chckbxUserDefNum->Checked)
	{
		if (tmpsql=="")
		{
            String userdefnum = edtUserDefNum->Text ;
			tmpsql = tmpsql + " (BookCatalogUserDefCode like '%" + userdefnum +"%')";
		}
		else
		{
        	String userdefnum = edtUserDefNum->Text ;
			tmpsql = tmpsql + " and (BookCatalogUserDefCode like '%" + userdefnum +"%')";
		}

	}
	if (chckbxPrice->Checked )
	{
		if(edtPrice->Text == "" )
		{}
		else
		{
			if (tmpsql=="")
			{
				String  price = edtPrice->Text;
				tmpsql = tmpsql + " (BookCatalogPrice = " + price + " )";
			}
			else
			{
				String  price = edtPrice->Text;
				tmpsql = tmpsql + " and (BookCatalogPrice = " + price + " )";
			}
		}

	}
	if (chckbxAuthor->Checked )
	{
		if (tmpsql=="")
		{
			String author = edtAuthor->Text ;
			tmpsql = tmpsql + " (BookCatalogAuthor like '%"+ author +"%')";
		}
		else
		{
        	String author = edtAuthor->Text ;
			tmpsql = tmpsql + " and (BookCatalogAuthor like '%"+ author +"%')";
		}

	}
	if (chckbxAmount->Checked )
	{
		if (edtAmountHigh->Text == "" && edtAmountLow->Text != "")
		{
        	if (tmpsql=="")
			{
				int amountlow = edtAmountLow->Text .ToInt();
				tmpsql = tmpsql + " (BookInfoAmount >= '" + amountlow + "')";
			}
			else
			{
				int amountlow = edtAmountLow->Text .ToInt();
				int amounthigh = edtAmountHigh->Text .ToInt();
				tmpsql = tmpsql + " and (BookInfoAmount >= '" + amountlow + "')";
			}
		}
		else if (edtAmountHigh->Text != "" && edtAmountLow->Text == "") {
        	if (tmpsql=="")
			{
				int amounthigh = edtAmountHigh->Text .ToInt();
				tmpsql = tmpsql + " (BookInfoAmount <= '" + amounthigh + "')";
			}
			else
			{
				int amounthigh = edtAmountHigh->Text .ToInt();
				tmpsql = tmpsql + " and (BookInfoAmount <= '" + amounthigh + "')";
			}
		}
		else if (edtAmountHigh->Text != "" && edtAmountLow->Text != "")
		{
			if (tmpsql=="")
			{
				int amountlow = edtAmountLow->Text .ToInt();
				int amounthigh = edtAmountHigh->Text .ToInt();
				tmpsql = tmpsql + " (BookInfoAmount >= '" + amountlow + "')";
				tmpsql = tmpsql + " and (BookInfoAmount <= '" + amounthigh + "')";
			}
			else
			{
				int amountlow = edtAmountLow->Text .ToInt();
				int amounthigh = edtAmountHigh->Text .ToInt();
				tmpsql = tmpsql + " and (BookInfoAmount >= '" + amountlow + "')";
				tmpsql = tmpsql + " and (BookInfoAmount <= '" + amounthigh + "')";
			}
		}

	}
	if (chckbxPressCount->Checked )
	{
		if (tmpsql=="")
		{
			String presscount = edtPressCount->Text ;
			tmpsql = tmpsql + " (BookCatalogPressCount like '" + presscount +"')";
		}
		else
		{
			String presscount = edtPressCount->Text ;
			tmpsql = tmpsql + " and (BookCatalogPressCount like '" + presscount +"')";
		}

	}
	if (chckbxType->Checked )
	{
		if (tmpsql=="")
		{
            String type = edtType->Text ;
			tmpsql = tmpsql + " (BookTypeName like '%"+ type +"%')";
		}
		else
		{
        	String type = edtType->Text ;
			tmpsql = tmpsql + " and (BookTypeName like '%"+ type +"%')";
		}

	}

	if (chckbxShopNum->Checked )
	{   edtShopNum->Text= edtstore->Text;
		if (edtShopNum->Text == "")
		{}
		else
		{
			if (tmpsql=="")
			{
				String shopnum = edtstore->Text ;
				tmpsql = tmpsql + " (StorageInfoName = '"+ shopnum +"')";
			}
			else
			{
				String shopnum = edtstore->Text ;
				tmpsql = tmpsql + " and (StorageInfoName = '"+ shopnum +"')";
			}
		}

	}
	else
	{
    	if (tmpsql=="")
			{
				String shopnum = edtstore->Text ;
				tmpsql = tmpsql + " (StgID = "+ IntToStr(m_storageID)  +")";
			}
			else
			{
				String shopnum = edtstore->Text ;
				tmpsql = tmpsql + " and (StgID = "+ IntToStr(m_storageID) +")";
			}
	}


		if (rzlocal->Checked ) {
	  if (edtlocal->Text =="") {

	  }else
	  {
		 if (tmpsql =="") {
			  String local = edtlocal->Text ;
			  tmpsql = tmpsql + " (BkstackName= '" +  local+"')";
		 }  else
		 {
			 String local = edtlocal->Text ;
			  tmpsql = tmpsql + " and ( BkstackName = '" +  local+"')";
		 }

	  }

	}

	return  tmpsql;
}
//---------------------------------
void __fastcall TfrmStockInQueryaa::btnExit1Click(TObject *Sender)
{

	Query();
}
//---------------------------------------------------------------------------

//void TfrmQuery::Query1()
//{
//	m_sql = "select OrderNoteHeaderHdTime,OrderNoteID,VendorName, OrderNoteHeaderTotalFixedPrice, OrderNoteHeaderTotalDiscountedPrice, OrderNoteAmount, OrderNoteSendAmount, OrderNoteUnsendAmount,StgName from UV_QryOrderNote where";
//	String tmpsql = QueryOrderNoteCom();
//	if (!chckbxShopNum->Checked  && !chckbxRemarks->Checked && !chckbxType->Checked && !chckbxPressCount->Checked && !chckbxAmount->Checked && !chckbxAuthor->Checked &&!chckbxPrice->Checked &&!chckbxUserDefNum->Checked && !chckbxCustomer->Checked &&!chckbxSupplier->Checked &&!chckbxISBN->Checked &&!chckbxStartTime->Checked&&!chckbxEndTime->Checked&&!chckbxBookName->Checked)
//	{
//		m_sql = "select OrderNoteHeaderHdTime,OrderNoteID,VendorName, OrderNoteHeaderTotalFixedPrice, OrderNoteHeaderTotalDiscountedPrice, OrderNoteAmount, OrderNoteSendAmount, OrderNoteUnsendAmount,StgName from UV_QryOrderNote";
//	}
//	m_sql = m_sql + tmpsql;
//	qry1->Active = false;
//	qry1->SQL->Clear();
//	qry1->SQL->Add(m_sql);
//	qry1->Active = true;
//}
//-----
void TfrmStockInQueryaa::Query()
{
	AnsiString sqlsum,sqlsumtotal;

	sqlsum = "select  sum(STK_BookInfo.Amount) as stockamount,  sum(STK_BookInfo.Amount *BS_BookCatalog.Price) as mayang,"
			 " sum(STK_BookInfo.Amount *STK_BookInfo.Cbprice) as shiyang  "
			 " FROM         dbo.BS_PressInfo RIGHT OUTER JOIN "
			 " dbo.BS_BookCatalog ON dbo.BS_PressInfo.ID = dbo.BS_BookCatalog.PressID RIGHT OUTER JOIN "
			 " dbo.STK_BookInfo LEFT OUTER JOIN "
			 " dbo.CUST_CustomerInfo ON dbo.STK_BookInfo.SupplierID = dbo.CUST_CustomerInfo.ID LEFT OUTER JOIN "
			 " dbo.STK_BookstackInfo ON dbo.STK_BookInfo.BkstackID = dbo.STK_BookstackInfo.ID LEFT OUTER JOIN "
			 " dbo.CUST_CustomerInfo AS CUST_CustomerInfo_1 ON dbo.STK_BookInfo.SupplierID = CUST_CustomerInfo_1.ID ON"
			 " dbo.BS_BookCatalog.ID = dbo.STK_BookInfo.BkcatalogID LEFT OUTER JOIN "
			 " dbo.STK_BookstackInfo AS STK_BookstackInfo_1 ON dbo.STK_BookInfo.BkstackID = STK_BookstackInfo_1.ID LEFT OUTER JOIN "
			 " dbo.SYS_StorageInfo ON STK_BookstackInfo_1.StgID = dbo.SYS_StorageInfo.ID LEFT OUTER JOIN "
			 " dbo.BS_BookType ON dbo.BS_BookCatalog.smallBookTypeID = dbo.BS_BookType.ID where (1=1) ";
  sqlsumtotal = " select sum(STK_BookInfo.Amount) as totalstock,sum(dbo.BS_BookCatalog.Price * STK_BookInfo.Amount) as totalmayang,sum(STK_BookInfo.Amount*Cbprice) as totalshiyang "
					" from STK_BookInfo LEFT JOIN BS_BookCatalog ON BS_BookCatalog.id = STK_BookInfo.BkcatalogID left join "
					" STK_BookstackInfo on STK_BookInfo.BkstackID = STK_BookstackInfo.id "
					" WHERE BS_BookCatalog.id in "
					"(select  distinct STK_BookInfo.BkcatalogID "
					" FROM dbo.BS_PressInfo RIGHT OUTER JOIN "
					" dbo.BS_BookCatalog ON dbo.BS_PressInfo.ID = dbo.BS_BookCatalog.PressID RIGHT OUTER JOIN "
					" dbo.STK_BookInfo LEFT OUTER JOIN "
					" dbo.CUST_CustomerInfo ON dbo.STK_BookInfo.SupplierID = dbo.CUST_CustomerInfo.ID LEFT OUTER JOIN "
					" dbo.STK_BookstackInfo ON dbo.STK_BookInfo.BkstackID = dbo.STK_BookstackInfo.ID LEFT OUTER JOIN "
					" dbo.CUST_CustomerInfo AS CUST_CustomerInfo_1 ON dbo.STK_BookInfo.SupplierID = CUST_CustomerInfo_1.ID ON"
					" dbo.BS_BookCatalog.ID = dbo.STK_BookInfo.BkcatalogID LEFT OUTER JOIN "
					" dbo.STK_BookstackInfo AS STK_BookstackInfo_1 ON dbo.STK_BookInfo.BkstackID = STK_BookstackInfo_1.ID LEFT OUTER JOIN "
					" dbo.SYS_StorageInfo ON STK_BookstackInfo_1.StgID = dbo.SYS_StorageInfo.ID LEFT OUTER JOIN "
					" dbo.BS_BookType ON dbo.BS_BookCatalog.smallBookTypeID = dbo.BS_BookType.ID where (1=1) ";



	m_sql = "select BookCatalogISBN,Cbprice,BookCatalogName,BookCatalogPressCount,BkstackName,SupplierName,PressName,BookTypeName,BookCatalogPrice,BookInfoAmount,BookCatalogTotalAmount,StorageInfoName,BookCatalogUserDefCode,BookCatalogDate,BookCatalogAuthor,kuchunyangmao,totalmayang,kuchunshiyang,totalshiyang from UV_QryStock where";
	String tmpsql = QueryCom();
	/*if(!chckbxShopNum->Checked  && !chckbxType->Checked && !chckbxPressCount->Checked && !chckbxAmount->Checked && !chckbxAuthor->Checked &&!chckbxPrice->Checked &&!chckbxUserDefNum->Checked &&!chckbxSupplier->Checked &&!chckbxISBN->Checked &&!chckbxBookName->Checked&&!rzlocal->Checked)
	{
		m_sql = "select BookCatalogISBN,Cbprice,BookCatalogName,BookCatalogPressCount,BkstackName,SupplierName,PressName,BookTypeName,BookCatalogPrice,BookInfoAmount,BookCatalogTotalAmount,StorageInfoName,BookCatalogUserDefCode,BookCatalogDate,BookCatalogAuthor,kuchunyangmao,totalmayang from UV_QryStock";
	} */

	m_sql = m_sql + tmpsql;



	if (QuerySum() != "") {
	  sqlsum = sqlsum + " and " ;
	  sqlsumtotal = sqlsumtotal + " and ";
	}

	sqlsum = sqlsum + QuerySum();
	sqlsumtotal = sqlsumtotal + QuerySum() + ") and STK_BookstackInfo.StgID = ";
	if (chckbxShopNum->Checked ) {
		sqlsumtotal = sqlsumtotal  + tblStore->FieldByName("id")->AsString ;
	}
	else
	{
		sqlsumtotal = sqlsumtotal  + IntToStr(m_storageID);
	}
	qry1->Active = false;
	qry1->SQL ->Clear();
	qry1->SQL ->Add(m_sql);
	try
	{

		qry1->Active = true;

		((TFloatField *)qry1->FieldByName("kuchunyangmao"))->DisplayFormat = Desic ;
		((TFloatField *)qry1->FieldByName("totalmayang"))->DisplayFormat =  Desic;
		((TFloatField *)qry1->FieldByName("BookCatalogPrice"))->DisplayFormat =  Desic;
		((TFloatField *)qry1->FieldByName("Cbprice"))->DisplayFormat =  Desic;
		((TFloatField *)qry1->FieldByName("kuchunshiyang"))->DisplayFormat = Desic ;
		((TFloatField *)qry1->FieldByName("totalshiyang"))->DisplayFormat =  Desic;


        aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sqlsumtotal);
		aquery->Open();

		/*DBGridEh1->Columns->Items[12]->Footer->ValueType = fvtStaticText  ;
		DBGridEh1->Columns->Items[12]->Footer->Value = FormatFloat("0",aquery->FieldByName("totalstock")->AsFloat);
		DBGridEh1->Columns->Items[13]->Footer->ValueType = fvtStaticText ;
		DBGridEh1->Columns->Items[13]->Footer->Value = FormatFloat(Desic,aquery->FieldByName("totalmayang")->AsFloat);
		DBGridEh1->Columns->Items[14]->Footer->ValueType = fvtStaticText ;
		DBGridEh1->Columns->Items[14]->Footer->Value = FormatFloat(Desic,aquery->FieldByName("totalshiyang")->AsFloat);  */


		lbcount->Caption ="共有 "+ IntToStr(qry1->RecordCount) + " 条查询记录";
	} catch (...)
	{
		if (chckbxPrice->Checked && edtPrice->Text  == "")
		{
			ShowMessage("请输入价格！");
		}
		if(chckbxAmount->Checked )
		if(edtAmountLow->Text == "" || edtAmountHigh == "")
		{
        	ShowMessage("请输入范围限制！");
		}
		if (edtShopNum->Text == "")
		{
        	ShowMessage("请输入店号！");
		}
	}

}
//-----------
void TfrmStockInQueryaa::OnHotKeyPress(DWORD vkCode)
{
	if(vkCode == 81)
	btnExit1Click(NULL);
	if(vkCode == VK_ESCAPE)
	btnExit4Click(NULL);
}

void __fastcall TfrmStockInQueryaa::edtISBNKeyPress(TObject *Sender, wchar_t &Key)
{
	if(Key == VK_RETURN)
	{
		if(chckbxISBN->Checked )
		{
			if(edtISBN->Text .Length() != 13 )
			{
				ShowMessage("位数不正确！");
				return;
			}
			for(int i=1;i<edtISBN->Text .Length();i++ )
			if(edtISBN->Text .SubString(i,1)>='0'&&edtISBN->Text .SubString(i,1)<='9'  )
			continue;
			else
			{
				ShowMessage("请输入数字！");
				return;
			}
		}
	}

}
//---------------------------------------------------------------------------

void __fastcall TfrmStockInQueryaa::edtAmountHighKeyPress(TObject *Sender, wchar_t &Key)

{
	if(Key==VK_RETURN)
	if(chckbxAmount->Checked )
	if(StrToInt(edtAmountHigh->Text )<StrToInt(edtAmountLow->Text ))
	{
		ShowMessage("上限小于下限");
		return;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStockInQueryaa::btnExit2Click(TObject *Sender)
{
		//Excel导出
	if (qry1->Active  && qry1->RecordCount >= 1)
	{
		DbgridToExcel(DBGrid1);
	}
}
//Excel导出函数
bool __fastcall TfrmStockInQueryaa::DbgridToExcel(TDBGrid* dbg)
{
	AnsiString temptext  ;
	int k = dbg->DataSource ->DataSet ->RecordCount ,n=0;
	int count =0,row =0,col =0;
	if(k == 0)
	{
		MessageBox(0,"没有数据！","错误确认" ,MB_OK);
		return false;
	}
	Variant     v;
	v   =Variant::CreateObject("Excel.Application");
	v.OlePropertySet("Visible",true);
	v.OlePropertyGet("WorkBooks").OleFunction("Add");
//  在Excel中成字符串显示
	temptext = "'"+ this->Caption;
	v.OlePropertyGet("Cells",1,8).OlePropertySet("Value","库存查询" );
	if (chckbxBookName->Checked ) {
		row = count/4,col = count%4;
		v.OlePropertyGet("Cells",3+row,3*col+1).OlePropertySet("Value","书名" );
		temptext = "'"+ edtBookName->Text;
		v.OlePropertyGet("Cells",3+row,3*col+2).OlePropertySet("Value",temptext .c_str() );
		count ++;
	}
	if (chckbxUserDefNum->Checked ) {
		row = count/4,col = count%4;
		v.OlePropertyGet("Cells",3+row,3*col+1).OlePropertySet("Value","自编号" );
		temptext = "'"+ edtUserDefNum->Text;
		v.OlePropertyGet("Cells",3+row,3*col+2).OlePropertySet("Value",temptext .c_str() );
		count ++;
	}
	if (chckbxPressCount->Checked ) {
		row = count/4,col = count%4;
		v.OlePropertyGet("Cells",3+row,3*col+1).OlePropertySet("Value","出版社" );
		temptext = "'"+ edtPressCount->Text;
		v.OlePropertyGet("Cells",3+row,3*col+2).OlePropertySet("Value",temptext .c_str() );
		count ++;
	}
	if (chckbxISBN->Checked ) {
		row = count/4,col = count%4;
		v.OlePropertyGet("Cells",3+row,3*col+1).OlePropertySet("Value","书号" );
		temptext = "'"+ edtISBN->Text;
		v.OlePropertyGet("Cells",3+row,3*col+2).OlePropertySet("Value",temptext .c_str() );
		count ++;
	}
	if (chckbxType->Checked ) {
		row = count/4,col = count%4;
		v.OlePropertyGet("Cells",3+row,3*col+1).OlePropertySet("Value","类别" );
		temptext = "'"+ edtType->Text;
		v.OlePropertyGet("Cells",3+row,3*col+2).OlePropertySet("Value",temptext .c_str() );
		count ++;
	}
	if (chckbxSupplier->Checked ) {
		row = count/4,col = count%4;
		v.OlePropertyGet("Cells",3+row,3*col+1).OlePropertySet("Value","供应商" );
		temptext = "'"+ edtSupplier->Text;
		v.OlePropertyGet("Cells",3+row,3*col+2).OlePropertySet("Value",temptext .c_str() );
		count ++;
	}
	if (chckbxAuthor->Checked ) {
		row = count/4,col = count%4;
		v.OlePropertyGet("Cells",3+row,3*col+1).OlePropertySet("Value","作者" );
		temptext = "'"+ edtAuthor->Text;
		v.OlePropertyGet("Cells",3+row,3*col+2).OlePropertySet("Value",temptext .c_str() );
		count ++;
	}
	if (rzlocal->Checked ) {
		row = count/4,col = count%4;
		v.OlePropertyGet("Cells",3+row,3*col+1).OlePropertySet("Value","库位" );
		temptext = "'"+ edtlocal->Text;
		v.OlePropertyGet("Cells",3+row,3*col+2).OlePropertySet("Value",temptext .c_str() );
		count ++;
	}
	if (chckbxShopNum->Checked ) {
		row = count/4,col = count%4;
		v.OlePropertyGet("Cells",3+row,3*col+1).OlePropertySet("Value","店号" );
		temptext = "'"+ edtstore->Text;
		v.OlePropertyGet("Cells",3+row,3*col+2).OlePropertySet("Value",temptext .c_str() );
		count ++;
	}
	if (chckbxPrice->Checked ) {
		row = count/4,col = count%4;
		v.OlePropertyGet("Cells",3+row,3*col+1).OlePropertySet("Value","定价" );
		temptext = "'>="+ edtPrice->Text;
		v.OlePropertyGet("Cells",3+row,3*col+2).OlePropertySet("Value",temptext .c_str() );
		count ++;
	}
	if (chckbxAmount->Checked ) {
		row = count/4,col = count%4;
		v.OlePropertyGet("Cells",3+row,3*col+1).OlePropertySet("Value","数量" );
		temptext = "'>="+ edtAmountLow->Text;
		v.OlePropertyGet("Cells",3+row,3*col+2).OlePropertySet("Value",temptext .c_str() );
		temptext = "'<="+ edtAmountHigh->Text;
		v.OlePropertyGet("Cells",3+row,3*col+3).OlePropertySet("Value",temptext .c_str() );
		count ++;
	}

	if (count == 0) {
		n = 2;
	}
	else if (count%4 == 0) {
		n = 3+count/4;
	}
	else if (count%4 != 0){
		n = 4+count/4;
	}


	int t1= 0;
	for(int q=0;q<dbg->FieldCount ;++q)
	{
		if (dbg->Columns->Items[q]->Visible == true) {
			t1++;
			temptext = "'"+ dbg->Columns ->Items [q]->Title ->Caption;
			v.OlePropertyGet("Cells",1+n,(t1)).OlePropertySet("Value",temptext .c_str() );
			v.OlePropertyGet("Cells",1+n,t1).OleFunction("BorderAround",1,2,1);
		}
	}



	int t2 = dbg->DataSource ->DataSet ->RecordCount ;

	dbg->DataSource ->DataSet ->First();
	for(int   i=2+n;i<=t2+1+n ;i++)
	{
		t1=0;
		for(int j=1;j<dbg->Columns ->Count+1  ;j++)
		{
			if (dbg->Columns->Items[j-1]->Visible == true) {
				t1++;
				temptext = "'"+ dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->DisplayText ;
				v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
				v.OlePropertyGet("Cells",i,t1).OleFunction("BorderAround",1,2,1);
			}
		}
		dbg->DataSource ->DataSet ->Next() ;
	}

	t1= 0;
	for(int q=0;q<dbg->FieldCount ;++q)
	{
		if (dbg->Columns->Items[q]->Visible == true) {
			t1++;
			v.OlePropertyGet("Cells",t2+2+n,t1).OleFunction("BorderAround",1,2,1);
		}
	}
	t1 = 0;
	/*for(int q=0;q<dbg->FieldCount ;++q)
	{
		if (dbg->Columns->Items[q]->Visible == true) {
			t1++;
			temptext = "'"+ dbg->GetFooterValue(0,dbg->Columns->Items[q]);
			v.OlePropertyGet("Cells",t2+2+n,t1).OlePropertySet("Value",temptext .c_str() );
		}
	} */

	return false;
}
//---------------------------------------------------------------------------


void __fastcall TfrmStockInQueryaa::btnExit3Click(TObject *Sender)
{
	/* if (dbgrdStockIn ->DataSource->DataSet->State == dsInactive ) {
		return;
	 }
	 Tfrmqueryprint * frm = new Tfrmqueryprint(this);

	frm->qrcompany->Caption = "国家医药管理局";
	frm->qrtitle->Caption = "库存查询结束报表";
	frm->qruser->Caption = "admin";
	frm->QRLabel3->Caption = DateToStr(Now());
	RPGrid(dbgrdStockIn,frm->qrdg);
	frm->qrreport->Preview();
	delete frm;     */


}
/*
void TfrmStockInQuery::RPGrid(TRzDBGrid *dg,TQRPGrid *PRdg )
{
   int rows,cols;
   rows = dg->DataSource->DataSet->RecordCount ;
   cols = dg->FieldCount ;
   PRdg->Columns = cols;
   PRdg->Rows = rows+2;
   PRdg->Height = (rows+2) * 20;
   String TempStr;
   float totalmayang=0,totalmayang1=0,totalnum=0,totalnum1=0;
   dg->DataSource->DataSet->First();
   for (int i = 0; i < cols; i++) {
	   PRdg->Cells[i][0]->Caption = dg->Columns->Items[i]->Title->Caption     ;
   }

   for (int i = 0; i< dg->DataSource->DataSet->RecordCount ; i++) {

		 for (int j = 0; j  <   dg->FieldCount; j++) {
		  PRdg->Cells[j][i+1]->Caption = dg->Fields[j]->AsAnsiString  ;

		 }
		totalmayang += dg->DataSource->DataSet->FieldByName("kuchunyangmao")->AsFloat ;
		totalmayang1 += dg->DataSource->DataSet->FieldByName("totalmayang")->AsFloat ;
		totalnum += dg->DataSource->DataSet->FieldByName("BookInfoAmount")->AsFloat ;
		totalnum1 += dg->DataSource->DataSet->FieldByName("BookCatalogTotalAmount")->AsFloat ;
		dg->DataSource->DataSet->Next();
	}

	PRdg->Cells[0][rows+1]->Caption = "合计";

	PRdg->Cells[9][rows+1]->Caption =  	FormatFloat("0.00",totalnum);
	PRdg->Cells[10][rows+1]->Caption =  	FormatFloat("0.00",totalmayang);
	PRdg->Cells[11][rows+1]->Caption =  	FormatFloat("0.00",totalnum1);
	PRdg->Cells[12][rows+1]->Caption =  	FormatFloat("0.00",totalmayang1);
}     */

//---------------------------------------------------------------------------


void __fastcall TfrmStockInQueryaa::edtBookNameChange(TObject *Sender)
{
	if (edtBookName->Text != "") {
        chckbxBookName->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStockInQueryaa::edtPriceChange(TObject *Sender)
{
	if (edtPrice->Text != "") {
        chckbxPrice->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStockInQueryaa::edtPressCountClick(TObject *Sender)
{
	if (edtPressCount->Text != "") {
        chckbxPressCount->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStockInQueryaa::edtstoreClick(TObject *Sender)
{
	if (edtstore->Text != "") {
		chckbxShopNum->Checked = true;
		int storage = tblStore->FieldByName("ID")->AsInteger ;
		tbllocal->Active = false;
		tbllocal->Filtered = true;
		tbllocal->Filter = "StgID = " + IntToStr(storage);
		tbllocal->Active = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStockInQueryaa::edtISBNChange(TObject *Sender)
{
	if (edtISBN->Text != "") {
        chckbxISBN->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStockInQueryaa::edtAuthorChange(TObject *Sender)
{
	if (edtAuthor->Text != "") {
        chckbxAuthor->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStockInQueryaa::edtAmountLowChange(TObject *Sender)
{
	if (edtAmountLow->Text != "") {
        chckbxAmount->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStockInQueryaa::edtAmountHighChange(TObject *Sender)
{
	if (edtAmountHigh->Text != "") {
        chckbxAmount->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStockInQueryaa::edtlocalClick(TObject *Sender)
{
	if (edtlocal->Text != "") {
        rzlocal->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStockInQueryaa::edtSupplierClick(TObject *Sender)
{
	if (edtSupplier->Text != "") {
        chckbxSupplier->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStockInQueryaa::edtTypeClick(TObject *Sender)
{
	if (edtType->Text != "") {
        chckbxType->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStockInQueryaa::edtUserDefNumChange(TObject *Sender)
{
	if (edtUserDefNum->Text != "") {
        chckbxUserDefNum->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStockInQueryaa::DBGridEh1TitleClick(TColumnEh *Column)
{
	if (qry1->IsEmpty() ) {
		return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (qry1->Sort == "") {
		qry1->Sort =  Column->FieldName + " ASC";
	}
	else if (qry1->Sort == qusort) {
		qry1->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		qry1->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStockInQueryaa::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStockInQueryaa::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F6) {      //导出
		btnExit2->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 70 ) {    //查询
		btnExit1->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 78 ) {    //最小化
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 81 ) {    //退出
		btnExit4->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==90) {   //恢复窗口
		WindowState = wsNormal  ;
	}
}
//---------------------------------------------------------------------------

