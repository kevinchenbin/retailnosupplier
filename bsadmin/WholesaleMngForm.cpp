//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "GetBsset.h"
#include "WholesaleMngForm.h"
#include "NoteCode.h"
#include "QryNoteCodeForm.h"
#include "SetNotesForm.h"
#include "mytrace.h"
//#include "SelectCustomerForm.h"
#include "RecMoneyForm.h"
#include "Print.h"
#include "SelectCatalogForm.h"
#include "..\supplier\detailemessage.h"
#include "UnitSelectClient.h"
#include "bookQuery.h"
#include "fastcheck.h"
#include "QueryDanHao.h"
#include "Addsyslog.h"
#include "UnitClient.h"
#include   <math.h>
#include "Unitorderquery.h"
#include "unitprintset.h"
#include "Orderdetail.h"
#include "Unitprintbag.h"
#include "bookhistory.h"
#include "unitorder.h"
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
#pragma link "DBCtrlsEh"
#pragma link "DBGridEh"
#pragma link "DBLookupEh"
#pragma resource "*.dfm"
TfrmWholesaleMng *frmWholesaleMng;
//---------------------------------------------------------------------------
__fastcall TfrmWholesaleMng::TfrmWholesaleMng(TComponent* Owner,int type)
	: TfrmMDIChild(Owner)
	, m_catalogSearchMode(0)
	, m_bsmode(BSUnknown)
	, m_opmode(OPUnknown)
	, m_supplierID(-1)
{
	m_module = MTWsaleMng;
	this->WindowState = wsMaximized ;
	ClientID = 1;
	Type = type;
	bakdot = 0.0;
    if (Type == 1) {
		RzToolButton2->Enabled  = false;
	}
	else
	{
		BtnNew->Enabled = false;
		tlbtn1->Enabled = false;
		tlbtnAddNote->Enabled = false;
		tlbtn2->Enabled = false;
		tlbtn3->Enabled = false;
		tlbtn4->Enabled = false;
		tlbtn5->Enabled = false;
		BtnClear->Enabled = false;
	}
	changehead = 0;
	printbagtype = 1;
	BkcatalogID = "-1";

	dbgrdNote->OnDrawColumnCell=dbgrdNoteDrawColumnCell;
}
//---------------------------------------------------------------------------
void TfrmWholesaleMng::Init(LandInfo* li)
{
	TfrmMDIChild::Init(li);
	linfo.app = li->app ;
	linfo.con = li->con ;
	linfo.userID = li->userID ;
	linfo.UserName = li->UserName ;
	linfo.storageID = li->storageID ;
	linfo.FormatStr = li->FormatStr ;
        linfo.version = li->version;
        version =     li->version;
	lblOpName->Caption = li->UserName ;
          QFClientTiaoJian=" 1=1 ";
        QFSupplierTiaoJian=" 1=1 ";


        if (li->qfclient) {
           QFClientTiaoJian=" stgid="+IntToStr(m_storageID);
        }
        qfclient= li->qfclient;
	cmdAddNtHeader->Connection = linfo.con;
	spQryNtHeader->Connection = linfo.con;
	spQryNtHeader1->Connection = linfo.con;
	cmdUpdateNtHeader->Connection = linfo.con;
	cmdAddNote->Connection = linfo.con;
	cmdUpdateNote->Connection = linfo.con;
	cmdDelNote->Connection = linfo.con;
	cmdUpdataamount->Connection = linfo.con;
	cmdDelNtHeader->Connection = linfo.con;
	cmdBatchDelNote->Connection = linfo.con;
	cmdBatchUpdateNote->Connection = linfo.con;
	cmdResetNtHeader->Connection = linfo.con;
	spQryNtHeader1->Connection = linfo.con;
	spcopy->Connection = linfo.con;
	adospcopy->Connection = linfo.con;
	cmdDelNote->Connection = linfo.con;
	dsetVendor->Connection = linfo.con;
	dsetStaff->Connection = linfo.con;
	dsetLkpVendor->Connection = linfo.con;
	dsetBkstack->Connection = linfo.con;
	qryrecord->Connection = linfo.con;
	querydan->Connection = linfo.con;
	dsetBkstack->CommandText = "select ID, Name from STK_BookstackInfo where stgid = " + IntToStr(m_storageID) ;
	dsetBkstack->Active = true;
        dsetVendor->CommandText=" select ID,Name,salesman from CUST_CustomerInfo where   Type in (2,3) and customerstate =1 and "+QFClientTiaoJian+" order by ID" ;
	dsetVendor->Active = true;
	dsetStaff->Active = true;


	bearsaledataset->Connection = linfo.con;
	bearsaledataset->Active = true;
	dsetStaff->Connection = linfo.con;
	query->Connection = m_con;
	dtGetTotal->Connection = linfo.con;
	dsetstkamount->Connection = linfo.con;
	ChangeCatalogSearchMode();
	//ChangeBsmode(BSNote);
	sphunhedabao->Connection = linfo.con; //混合打包
	aqhunhedabao->Connection = linfo.con;
	if (Type == 1) {
		ChangeOpmode(OPAddNtHeader);
	}
	else
	{
		ChangeOpmode(OPFind);
	}

	spsave->Connection = m_con;
	addnotereturnvalue = 0;

	String sql;

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

	sql = "select * from SYS_BSSET where name in('wosaleday','checkedview','WsalelDiscountChange'" ;
	sql = sql +",'salexiaoshudian','xianchangrecive','changeDanHaoDisplay','pxallclientdetail','pxdeleteusepassword', " ;
	sql = sql +"'pxfindusepassword','pxusechange','autolocalstockbyOrder','wsalesametishi','wosaleday')";

	SYSSet * BSSET = new SYSSet();

	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();

	while(!query->Eof)
	{
		 SYSSet *Note = new SYSSet();
		 Note->Name = query->FieldByName("NAME")->AsAnsiString;

		 if (query->FieldByName("NAME")->AsAnsiString=="wosaleday"||
		 query->FieldByName("NAME")->AsAnsiString=="salexiaoshudian" ||
		 query->FieldByName("NAME")->AsAnsiString=="changeDanHaoDisplay"||
		 query->FieldByName("NAME")->AsAnsiString=="wosaleday")

																	//wosaleday
		  Note->ValueStr = query->FieldByName("bk")->AsAnsiString;
		else
		  Note->ValueBool = query->FieldByName("value")->AsBoolean;

		 BSSET->Add(query->FieldByName("NAME")->AsAnsiString,(TObject*)Note);


	  query->Next();
	}
	 BSSET->GetSetInfo("wosaleday");
	 wosaleday = StrToInt(BSSET->ValueStr);
  //	BSSET->GetSetInfo("wosaleday");
  //	storageday = StrToInt(BSSET->ValueStr);
	BSSET->GetSetInfo("wosaleday");
	/*if (BSSET->ValueBool) {
		dgrecord->Visible = true;
	}
	else
	{
		dgrecord->Visible = false;
	} */

	// checkedview
	BSSET->GetSetInfo("checkedview");

	//批销折扣改变
	BSSET->GetSetInfo("WsalelDiscountChange");

	if (BSSET->ValueBool) {
		dbnbedtDiscount->Enabled = true;
	}
	else
	{
		dbnbedtDiscount->Enabled = false;
	}

	//小数点
	BSSET->GetSetInfo("salexiaoshudian");
	format = "###,###,##" + BSSET->ValueStr ;
	dbnbedt3->DisplayFormat = format;
	dbnbedt4->DisplayFormat = format;
        netotalyingfu->DisplayFormat = format;
	dbnbedt5->DisplayFormat = "###,###,##0.00";
	dbnbedt6->DisplayFormat = "###,###,##0.00";

	 //xianchangrecive

	BSSET->GetSetInfo("salexiaoshudian");

	if (BSSET->ValueBool) {
		RzToolButton2->Enabled = true;
	}
	else
	{
		RzToolButton2->Enabled = false;
	}

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

	sql = "select ID,Name from SYS_StorageInfo where id  = " + IntToStr(m_storageID) ;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	labtitle->Caption =  query->FieldByName("Name")->AsString.Trim();
	dblkpcbbVendorID->KeyValue = dsetVendor->FieldByName("ID")->AsInteger ;
	ReadClient();

	 //change danhao

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
		dgrecord->Columns->Items[1]->Visible = false;
		dgrecord->Columns->Items[0]->Visible = true;
	}

	//所有客户历史明细


	BSSET->GetSetInfo("pxallclientdetail");
	allclient  = BSSET->ValueBool  ;

	//删单密码
	BSSET->GetSetInfo("pxdeleteusepassword");
	deletedetail  = BSSET->ValueBool  ;


	//查单密码
	BSSET->GetSetInfo("pxfindusepassword");
	find  = BSSET->ValueBool  ;


	//修改单头密码是否启用

	BSSET->GetSetInfo("pxusechange");
	changepassword  = BSSET->ValueBool  ;

	// 锁定库存
	BSSET->GetSetInfo("autolocalstockbyOrder");
	localstack  = BSSET->ValueBool  ;


	// 重复提示

	BSSET->GetSetInfo("wsalesametishi");
	sametishi  = BSSET->ValueBool  ;

	delete BSSET;

	FormView();
	printmodle = 0;
}

void __fastcall TfrmWholesaleMng::FormClose(TObject *Sender, TCloseAction &Action)
{
	DelInvalidNtHeader();
	//SaveWsale(2);
	spQryNtHeader->Active = false;
	spQryNtHeader1->Active = false;
	dsetStaff->Active = false;
	dsetLkpVendor->Active = false;
	dsetBkstack->Active = false;
	dsetVendor->Active = false;
	TfrmMDIChild::FormClose(Sender, Action);
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleMng::tlbtn1Click(TObject *Sender)
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

void __fastcall TfrmWholesaleMng::tlbtn7Click(TObject *Sender)
{

        HANDLE hWindow = FindWindow("TfrmMain",NULL);
        SendMessage(hWindow ,WM_MYMESSAGE,0,0);
        Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleMng::edtQryVendorKeyPress(TObject *Sender, wchar_t &Key)
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
		ClientID = dsetVendor->FieldByName("ID")->AsInteger ;
		checkedview(1);


	       //	dsetNtHeader->Edit();
	      //	dsetNtHeader->FieldByName("VendorID")->AsInteger = dsetVendor->FieldByName("ID")->AsInteger;
	      //	dsetNtHeader->Post();
		dblkpcbbVendorID->SetFocus();
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmWholesaleMng::edtCatalogKeyPress(TObject *Sender, wchar_t &Key)
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
			ShowMsg(Handle ,"请先保存批销单！",3);
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
					frm->DoModalType = 2;
					frm->Wholefrm = this;
					frm->SetSearchMode(m_catalogSearchMode, edtCatalog->Text);
					frm->SelectAll = false;
					frm->QryBkInfo();

					if (frm->findbooks == 3) {
					   results= frm->ShowModal();
					 }else if (frm->findbooks==1) {
						results = 1;
					 }else if ((frm->findbooks==0)||(frm->findbooks==-1)) {
						results = -1 ;
					 }

					if (mrOk == results)
					{
						int bkinfoid = -1,catalogID = -1;
						if (frm->SelectAll) {        //全选　或多选
							 for (int i = 0; i < frm->lengthint  ; i++) {
								   if (!saleenable(frm->stkbkid[i])) {
									return;
								}
								 //cbbkstackID->ItemIndex = cbbkstackID->Items->IndexOfObject((TObject*)frm->BKSKid[i]);
								if (AddNote(frm->SupplierID[i],frm->BkcatalogiD[i],frm->stkbkid[i],1)) { //从数组中取出选中的数据

									 //Key = 0;
									 //Perform(WM_NEXTDLGCTL, 0, 0);
									 //historyview();

								}
							}
							QryNtHeader();
						}else     //单选
						{
							frm->GetSelectResult(bkinfoid,catalogID);
							/*if (!retailreturn(catalogID)) {
                                                        	return;
							}  */
							if (bkinfoid >= 0 && catalogID >= 0)
							{
								//cbbkstackID->ItemIndex = cbbkstackID->Items->IndexOfObject((TObject*)frm->BSKid);

								TLocateOptions Opts;
								Opts.Clear();
								Opts  <<  loPartialKey;
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


								if (samerecode) //samerecode
								{
									if (!saleenable(frm->BKinfoid)) {
										return;
									}
									if (AddNote(frm->m_supplierID,catalogID,bkinfoid,0))
									{
										if (addnotereturnvalue == -2) {
                                                                                               ShowMsg(Handle ,"不允许负库存销售！",3);

											edtCatalog->Text = "";
											addnotereturnvalue = 0;
										} else
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
												else if (chfajia->Checked ) {
													editprice->SetFocus();
												}
												else if (chfsluru->Checked) {
													edtCatalog->SetFocus();
												}
											}
											else
											{
												dbnbedtAmount ->SetFocus();
											}
										 }
										 editprice->Text =  FormatFloat("0.00", dsetNote->FieldByName("price")->AsFloat * dbnbedtDiscount->Value * 0.01);
									}
									//else
										//ShowMessage("库存无该书!");
								} else
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

void TfrmWholesaleMng::ChangeCatalogSearchMode()
{
	if (m_catalogSearchMode==3) {
		m_catalogSearchMode=5;
	}else
	{
		m_catalogSearchMode++;
	}
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

/*void TfrmWholesaleMng::ChangeBsmode(BSMode bsmode)
{
	if (bsmode != m_bsmode)
	{
		m_bsmode = bsmode;
    }

	if (m_bsmode == BSNote)
	{
		Label2->Caption = "一般发货单";
		mniBsNote->Checked = true;
		mniBsNoteSendback->Checked = false;
	}
	else if (m_bsmode == BSNoteSendback)
	{
		//grpbxNtHeader->Caption = "一般发货退货单信息";
		Label2->Caption = "一般发货退货单";
		mniBsNote->Checked = false;
		mniBsNoteSendback->Checked = true;
	}
}*/

void TfrmWholesaleMng::ChangeOpmode(OPMode opmode)
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

			Tfrmorderquery* frm = new Tfrmorderquery(Application,m_con,m_storageID,2,0,linfo.UserName,qfclient);
                        frm->fversion=linfo.version;
                        frm->enablefahuofangshi();
			if (frm->ShowModal() == mrOk)
			{
                                if (frm->printnow) {    //用户选择打印
                                    muilprint(frm->headerid,0,false);

                                }else
                                {
				String sql;
				sql = " select * from CUST_CustomerInfo where Type in(2,3) and customerstate =1 and  "+QFClientTiaoJian+" order by name ";
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
						sql = "select * from BS_WsaleNoteHeader " + sqlwhere ;
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
					//LockWindowUpdate(NULL);
				}
				m_opmode = opmode;

				delete frm;
				dblkpcbbVendorID->Enabled = false;
				BtnSave->Enabled = false;
				SaveOrNot = true;
				spnew->Enabled = false;
				dbnbedtAddCosts->Enabled = false;
				dblkpcbbStaffID->Enabled = false;
                                }
			}
		}
		break;
	case OPAddNtHeader:
		{
			dblkpcbbVendorID->Enabled = true;

			spnew->Enabled = true;
			//如果上次是添加模式，并且没有加进任何数据，则不能添加
			if (m_opmode == OPAddNtHeader &&
				dsetNote->Active && dsetNote->RecordCount < 1)
				return;

			if (m_opmode == OPDelNote  //如果上次是删除模式，并且删除所有的数据
				&& dsetNote->Active && dsetNote->RecordCount < 1)
				return;

			edtCatalog->Text = "";
			edtQryVendor->Text = "";
			editprice->Text = "0.00";
			AddNtHeader();
			m_opmode = opmode;
			edtQryVendor->SetFocus();
		}
		break;
	/*case OPDelNtHeader:
		{
			if (!CheckOperateAuthority())
				return;

			edtCatalog->Text = "";
			edtQryVendor->Text = "";
//			DelNtHeader();
			m_opmode = opmode;
        }
		break;   */
	case OPAddNote:
    	edtCatalog->Text = "";
		edtCatalog->SetFocus();
		m_opmode = opmode;
		break;
	case OPDelNote:
    	if (dsetNote->IsEmpty() ) {
			return;
		}
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

			frm->ChangeBsmode(1);
			if (frm->ShowModal() == mrOk)
			{
				int amount = 0;
				float discount = 0,pixiaodiscount = 0;
				bool bsetAmount = frm->GetAmount(amount);
				bool bsetDiscount;
				if (cbtype->ItemIndex == 0) {
					bsetDiscount = frm->GetDiscount(discount);
				}
				else
				{
					bsetDiscount = false;
				}
				bool bsetpixiaodiscount = frm->GetpixiaoDiscount(pixiaodiscount);
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
			/*AnsiString NtHeader = dbedtWsaleNtCode->Text.Trim(),Headerdate;
			if (NtHeader == "" || NtHeader == "0") {
				return;
			}
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
			}
			*/
			AnsiString sql;
			sql = " select datediff(day,getdate(),HdTime) as day from BS_WsaleNoteHeader where id = " +  dsetNtHeader->FieldByName("ID")->AsAnsiString;
			query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->Open();
			if (query->FieldByName("day")->AsInteger != 0 ) {

                                ShowMsg(Handle ,"现场收款只能收当日的！",3);
				return;
			}

			TfrmRecMoney* frm = new TfrmRecMoney(this);
			frm->format = format;
			frm->SetDiscountedPrice(dsetNtHeader->FieldByName("Totalyingshou")->AsFloat+dsetNtHeader->FieldByName("addcosts")->AsFloat);
			frm->SetChecked(dsetNtHeader->FieldByName("Checked")->AsFloat);
			frm->lbl2->Caption = "现场收款";
			frm->RzLabel1->Caption = "应收金额";
                     
			if (mrOk == frm->ShowModal())
			{
				if (frm->numedtUnchecked ->Value > 0) {

					if (ShowMsg(Handle ,"您还有未结金额，是否继续按照此金额结款？",1)!=1) {
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
				/*String sql ;
				sql = "insert into BS_WsaleNoteHeader_Attachment(wsalentcode,thistime,Time) values(" + dsetNtHeader->FieldByName("ID")->AsString + "," + FloatToStr(frm->GetReceived()) + ",getdate())";
				query->Close();
				query->SQL->Clear();
				query->SQL->Add(sql);
				query->ExecSQL(); */
			}
			delete frm;
		}
        //shoukuanview();
    	m_opmode = opmode;
    	break;
    default:
        break;
	}
	/*if (Type == 2) {
		ModifyEnable();
	} */
	//ModifyEnable();
}

void TfrmWholesaleMng::BatchSetNotes(int amount, float discount, int mode)
{
	if (dsetNote->Active && dsetNote->RecordCount >= 1)
	{
    	String ids = "";
		if (dbgrdNote->SelectedRows->Count == 0)
		{
			ids = ids + dsetNote->FieldByName("BkcatalogID")->AsString;
			if (mode != 2) {
				Backdot(discount);
			}
			if (mode !=3) {
				UpdateAmount(amount);
			}

			/*if ((mode == 1 || mode == 2) && localstack) {
				localnum(amount);
				cmdUpdateNote->Parameters->ParamByName("@ID")->Value
				= dsetNote->FieldByName("ID")->AsInteger;

				cmdUpdateNote->Parameters->ParamByName("@Amount")->Value
				= abs(dsetNote->FieldByName("Amount")->AsInteger);

				cmdUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 2;
				cmdUpdateNote->Execute();
			}  */
		}
		else if (dbgrdNote->SelectedRows->Count > 0)
		{
			dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[0];
			ids = dsetNote->FieldByName("BkcatalogID")->AsString;
			if (mode != 2) {
				Backdot(discount);
			}
			if (mode !=3) {
				UpdateAmount(amount);
			}
			/*if ((mode == 1 || mode == 2) && localstack) {
				localnum(amount);
				cmdUpdateNote->Parameters->ParamByName("@ID")->Value
				= dsetNote->FieldByName("ID")->AsInteger;

				cmdUpdateNote->Parameters->ParamByName("@Amount")->Value
				= abs(dsetNote->FieldByName("Amount")->AsInteger);

				cmdUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 2;
				cmdUpdateNote->Execute();
			}   */
			for (int i=1; i < dbgrdNote->SelectedRows->Count; i++)
			{
				dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[i];
				ids = ids + "," + dsetNote->FieldByName("BkcatalogID")->AsString;
				if (mode != 2) {
					Backdot(discount);
				}
				if (mode !=3) {
					UpdateAmount(amount);
				}
				/*if ((mode == 1 || mode == 2) && localstack) {
					localnum(amount);
					cmdUpdateNote->Parameters->ParamByName("@ID")->Value
					= dsetNote->FieldByName("ID")->AsInteger;

					cmdUpdateNote->Parameters->ParamByName("@Amount")->Value
					= abs(dsetNote->FieldByName("Amount")->AsInteger);

					cmdUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 2;
					cmdUpdateNote->Execute();
				} */
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
			//if (localstack) {
				cmdBatchUpdateNote->Parameters->ParamByName("@Amount")->Value = "";
			//}
		   //	else
		   //	{
				cmdBatchUpdateNote->Parameters->ParamByName("@Amount")->Value = amount;
		   //	}
			cmdBatchUpdateNote->Parameters->ParamByName("@Discount")->Value = discount;
			cmdBatchUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 2;
			cmdBatchUpdateNote->Parameters->ParamByName("@Ntheaderid")->Value = dsetNtHeader->FieldByName("ID")->AsAnsiString;
			cmdBatchUpdateNote->Execute();    */
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
			cmdBatchUpdateNote->Parameters->ParamByName("@Discount")->Value = discount;
			cmdBatchUpdateNote->Parameters->ParamByName("@Amount")->Value = "";
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

void __fastcall TfrmWholesaleMng::mniBsNoteSendbackClick(TObject *Sender)
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
void __fastcall TfrmWholesaleMng::tlbtn4Click(TObject *Sender)
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
bool __fastcall TfrmWholesaleMng::DbgridToExcel(TRzDBGrid* dbg)
{
	AnsiString temptext,path  ;
	int k = dbg->DataSource ->DataSet ->RecordCount ,n=0;

	savedlg->FileName = StringReplace(dblkpcbbVendorID->Text+editdanhao->Text ,"\\","-",TReplaceFlags()<<rfReplaceAll) + "发货单";
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
	   if (DeleteFileA(path))
			iFileHandle = FileCreate(path.c_str());
	   else
			return false;
	else
		iFileHandle = FileCreate(path.c_str());

	*/

	Variant  v,vSheet,R,xWorkbook;
	v   =Variant::CreateObject("Excel.Application");
	v.OlePropertySet("Visible",true);
	v.OlePropertyGet("WorkBooks").OleFunction("Add");
	xWorkbook = v.OlePropertyGet("ActiveWorkBook");
	vSheet =  xWorkbook.OlePropertyGet("ActiveSheet");


	n=0 ;

	int t1= 0;
	temptext = "\n";
	for(int q=0;q<dbg->FieldCount-1 ;++q)
	{
		if (dbg->Columns->Items[q]->Visible == true) {
			t1++;
			temptext = "'"+ dbg->Columns ->Items [q]->Title ->Caption;
			v.OlePropertyGet("Cells",1+n,(t1)).OlePropertySet("Value",temptext .c_str() );

		}
	}


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
					temptext = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsString;
                    v.OlePropertyGet("Cells",i,t1).OlePropertySet("NumberFormatLocal","@");
					v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );
					//mptext = temptext + "'" + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
				}

				else if (dbg->Columns ->Items [j-1]->FieldName == "id" || dbg->Columns ->Items [j-1]->FieldName == "backdot"){

				}
				else
				{
				
					t1++;
					temptext = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsString;
					v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
				}
			}
		}

		dbg->DataSource ->DataSet ->Next() ;
	}

    R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",n+1,1),vSheet.OlePropertyGet("Cells",t2+n+2,t1)); //取得合并的区域
	R.OlePropertyGet("Borders",2).OlePropertySet("linestyle",1);
	R.OlePropertyGet("Borders",4).OlePropertySet("linestyle",1);

	v.OlePropertyGet("Cells",t2+2+n,1).OlePropertySet("Value","合计");
	temptext = dbnbedt2->Text ;
	v.OlePropertyGet("Cells",t2+2+n,6).OlePropertySet("Value",temptext .c_str() );
	temptext = dbnbedt3->Text ;
	v.OlePropertyGet("Cells",t2+2+n,8).OlePropertySet("Value",temptext .c_str() );
	temptext = dbnbedt4->Text ;
	v.OlePropertyGet("Cells",t2+2+n,9).OlePropertySet("Value",temptext .c_str() );
	dbg->DataSource ->DataSet->EnableControls();

    try {
		xWorkbook.OleFunction("SaveAs",path.c_str());
	} catch (Exception &E) {
		//ShowMessage(E.Message);
	}

	return false;
}
//---------------------------------------------------------------------------
void TfrmWholesaleMng::GetHtHeaderTotal()
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
                netotalyingfu->Value = dbnbedtAddCosts->Value+dbnbedt4->Value ;
	}
}

//---------------------------------------------------------------------------
void TfrmWholesaleMng::QryNtHeader(String code, bool qrybkstack)
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
		GetHtHeaderTotal();//取得单头汇总

		dsetNote->AfterScroll = dsetNoteAfterScroll;
		if (qrybkstack)
		{
            QryBkstack();
		}
		ClientID = dsrcNtHeader->DataSet->FieldByName("VendorID")->Value;
	
		editdanhao->Text = dsetNtHeader->FieldByName("WsaleNtCodeStr")->AsAnsiString ;
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "###,###,##0.00";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = format;
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = format;
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("backdot"))->DisplayFormat = format;
		operterview(dsetNtHeader->FieldByName("OperatorID")->AsInteger );
		dtpdate->Date = dsetNtHeader->FieldByName("HdTime")->AsDateTime ;
		membk->Text = dsetNtHeader->FieldByName("Remarks")->AsString;
		if (dsetNtHeader->FieldByName("state")->AsInteger == 0 ) {
			cbtype->ItemIndex = 0;
		}
		else if (dsetNtHeader->FieldByName("state")->AsInteger == 2 )
		{
			cbtype->ItemIndex = 1;
		}
		cbtype->Enabled = false;
		if (dsetNtHeader->FieldByName("cwstate")->AsInteger == 1 || dsetNtHeader->FieldByName("Checked")->AsFloat != 0.00) {
			grpbxNote->Enabled = false;
			tlbtnAddNote->Enabled = false;
			tlbtn2->Enabled = false;
			tlbtn3->Enabled = false;
			Image1->Visible = true;
			checkedview(0);
		}
		else
		{
			if (cbtype->ItemIndex == 1) {
				grpbxNote->Enabled = true;
				dbnbedtDiscount->Enabled = false;
			}
			else
			{
            	if (checkedview(1)) {
					grpbxNote->Enabled = true;
				}
				else
				{
					grpbxNote->Enabled = false;
				}
			}

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

void TfrmWholesaleMng::QryNtHeader(bool qrybkstack)
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



			GetHtHeaderTotal();//取得单头汇总

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
			if (qrybkstack)
			{
				QryBkstack();
			}
			ClientID = dsrcNtHeader->DataSet->FieldByName("VendorID")->Value;

	
			editdanhao->Text = dsetNtHeader->FieldByName("WsaleNtCodeStr")->AsAnsiString ;
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00";
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "###,###,##0.00";
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = format;
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = format;
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("backdot"))->DisplayFormat = format;
			operterview(dsetNtHeader->FieldByName("OperatorID")->AsInteger );
			dtpdate->Date = dsetNtHeader->FieldByName("HdTime")->AsDateTime ;
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

void TfrmWholesaleMng::QryNtHeader(int id, bool qrybkstack)
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

        GetHtHeaderTotal();//取得单头汇总

		if (qrybkstack)
		{
			QryBkstack();
		}
		ClientID = dsrcNtHeader->DataSet->FieldByName("VendorID")->Value;
		editdanhao->Text = dsetNtHeader->FieldByName("WsaleNtCodeStr")->AsAnsiString ;
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "###,###,##0.00";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = format;
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = format;
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("backdot"))->DisplayFormat = format;
		operterview(dsetNtHeader->FieldByName("OperatorID")->AsInteger );
		dtpdate->Date = dsetNtHeader->FieldByName("HdTime")->AsDateTime ;
		membk->Text =  dsetNtHeader->FieldByName("Remarks")->AsString;
		if (dsetNtHeader->FieldByName("state")->AsInteger == 0 ) {
			cbtype->ItemIndex = 0;
			dbnbedtDiscount->Enabled = true;
		}
		else if (dsetNtHeader->FieldByName("state")->AsInteger == 2 )
		{
			cbtype->ItemIndex = 1;
			dbnbedtDiscount->Enabled = false;
		}
		if (dsetNtHeader->FieldByName("cwstate")->AsInteger == 1 ) {
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
	catch(Exception &E)
	{
		//ShowMessage("该单不存在！");
	}
}

void TfrmWholesaleMng::AddNtHeader()
{
	spQryNtHeader->Active = false;
	spQryNtHeader1->Active = false;
	cmdAddNtHeader->Parameters->ParamByName("@StgID")->Value = m_storageID;
	cmdAddNtHeader->Parameters->ParamByName("@OperatorID")->Value = m_userID;
	cmdAddNtHeader->Parameters->ParamByName("@Bsmode")->Value = 2;
	cmdAddNtHeader->Parameters->ParamByName("@CODEMODE")->Value = 0;
	MYTRACEF(_T("add note header @StgID=%d,@OperatorID=%d,@Bsmode=%d"),m_storageID,m_userID,2);
	cmdAddNtHeader->Execute();
	int id = cmdAddNtHeader->Parameters->ParamByName("@RETURN_VALUE")->Value;
	try
	{
		QryNtHeader(id);
	}
	__finally
	{

	}
}

void TfrmWholesaleMng::DelInvalidNtHeader()
{
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1
		&& dsetNote->Active && dsetNote->RecordCount < 1
		&& dsetNtHeader->FieldByName("State")->AsInteger == 0 && dsetNtHeader->FieldByName("WsaleNtCode")->AsInteger == 0)
	{
        DelNtHeader();
    }
}

void TfrmWholesaleMng::DelNtHeader()
{
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		cmdDelNtHeader->Parameters->ParamByName("@ID")->Value
			= dsetNtHeader->FieldByName("ID")->AsInteger;
		int id = dsetNtHeader->FieldByName("ID")->AsInteger;
		cmdDelNtHeader->Parameters->ParamByName("@Bsmode")->Value = 2;
		MYTRACEF(_T("del note header @ID=%d,@Bsmode=%d"), id, 2);
		cmdDelNtHeader->Execute();
	}
}

void TfrmWholesaleMng::UpdateNtHeader()
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
				dsetNtHeader->FieldByName("State")->AsInteger;
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

bool TfrmWholesaleMng::AddNote(int supplierID, int catalogID,int bkinfoid,int mod)
{
	bool result = false;
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		cmdAddNote->Parameters->ParamByName("@NtHeaderID")->Value
			= dsetNtHeader->FieldByName("ID")->AsInteger;
		cmdAddNote->Parameters->ParamByName("@BkcatalogID")->Value
			= catalogID;
		cmdAddNote->Parameters->ParamByName("@STKinfoID")->Value
            = bkinfoid; //库存号
		cmdAddNote->Parameters->ParamByName("@SupplierID")->Value = supplierID;
		//cmdAddNote->Parameters->ParamByName("@bkstackID")->Value = (int)(cbbkstackID->Items->Objects[cbbkstackID->ItemIndex]);
		if (Label11->Caption == "退货状态") {
			cmdAddNote->Parameters->ParamByName("@Bsmode")->Value = 9;
		}
		else
		{
			cmdAddNote->Parameters->ParamByName("@Bsmode")->Value = 2;
		}

		cmdAddNote->Execute();
		int ret = cmdAddNote->Parameters->ParamByName("@RETURN_VALUE")->Value;
		if (ret > 0)//插入成功
		{
			if (mod == 0) {
            	try
				{
					//LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
					Backdot(dsetNote->FieldByName("Discount")->AsFloat);
					QryNtHeader(dsetNtHeader->FieldByName("ID")->AsInteger, true);
					/*((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00%";
					((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "###,###,##0.00";
					((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = "###,###,##0.00";
					((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = "###,###,##0.00";
					((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("backdot"))->DisplayFormat = "￥###,###,##0.00";*/
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
		else if (ret == -2) { //负库存
			addnotereturnvalue = -2;
			result = true;
		}
	}
	return result;
}
void TfrmWholesaleMng::UpdateNote()
{
	if (dsetNote->Active && dsetNote->RecordCount >= 1)
	{
		cmdUpdateNote->Parameters->ParamByName("@ID")->Value
			= dsetNote->FieldByName("BkcatalogID")->AsInteger;
		/*if (Label11->Caption == "退货状态") {
			cmdUpdateNote->Parameters->ParamByName("@Amount")->Value
				= -abs(dsetNote->FieldByName("Amount")->AsInteger);
		}
		else
		{
			cmdUpdateNote->Parameters->ParamByName("@Amount")->Value
				= abs(dsetNote->FieldByName("Amount")->AsInteger);
		} */
		cmdUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 2;
		if (cbtype->ItemIndex == 0) {
			cmdUpdateNote->Parameters->ParamByName("@Discount")->Value = dbnbedtDiscount->Value ;
		}
		else
		{
			cmdUpdateNote->Parameters->ParamByName("@Discount")->Value = 0;
		}

		cmdUpdateNote->Parameters->ParamByName("@Ntheaderid")->Value = dsetNote->FieldByName("ID")->AsInteger;;
		cmdUpdateNote->Execute();
	}
	try
	{
		//LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
		QryNtHeader();
		//GetHtHeaderTotal();//取得单头汇总
		/*((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00%";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "###,###,##0.00";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = "###,###,##0.00";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = "###,###,##0.00";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("backdot"))->DisplayFormat = "￥###,###,##0.00";   */
	}
	__finally
	{
		//LockWindowUpdate(NULL);
	}
}
void TfrmWholesaleMng::DelNote()
{
	if (dsetNote->Active && dsetNote->RecordCount >= 1)
	{
		if (dbgrdNote->SelectedRows->Count == 0)
		{
			cmdDelNote->Parameters->ParamByName("@ID")->Value
				= dsetNote->FieldByName("id")->AsInteger;
			cmdDelNote->Parameters->ParamByName("@Bsmode")->Value = 2;
			cmdDelNote->Parameters->ParamByName("@Ntheaderid")->Value = dsetNote->FieldByName("ID")->AsInteger;
			if (ChangeDisplay) {
				logmessage = "删除一般发货单" + dsetNtHeader->FieldByName("WsaleNtCodeStr")->AsAnsiString ;
			}
			else
			{
				logmessage = "删除一般发货单" + dsetNtHeader->FieldByName("WsaleNtCode")->AsAnsiString ;
			}
			logmessage = logmessage + "的书目《" + dsetNote->FieldByName("CatalogName")->AsAnsiString + "》";
			AddEvent(1,"一般发货窗口",m_userID,m_storageID,logmessage,linfo.con);
			cmdDelNote->Execute();
		}
		else if (dbgrdNote->SelectedRows->Count > 0)
		{
			String ids = "";
			dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[0];
			ids = ids + dsetNote->FieldByName("id")->AsString;
			if (ChangeDisplay) {
				logmessage = "删除一般发货单" + dsetNtHeader->FieldByName("WsaleNtCodeStr")->AsAnsiString ;
			}
			else
			{
				logmessage = "删除一般发货单" + dsetNtHeader->FieldByName("WsaleNtCode")->AsAnsiString ;
			}
			logmessage = logmessage + "的书目《" + dsetNote->FieldByName("CatalogName")->AsAnsiString + "》";
			AddEvent(1,"一般发货窗口",m_userID,m_storageID,logmessage,linfo.con);
			for (int i=1; i < dbgrdNote->SelectedRows->Count; i++)
			{
				dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[i];
				ids = ids + "," + dsetNote->FieldByName("id")->AsString;
				if (ChangeDisplay) {
					logmessage = "删除一般发货单" + dsetNtHeader->FieldByName("WsaleNtCodeStr")->AsAnsiString ;
				}
				else
				{
					logmessage = "删除一般发货单" + dsetNtHeader->FieldByName("WsaleNtCode")->AsAnsiString ;
				}
				logmessage = logmessage + "的书目《" + dsetNote->FieldByName("CatalogName")->AsAnsiString + "》";
				AddEvent(1,"一般发货窗口",m_userID,m_storageID,logmessage,linfo.con);
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

void __fastcall TfrmWholesaleMng::dblkpcbbBkstackIDKeyPress(TObject *Sender, wchar_t &Key)
{
	//
	if (Key == '\r')
	{
		tlbtn1Click(tlbtnAddNote);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleMng::dbl(TObject *Sender, wchar_t &Key)
{
	//
       // return;
	if (Key == '\r')
	{
		if (dsetNote->IsEmpty() ) {
            return;
		}
		Key = 0;
		if (dbnbedtAmount->Text == "") {
			dbnbedtAmount->Text ="0";
		}

		bearsaledataset->First();
		if (!bearsaledataset->FieldByName("value")->AsBoolean && Label11->Caption == "发货状态") {     //不允许负库存销售，当前状态为发货状态
			if (StrToInt(dbnbedtAmount->Text) > StrToInt(dbnbedtTotalAmount->Text) + dsetNote->FieldByName("Amount")->AsInteger ) {

                               ShowMsg(Handle ,"销售数据大于当前库存数量！",3);
				dbnbedtAmount->Text =  IntToStr(StrToInt(dbnbedtTotalAmount->Text) + dsetNote->FieldByName("Amount")->AsInteger) ;
				if (StrToInt(dbnbedtAmount->Text) < 0 ) {
                	dbnbedtAmount->Text = "0";
				}
			}
		}
	
		if (chfoceset->Checked) {
			if (chfsdiscount->Checked) {
				Perform(WM_NEXTDLGCTL, 0, 0);
			}
			else if (chfajia->Checked ) {
				editprice->SetFocus();
			}
			else if (chfsluru->Checked) {
				edtCatalog->SetFocus();
			}
			else if (chfsamount->Checked) {
				if (!dsetNote->Eof) {
					dbgrdNote->SelectedRows->CurrentRowSelected = false;
					dbgrdNote->SetFocus();
					dsetNote->Next();
					dbgrdNote->SelectedRows->CurrentRowSelected = true;
					historyview();
					// 发价
					editprice->Text = FormatFloat("0.00",dsetNote->FieldByName("price")->AsFloat * dbnbedtDiscount->Value*0.01);
					dbnbedtAmount->SetFocus();
				}
			}
		}
		else
		{
			if (dbnbedtDiscount->Enabled ) {
				Perform(WM_NEXTDLGCTL, 0, 0);
			}
			else
			{
            	edtCatalog->SetFocus();
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleMng::dblkpcbbStaffIDExit(TObject *Sender)
{
	UpdateNtHeader();
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleMng::dbnbedtAmountExit(TObject *Sender)
{
	if (dsetNote->RecordCount==0) {
		return;
	}
		if (Label11->Caption == "退货状态") {
			dbnbedtAmount->Value = -abs(dbnbedtAmount->Value);
		}
		else
		{
			dbnbedtAmount->Value = abs(dbnbedtAmount->Value);
		}

         if (dbnbedtAmount->Value >= 100000)
                {
                    dbnbedtAmount->Value = 0;

                }
	/*if (!discountcatch(dsetNote->FieldByName("BkcatalogID")->AsInteger)) { //是否低于成本折扣等
		DelNote();
		//ResetNtHeader();
		return;
	}  */
	try
	{
		//Backdot(dbnbedtDiscount->Value);
		if (localstack) {   //锁定发货数量
			localnum(dsetNote->FieldByName("Amount")->AsInteger);
		}

		UpdateAmount(dbnbedtAmount->Value);
	      	UpdateNote();
               QryNtHeader();
	//更新当前dataset

		historyview();
	//shoukuanview();

	}
	catch(...)
	{}
}
//---------------------------------------------------------------------------
void TfrmWholesaleMng::UpdateAmount(int amount)
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

void TfrmWholesaleMng::Print(int modle,int type,int printid)//modle 1预览，2打印 type 0 默认方案 1 指定方案  prinid 方案id
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
                frm->pixiaoortuihuo=true;
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

		// frm->RvSystem1->SystemSetups<<ssAllowSetup;
		frm->RvSystem1->SystemSetups<<ssAllowDestPrinter;
		// frm->RvSystem1->SystemSetups<<ssAllowPrinterSetup;

		frm->yingshou = dbnbedt5->Value ;
		frm->fandian = dbnbedt6->Value ;
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
			frm->printmodle =printid;
		}
    	frm->tuihuo = 0;
		frm->previewprint(modle,1);
		/*if (Label2->Caption == "一般发货单")
		{
			frm->previewprint(1,1);
		}else
		{
		   frm->previewprint(2,1);
		}   */
		//1,一般发货单 2.一般发货退货单 //1打印格式1 2 打印格式2
		frm->Close();
		delete frm;
		if (modle = 0) {
        	AnsiString sql = "update BS_WsaleNoteHeader set printcount = printcount + 1 where id = " + dsetNtHeader->FieldByName("id")->AsString ;
			query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->ExecSQL();
			QryNtHeader();
		}
	}
}
void TfrmWholesaleMng::muilprint(AnsiString HeaderID,int type,bool xiaopiao)
{
    	Tfrmwsaleprinta* frm = new Tfrmwsaleprinta(this,m_con);
		::ShowWindow(frm->Handle, SW_HIDE);
		LandInfo li;
		li.app = m_app;
		li.con = m_con;
		li.userID = m_userID;
		li.storageID = m_storageID;
		frm->yingshou = dbnbedt5->Value ;
		frm->fandian = dbnbedt6->Value ;
		frm->pxbk = pxbk;
		frm->printtitle = printtitle;
		frm->contact = contact;
		frm->tel = tel;
		frm->address = address;

                frm->pixiaoortuihuo = true;
                frm->wsalemuilPrint(HeaderID,type,xiaopiao);
		frm->Close();
		delete frm;
                AnsiString sql = "update BS_WsaleNoteHeader set printcount = printcount + 1 where id in (" + HeaderID+"-1)" ;
                query->Close();
                query->SQL->Clear();
                query->SQL->Add(sql);
                query->ExecSQL();
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleMng::tlbtn5Click(TObject *Sender)
{

   if (version==0) {
     try
    {
   	Print(0,0,0);
    }catch(...)
    {ShowMsg(Handle ,"打印失败，请重试！",3);}
   }else
   {
   try
   {
    if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1 && dsrcNote->DataSet != NULL)
	{
           muilprint(dsetNtHeader->FieldByName("ID")->AsString,0,false);
        }
   }catch(...){};
   }
   //   try
   // {
   //	Print(0,0,0);
   // }catch(...)
   // {}

}
//---------------------------------------------------------------------------


void TfrmWholesaleMng::QryBkstack()
{
	/*if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1
		&& dsetNote->Active && dsetNote->RecordCount >= 1)
	{
		String sql;
		sql = " SELECT STK_BookstackInfo.ID, STK_BookstackInfo.Name "
			" FROM STK_BookInfo LEFT OUTER JOIN"
			" STK_BookstackInfo ON STK_BookInfo.BkstackID = STK_BookstackInfo.ID"
			" where SupplierID=" + dsetNote->FieldByName("SupplierID")->AsString
			 + " and BkcatalogID=" + dsetNote->FieldByName("BkcatalogID")->AsString
			 + " and STK_BookstackInfo.StgID=" + dsetNtHeader->FieldByName("StgID")->AsString;
		dsetBkstack->Active = false;
		//dblkpcbbBkstackID->ListSource = NULL;
		//dblkpcbbBkstackID->DataSource = NULL;
		dsetBkstack->CommandText = sql;
		dsetBkstack->Active = true;
		//dblkpcbbBkstackID->ListSource = dsrcBkstack;
		//dblkpcbbBkstackID->DataSource = dsrcNote;
		//ShowMessage("OK");
	}  */
}

void __fastcall TfrmWholesaleMng::dsetNoteAfterScroll(TDataSet *DataSet)
{
   //	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
      //  QryBkstack();
}
//---------------------------------------------------------------------------

/*void TfrmWholesaleMng::ResetNtHeader()
{
	//重置单头
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1
		&& dsetNote->Active && dsetNote->RecordCount < 1
		&& dsetNtHeader->FieldByName("State")->AsInteger == 0)
	{
		cmdResetNtHeader->Parameters->ParamByName("@ID")->Value =
			dsetNtHeader->FieldByName("ID")->AsInteger;
		cmdResetNtHeader->Parameters->ParamByName("@Bsmode")->Value = 2;
		cmdResetNtHeader->Execute();
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
}   */
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleMng::N1Click(TObject *Sender)
{
	lblCatalog->Caption = "书号";
	m_catalogSearchMode=1;
	edtCatalog->MaxLength = 20;
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleMng::N2Click(TObject *Sender)
{
	lblCatalog->Caption = "自编码";
	m_catalogSearchMode=2;
	edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleMng::N3Click(TObject *Sender)
{
	lblCatalog->Caption = "书名";
	m_catalogSearchMode=3;
	edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleMng::lblCatalogMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	if (Button == mbLeft ) {
		TPoint  pt;
		GetCursorPos(&pt);
		pm->Popup(pt.x,pt.y);

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleMng::N11Click(TObject *Sender)
{
  tlbtn5->Click();
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleMng::N21Click(TObject *Sender)
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


void __fastcall TfrmWholesaleMng::BtnClearClick(TObject *Sender)
{
   if(version==0)
   {

    try
    {
 Print(1,0,0);
    }catch(...)
   {ShowMsg(Handle ,"打印失败，请重试！",3);}


   }else
   {
     try
   {
    if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1 && dsrcNote->DataSet != NULL)
	{
           muilprint(dsetNtHeader->FieldByName("ID")->AsString,1,false);
        }
   }catch(...){};
    }

 //   try
  //  {
 //	Print(1,0,0);
 //   }catch(...)
 //  {}
	/*if (!SaveWsale(1))
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
		frm->InputPara(dsetNtHeader->FieldByName("ID")->AsString);

		frm->DanhaoChange = ChangeDisplay ;                      //change danhao
		frm->RvSystem1->SystemSetups >>ssAllowSetup;
		frm->RvSystem1->SystemSetups >>ssAllowDestPreview;
		frm->RvSystem1->SystemSetups >>ssAllowDestPrinter;
		frm->RvSystem1->SystemSetups >>ssAllowPrinterSetup;
		frm->RvSystem1->SystemSetups >>ssAllowDestFile;

		frm->RvSystem1->DefaultDest  = rdPreview ;
		frm->RvSystem1->SystemSetups<<ssAllowDestPreview;

		frm->yingshou = dbnbedt5->Value ;
		frm->fandian = dbnbedt6->Value ;
		frm->pxbk = pxbk;
		frm->ClientName = edtclient->Text ;
		frm->printmodle = printmodle;
		frm->previewprint(1,1);
		frm->Close();
		delete frm;
	}  */
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleMng::N22Click(TObject *Sender)
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
		frm->stgid = m_storageID;
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

void __fastcall TfrmWholesaleMng::N12Click(TObject *Sender)
{
  BtnClear->Click();
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleMng::dbnbedtDiscountKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r')
	{
		edtCatalog->Text = "";
		if (chfoceset->Checked) {
			if (chfajia->Checked ) {
				editprice->SetFocus();
			}
			else if (chfsluru->Checked) {
				edtCatalog->SetFocus();
			}
			else if (chfsamount->Checked) {
				if (!dsetNote->Eof) {
					dbgrdNote->SelectedRows->CurrentRowSelected = false;
					dbgrdNote->SetFocus();
					dsetNote->Next();
					dbgrdNote->SelectedRows->CurrentRowSelected = true;
					historyview();
					// 发价
					editprice->Text = FormatFloat("0.00",dsetNote->FieldByName("price")->AsFloat * dbnbedtDiscount->Value*0.01);
					dbnbedtAmount->SetFocus();
				}
			}
			else if (chfsdiscount->Checked) {
				if (!dsetNote->Eof) {
                	dbgrdNote->SelectedRows->CurrentRowSelected = false;
					dbgrdNote->SetFocus();
					dsetNote->Next();
					dbgrdNote->SelectedRows->CurrentRowSelected = true;
					historyview();
					// 发价
					editprice->Text = FormatFloat("0.00",dsetNote->FieldByName("price")->AsFloat * dbnbedtDiscount->Value*0.01);
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

void __fastcall TfrmWholesaleMng::FormResize(TObject *Sender)
{
	//dbgrdNote->Height = 393;
	//dbgrdNote->Width = 700;

}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleMng::N4Click(TObject *Sender)
{
	lblCatalog->Caption = "定价";
	m_catalogSearchMode=6;
	edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleMng::dbnbedtTotalAmountKeyPress(TObject *Sender, wchar_t &Key)

{
       if (Key == '\r')
	{
	  Perform(WM_NEXTDLGCTL, 0, 0);

	}
}
//---------------------------------------------------------------------------

void  TfrmWholesaleMng::FindNote(String code)
{
	DelInvalidNtHeader();
	edtCatalog->Text = "";
	edtQryVendor->Text = "";
	try
	{
		//LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
		QryNtHeader(code);
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


void __fastcall TfrmWholesaleMng::N6Click(TObject *Sender)
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

void __fastcall TfrmWholesaleMng::dbgrdNoteCellClick(TColumn *Column)
{
	//historyview();
	// 发价
	//editprice->Text = FormatFloat("0.00",dsetNote->FieldByName("price")->AsFloat * dbnbedtDiscount->Value*0.01);
}
//---------------------------------------------------------------------------

void TfrmWholesaleMng::historyview()
{
	String sql;
	if (dsetNote->RecordCount > 0) {

		DATE datetime = Date();
		datetime = datetime - wosaleday;
		sql = "select BS_WsaleNoteHeader.WsaleNtCode,BS_WsaleNoteHeader.WsaleNtCodeStr,BS_WsaleNote.Amount,BS_WsaleNote.Discount,Convert(varchar(20),BS_WsaleNoteHeader.HdTime,111) as HdTime,CUST_CustomerInfo.Name from BS_WsaleNote left join BS_WsaleNoteHeader on BS_WsaleNote.WsaleNtHeaderID = BS_WsaleNoteHeader.ID";
		sql = sql + " left join CUST_CustomerInfo on BS_WsaleNoteHeader.VendorID = CUST_CustomerInfo.id ";
		//sql = sql + " where BS_WsaleNoteHeader.VendorID = " + dsetVendor->FieldByName("ID")->AsString ;
		sql = sql + " where BS_WsaleNote.BkcatalogID = " + dsetNote->FieldByName("BkcatalogID")->AsString ;
		sql = sql + " and BS_WsaleNoteHeader.HdTime >= '" + DateToStr(datetime) + "'";
		//if (dblkpcbbVendorID->Text != "") {
		//	sql = sql + " and BS_WsaleNoteHeader.VendorID = " + dsetVendor->FieldByName("ID")->AsString ;
		//}
		if (!allclient) {
			sql = sql + " and BS_WsaleNoteHeader.VendorID = " + dsetVendor->FieldByName("ID")->AsString;
		}

		qryrecord->Close();
		qryrecord->SQL->Clear();
		qryrecord->SQL->Add(sql);
		qryrecord->Open();
		((TFloatField *)dgrecord->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00";
        int totamount = 0;
		qryrecord->DisableControls();
		qryrecord->First();
		while(!qryrecord->Eof)
		{
			totamount = totamount + qryrecord->FieldByName("Amount")->AsInteger ;
			qryrecord->Next();
		}
		qryrecord->EnableControls();
		edtotamount->Text = IntToStr(totamount);

		//添加值到数量折扣里

		dbnbedtAmount->Value = dsetNote->FieldByName("Amount")->AsInteger;
		dbnbedtDiscount->Value = dsetNote->FieldByName("Discount")->AsFloat;

			try
		{
			dsetstkamount->Parameters->ParamByName("@mode")->Value = 2;
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

bool  TfrmWholesaleMng::checkedview(int modle)
{
	AnsiString sql;
	float nocheck;
	//sql = "select sum(Checked) as checked,sum(Nochecked) as nochecked from BS_WsaleNoteHeader where VendorID = " + dsetVendor->FieldByName("ID")->AsString ;
	sql = "select sum(Checked) as checked,sum(Nochecked) as nochecked from BS_WsaleNoteHeader where VendorID = " + IntToStr(ClientID) ;


      //	sql = "select CreditMoney,bond from CUST_CustomerInfo where id = " + IntToStr(ClientID) ;
       TADOQuery *aq = new TADOQuery(Application);

        aq->Connection = m_con;
        aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
       edchecked->Text  =FormatFloat("0.00",aq->FieldByName("checked")->AsFloat);
       ednocheck->Text =FormatFloat("0.00",aq->FieldByName("nochecked")->AsFloat);
        delete aq;
        return true;
      /*	if (modle == 0) {
		return true;
	}
	else
	{
		if (nocheck > query->FieldByName("CreditMoney")->AsFloat && query->FieldByName("bond")->AsFloat > 0) {
                       ;
			if (ShowMsg(Handle ,"该客户的未结金额超过信用额度，是否继续?",1)==1 )
			{
				return true;
			}else
			{
				return false;
			}
		}
		else
		{
			return true;
		}
	} */
}
//---------------------------------------------------------------------------

/*bool TfrmWholesaleMng::retailreturn(int catalogID)
{
    String sql;
	if (Label2->Caption == "一般发货退货单") {
	sql = "select * from SYS_BSSET where name = 'wosalereturn'";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	if (!query->FieldByName("value")->AsBoolean) {
		sql = "select count(*) as count from BS_WsaleNote left join STK_BookInfo on BS_WsaleNote.BkInfoID = STK_BookInfo.ID "
		" left join BS_BookCatalog on STK_BookInfo.BkcatalogID = BS_BookCatalog.ID where BS_BookCatalog.ID = " + IntToStr(catalogID);
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->Open();
		if (query->FieldByName("count")->AsInteger == 0 ) {
			MessageBox(0,"该书没有一般发货过，不能退货！","一般发货退货" ,MB_OK);
			return false;
		}
	}
	}
	return true;
} */
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleMng::BtnNewClick(TObject *Sender)
{
	if (!SaveWsale(1))
	{
		return;
	}
	AnsiString sql;
	sql = " select * from CUST_CustomerInfo where Type in(2,3) and customerstate =1 and "+QFClientTiaoJian+" order by name";
	dsetVendor->Active = false;
	dsetVendor->CommandText = sql;
	dsetVendor->Active = true;
    querydan->Active = false;
	querydan->Active = true;
	DBNav->Enabled = false;

	//ChangeBsmode(BSNote);
	ChangeOpmode(OPAddNtHeader);
	ednocheck->Text = "";
	edcredit->Text = "";
	edbond->Text = "";
	edchecked->Text = "";
	BtnSave->Enabled = true;
	dbnbedtAddCosts->Enabled = true;
	dblkpcbbStaffID->Enabled =  true;
	SaveOrNot = false;
	dbedtWsaleNtCode->Text = "";//SaveBenDan
	cbtype->Enabled = true;
	cbtype->ItemIndex = 0;
	dbnbedtDiscount->Enabled = true;

	dbnbedt2->Visible = true;
	dbnbedt3->Visible = true;
	dbnbedt4->Visible = true;
	dsetNtHeader->Edit();
	dsrcNtHeader->DataSet->FieldByName("AddCosts")->Value =  0.0;
	dsrcNtHeader->DataSet->FieldByName("Remarks")->Value =  "";
	dsetNtHeader->UpdateRecord();
	membk->Text = "";
	dbnbedtAddCosts->Text = "0.0";
	edtQryVendor->Text = "";
	editdanhao->Text = "";
	dblkpcbbStaffID->ItemIndex = -1;
	try {
		qryrecord->Active = false;
	} catch (...) {
	}
}
//---------------------------------------------------------------------------

/*void  TfrmWholesaleMng::ModifyEnable()
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
		edtCatalog->Enabled = false;
	}
	else
	{
		Label2->Caption = "一般发货单";
		dbnbedtAmount->Enabled = true;
		edtCatalog->Enabled = true;
		if (query->FieldByName("value")->AsBoolean  ) {
			dbnbedtDiscount->Enabled = true;
		}
	  //	cbbkstackID->Enabled = true;
	}
}  */
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleMng::cbbkstackIDExit(TObject *Sender)
{
	UpdateNote();
	historyview();
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleMng::cbbkstackIDKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r')
	{
		tlbtn1Click(tlbtnAddNote);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleMng::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F1) {  //查单
		if (!RzToolButton1->Enabled ) {
			return;
		}
		RzToolButton1->Click();
	}
	if (Key == VK_F2) {  //增单
		if (!BtnNew->Enabled ) {
			return;
		}
		BtnNew->Click();
	}
	if (Key == VK_F3) {  //保存
		if (!BtnSave->Enabled ) {
			return;
		}
		BtnSave->Click();
	}
	if (Key == VK_F4) {  //修改单头
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
	if (Key == VK_F6) {   //统一
		if (!tlbtn3->Enabled ) {
			return;
		}
		tlbtn3->Click();
	}
	if (Key == VK_F7) {   //现场收款
		if (!RzToolButton2->Enabled ) {
			return;
		}
		RzToolButton2->Click();
	}
	if (Key == VK_F8) {   // 导出
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
	if (Key == VK_F12) {    //打印设置
		if (!BtnViewList->Enabled ) {
			return;
		}
		BtnViewList->Click();
	}
	if (Shift.Contains(ssAlt)&& Key == 67) {    //定位
		SpeedButton1->Click();
	}

	if (Shift.Contains(ssAlt)&& Key ==81  ) { //退出
	   tlbtn7->Click();
	}
	if (Shift.Contains(ssAlt)&& Key == 78 ) {    //最小化
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssAlt)&& Key == 70 ) {   //查书
		BtnView->Click();
	}
	if (Shift.Contains(ssAlt)&& Key ==90) {
		WindowState = wsNormal  ;
	}
	if (Shift.Contains(ssAlt)&& Key == 80) {    //退换
		SpeedButton2->Click();
	}
	if (Shift.Contains(ssCtrl)&& Shift.Contains(ssAlt)&& Key == 48) {    //退换

	  // dbgrdNote->Fields[11]->Visible=true;
	   if (dbgrdNote->Columns->Items[11]->Visible==true) {
		  dbgrdNote->Columns->Items[11]->Visible=false;//

	   }else
	   {
		  dbgrdNote->Columns->Items[11]->Visible=true;//
		dbgrdNote->Columns->Items[11]->Width=60;


	   }


	}


}
void TfrmWholesaleMng::ReadClient()
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
  cbclient->ItemIndex = cbclient->Items->IndexOfObject((TObject*)dsetVendor->FieldByName("ID")->AsInteger );*/

}
//---------------------------------------------------------------------------





void __fastcall TfrmWholesaleMng::tlbtnAddNoteClick(TObject *Sender)
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
			if (dsetNote->Active && dsetNote->RecordCount > 0) {
				cbtype->Enabled = false;
			}
			else
			{
				cbtype->Enabled = true;
			}
			dblkpcbbVendorID->Enabled = true;
		   //	RzButton1->Enabled = true;
			spnew->Enabled = true;
			dbnbedtAddCosts->Enabled = true;
			dblkpcbbVendorID->SetFocus();
			BtnSave->Enabled = true;
			dtpdate->Enabled =  true;
			dblkpcbbStaffID->Enabled =  true;

   }else //不显示密码输入
   {
			//cbclient->Enabled = true;
			if (dsetNote->Active && dsetNote->RecordCount > 0) {
				cbtype->Enabled = false;
			}
			else
			{
				cbtype->Enabled = true;
			}
			dblkpcbbVendorID->Enabled = true;
		//	RzButton1->Enabled = true;
			spnew->Enabled = true;
			dbnbedtAddCosts->Enabled = true;
			dblkpcbbVendorID->SetFocus();
			BtnSave->Enabled = true;
			dtpdate->Enabled =  true;
			dblkpcbbStaffID->Enabled =  true;
   }
   SaveOrNot = false;
   delete aq;
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleMng::dbgrdNoteMouseUp(TObject *Sender, TMouseButton Button,
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

void __fastcall TfrmWholesaleMng::N8Click(TObject *Sender)
{
	if (dsetNote->IsEmpty() ) {
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

void __fastcall TfrmWholesaleMng::N9Click(TObject *Sender)
{
	if (BtnSave->Enabled) {

                ShowMsg(Handle ,"本单还未保存，请先保存！",3);
		return;
	}
	spcopy->ProcedureName = "StickData";
	spcopy->Parameters->Clear();
	spcopy->Parameters->CreateParameter("@mode",ftInteger,pdInput,sizeof(int),2);
	spcopy->Parameters->CreateParameter("@HeadId",ftInteger,pdInput,sizeof(int),dsetNtHeader->FieldByName("ID")->AsInteger);
	spcopy->Parameters->CreateParameter("@userid",ftInteger,pdInput,sizeof(int),linfo.userID );

        spcopy->Parameters->CreateParameter("@stgid",ftInteger,pdInput,sizeof(int),linfo.storageID );
	spcopy->ExecProc();
	QryNtHeader(dsetNtHeader->FieldByName("ID")->AsInteger, true);

	Screen->Cursor = crDefault ;

}
//---------------------------------------------------------------------------

bool  TfrmWholesaleMng::saleenable(int stkid)
{
	AnsiString sql;
	sql = "select * from STK_StockInventories where states = 0 and notecode <>'' and STK_bookInfoID = " + IntToStr(stkid);
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
bool  TfrmWholesaleMng::discountcatch(int stkid)
{
	AnsiString sql;
	sql = "select * from SYS_BSSET where name = 'lowcostenable'";    //是否可以低于成本折扣
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	if (query->FieldByName("value")->AsBoolean == false ) {
		sql = "select top 1 Discount from BS_StorageNote where bkcatalogID = " + IntToStr(stkid) + " order by id DESC";
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->Open();
		if (dbnbedtDiscount->Value < query->FieldByName("Discount")->AsFloat ) {

                        ShowMsg(Handle ,"批销折扣低于成本折扣，不能发货！",3);
			return false;
		}
	}
	sql = "select * from SYS_BSSET where name = 'lowcostalter'";    //低于成本折扣提示
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	if (query->FieldByName("value")->AsBoolean == true ) {
		sql = "select top 1 Discount from BS_StorageNote where bkcatalogID = " + IntToStr(stkid) + " order by id DESC";
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->Open();
		if (dbnbedtDiscount->Value < query->FieldByName("Discount")->AsFloat ) {

                        ShowMsg(Handle ,"批销折扣低于成本折扣！",3);
		}
	}

	sql = "select * from SYS_BSSET where name = 'lownormalenable'";    //是否可以低于正常折扣
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	if (query->FieldByName("value")->AsBoolean == false ) {
		sql = "select top 1 wsalediscount from BS_StorageNote where bkcatalogID = " + IntToStr(stkid) + " order by id DESC";
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->Open();
		if (dbnbedtDiscount->Value < query->FieldByName("wsalediscount")->AsFloat ) {

                        ShowMsg(Handle ,"批销折扣低于正常折扣，不能发货",3);
			return false;
		}
	}
	sql = "select * from SYS_BSSET where name = 'lownormalalter'";   //低于正常折扣提示
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	if (query->FieldByName("value")->AsBoolean == true ) {
		sql = "select top 1 wsalediscount from BS_StorageNote where bkcatalogID = " + IntToStr(stkid) + " order by id DESC";
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->Open();
		if (dbnbedtDiscount->Value < query->FieldByName("wsalediscount")->AsFloat ) {

                         ShowMsg(Handle ,"批销折扣低于正常折扣！",3);
		}
	}
	return true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleMng::BtnViewClick(TObject *Sender)
{
	Tfrmbookquery * frm = new Tfrmbookquery(Application,linfo.con,linfo.storageID);
	frm->ShowModal();
	delete frm;
}
//---------------------------------------------------------------------------
bool TfrmWholesaleMng::SaveWsale(int mode)
{
	if (dsrcNote->DataSet == NULL) {
        return true;
	}
	if (dsetNote->IsEmpty() ) {
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
			spsave->Parameters->ParamByName("@CODEMODE")->Value = 0;
			spsave->Parameters->ParamByName("@ReturnCode")->Value = 0;
			spsave->Parameters->ParamByName("@ReturnCode2")->Value = 0;
			spsave->ExecProc() ;
		  }
	}
	}else return true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleMng::cbclientExit(TObject *Sender)
{
   //	wchar_t Key = '\r';
  //	cbclientKeyPress(Sender,Key);
 // cbclient->ItemIndex = cbclient->Items->IndexOfObject((TObject*)dsetVendor->FieldByName("ID")->AsInteger );
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleMng::BtnSaveClick(TObject *Sender)
{
	//SaveBenDan
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
	UpdateNtHeader();*/
        try
        {
	if (!SaveOK()) {

		return;
	}else
        {
           GetHtHeaderTotal();
        }
         edtCatalog->SetFocus();
        }catch(...)
        {

          ShowMsg(Handle ,"保存失败，请重新开单！",3);

        }

}
//---------------------------------------------------------------------------

bool TfrmWholesaleMng::SaveOK()
{
	ClientID = dsetVendor->FieldByName("ID")->AsInteger;
	if (!checkedview(1)) {
		return false;	
	}
	if (dsetNtHeader->IsEmpty() ) {
		return false;
	}

	dsetNtHeader->Edit();
	dsrcNtHeader->DataSet->FieldByName("VendorID")->Value =  dsetVendor->FieldByName("ID")->AsInteger;
	if (cbtype->ItemIndex == 0) {
		dsrcNtHeader->DataSet->FieldByName("State")->Value = 0;
	}
	else
	{
		dsrcNtHeader->DataSet->FieldByName("State")->Value = 2;
	}
	dsrcNtHeader->DataSet->FieldByName("HdTime")->Value = dtpdate->DateTime ;
	dsetNtHeader->UpdateBatch(arCurrent);

	if (dsetNote->RecordCount > 0 || dsetNtHeader->FieldByName("WsaleNtCode")->AsInteger != 0) {
		//dsetNtHeader->Edit();
		//dsetNtHeader->FieldByName("VendorID")->AsInteger = dsetVendor->FieldByName("ID")->AsInteger;
		//dsetNtHeader->Post();
		SaveOrNot = true;
		BtnSave->Enabled = false;
		dbnbedtAddCosts->Enabled = false;
		//cbclient->Enabled = false;
		edtCatalog->SetFocus();
		dblkpcbbVendorID->Enabled = false;
		spnew->Enabled = false;
		dtpdate->Enabled =  false;
		dblkpcbbStaffID->Enabled = false;
		cbtype->Enabled = false;

		return true;
	}
	/*
	else if (dsetNtHeader->FieldByName("WsaleNtCode")->AsInteger != 0 ) {

		SaveOrNot = true;
		BtnSave->Enabled = false;
		dbnbedtAddCosts->Enabled = false;
		//cbclient->Enabled = false;
		dblkpcbbVendorID->Enabled = false;
		spnew->Enabled = false;
		dtpdate->Enabled =  false;
		dblkpcbbStaffID->Enabled = false;
		return true;
	}  */
	spsave->Parameters->ParamByName("@MODE")->Value = 1;
	spsave->Parameters->ParamByName("@ID")->Value = dsetNtHeader->FieldByName("ID")->AsInteger ;
	spsave->Parameters->ParamByName("@STGID")->Value = linfo.storageID;
	spsave->Parameters->ParamByName("@TYPE")->Value = 2;
	spsave->Parameters->ParamByName("@CODEMODE")->Value = 0;
	spsave->Parameters->ParamByName("@ReturnCode")->Value = 0;
	spsave->Parameters->ParamByName("@ReturnCode2")->Value = 0;
	spsave->ExecProc() ;

	if (ChangeDisplay) {
		logmessage = "添加一般发货单" + spsave->Parameters->ParamByName("@ReturnCode2")->Value ;
	}
	else
	{
		logmessage = "添加一般发货单" + spsave->Parameters->ParamByName("@ReturnCode")->Value ;
	}
	AddEvent(1,"一般发货窗口",m_userID,m_storageID,logmessage,linfo.con);
	historyview();     //SaveBenDan
	dbedtWsaleNtCode->Text = spsave->Parameters->ParamByName("@ReturnCode")->Value ;
	editdanhao->Text = spsave->Parameters->ParamByName("@ReturnCode2")->Value ;
	SaveOrNot = true;
	BtnSave->Enabled = false;
	dbnbedtAddCosts->Enabled = false;
	//cbclient->Enabled = false;
	edtCatalog->SetFocus();
	dblkpcbbVendorID->Enabled = false;
	spnew->Enabled = false;
	dtpdate->Enabled =  false;
	dblkpcbbStaffID->Enabled = false;
    cbtype->Enabled = false;
	QryNtHeader();
	return true ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleMng::dbnbedtAddCostsExit(TObject *Sender)
{
   /*	if (dsetNtHeader->RecordCount > 0) {
    	AnsiString sql = "update BS_WsaleNoteHeader set AddCosts = " + FloatToStr(dsetNtHeader->FieldByName("AddCosts")->AsFloat)  + " where id = " + dsetNtHeader->FieldByName("id")->AsString ;
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->ExecSQL();
	} */
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleMng::dbnbedtAddCostsKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		membk->SetFocus();
	}
}
//---------------------------------------------------------------------------

void TfrmWholesaleMng::Backdot(float discount)

{
	/*if (dsetNote->IsEmpty() ) {
		return;
	}
	AnsiString sql;
	sql = "select * from BS_ClientBackdot where ClientID = " + dsetVendor->FieldByName("ID")->AsString + " and StgID = " + IntToStr(m_storageID);
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	bakdot = 0.0;
	float low=0.0,hight = 0.0;
	if (query->RecordCount > 0) {
		low = query->FieldByName("DiscountLow")->AsFloat ;
		hight = query->FieldByName("DiscountHight")->AsFloat ;
		if (low <= discount && hight >= discount) {
			bakdot = (dsetNote->FieldByName("FixedPrice")->AsFloat)*(query->FieldByName("BackDot")->AsFloat)/100 ;
		}
	}
	sql = "update BS_WsaleNote set backdot = " + FloatToStr(bakdot) + " where id = " + dsetNote->FieldByName("ID")->AsString ;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->ExecSQL();  */
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleMng::DBNavClick(TObject *Sender, TNavigateBtn Button)

{
	AnsiString code ;
	code = querydan->FieldByName("WsaleNtCode")->AsAnsiString ;
	editdanhao->Text = querydan->FieldByName("WsaleNtCodeStr")->AsAnsiString ;
	QryNtHeader(code,false);
	//cbclient->Text =  dsetVendor->FieldByName("Name")->AsString;
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleMng::dbnbedtDiscountExit(TObject *Sender)
{
	if (dsetNote->RecordCount==0) {
        return;
	}

		/*double jinjia;
		double discount;
		double price ;

		int amount;
		double totaldis,totalfix;

		price = dsetNote->FieldByName("price")->AsFloat ;
		discount =  dbnbedtDiscount->Value;

		amount = dbnbedtAmount->Value;

		totaldis = amount * price * discount * 0.01;
		totalfix = amount * price;
		dsetNote->DisableControls();
		dsetNote->Edit();
		dsetNote->FieldByName("Discount")->AsFloat =discount;
		dsetNote->FieldByName("DiscountedPrice")->AsFloat = totaldis;

		dsetNote->Post();
		dsetNote->EnableControls(); */
	if (!discountcatch(dsetNote->FieldByName("BkcatalogID")->AsInteger)) {
		//DelNote();
		//ResetNtHeader();
                dbnbedtDiscount->SetFocus();
		return;
	}
	try
	{
		//Backdot(dbnbedtDiscount->Value);
		UpdateNote();

		historyview();
		//shoukuanview();

		editprice->Text =  FormatFloat("0.00", dsetNote->FieldByName("price")->AsFloat * dbnbedtDiscount->Value * 0.01);
		//if (dblkpcbbVendorID->Text == "") {
			//dblkpcbbVendorID->KeyValue = dsetVendor->FieldByName("ID")->AsInteger ;
		//}
	}
	catch(...)
	{}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleMng::spnewClick(TObject *Sender)
{
	String ID;
	ID = "";
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		dsetVendor->Active = false;
		dsetVendor->CommandText = "select ID,Name,salesman from CUST_CustomerInfo where Type in (2,3)  and customerstate =1 and "+QFClientTiaoJian+" order by ID";
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
			dsetVendor->Last() ;
			dblkpcbbVendorID->KeyValue = dsetVendor->FieldByName("ID")->AsInteger ;
			//dsetNtHeader->Edit();
			//dsetNtHeader->FieldByName("VendorID")->AsInteger = dsetVendor->FieldByName("ID")->AsInteger;
			//editclientname->Text = dsetVendor->FieldByName("name")->AsAnsiString ;
			//cbclient->Items->AddObject(dsetVendor->FieldByName("name")->AsAnsiString,(TObject*)dsetVendor->FieldByName("ID")->AsInteger);
			//cbclient->ItemIndex = cbclient->Items->IndexOfObject((TObject*)dsetVendor->FieldByName("ID")->AsInteger );
			//cbclient->SetFocus();
			//UpdateNtHeader();
			ClientID = dsetVendor->FieldByName("ID")->AsInteger;
			if (!checkedview(0)) {
				return;    
			}
			dsetNtHeader->Edit();
			dsrcNtHeader->DataSet->FieldByName("VendorID")->Value =  ClientID;
			dsetNtHeader->UpdateRecord();
			dblkpcbbVendorID->SetFocus();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleMng::cbclientClick(TObject *Sender)
{
   /* try {
		ClientID = (int)(cbclient->Items->Objects[cbclient->ItemIndex]);
	} catch (...) {
    	MessageBoxA(0,"请输入正确单位名称！","提示",MB_ICONINFORMATION);
		return;
	}
	dsetNtHeader->Edit();
	dsrcNtHeader->DataSet->FieldByName("VendorID")->Value =  ClientID;
	dsetNtHeader->UpdateRecord();
	dblkpcbbVendorID->KeyValue =  ClientID;
	UpdateNtHeader();
	checkedview();    */
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleMng::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleMng::dbgrdNoteTitleClick(TColumn *Column)
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

void TfrmWholesaleMng::FormView()
{
	AnsiString sql;
	/*sql = "select * from BS_SYS_Formview where stgid = " + IntToStr(m_storageID) + " and ParentID = 3";
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
		if (query->FieldByName("Name")->AsAnsiString == "打印设置" ) {
			BtnViewList->Visible = query->FieldByName("state")->AsBoolean ;
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

void __fastcall TfrmWholesaleMng::MyClick(TObject *Sender)
{
	TMenuItem *item = dynamic_cast<TMenuItem*>(Sender);
	if(item==NULL)
		return;
	Print(0,1,item->Tag);
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleMng::MyClickPreview(TObject *Sender)
{
	TMenuItem *item = dynamic_cast<TMenuItem*>(Sender);
	if(item==NULL)
		return;
	Print(1,1,item->Tag);
}

//---------------------------------------------------------------------------



void __fastcall TfrmWholesaleMng::edtclientKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		if (dblkpcbbVendorID->Text =="") {

                        ShowMsg(Handle ,"请选择单位！",3);
			return;
		}

			AnsiString sql = "select Salesman from CUST_CustomerInfo where  customerstate =1 and id = " + IntToStr(ClientID);
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

                                dblkpcbbStaffID->ItemIndex = dblkpcbbStaffID->Items->IndexOfObject((TObject*)staff);
				dsetNtHeader->Edit();
				dsetNtHeader->FieldByName("StaffID")->AsInteger = staff;
				dsetNtHeader->Post();
			}
			dsetNtHeader->Edit();
			dsrcNtHeader->DataSet->FieldByName("VendorID")->Value =  ClientID;
			dsetNtHeader->UpdateRecord();
			dblkpcbbVendorID->KeyValue =  ClientID;
			UpdateNtHeader();

			//dbnbedtAddCosts->SetFocus();
		   //	RzButton1->Enabled = false;
		   //cbclient->Enabled = false;
		   dblkpcbbVendorID->Enabled = false;
		   spnew->Enabled = false;
		   BtnSave->Click();
	}
}
//---------------------------------------------------------------------------

void TfrmWholesaleMng::localnum(int amount)
{
	/*AnsiString sql;
	int d = dsetNote->RecordCount;
	if ((dsetNote->IsEmpty() )||(dsetNote->RecordCount == 0)) {
		return;
	}
	sql = "select usableamount from Order_lock where bkcatalogid = " + dsetNote->FieldByName("BkcatalogID")->AsString + " and stgid = " + IntToStr(m_storageID) ;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = m_con ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	if (!aq->IsEmpty() ) {
		int usableamount = aq->FieldByName("usableamount")->AsInteger ;
		sql = "select BS_OrderNote.id,UnsendAmount,localnum from BS_OrderNote join BS_OrderNoteHeader on BS_OrderNote.OrderNtHeaderID = BS_OrderNoteHeader.id where BkcatalogID = " + dsetNote->FieldByName("BkcatalogID")->AsString + " and VendorID = "  + dsetNtHeader->FieldByName("VendorID")->AsAnsiString + " and BS_OrderNoteHeader.state in (0,1) and BS_OrderNote.state = 0" ;
		aq->Connection = m_con ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		if (!aq->IsEmpty() ) {
			usableamount = usableamount + aq->FieldByName("localnum")->AsInteger;
		}
		sql = "select amount from BS_WsaleNote where id = " + dsetNote->FieldByName("ID")->AsString ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
        if (!aq->IsEmpty() ) {
			usableamount = usableamount + aq->FieldByName("amount")->AsInteger;
		}
		if (usableamount <= 0) {
			dsetNote->Edit();
			dsetNote->FieldByName("Amount")->AsInteger = 0;
			dsetNote->Post();
		}
		else if (amount > usableamount ) {
			dsetNote->Edit();
			dsetNote->FieldByName("Amount")->AsInteger = usableamount;
			dsetNote->Post();
		}
		else
		{
			dsetNote->Edit();
			dsetNote->FieldByName("Amount")->AsInteger = amount;
			dsetNote->Post();
		}
	}
	else
	{
    	dsetNote->Edit();
		dsetNote->FieldByName("Amount")->AsInteger = amount;
		dsetNote->Post();
	}
	delete aq;  */
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleMng::N10Click(TObject *Sender)
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

void __fastcall TfrmWholesaleMng::N13Click(TObject *Sender)
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


void  TfrmWholesaleMng::operterview(int operterid)
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

void __fastcall TfrmWholesaleMng::membkKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r')
	{
		//BtnSave->Click();
                try
                {
		if (dsetNtHeader->RecordCount > 0) {
			AnsiString sql = "update BS_WsaleNoteHeader set Remarks = '" + membk->Text + "' where id = " + dsetNtHeader->FieldByName("id")->AsString ;
			query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->ExecSQL();
                              //	QryNtHeader();
		}
                }catch(...)
                {
                ShowMsg(Handle ,"保存失败，请重新开单！",3);

                }
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmWholesaleMng::SpeedButton1Click(TObject *Sender)
{
	if (GroupBox2->Visible) {
		GroupBox2->Visible = false;
	}
	else
	{
    	GroupBox2->Visible = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleMng::N14Click(TObject *Sender)
{
	lblCatalog->Caption = "作者";
	m_catalogSearchMode=5;
	edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleMng::chfsluruClick(TObject *Sender)
{
	if (cbtype->ItemIndex == 1 && chfsdiscount->Checked) {
    	chfsdiscount->Checked = false;
	}
	if (chfsluru->Checked ) {
		chfoceset->Checked = true;
	}
	else if (chfsamount->Checked ) {
		chfoceset->Checked = true;
	}
	else if (chfsdiscount->Checked ) {
		chfoceset->Checked = true;
	}
	else if (chfajia->Checked ) {
		chfoceset->Checked = true;
	}
	else
	{
		chfoceset->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleMng::editpriceKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		if (dsetNote->IsEmpty() ) {
			return;
		}
		float fajia,totaldis,price;
		float discount;
		try {
			fajia = StrToFloat(editprice->Text);
			discount =  fajia*100/dsetNote->FieldByName("price")->AsFloat;
			price = dsetNote->FieldByName("price")->AsFloat;
			dbnbedtDiscount->Value =  discount;

			editprice->Text = FormatFloat("0.00",fajia);
		} catch (...) {
			return;
		}


		if (!discountcatch(dsetNote->FieldByName("BkcatalogID")->AsInteger)) {
			DelNote();
			//ResetNtHeader();
			return;
		}
		try
		{
			Backdot(dbnbedtDiscount->Value);

			/*totaldis = dsetNote->FieldByName("Amount")->AsInteger * discount * 0.01 * price;

			dsetNote->Edit();
			dsetNote->FieldByName("Discount")->AsFloat = discount;
			dsetNote->FieldByName("DiscountedPrice")->AsFloat = totaldis;
			dsetNote->Post();   */
			UpdateNote();

			historyview();
		}
		catch(...)
		{}

		edtCatalog->Text = "";
		if (chfoceset->Checked) {
			if (chfsluru->Checked) {
				edtCatalog->SetFocus();
			}
			else if (chfsamount->Checked) {
				if (!dsetNote->Eof) {
					dbgrdNote->SelectedRows->CurrentRowSelected = false;
					dbgrdNote->SetFocus();
					dsetNote->Next();
					dbgrdNote->SelectedRows->CurrentRowSelected = true;
					historyview();
					// 发价
					editprice->Text = FormatFloat("0.00",dsetNote->FieldByName("price")->AsFloat * dbnbedtDiscount->Value*0.01);
					dbnbedtAmount->SetFocus();
				}
			}
			else if (chfsdiscount->Checked) {
				if (!dsetNote->Eof) {
					dbgrdNote->SelectedRows->CurrentRowSelected = false;
					dbgrdNote->SetFocus();
					dsetNote->Next();
					dbgrdNote->SelectedRows->CurrentRowSelected = true;
					historyview();
					// 发价
					editprice->Text = FormatFloat("0.00",dsetNote->FieldByName("price")->AsFloat * dbnbedtDiscount->Value*0.01);
					dbnbedtDiscount->SetFocus();
				}
			}
			else if (chfajia->Checked) {
				if (!dsetNote->Eof) {
                	dbgrdNote->SelectedRows->CurrentRowSelected = false;
					dbgrdNote->SetFocus();
					dsetNote->Next();
					dbgrdNote->SelectedRows->CurrentRowSelected = true;
					historyview();
					// 发价
					editprice->Text = FormatFloat("0.00",dsetNote->FieldByName("price")->AsFloat * dbnbedtDiscount->Value*0.01);
					editprice->SetFocus();
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

void __fastcall TfrmWholesaleMng::BtnViewListClick(TObject *Sender)
{
       //	Tfrmprintset *frm = new Tfrmprintset(Application,m_con,1,m_storageID);
	//frm->ShowModal();
	//delete frm;
	//PrintAdd();
     	if (dsetNtHeader->IsEmpty() || dsetNote->IsEmpty()) {
		return;
	}
        if(!complierDateTime())
       {
           ShowMsg(Handle ,"只能操作当日入库单！",3);
           return;
      }

	Tfrmunitorder * frm = new Tfrmunitorder(Application,m_con,dsetNtHeader->FieldByName("id")->AsInteger,2);

	frm->rkcode = editdanhao->Text;
        frm->init(&linfo);

        frm->fuserid = m_userID;
        frm->fstgid = m_storageID;


}
bool TfrmWholesaleMng::complierDateTime()
{

   int t;

   t = StrToDateTime(FormatDateTime("yyyy-mm-dd",dsetNtHeader->FieldByName("HdTime")->AsDateTime))-StrToDateTime(FormatDateTime("yyyy-mm-dd",Now()));
   if (t==0) {
       return true;
   }else   return false;


}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleMng::dbgrdNoteDblClick(TObject *Sender)
{
	/*if (dsetNote->IsEmpty() ) {
		return;
	}
	TfrmOrderdetail *frm = new TfrmOrderdetail(Application,m_con,dsetNote->FieldByName("BkcatalogID")->AsInteger ,m_storageID );
	frm->ShowModal();
	delete frm;   */
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleMng::BtnBringtoFrontClick(TObject *Sender)
{


    if (BtnBringtoFront->Caption =="显示\r主菜单")
    {

      HANDLE hWindow = FindWindow("TfrmMain",NULL);
      SendMessage(hWindow ,WM_MYMESSAGE,1,0);
      BtnBringtoFront->Caption ="隐藏\r主菜单";
    }else

    {
    HANDLE hWindow = FindWindow("TfrmMain",NULL);
    SendMessage(hWindow ,WM_MYMESSAGE,0,0);
      BtnBringtoFront->Caption ="显示\r主菜单";

    }
	/*AnsiString xuhao;
	AnsiString BkCatalogID;
	if (dsetNote->Active && dsetNote->RecordCount >= 1)
	{
		String ids = "(";
		if (dbgrdNote->SelectedRows->Count == 0)
		{
			ids = ids + dsetNote->FieldByName("ID")->AsString;
		}
		else if (dbgrdNote->SelectedRows->Count > 0)
		{
			dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[0];
			ids = ids + dsetNote->FieldByName("ID")->AsString;
			xuhao = xuhao +  dsetNote->FieldByName("xuhao")->AsString;
			BkCatalogID = BkCatalogID + dsetNote->FieldByName("BkcatalogID")->AsString;

			for (int i=1; i < dbgrdNote->SelectedRows->Count; i++)
			{
				dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[i];
				ids = ids + "," + dsetNote->FieldByName("ID")->AsString;
				xuhao = xuhao + ","+ dsetNote->FieldByName("xuhao")->AsString;
				BkCatalogID = BkCatalogID + "," + dsetNote->FieldByName("BkcatalogID")->AsString;
			}
		}
		else
			return;

		ids = ids + ")";
		AnsiString sql = "update BS_WsaleNote set printbag = BS_BookCatalog.BookWords "
			" from BS_WsaleNote join stk_bookinfo on BS_WsaleNote.BkInfoID = stk_bookinfo.id "
			" join BS_BookCatalog on  STK_BookInfo.BkcatalogID = BS_BookCatalog.id where BS_WsaleNote.id in " + ids;
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->ExecSQL();
		Tfrmprintbag *frm = new Tfrmprintbag(Application,m_con,ids);
		frm->xuhao = xuhao;
		frm->stgid = linfo.storageID ;
		frm->userid = linfo.userID ;
		frm->headid = dsetNtHeader->FieldByName("ID")->AsInteger  ;
		frm->bkcatalogid = BkCatalogID;
		frm->ShowModal();
		delete frm;
	} */
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleMng::N19Click(TObject *Sender)
{
   //混合打包

   /* AnsiString xuhao;
	AnsiString BkCatalogID;
	if (dsetNote->Active && dsetNote->RecordCount >= 1)
	{
		String ids = "(";
		if (dbgrdNote->SelectedRows->Count == 0)
		{
			ids = ids + dsetNote->FieldByName("ID")->AsString;
		}
		else if (dbgrdNote->SelectedRows->Count > 0)
		{
			dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[0];
			ids = ids + dsetNote->FieldByName("ID")->AsString;
			xuhao = xuhao +  dsetNote->FieldByName("xuhao")->AsString;
			BkCatalogID = BkCatalogID + dsetNote->FieldByName("BkcatalogID")->AsString;

			for (int i=1; i < dbgrdNote->SelectedRows->Count; i++)
			{
				dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[i];
				ids = ids + "," + dsetNote->FieldByName("ID")->AsString;
				xuhao = xuhao + ","+ dsetNote->FieldByName("xuhao")->AsString;
				BkCatalogID = BkCatalogID + "," + dsetNote->FieldByName("BkcatalogID")->AsString;
			}
		}
		else
			return;
		}


	sphunhedabao->Parameters->ParamByName("@DanHaoID")->Value =  dsetNtHeader->FieldByName("ID")->AsInteger  ; ;
	sphunhedabao->Parameters->ParamByName("@CatalogiD")->Value = BkCatalogID;
	sphunhedabao->Parameters->ParamByName("@xuhaostr")->Value =  xuhao;
	sphunhedabao->Parameters->ParamByName("@userid")->Value = linfo.userID ;
	sphunhedabao->Parameters->ParamByName("@stgid")->Value = linfo.storageID;
	sphunhedabao->ExecProc();
	hunhedabao();   //显示    */

}
void TfrmWholesaleMng::hunhedabao()
{
	AnsiString sql ;
	sql ="select * from sys_dabaoB where stgid ="+ IntToStr(linfo.storageID)+ " and userid =" +  IntToStr(linfo.userID);

	aqhunhedabao->Close();
	aqhunhedabao->SQL->Clear();
	aqhunhedabao->SQL->Add(sql);
	aqhunhedabao->Open();


	/*aqhunhedabao->Close();
	aqhunhedabao->SQL->Clear();
	aqhunhedabao->SQL->Add("select * from sys_dabaoB");
		 aqhunhedabao->Open();    */
	Variant ex;
	Variant newxls;
	try
	{
	ex = Variant::CreateObject("Excel.Application");
	}
	catch(Exception &E)
	{
   //	  MessageBoxA(this,E.Message,"提示");

	}
	Variant sheet;

	ex.OlePropertySet("Visible",true);


	Variant WorkBook1,range1,range2,range3,range4;
	WorkBook1 = ex.OlePropertyGet("WorkBooks").OleFunction("Add");

	Variant Sheet1;
	 Sheet1 = WorkBook1.OlePropertyGet("ActiveSheet");

	int i,j,k,n,h,w;
	int XA,XB;
	AnsiString strRange1,strRange2,strRange3,strRange4,strRange5,strRange6;

	Sheet1.OlePropertyGet("Cells").OlePropertySet("ColumnWidth",15);
	Sheet1.OlePropertyGet("Cells").OlePropertySet("RowHeight",48);
	i = 1;  //左边
	j = 5;

	k = 1;  //右边
	n = 5;

	XA = 2;  //横坐标
	XB = 2;
	bool t;
	t = true;

	AnsiString bookname,price,count,xuhao,supplier,receiver,pressname,supplier1,receiver1;

	while(!aqhunhedabao->Eof)
	{

		if (t) {


				strRange1 = "A"+IntToStr(i) +":"+"D"+IntToStr(i);
				strRange3 = "A"+IntToStr(j) +":"+"D"+IntToStr(j); ;
				receiver = "收货单位:"+ aqhunhedabao->FieldByName("receiver")->AsAnsiString;
				supplier = "发货单位:"  + aqhunhedabao->FieldByName("supplier")->AsAnsiString;

				strRange5 = "A"+IntToStr(i) +":"+"D"+IntToStr(j);

				//指定区域画线
				Sheet1.OlePropertyGet("Range",strRange5.c_str()).OlePropertyGet("Borders").OlePropertySet("linestyle",1);

			   //range1 = sheet.OlePropertyGet("Cells",3,6).OlePropertySet("Value",str)
				 Sheet1.OlePropertyGet("Range", strRange1.c_str() ).OleFunction("Merge",false);
				Sheet1.OlePropertyGet("Range",strRange1.c_str()).OlePropertySet("Value", receiver.c_str());  //	range1.OlePropertySet("Value",aqhunhedabao->FieldByName("receiver")->AsAnsiString);
			   //设置字体          Bold
					Sheet1.OlePropertyGet("Range",strRange1.c_str()).OlePropertyGet("Font").OlePropertySet("size",18);
					Sheet1.OlePropertyGet("Range",strRange1.c_str()).OlePropertyGet("Font").OlePropertySet("Bold",true);
			   //居中 VerticalAlignment
				 Sheet1.OlePropertyGet("Range",strRange1.c_str()).OlePropertySet("VerticalAlignment",2);

				Sheet1.OlePropertyGet("Range", strRange3.c_str() ).OleFunction("Merge",false);
				Sheet1.OlePropertyGet("Range",strRange3.c_str()).OlePropertySet("Value",supplier.c_str() );  //	range1.OlePropertySet("Value",aqhunhedabao->FieldByName("receiver")->AsAnsiString);
				Sheet1.OlePropertyGet("Range",strRange3.c_str()).OlePropertyGet("Font").OlePropertySet("size",18);
				Sheet1.OlePropertyGet("Range",strRange3.c_str()).OlePropertyGet("Font").OlePropertySet("Bold",true);
				//居中 VerticalAlignment
				Sheet1.OlePropertyGet("Range",strRange3.c_str()).OlePropertySet("VerticalAlignment",2);


					for (int p = XA; p < XA+3; p++) {

							if (aqhunhedabao->Eof) {
								break;
							}
							bookname = "书名: " + aqhunhedabao->FieldByName("bookname")->AsAnsiString;
							xuhao =  "序号: "+ aqhunhedabao->FieldByName("xuhao")->AsAnsiString;
							count =  "版次:"+ aqhunhedabao->FieldByName("press")->AsAnsiString;
							pressname ="版别:" + aqhunhedabao->FieldByName("pressname")->AsAnsiString;
							price = "单价:"+ aqhunhedabao->FieldByName("price")->AsAnsiString;
							AnsiString content[3];
							content[4] = xuhao;
							content[1] = bookname;

							content[2] = price + "     " + count + "      " +pressname;
							content[3]  = "数量:  本";


					 for (int y = 4; y > 0; y--) {      //每格
							Sheet1.OlePropertyGet("Cells",p,y).OlePropertySet("WrapText",true);
							Sheet1.OlePropertyGet("Cells",p,y).OlePropertySet("Value",content[y].c_str());  //	range1.OlePropertySet("Value",aqhunhedabao->FieldByName("receiver")->AsAnsiString);
							Sheet1.OlePropertyGet("Cells",p,y).OlePropertyGet("Font").OlePropertySet("size",12);
							Sheet1.OlePropertyGet("Cells",p,y).OlePropertyGet("Font").OlePropertySet("Bold",true);
					   }

					
						   aqhunhedabao->Next();
					}

				i = i+6;
				j = j+6;
				t = false;
				XA = XA + 6;
		}else
		{
				strRange2 = "F"+IntToStr(k) +":"+"I"+IntToStr(k);
				strRange4 = "F"+IntToStr(n) +":"+"I"+IntToStr(n);


				strRange6 = "F"+IntToStr(k) +":"+"I"+IntToStr(n);

				//指定区域画线
				Sheet1.OlePropertyGet("Range",strRange6.c_str()).OlePropertyGet("Borders").OlePropertySet("linestyle",1);
				receiver1 =  "收货单位:"+ aqhunhedabao->FieldByName("receiver")->AsAnsiString;
				 supplier1 = "发货单位:"  +aqhunhedabao->FieldByName("supplier")->AsAnsiString;

				Sheet1.OlePropertyGet("Range",strRange2.c_str()).OleFunction("Merge",false);
				Sheet1.OlePropertyGet("Range",strRange2.c_str()).OlePropertySet("Value",receiver1.c_str());  //	range1.OlePropertySet("Value",aqhunhedabao->FieldByName("receiver")->AsAnsiString);
				Sheet1.OlePropertyGet("Range",strRange2.c_str()).OlePropertyGet("Font").OlePropertySet("size",18);
				Sheet1.OlePropertyGet("Range",strRange2.c_str()).OlePropertyGet("Font").OlePropertySet("Bold",true);
				//居中 VerticalAlignment
				Sheet1.OlePropertyGet("Range",strRange2.c_str()).OlePropertySet("VerticalAlignment",2);

				Sheet1.OlePropertyGet("Range", strRange4.c_str() ).OleFunction("Merge",false);
				Sheet1.OlePropertyGet("Range",strRange4.c_str()).OlePropertySet("Value",supplier1.c_str());  //	range1.OlePropertySet("Value",aqhunhedabao->FieldByName("receiver")->AsAnsiString);
				Sheet1.OlePropertyGet("Range",strRange4.c_str()).OlePropertyGet("Font").OlePropertySet("size",18);
				Sheet1.OlePropertyGet("Range",strRange4.c_str()).OlePropertyGet("Font").OlePropertySet("Bold",true);
				//居中 VerticalAlignment
				Sheet1.OlePropertyGet("Range",strRange4.c_str()).OlePropertySet("VerticalAlignment",2);

				////////////////////////单元格设置//////////////////////////////
					for (int p = XB; p < XB+3; p++) { //横坐标
								if (aqhunhedabao->Eof) {
								break;
							}

							bookname = "书名: " + aqhunhedabao->FieldByName("bookname")->AsAnsiString;
							xuhao =  "序号: "+ aqhunhedabao->FieldByName("xuhao")->AsAnsiString;
							count =  "版次:"+ aqhunhedabao->FieldByName("press")->AsAnsiString;
							pressname ="版别:" + aqhunhedabao->FieldByName("pressname")->AsAnsiString;
							price = "单价:"+ aqhunhedabao->FieldByName("price")->AsAnsiString;
							AnsiString content[3];
							content[4] = xuhao;
							content[1] = bookname;

							content[2] = price + "     " + count + "      " +pressname;
							content[3]  = "数量:  本";


					 for (int y = 9; y > 5; y--) {      //纵坐标
							Sheet1.OlePropertyGet("Cells",p,y).OlePropertySet("WrapText",true);
							Sheet1.OlePropertyGet("Cells",p,y).OlePropertySet("Value",content[y-5].c_str());  //	range1.OlePropertySet("Value",aqhunhedabao->FieldByName("receiver")->AsAnsiString);
							Sheet1.OlePropertyGet("Cells",p,y).OlePropertyGet("Font").OlePropertySet("size",12);
							Sheet1.OlePropertyGet("Cells",p,y).OlePropertyGet("Font").OlePropertySet("Bold",true);
					   }


						   aqhunhedabao->Next();
					}

		  t = true;
		  k = k+6;
		  XB = XB +6; //坐标　增加　６
		  n  = n+6;
		}

	}
  //	ex.OleFunction("Quit");
   //	ex = Unassigned;
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleMng::SpeedButton2Click(TObject *Sender)
{
	/*if (dsetNote->IsEmpty() ) {
		return;
	}

	int amount;
	if (dbgrdNote->SelectedRows->Count == 0)
	{
		amount = dsetNote->FieldByName("Amount")->AsInteger ;
		if (amount > 0) {
			amount = 0-amount;
		}
		dsetNote->Edit();
		dsetNote->FieldByName("Amount")->AsInteger = amount;
		dsetNote->UpdateBatch(arCurrent);
	}
	else if (dbgrdNote->SelectedRows->Count > 0)
	{
		dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[0];
		amount = dsetNote->FieldByName("Amount")->AsInteger ;
		if (amount > 0) {
			amount = 0-amount;
		}
		dsetNote->Edit();
		dsetNote->FieldByName("Amount")->AsInteger = amount;
		dsetNote->UpdateBatch(arCurrent);
		for (int i=1; i < dbgrdNote->SelectedRows->Count; i++)
		{
			dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[i];
			amount = dsetNote->FieldByName("Amount")->AsInteger ;
			if (amount > 0) {
				amount = 0-amount;
			}
			dsetNote->Edit();
			dsetNote->FieldByName("Amount")->AsInteger = amount;
			dsetNote->UpdateBatch(arCurrent);
		}
	}

	AnsiString remarks = dsetNtHeader->FieldByName("Remarks")->AsAnsiString;
	if (remarks.Pos("(换书单)")<=0 ) {
    	dsetNtHeader->Edit();
		dsetNtHeader->FieldByName("Remarks")->AsAnsiString  = dsetNtHeader->FieldByName("Remarks")->AsAnsiString + "(换书单)";
		dsetNtHeader->UpdateBatch(arCurrent);
	}
	QryNtHeader();    */
	if (SpeedButton2->Caption == "发货(&T)") {
		SpeedButton2->Caption = "退换(&T)";
		Label11->Caption = "退货状态";
	}
	else{
		SpeedButton2->Caption = "发货(&T)";
		Label11->Caption = "发货状态";
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleMng::N20Click(TObject *Sender)
{
	if (dsetNote->IsEmpty() ) {
        return;
	}
	Tfrmbookhistory *frm = new Tfrmbookhistory(Application,m_con,m_storageID,dsetNote->FieldByName("BkcatalogID")->AsInteger );
	frm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleMng::dblkpcbbVendorID1KeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		if (dblkpcbbVendorID->Text =="") {
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
				dblkpcbbStaffID->KeyValue = staff;
				dsetNtHeader->Edit();
				dsetNtHeader->FieldByName("StaffID")->AsInteger = staff;
				dsetNtHeader->Post();
			}


		dblkpcbbVendorID->Enabled = false;
		spnew->Enabled = false; */
		checkedview(1);


                dblkpcbbStaffID->ItemIndex =  dblkpcbbStaffID->Items->IndexOf(dsetVendor->FieldByName("salesman")->AsAnsiString);

		dsetNtHeader->Edit();
                if (dblkpcbbStaffID->ItemIndex!=-1) {
                  dsrcNtHeader->DataSet->FieldByName("StaffID")->AsInteger= (int)(dblkpcbbStaffID->Items->Objects[dblkpcbbStaffID->ItemIndex]);
                }
		dsrcNtHeader->DataSet->FieldByName("VendorID")->Value =  ClientID;
		dsetNtHeader->UpdateRecord();

		UpdateNtHeader();
		BtnSave->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleMng::dblkpcbbVendorID1Click(TObject *Sender)
{
	try {
		ClientID = dsetVendor->FieldByName("ID")->AsInteger ;
		checkedview(0);
                dblkpcbbStaffID->ItemIndex =  dblkpcbbStaffID->Items->IndexOf(dsetVendor->FieldByName("salesman")->AsAnsiString);


	} catch (...) {
	}
}
//---------------------------------------------------------------------------
void TfrmWholesaleMng::PrintAdd()
{
	AnsiString sql;
	sql = "select * from sys_printhead where modle = 1 and stgid = " + IntToStr(m_storageID) ;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	pmprint->Items->Clear();
	pmpreview->Items->Clear();
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



void __fastcall TfrmWholesaleMng::dblkpcbbVendorIDClick(TObject *Sender, bool &Handled)

{
	try {
		ClientID = dsetVendor->FieldByName("ID")->AsInteger ;
	} catch (...) {
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleMng::dblkpcbbVendorIDKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		if (dblkpcbbVendorID->Text =="") {

                         ShowMsg(Handle ,"请选择单位！",3);
			return;
		}
			AnsiString sql = "select Salesman from CUST_CustomerInfo where id = " + IntToStr(ClientID);
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
				    dblkpcbbStaffID->ItemIndex = dblkpcbbStaffID->Items->IndexOfObject((TObject*)staff);
				dsetNtHeader->Edit();
				dsetNtHeader->FieldByName("StaffID")->AsInteger = staff;
				dsetNtHeader->Post();
			}
			dsetNtHeader->Edit();
			dsrcNtHeader->DataSet->FieldByName("VendorID")->Value =  ClientID;
			dsetNtHeader->UpdateRecord();
			UpdateNtHeader();

			//dbnbedtAddCosts->SetFocus();
		   //	RzButton1->Enabled = false;
		   //cbclient->Enabled = false;
		   dblkpcbbVendorID->Enabled = false;
		   spnew->Enabled = false;
		   BtnSave->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleMng::CheckBox1Click(TObject *Sender)
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

void __fastcall TfrmWholesaleMng::dsetNoteBeforeScroll(TDataSet *DataSet)
{
	scroll = 1;
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleMng::dsrcNoteDataChange(TObject *Sender, TField *Field)

{
	if (scroll == 1) {
		if (dsetNote->IsEmpty() ) {
			editprice->Text = "0.00";
			dbnbedtAmount->Text = "0";
			dbnbedtDiscount->Text = "100.00";
			dbnbedtTotalAmount->Text = "";
			scroll = 0;
			return;
		}
        historyview();
		// 发价
		editprice->Text = FormatFloat("0.00",dsetNote->FieldByName("price")->AsFloat * dbnbedtDiscount->Value*0.01);
    	scroll = 0;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleMng::dbgrdNoteDrawColumnCell(TObject *Sender, const TRect &Rect,
		  int DataCol, TColumn *Column, Grids::TGridDrawState State)
{
   /*	if (Column->FieldName == "stkamount" ) {
		//显示库存
		AnsiString sql;
		sql = "select dbo.UF_BS_GetAmountByCatalogid(" +dbgrdNote->DataSource->DataSet->FieldByName("BkcatalogID")->AsString + "," + IntToStr(m_storageID) + ") as stkamount";
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->Open();
		 if (Column-) {
			dbgrdNote->Canvas->TextRect(Rect,Rect.Left,Rect.Top,"000") ;
		 }else
		 {
			dbgrdNote->Canvas->TextRect(Rect,Rect.Left,Rect.Top,Column->Field->Value) ;

		 }
	}
	else
	{
		dbgrdNote->DefaultDrawColumnCell(Rect,DataCol,Column,State);
	}  */
	dbgrdNote->DefaultDrawColumnCell(Rect,DataCol,Column,State);
   //	dbgrdNote->
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleMng::cbtypeSelect(TObject *Sender)
{
	if (cbtype->ItemIndex == 1) {
		dbnbedtDiscount->Enabled = false;
	}
	else
	{
		dbnbedtDiscount->Enabled = true;
	}
}
void TfrmWholesaleMng::SearchDanHao(AnsiString awhere)
{


       AnsiString sql = "select * from BS_WsaleNoteHeader " + awhere ;
        querydan->Close();
        querydan->SQL->Clear();
        querydan->SQL->Add(sql);
        querydan->Open();
       // TLocateOptions Opts;
       // Opts.Clear();
       // Opts << loPartialKey;
       // querydan->Locate("WsaleNtCode", code, Opts);




}

//---------------------------------------------------------------------------





void __fastcall TfrmWholesaleMng::dblkpcbbStaffIDChange(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleMng::RzToolButton3Click(TObject *Sender)
{
//
//导入
  	if (BtnSave->Enabled) {
	       //	MessageBox(0,"请先保存入库单！","一般入库" ,MB_ICONEXCLAMATION);
                ShowMsg(Handle ,"请先保存发货单！",3);
		return;
	}
	TfrmImport *frm = new TfrmImport(Application,m_con,dsetNtHeader->FieldByName("ID")->AsInteger,m_userID,m_storageID );
	frm->mode = 2;
        frm->stackname = "";
	if (frm->ShowModal() == mrOk  ) {
    	QryNtHeader();
	}
	delete frm;
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleMng::N23Click(TObject *Sender)
{
//晓票
	Tfrmorderquery1* frm = new Tfrmorderquery1(Application,m_con,m_storageID,2,0,linfo.UserName,qfclient);
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

void __fastcall TfrmWholesaleMng::N24Click(TObject *Sender)
{
  try
   {
    if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1 && dsrcNote->DataSet != NULL)
	{
           muilprint(dsetNtHeader->FieldByName("ID")->AsString,1,true);
        }
   }catch(...){ShowMsg(Handle ,"打印失败，请重试！",3);};

}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleMng::A41Click(TObject *Sender)
{
//A4

     try
    {
   	Print(0,0,0);
    }catch(...)
    {ShowMsg(Handle ,"打印失败，请重试！",3);}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleMng::N21A41Click(TObject *Sender)
{
//21 A4
      try
   {
    if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1 && dsrcNote->DataSet != NULL)
	{
           muilprint(dsetNtHeader->FieldByName("ID")->AsString,0,false);
        }
   }catch(...){ShowMsg(Handle ,"打印失败，请重试！",3);};
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleMng::A42Click(TObject *Sender)
{


   try
    {
 Print(1,0,0);
    }catch(...)
   {ShowMsg(Handle ,"打印失败，请重试！",3);}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleMng::N21A42Click(TObject *Sender)
{
//A5打印 预览
  try
   {
    if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1 && dsrcNote->DataSet != NULL)
	{
           muilprint(dsetNtHeader->FieldByName("ID")->AsString,1,false);
        }
   }catch(...){ShowMsg(Handle ,"打印失败，请重试！",3);};
}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleMng::muilprintbuttonClick(TObject *Sender)
{
//批量打应   2/1A4
	Tfrmorderquery1* frm = new Tfrmorderquery1(Application,m_con,m_storageID,2,0,linfo.UserName,qfclient);
                        frm->enablefahuofangshi();
			if (frm->ShowModal() == mrOk)
			{
                                if (frm->printnow) {    //用户选择打印

                                try
                                   {

                                     muilprint(frm->headerid,3,false);
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

void __fastcall TfrmWholesaleMng::A43Click(TObject *Sender)
{
//A4批量打应
 	Tfrmorderquery1* frm = new Tfrmorderquery1(Application,m_con,m_storageID,2,0,linfo.UserName,qfclient);
                        frm->enablefahuofangshi();
                        frm->version = linfo.version;
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
void TfrmWholesaleMng::A4muilprint(AnsiString HeaderID,int type)
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

                frm->yingshou = dbnbedt5->Value ;
		frm->fandian = dbnbedt6->Value ;
		frm->pxbk = pxbk;
		frm->printtitle = printtitle;
		frm->contact = contact;
		frm->tel = tel;
		frm->address = address;
		frm->ClientName = dblkpcbbVendorID->Text ;
                frm->DanhaoChange = ChangeDisplay ;
                frm->lianxueprint= true;//批打

                frm->pixiaoortuihuo = true;
               frm->A4print(HeaderID);
              /* for (int i=0; i < IDStr->Count; i++) {

                    if ((IDStr->Strings[i]!="-1")&&(IDStr->Strings[i]!="")) {
                        frm->pixiaoortuihuo = true;
                        frm->InputPara(StrToInt(IDStr->Strings[i]));

                        if (type == 0) {
                            frm->printmodle = -1;
                        }
                        else
                        {
                            frm->printmodle = 0;
                        }
                        frm->tuihuo = 0;
                        frm->previewprint(0,1);
                    }
               }  */

		frm->Close();
		delete frm;

                AnsiString sql = "update BS_WsaleNoteHeader set printcount = printcount + 1 where id in (" + HeaderID+"-1)" ;
                query->Close();
                query->SQL->Clear();
                query->SQL->Add(sql);
                query->ExecSQL();

}
//---------------------------------------------------------------------------

void __fastcall TfrmWholesaleMng::N25Click(TObject *Sender)
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





//---------------------------------------------------------------------------

