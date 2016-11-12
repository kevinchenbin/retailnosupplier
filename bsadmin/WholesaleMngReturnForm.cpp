//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "WholesaleMngReturnForm.h"
#include "NoteCode.h"
#include "QryNoteCodeForm.h"
#include "SetNotesForm.h"
#include "mytrace.h"
//#include "SelectCustomerForm.h"
#include "RecMoneyForm.h"
#include "Print.h"
//#include "customer\customer.h"
#include "SelectCatalogForm.h"
//#include "bsprint.h"
#include "..\supplier\detailemessage.h"
#include "UnitSelectClient.h"
#include "bookQuery.h"
#include "QueryDanHao.h"
#include "Addsyslog.h"
#include "UnitClient.h"
#include   <math.h>
#include "Unitorderquery.h"
#include "Unitorderquery.h"
#include "bookhistory.h"
#include "GetBsset.h"
#include "Import.h"
#include "Unitmuilprint.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "MDIChild"
#pragma link "RzButton"
#pragma link "RzDBCmbo"
#pragma link "RzDBEdit"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzPanel"
#pragma link "RzDBGrid"
#pragma link "RzDBLbl"
#pragma link "RzCommon"
#pragma link "RzDBLook"
#pragma link "RzRadGrp"
#pragma link "RzRadChk"
#pragma link "RzDBDTP"
#pragma link "RzDTP"
#pragma resource "*.dfm"
TfrmWholesaleReturnMng *frmWholesaleReturnMng;
//---------------------------------------------------------------------------
__fastcall TfrmWholesaleReturnMng::TfrmWholesaleReturnMng(TComponent* Owner)
	: TfrmMDIChild(Owner)
	, m_catalogSearchMode(0)
	, m_bsmode(BSUnknown)
	, m_opmode(OPUnknown)
	, m_supplierID(-1)
{
	m_module = MTWsaleMng;
	this->WindowState = wsMaximized ;
	ClientID = 1;
	changehead = 0;
	scroll = 0;
}
//---------------------------------------------------------------------------
void TfrmWholesaleReturnMng::Init(LandInfo* li)
{
	TfrmMDIChild::Init(li);
	linfo.app = li->app ;
	linfo.con = li->con ;
	linfo.userID = li->userID ;
	linfo.UserName = li->UserName ;
	linfo.storageID = li->storageID ;
	linfo.FormatStr = li->FormatStr ;
	lblOpName->Caption = m_opName;
	cmdAddNtHeader->Connection = m_con;
	spQryNtHeader->Connection = m_con;
	spQryNtHeader1->Connection = m_con;
	cmdUpdateNtHeader->Connection = m_con;
	cmdAddNote->Connection = m_con;
	cmdUpdataamount->Connection = m_con;
	cmdUpdateNote->Connection = m_con;
	cmdDelNote->Connection = m_con;
	cmdDelNtHeader->Connection = m_con;
	cmdBatchDelNote->Connection = m_con;
	cmdBatchUpdateNote->Connection = m_con;
	cmdResetNtHeader->Connection = m_con;
	spQryNtHeader1->Connection = m_con;
	cmdDelNote->Connection = m_con;
	dsetVendor->Connection = m_con;
	dsetStaff->Connection = m_con;
	dsetLkpVendor->Connection = m_con;
	dsetBkstack->Connection = m_con;
	qryrecord->Connection = m_con;
	adospcopy->Connection = m_con;
	spcopy->Connection = m_con;
	spsave->Connection = m_con;
	querydan->Connection = m_con;
	dsetBkstack->CommandText = "select ID, Name from STK_BookstackInfo where stgid = " + IntToStr(m_storageID) ;
	dsetBkstack->Active = true;
          QFClientTiaoJian=" 1=1 ";
        QFSupplierTiaoJian=" 1=1 ";
        if (li->qfclient) {
           QFClientTiaoJian=" stgid="+IntToStr(m_storageID);
        }
        qfclient= li->qfclient;
         dsetVendor->CommandText=" select ID,Name,salesman from CUST_CustomerInfo where   Type in (2,3) and customerstate =1 and "+QFClientTiaoJian+" order by ID";
	dsetVendor->Active = true;
	dsetStaff->Active = true;
	bearsaledataset->Connection = m_con;
	bearsaledataset->Active = true;
	dsetStaff->Connection = m_con;
	sptuihuo1->Connection = m_con;
	query->Connection = m_con;
	dtGetTotal->Connection= m_con;
	dsetstkamount->Connection =m_con;
	ChangeCatalogSearchMode();
	//ChangeBsmode(BSNoteSendback);
	//退货密码

	SYSSet * BSSET = new SYSSet();
	AnsiString sql;



        sql = "select * from SYS_StaffInfo where stgID = " + IntToStr(m_storageID) + " and Career = 2";
        query->Close();
        query->SQL->Clear();
        query->SQL->Add(sql);
        query->Open();
        while(!query->Eof)
	{
           dblkpcbbStaffID->AddItem(query->FieldByName("name")->AsAnsiString,(TObject*)query->FieldByName("ID")->AsInteger);
           query->Next();
        }

	sql = "select name,value,bk from SYS_BSSET where name in('pxtuihuousepassword','wosaleday','checkedview', ";
	sql = sql + "'WsalelDiscountChange','salexiaoshudian','xianchangrecive','changeDanHaoDisplay'";
	sql = sql + ",'pxallclientdetail','pxdeleteusepassword','pxfindusepassword','pxusechange','wsalesametuihuotishi');";


	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	//	tuihuo  = query->FieldByName("value")->AsBoolean ;
	while(!query->Eof)
	{
		SYSSet *Note = new SYSSet();
		Note->Name = query->FieldByName("NAME")->AsAnsiString;

		if (query->FieldByName("NAME")->AsAnsiString=="changeDanHaoDisplay" ||
			query->FieldByName("NAME")->AsAnsiString=="salexiaoshudian" )
			Note->ValueStr = query->FieldByName("bk")->AsAnsiString;
		else
			Note->ValueBool = query->FieldByName("value")->AsBoolean;

		BSSET->Add(query->FieldByName("NAME")->AsAnsiString,(TObject*)Note);
		query->Next();
	}

	BSSET->GetSetInfo("pxtuihuousepassword");
	if (BSSET->ValueBool) {
    	if (!CheckOperateAuthority()) {
			Close();
			return;
		}
	}

	ChangeOpmode(OPAddNtHeader);
	addnotereturnvalue = 0;


	 BSSET->GetSetInfo("wosaleday");
	/*if (BSSET->ValueBool ) {
		dgrecord->Visible = true;
	}
	else
	{
		dgrecord->Visible = false;
	} */


	BSSET->GetSetInfo("WsalelDiscountChange");

	if (BSSET->ValueBool ) {
			dbnbedtDiscount->Enabled = true;
	}
	else
	{
		dbnbedtDiscount->Enabled = false;
	}


	BSSET->GetSetInfo("salexiaoshudian");
	format = "###,###,##" + BSSET->ValueStr;
	dbnbedt3->DisplayFormat = format;
	dbnbedt4->DisplayFormat = format;

         totalyingshou->DisplayFormat = format;
	BSSET->GetSetInfo("xianchangrecive");
	if (BSSET->ValueBool) {
		RzToolButton2->Enabled = true;
	}
	else
	{
		RzToolButton2->Enabled = false;
	}

	sql = "select ID,Name from SYS_StorageInfo where id  = " + IntToStr(m_storageID) ;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	labtitle->Caption = query->FieldByName("Name")->AsString.Trim();
	dblkpcbbVendorID->KeyValue = dsetVendor->FieldByName("ID")->AsInteger ;
	ReadClient();

	sql = "select wsprinttitle,wscontact,wstel,wsaddress,wsprintbk from sys_printtitle where stgid = " + IntToStr(m_storageID);
    query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();

	pxbk = query->FieldByName("wsprintbk")->AsAnsiString ;
	printtitle = query->FieldByName("wsprinttitle")->AsAnsiString ;
	contact = query->FieldByName("wscontact")->AsAnsiString ;
	tel = query->FieldByName("wstel")->AsAnsiString ;
	address = query->FieldByName("wsaddress")->AsAnsiString ;


	 BSSET->GetSetInfo("changeDanHaoDisplay");
	 ChangeDisplay  = BSSET->ValueBool ;

	if (ChangeDisplay) {
	  editdanhao->Visible = true;
	  dbedtWsaleNtCode->Visible = false;
	   DBNav->Visible = true;
	   dgrecord->Columns->Items[1]->Visible = true;
	   dgrecord->Columns->Items[0]->Visible = false;
	}else
	{
	  editdanhao->Visible = false;
	  dbedtWsaleNtCode->Visible = true;
	  /*Sbutfirst->Visible = true;
		Sbutbefore->Visible = true;
		Sbutnext->Visible = true;
		Sbutend->Visible = true;
		DBNav->Visible = false; */
		dgrecord->Columns->Items[1]->Visible = false;
		dgrecord->Columns->Items[0]->Visible = true;
	}

	//所有客户历史明细
	 BSSET->GetSetInfo("pxallclientdetail");
	 allclient  = BSSET->ValueBool ;
	//删单密码
	 BSSET->GetSetInfo("pxdeleteusepassword");
	 deletedetail  =  BSSET->ValueBool ;
	//查单密码
	  BSSET->GetSetInfo("pxfindusepassword");
	  find = BSSET->ValueBool ;
	//修改单头密码是否启用
	  BSSET->GetSetInfo("pxusechange");
	  changepassword = BSSET->ValueBool ;
	// 重复提示
	  BSSET->GetSetInfo("wsalesametuihuotishi");
	  sametishi = BSSET->ValueBool ;
	  FormView();
	  printmodle = 0;
          dbdtedtHdTime->DateTime = Now();
}

void __fastcall TfrmWholesaleReturnMng::FormClose(TObject *Sender, TCloseAction &Action)
{
	DelInvalidNtHeader();

	spQryNtHeader->Active = false;
	spQryNtHeader1->Active = false;
	dsetStaff->Active = false;
	dsetLkpVendor->Active = false;
	dsetBkstack->Active = false;
	dsetVendor->Active = false;
	TfrmMDIChild::FormClose(Sender, Action);
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::tlbtn1Click(TObject *Sender)
{
	//删除
	if (!SaveWsale(1))
	{
		return;
	}
	//DelInvalidNtHeader();
	TControl* con = dynamic_cast<TControl*>(Sender);
	if (con)
	{
		ChangeOpmode(con->Tag);
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmWholesaleReturnMng::tlbtn7Click(TObject *Sender)
{

	Close();
        HANDLE hWindow = FindWindow("TfrmMain",NULL);
        SendMessage(hWindow ,WM_MYMESSAGE,0,0);
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::edtQryVendorKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r')
	{
		if (!dsetNtHeader->Active
			|| !dsetNote->Active
			|| (dsetNtHeader->Active && dsetNtHeader->RecordCount < 1))
			return;
		if (!dblkpcbbVendorID->Enabled ) {
		   return;
		}
		AnsiString sql;
		sql = " select * from CUST_CustomerInfo where Type in(2,3) and customerstate =1 and "+QFClientTiaoJian+" and Name like '%"+ edtQryVendor->Text.Trim() + "%' order by name";
		dsetVendor->Active = false;
		dsetVendor->CommandText = sql;
		dsetVendor->Active = true;
		dsetVendor->First();
	      	dblkpcbbVendorID->KeyValue = dsetVendor->FieldByName("ID")->AsInteger ;
	       //	dsetNtHeader->Edit();
		//dsetNtHeader->FieldByName("VendorID")->AsInteger = dsetVendor->FieldByName("ID")->AsInteger;
	       //	dsetNtHeader->Post();


		dblkpcbbVendorID->SetFocus();
		ClientID = dsetVendor->FieldByName("ID")->AsInteger ;
		checkedview();
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmWholesaleReturnMng::edtCatalogKeyPress(TObject *Sender, wchar_t &Key)
{
	//
        int results;
    if (m_catalogSearchMode == 6) {
		if ((Key < '0' || Key > '9') && (Key != '\b') && (Key != '.') && (Key != '\r') ) {
            Key = NULL;
		}
	}
	if (Key == '\r')
	{
		if (BtnSave->Enabled) {
			ShowMsg(Handle ,"请先保存批销退货单！",3);
			return;
		}
		if (!dsetNote->Active || !dsetNtHeader->Active
			|| (dsetNtHeader->Active && dsetNtHeader->RecordCount < 1))
			return;

		if (edtCatalog->Text == "")
		{
			ChangeCatalogSearchMode();
		}
		else
		{
            float price;
			if (m_catalogSearchMode == 6) {
				try {
					price = StrToFloat(edtCatalog->Text.Trim());
				} catch (...) {

                                         ShowMsg(Handle ,"请输入正确的定价！",3);
					return;
				}
			}

			switch (m_catalogSearchMode)
			{
			case 1:
			case 6:
			case 2:
			case 3:
			case 5:
				{
					TfrmSelectCatalog* frm = new TfrmSelectCatalog(Application,m_con);
					LandInfo li;
					li.app = m_app;
					li.con = m_con;
					li.userID = m_userID;
					li.storageID = m_storageID;
					frm->Init(&li);
					frm->DoModalType = 7; //一般发货退货模式
					frm->WholeReturnfrm = this;
					frm->SetSearchMode(m_catalogSearchMode, edtCatalog->Text);

                                        frm->SelectAll = false;
                                        frm->QryBkInfo();
                                        if (frm->findbooks == 3) {
                                           results= frm->ShowModal();
                                         }else if (frm->findbooks==1) {  //只找到一条，就不显示选择窗口了
                                            results = 1;
                                         }else if ((frm->findbooks==0)||(frm->findbooks==-1)) {
                                            results = -1 ;       //没有找到或都出错
                                         }
					if (mrOk == results)
					{
						int bkinfoid = -1,catalogID = -1;
						if (frm->SelectAll) {
							 for (int i = 0; i < frm->lengthint; i++) {
								 //cbbkstackID->ItemIndex = cbbkstackID->Items->IndexOfObject((TObject*)frm->BKSKid[i]);

								 if (!retailreturn(frm->BkcatalogiD[i])) {
									return;
								 }
								 if (!saleenable(frm->stkbkid[i])) {
									return;
								 }
								 if (AddNote(frm->SupplierID[i],frm->BkcatalogiD[i],frm->stkbkid[i],1)) {
									 /*Key = 0;
									 Perform(WM_NEXTDLGCTL, 0, 0);
									 historyview();  */
								 }
							 }
							 QryNtHeader();
						}else
						{
							frm->GetSelectResult(bkinfoid,catalogID);
							if (!retailreturn(catalogID)) {
                            	return;
							}
							if (frm->addbkinfo ) {
								//supplierID = 0;
							}
							if (bkinfoid >= 0 && catalogID >= 0)
							{
								if (!frm->addbkinfo) {
                                	//cbbkstackID->ItemIndex = cbbkstackID->Items->IndexOfObject((TObject*)frm->BSKid);
                                	if (!saleenable(frm->BKinfoid)) {
										return;
									}
								}

                                TLocateOptions   Opts;
								Opts.Clear();
								Opts   <<   loPartialKey;
								AnsiString str = AnsiString(catalogID);





                                                                  bool samerecode;
                                                                if (!dsetNote->Locate("BkcatalogID",str,Opts)) {
                                                                    samerecode=true;
                                                                }else //有相同的记录
                                                                {
                                                                   if (sametishi) {
                                                                               samerecode=true;

									}else samerecode = false;

                                                                }
								if (samerecode){ //samerecode
									if (AddNote(frm->m_supplierID,catalogID,bkinfoid,0))
									{
										Key=0;
										historyview();
										if (chfoceset->Checked) {
											if (chfsamount->Checked ) {
												dbnbedtAmount->SetFocus();
											}
											else if (chfsdiscount->Checked ) {
												dbnbedtDiscount->SetFocus();
											}
											else if (chfsluru->Checked) {
												edtCatalog->SetFocus();
											}
										}
										else
										{
											dbnbedtAmount->SetFocus();
										}
										editprice->Text =  FormatFloat("0.00", dsetNote->FieldByName("price")->AsFloat * dbnbedtDiscount->Value * 0.01);
									}
								}
								else
								{

									dbgrdNote->SelectedRows->CurrentRowSelected = true;
									dbgrdNote->SetFocus();
									dbnbedtAmount->SetFocus();
								}
							}
						}
					}
					delete frm;
					edtCatalog->Text = "";
					if (dblkpcbbVendorID->Text == "") {
						dblkpcbbVendorID->KeyValue = dsetVendor->FieldByName("ID")->AsInteger ;
					}
				}
				break;
            default:
				;
			}
		}
    }
}
//---------------------------------------------------------------------------

void TfrmWholesaleReturnMng::ChangeCatalogSearchMode()
{
	if (m_catalogSearchMode==3) {
		m_catalogSearchMode=5;
	}else
	{
	m_catalogSearchMode++;  }
	if (m_catalogSearchMode >= 7)
	{
		m_catalogSearchMode = 1;
	}

	switch (m_catalogSearchMode)
	{
	case 1:
    	edtCatalog->MaxLength = 20;
		lblCatalog->Caption = "书号";
		break;
	case 2:
		edtCatalog->MaxLength = 0;
		lblCatalog->Caption = "自编码";
		break;
	case 3:
		edtCatalog->MaxLength = 0;
		lblCatalog->Caption = "书名";
		break;
	case 5:
		edtCatalog->MaxLength = 0;
		lblCatalog->Caption = "作者";
		break;
	case 6:
		edtCatalog->MaxLength = 0;
		lblCatalog->Caption = "定价";
		break;
    default:
        break;
	}
}

//---------------------------------------------------------------------------
/*void TfrmWholesaleReturnMng::ChangeBsmode(BSMode bsmode)
{
	if (bsmode != m_bsmode)
	{
		m_bsmode = bsmode;
    }

	if (m_bsmode == BSNote)
	{
		mniBsNote->Checked = true;
		mniBsNoteSendback->Checked = false;
	}
	else if (m_bsmode == BSNoteSendback)
	{
		mniBsNote->Checked = false;
		mniBsNoteSendback->Checked = true;
	}
}   */
//---------------------------------------------------------------------------
void TfrmWholesaleReturnMng::ChangeOpmode(OPMode opmode)
{
	if (opmode == m_opmode
		&& (opmode == OPDelNtHeader))
		return;

	//1为查单模式 2为添加单头模式 3为删除单头模式 4为添加单模式 5为删除单模式 6为统一模式 7为现场收款模式
	switch (opmode)
	{
	case OPFind:
		{
			if (!SaveWsale(1))
			{
				return;
			}

            AnsiString sql;

			if (find) {
            	if (!CheckOperateAuthority())
					return;
			}
			DBNav->Enabled = true;

			Tfrmorderquery* frm = new Tfrmorderquery(Application,m_con,m_storageID,2,1,linfo.UserName,qfclient);
			if (frm->ShowModal() == mrOk)
			{

                               if (frm->printnow) {    //用户选择打印
                                    muilprint(frm->headerid,0);

                                }else
                                {
				String sql;
				sql = " select * from CUST_CustomerInfo where Type in (2,3) and customerstate =1 and "+QFClientTiaoJian+" order by name ";
				dsetVendor->Active = false;
				dsetVendor->CommandText = sql;
				dsetVendor->Active = true;
				dsetVendor->First();
				dblkpcbbVendorID->KeyValue = dsetVendor->FieldByName("ID")->AsInteger ;

				DelInvalidNtHeader();
				edtCatalog->Text = "";
				edtQryVendor->Text = "";
				AnsiString code = frm->GetNoteCode();
				AnsiString sqlwhere = frm->GetWhere();
				try
				{
					QryNtHeader(code);
					String sql;
					if (sqlwhere != "") {
						sql = "select * from BS_WsaleNoteHeader " + sqlwhere;
						querydan->Close();
						querydan->SQL->Clear();
						querydan->SQL->Add(sql);
						querydan->Open();
						TLocateOptions Opts;
						Opts.Clear();
						Opts << loPartialKey;
						querydan->Locate("WsaleNtCode", code, Opts);
					}
				}
				__finally
				{

				}
				m_opmode = opmode;
				delete frm;

				dblkpcbbVendorID->Enabled = false;
				BtnSave->Enabled = false;
				SaveOrNot = true;
				RzButton1->Enabled = false;
				dbnbedtAddCosts->Enabled = false;
                                dbdtedtHdTime->Enabled=false;
                                dblkpcbbStaffID->Enabled = false;

			}
                                }
        }
		break;
	case OPAddNtHeader:
		{
			RzToolButton2->Enabled = true;
			dblkpcbbVendorID->Enabled = true;
			RzButton1->Enabled= true;
			//如果上次是添加模式，并且没有加进任何数据，则不能添加
			if (m_opmode == OPAddNtHeader &&
				dsetNote->Active && dsetNote->RecordCount < 1)
				return;

			if (m_opmode == OPDelNote
				&& dsetNote->Active && dsetNote->RecordCount < 1)
				return;

			edtCatalog->Text = "";
			edtQryVendor->Text = "";
			editprice->Text = "0.00";
			AddNtHeader();
			m_opmode = opmode;
			edtQryVendor->SetFocus();
			//cbclient->ItemIndex = cbclient->Items->IndexOfObject((TObject*)dsetVendor->FieldByName("ID")->AsInteger );
        }
		break;
	/*case OPDelNtHeader:
		{
			RzToolButton2->Enabled = true;
			if (!CheckOperateAuthority())
				return;

			edtCatalog->Text = "";
			edtQryVendor->Text = "";
//			DelNtHeader();
			m_opmode = opmode;
        }
		break; */
	case OPAddNote:
		RzToolButton2->Enabled = true;
    	edtCatalog->Text = "";
		edtCatalog->SetFocus();
		m_opmode = opmode;
		break;
	case OPDelNote:
    	if (dsetNote->IsEmpty() ) {
            	return;
		}
		RzToolButton2->Enabled = true;
		if (deletedetail) {
			if (!CheckOperateAuthority())
				return;
		}
		else
		{
			if (ShowMsg(Handle ,"确定要删除该记录吗?",1)!=1 )
				return;
		}
		DelNote();

		//ResetNtHeader();
    	m_opmode = opmode;
		break;
	case OPSetNotes:
		RzToolButton2->Enabled = true;
    	if (dsetNote->Active && dsetNote->RecordCount >= 1)
		{
			//统一模式
			if (dbgrdNote->SelectedRows->Count == 0 || dbgrdNote->SelectedRows->Count == 1) {
            	for (int i = 1; i <= dsetNote->RecordCount ; i++) {
					dbgrdNote->DataSource->DataSet->RecNo = i;
					dbgrdNote->SelectedRows->CurrentRowSelected = true;
				}
			}
			TfrmSetNotes* frm = new TfrmSetNotes(this);
			frm->ChangeBsmode(2);
			if (frm->ShowModal() == mrOk)
			{
				int amount = 0;
				float discount = 0;
				bool bsetAmount = frm->GetAmount(amount);
				bool bsetDiscount = frm->GetDiscount(discount);
				if (bsetAmount && bsetDiscount)
				{
					BatchSetNotes(amount, discount, 1);
				}
				else if (bsetAmount && !bsetDiscount)
				{
					BatchSetNotes(amount, discount, 2);
				}
				else if (!bsetAmount && bsetDiscount)
				{
                	BatchSetNotes(amount, discount, 3);
				}
				else
				{

                }
			}
			delete frm;
			m_opmode = opmode;
        }
		break;
	case OPRecCash:
    	//现场收款模式
    	if (!SaveWsale(1))
		{
			return;
		}
    	RzToolButton2->Enabled = true;

		if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
		{
			//首先把修改的更新一下哈
			dbgrdNote->SetFocus();
			//其次把最新数据刷新一下哈
			QryNtHeader();
			if (dsetNote->IsEmpty() ) {
            	return;
			}
			//
			/*String NtHeader = dbedtWsaleNtCode->Text.Trim(),Headerdate;
			if (NtHeader.Length() == 13 ) {
				Headerdate = NtHeader.SubString(0,4)+ "-" + NtHeader.SubString(5,2) + "-" + NtHeader.SubString(7,2);
			}
			else if(NtHeader.Length() == 14)
			{
				Headerdate = NtHeader.SubString(1,4)+ "-" + NtHeader.SubString(6,2) + "-" + NtHeader.SubString(8,2);
			}
			else if (NtHeader.Length() == 15) {
				Headerdate = NtHeader.SubString(2,4)+ "-" + NtHeader.SubString(7,2) + "-" + NtHeader.SubString(9,2);
			}
			if (StrToDate(Headerdate) != Date()) {
				MessageBox(0,"现场收款只能收当日的！","一般发货退货" ,MB_OK);
				return;
			}   */
			AnsiString sql;
			sql = " select datediff(day,getdate(),HdTime) as day from BS_WsaleNoteHeader where id = " +  dsetNtHeader->FieldByName("ID")->AsAnsiString;
			query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->Open();
			if (query->FieldByName("day")->AsInteger != 0 ) {

                                ShowMsg(Handle ,"现场收款只能收当日的!",3);
				return;
			}

			TfrmRecMoney* frm = new TfrmRecMoney(this);
			frm->format = format;
			frm->SetDiscountedPrice(dsetNtHeader->FieldByName("DiscountedPrice")->AsFloat);
			frm->SetChecked(dsetNtHeader->FieldByName("Checked")->AsFloat);
			frm->lbl2->Caption = "现场收款";
			frm->RzLabel1->Caption = "应收金额";
			if (mrOk == frm->ShowModal())
			{
				if (frm->numedtUnchecked ->Value > 0) {

					if (ShowMsg(Handle ,"你还有未结金额，是否继续？",1)!=1) {
                        frm->ShowModal();
						return;
					}
				}
				dsetNtHeader->Edit();
				dsetNtHeader->FieldByName("Checked")->AsFloat =
				dsetNtHeader->FieldByName("Checked")->AsFloat + frm->GetReceived();
				UpdateNtHeader();
				AnsiString Code = NoteCode::BuildCode(query, GetDBTime(query), 0, "FN_CUSEndMoneyDocuments", "MoneyCode");
				sql = "insert into FN_CUSEndMoneyDocuments (MoneyCode,date,state,type,userid,CustmerName,ClearingType,Clearingstyle,stgid) values ("+Code+",getdate(),1,2," + IntToStr(m_userID) +",'" + dblkpcbbVendorID->Text + "','现场收款','现金'," + IntToStr(m_storageID) + ")";
				query->Close();
				query->SQL->Clear();
				query->SQL->Add(sql);
				query->ExecSQL();
				sql = "insert into FN_CUSEndMoneyDtails(EndMoneyDocumentID,stgntcode,thistime,type,CodeStr) values(" + Code + "," + dsetNtHeader->FieldByName("WsaleNtCode")->AsAnsiString + "," + FloatToStr(frm->GetReceived()) + ",2,'" + dsetNtHeader->FieldByName("WsaleNtCodeStr")->AsAnsiString + "')";
				query->Close();
				query->SQL->Clear();
				query->SQL->Add(sql);
				query->ExecSQL();
			}
			delete frm;
		}
    	m_opmode = opmode;
    	break;
    default:
        break;
	}
	//ModifyEnable();
}

void TfrmWholesaleReturnMng::BatchSetNotes(int amount, float discount, int mode)
{
	if (dsetNote->Active && dsetNote->RecordCount >= 1)
	{
		String ids = "-1";
		if (dbgrdNote->SelectedRows->Count == 0)
		{
			if (mode != 3) {
				if (tuihuocatch(abs(amount),dsetNote->FieldByName("BkcatalogID")->AsInteger)) {
					ids = ids + "," + dsetNote->FieldByName("BkcatalogID")->AsString;
					UpdateAmount(amount);
				}
			}
			else
			{
				ids = ids + "," + dsetNote->FieldByName("BkcatalogID")->AsString;
			}
		}
		else if (dbgrdNote->SelectedRows->Count > 0)
		{
			dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[0];
			if (mode != 3) {
				if (tuihuocatch(abs(amount),dsetNote->FieldByName("BkcatalogID")->AsInteger)) {
					ids = ids + "," + dsetNote->FieldByName("BkcatalogID")->AsString;
					UpdateAmount(amount);
				}
			}
			else
			{
				ids = ids + "," + dsetNote->FieldByName("BkcatalogID")->AsString;
			}
			for (int i=1; i < dbgrdNote->SelectedRows->Count; i++)
			{
				dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[i];
				if (mode != 3) {
					if (tuihuocatch(abs(amount),dsetNote->FieldByName("BkcatalogID")->AsInteger)) {
						ids = ids + "," + dsetNote->FieldByName("BkcatalogID")->AsString;
						UpdateAmount(amount);
					}
				}
				else
				{
					ids = ids + "," + dsetNote->FieldByName("BkcatalogID")->AsString;
				}
			}
		}
		else
			return;

		if (mode == 1) {
            mode = 3;
		}
		switch(mode)
		{
		case 1://两者均更新
			/*cmdBatchUpdateNote->Parameters->ParamByName("@IDS")->Value = ids;
			cmdBatchUpdateNote->Parameters->ParamByName("@Amount")->Value = amount;
			cmdBatchUpdateNote->Parameters->ParamByName("@Discount")->Value = discount;
			cmdBatchUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 2;
			cmdBatchUpdateNote->Parameters->ParamByName("@Ntheaderid")->Value = dsetNtHeader->FieldByName("ID")->AsAnsiString;
			cmdBatchUpdateNote->Execute(); */
			try
			{
				//LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
				QryNtHeader();
			}
			__finally
			{
				//LockWindowUpdate(NULL);
			}
			break;
		case 2://只更新Amount
			/*cmdBatchUpdateNote->Parameters->ParamByName("@IDS")->Value = ids;
			cmdBatchUpdateNote->Parameters->ParamByName("@Amount")->Value = amount;
			cmdBatchUpdateNote->Parameters->ParamByName("@Discount")->Value = "";
			cmdBatchUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 2;
			cmdBatchUpdateNote->Parameters->ParamByName("@Ntheaderid")->Value = dsetNtHeader->FieldByName("ID")->AsAnsiString;
			cmdBatchUpdateNote->Execute();  */
			try
			{
				//LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
				QryNtHeader();
			}
			__finally
			{
				//LockWindowUpdate(NULL);
			}
			break;
		case 3://只更新Discount
			cmdBatchUpdateNote->Parameters->ParamByName("@IDS")->Value = ids;
			cmdBatchUpdateNote->Parameters->ParamByName("@Amount")->Value = "";
			cmdBatchUpdateNote->Parameters->ParamByName("@Discount")->Value = discount;
			cmdBatchUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 2;
			cmdBatchUpdateNote->Parameters->ParamByName("@Ntheaderid")->Value = dsetNtHeader->FieldByName("ID")->AsAnsiString;
			cmdBatchUpdateNote->Execute();
			try
			{
				//LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
				QryNtHeader();
			}
			__finally
			{
				//LockWindowUpdate(NULL);
			}
			break;
		default:
			break;
		}
	}
}

void __fastcall TfrmWholesaleReturnMng::mniBsNoteSendbackClick(TObject *Sender)
{
	//添加单据类型
	TMenuItem* item = dynamic_cast<TMenuItem*>(Sender);
	if (item != NULL)
	{
		if (item->Tag == BSNoteSendback && !CheckOperateAuthority())
			return;

		//ChangeBsmode(item->Tag);
		ChangeOpmode(OPAddNtHeader);
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmWholesaleReturnMng::tlbtn4Click(TObject *Sender)
{
	//Excel导出
	//Excel导出
	if (!SaveWsale(1))
	{
		return;
	}
	if (dsetNote->Active && dsetNote->RecordCount >= 1)
	{
		DbgridToExcel(dbgrdNote);
	}
}
//---------------------------------------------------------------------------
//Excel导出函数
bool __fastcall TfrmWholesaleReturnMng::DbgridToExcel(TRzDBGrid* dbg)
{
	AnsiString temptext,path  ;
	int k = dbg->DataSource ->DataSet ->RecordCount ,n=0;

	savedlg->FileName = StringReplace(dblkpcbbVendorID->Text+editdanhao->Text ,"\\","-",TReplaceFlags()<<rfReplaceAll) + "发货退货单";
	if (savedlg->Execute())
	{
		String DBPath,Name;
		DBPath = Sysutils::ExtractFilePath(savedlg->FileName .c_str()  );
		Name = Sysutils::ExtractFileName(savedlg->FileName .c_str() );
		DBPath = DBPath + Name + ".xls";
		path =  DBPath;
	}
	else
	{
		return false;
	}

	if(FileExists(path))
		try {
			DeleteFileA(path);
		} catch (...) {
			return false;
		}

	/*int  iFileHandle;
	int   iFileLength;
	if(FileExists(path))
	   //iFileHandle = FileOpen(path.c_str() ,fmOpenReadWrite);
	   if (DeleteFileA(path))
			iFileHandle = FileCreate(path.c_str());
	   else
			return false;
	else
		iFileHandle = FileCreate(path.c_str());*/

    Variant  v,vSheet,R,xWorkbook;
	v   =Variant::CreateObject("Excel.Application");
	v.OlePropertySet("Visible",true);
	v.OlePropertyGet("WorkBooks").OleFunction("Add");
	xWorkbook = v.OlePropertyGet("ActiveWorkBook");
	vSheet =  xWorkbook.OlePropertyGet("ActiveSheet");

	int t1= 0;
	temptext = "\n";
	for(int q=0;q<dbg->FieldCount-1 ;++q)
	{
		if (dbg->Columns->Items[q]->Visible == true) {
			t1++;
			temptext = "'"+ dbg->Columns ->Items [q]->Title ->Caption;
			v.OlePropertyGet("Cells",1+n,(t1)).OlePropertySet("Value",temptext .c_str() );
			/*if (printmodle == 0 && (dbg->Columns ->Items [q]->Title ->Caption == "折扣" ||dbg->Columns ->Items [q]->Title ->Caption == "实洋")) {

			}
			else
			{
            	temptext = temptext + dbg->Columns ->Items [q]->Title ->Caption + ",";
			}*/
		}
	}
	//FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	int t2 = dbg->DataSource ->DataSet ->RecordCount ;

	dbg->DataSource ->DataSet ->First();
	dbg->DataSource ->DataSet->DisableControls();
	for(int   i=2+n;i<=t2+1+n ;i++)
	{
		t1=0;
		temptext = "\n";
		for(int j=1;j<dbg->Columns ->Count  ;j++)
		{
			if (dbg->Columns->Items[j-1]->Visible == true) {
				if (dbg->Columns ->Items [j-1]->FieldName == "ISBN") {
                	t1++;
					temptext = "'"+ dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );
					//temptext = temptext + "'" + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
				}
			
				else if (dbg->Columns ->Items [j-1]->FieldName == "id" || dbg->Columns ->Items [j-1]->FieldName == "backdot"){

				}
				else
				{
					/*if (printmodle == 0 && (dbg->Columns ->Items [j-1]->FieldName == "DiscountedPrice" || dbg->Columns ->Items [j-1]->FieldName == "Discount")) {

					}
					else
					{
						temptext = temptext + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
					} */
					t1++;
					temptext = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
				}
			}
		}
		//FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
		dbg->DataSource ->DataSet ->Next() ;
	}
    R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",n+1,1),vSheet.OlePropertyGet("Cells",t2+n+2,t1)); //取得合并的区域
	R.OlePropertyGet("Borders",2).OlePropertySet("linestyle",1);
	R.OlePropertyGet("Borders",4).OlePropertySet("linestyle",1);

	v.OlePropertyGet("Cells",t2+2+n,1).OlePropertySet("Value","合计");
	temptext = dbnbedt2->Text ;
	v.OlePropertyGet("Cells",t2+2+n,4).OlePropertySet("Value",temptext .c_str() );
	temptext = dbnbedt3->Text ;
	v.OlePropertyGet("Cells",t2+2+n,6).OlePropertySet("Value",temptext .c_str() );
	temptext = dbnbedt4->Text ;
	v.OlePropertyGet("Cells",t2+2+n,7).OlePropertySet("Value",temptext .c_str() );
	dbg->DataSource ->DataSet->EnableControls();

	try {
		xWorkbook.OleFunction("SaveAs",path.c_str());
	} catch (Exception &E) {
		//ShowMessage(E.Message);
	}

	/*AnsiString pxamount,mayang,shiyang;
	mayang =  dbnbedt3->Text;
	shiyang = dbnbedt4->Text;
	pxamount = dbnbedt2->Text;
	mayang = StringReplace(mayang , ",","",TReplaceFlags()<<rfReplaceAll);
	shiyang = StringReplace(shiyang , ",","",TReplaceFlags()<<rfReplaceAll);
	pxamount = StringReplace(pxamount , ",","",TReplaceFlags()<<rfReplaceAll);
	temptext = "\n";
	if (printmodle == 0) {
		temptext = temptext + "合计,,,,,,,," + pxamount + ",'" + mayang ;
	}
	else
	{
		temptext = temptext + "合计,,,,,,,," + pxamount + ",,'" + mayang + ",'" + shiyang ;
	}

	iFileLength   =   FileSeek(iFileHandle,0,2);
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	FileClose(iFileHandle);

	MessageBox(0,"导出完毕！","提示" ,MB_OK);   */
	return false;
}
//---------------------------------------------------------------------------}
//---------------------------------------------------------------------------
void TfrmWholesaleReturnMng::QryNtHeader(String code, bool qrybkstack)
{
	spQryNtHeader->Active = false;
	spQryNtHeader1->Active = false;
	spQryNtHeader1->Parameters->ParamByName("@NtCode")->Value = code;
	spQryNtHeader1->Parameters->ParamByName("@Bsmode")->Value = 2;
	MYTRACEF(_T("query note header @NtCode=%S"), code.c_str());
	try
	{
		spQryNtHeader1->Active = true;
		dsrcNtHeader->DataSet = NULL;
		dsetNtHeader->Recordset = spQryNtHeader1->Recordset;
		dsrcNtHeader->DataSet = dsetNtHeader;
		dsetNtHeader->Last();
		int count = 0;
		dsrcNote->DataSet = NULL;
		dsetNote->AfterScroll = NULL;
		dsetNote->Recordset = spQryNtHeader1->NextRecordset(count);
		dsrcNote->DataSet = dsetNote;
		dsetNote->Last();
		dbnbedt2->Visible = true;
		dbnbedt3->Visible = true;
		dbnbedt4->Visible = true;

		dsetNote->AfterScroll = dsetNoteAfterScroll;
		ClientID = dsrcNtHeader->DataSet->FieldByName("VendorID")->Value;
		checkedview();
		GetHtHeaderTotal();
		/*if (qrybkstack)
		{
            QryBkstack();
		} */
		editdanhao->Text = dsetNtHeader->FieldByName("WsaleNtCodeStr")->AsAnsiString ;
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "###,###,##0.00";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = format;
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = format;
		operterview(dsetNtHeader->FieldByName("OperatorID")->AsInteger );
                dbdtedtHdTime->DateTime =dsetNtHeader->FieldByName("HdTime")->AsDateTime;
		membk->Text =  dsetNtHeader->FieldByName("Remarks")->AsString;
		if (dsetNtHeader->FieldByName("cwstate")->AsInteger == 1 || dsetNtHeader->FieldByName("Checked")->AsFloat != 0.00) {
			grpbxNote->Enabled = false;
			tlbtnAddNote->Enabled = false;
			tlbtn2->Enabled = false;
			tlbtn3->Enabled = false;
			Image1->Visible = true;
		}
		else
		{
			grpbxNote->Enabled = true;
			tlbtnAddNote->Enabled = true;
			tlbtn2->Enabled = true;
			tlbtn3->Enabled = true;
			Image1->Visible = false;
		}
	}
	catch(...)
	{
		//ShowMessage("该单不存在！");
	}
}

void TfrmWholesaleReturnMng::QryNtHeader(bool qrybkstack)
{
	//保存查询之前的当前活动记录ID
	int noteID = 0;
	if (dsetNote->Active && dsetNote->RecordCount >= 1)
	{
        noteID = dsetNote->FieldByName("ID")->AsInteger;
	}
	//查询单头
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		spQryNtHeader1->Active = false;
		spQryNtHeader->Active = false;
		spQryNtHeader->Parameters->ParamByName("@ID")->Value = dsetNtHeader->FieldByName("ID")->AsInteger;
		spQryNtHeader->Parameters->ParamByName("@Bsmode")->Value = 2;
		try
		{
			spQryNtHeader->Active = true;
			dsrcNtHeader->DataSet = NULL;
			dsetNtHeader->Recordset = spQryNtHeader->Recordset;
			dsrcNtHeader->DataSet = dsetNtHeader;
			dsetNtHeader->Last();
			int count = 0;
			dsrcNote->DataSet = NULL;
			dsetNote->AfterScroll = NULL;
			dsetNote->Recordset = spQryNtHeader->NextRecordset(count);
			dsrcNote->DataSet = dsetNote;
			if (noteID > 0)//将当前记录的ID重新调整至noteID
			{
                TLocateOptions Opts;
				Opts.Clear();
				Opts << loPartialKey;
				if (!dsetNote->Locate("ID", noteID, Opts))
					dsetNote->Last();
			}
			else
			{
				dsetNote->Last();
			}
			dsetNote->AfterScroll = dsetNoteAfterScroll;
			ClientID = dsrcNtHeader->DataSet->FieldByName("VendorID")->Value;


			GetHtHeaderTotal();

			editdanhao->Text = dsetNtHeader->FieldByName("WsaleNtCodeStr")->AsAnsiString ;
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00";
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "###,###,##0.00";
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = format;
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = format;
			operterview(dsetNtHeader->FieldByName("OperatorID")->AsInteger );
			membk->Text =  dsetNtHeader->FieldByName("Remarks")->AsString;
            if (dsetNtHeader->FieldByName("cwstate")->AsInteger == 1 || dsetNtHeader->FieldByName("Checked")->AsFloat != 0.00 ) {
				grpbxNote->Enabled = false;
				tlbtnAddNote->Enabled = false;
				tlbtn2->Enabled = false;
				tlbtn3->Enabled = false;
				Image1->Visible = true;
			}
			else
			{
				grpbxNote->Enabled = true;
				tlbtnAddNote->Enabled = true;
				tlbtn2->Enabled = true;
				tlbtn3->Enabled = true;
				Image1->Visible = false;
			}
		}
		catch(...)
		{
			//ShowMessage("该单不存在！");
		}
	}
}

void TfrmWholesaleReturnMng::QryNtHeader(int id, bool qrybkstack)
{
	//查询单头
	spQryNtHeader1->Active = false;
	spQryNtHeader->Active = false;
	spQryNtHeader->Parameters->ParamByName("@ID")->Value = id;
	spQryNtHeader->Parameters->ParamByName("@Bsmode")->Value = 2;
	try
	{
		spQryNtHeader->Active = true;
		dsrcNtHeader->DataSet = NULL;
		dsetNtHeader->Recordset = spQryNtHeader->Recordset;
		dsrcNtHeader->DataSet = dsetNtHeader;
		dsetNtHeader->Last();
		int count = 0;
		dsrcNote->DataSet = NULL;
		dsetNote->AfterScroll = NULL;
		dsetNote->Recordset = spQryNtHeader->NextRecordset(count);
		dsrcNote->DataSet = dsetNote;
		dsetNote->Last();
		dsetNote->AfterScroll = dsetNoteAfterScroll;
		ClientID = dsrcNtHeader->DataSet->FieldByName("VendorID")->Value;

		GetHtHeaderTotal();
		editdanhao->Text = dsetNtHeader->FieldByName("WsaleNtCodeStr")->AsAnsiString ;
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "###,###,##0.00";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = format;
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = format;
		operterview(dsetNtHeader->FieldByName("OperatorID")->AsInteger );
		membk->Text =  dsetNtHeader->FieldByName("Remarks")->AsString;
		if (dsetNtHeader->FieldByName("cwstate")->AsInteger == 1 || dsetNtHeader->FieldByName("Checked")->AsFloat != 0.00 ) {
			grpbxNote->Enabled = false;
			tlbtnAddNote->Enabled = false;
			tlbtn2->Enabled = false;
			tlbtn3->Enabled = false;
			Image1->Visible = true;
		}
		else
		{
			grpbxNote->Enabled = true;
			tlbtnAddNote->Enabled = true;
			tlbtn2->Enabled = true;
			tlbtn3->Enabled = true;
			Image1->Visible = false;
		}
	}
	catch(...)
	{
    	//ShowMessage("该单不存在！");
    }
}

void TfrmWholesaleReturnMng::AddNtHeader()
{
	spQryNtHeader->Active = false;
	spQryNtHeader1->Active = false;
	cmdAddNtHeader->Parameters->ParamByName("@StgID")->Value = m_storageID;
	cmdAddNtHeader->Parameters->ParamByName("@OperatorID")->Value = m_userID;
	cmdAddNtHeader->Parameters->ParamByName("@Bsmode")->Value = 2;
	cmdAddNtHeader->Parameters->ParamByName("@CODEMODE")->Value = 1;
	MYTRACEF(_T("add note header @StgID=%d,@OperatorID=%d,@Bsmode=%d"),m_storageID,m_userID,2);
	cmdAddNtHeader->Execute();
	int id = cmdAddNtHeader->Parameters->ParamByName("@RETURN_VALUE")->Value;
	try
	{
		//LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
		QryNtHeader(id);
	}
	__finally
	{
		//LockWindowUpdate(NULL);
	}
}

void TfrmWholesaleReturnMng::DelInvalidNtHeader()
{
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1
		&& dsetNote->Active && dsetNote->RecordCount < 1
		&& dsetNtHeader->FieldByName("State")->AsInteger == 0 && dsetNtHeader->FieldByName("WsaleNtCode")->AsInteger == 0)
	{
		DelNtHeader();
    }
}

void TfrmWholesaleReturnMng::DelNtHeader()
{
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		cmdDelNtHeader->Parameters->ParamByName("@ID")->Value
			= dsetNtHeader->FieldByName("ID")->AsInteger;
		int id = dsetNtHeader->FieldByName("ID")->AsInteger;
		cmdDelNtHeader->Parameters->ParamByName("@Bsmode")->Value = 2;
		MYTRACEF(_T("del note header @ID=%d,@Bsmode=%d"), id, 2);
		cmdDelNtHeader->Execute();
		try
		{
			//LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
			//QryNtHeader(id);
		}
		__finally
		{
			//LockWindowUpdate(NULL);
		}
	}
}

void TfrmWholesaleReturnMng::UpdateNtHeader()
{
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		cmdUpdateNtHeader->Parameters->ParamByName("@ID")->Value =
			dsetNtHeader->FieldByName("ID")->AsInteger;
		cmdUpdateNtHeader->Parameters->ParamByName("@HdTime")->Value =
			dsetNtHeader->FieldByName("HdTime")->AsDateTime;
		cmdUpdateNtHeader->Parameters->ParamByName("@StgID")->Value =
			dsetNtHeader->FieldByName("StgID")->AsInteger;
		if (dsetNtHeader->FieldByName("StaffID")->AsString != "")
			cmdUpdateNtHeader->Parameters->ParamByName("@StaffID")->Value =
				dsetNtHeader->FieldByName("StaffID")->AsInteger;
		cmdUpdateNtHeader->Parameters->ParamByName("@AddCosts")->Value =
			abs(dsetNtHeader->FieldByName("AddCosts")->AsFloat);
		cmdUpdateNtHeader->Parameters->ParamByName("@Remarks")->Value =
			dsetNtHeader->FieldByName("Remarks")->AsWideString;
		cmdUpdateNtHeader->Parameters->ParamByName("@CustomerID")->Value =
			dsetNtHeader->FieldByName("VendorID")->AsInteger;
		cmdUpdateNtHeader->Parameters->ParamByName("@Cash")->Value =
			dsetNtHeader->FieldByName("Checked")->AsFloat;
		if (dsetNtHeader->FieldByName("DiscountedPrice")->AsFloat > 0 &&
			dsetNtHeader->FieldByName("Checked")->AsFloat >= dsetNtHeader->FieldByName("DiscountedPrice")->AsFloat)
		{
			cmdUpdateNtHeader->Parameters->ParamByName("@State")->Value = 1;
		}
		else if (dsetNtHeader->FieldByName("DiscountedPrice")->AsFloat < 0 &&
			dsetNtHeader->FieldByName("Checked")->AsFloat <= dsetNtHeader->FieldByName("DiscountedPrice")->AsFloat)
		{
			cmdUpdateNtHeader->Parameters->ParamByName("@State")->Value = 1;
		}
		else
		{
			cmdUpdateNtHeader->Parameters->ParamByName("@State")->Value =
				dsetNtHeader->FieldByName("State")->AsInteger;;
		}
		cmdUpdateNtHeader->Parameters->ParamByName("@Bsmode")->Value = 2;
		cmdUpdateNtHeader->Execute();

		try
		{
			//LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
			QryNtHeader();
		}
		__finally
		{
			//LockWindowUpdate(NULL);
		}
	}
}

bool TfrmWholesaleReturnMng::AddNote(int supplierID, int catalogID,int stkid,int mod)
{
	bool result = false;
	if (!retailreturn(catalogID)) {
		return true;
	}
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		cmdAddNote->Parameters->ParamByName("@NtHeaderID")->Value
			= dsetNtHeader->FieldByName("ID")->AsInteger;
		cmdAddNote->Parameters->ParamByName("@BkcatalogID")->Value
			= catalogID;
		cmdAddNote->Parameters->ParamByName("@STKinfoID")->Value = stkid;
		cmdAddNote->Parameters->ParamByName("@SupplierID")->Value = supplierID;
		cmdAddNote->Parameters->ParamByName("@Bsmode")->Value = 9;
		cmdAddNote->Execute();
		int ret = cmdAddNote->Parameters->ParamByName("@RETURN_VALUE")->Value;
		if (ret > 0)//插入成功
		{
			if (mod == 0) {     //全选添加记录
            	try
				{
					//LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
					QryNtHeader(dsetNtHeader->FieldByName("ID")->AsInteger, true);
					/*((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00%";
					((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "￥###,###,##0.00";
					((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = "￥###,###,##0.00";
					((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = "￥###,###,##0.00"; */
				}
				__finally
				{
					//LockWindowUpdate(NULL);
				}
			}

			result = true;
		}
		else if (ret == 0)//查无此书
		{

		}
		else if (ret == -1)//库存出错了
		{

		}
		else if (ret == -2) {
				  //addnotereturnvalue = -2;
                        //负库存
			result = true;
		}
	}
	return result;
}

void TfrmWholesaleReturnMng::UpdateNote()
{
	if (dsetNote->Active && dsetNote->RecordCount >= 1)
	{
		cmdUpdateNote->Parameters->ParamByName("@ID")->Value
			= dsetNote->FieldByName("BkcatalogID")->AsInteger;
		/*if (m_bsmode == BSNote)
		{
			cmdUpdateNote->Parameters->ParamByName("@Amount")->Value
				= abs(dsetNote->FieldByName("Amount")->AsInteger);
		}
		else
		{
			cmdUpdateNote->Parameters->ParamByName("@Amount")->Value
				= - abs(dsetNote->FieldByName("Amount")->AsInteger);
		} */
		cmdUpdateNote->Parameters->ParamByName("@Discount")->Value
			= dbnbedtDiscount->Value ;
		cmdUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 2;
		cmdUpdateNote->Parameters->ParamByName("@Ntheaderid")->Value = dsetNote->FieldByName("ID")->AsInteger;
		cmdUpdateNote->Execute();
	}
	try
	{
		//LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
	   //	QryNtHeader();
		/*((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00%";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "￥###,###,##0.00";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = "￥###,###,##0.00";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = "￥###,###,##0.00"; */
	}
	__finally
	{
		//LockWindowUpdate(NULL);
	}
}
void TfrmWholesaleReturnMng::DelNote()
{
	if (dsetNote->Active && dsetNote->RecordCount >= 1)
	{
		if (dbgrdNote->SelectedRows->Count == 0)
		{
			cmdDelNote->Parameters->ParamByName("@ID")->Value
				= dsetNote->FieldByName("id")->AsInteger;
			cmdDelNote->Parameters->ParamByName("@Bsmode")->Value = 2;
			cmdDelNote->Parameters->ParamByName("@Ntheaderid")->Value = dsetNtHeader->FieldByName("ID")->AsInteger;
			if (ChangeDisplay) {
				logmessage = "删除一般发货退货单" + dsetNtHeader->FieldByName("WsaleNtCodeStr")->AsAnsiString ;
			}
			else
			{
				logmessage = "删除一般发货退货单" + dsetNtHeader->FieldByName("WsaleNtCode")->AsAnsiString ;
			}
			logmessage = logmessage + "的书目《" + dsetNote->FieldByName("CatalogName")->AsAnsiString + "》";
			AddEvent(1,"一般发货退货窗口",m_userID,m_storageID,logmessage,linfo.con);
			cmdDelNote->Execute();
		}
		else if (dbgrdNote->SelectedRows->Count > 0)
		{
			String ids = "";
			dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[0];
			ids = ids + dsetNote->FieldByName("id")->AsString;
			if (ChangeDisplay) {
				logmessage = "删除一般发货退货单" + dsetNtHeader->FieldByName("WsaleNtCodeStr")->AsAnsiString ;
			}
			else
			{
				logmessage = "删除一般发货退货单" + dsetNtHeader->FieldByName("WsaleNtCode")->AsAnsiString ;
			}
			logmessage = logmessage + "的书目《" + dsetNote->FieldByName("CatalogName")->AsAnsiString + "》";
			AddEvent(1,"一般发货退货窗口",m_userID,m_storageID,logmessage,linfo.con);
			for (int i=1; i < dbgrdNote->SelectedRows->Count; i++)
			{
				dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[i];
				ids = ids + "," + dsetNote->FieldByName("id")->AsString;
				if (ChangeDisplay) {
					logmessage = "删除一般发货退货单" + dsetNtHeader->FieldByName("WsaleNtCodeStr")->AsAnsiString ;
				}
				else
				{
					logmessage = "删除一般发货退货单" + dsetNtHeader->FieldByName("WsaleNtCode")->AsAnsiString ;
				}
				logmessage = logmessage + "的书目《" + dsetNote->FieldByName("CatalogName")->AsAnsiString + "》";
				AddEvent(1,"一般发货退货窗口",m_userID,m_storageID,logmessage,linfo.con);
			}
                        dsetNote->Next();
			cmdBatchDelNote->Parameters->ParamByName("@IDS")->Value = ids;
			cmdBatchDelNote->Parameters->ParamByName("@Bsmode")->Value = 2;
			cmdBatchDelNote->Parameters->ParamByName("@Ntheaderid")->Value = dsetNtHeader->FieldByName("ID")->AsAnsiString;
			cmdBatchDelNote->Execute();
		}
		try
		{
			//LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
			QryNtHeader();
		}
		__finally
		{
			//LockWindowUpdate(NULL);
		}
	}
}

void __fastcall TfrmWholesaleReturnMng::dblkpcbbBkstackIDKeyPress(TObject *Sender, wchar_t &Key)
{
	//
	if (Key == '\r')
	{
		tlbtn1Click(tlbtnAddNote);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::dblkpcbbStaffIDExit(TObject *Sender)
{
	UpdateNtHeader();
}
//---------------------------------------------------------------------------
void __fastcall TfrmWholesaleReturnMng::dbnbedtAmountExit(TObject *Sender)
{
   if (dsetNote->RecordCount==0) {
        return;
   }else
   {

		double price,discount;
		int amount;
		double totaldis,totalfix;
               if (dbnbedtAmount->Value >= 100000)
                {
                    dbnbedtAmount->Value = 0;

                }
		//price = dsetNote->FieldByName("price")->AsFloat ;
		//discount = dbnbedtDiscount->Value;
		amount = 0-abs(dbnbedtAmount->Value);
		/*totaldis = abs(amount) * price * discount * 0.01*-1;
		totalfix = abs(amount) * price*-1;
		dsetNote->DisableControls();
		dsetNote->Edit();
		dsetNote->FieldByName("Amount")->AsInteger = abs(amount)*-1;
		dsetNote->FieldByName("FixedPrice")->AsFloat =  totalfix;
		dsetNote->FieldByName("DiscountedPrice")->AsFloat = totaldis;
		dsetNote->Post();
		dsetNote->EnableControls();   */

		try {
			int amount;
			amount = 0-abs(dbnbedtAmount->Value);

			UpdateAmount(amount);
                        UpdateNote();
			QryNtHeader();
			historyview();

        } catch (...) {
		}
   }

	/*UpdateNote();
	historyview();
	try
	{
		GetHtHeaderTotal();
	}
	catch(...)
	{

	}


	editprice->Text =  FormatFloat("0.00", dsetNote->FieldByName("price")->AsFloat * dbnbedtDiscount->Value * 0.01);
	if (dblkpcbbVendorID->Text == "") {
		dblkpcbbVendorID->KeyValue = dsetVendor->FieldByName("ID")->AsInteger ;
	}

	}*/
}
//---------------------------------------------------------------------------
 void TfrmWholesaleReturnMng::UpdateAmount(int amount)
{
	if (dsetNote->RecordCount==0) {
		return;
	}else
	{
		try {
			cmdUpdataamount->Parameters->ParamByName("@Bkcatalogid")->Value
			= dsetNote->FieldByName("BkcatalogID")->AsInteger;
			cmdUpdataamount->Parameters->ParamByName("@Amount")->Value = amount;
			cmdUpdataamount->Parameters->ParamByName("@Ntheaderid")->Value = dsetNote->FieldByName("ID")->AsInteger;
			cmdUpdataamount->Parameters->ParamByName("@stgid")->Value = m_storageID ;
			cmdUpdataamount->Execute();

        } catch (...) {
		}
	}
}
//---------------------------------------------------------------------------

void TfrmWholesaleReturnMng::Print(int modle,int type,int printid)//modle 1预览，2打印 type 0 默认方案 1 指定方案  prinid 方案id
{
	if (!SaveWsale(1))
	{
		return;
	}
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1 && dsrcNote->DataSet != NULL)
	{
		Tfrmwsaleprinta* frm = new Tfrmwsaleprinta(this,m_con);
		::ShowWindow(frm->Handle, SW_HIDE);
		LandInfo li;
		li.app = m_app;
		li.con = m_con;
		li.userID = m_userID;
		li.storageID = m_storageID;
                frm->pixiaoortuihuo=false;
		frm->InputPara(dsetNtHeader->FieldByName("ID")->AsString);

		frm->DanhaoChange = ChangeDisplay ;                      //change danhao
		frm->RvSystem1->SystemSetups >>ssAllowSetup;
		frm->RvSystem1->SystemSetups >>ssAllowDestPreview;
		frm->RvSystem1->SystemSetups >>ssAllowDestPrinter;
		frm->RvSystem1->SystemSetups >>ssAllowPrinterSetup;
		frm->RvSystem1->SystemSetups >>ssAllowDestFile;

		if (modle == 1) {
			frm->RvSystem1->DefaultDest   = rdPreview ;
		}
		else
		{
			frm->RvSystem1->DefaultDest   = rdPrinter ;
		}

		frm->RvSystem1->SystemSetups<<ssAllowDestPrinter;

		frm->RvSystem1->SystemSetups<<ssAllowDestPrinter;
		frm->pxbk = pxbk;
		frm->printtitle = printtitle;
		frm->contact = contact;
		frm->tel = tel;
		frm->address = address;
		frm->ClientName = dblkpcbbVendorID->Text ;
        if (type == 0) {
			frm->printmodle = -1;
		}
		else
		{
			frm->printmodle = printid;
		}
		frm->tuihuo = 1;
		frm->previewprint(modle,2);
		frm->Close();
		delete frm;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::tlbtn5Click(TObject *Sender)
{


   try
   {
    if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1 && dsrcNote->DataSet != NULL)
	{
           muilprint(dsetNtHeader->FieldByName("ID")->AsString,0);
        }
   }catch(...){};
//	Print(0,0,0);
	
}
//---------------------------------------------------------------------------




//---------------------------------------------------------------------------
void __fastcall TfrmWholesaleReturnMng::dsetNoteAfterScroll(TDataSet *DataSet)
{
	/*if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
		QryBkstack();   */
}
//---------------------------------------------------------------------------


void __fastcall TfrmWholesaleReturnMng::N1Click(TObject *Sender)
{
	lblCatalog->Caption = "书号";
	m_catalogSearchMode=1;
	edtCatalog->MaxLength = 20;
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::N2Click(TObject *Sender)
{
	lblCatalog->Caption = "自编码";
	m_catalogSearchMode=2;
	edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::N3Click(TObject *Sender)
{
	lblCatalog->Caption = "书名";
	m_catalogSearchMode=3;
	edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::lblCatalogMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	if (Button == mbLeft ) {
		TPoint  pt;
		GetCursorPos(&pt);
		pm->Popup(pt.x,pt.y);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::N11Click(TObject *Sender)
{
	tlbtn5->Click();
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::N21Click(TObject *Sender)
{
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		Tfrmwsaleprinta* frm = new Tfrmwsaleprinta(this,m_con);
		::ShowWindow(frm->Handle, SW_HIDE);
		LandInfo li;
		li.app = m_app;
		li.con = m_con;
		li.userID = m_userID;
		li.storageID = m_storageID;
		frm->InputPara(dsetNtHeader->FieldByName("ID")->AsString);

		frm->RvSystem1->SystemSetups >>ssAllowSetup;
		frm->RvSystem1->SystemSetups >>ssAllowDestPreview;
		frm->RvSystem1->SystemSetups >>ssAllowDestPrinter;
		frm->RvSystem1->SystemSetups >>ssAllowPrinterSetup;
		frm->RvSystem1->SystemSetups >>ssAllowDestFile;

		frm->RvSystem1->DefaultDest    = rdPrinter ;
		// frm->RvSystem1->SystemSetups<<ssAllowSetup;
		 frm->RvSystem1->SystemSetups<<ssAllowDestPrinter;
	  //	 frm->RvSystem1->SystemSetups<<ssAllowPrinterSetup;
		if (Label2->Caption == "一般发货单")
		{
			frm->previewprint(1,2);
		}else
		{
		   frm->previewprint(2,2);
		}
		  //1,一般发货单 2.一般发货退货单 //1打印格式1 2 打印格式2
		frm->Close();
		delete frm;
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmWholesaleReturnMng::BtnClearClick(TObject *Sender)
{


try
   {
    if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1 && dsrcNote->DataSet != NULL)
	{
           muilprint(dsetNtHeader->FieldByName("ID")->AsString,1);
        }
   }catch(...){};
  //try
 // {
  // Print(1,0,0);
 // }catch(...)
 // {}

}
void TfrmWholesaleReturnMng::muilprint(AnsiString HeaderID,int type,bool xiaopiao)
{
    	Tfrmwsaleprinta* frm = new Tfrmwsaleprinta(this,m_con);
		::ShowWindow(frm->Handle, SW_HIDE);
		LandInfo li;
		li.app = m_app;
		li.con = m_con;
		li.userID = m_userID;
		li.storageID = m_storageID;
	        frm->tuihuo = 1;
		frm->pxbk = pxbk;
		frm->printtitle = printtitle;
		frm->contact = contact;
		frm->tel = tel;
		frm->address = address;
                frm->pixiaoortuihuo = false;
                frm->wsalemuilPrint(HeaderID,type,xiaopiao);
		frm->Close();
		delete frm;

}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::N22Click(TObject *Sender)
{
	 if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		Tfrmwsaleprinta* frm = new Tfrmwsaleprinta(this,m_con);
		::ShowWindow(frm->Handle, SW_HIDE);
		LandInfo li;
		li.app = m_app;
		li.con = m_con;
		li.userID = m_userID;
		li.storageID = m_storageID;
		frm->InputPara(dsetNtHeader->FieldByName("ID")->AsString);

		frm->RvSystem1->SystemSetups >>ssAllowSetup;
		frm->RvSystem1->SystemSetups >>ssAllowDestPreview;
		frm->RvSystem1->SystemSetups >>ssAllowDestPrinter;
		frm->RvSystem1->SystemSetups >>ssAllowPrinterSetup;
		frm->RvSystem1->SystemSetups >>ssAllowDestFile;



		frm->RvSystem1->DefaultDest  = rdPreview ;
		frm->RvSystem1->SystemSetups<<ssAllowDestPreview;
		if (Label2->Caption == "一般发货单")
		{
			frm->previewprint(1,2);
		}else
		{
		   frm->previewprint(2,2);
		}
		  //1,一般发货单 2.一般发货退货单 //1打印格式1 2 打印格式2
		frm->Close();
		delete frm;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::N12Click(TObject *Sender)
{
  BtnClear->Click();
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::dbnbedtDiscountKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r')
	{
	 // Perform(WM_NEXTDLGCTL, 0, 0);
	  edtCatalog->Text = "";

	  if (chfoceset->Checked) {
			if (chfsluru->Checked) {
				edtCatalog->SetFocus();
			}
			else if (chfsamount->Checked) {
				if (!dsetNote->Eof) {
					dbgrdNote->SetFocus();
					dsetNote->Next();
					dbgrdNote->SelectedRows->CurrentRowSelected = true;
					dbnbedtAmount->SetFocus();
				}
			}
			else if (chfsdiscount->Checked) {
				if (!dsetNote->Eof) {
					dbgrdNote->SetFocus();
					dsetNote->Next();
					dbgrdNote->SelectedRows->CurrentRowSelected = true;
					dbnbedtDiscount->SetFocus();
				}
			}
		}
		else
		{
			edtCatalog->SetFocus();
		}

	}
}
//---------------------------------------------------------------------------



void __fastcall TfrmWholesaleReturnMng::FormResize(TObject *Sender)
{
	//dbgrdNote->Height = 393;
	//dbgrdNote->Width = 700;

}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::N4Click(TObject *Sender)
{
	lblCatalog->Caption = "定价";
	m_catalogSearchMode=6;
	edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::dbnbedtTotalAmountKeyPress(TObject *Sender, wchar_t &Key)

{
       if (Key == '\r')
	{
	  Perform(WM_NEXTDLGCTL, 0, 0);

	}
}
//---------------------------------------------------------------------------

void  TfrmWholesaleReturnMng::FindNote(String code)
{
	DelInvalidNtHeader();
	edtCatalog->Text = "";
	edtQryVendor->Text = "";
	try
	{
		//LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
		QryNtHeader(code);
		//editclientname->Text = dsetVendor->FieldByName("Name")->AsString ;
		//cbclient->Text =  dsetVendor->FieldByName("Name")->AsString ;

	}
	__finally
	{
		//LockWindowUpdate(NULL);
	}
	//cbclient->Enabled = false;
	dblkpcbbVendorID->Enabled = false;
	BtnSave->Enabled = false;
	SaveOrNot = true;
}

//---------------------------------------------------------------------------


void __fastcall TfrmWholesaleReturnMng::N6Click(TObject *Sender)
{
	if (dsetNote->IsEmpty() ) {
		return;
	}
	for (int i = 1; i <= dsetNote->RecordCount; i++) {
		dbgrdNote->DataSource->DataSet->RecNo = i;
		dbgrdNote->SelectedRows->CurrentRowSelected = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::dbgrdNoteCellClick(TColumn *Column)
{
	//historyview();
	//editprice->Text = FormatFloat("0.00",dsetNote->FieldByName("price")->AsFloat * dbnbedtDiscount->Value*0.01);
}
//---------------------------------------------------------------------------
void TfrmWholesaleReturnMng::GetHtHeaderTotal()
{
	if (!dsetNtHeader->IsEmpty()) {

	  dtGetTotal->Parameters->ParamByName("@mode")->Value = 2;
	  dtGetTotal->Parameters->ParamByName("@ID")->Value = dsetNtHeader->FieldByName("ID")->AsInteger;

	  if (!dtGetTotal->Active ) {
		dtGetTotal->Active = true;
	  }else
	  {
		 dtGetTotal->Active=false;
		 dtGetTotal->Active = true;
	  }
          totalyingshou->Value = dbnbedt4->Value+dbnbedtAddCosts->Value;
      }
}
void TfrmWholesaleReturnMng::historyview()
{
	AnsiString sql;
	if (dsetNote->RecordCount > 0) {
			sql = "select * from SYS_BSSET where name = 'wosaleday'" ;
			query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->Open();
			int day = query->FieldByName("bk")->AsInteger ;
			DATE datetime = Date();
			datetime = datetime - day;
			sql = "select BS_WsaleNoteHeader.WsaleNtCode,BS_WsaleNoteHeader.WsaleNtCodeStr,BS_WsaleNote.Amount,BS_WsaleNote.Discount,Convert(varchar(20),BS_WsaleNoteHeader.HdTime,111) as HdTime,CUST_CustomerInfo.Name from BS_WsaleNote left join BS_WsaleNoteHeader on BS_WsaleNote.WsaleNtHeaderID = BS_WsaleNoteHeader.ID";
			sql = sql + " left join CUST_CustomerInfo on BS_WsaleNoteHeader.VendorID = CUST_CustomerInfo.id ";

			sql = sql + " where BS_WsaleNote.BkcatalogID = " + dsetNote->FieldByName("BkcatalogID")->AsString ;
			sql = sql + " and BS_WsaleNoteHeader.HdTime >= '" + DateToStr(datetime) + "'";

			if (!allclient) {
				sql = sql + " and BS_WsaleNoteHeader.VendorID = " + dsetVendor->FieldByName("ID")->AsString;
			}

			//数量折扣
			dbnbedtAmount->Value = dsetNote->FieldByName("Amount")->AsInteger;
			dbnbedtDiscount->Value = dsetNote->FieldByName("Discount")->AsFloat;



			qryrecord->Close();
			qryrecord->SQL->Clear();
			qryrecord->SQL->Add(sql);
			qryrecord->Open();
			((TFloatField *)dgrecord->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0%";
			ClientTuiHuo();
			try
			{
				dsetstkamount->Parameters->ParamByName("@mode")->Value = 3;
				dsetstkamount->Parameters->ParamByName("@stgid")->Value =linfo.storageID;
				dsetstkamount->Parameters->ParamByName("@ID")->Value = dsetNote->FieldByName("ID")->AsInteger;

				if (!dsetstkamount->Active) {
				   dsetstkamount->Active= true;
				}else
				{
				   dsetstkamount->Active = false;
				   dsetstkamount->Active= true;
				}
			}
			catch(...)
			{
			}
		}
}
//---------------------------------------------------------------------------

void  TfrmWholesaleReturnMng::checkedview()
{
	String sql;
        String vendor="-1";
        if (dsetVendor->FieldByName("ID")->AsAnsiString  =="") {
           return ;
        }
	sql = "select sum(Checked) as checked,sum(Nochecked) as nochecked from BS_WsaleNoteHeader where VendorID = " + dsetVendor->FieldByName("ID")->AsAnsiString  ;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	edchecked->Text = FormatFloat("0.00",query->FieldByName("checked")->AsFloat);
	ednocheck->Text = FormatFloat("0.00",query->FieldByName("nochecked")->AsFloat);
	sql = "select CreditMoney,bond from  CUST_CustomerInfo where id = " + dsetVendor->FieldByName("ID")->AsAnsiString  ;
    query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	edbond->Text = FormatFloat("0.00",query->FieldByName("bond")->AsFloat);
	edcredit->Text = FormatFloat("0.00",query->FieldByName("CreditMoney")->AsFloat);
}
//---------------------------------------------------------------------------

bool TfrmWholesaleReturnMng::retailreturn(int catalogID)
{
	AnsiString sql;
	sql = "select * from SYS_BSSET where name = 'wosalereturn'";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	if (!query->FieldByName("value")->AsBoolean) {
		sql = " select count(*) as count from BS_WsaleNote left join BS_WsaleNoteHeader on BS_WsaleNote.WsaleNtHeaderID = BS_WsaleNoteHeader.id "
			" where BS_WsaleNote.bkcatalogID = " + IntToStr(catalogID) + " and BS_WsaleNoteHeader.VendorID = " + dsetNtHeader->FieldByName("VendorID")->AsAnsiString ;
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->Open();
		if (query->FieldByName("count")->AsInteger == 0 ) {

                        ShowMsg(Handle ,"该书没有发货过，不能退货！",3);
			return false;
		}
	}
	return true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::BtnNewClick(TObject *Sender)
{
	if (!SaveWsale(1))
	{
	  return;
	}
	//DelInvalidNtHeader();
	querydan->Active = false;
	querydan->Active = true;
	DBNav->Enabled = false;
    AnsiString sql;
	/*sql = " select * from CUST_CustomerInfo where Type in (2,3) order by name";
	dsetVendor->Active = false;
	dsetVendor->CommandText = sql;
	dsetVendor->Active = true;
	dsetVendor->First();
	dblkpcbbVendorID->KeyValue = dsetVendor->FieldByName("ID")->AsInteger ;
	cbclient->Items->Clear();
	while(!dsetVendor->Eof)
	{
		cbclient->Items->AddObject(dsetVendor->FieldByName("name")->AsAnsiString ,(TObject*)dsetVendor->FieldByName("id")->AsInteger );
		dsetVendor->Next();
	} */

	//ChangeBsmode(BSNoteSendback);
	ChangeOpmode(OPAddNtHeader);
	ednocheck->Text = "";
	edcredit->Text = "";
	edbond->Text = "";
	edchecked->Text = "";
	SaveOrNot = false;
	BtnSave->Enabled = true;
	dbnbedtAddCosts->Enabled = true;
	//cbclient->ItemIndex = cbclient->Items->IndexOfObject((TObject*)dsetVendor->FieldByName("ID")->AsInteger );
	//cbclient->ItemIndex = cbclient->Items->IndexOfObject((TObject*)1);
	dbnbedt2->Visible = true;
	dbnbedt3->Visible = true;
	dbnbedt4->Visible = true;
        dblkpcbbStaffID->Enabled=true;

        dbdtedtHdTime->Enabled = true;
	dsetNtHeader->Edit();
	dsrcNtHeader->DataSet->FieldByName("AddCosts")->Value =  0.0;
	dsrcNtHeader->DataSet->FieldByName("Remarks")->Value =  "";
	dsetNtHeader->UpdateRecord();
	membk->Text = "";
	dbnbedtAddCosts->Text = "";
	edtQryVendor->Text = "";
	editdanhao->Text = "";

	try {
		qryrecord->Active = false;
	} catch (...) {
	}
}
//---------------------------------------------------------------------------


/*void  TfrmWholesaleReturnMng::ModifyEnable()
{
    String sql = "select * from SYS_BSSET where name = 'WsalelDiscountChange'";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	if (m_opmode == OPFind) {
		dbnbedtAmount->Enabled = false;
		dbnbedtDiscount->Enabled = false;
		cbbkstackID->Enabled = false;
		if (dsetNote->FieldByName("amount")->AsInteger >= 0 ) {
			Label2->Caption = "一般发货退货单";
		}
		else
		{
			//Label2->Caption = "一般发货单";
		}
	}
	else
	{
		Label2->Caption = "一般发货退货单";
		dbnbedtAmount->Enabled = true;
		if (query->FieldByName("value")->AsBoolean  ) {
			dbnbedtDiscount->Enabled = true;
		}
	  //	cbbkstackID->Enabled = true;
	}
} */
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::cbbkstackIDKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r')
	{
		tlbtn1Click(tlbtnAddNote);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::cbbkstackIDExit(TObject *Sender)
{
	UpdateNote();
	historyview();
}

//---------------------------------------------------------------------------
void __fastcall TfrmWholesaleReturnMng::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F1) {   //查单
		if (!RzToolButton1->Enabled ) {
			return;
		}
		RzToolButton1->Click();
	}
	if (Key == VK_F2) {   //增单
		if (!BtnNew->Enabled ) {
			return;
		}
		BtnNew->Click();
	}
	if (Key == VK_F3) {   //保存
		if (!BtnSave->Enabled ) {
			return;
		}
		BtnSave->Click();
	}
	if (Key == VK_F4) {   //修改单头
		if (!tlbtnAddNote->Enabled ) {
			return;
		}
		tlbtnAddNote->Click();
	}
	if (Key == VK_F5) {   //删行
		if (!tlbtn2->Enabled ) {
			return;
		}
		tlbtn2->Click();
	}
	if (Key == VK_F6) {    //统一
		if (!tlbtn3->Enabled ) {
			return;
		}
		tlbtn3->Click();
	}
	if (Key == VK_F7) {    //现场收款
		if (!RzToolButton2->Enabled ) {
			return;
		}
		RzToolButton2->Click();
	}
	if (Key == VK_F8) {    //导出
		if (!tlbtn4->Enabled ) {
			return;
		}
		tlbtn4->Click();
	}
	if (Key == VK_F10) {   //打印
		if (!tlbtn5->Enabled ) {
			return;
		}
		tlbtn5->Click();
	}
	if (Key == VK_F11) {    //预览
		if (!BtnClear->Enabled ) {
			return;
		}
		BtnClear->Click();
	}

	if (Shift.Contains(ssAlt)&& Key == 67) {    //定位
		SpeedButton1->Click();
	}
	if (Shift.Contains(ssAlt)&& Key ==81  ) {  //退出
		tlbtn7->Click();
	}
	if (Shift.Contains(ssAlt)&& Key == 78 ) {  //最小化
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssAlt)&& Key == 70 ) {  //查书
		BtnView->Click();
	}
	if (Shift.Contains(ssAlt)&& Key ==90) {
		WindowState = wsNormal  ;
	}
}
//---------------------------------------------------------------------------
void TfrmWholesaleReturnMng::ReadClient()
{
  /*AnsiString sql;
  sql = "select ID,name from CUST_CustomerInfo where type =2 or type = 3 order by name";
  TADOQuery *aq = new TADOQuery(NULL);
  aq->Connection = m_con ;
  aq->Close();
  aq->SQL->Clear();
  aq->SQL->Add(sql);
  aq->Open();
  while(!aq->Eof)
  {
	cbclient->Items->AddObject(aq->FieldByName("name")->AsAnsiString ,(TObject*)aq->FieldByName("id")->AsInteger );
	aq->Next();
  }
  delete aq;
   cbclient->ItemIndex = cbclient->Items->IndexOfObject((TObject*)1);     */

}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::tlbtnAddNoteClick(TObject *Sender)
{
    if (changepassword) {
		if (!CheckOperateAuthority())
					return;
   	}
	AnsiString sql;
   sql = "select value from sys_bsset where name ='modifypxdanwei'";
   TADOQuery *aq = new TADOQuery(NULL);
   aq->Connection = m_con ;
   aq->Close();
   aq->SQL->Clear();
   aq->SQL->Add(sql);
   aq->Open();
   if (aq->FieldByName("value")->AsBoolean ) {     //显示密码
	   if (!CheckOperateAuthority())
				return;
			//cbclient->Enabled = true;
			dblkpcbbVendorID->Enabled = true;
			RzButton1->Enabled = true;
			dbnbedtAddCosts->Enabled = true;
			dblkpcbbVendorID->SetFocus();
			BtnSave->Enabled = true;
                        dblkpcbbStaffID->Enabled=true;
                        dbdtedtHdTime->Enabled = true;

   }else //不显示密码输入
   {
			//cbclient->Enabled = true;
			dblkpcbbVendorID->Enabled = true;
			RzButton1->Enabled = true;
			dbnbedtAddCosts->Enabled = true;
			dblkpcbbVendorID->SetFocus();
			BtnSave->Enabled = true;
                        dblkpcbbStaffID->Enabled=true;
                        dbdtedtHdTime->Enabled = true;
   }
   SaveOrNot = false;
   delete aq;
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::dbgrdNoteMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	  int CurrNo;
  if (Button == mbLeft ) {
	  if (!blSelect) {
		 BookMark = dsetNote->GetBookmark();   //dataset
		 blSelect  = true;
		 return;
	  }
  }
   if (Shift.Contains(ssShift)) {
		  CurrNo = dsetNote->FieldByName("ID")->AsInteger ;
		  dsetNote->DisableControls();
		  dsetNote->GotoBookmark(BookMark);
		  dbgrdNote->SelectedRows->CurrentRowSelected = true;
		  if (CurrNo > dsetNote->FieldByName("ID")->AsInteger) {
			  while(CurrNo > dsetNote->FieldByName("ID")->AsInteger)
			  {
				dbgrdNote->SelectedRows->CurrentRowSelected = true;
				dsetNote->Next();
			  }
		  }
		  if ( CurrNo < dsetNote->FieldByName("ID")->AsInteger ) {
				  while(CurrNo < dsetNote->FieldByName("ID")->AsInteger)
			  {
				dbgrdNote->SelectedRows->CurrentRowSelected = true;
				dsetNote->Prior() ;
			  }
		  }
		  dsetNote->EnableControls();
		  dsetNote->FreeBookmark(BookMark);
		  blSelect = false;
		}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::N8Click(TObject *Sender)
{
	if (dsetNote->IsEmpty()) {
		return;
	}
	AnsiString StgID;
	StgID = "-10";

	dsetNote->DisableControls();

	if (dbgrdNote->SelectedRows->Count > 0) {
		for (int i=0; i < dbgrdNote->SelectedRows->Count; i++)
		{
			dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[i];
			StgID = StgID + "," + dsetNote->FieldByName("ID")->AsString;
		}
	}
	else
	{
		StgID = StgID + "," + dsetNote->FieldByName("ID")->AsString;
	}

	spcopy->ProcedureName = "CopyData";
	spcopy->Parameters->Clear();
	spcopy->Parameters->CreateParameter("@mode",ftInteger,pdInput,sizeof(int),2);
	spcopy->Parameters->CreateParameter("@ID",ftString,pdInput,StgID.Length(),StgID.c_str());
	spcopy->Parameters->CreateParameter("@userid",ftInteger,pdInput,sizeof(int),linfo.userID );
	spcopy->ExecProc();
	dsetNote->EnableControls();

}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::N9Click(TObject *Sender)
{
	if (BtnSave->Enabled) {

                ShowMsg(Handle ,"本单还未保存，请先保存！",3);
		return;
	}
	spcopy->ProcedureName = "StickData";
	spcopy->Parameters->Clear();
	spcopy->Parameters->CreateParameter("@mode",ftInteger,pdInput,sizeof(int),4);
	spcopy->Parameters->CreateParameter("@HeadId",ftInteger,pdInput,sizeof(int),dsetNtHeader->FieldByName("ID")->AsInteger);
	spcopy->Parameters->CreateParameter("@userid",ftInteger,pdInput,sizeof(int),linfo.userID );

        spcopy->Parameters->CreateParameter("@stgid",ftInteger,pdInput,sizeof(int),linfo.storageID );

	spcopy->ExecProc();
	QryNtHeader(dsetNtHeader->FieldByName("ID")->AsInteger, true);


	Screen->Cursor = crDefault ;

}
//---------------------------------------------------------------------------

bool  TfrmWholesaleReturnMng::saleenable(int stkid)
{
	AnsiString sql;
	sql = "select * from STK_StockInventories where states = 0 and STK_bookInfoID = " + IntToStr(stkid);
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	if (query->RecordCount > 0) {

        ShowMsg(Handle ,"该书正在盘点，不能销售！",3);
		return false;
	}
	else
	{
    	sql = "select * from STK_stockxuyiDetail,STK_stockxuyiHeader where STK_stockxuyiHeader.AdjustHeaderID = STK_stockxuyiDetail.AdjustHeaderID and STK_stockxuyiHeader.state = 0 and STK_stockxuyiDetail.bkinfoid = " + IntToStr(stkid);
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->Open();
		if (query->RecordCount > 0) {

                           ShowMsg(Handle ,"该书正在盘点，不能销售！",3);
			return false;
		}
		else
		{
        	return true;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::BtnViewClick(TObject *Sender)
{
	Tfrmbookquery * frm = new Tfrmbookquery(Application,linfo.con,linfo.storageID);
	frm->ShowModal();
	delete frm;
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::cbclientExit(TObject *Sender)
{
	//wchar_t Key = '\r';
	//cbclientKeyPress(Sender,Key);
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::BtnSaveClick(TObject *Sender)
{
	/*if (changehead == 1) {
		wchar_t key = '\r';
		cbclientKeyPress(Sender, key);
	}
	try {
			ClientID = (int)(cbclient->Items->Objects[cbclient->ItemIndex]);
	} catch (...) {
			MessageBoxA(0,"请输入正确单位名称！","提示",MB_ICONINFORMATION);
			return;
	}
	dsetNtHeader->Edit();
	dsrcNtHeader->DataSet->FieldByName("VendorID")->Value =  ClientID;
	dsetNtHeader->UpdateRecord();
	dblkpcbbVendorID->KeyValue =  ClientID;
	UpdateNtHeader();     */
	if (!SaveOK()) {
		return;
	}else GetHtHeaderTotal();
	edtCatalog->SetFocus();
}
//---------------------------------------------------------------------------

bool TfrmWholesaleReturnMng::SaveOK()
{
   /* if (cbclient->Enabled) {
        MessageBoxA(0,"请在单位处用回车键确认客户！","提示",MB_ICONASTERISK);
		return false;
  }

	if (dsetNtHeader->RecordCount > 0) {
		AnsiString sql = "update BS_WsaleNoteHeader set HdTime = '" + DateToStr(dtpdate->Date)  + "',VendorID = " + IntToStr(ClientID) + " where id = " + dsetNtHeader->FieldByName("id")->AsString ;
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->ExecSQL();
	}  */

         dsetNtHeader->Edit();
	 dsrcNtHeader->DataSet->FieldByName("VendorID")->Value =  dsetVendor->FieldByName("ID")->AsInteger;
         dsrcNtHeader->DataSet->FieldByName("HdTime")->Value = dbdtedtHdTime->DateTime ;
         dsrcNtHeader->DataSet->FieldByName("addCosts")->Value =  dbnbedtAddCosts->Value ;
          if (dblkpcbbStaffID->ItemIndex!=-1) {
                  dsrcNtHeader->DataSet->FieldByName("StaffID")->AsInteger= (int)(dblkpcbbStaffID->Items->Objects[dblkpcbbStaffID->ItemIndex]);
                }

	 dsetNtHeader->UpdateBatch(arAll);

	if (dsetNote->RecordCount > 0) {
		SaveOrNot = true;
		BtnSave->Enabled = false;
		dbnbedtAddCosts->Enabled = false;
		//cbclient->Enabled = false;
		edtCatalog->SetFocus();
		dblkpcbbVendorID->Enabled = false;
                   dblkpcbbStaffID->Enabled=false;
        dbdtedtHdTime->Enabled = false;
		return true;
	}
	else if (dsetNtHeader->FieldByName("WsaleNtCode")->AsInteger != 0 ) {
		SaveOrNot = true;
		BtnSave->Enabled = false;
		dbnbedtAddCosts->Enabled = false;
		//cbclient->Enabled = false;
		edtCatalog->SetFocus();
		dblkpcbbVendorID->Enabled = false;

		return true;
	}




	spsave->Parameters->ParamByName("@MODE")->Value = 1;
	spsave->Parameters->ParamByName("@ID")->Value = dsetNtHeader->FieldByName("ID")->AsInteger ;
	spsave->Parameters->ParamByName("@STGID")->Value = linfo.storageID;
	spsave->Parameters->ParamByName("@TYPE")->Value = 2;
	spsave->Parameters->ParamByName("@CODEMODE")->Value = 1;
	spsave->Parameters->ParamByName("@ReturnCode")->Value = 0;
	spsave->Parameters->ParamByName("@ReturnCode2")->Value = 0;
	spsave->ExecProc() ;




	if (ChangeDisplay) {
		logmessage = "添加一般发货退货单" + spsave->Parameters->ParamByName("@ReturnCode2")->Value ;
	}
	else
	{
		logmessage = "添加一般发货退货单" + spsave->Parameters->ParamByName("@ReturnCode")->Value ;
	}
	AddEvent(1,"一般发货退货窗口",m_userID,m_storageID,logmessage,linfo.con);
	historyview();     //SaveBenDan
	dbedtWsaleNtCode->Text = spsave->Parameters->ParamByName("@ReturnCode")->Value ;
	editdanhao->Text = spsave->Parameters->ParamByName("@ReturnCode2")->Value ;
	SaveOrNot = true;
	BtnSave->Enabled = false;
	dbnbedtAddCosts->Enabled = false;
	//cbclient->Enabled = false;
	edtCatalog->SetFocus();
	dblkpcbbVendorID->Enabled = false;
        dblkpcbbStaffID->Enabled=false;
        dbdtedtHdTime->Enabled = false;
	QryNtHeader();
	return true;
}
//---------------------------------------------------------------------------


void __fastcall TfrmWholesaleReturnMng::cbclientDropDown(TObject *Sender)
{
	int i;
   int maxwidth;
	maxwidth = ((TComboBox*)Sender)->Width;
	for (int i=0 ; i < ((TComboBox*)Sender)->Items->Count ; i++) {
	 maxwidth = Math::Max(maxwidth, ((TComboBox*)Sender)->Canvas->TextWidth(((TComboBox*)Sender)->Items->Strings[i])+10);
	((TComboBox*)Sender)->Perform(CB_SETDROPPEDWIDTH,maxwidth,0);
	}
}
//---------------------------------------------------------------------------

 bool TfrmWholesaleReturnMng::SaveWsale(int mode)
{
    if (dsrcNote->DataSet == NULL) {
		return true;
	}
	if (!dbgrdNote->DataSource->DataSet->Active ) {
		return true;
	}
	int recordRN = dbgrdNote->DataSource->DataSet->RecordCount;
	if ((!SaveOrNot)&& (recordRN != 0)) {                      //SaveBenDan
	if (mode == 1) {                      //打印或预


                ShowMsg(Handle ,"本单还未保存，请先保存！",3);
		return false;

	}else
	{
		  if(ShowMsg(Handle ,"本单还未保存，是否需要保存？",1)==1)
		  {
			  BtnSave->Click();
		  }else
		  {
			spsave->Parameters->ParamByName("@MODE")->Value = 2;
			spsave->Parameters->ParamByName("@ID")->Value = dsetNtHeader->FieldByName("ID")->AsInteger ;
			spsave->Parameters->ParamByName("@STGID")->Value = 0;
			spsave->Parameters->ParamByName("@TYPE")->Value = 2;
			spsave->Parameters->ParamByName("@CODEMODE")->Value = 1;
			spsave->Parameters->ParamByName("@ReturnCode")->Value = 0;
			spsave->Parameters->ParamByName("@ReturnCode2")->Value = 0;
			spsave->ExecProc() ;
		  }
	  }
	}else return true;

}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::dbnbedtAddCostsExit(TObject *Sender)
{
/*	if (dsetNtHeader->RecordCount > 0) {
		AnsiString sql = "update BS_WsaleNoteHeader set AddCosts = " + FloatToStr(dsetNtHeader->FieldByName("AddCosts")->AsFloat)  + " where id = " + dsetNtHeader->FieldByName("id")->AsString ;
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->ExecSQL();
	}   */
}
//---------------------------------------------------------------------------


void __fastcall TfrmWholesaleReturnMng::dbnbedtAddCostsKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        		membk->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::DBNavClick(TObject *Sender, TNavigateBtn Button)

{
	AnsiString code ;
	code = querydan->FieldByName("WsaleNtCode")->AsAnsiString ;
	editdanhao->Text = querydan->FieldByName("WsaleNtCodeStr")->AsAnsiString ;
	QryNtHeader(code,false);
	//editclientname->Text = dsetVendor->FieldByName("Name")->AsString ;
	//cbclient->Text =  dsetVendor->FieldByName("Name")->AsString ;
    historyview();
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::RzButton1Click(TObject *Sender)
{
	String ID;
	ID = "";
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
        dsetVendor->Active = false;
		dsetVendor->CommandText = "select ID,Name from CUST_CustomerInfo where   Type in (2,3) and customerstate=1 and "+QFClientTiaoJian+" order by ID";
		dsetVendor->Active = true;
		int count1 = dsetVendor->RecordCount;

		TDetaileForm * frm = new TDetaileForm(m_app,2,1,ID.c_str() ,m_con,m_storageID);
		frm->ShowModal();
		delete frm;

		/*Tfrmclient * frm = new Tfrmclient(Application,m_con);
	   frm->FormStyle = fsNormal ;
	   frm->WindowState = wsNormal ;
	   frm->Visible = false;
	   frm->Position = poMainFormCenter ;
		frm->ShowModal();
	   delete frm;  */

		dsetVendor->Active = false;
		dsetVendor->Active = true;
		int count2 = dsetVendor->RecordCount;
		if (count2 > count1)
		{
			dsetVendor->Last();
			dblkpcbbVendorID->KeyValue = dsetVendor->FieldByName("ID")->AsInteger ;
			//dsetNtHeader->Edit();
			//dsetNtHeader->FieldByName("VendorID"/)->AsInteger = dsetVendor->FieldByName("ID")->AsInteger;
			//cbclient->Items->AddObject(dsetVendor->FieldByName("name")->AsAnsiString,(TObject*)dsetVendor->FieldByName("ID")->AsInteger);
			//cbclient->ItemIndex = cbclient->Items->IndexOfObject((TObject*)dsetVendor->FieldByName("ID")->AsInteger );
			//cbclient->SetFocus();
			//UpdateNtHeader();
			ClientID = dsetVendor->FieldByName("ID")->AsInteger;
			dsetNtHeader->Edit();
			dsrcNtHeader->DataSet->FieldByName("VendorID")->Value =  ClientID;
			dsetNtHeader->UpdateRecord();
			dblkpcbbVendorID->SetFocus();
		}
	}
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::dbgrdNoteTitleClick(TColumn *Column)
{
	if (dsetNote->IsEmpty() ) {
    	return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (dsetNote->Sort == "") {
		dsetNote->Sort =  Column->FieldName + " ASC";
	}
	else if (dsetNote->Sort == qusort) {
		dsetNote->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		dsetNote->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------

void TfrmWholesaleReturnMng::FormView()
{
	AnsiString sql;
	/*sql = "select * from BS_SYS_Formview where stgid = " + IntToStr(m_storageID) + " and ParentID = 4";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	while (!query->Eof)
	{
		if (query->FieldByName("Name")->AsAnsiString == "查单" ) {
			RzToolButton1->Visible = query->FieldByName("state")->AsBoolean ;
		}
		if (query->FieldByName("Name")->AsAnsiString == "增单" ) {
			BtnNew->Visible = query->FieldByName("state")->AsBoolean ;
		}
		if (query->FieldByName("Name")->AsAnsiString == "保存" ) {
			BtnSave->Visible = query->FieldByName("state")->AsBoolean ;
		}
		if (query->FieldByName("Name")->AsAnsiString == "修改单头" ) {
			tlbtnAddNote->Visible = query->FieldByName("state")->AsBoolean ;
		}
		if (query->FieldByName("Name")->AsAnsiString == "删行" ) {
			tlbtn2->Visible = query->FieldByName("state")->AsBoolean ;
		}
		if (query->FieldByName("Name")->AsAnsiString == "统一" ) {
			tlbtn3->Visible = query->FieldByName("state")->AsBoolean ;
		}
		if (query->FieldByName("Name")->AsAnsiString == "现场收款" ) {
			RzToolButton2->Visible = query->FieldByName("state")->AsBoolean ;
		}
		if (query->FieldByName("Name")->AsAnsiString == "Excel导出" ) {
			tlbtn4->Visible = query->FieldByName("state")->AsBoolean ;
		}
		if (query->FieldByName("Name")->AsAnsiString == "预览" ) {
			BtnClear->Visible = query->FieldByName("state")->AsBoolean ;
		}
		if (query->FieldByName("Name")->AsAnsiString == "打印" ) {
			tlbtn5->Visible = query->FieldByName("state")->AsBoolean ;
		}
		if (query->FieldByName("Name")->AsAnsiString == "查书" ) {
			BtnView->Visible = query->FieldByName("state")->AsBoolean ;
		}
		if (query->FieldByName("Name")->AsAnsiString == "最小化" ) {
			BtnAlignBottom->Visible = query->FieldByName("state")->AsBoolean ;
		}
		query->Next();
	} */
	sql = "select * from sys_printhead where modle = 1 and stgid = " + IntToStr(m_storageID) ;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();

	while (!query->Eof )
	{
		TMenuItem * item = new TMenuItem(this);
		TMenuItem * item1 = new TMenuItem(this);
		item->Caption = query->FieldByName("typename")->AsAnsiString;
		item->Tag = query->FieldByName("id")->AsInteger ;
		item->OnClick = MyClick;
		pmprint->Items->Add(item);
		item1->Caption = query->FieldByName("typename")->AsAnsiString;
		item1->Tag = query->FieldByName("id")->AsInteger ;
		item1->OnClick = MyClickPreview;
		pmpreview->Items->Add(item1);
		query->Next();
	}
}

//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::MyClick(TObject *Sender)
{
	TMenuItem *item = dynamic_cast<TMenuItem*>(Sender);
	if(item==NULL)
		return;
	Print(0,1,item->Tag);
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::MyClickPreview(TObject *Sender)
{
	TMenuItem *item = dynamic_cast<TMenuItem*>(Sender);
	if(item==NULL)
		return;
	Print(1,1,item->Tag);
}

//---------------------------------------------------------------------------
void TfrmWholesaleReturnMng::ClientTuiHuo()
{
 FLOAT yeartuihuo,timetuihuo;
 yeartuihuo =0.00,
 timetuihuo =0.00;
 int totalamountall;
	   sptuihuo1->Parameters->ParamByName("@clientID")->Value =  ClientID;
	   sptuihuo1->Parameters->ParamByName("@timelv")->Value =  0.00;
	   sptuihuo1->Parameters->ParamByName("@yearlv")->Value =  0.00;
	   sptuihuo1->Parameters->ParamByName("@totaltuihuoall")->Value =  0;
	   sptuihuo1->ExecProc();
	   timetuihuo = sptuihuo1->Parameters->ParamByName("@timelv")->Value;
	   yeartuihuo = sptuihuo1->Parameters->ParamByName("@yearlv")->Value;
	   totalamountall = sptuihuo1->Parameters->ParamByName("@totaltuihuoall")->Value;

	  // edittuihuo->Text =  IntToStr(totalamountall);
	   editlv1->Text = FormatFloat("0.00",yeartuihuo) + "%" ;
	   editallyear->Text  = FormatFloat("0.00",timetuihuo)+ "%" ;

	   if (yeartuihuo >= 100.00) {
		 editlv1->Color = clRed ;
	   }else
	   {
		editlv1->Color = cl3DLight  ;
	   }

	   if (timetuihuo >= 100.00) {
		  editallyear->Color = clRed;
	   }
	   else
	   {
        editallyear->Color = cl3DLight ;

	   }
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::N10Click(TObject *Sender)
{
	if (N10->Checked ) {
		N13->Checked = false;
		printmodle = 0;
	}
	else
	{
		N13->Checked = true;
		printmodle = 1;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::N13Click(TObject *Sender)
{
	if (N13->Checked ) {
		N10->Checked = false;
		printmodle = 1;
	}
	else
	{
		N10->Checked = true;
		printmodle = 0;
	}
}
//---------------------------------------------------------------------------
void  TfrmWholesaleReturnMng::operterview(int operterid)
{
	AnsiString sql;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = linfo.con ;
	sql = "select name from sys_user where id = " + IntToStr(operterid);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	lblOpName->Caption = aq->FieldByName("name")->AsString;
	delete aq;
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::membkKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r')
	{
		//BtnSave->Click();
		if (dsetNtHeader->RecordCount > 0) {
			AnsiString sql = "update BS_WsaleNoteHeader set Remarks = '" + membk->Text + "' where id = " + dsetNtHeader->FieldByName("id")->AsString ;
			query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->ExecSQL();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::SpeedButton1Click(TObject *Sender)
{
	if (GroupBox1->Visible) {
		GroupBox1->Visible = false;
	}
	else
	{
    	GroupBox1->Visible = true;
	}

}
//---------------------------------------------------------------------------


void __fastcall TfrmWholesaleReturnMng::N14Click(TObject *Sender)
{
	lblCatalog->Caption = "作者";
	m_catalogSearchMode=5;
	edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::chfsluruClick(TObject *Sender)
{
	if (chfsluru->Checked ) {
		chfoceset->Checked = true;
	}
	else if (chfsamount->Checked ) {
		chfoceset->Checked = true;
	}
	else if (chfsdiscount->Checked ) {
		chfoceset->Checked = true;
	}
	else
	{
		chfoceset->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::editpriceKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		if (dsetNote->IsEmpty() ) {
			return;
		}
		float fajia;
		float discount;
		try {
			fajia = StrToFloat(editprice->Text);
			discount =  fajia*100/dsetNote->FieldByName("price")->AsFloat;
			dbnbedtDiscount->Value =  discount;

			editprice->Text = FormatFloat("0.00",fajia);
			/*dsetNote->Edit();
			dsetNote->FieldByName("Discount")->AsFloat = discount;
			dsetNote->Post(); */
			UpdateNote();

			historyview();
		} catch (...) {
			return;
		}
		edtCatalog->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::N15Click(TObject *Sender)
{
	if (dsetNote->IsEmpty() ) {
        return;
	}
	Tfrmbookhistory *frm = new Tfrmbookhistory(Application,m_con,m_storageID,dsetNote->FieldByName("BkcatalogID")->AsInteger );
frm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::dbnbedtAmountKeyPress(TObject *Sender, wchar_t &Key)

{
	//
	if (Key == '\r')
	{
		if (dsetNote->FieldByName("BkcatalogID")->AsString == "") {
			return;
		}
		Key = 0;
		if (dbnbedtAmount->Text == "") {
			dbnbedtAmount->Text ="0";
		}

		if (tuihuocatch(dbnbedtAmount->IntValue,dsetNote->FieldByName("BkcatalogID")->AsInteger)) {
        	if (chfoceset->Checked) {
				if (chfsdiscount->Checked) {
					Perform(WM_NEXTDLGCTL, 0, 0);
				}
				else if (chfsluru->Checked) {
					edtCatalog->SetFocus();
				}
				else if (chfsamount->Checked) {
					if (!dsetNote->Eof) {
						dbgrdNote->SetFocus();
						dsetNote->Next();
						dbgrdNote->SelectedRows->CurrentRowSelected = true;
						dbnbedtAmount->SetFocus();
					}
				}
			}
			else
			{
				Perform(WM_NEXTDLGCTL, 0, 0);
			}
		}
		else
		{

                ShowMsg(Handle ,"退货数量大于发货数量!",3);
			dbnbedtAmount->Value = 0;
		}
	}
}
//---------------------------------------------------------------------------

bool TfrmWholesaleReturnMng::tuihuocatch(int amount,int bkcatalogid)
{
	if (bearsaledataset->FieldByName("value")->AsBoolean) {
        amount = abs(amount);
		AnsiString sql;
		sql = "select sum(BS_WsaleNote.amount) as amount from BS_WsaleNote left join BS_WsaleNoteHeader "
			" on BS_WsaleNote.WsaleNtHeaderID = BS_WsaleNoteHeader.id "
			" where BS_WsaleNote.bkcatalogid = " + IntToStr(bkcatalogid) + " and BS_WsaleNoteHeader.VendorID = " + IntToStr(ClientID) ;
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->Open();
		if (amount > query->FieldByName("amount")->AsInteger - dsetNote->FieldByName("Amount")->AsInteger) {
        	return false;
		}
		else
		{
        	return true;
		}
	}
	else
	{
		return true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::dblkpcbbVendorIDKeyPress(TObject *Sender,
          wchar_t &Key)
{
	if (Key == '\r') {
		if (dblkpcbbVendorID->Text == "") {
			ShowMsg(Handle ,"请选择单位！",3);
			return;
		}
			/*AnsiString sql = "select Salesman from CUST_CustomerInfo where id = " + IntToStr(ClientID);
			query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->Open();
			sql = "select * from SYS_StaffInfo where Name = '" + query->FieldByName("Salesman")->AsString + "' and stgID = " + IntToStr(m_storageID) + " and Career = 2";
			query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->Open();
			if (!query->IsEmpty() ) {
				int staff = query->FieldByName("ID")->AsInteger;

				dsetNtHeader->Edit();
				dsetNtHeader->FieldByName("StaffID")->AsInteger = staff;
				dsetNtHeader->Post();
			}



			//dbnbedtAddCosts->SetFocus();
		   //	RzButton1->Enabled = false;
		   //cbclient->Enabled = false;
		   dblkpcbbVendorID->Enabled = false;   */


                  dblkpcbbStaffID->ItemIndex =   dblkpcbbStaffID->Items->IndexOf(dsetVendor->FieldByName("salesman")->AsAnsiString);
	         	ClientID = dsetVendor->FieldByName("ID")->AsInteger ;
		checkedview();
              
		 //  dblkpcbbVendorID->Enabled = false;

		   BtnSave->Click();

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::dblkpcbbVendorIDClick(TObject *Sender)
{
	try {
		ClientID = dsetVendor->FieldByName("ID")->AsInteger ;
		checkedview();
                 dblkpcbbStaffID->ItemIndex =   dblkpcbbStaffID->Items->IndexOf(dsetVendor->FieldByName("salesman")->AsAnsiString);
    } catch (...) {
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::dbnbedtDiscountExit(TObject *Sender)
{
	if (dsetNote->RecordCount==0) {
        return;
	}else
	{

       	double price,discount;
		int amount;
		double totaldis,totalfix;

		price = dsetNote->FieldByName("price")->AsFloat ;
		discount = dbnbedtDiscount->Value;
		amount = dbnbedtAmount->Value;
		totaldis = abs(amount) * price * discount * 0.01*-1;
		totalfix = abs(amount) * price*-1;
		/*dsetNote->DisableControls();
		dsetNote->Edit();
		dsetNote->FieldByName("Discount")->AsFloat =  discount;
		dsetNote->FieldByName("FixedPrice")->AsFloat =  totalfix;
		dsetNote->FieldByName("DiscountedPrice")->AsFloat = totaldis;
		dsetNote->Post();
		dsetNote->EnableControls();  */

		UpdateNote();
		historyview();

		QryNtHeader();
    /*try
	{
		GetHtHeaderTotal();
	}
	catch(...)
	{

	} */

		editprice->Text =  FormatFloat("0.00", dsetNote->FieldByName("price")->AsFloat * dbnbedtDiscount->Value * 0.01);
	/*if (dblkpcbbVendorID->Text == "") {
		dblkpcbbVendorID->KeyValue = dsetVendor->FieldByName("ID")->AsInteger ;
	}
		*/
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::CheckBox1Click(TObject *Sender)
{
	if (CheckBox1->Checked ) {
		dgrecord->Visible = true;
	}
	else
	{
    	dgrecord->Visible = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::dsrcNoteDataChange(TObject *Sender, TField *Field)

{
	if (scroll == 1) {
		if (dsetNote->IsEmpty() ) {
			dbnbedtAmount->Text = "0";
			dbnbedtDiscount->Text = "0.00";
			editprice->Text = "0.00";
        	scroll = 0;
			return;
		}
		historyview();
		editprice->Text = FormatFloat("0.00",dsetNote->FieldByName("price")->AsFloat * dbnbedtDiscount->Value*0.01);
		scroll = 0;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::dsetNoteBeforeScroll(TDataSet *DataSet)
{
	scroll = 1;
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::rztlbr1Click(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::RzToolButton3Click(TObject *Sender)
{
//
	TfrmImport *frm = new TfrmImport(Application,m_con,dsetNtHeader->FieldByName("ID")->AsInteger,m_userID,m_storageID );
	frm->mode = 2;
        frm->stackname = "";
	if (frm->ShowModal() == mrOk  ) {
    	QryNtHeader();
	}
	delete frm;
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::A41Click(TObject *Sender)
{
    try
    {
   	Print(0,0,0);
    }catch(...)
    {ShowMsg(Handle ,"打印失败，请重试！",3);}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::N21A41Click(TObject *Sender)
{
try
   {
    if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1 && dsrcNote->DataSet != NULL)
	{
           muilprint(dsetNtHeader->FieldByName("ID")->AsString,0);
        }
   }catch(...){ShowMsg(Handle ,"打印失败，请重试！",3);};
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::A42Click(TObject *Sender)
{
          try
    {
 Print(1,0,0);
    }catch(...)
   {ShowMsg(Handle ,"打印失败，请重试！",3);}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::N21A42Click(TObject *Sender)
{
      try
   {
    if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1 && dsrcNote->DataSet != NULL)
	{
           muilprint(dsetNtHeader->FieldByName("ID")->AsString,1);
        }
   }catch(...){ShowMsg(Handle ,"打印失败，请重试！",3);};
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::A43Click(TObject *Sender)
{
    //A4批量打应
 	Tfrmorderquery1* frm = new Tfrmorderquery1(Application,m_con,m_storageID,2,1,linfo.UserName,qfclient);
                        frm->enablefahuofangshi();
			if (frm->ShowModal() == mrOk)
			{
                                if (frm->printnow) {    //用户选择打印

                                   try
                                   {
                                    A4muilprint(frm->headerid,0);
                                   }catch(...)
                                   {

                                      ShowMsg(Handle ,"打印失败，请重试！",3);
                                       delete frm;
                                       return;
                                   }
                                   }

                        }
        delete frm;
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::N21A43Click(TObject *Sender)
{
   //批量打应   2/1A4
	Tfrmorderquery1* frm = new Tfrmorderquery1(Application,m_con,m_storageID,2,1,linfo.UserName,qfclient);
                        frm->enablefahuofangshi();
			if (frm->ShowModal() == mrOk)
			{
                                if (frm->printnow) {    //用户选择打印

                                try
                                   {
                                     muilprint(frm->headerid,0);
                                   }catch(...)
                                   {

                                      ShowMsg(Handle ,"打印失败，请重试！",3);
                                       delete frm;
                                       return;
                                   }
                                   }

                        }
                        delete frm;
}
void TfrmWholesaleReturnMng::A4muilprint(AnsiString HeaderID,int type)
{

                TStringList *IDStr = new TStringList(NULL);
                AnsiString ps;
                IDStr->DelimitedText=HeaderID;
                IDStr->Delimiter=',';

		Tfrmwsaleprinta* frm = new Tfrmwsaleprinta(this,m_con);
		::ShowWindow(frm->Handle, SW_HIDE);
		LandInfo li;
		li.app = m_app;
		li.con = m_con;
		li.userID = m_userID;
		li.storageID = m_storageID;

        
		frm->pxbk = pxbk;
		frm->printtitle = printtitle;
		frm->contact = contact;
		frm->tel = tel;
		frm->address = address;
		frm->ClientName = dblkpcbbVendorID->Text ;
                frm->DanhaoChange = ChangeDisplay ;

                frm->pixiaoortuihuo = false;
               frm->A4print(HeaderID);
               /*
               for (int i=0; i < IDStr->Count; i++) {

                    if ((IDStr->Strings[i]!="-1")&&(IDStr->Strings[i]!="")) {
                        frm->pixiaoortuihuo = false;
                        frm->InputPara(StrToInt(IDStr->Strings[i]));

                        if (type == 0) {
                            frm->printmodle = -1;
                        }
                        else
                        {
                            frm->printmodle = 0;
                        }
                        frm->tuihuo = 1;
                        frm->previewprint(0,1);
                    }
               }
                     */
		frm->Close();
		delete frm;

                AnsiString sql = "update BS_WsaleNoteHeader set printcount = printcount + 1 where id in (" + HeaderID+"-1)" ;
                query->Close();
                query->SQL->Clear();
                query->SQL->Add(sql);
                query->ExecSQL();

}
//---------------------------------------------------------------------------


void __fastcall TfrmWholesaleReturnMng::N16Click(TObject *Sender)
{
//
      try
   {
    if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1 && dsrcNote->DataSet != NULL)
	{
           muilprint(dsetNtHeader->FieldByName("ID")->AsString,1,true);
        }
   }catch(...){ShowMsg(Handle ,"打印失败，请重试！",3);};
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::N17Click(TObject *Sender)
{
 //批量打应   2/1A4
	Tfrmorderquery1* frm = new Tfrmorderquery1(Application,m_con,m_storageID,2,1,linfo.UserName,qfclient);
                        frm->enablefahuofangshi();
			if (frm->ShowModal() == mrOk)
			{
                                if (frm->printnow) {    //用户选择打印

                                try
                                   {
                                     muilprint(frm->headerid,0,true);
                                   }catch(...)
                                   {

                                      ShowMsg(Handle ,"打印失败，请重试！",3);
                                       delete frm;
                                       return;
                                   }
                                   }

                        }
                        delete frm;
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::N18Click(TObject *Sender)
{
try
   {
    if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1 && dsrcNote->DataSet != NULL)
	{
           muilprint(dsetNtHeader->FieldByName("ID")->AsString,0,true);
        }
   }catch(...){ShowMsg(Handle ,"打印失败，请重试！",3);};
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleReturnMng::RzToolButton4Click(TObject *Sender)
{
    if (RzToolButton4->Caption =="显示\r主菜单")
    {

      HANDLE hWindow = FindWindow("TfrmMain",NULL);
      SendMessage(hWindow ,WM_MYMESSAGE,1,0);
      RzToolButton4->Caption ="隐藏\r主菜单";
    }else

    {
    HANDLE hWindow = FindWindow("TfrmMain",NULL);
    SendMessage(hWindow ,WM_MYMESSAGE,0,0);
      RzToolButton4->Caption ="显示\r主菜单";

    }
}
//---------------------------------------------------------------------------

