//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "GetBsset.h"
#include "SelectCatalogForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ModalDialog"
#pragma link "RzButton"
#pragma link "RzLabel"
#pragma link "RzDBGrid"
#pragma link "RzEdit"
#pragma link "RzPanel"
#pragma resource "*.dfm"

TfrmSelectCatalog *frmSelectCatalog;
//---------------------------------------------------------------------------
__fastcall TfrmSelectCatalog::TfrmSelectCatalog(TComponent* Owner,TADOConnection* con)
	: TfrmModalDialog(Owner)
	, m_searchMode(0)
	, m_supplierID(-1)
	, m_catalogID(-1)
	, m_bkinfoid(-1)
	, m_ok(false)
{
	dsetQry->Connection = con;
	aquery->Connection = con;
	MutilSelectModal = false;


	SYSSet * BSSET = new SYSSet();

	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = con;
	AnsiString sql;
	sql = "select * from SYS_BSSET where name in('pxnobkinfotuihuo'," ;
	sql = sql + "'mutisupplier','nokucunpxth','wosalereturn','rktuihuoguanli','searchmode')";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();          //	bool Display,Mutisupplier;

	while(!aq->Eof)
	{
		 SYSSet *Note = new SYSSet();
		 Note->Name = aq->FieldByName("NAME")->AsAnsiString;


		 Note->ValueBool = aq->FieldByName("value")->AsBoolean;

		 BSSET->Add(aq->FieldByName("NAME")->AsAnsiString,(TObject*)Note);


	  aq->Next();
	}
	delete aq;
	BSSET->GetSetInfo("pxnobkinfotuihuo");
	nobkinforsale = BSSET->ValueBool;

	//是否显示多供应商
	BSSET->GetSetInfo("mutisupplier");
	Mutisupplier = BSSET->ValueBool;

	//是否允许无批销退货
	BSSET->GetSetInfo("nokucunpxth");
	nokucpxth = BSSET->ValueBool;

	//是否允许无批销退货
	BSSET->GetSetInfo("wosalereturn");
	nowsreturn =  BSSET->ValueBool;

        //是否启用退货监管

		BSSET->GetSetInfo("rktuihuoguanli");
	rktuihuoguanli =  BSSET->ValueBool;
	   //是否是模糊区配
		 BSSET->GetSetInfo("searchmode");
	searchmohu =  BSSET->ValueBool;

	delete BSSET;

	addbkinfo = false;
}
//---------------------------------------------------------------------------
void TfrmSelectCatalog::SetSearchMode(int searchMode, String text)
{

   if (searchMode==6) {       //对定价进行格式化操作

	SearchCont = FormatFloat("0.00",StrToFloat(text));
	m_searchMode =  searchMode;
   }else
   {
	 SearchCont = text.Trim();
	 m_searchMode =  searchMode;
   }
}
 bool TfrmSelectCatalog::shuzhi(AnsiString context)
 {

        char* t;
	char t2;
	String t1,t3,t4;
        bool res;
	t1 = context;//.TrimLeft().TrimLeft()  ;//.TrimRight();//  .TrimLeft()  ;
	int t5=1,i = context.Length()  ;
	for( int j=1;j<=i;j++)
	{
	t3 = t1.SubString(j,1);
	t = t3.t_str();
	Word k = int (t[0])<<8;
	k = k >> 8;

        if (k<=58&&k>=48) {    //数字
                         // t4=t4+t3;
                         res = true;
                         break;

        }
          res = false;
          break;
        }
       return res;
 }
//---------------------------------------------------------------------------
void TfrmSelectCatalog::QryBkInfo()
{
	if (DoModalType != 8) {
    	m_supplierID = -1;
	}

	m_catalogID = -1;
	m_bkinfoid = -1;
	m_ok = false;
	 //1条码 2为自编码 3为书名  4 ISBN 5 作者
	switch (DoModalType) {
	case 1://零售
	case 2://批销
	case 6://零售退货
	case 7://批销退货
	case 12://样/赠书处理
			dsetQry->Active = false;
			dsetQry->CommandType = cmdStoredProc;
			dsetQry->CommandText = "GetSelectBooks";
			dsetQry->Parameters->Clear();
			dsetQry->Parameters->AddParameter();
			dsetQry->Parameters->Items[0]->Name = "@SelectModal" ;
			dsetQry->Parameters->Items[0]->DataType =ftInteger;
			dsetQry->Parameters->Items[0]->Direction =pdInput ;
			dsetQry->Parameters->Items[0]->Value = m_searchMode;

			dsetQry->Parameters->AddParameter();
			dsetQry->Parameters->Items[1]->Name = "@Value" ;
			dsetQry->Parameters->Items[1]->DataType =ftString;
			dsetQry->Parameters->Items[1]->Direction =pdInput ;
			dsetQry->Parameters->Items[1]->Size = 1024;
			dsetQry->Parameters->Items[1]->Value = SearchCont;


			dsetQry->Parameters->AddParameter();
			dsetQry->Parameters->Items[2]->Name ="@stgid"  ;
			dsetQry->Parameters->Items[2]->DataType =ftInteger;
			dsetQry->Parameters->Items[2]->Direction =pdInput ;
			dsetQry->Parameters->Items[2]->Value = m_storageID;

                        dsetQry->Parameters->AddParameter();
			dsetQry->Parameters->Items[3]->Name ="@DoModalType"  ;
			dsetQry->Parameters->Items[3]->DataType =ftInteger;
			dsetQry->Parameters->Items[3]->Direction =pdInput ;
			dsetQry->Parameters->Items[3]->Value = DoModalType;

			try
			{
			dsetQry->Active = true;
			}catch(...)
			{
				dsetQry->Active = false;

				ModalResult = mrCancel;

			}

			m_searchMode = 10;//置为无效的，以避免与后面的代码冲突
		 break;

	case 9://库存调整
	case 10://虚拟盘点
			sql = " select BS_BookCatalog.ID,BS_BookCatalog.Author,STK_BookInfo.ID as bkinfoid,BS_BookCatalog.Name,BS_BookCatalog.Barcode,BS_BookCatalog.UserDefCode,BS_BookCatalog.ISBN,'' SupplierName,STK_BookInfo.Amount,STK_BookstackInfo.Name as BkstackName,BS_BookCatalog.Price ,BS_PressInfo.fullname,STK_BookstackInfo.Name as BKStName,BS_BookCatalog.year,BS_BookCatalog.duokantext,BS_BookCatalog.Presscount,STK_BookstackInfo.ID as BSKID "
			  " from BS_BookCatalog  join STK_BookInfo on STK_BookInfo.BkcatalogID=BS_BookCatalog.ID "

			  " join STK_BookstackInfo on STK_BookInfo.BkstackID=STK_BookstackInfo.ID "
			  " left join BS_PressInfo ON BS_BookCatalog.PressID = BS_PressInfo.ID "
			  " where   BS_BookCatalog.Unavailable=1 and STK_BookstackInfo.StgID = " + IntToStr(m_storageID) ;

		//if ((DoModalType == 1 || DoModalType == 2) && !Display) {
		//	sql = sql + " and STK_BookInfo.amount > 0 ";
		//}

		//this->Caption = "多货源选择";
		break;
	case 3://入库
	case 4://订单
	case 5://采购
	case 8://入库退货
	case 11://智能入库
		//sql = "select BS_BookCatalog.ID,BS_BookCatalog.Author,BS_BookCatalog.Name,BS_BookCatalog.Barcode,BS_BookCatalog.UserDefCode,BS_BookCatalog.ISBN,BS_BookCatalog.Price ,BS_PressInfo.fullname,BS_BookCatalog.year,BS_BookCatalog.duokantext,BS_BookCatalog.Presscount "
		//	  " from BS_BookCatalog left join BS_PressInfo ON BS_BookCatalog.PressID = BS_PressInfo.ID "
		//	  " where   BS_BookCatalog.Unavailable=1" ;
		//this->Caption = "一号多书";

		sql = " select BS_BookCatalog.ID,BS_BookCatalog.Author,STK_BookInfo.ID as bkinfoid,BS_BookCatalog.Name,BS_BookCatalog.Barcode,BS_BookCatalog.UserDefCode,BS_BookCatalog.ISBN,'' SupplierName,STK_BookInfo.Amount,BS_BookCatalog.Price ,BS_PressInfo.fullname,BS_BookCatalog.year,BS_BookCatalog.duokantext,BS_BookCatalog.Presscount "
			  " from BS_BookCatalog left join (select * from STK_BookInfo where stgid = " + IntToStr(m_storageID) + ") as STK_BookInfo on STK_BookInfo.BkcatalogID=BS_BookCatalog.ID "

			  " left join BS_PressInfo ON BS_BookCatalog.PressID = BS_PressInfo.ID "
			  " where   BS_BookCatalog.Unavailable=1 ";
		if ((DoModalType == 8)&&(rktuihuoguanli)) {
		   //	sql = sql + " and STK_BookInfo.supplierid = " + IntToStr(m_supplierID);
		}


		dbgrdQry->Columns->Items[12]->Visible = false;
		break;
	default:
		;
	}
	sql1 = "select BS_BookCatalog.ID,BS_BookCatalog.Author,BS_BookCatalog.Name,BS_BookCatalog.Barcode,BS_BookCatalog.UserDefCode,BS_BookCatalog.ISBN,BS_BookCatalog.Price ,BS_PressInfo.fullname,BS_BookCatalog.year,BS_BookCatalog.duokantext,BS_BookCatalog.Presscount "
			  " from BS_BookCatalog left join BS_PressInfo ON BS_BookCatalog.PressID = BS_PressInfo.ID "
			  " where   BS_BookCatalog.Unavailable=1 " ;
	if (qikan) {
		sql = sql + " and BS_BookCatalog.PressCount like '%" + qikanhao + "%' and BS_BookCatalog.type = 1 ";
		sql1 = sql1 + " and BS_BookCatalog.PressCount like '%" + qikanhao + "%' and BS_BookCatalog.type = 1 ";
		dbgrdQry->Columns->Items[10]->Visible = true;
		dbgrdQry->Columns->Items[9]->Title->Caption = "刊号";
		dbgrdQry->Columns->Items[9]->Width = 50;
		dbgrdQry->Columns->Items[8]->Visible = true;
	}
	switch (m_searchMode)
	{
	case 1:
        case 2:
               if(shuzhi(LeftStr(SearchCont,1)))
			   {
					if (searchmohu) {
							if (SearchCont.Length()==13 || SearchCont.Length() == 10) {
									SearchCont = SearchCont.Delete(SearchCont.Length(),1);
							}else if (SearchCont.Length()>13) {
								  SearchCont = SearchCont.SubString(0,13);
							}

						sql = sql + "  and (BS_BookCatalog.Barcode like '%" + SearchCont + "%' or BS_BookCatalog.ISBN like '%" + SearchCont + "%') ";
						sql1 = sql1 + "  and (BS_BookCatalog.Barcode like '%" + SearchCont + "%' or BS_BookCatalog.ISBN like '%" + SearchCont + "%') ";
					}else
					{
						if (SearchCont.Length()>13) {
									  SearchCont = SearchCont.SubString(0,13);
						}
					   sql = sql + "  and (BS_BookCatalog.Barcode = '" + SearchCont + "' or BS_BookCatalog.ISBN = '" + SearchCont + "') ";
					   sql1 = sql1 + "  and (BS_BookCatalog.Barcode = '" + SearchCont + "' or BS_BookCatalog.ISBN = '" + SearchCont + "') ";
					}

					if (!Mutisupplier && DoModalType!=3 && DoModalType!=4 && DoModalType!=5 && DoModalType!=8 && DoModalType!=11) {
						   //	sql = sql + " ) AS A "  ;

                    }
                    dsetQry->Active = false;
					dsetQry->CommandText = sql;
                    try {
                            dsetQry->Active = true;
                            if (dsetQry->RecordCount == 0 && DoModalType == 7 && nokucpxth) {
                                    addbkinfo = true;
                                    dsetQry->Active = false;
                                    dsetQry->CommandText = sql1;
									dsetQry->Active = true;
                            }
                    } catch (...) {
                    }
                }else
                 {

                    sql = sql + "  and BS_BookCatalog.UserDefCode like '%" + SearchCont + "%'";
                    sql1 = sql1 + "  and BS_BookCatalog.UserDefCode like '%" + SearchCont + "%'";
                    if (!Mutisupplier && DoModalType!=3 && DoModalType!=4 && DoModalType!=5 && DoModalType!=8 && DoModalType!=11) {
                            sql = sql + " ) AS A " ;

                    }
                    dsetQry->Active = false;
                    dsetQry->CommandText = sql;
                    try {
                            dsetQry->Active = true;
                            if (dsetQry->RecordCount == 0 && DoModalType == 7 && nokucpxth) {
                                    addbkinfo = true;
                                    dsetQry->Active = false;
                                    dsetQry->CommandText = sql1;
                                    dsetQry->Active = true;
                            }
                    } catch (...) {
                    }
		}
                break;
	case 3://书名

		sql = sql +  " and  BS_BookCatalog.Name like '%" + SearchCont + "%'";
		sql1 = sql1 +  " and  BS_BookCatalog.Name like '%" + SearchCont + "%'";

		if (!Mutisupplier && DoModalType!=3 && DoModalType!=4 && DoModalType!=5 && DoModalType!=8 && DoModalType!=11) {
			sql = sql + " ) AS A " ;

		}
		dsetQry->Active = false;
		dsetQry->CommandText = sql;
		try {
			dsetQry->Active = true;
			if (dsetQry->RecordCount == 0 && DoModalType == 7 && nokucpxth) {
				addbkinfo = true;
				dsetQry->Active = false;
				dsetQry->CommandText = sql1;
				dsetQry->Active = true;
			}
		} catch (...) {
		}
		break;
	case 4: //ISBN

		sql = sql + "  and BS_BookCatalog.ISBN='" + SearchCont + "'";
		sql1 = sql1 + "  and BS_BookCatalog.ISBN='" + SearchCont + "'";

		if (!Mutisupplier && DoModalType!=3 && DoModalType!=4 && DoModalType!=5 && DoModalType!=8 && DoModalType!=11) {
			sql = sql + " ) AS A " ;

		}

		dsetQry->Active = false;
		dsetQry->CommandText = sql;
		try {
			dsetQry->Active = true;
			if (dsetQry->RecordCount == 0 && DoModalType == 7 && nokucpxth) {
				addbkinfo = true;
				dsetQry->Active = false;
				dsetQry->CommandText = sql1;
				dsetQry->Active = true;
			}
		} catch (...) {
		}
		break;
	case 5://作者

		sql = sql +  " and BS_BookCatalog.Author like'%" + SearchCont + "%'";
		sql1 = sql1 +  " and BS_BookCatalog.Author like'%" + SearchCont + "%'";

		if (!Mutisupplier && DoModalType!=3 && DoModalType!=4 && DoModalType!=5 && DoModalType!=8 && DoModalType!=11) {
			sql = sql + " ) AS A " ;

		}
		dsetQry->Active = false;
		dsetQry->CommandText = sql;
		try {
			dsetQry->Active = true;
			if (dsetQry->RecordCount == 0 && DoModalType == 7 && nokucpxth) {
				addbkinfo = true;
				dsetQry->Active = false;
				dsetQry->CommandText = sql1;
				dsetQry->Active = true;
			}
		} catch (...) {
		}
		break;
	case 6://定价

		sql = sql +  " and BS_BookCatalog.price=" + SearchCont;
		sql1 = sql1 +  " and BS_BookCatalog.price=" + SearchCont;

		if (!Mutisupplier && DoModalType!=3 && DoModalType!=4 && DoModalType!=5 && DoModalType!=8 && DoModalType!=11) {
			sql = sql + " ) AS A ";

		}

		dsetQry->Active = false;
		dsetQry->CommandText = sql;
		try {
			dsetQry->Active = true;
			if (dsetQry->RecordCount == 0 && DoModalType == 7 && nokucpxth) {
				addbkinfo = true;
				dsetQry->Active = false;
				dsetQry->CommandText = sql1;
				dsetQry->Active = true;
			}
		} catch (...) {
		}
		break;
	default:
		break;
	}


	if (dsetQry->Active && dsetQry->RecordCount > 1)//查找到多条记录
	{
	       //	dbgrdQry->SetFocus();
		m_ok = true;
		findbook = true;
                findbooks = 3;
	}
	else if (dsetQry->Active && dsetQry->RecordCount == 1)//查找到一条记录
	{
		if (DoModalType == 1 || DoModalType == 2 || DoModalType == 6 || (DoModalType == 7 && !addbkinfo) ||DoModalType==9 ||DoModalType==10 ||DoModalType==12) {
			BSKid =  dsetQry->FieldByName("BSKID")->AsInteger ;
			BKinfoid = dsetQry->FieldByName("bkinfoid")->AsInteger;
			Amount =  dsetQry->FieldByName("Amount")->AsInteger;
			m_bkinfoid =  dsetQry->FieldByName("bkinfoid")->AsInteger;
		   //	m_supplierID = dsetQry->FieldByName("SupplierID")->AsInteger;
		}
		m_ok = true;
		findbook = true;
        findbooks = 1;
	      //	PostMessage(Handle, WM_CLOSE, 0, 0);
	}
	else if (dsetQry->Active && dsetQry->RecordCount < 1)//未找到记录
	{
		if (DoModalType == 1 || DoModalType == 2 || DoModalType == 6 || DoModalType == 7)  {

                ShowMsg(Handle ,"该书未作过入库或调拨操作，无库存记录！",3);
		}

		m_ok = false;
		findbook = false;
                findbooks = 0 ;
	       //	PostMessage(Handle, WM_CLOSE, 0, 0);


	}
	else//查找出错
	{
			m_ok = false;
		findbook = false;
                findbooks = 0 ;
                findbooks = -1;
	}

	if (DoModalType == 1 || DoModalType == 2 || DoModalType == 6 || (DoModalType == 7 && !addbkinfo) ||DoModalType==9|| DoModalType ==10 ||DoModalType ==12) {
		dbgrdQry->Columns->Items[12]->Visible = true;
		dbgrdQry->Columns->Items[12]->Field = dsetQry->FieldByName("BKStName");
	}
	//edgried->SetFocus();
}
//---------------------------------------------------------------------------
void TfrmSelectCatalog::Init(LandInfo* li)
{
	TfrmModalDialog::Init(li);
}

//---------------------------------------------------------------------------
void TfrmSelectCatalog::Qry()
{
    AnsiString sql;
	if (dsetQry->Active && dsetQry->RecordCount > 1)//查找到多条记录
	{
		dbgrdQry->SetFocus();
		m_ok = true;
		findbook = true;
	}
	else if (dsetQry->Active && dsetQry->RecordCount == 1)//查找到一条记录
	{
		if (DoModalType == 1 || DoModalType == 2 || DoModalType == 6 || (DoModalType == 7 && !addbkinfo) ||DoModalType==9 ||DoModalType==10 ||DoModalType==12) {
			BSKid =  dsetQry->FieldByName("BSKID")->AsInteger ;
			BKinfoid = dsetQry->FieldByName("bkinfoid")->AsInteger;
			Amount = dsetQry->FieldByName("Amount")->AsInteger ;
			m_bkinfoid =  dsetQry->FieldByName("bkinfoid")->AsInteger;
		}
		m_ok = true;
		findbook = true;
		PostMessage(Handle, WM_CLOSE, 0, 0);
		//ModalResult = mrOk;
	}
	else if (dsetQry->Active && dsetQry->RecordCount < 1)//未找到记录
	{
		m_ok = false;
		findbook = false;
		PostMessage(Handle, WM_CLOSE, 0, 0);
	}
	else//查找出错
	{

	}
}

//---------------------------------------------------------------------------
void TfrmSelectCatalog::GetSelectResult(int& Bkinfoid, int& BkcatalogID)
{
	Bkinfoid = m_bkinfoid;
	BkcatalogID = m_catalogID;
}

//---------------------------------------------------------------------------
void __fastcall TfrmSelectCatalog::dbgrdQryKeyPress(TObject *Sender, wchar_t &Key)
{
	//
	if (Key == '\r')
	{
		if (DoModalType == 1 || DoModalType == 2 || DoModalType == 6 || (DoModalType == 7 && !addbkinfo) ||DoModalType == 9||DoModalType==10 || DoModalType==12) {
			BSKid =  dsetQry->FieldByName("BSKID")->AsInteger ;
			BKinfoid = dsetQry->FieldByName("bkinfoid")->AsInteger;
			Amount = dsetQry->FieldByName("Amount")->AsInteger ;
			m_bkinfoid =  dsetQry->FieldByName("bkinfoid")->AsInteger;
		   //	m_supplierID = dsetQry->FieldByName("SupplierID")->AsInteger;
		}
		ModalResult = mrOk;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmSelectCatalog::dsetQryAfterScroll(TDataSet *DataSet)
{
	//
	m_catalogID = DataSet->FieldByName("ID")->AsInteger;
	if (DoModalType== 1 || DoModalType == 2 || DoModalType== 6 || (DoModalType == 7 && !addbkinfo) || DoModalType==9||DoModalType==10) {
   //	 m_supplierID=0; //	m_supplierID = DataSet->FieldByName("SupplierID")->AsInteger;
		m_bkinfoid =  DataSet->FieldByName("bkinfoid")->AsInteger;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmSelectCatalog::dsetQryAfterOpen(TDataSet *DataSet)
{
	//
	m_catalogID = DataSet->FieldByName("ID")->AsInteger;
	if (DoModalType == 1 || DoModalType == 2 || DoModalType== 6 || (DoModalType == 7 && !addbkinfo) || DoModalType==9 ||DoModalType==10 || DoModalType==12) {
	   //	m_supplierID = DataSet->FieldByName("SupplierID")->AsInteger;
		m_bkinfoid =  DataSet->FieldByName("bkinfoid")->AsInteger;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmSelectCatalog::edtSearchKeyPress(TObject *Sender, wchar_t &Key)
{
	//
	if (Key == '\r')
	{
		QryBkInfo();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmSelectCatalog::FormClose(TObject *Sender, TCloseAction &Action)
{
	if (dsetQry->Active == true && dsetQry->RecordCount == 1) {
		ModalResult = mrOk;
	}
	dsetQry->Active = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSelectCatalog::FormShow(TObject *Sender)
{
       //	SelectAll = false;
       //	QryBkInfo();
}
//---------------------------------------------------------------------------

void __fastcall TfrmSelectCatalog::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmSelectCatalog::BtnselectallClick(TObject *Sender)
{
	int Recount;
	Recount = dsetQry->RecordCount ;
	//SupplierID = new int[Recount];
	BkcatalogiD = new int[Recount];
	BKSKid = new int[Recount];
	stkbkid = new int[Recount];
	skAmount = new int[Recount];
	lengthint = Recount;
	dsetQry->First();
	for (int i = 0; i < dsetQry->RecordCount  ; i++) {

		if (DoModalType == 1 || DoModalType == 2 || DoModalType== 6 || (DoModalType == 7 && !addbkinfo)||DoModalType==9 ||DoModalType==10 ||DoModalType==12) {
			//SupplierID[i] = dsetQry->FieldByName("SupplierID")->AsInteger;
			BKSKid[i] =  dsetQry->FieldByName("BSKID")->AsInteger ;
			stkbkid[i] = dsetQry->FieldByName("bkinfoid")->AsInteger;
			skAmount[i] = dsetQry->FieldByName("Amount")->AsInteger;
		}

		BkcatalogiD[i] = dsetQry->FieldByName("ID")->AsInteger;
		dsetQry->Next();
	}
	SelectAll = true;
	ModalResult = mrOk;
}

//---------------------------------------------------------------------------
void __fastcall TfrmSelectCatalog::BtnPropertiesClick(TObject *Sender)
{
	if (DoModalType == 1 || DoModalType == 2 || DoModalType == 6 || (DoModalType == 7 && !addbkinfo)||DoModalType == 9||DoModalType==10 || DoModalType == 12) {
		BSKid =  dsetQry->FieldByName("BSKID")->AsInteger ;
		BKinfoid = dsetQry->FieldByName("bkinfoid")->AsInteger;
		Amount = dsetQry->FieldByName("Amount")->AsInteger ;
	   //	m_supplierID = dsetQry->FieldByName("SupplierID")->AsInteger;
		m_bkinfoid = dsetQry->FieldByName("bkinfoid")->AsInteger;
	}

	if (MutilSelectModal) {
		ModalResult = mrCancel ;
	}else
	{
		ModalResult = mrOk ;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmSelectCatalog::dbgrdQryDblClick(TObject *Sender)
{
	//	 ModalResult = mrOk;
	int supplierid;
	int cataid;
	if (MutilSelectModal) {
		if (DoModalType == 1 || DoModalType == 2 || DoModalType == 6 || (DoModalType == 7 && !addbkinfo)||DoModalType == 9||DoModalType==10|| DoModalType==12) {
			//supplierid = dsetQry->FieldByName("SupplierID")->AsInteger;
			BSKid =  dsetQry->FieldByName("BSKID")->AsInteger ;
			BKinfoid = dsetQry->FieldByName("bkinfoid")->AsInteger;
			Amount =  dsetQry->FieldByName("Amount")->AsInteger;
		}

		cataid = dsetQry->FieldByName("ID")->AsInteger;
		switch (DoModalType) {
			case 1:    //零售模式
			//	Retailfrm = (TfrmretailMng*)frm;
				/*if (!Retailfrm->retailreturn(cataid)) {
					return;
				} */
				if (!Retailfrm->saleenable(BKinfoid) ) {
					return;
				}
				Retailfrm->Amount = Amount;
				Retailfrm->cbbkstackID->ItemIndex = Retailfrm->cbbkstackID->Items->IndexOfObject((TObject*)BSKid);
				Retailfrm->AddNote(BKinfoid,cataid,0);
			break;
			case 2: //批销
				/*if (!Wholefrm->retailreturn(cataid) ) {
					return;
				}*/
				if (!Wholefrm->saleenable(BKinfoid) ) {
					return;
				}
				Wholefrm->AddNote(supplierid,cataid,BKinfoid,0);

			break;
			case 3: //入库
				Storagefrm->AddNote(-1,cataid);
			break;
			case 4: //订单
				if (order->chongfutishi(cataid) ) {
					order->AddNote(0,cataid) ;
				}
			break;
			case 5://采购
				Procurefrm->AddNote(supplierid,cataid);
			break;
			case 6: //零售退货
				if (!RetailReturnfrm->retailreturn(cataid)) {
					return;
				}
				if (!RetailReturnfrm->saleenable(BKinfoid) ) {
					return;
				}
				//RetailReturnfrm->cbbkstackID->ItemIndex = RetailReturnfrm->cbbkstackID->Items->IndexOfObject((TObject*)BSKid);
				RetailReturnfrm->AddNote(supplierid,cataid,0);
			break;
			case 7: //批销退货
				if (!WholeReturnfrm->retailreturn(cataid) ) {
					return;
				}
				if (!addbkinfo) {
					if (!WholeReturnfrm->saleenable(BKinfoid) ) {
						return;
					}
					//WholeReturnfrm->cbbkstackID->ItemIndex = WholeReturnfrm->cbbkstackID->Items->IndexOfObject((TObject*)BSKid);
					WholeReturnfrm->AddNote(supplierid,cataid,BKinfoid,0);
				}
				else
				{
					//WholeReturnfrm->AddNote(0,cataid);
				}

			break;
			case 8: //入库退货
				StorageReturnfrm->AddNote(-1,cataid);
			break;
			case 9://  库存调整
				StockAdjust->AddNote(supplierid,cataid,BKinfoid,Amount);
			break;
			/*case 10: //虚拟盘点
				stockcheckxuyi->AddNote(supplierid,cataid,BSKid,BKinfoid);
			break;   */
			case 12: //样/赠书处理
				Ysbooksale->AddNote(BKinfoid,cataid);
			break;
			default:
			;
		}
	}
	else
	{
		if (DoModalType == 1 || DoModalType == 2 || DoModalType == 6 || (DoModalType == 7 && !addbkinfo)||DoModalType == 9||DoModalType==10 || DoModalType == 12) {
			BSKid =  dsetQry->FieldByName("BSKID")->AsInteger ;
			BKinfoid = dsetQry->FieldByName("bkinfoid")->AsInteger;
			Amount =  dsetQry->FieldByName("Amount")->AsInteger;
		   //	m_supplierID = dsetQry->FieldByName("SupplierID")->AsInteger;
		}
		ModalResult = mrOk ;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmSelectCatalog::BtnWeekViewClick(TObject *Sender)
{
	MutilSelectModal = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSelectCatalog::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F4)
	{
		BtnProperties->Click();
	}
	if (Key == VK_F6) {
		BtnWeekView->Click();
	}
	if (Key == VK_F7) {
		Btnselectall->Click();
	}
}
//---------------------------------------------------------------------------

void TfrmSelectCatalog::fiter()
{
	AnsiString filter,filter1,filter2;
	if (chnianji->Checked ) {
    	switch (rg1->ItemIndex) {
			case 0:
				filter = " Name like '%一年级%'";
				filter2 = " Name like '%1年级%'";
			break;
			case 1:
				filter = " Name like '%二年级%'";
				filter2 = " Name like '%2年级%'";
			break;
			case 2:
				filter = " Name like '%三年级%'";
				filter2 = " Name like '%3年级%'";
			break;
			case 3:
				filter = " Name like '%四年级%'";
				filter2 = " Name like '%4年级%'";
			break;
			case 4:
				filter = " Name like '%五年级%'";
				filter2 = " Name like '%5年级%'";
			break;
			case 5:
				filter = " Name like '%六年级%'";
				filter2 = " Name like '%6年级%'";
			break;
			case 6:
				filter = " Name like '%七年级%'";
				filter2 = " Name like '%7年级%'";
			break;
			case 7:
				filter = " Name like '%八年级%'";
				filter2 = " Name like '%8年级%'";
			break;
			case 8:
				filter = " Name like '%九年级%'";
				filter2 = " Name like '%9年级%'";
			break;
		default:
			;
		}
	}
	if (chkemu->Checked ) {
		switch (rg2->ItemIndex) {
			case 0:
				filter1 = " Name like '%语文%'";
			break;
			case 1:
				filter1 = " Name like '%数学%'";
			break;
			case 2:
				filter1 = " Name like '%英语%'";
			break;
			case 3:
				filter1 = " Name like '%历史%'";
			break;
			case 4:
				filter1 = " Name like '%地理%'";
			break;
			case 5:
				filter1 = " Name like '%政治%'";
			break;
			case 6:
				filter1 = " Name like '%物理%'";
			break;
			case 7:
				filter1 = " Name like '%化学%'";
			break;
			case 8:
				filter1 = " Name like '%生物%'";
			break;
		default:
			;
		}
	}
	if (filter == "") {
		filter =  filter1;
	}
	else if (filter1 == "") {
		filter = filter + " or " + filter2;
	}
	else
	{
		filter = "(" + filter + " and " + filter1 + ") or (" + filter2 + " and " + filter1 + ")";
	}
	if (chuserdef->Checked ) {
		if (filter != "") {
			filter = filter + " and UserDefCode like '%" + eduserdef->Text + "%' ";
		}
		else
		{
			filter = "UserDefCode like '%" + eduserdef->Text + "%' ";
		}
	}
	if (chprice->Checked ) {
		if (filter != "") {
			filter = filter + " and Price = " + edprice->Text ;
		}
		else
		{
			filter = "Price = " + edprice->Text ;
		}
	}
	if (chauthor->Checked ) {
    	if (filter != "") {
			filter = filter + " and Author like '%" + edauthor->Text + "%'";
		}
		else
		{
			filter = "Author like '%" + edauthor->Text + "%'";
		}
	}
	try {
    	dsetQry->Active = false;
		dsetQry->Filtered = true;
		dsetQry->Filter =  filter;
		dsetQry->Active = true;
	} catch (...) {
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmSelectCatalog::rg1Click(TObject *Sender)
{
	chnianji->Checked = true;
	fiter();
}
//---------------------------------------------------------------------------

void __fastcall TfrmSelectCatalog::rg2Click(TObject *Sender)
{
    chkemu->Checked = true;
	fiter();
}
//---------------------------------------------------------------------------

void __fastcall TfrmSelectCatalog::chnianjiClick(TObject *Sender)
{
	fiter();
}
//---------------------------------------------------------------------------

void __fastcall TfrmSelectCatalog::chkemuClick(TObject *Sender)
{
	fiter();
}
//---------------------------------------------------------------------------

void __fastcall TfrmSelectCatalog::eduserdefChange(TObject *Sender)
{
	if (eduserdef->Text != "") {
		chuserdef->Checked = true;
	}
	else
	{
		chuserdef->Checked = false;
	}

}
//---------------------------------------------------------------------------

void __fastcall TfrmSelectCatalog::edpriceChange(TObject *Sender)
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

void __fastcall TfrmSelectCatalog::edauthorChange(TObject *Sender)
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

void __fastcall TfrmSelectCatalog::edpriceKeyPress(TObject *Sender, wchar_t &Key)

{
	if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key !='.')&&(Key != '\b')) {
	  	Key = NULL;
	}
	if (Key == '\r') {
		fiter();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmSelectCatalog::edauthorKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		fiter();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmSelectCatalog::dbgrdQryTitleClick(TColumn *Column)
{
	if (dsetQry->IsEmpty() ) {
    	return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (dsetQry->Sort == "") {
		dsetQry->Sort =  Column->FieldName + " ASC";
	}
	else if (dsetQry->Sort == qusort) {
		dsetQry->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		dsetQry->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmSelectCatalog::eduserdefKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		fiter();
	}
}
void TfrmSelectCatalog::disableduoxuan()
{



          BtnWeekView->Visible=false;
          Btnselectall->Visible=false;


}
//---------------------------------------------------------------------------

