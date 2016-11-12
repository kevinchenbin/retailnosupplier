//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "GetBsset.h"
#include "StorageReturnMngForm.h"
#include <systdate.h>
#include "NoteCode.h"
#include "QryNoteCodeForm.h"
#include "SetNotesForm.h"
#include "mytrace.h"
#include "Print.h"
#include "pdtypes.h"
//#include "..\catalogadmin\catalogadmin.h"
//#include "..\customer\customer.h"
#include "..\supplier\detailemessage.h"
#include "Dialogs.hpp"
#include "NewBookinput.h"
#include "NewBookModify.h"
#include "bookQuery.h"
#include "RecMoneyForm.h"
#include "QueryDanHao.h"
#include "Addsyslog.h"
#include   <math.h>
#include "Unitcaigouquery.h"
#include "SelectCatalogForm.h"
#include "bookhistory.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "MDIChild"
#pragma link "RzCommon"
#pragma link "RzDBLook"
#pragma link "RzRadChk"
#pragma link "RzDBDTP"
#pragma link "RzDTP"
#pragma link "frxClass"
#pragma link "frxDBSet"
#pragma resource "*.dfm"
TfrmStorageReturnMng *frmStorageReturnMng;
//---------------------------------------------------------------------------
__fastcall TfrmStorageReturnMng::TfrmStorageReturnMng(TComponent* Owner)
	: TfrmMDIChild(Owner)
	, m_catalogSearchMode(0)
	, m_bsmode(BSUnknown)
	, m_opmode(OPUnknown)
{
	m_module = MTStorageMng;
	m_catalogSearchMode = 1;
	this->WindowState = wsMaximized ;
	stackchange = false;
	scroll = 0;

}
//---------------------------------------------------------------------------

void TfrmStorageReturnMng::Init(LandInfo* li)
{
	TfrmMDIChild::Init(li);
	linfo.app = li->app ;
	linfo.con = li->con ;
	linfo.userID = li->userID ;
	linfo.UserName = li->UserName ;
	linfo.storageID = li->storageID ;
	linfo.FormatStr = li->FormatStr ;
	lblOpName->Caption = li->UserName ;
	cmdAddNtHeader->Connection = linfo.con;
	spQryNtHeader->Connection = linfo.con;
	spQryNtHeader1->Connection = linfo.con;
	cmdUpdateNtHeader->Connection = linfo.con;
	cmdAddNote->Connection = linfo.con;
	cmdUpdateNote->Connection = linfo.con;
	cmdDelNote->Connection = linfo.con;
	cmdDelNtHeader->Connection = linfo.con;
	cmdBatchDelNote->Connection = linfo.con;
	cmdBatchUpdateNote->Connection = linfo.con;
	cmdResetNtHeader->Connection = linfo.con;
	dsetSupplier->Connection = linfo.con;
	dsetStaff->Connection = linfo.con;
	adospupdatewsaleprice->Connection = linfo.con;
	adospcopy->Connection = linfo.con;
	spsave->Connection = linfo.con;
	querydan->Connection = linfo.con;
	sptuihuo->Connection = linfo.con;
	GetBkStackInfo();
	query->Connection = linfo.con;
	qudetail->Connection = linfo.con;
	qrystorge->Connection = linfo.con;
           QFClientTiaoJian=" 1=1 ";
        QFSupplierTiaoJian=" 1=1 ";
         qfsupplier= li->qfsupply;
         if (li->qfsupply) {
            QFSupplierTiaoJian=" stgid ="+IntToStr(linfo.storageID);
       }

           dsetSupplier->CommandText="select ID, Name from CUST_CustomerInfo where customerstate =1 and Type=1 and "+QFSupplierTiaoJian+" order by name";
	dsetSupplier->Active = true;
	dsetStaff->Active = true;
	dblkpcbbSupplierID->KeyValue = 0;
	adoGetHeadTotal->Connection= linfo.con;
	dssetStkAmount->Connection= linfo.con;
	AnsiString sql;
	sql = "SELECT NAME,value,bk FROM SYS_BSSET WHERE NAME IN('rkusetuihuo','storageday','xiaoshudian','rktuihuoguanli', ";
	sql = sql+ " 'changeDanHaoDisplay','rkallsupplier','rkusefind','rkusedelete','rkusechange','storagesametishi','storageday','cbsamerkts','cbsamerkyx')";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();


	 SYSSet * GetSet = new SYSSet();


	 while(!query->Eof)
	 {

		  SYSSet * Note = new SYSSet();
		  Note->Name = query->FieldByName("NAME")->AsAnsiString;

		 if ((query->FieldByName("NAME")->AsAnsiString=="xiaoshudian")
		 || (query->FieldByName("NAME")->AsAnsiString=="storageday")
		 || (query->FieldByName("NAME")->AsAnsiString=="changeDanHaoDisplay")
		 ||(query->FieldByName("NAME")->AsAnsiString=="storageday"   )) {
			 Note->ValueStr =query->FieldByName("bk")->AsAnsiString;
			 GetSet->Add(query->FieldByName("NAME")->AsAnsiString,(TObject*)Note);
		 }else
		 {
			 Note->ValueBool=  query->FieldByName("value")->AsBoolean;
			 GetSet->Add(query->FieldByName("NAME")->AsAnsiString,(TObject*)Note);
		 }
		 query->Next();
	 }
	///storageday
	  GetSet->GetSetInfo("storageday");
	  storageday = StrToInt(GetSet->ValueStr);

	//退货密码是否启用



		GetSet->GetSetInfo("rkusetuihuo");
		tuihuopassword = GetSet->ValueBool;
	if (tuihuopassword) {
		if (!CheckOperateAuthority()) {
			Close();
			return;
		}
	}
	//ChangeBsmode(BSNoteSendback);

	sql = "select ID,Name from SYS_StorageInfo where id = " + IntToStr(li->storageID) ;
	qrystorge->Close();
	qrystorge->SQL->Clear();
	qrystorge->SQL->Add(sql);
	qrystorge->Open();
	labtitle->Caption = qrystorge->FieldByName("Name")->AsAnsiString.Trim();

	//ChangeOpmode(OPAddNtHeader);



	/*if ( true) {
		dgdetail->Visible = true;
	}
	else
	{
		dgdetail->Visible = false;
	}  */
	GetSet->GetSetInfo("xiaoshudian");
	format = "###,###,##"+GetSet->ValueStr;
	RzDBNumericEdit3->DisplayFormat = format;
	RzDBNumericEdit4->DisplayFormat = format;

	//打印信息
	sql = "select rkprinttitle,rkcontact,rktel,rkaddress,rkprintbk from sys_printtitle where stgid = " + IntToStr(m_storageID);
    query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();

	rkbk = query->FieldByName("rkprintbk")->AsAnsiString ;
	printtitle = query->FieldByName("rkprinttitle")->AsAnsiString ;
	contact = query->FieldByName("rkcontact")->AsAnsiString ;
	tel = query->FieldByName("rktel")->AsAnsiString ;
	address = query->FieldByName("rkaddress")->AsAnsiString ;



	//退货监管
		GetSet->GetSetInfo("rktuihuoguanli");
		rktuihuoguanli = GetSet->ValueBool;

	//change danhao
		GetSet->GetSetInfo("changeDanHaoDisplay");
		ChangeDisplay = GetSet->ValueBool;

	if (ChangeDisplay) {
		editdanhao->Visible = true;
		dbedtStgNtCode->Visible = false;
		DBNav->Visible = true;
		dgdetail->Columns->Items[1]->Visible = true;
		dgdetail->Columns->Items[0]->Visible = false;
	}else
	{
		editdanhao->Visible = false;
		dbedtStgNtCode->Visible = true;
		dgdetail->Columns->Items[1]->Visible = false;
		dgdetail->Columns->Items[0]->Visible = true;
	}
	//所有供应商历史明细
	GetSet->GetSetInfo("rkallsupplier");
	  allsupplier = GetSet->ValueBool;


	//查单密码是否启用
	  GetSet->GetSetInfo("rkusefind");
	   findpassword = GetSet->ValueBool;


	//删单密码是否启用
		 GetSet->GetSetInfo("rkusedelete");
		  deletepassword = GetSet->ValueBool;



	//修改单头密码是否启用
		  GetSet->GetSetInfo("rkusechange");
		 changepassword  = GetSet->ValueBool;


	//重复退货提示
		  GetSet->GetSetInfo("cbsamerkts");
		  sameid   = GetSet->ValueBool;
                  //退货重复录入
               GetSet->GetSetInfo("cbsamerkyx");
		  sametuiinput   = GetSet->ValueBool;



         delete GetSet;
	RzToolButton5Click(BtnNew);
	ChangeOpmode(OPAddNtHeader);
	FormView();
}
//---------------------------------------------------------------------------
void TfrmStorageReturnMng::GetBkStackInfo()
{
	AnsiString sql= "select   name , ID from STK_BookstackInfo where StgID = " + IntToStr(m_storageID);
	TADOQuery *aq  = new TADOQuery(Application);
	try
	{
		aq->Connection = m_con ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		while(!aq->Eof)
		{
			cbbkstackID->AddItem(aq->FieldByName("name")->AsAnsiString ,(TObject*)aq->FieldByName("ID")->AsInteger);
			aq->Next();
		}
		cbbkstackID->ItemIndex = 0;
	}
	__finally
	{
		delete aq;
	}
}
//---------------------------------------------------------------------------
void TfrmStorageReturnMng::ChangeCatalogSearchMode()
{
		 //
}

void TfrmStorageReturnMng::ChangeBsmode(BSMode bsmode)
{
//
}

void TfrmStorageReturnMng::ChangeOpmode(OPMode opmode)
{
	//if (opmode == m_opmode
	//	&& (opmode == OPDelNtHeader))
	//	return;

	//1为查单模式 2为添加单头模式 3为删除单头模式 4为添加单模式 5为删除单模式 6为统一模式 7为现场收款模式
	switch (opmode)
	{
	case OPFind:
		{
			if (!SaveStorage(1))
			{
				return;
			}

			if (findpassword) {
            	if (!CheckOperateAuthority())
					return;
			}
			DBNav->Enabled = true;

			Tfrmcaigouquery* frm = new Tfrmcaigouquery(Application,m_con,m_storageID,2,1,qfsupplier);
			if (frm->ShowModal() == mrOk)
			{
				AnsiString sql;
				sql = " select * from CUST_CustomerInfo where Type =1  and customerstate =1 and "+QFSupplierTiaoJian+" order by name ";
				dsetSupplier->Active = false;
				dsetSupplier->CommandText = sql;
				dsetSupplier->Active = true;
				dsetSupplier->First();
				dblkpcbbSupplierID->KeyValue = dsetSupplier->FieldByName("ID")->AsInteger ;

				DelInvalidNtHeader();
				edtCatalog->Text = "";
				edtQrySupplier->Text = "";
				AnsiString code = frm->GetNoteCode();
				AnsiString sqlwhere = frm->GetWhere();
				try
				{
					QryNtHeader(code);
					String sql,codetmp;
					if (sqlwhere != "") {
						sql = "select * from BS_StorageNoteHeader " + sqlwhere;
						querydan->Close();
						querydan->SQL->Clear();
						querydan->SQL->Add(sql);
						querydan->Open();
						TLocateOptions Opts;
						Opts.Clear();
						Opts << loPartialKey;
						querydan->Locate("StgNtCode", code, Opts);
					}
				}
				__finally
				{
				}
				m_opmode = opmode;
				delete frm;
				SaveOrNot = true;
				BtnSave->Enabled = false;
				dblkpcbbSupplierID->Enabled = false;
				sbnewcustomer->Enabled = false;
				//dbedtSupplySN->Enabled = false;
				dbnbedtAddCosts->Enabled = false;
			}

		}
		break;
	case OPAddNtHeader:
		{
			//如果上次是添加模式，并且没有加进任何数据，则不能添加
			if (m_opmode == OPAddNtHeader &&
				dsetNote->Active && dsetNote->RecordCount < 1)
				return;

			if (m_opmode == OPDelNote      //上次是删除模式，并且所有数据都删除
				&& dsetNote->Active && dsetNote->RecordCount < 1)
				return;

			edtCatalog->Text = "";
			edtQrySupplier->Text = "";
			AddNtHeader();
			m_opmode = opmode;
		}
		break;
	case OPDelNtHeader:
		/*{
			if (deletepassword) {
            	if (!CheckOperateAuthority())
					return;
			}
			else
			{
				if (MessageBoxA(0,"是否要删除该单?","询问",MB_ICONQUESTION|MB_OKCANCEL)!=1 )
					return;
			}

			edtCatalog->Text = "";
			edtQrySupplier->Text = "";
			DelNtHeader();
			m_opmode = opmode;
        }
		break;   */
	case OPAddNote:
    	edtCatalog->Text = "";
		edtCatalog->SetFocus();
		m_opmode = opmode;
		break;
	case OPDelNote:
		{
			if (dsetNote->IsEmpty() ) {
            	return;
			}
                        ;
			if (ShowMsg(Handle ,"确定要删除该记录吗?",1)==1 )
			{
				DelNote();

				//ResetNtHeader();
				m_opmode = opmode;
				break;
			}else
			{

			 return;
			}
        }

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
		//现场付款模式
		if (editdanhao->Text == "") {
			return;
		}
		if (!SaveStorage(1))
		{
			return;
		}
        if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
		{
			//首先把修改的更新一下哈
			dbgrdNote->SetFocus();
			//其次把最新数据刷新一下哈
			QryNtHeader();

			AnsiString sql;
			sql = " select datediff(day,getdate(),HdTime) as day from BS_StorageNoteHeader where id = " +  dsetNtHeader->FieldByName("ID")->AsAnsiString;
			query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->Open();
			if (query->FieldByName("day")->AsInteger != 0 ) {

                                 ShowMsg(Handle ,"现场付款只能付当日的！",3);
				return;
			}

			/*if (StrToDate(dsetNtHeader->FieldByName("HdTime")->AsAnsiString ) != Date()  ) {
				MessageBox(0,"现场付款只能付当日的！","入库退货单" ,MB_OK);
				return;
			} */
			TfrmRecMoney* frm = new TfrmRecMoney(this);
			frm->SetDiscountedPrice(dsetNtHeader->FieldByName("TotalDiscountedPrice")->AsFloat);
			frm->SetChecked(dsetNtHeader->FieldByName("Checked")->AsFloat);
			if (mrOk == frm->ShowModal())
			{
				if (frm->numedtUnchecked ->Value > 0) {

					if (ShowMsg(Handle ,"你还有未付金额，是否继续？",1)!=1) {
						frm->ShowModal();
						return;
					}
				}
				if (dsetNtHeader->FieldByName("Checked")->AsFloat + frm->GetReceived() >= dsetNtHeader->FieldByName("TotalDiscountedPrice")->AsFloat ) {
					sql = "update BS_StorageNoteHeader set Checked = Checked + " + FloatToStr(frm->GetReceived()) + ",State = 1 where id = " + dsetNtHeader->FieldByName("ID")->AsString ;
				}
				else
				{
					sql = "update BS_StorageNoteHeader set Checked = Checked + " + FloatToStr(frm->GetReceived()) + " where id = " + dsetNtHeader->FieldByName("ID")->AsString ;
                }
				query->Close();
				query->SQL->Clear();
				query->SQL->Add(sql);
				query->ExecSQL();
				AnsiString Code = NoteCode::BuildCode(query, GetDBTime(query), 0, "FN_CUSEndMoneyDocuments", "MoneyCode");
				sql = "insert into FN_CUSEndMoneyDocuments (MoneyCode,date,state,type,userid,CustmerName,ClearingType,Clearingstyle,stgid) values ("+Code+",getdate(),1,1," + IntToStr(m_userID) +",'" + dblkpcbbSupplierID->Text + "','现场付款','现金'," + IntToStr(m_storageID) + ")";
				query->Close();
				query->SQL->Clear();
				query->SQL->Add(sql);
				query->ExecSQL();
				sql = "insert into FN_CUSEndMoneyDtails(EndMoneyDocumentID,stgntcode,thistime,type,CodeStr) values(" + Code + "," + dsetNtHeader->FieldByName("StgNtCode")->AsAnsiString + "," + FloatToStr(frm->GetReceived()) + ",1,'" + dsetNtHeader->FieldByName("StgNtCodeStr")->AsAnsiString + "')";
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

void TfrmStorageReturnMng::AddNtHeader()//添加单头
{
	spQryNtHeader->Active = false;
	spQryNtHeader1->Active = false;
	cmdAddNtHeader->Parameters->ParamByName("@StgID")->Value = m_storageID;
	cmdAddNtHeader->Parameters->ParamByName("@Bsmode")->Value = 1;
	cmdAddNtHeader->Parameters->ParamByName("@OperatorID")->Value = m_userID;
	cmdAddNtHeader->Parameters->ParamByName("@CODEMODE")->Value = 1;
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

void TfrmStorageReturnMng::QryNtHeader(String code, bool qrybkstack)//查询单头
{
	spQryNtHeader->Active = false;
	spQryNtHeader1->Active = false;
	scroll = 1;
	spQryNtHeader1->Parameters->ParamByName("@NtCode")->Value = code;
	spQryNtHeader1->Parameters->ParamByName("@Bsmode")->Value = 1;
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
		//dsetNote->Last();
		//dsetNote->AfterScroll = dsetNoteAfterScroll;

		GetHtHeaderTotal();//统计总数量
		SupplierCreit();

		editdanhao->Text = dsetNtHeader->FieldByName("StgNtCodeStr")->AsAnsiString ;
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "###,###,##0.00";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = format;
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = format;
		operterview(dsetNtHeader->FieldByName("OperatorID")->AsInteger );
		membk->Text =  dsetNtHeader->FieldByName("Remarks")->AsString;
		if (dsetNtHeader->FieldByName("cwstate")->AsInteger == 1 ) {
			grpbxNote->Enabled = false;
			BtnChangeOptions->Enabled = false;
			RzToolButton2->Enabled = false;
			RzToolButton3->Enabled = false;
			Image1->Visible = true;
		}
		else
		{
			grpbxNote->Enabled = true;
			BtnChangeOptions->Enabled = true;
			RzToolButton2->Enabled = true;
			RzToolButton3->Enabled = true;
			Image1->Visible = false;
		}
	}
	catch(...)
	{
		//ShowMessage("该单不存在！");
	}
}

void TfrmStorageReturnMng::QryNtHeader(bool qrybkstack)//查询单头
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
		scroll = 1;
		spQryNtHeader->Parameters->ParamByName("@ID")->Value = dsetNtHeader->FieldByName("ID")->AsInteger;
		spQryNtHeader->Parameters->ParamByName("@Bsmode")->Value = 1;
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

			GetHtHeaderTotal();//统计总数量
			//dsetNote->AfterScroll = dsetNoteAfterScroll;
			/*if (qrybkstack)
			{
				QryBkstack();
			}  */
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00";
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "###,###,##0.00";
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = format;
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = format;
			operterview(dsetNtHeader->FieldByName("OperatorID")->AsInteger );
			membk->Text =  dsetNtHeader->FieldByName("Remarks")->AsString;
			editdanhao->Text = dsetNtHeader->FieldByName("StgNtCodeStr")->AsAnsiString ;
			if (dsetNtHeader->FieldByName("cwstate")->AsInteger == 1 ) {
				grpbxNote->Enabled = false;
				BtnChangeOptions->Enabled = false;
				RzToolButton2->Enabled = false;
				RzToolButton3->Enabled = false;
				Image1->Visible = true;
			}
			else
			{
				grpbxNote->Enabled = true;
				BtnChangeOptions->Enabled = true;
				RzToolButton2->Enabled = true;
				RzToolButton3->Enabled = true;
				Image1->Visible = false;
			}
		}
		catch(...)
		{
            //ShowMessage("该单不存在！");
		}
	}
}

void TfrmStorageReturnMng::QryNtHeader(int id, bool qrybkstack)//查询单头
{
	//查询单头
	spQryNtHeader1->Active = false;
	spQryNtHeader->Active = false;
	scroll = 1;
	spQryNtHeader->Parameters->ParamByName("@ID")->Value = id;
	spQryNtHeader->Parameters->ParamByName("@Bsmode")->Value = 1;
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
		//dsetNote->AfterScroll = dsetNoteAfterScroll;
		/*if (qrybkstack)
		{
			QryBkstack();
		}   */
		GetHtHeaderTotal();//统计总数量
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "###,###,##0.00";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = format;
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = format;
		operterview(dsetNtHeader->FieldByName("OperatorID")->AsInteger );
		membk->Text =  dsetNtHeader->FieldByName("Remarks")->AsString;
		editdanhao->Text = dsetNtHeader->FieldByName("StgNtCodeStr")->AsAnsiString ;
		if (dsetNtHeader->FieldByName("cwstate")->AsInteger == 1 ) {
			grpbxNote->Enabled = false;
			BtnChangeOptions->Enabled = false;
			RzToolButton2->Enabled = false;
			RzToolButton3->Enabled = false;
			Image1->Visible = true;
		}
		else
		{
			grpbxNote->Enabled = true;
			BtnChangeOptions->Enabled = true;
			RzToolButton2->Enabled = true;
			RzToolButton3->Enabled = true;
			Image1->Visible = false;
		}
	}
	catch(...)
	{
    	//ShowMessage("该单不存在！");
    }
}

void TfrmStorageReturnMng::DelNtHeader()//删除单头
{
//iu
}

void TfrmStorageReturnMng::UpdateNtHeader()//更新单头
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
			membk->Text;
		cmdUpdateNtHeader->Parameters->ParamByName("@SupplySN")->Value =
			dsetNtHeader->FieldByName("SupplySN")->AsWideString;
		cmdUpdateNtHeader->Parameters->ParamByName("@CustomerID")->Value =
			dsetSupplier->FieldByName("ID")->AsInteger;
			//dsetNtHeader->FieldByName("SupplierID")->AsInteger;
		cmdUpdateNtHeader->Parameters->ParamByName("@Bsmode")->Value = 1;
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

bool TfrmStorageReturnMng::AddNote(int supplierID, int catalogID)//添加单
{
	bool result = false;
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1 )
	{
		if (rktuihuoguanli) {
        	AnsiString sql;
			sql = "select * from stk_bookinfo where amount > 0 and stgid = " + IntToStr(m_storageID) + " and SupplierID = " + dsetNtHeader->FieldByName("SupplierID")->AsString + " and BkcatalogID = " + IntToStr(catalogID);
			query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->Open();
			if (query->IsEmpty() ) {
				sql = "select CUST_CustomerInfo.Name from CUST_CustomerInfo left join stk_bookinfo on CUST_CustomerInfo.id = stk_bookinfo.SupplierID "
					" where stk_bookinfo.amount > 0 and stk_bookinfo.stgid = " + IntToStr(m_storageID) + " and stk_bookinfo.BkcatalogID = " + IntToStr(catalogID) ;
                query->Close();
				query->SQL->Clear();
				query->SQL->Add(sql);
				query->Open();
				AnsiString msg;
				if (query->IsEmpty() ) {
					msg = "库存无该书,请核实后退货！";
				}
				else
				{
                	while (!query->Eof )
					{
						if (msg == "") {
							msg =  query->FieldByName("Name")->AsAnsiString.Trim();
						}
						else
						{
							msg = msg + ";"+ query->FieldByName("Name")->AsAnsiString.Trim();
						}
						query->Next();
					}
					msg = "此书没有在该供应商处进货," + msg + "有供货记录，请核实！";
				}     // 此书没有在该供应商处进货，XXXX有供货记录，请核实
				ShowMsg(Handle ,msg.c_str() ,3);
				edtCatalog->SetFocus();
				return true;
			}
		}
		cmdAddNote->Parameters->ParamByName("@NtHeaderID")->Value
			= dsetNtHeader->FieldByName("ID")->AsInteger;
		cmdAddNote->Parameters->ParamByName("@BkcatalogID")->Value
		   =catalogID;//	= dsetCatalog->FieldByName("ID")->AsInteger;
		cmdAddNote->Parameters->ParamByName("@STKinfoID")->Value
		   =-1;
		cmdAddNote->Parameters->ParamByName("@SupplierID")->Value
		   = dsetNtHeader->FieldByName("SupplierID")->AsInteger;
		cmdAddNote->Parameters->ParamByName("@Bsmode")->Value = 1;
		cmdAddNote->Parameters->ParamByName("@bkstackID")->Value = (int)(cbbkstackID->Items->Objects[cbbkstackID->ItemIndex]);
		MYTRACEF(_T("add note @NtHeaderID=%d,@BkcatalogID=%d,@STKinfoID=%d,@SupplierID=%d,@Bsmode=%d,@bkstackID=%d")
			, dsetNtHeader->FieldByName("ID")->AsInteger
			, catalogID//dsetCatalog->FieldByName("ID")->AsInteger
			,-1
			, supplierID//dsetNtHeader->FieldByName("SupplierID")->AsInteger
			, 1);
		cmdAddNote->Execute();
		int ret = cmdAddNote->Parameters->ParamByName("@RETURN_VALUE")->Value;

		if (ret > 0)//插入成功
		{
			//int bkinfoid = dsetNote->FieldByName("BkInfoID")->AsInteger;
			try
			{
				//LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
				QryNtHeader(dsetNtHeader->FieldByName("ID")->AsInteger, true);
				//((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00%";
				//((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "￥###,###,##0.00";
				//((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = "￥###,###,##0.00";
				//((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = "￥###,###,##0.00";
			}
			__finally
			{
				//LockWindowUpdate(NULL);
			}
			//提示插入相同书目;
			//ShowMessage(dsetNote->Lookup("BkInfoID", bkinfoid, "BkInfoID").VInteger);
			result = true;
		}
		else if (ret == 0)//查无此书
		{

		}
		else if (ret == -1)//库存出错了
		{

		}
		else 	if (ret == -2) {
			if (sameid) {
				ShowMsg(Handle ,"不能添加相同目录的书！",3);
			}
            result = true;
		}
	}
	return result;
}

bool TfrmStorageReturnMng::AddNote(int id)
{
	bool result = false;
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
        if (rktuihuoguanli) {
        	AnsiString sql;
			sql = "select * from BS_StorageNote where amount >= 0 and BkInfoID in (select id from stk_bookinfo where stgid = " + IntToStr(m_storageID) + " and SupplierID = " + dsetNtHeader->FieldByName("SupplierID")->AsString + " and BkcatalogID = " + IntToStr(id) + ")";
			query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->Open();
			if (query->IsEmpty() ) {

            	sql = "select CUST_CustomerInfo.Name from CUST_CustomerInfo left join BS_StorageNoteHeader on CUST_CustomerInfo.id = BS_StorageNoteHeader.SupplierID "
					" left join BS_StorageNote on BS_StorageNote.StgNtHeaderID = BS_StorageNoteHeader.id "
					" left join stk_bookinfo on BS_StorageNote.BkInfoID = stk_bookinfo.id "
					" where BS_StorageNote.amount > 0 and stk_bookinfo.stgid = " + IntToStr(m_storageID) + " and BkcatalogID = " + IntToStr(id) ;
                query->Close();
				query->SQL->Clear();
				query->SQL->Add(sql);
				query->Open();
				AnsiString msg;
				if (query->IsEmpty() ) {
					msg = "该书无进货记录,请查证后退货！";
				}
				else
				{
                	while (!query->Eof )
					{
						if (msg == "") {
							msg =  query->FieldByName("Name")->AsAnsiString ;
						}
						else
						{
							msg = msg + ";"+ query->FieldByName("Name")->AsAnsiString ;
						}
						query->Next();
					}
					msg = "该书在供应商：" + msg + "处进货,请查证后退货！";
				}


                                 ShowMsg(Handle ,msg.c_str(),3);
				return true;
			}
		}
		cmdAddNote->Parameters->ParamByName("@NtHeaderID")->Value
			= dsetNtHeader->FieldByName("ID")->AsInteger;
		cmdAddNote->Parameters->ParamByName("@BkcatalogID")->Value
			= id;
		cmdAddNote->Parameters->ParamByName("@STKinfoID")->Value
			= -1;
		cmdAddNote->Parameters->ParamByName("@SupplierID")->Value
			= dsetNtHeader->FieldByName("SupplierID")->AsInteger;
		cmdAddNote->Parameters->ParamByName("@Bsmode")->Value = 1;
				cmdAddNote->Parameters->ParamByName("@bkstackID")->Value = (int)(cbbkstackID->Items->Objects[cbbkstackID->ItemIndex]);
		MYTRACEF(_T("add note @NtHeaderID=%d,@BkcatalogID=%d,@SupplierID=%d,@Bsmode=%d,@bkstackID=%d")
			, dsetNtHeader->FieldByName("ID")->AsInteger
			, id
			,-1
			, dsetNtHeader->FieldByName("SupplierID")->AsInteger
			, 1);
		cmdAddNote->Execute();
		int ret = cmdAddNote->Parameters->ParamByName("@RETURN_VALUE")->Value;
		if (ret > 0)//插入成功
		{
			//int bkinfoid = dsetNote->FieldByName("BkInfoID")->AsInteger;
			try
			{
				//LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
				//QryNtHeader(dsetNtHeader->FieldByName("ID")->AsInteger, true);
				//((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00%";
				//((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "￥###,###,##0.00";
				//((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = "￥###,###,##0.00";
				//((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = "￥###,###,##0.00";
			}
			__finally
			{
				//LockWindowUpdate(NULL);
			}
			//提示插入相同书目;
			//ShowMessage(dsetNote->Lookup("BkInfoID", bkinfoid, "BkInfoID").VInteger);
			result = true;
		}
		else if (ret == 0)//查无此书
		{

		}
		else if (ret == -1)//库存出错了
		{

		}
		else if (ret == -2) {

                        ShowMsg(Handle ,"不能添加相同目录的书!",3);
            result = true;
		}
	}
	return result;
}


void TfrmStorageReturnMng::UpdateNote()//更新单
{
	if (dsetNote->Active && dsetNote->RecordCount >= 1)
	{
		cmdUpdateNote->Parameters->ParamByName("@ID")->Value
			= dsetNote->FieldByName("ID")->AsInteger;
		cmdUpdateNote->Parameters->ParamByName("@Amount")->Value
				= - abs(dsetNote->FieldByName("Amount")->AsInteger);
		cmdUpdateNote->Parameters->ParamByName("@Discount")->Value
			= fabs(dsetNote->FieldByName("Discount")->AsFloat);
		cmdUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 1;
		cmdUpdateNote->Parameters->ParamByName("@bkstackID")->Value = (int)(cbbkstackID->Items->Objects[cbbkstackID->ItemIndex]);
		if (stackchange) {
			cmdUpdateNote->Parameters->ParamByName("@bkchange")->Value = 1;
		}
		else
		{
			cmdUpdateNote->Parameters->ParamByName("@bkchange")->Value = 0;
		}
		cmdUpdateNote->Execute();
		try
		{
			//LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
		 //	QryNtHeader();      重新查询单头


			//((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00";
			//((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "￥###,###,##0.00";
			//((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = "￥###,###,##0.00";
			//((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = "￥###,###,##0.00";
		}
		__finally
		{
			//LockWindowUpdate(NULL);
		}
	}
}


void TfrmStorageReturnMng::UpdateNote1()//更新单
{
	if (dsetNote->Active && dsetNote->RecordCount >= 1)
	{
		cmdUpdateNote->Parameters->ParamByName("@ID")->Value
			= dsetNote->FieldByName("ID")->AsInteger;
		cmdUpdateNote->Parameters->ParamByName("@Amount")->Value
				= - abs(dsetNote->FieldByName("Amount")->AsInteger);
		cmdUpdateNote->Parameters->ParamByName("@Discount")->Value
			= fabs(dsetNote->FieldByName("Discount")->AsFloat);
		cmdUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 1;
		cmdUpdateNote->Execute();
	}
}


void TfrmStorageReturnMng::DelNote()//删除单
{
	if (dsetNote->Active && dsetNote->RecordCount >= 1)
	{
		if (dbgrdNote->SelectedRows->Count == 0)
		{
			cmdDelNote->Parameters->ParamByName("@ID")->Value
				= dsetNote->FieldByName("ID")->AsInteger;
			cmdDelNote->Parameters->ParamByName("@Bsmode")->Value = 1;
			if (ChangeDisplay) {
				logmessage = "删除入库退货单" + dsetNtHeader->FieldByName("StgNtCodeStr")->AsAnsiString ;
			}
			else
			{
				logmessage = "删除入库退货单" + dsetNtHeader->FieldByName("StgNtCode")->AsAnsiString ;
			}
			logmessage = logmessage + "的书目《" + dsetNote->FieldByName("CatalogName")->AsAnsiString + "》";
			AddEvent(1,"一般入库退货窗口",m_userID,m_storageID,logmessage,linfo.con);
			cmdDelNote->Execute();
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
		else if (dbgrdNote->SelectedRows->Count > 0)
		{
			String ids = "";
			dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[0];
			ids = ids + dsetNote->FieldByName("ID")->AsString;
			if (ChangeDisplay) {
				logmessage = "删除入库退货单" + dsetNtHeader->FieldByName("StgNtCodeStr")->AsAnsiString ;
			}
			else
			{
				logmessage = "删除入库退货单" + dsetNtHeader->FieldByName("StgNtCode")->AsAnsiString ;
			}
			logmessage = logmessage + "的书目《" + dsetNote->FieldByName("CatalogName")->AsAnsiString + "》";
			AddEvent(1,"一般入库退货窗口",m_userID,m_storageID,logmessage,linfo.con);
			for (int i=1; i < dbgrdNote->SelectedRows->Count; i++)
			{
				dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[i];
				ids = ids + "," + dsetNote->FieldByName("ID")->AsString;
				if (ChangeDisplay) {
					logmessage = "删除入库退货单" + dsetNtHeader->FieldByName("StgNtCodeStr")->AsAnsiString ;
				}
				else
				{
					logmessage = "删除入库退货单" + dsetNtHeader->FieldByName("StgNtCode")->AsAnsiString ;
				}
				logmessage = logmessage + "的书目《" + dsetNote->FieldByName("CatalogName")->AsAnsiString + "》";
				AddEvent(1,"一般入库退货窗口",m_userID,m_storageID,logmessage,linfo.con);
			}
                        dsetNote->Next();
			cmdBatchDelNote->Parameters->ParamByName("@IDS")->Value = ids;
			cmdBatchDelNote->Parameters->ParamByName("@Bsmode")->Value = 1;
			cmdBatchDelNote->Execute();
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
}

void TfrmStorageReturnMng::BatchSetNotes(int amount, float discount, int mode)
{
	String ids = "";
	if (dsetNote->Active && dsetNote->RecordCount >= 1)
	{
		if (mode == 1 || mode == 2) {

			if (dbgrdNote->SelectedRows->Count == 0)
			{
				if (rktuihuoguanli) {
					AnsiString sql;
					sql = "select A.amount - B.amount as amount from "
						" (select sum(amount) as amount from BS_StorageNote where BkInfoID = " + dsetNote->FieldByName("BkInfoID")->AsString  + ") A,"
						" (select amount from BS_StorageNote where id = " + dsetNote->FieldByName("ID")->AsString + ") B " ;
					query->Close();
					query->SQL->Clear();
					query->SQL->Add(sql);
					query->Open();
					if (abs(amount) > query->FieldByName("amount")->AsInteger ) {
						dsetNote->Edit();
						dsetNote->FieldByName("Amount")->AsInteger = query->FieldByName("amount")->AsInteger;
						if (mode == 1) {
							dsetNote->FieldByName("discount")->AsFloat =  discount;
						}
						dsetNote->UpdateBatch(arCurrent);
						//MessageBox(0,"退货数量大于入库总数量！","提示" ,MB_OK);
						UpdateNote1();
					}
					else
					{
						ids = ids + dsetNote->FieldByName("ID")->AsString;
					}
				}
				else
				{
					ids = ids + dsetNote->FieldByName("ID")->AsString;
				}
			}
			else if (dbgrdNote->SelectedRows->Count > 0)
			{
				dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[0];
                if (rktuihuoguanli) {
					AnsiString sql;
					sql = "select A.amount - B.amount as amount from "
						" (select sum(amount) as amount from BS_StorageNote where BkInfoID = " + dsetNote->FieldByName("BkInfoID")->AsString  + ") A,"
						" (select amount from BS_StorageNote where id = " + dsetNote->FieldByName("ID")->AsString + ") B " ;
					query->Close();
					query->SQL->Clear();
					query->SQL->Add(sql);
					query->Open();
					if (abs(amount) > query->FieldByName("amount")->AsInteger ) {
						dsetNote->Edit();
						dsetNote->FieldByName("Amount")->AsInteger = query->FieldByName("amount")->AsInteger;
						if (mode == 1) {
							dsetNote->FieldByName("discount")->AsFloat =  discount;
						}
						dsetNote->UpdateBatch(arCurrent);
						//MessageBox(0,"退货数量大于入库总数量！","提示" ,MB_OK);
						UpdateNote1();
					}
					else
					{
						ids = ids + dsetNote->FieldByName("ID")->AsString;
					}
				}
				else
				{
					ids = ids + dsetNote->FieldByName("ID")->AsString;
				}
				for (int i=1; i < dbgrdNote->SelectedRows->Count; i++)
				{
					dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[i];
					if (rktuihuoguanli) {
						AnsiString sql;
						sql = "select A.amount - B.amount as amount from "
							" (select sum(amount) as amount from BS_StorageNote where BkInfoID = " + dsetNote->FieldByName("BkInfoID")->AsString  + ") A,"
							" (select amount from BS_StorageNote where id = " + dsetNote->FieldByName("ID")->AsString + ") B " ;
						query->Close();
						query->SQL->Clear();
						query->SQL->Add(sql);
						query->Open();
						if (abs(amount) > query->FieldByName("amount")->AsInteger ){
							dsetNote->Edit();
							dsetNote->FieldByName("Amount")->AsInteger = query->FieldByName("amount")->AsInteger;
                            if (mode == 1) {
								dsetNote->FieldByName("discount")->AsFloat =  discount;
							}
							dsetNote->UpdateBatch(arCurrent);
							//MessageBox(0,"退货数量大于入库总数量！","提示" ,MB_OK);
							UpdateNote1();
						}
						else
						{
							ids = ids + "," + dsetNote->FieldByName("ID")->AsString;
						}
					}
					else
					{
						ids = ids + "," + dsetNote->FieldByName("ID")->AsString;
					}
				}
			}
			else
				return;
		}
		else if (mode == 3) {

			if (dbgrdNote->SelectedRows->Count == 0)
			{
				ids = ids + dsetNote->FieldByName("ID")->AsString;
			}
			else if (dbgrdNote->SelectedRows->Count > 0)
			{
				dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[0];
				ids = dsetNote->FieldByName("ID")->AsString;
				for (int i=1; i < dbgrdNote->SelectedRows->Count; i++)
				{
					dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[i];
					ids = ids + "," + dsetNote->FieldByName("ID")->AsString;
				}
			}
			else
				return;
		}

		if (ids == "") {
			QryNtHeader();
		}
		else
		{
        	switch(mode)
			{
			case 1://两者均更新
				cmdBatchUpdateNote->Parameters->ParamByName("@IDS")->Value = ids;
				cmdBatchUpdateNote->Parameters->ParamByName("@Amount")->Value = amount;
				cmdBatchUpdateNote->Parameters->ParamByName("@Discount")->Value = discount;
				cmdBatchUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 1;
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
			case 2://只更新Amount
				cmdBatchUpdateNote->Parameters->ParamByName("@IDS")->Value = ids;
				cmdBatchUpdateNote->Parameters->ParamByName("@Amount")->Value = amount;
				cmdBatchUpdateNote->Parameters->ParamByName("@Discount")->Value = "";
				cmdBatchUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 1;
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
			case 3://只更新Discount
				cmdBatchUpdateNote->Parameters->ParamByName("@IDS")->Value = ids;
				cmdBatchUpdateNote->Parameters->ParamByName("@Discount")->Value = discount;
				cmdBatchUpdateNote->Parameters->ParamByName("@Amount")->Value = "";
				cmdBatchUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 1;
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
}

void __fastcall TfrmStorageReturnMng::edtQrySupplierKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r')
	{
		if (!dsetNtHeader->Active
			|| !dsetNote->Active
			|| (dsetNtHeader->Active && dsetNtHeader->RecordCount < 1))
			return;
		if (!dblkpcbbSupplierID->Enabled ) {
		   return;
		}
		AnsiString sql;
		sql = " select * from CUST_CustomerInfo where Type =1 and customerstate =1 and "+QFSupplierTiaoJian+" and  Name like '%"+ edtQrySupplier->Text.Trim() + "%' order by name";
		dsetSupplier->Active = false;
		dsetSupplier->CommandText = sql;
		dsetSupplier->Active = true;
		dsetSupplier->First();
		dblkpcbbSupplierID->KeyValue = dsetSupplier->FieldByName("ID")->AsInteger ;
		dsetNtHeader->Edit();
		dsetNtHeader->FieldByName("SupplierID")->AsInteger = dsetSupplier->FieldByName("ID")->AsInteger;
		dsetNtHeader->Post();
		dblkpcbbSupplierID->SetFocus();
		SupplierCreit();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::dblkpcbbStaffIDKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r')
	{
		Key = 0;
		Perform(WM_NEXTDLGCTL, 0, 0);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::edtCatalogKeyPress(TObject *Sender, wchar_t &Key)
{
	int results;
	if (m_catalogSearchMode == 6) {
		if ((Key < '0' || Key > '9') && (Key != '\b') && (Key != '.') && (Key != '\r') ) {
            Key = NULL;
		}
	}
	if (Key == '\r')
	{
        if (BtnSave->Enabled) {
			ShowMsg(Handle ,"请先保存入库退货单!",3);
			return;
		}
		if (!dsetNote->Active || !dsetNtHeader->Active
			|| (dsetNtHeader->Active && dsetNtHeader->RecordCount < 1))
			return;

		if (edtCatalog->Text == "")
		{
			changeInputMode();
		}
		else
		{
			float price;
			if (m_catalogSearchMode == 6) {
				try {
					price = StrToFloat(edtCatalog->Text.Trim());
				} catch (...) {
					ShowMsg(Handle ,"请输入正确的定价!",3);
					return;
				}
			}
					String ISBN;
					bool exec = true;

					TfrmSelectCatalog* frm = new TfrmSelectCatalog(Application,m_con);
					//frm->BtnWeekView ->Visible = false;
					LandInfo li;
					li.app = m_app;
					li.con = m_con;
					li.userID = m_userID;
					li.storageID = m_storageID;
					frm->Init(&li);

					frm->m_supplierID = dsetNtHeader->FieldByName("SupplierID")->AsInteger ;
					frm->SetSearchMode(m_catalogSearchMode, edtCatalog->Text);
					frm->DoModalType = 8;
					frm->StorageReturnfrm = this;
                                         frm->SelectAll = false;


                                        //期刊处理
                                        if (edtCatalog->Text.Trim().Length()>13) {

                                           frm->qikan= true;
                                           frm->qikanhao =edtCatalog->Text.SubString(14,edtCatalog->Text.Trim().Length()-13) ;
                                        }
                                        frm->QryBkInfo();
                                          if (frm->findbooks == 3) {   //找到多条记录
                                          results= frm->ShowModal();
                                        }else if (frm->findbooks==1) {  //只找到一条，就不显示选择窗口了
                                          results = 1;
                                        }else if ((frm->findbooks==0)||(frm->findbooks==-1)) {  //没有找到或都出错
                                          results = -1 ;
                                        }

				if (mrOk == results)
				{
				   int bkinfoid = -1,catalogID = -1;
				   frm->GetSelectResult(bkinfoid,catalogID);
					 //supplierID = dsetSupplier->FieldByName("ID")->AsInteger ;
					 if (frm->SelectAll) {                           //全选
						  for (int i = 0; i < frm->lengthint  ; i++) {
							 if (AddNote(frm->BkcatalogiD[i])) {
								 Key = 0;
								 Perform(WM_NEXTDLGCTL, 0, 0);

							 }
						  }
						  QryNtHeader();
					 } else
						  {
							if (catalogID >= 0)
							{
                                TLocateOptions   Opts;
								Opts.Clear();
								Opts   <<   loPartialKey;
								String   str   = AnsiString(catalogID);

                                                                bool samein;
                                                                if (!dsetNote->Locate("BkcatalogID",str,Opts)) {   //没有相同记录书
                                                                    samein=true;
                                                                }else       //有相同的记录
                                                                {
                                                                     if (sametuiinput) {   //如果允许重复录入
                                                                       samein=true;
                                                                     }else samein = false;
                                                                    if (sameid) {    //后台设置需要提示
                                                                            ShowMsg(Handle ,"有相同记录请核实！",3);

                                                                    }
                                                                }
                                                                                                                    //允许重复录入
                                                                if (samein)
                                                                {

								if (AddNote(-1, catalogID))
								{
									Key=0;
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
										dbnbedtAmount ->SetFocus();
										 //	edtCatalog->SetFocus();
									}
								}
								}
								else
								{
									
									dbgrdNote->SelectedRows->CurrentRowSelected = true;
									dbgrdNote->SetFocus();
									dbnbedtAmount->SetFocus();
								}

								   //	MessageBox(0,"库存无该书!","入库单",MB_ICONEXCLAMATION);
							}
						  }
					 }
					 Key=0;
					 edtCatalog->Text = "";
				   delete frm;
				   historyview();

		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmStorageReturnMng::dbedtSupplySNKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r')
	{
		Key = 0;
		dbnbedtAddCosts->SetFocus();
		//Perform(WM_NEXTDLGCTL, 0, 0);
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmStorageReturnMng::dbnbedtAmountKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r')
	{
		Key = 0;
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
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "0.00";
		historyview();
   /*	try
	{
		double price,discount;
		int amount;
		double totaldis,totalfix;

		price = dsetNote->FieldByName("price")->AsFloat ;
		discount =  dsetNote->FieldByName("Discount")->AsFloat;
		amount = dbnbedtAmount->Value;
		totaldis = amount * price * discount * 0.01*-1;
		totalfix = amount * price*-1;
		dsetNote->Edit();
		dsetNote->FieldByName("Amount")->AsInteger = amount*-1;
		dsetNote->FieldByName("FixedPrice")->AsInteger =  totalfix;
		dsetNote->FieldByName("DiscountedPrice")->AsInteger = totaldis;
		GetHtHeaderTotal();
	}
	catch(...)
	{

	}  */

	}
}
//---------------------------------------------------------------------------

void TfrmStorageReturnMng::DelInvalidNtHeader()
{
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1
		&& dsetNote->Active && dsetNote->RecordCount < 1 && dsetNtHeader->FieldByName("StgNtCode")->AsInteger  == 0)
	{
    	DelNtHeader();
	}
}

void __fastcall TfrmStorageReturnMng::FormClose(TObject *Sender, TCloseAction &Action)
{
	DelInvalidNtHeader();
	spQryNtHeader->Active = false;
	spQryNtHeader1->Active = false;
	dsetSupplier->Active = false;
	dsetStaff->Active = false;
	dsetSupplier->Active = false;
	dsetBkstack->Active = false;
	BSSET->Free();
	TfrmMDIChild::FormClose(Sender, Action);
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::RzToolButton9Click(TObject *Sender)
{
	Close();
        HANDLE hWindow = FindWindow("TfrmMain",NULL);
        SendMessage(hWindow ,WM_MYMESSAGE,0,0);
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::RzToolButton8Click(TObject *Sender)
{
	//打印
	if (!SaveStorage(1))
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
		frm->PrintStorage(StrToInt(dsetNtHeader->FieldByName("ID")->AsString));

		frm->DanhaoChange = ChangeDisplay ;      //change danhao
		frm->RvSystem1->SystemSetups >>ssAllowSetup;
		frm->RvSystem1->SystemSetups >>ssAllowDestPreview;
		frm->RvSystem1->SystemSetups >>ssAllowDestPrinter;
		frm->RvSystem1->SystemSetups >>ssAllowPrinterSetup;
		frm->RvSystem1->SystemSetups >>ssAllowDestFile;
		frm->RvSystem1->DefaultDest   = rdPrinter ;
		frm->RvSystem1->SystemSetups<<ssAllowDestPrinter;
		frm->Maker = 	lblOpName->Caption;
		frm->rkbk = rkbk;
		frm->printtitle = printtitle;
		frm->contact = contact;
		frm->tel = tel;
		frm->address = address;
		frm->tuihuo = 1;
		frm->PrintStorageExe(0);
		/*if (lbcaption->Caption == "入库单")
		{
			 frm->PrintStorageExe(1);
		}else
		{
			 frm->PrintStorageExe(2);
		}    */

		frm->Close();
		delete frm;
        AnsiString sql = "update BS_StorageNoteHeader set printcount = printcount + 1 where id = " + dsetNtHeader->FieldByName("id")->AsString ;
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->ExecSQL();
		QryNtHeader();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::RzToolButton6Click(TObject *Sender)
{
	//Excel导出
	if (!SaveStorage(1))
	{
		return;
	}
	if (dsetNote->Active && dsetNote->RecordCount >= 1)
	{
		DbgridToExcel(dbgrdNote);
	}
}
bool __fastcall TfrmStorageReturnMng::DbgridToExcel(TRzDBGrid* dbg)
{
	AnsiString temptext,path  ;
	int k = dbg->DataSource ->DataSet ->RecordCount ,n=0;

	savedlg->FileName = StringReplace(dblkpcbbSupplierID->Text.Trim()+editdanhao->Text.Trim() ,"\\","-",TReplaceFlags()<<rfReplaceAll)+ "入库退货单";
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



	Variant  v,vSheet,R,xWorkbook;
	v   =Variant::CreateObject("Excel.Application");
	v.OlePropertySet("Visible",true);
	v.OlePropertyGet("WorkBooks").OleFunction("Add");
	xWorkbook = v.OlePropertyGet("ActiveWorkBook");
	vSheet =  xWorkbook.OlePropertyGet("ActiveSheet");


	n=0;

	int t1= 0;
	temptext = "\n";
	for(int q=0;q<dbg->FieldCount-1 ;++q)
	{
		if (dbg->Columns->Items[q]->Visible == true) {
			t1++;
			temptext = "'"+ dbg->Columns ->Items [q]->Title ->Caption;
			v.OlePropertyGet("Cells",1+n,(t1)).OlePropertySet("Value",temptext .c_str() );
			//temptext = temptext + dbg->Columns ->Items [q]->Title ->Caption + ",";
		}
	}
	//FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	int t2 = dbg->DataSource ->DataSet ->RecordCount ;

	dbg->DataSource ->DataSet ->First();
	dbg->DataSource ->DataSet->DisableControls();
	for(int i=2+n;i<=t2+1+n ;i++)
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

				else if (dbg->Columns ->Items [j-1]->FieldName == "id"){

				}
				else
				{
                    t1++;
					temptext = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
					//temptext = temptext + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
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
	temptext = RzDBNumericEdit2->Text ;
	v.OlePropertyGet("Cells",t2+2+n,9).OlePropertySet("Value",temptext .c_str() );
	temptext = RzDBNumericEdit3->Text ;
	v.OlePropertyGet("Cells",t2+2+n,11).OlePropertySet("Value",temptext.c_str() );
	temptext = RzDBNumericEdit4->Text ;
	v.OlePropertyGet("Cells",t2+2+n,12).OlePropertySet("Value",temptext .c_str() );
	dbg->DataSource ->DataSet->EnableControls();

    try {
		xWorkbook.OleFunction("SaveAs",path.c_str());
	} catch (Exception &E) {
		//ShowMessage(E.Message);
	}
	return false;
}

//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::dbnbedtAmountExit(TObject *Sender)
{
	if ((dsetNote->IsEmpty()) || (dsetNote->RecordCount==0)) {
		return;
	}
              if (dbnbedtAmount->Value >= 100000)
                {
                    dbnbedtAmount->Value = 0;

                }
	if (rktuihuoguanli) {
		AnsiString sql;
		sql = "select sum(amount) as amount from BS_StorageNote where bkinfoid = " + dsetNote->FieldByName("BkInfoID")->AsString ;
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->Open();
		if (dbnbedtAmount->IntValue > query->FieldByName("amount")->AsInteger - dsetNote->FieldByName("Amount")->AsInteger ) {
                      ShowMsg(Handle ,"退货数量大于该供应商可退数量！",3);

			dbnbedtAmount->SetFocus();
			return;
		}
		if (dbnbedtAmount->IntValue > RzDBNumericEdit1->IntValue - dsetNote->FieldByName("Amount")->AsInteger ) {
                      ShowMsg(Handle ,"退货数量大于该供应商库存数量！",3);


			dbnbedtAmount->SetFocus();
			return;
		}
	}

	try
	{
		double price,discount;
		int amount;
		double totaldis,totalfix;

		price = dsetNote->FieldByName("price")->AsFloat ;
		discount =  dsetNote->FieldByName("Discount")->AsFloat;
		amount = dbnbedtAmount->Value;
		totaldis = abs(amount) * price * discount * 0.01*-1;
		totalfix = abs(amount) * price*-1;
		dsetNote->Edit();
		dsetNote->FieldByName("Amount")->AsInteger = abs(amount)*-1;
		dsetNote->FieldByName("FixedPrice")->AsInteger =  totalfix;
		dsetNote->FieldByName("DiscountedPrice")->AsInteger = totaldis;
		dsetNote->Post();
		GetHtHeaderTotal();
	}
	catch(...)
	{

	}
	//更新完dataset后，才更新数据库
	UpdateNote();
	tuihuolv();
	GetHtHeaderTotal();
}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------


void TfrmStorageReturnMng::QryBkstack()
{
   if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1
		&& dsetNote->Active && dsetNote->RecordCount >= 1)
	{
		String sql;
		sql = " SELECT STK_BookstackInfo.ID, STK_BookstackInfo.Name "
			" FROM STK_BookInfo LEFT OUTER JOIN"
			" STK_BookstackInfo ON STK_BookInfo.BkstackID = STK_BookstackInfo.ID"
			" where SupplierID=" + dsetNtHeader->FieldByName("SupplierID")->AsString
			 + " and BkcatalogID=" + dsetNote->FieldByName("BkcatalogID")->AsString
			 + " and STK_BookstackInfo.StgID=" + dsetNtHeader->FieldByName("StgID")->AsString;
		TADOQuery *aq  = new TADOQuery(Application);
		aq->Connection = m_con ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		while(!aq->Eof)
		{
		  aq->Next();
		}
	}
}


/*void TfrmStorageReturnMng::OnHotKeyPress(DWORD vkCode, bool ctrlpress)
{
	//快捷键

}

void TfrmStorageReturnMng::ResetNtHeader()
{
	//重置单头
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1
		&& dsetNote->Active && dsetNote->RecordCount < 1
		&& dsetNtHeader->FieldByName("State")->AsInteger == 0)
	{
		cmdResetNtHeader->Parameters->ParamByName("@ID")->Value =
			dsetNtHeader->FieldByName("ID")->AsInteger;
		cmdResetNtHeader->Parameters->ParamByName("@Bsmode")->Value = 1;
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
}  */
void __fastcall TfrmStorageReturnMng::sbnewcustomerClick(TObject *Sender)
{
	//添加新供应商
	String ID;
	ID = "";

   dsetSupplier->Active = false;
   dsetSupplier->CommandText = "select ID, Name from CUST_CustomerInfo where Type=1 and customerstate =1 and "+QFSupplierTiaoJian;
   dsetSupplier->Active = true;

	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1
		&& dsetNote->Active && dsetNote->RecordCount >= 1)//此时不能修改供应商
	{

	}
	else if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1
		&& dsetNote->Active && dsetNote->RecordCount < 1)//可以修改供应商
	{

		int count1 = dsetSupplier->RecordCount;
		TDetaileForm * frm = new TDetaileForm(m_app,1,1,ID.c_str() ,m_con,m_storageID);
		frm->ShowModal();
		delete frm;

		dsetSupplier->Active = false;
		dsetSupplier->Active = true;
		int count2 = dsetSupplier->RecordCount;
		if (count2 > count1)
		{
			dsetSupplier->Last();
			dsetNtHeader->Edit();
			dsetNtHeader->FieldByName("SupplierID")->AsInteger = dsetSupplier->FieldByName("ID")->AsInteger;
			UpdateNtHeader();
			dblkpcbbSupplierID->SetFocus();
			SupplierCreit();
		}
	}

	   //	NewSupplier(m_app, m_con);

	 //  i = NewSupplier(m_app,m_con);
			 //	NewCustomer(m_app, m_con);
	   /*  LandInfo *li;
		 li->con = m_con;
		 li->userID = m_userID;



		 frmSupplierinfo = new TfrmSupplierinfo(m_app);
		 frmSupplierinfo->Init(li);
		 frmSupplierinfo->ShowModal();
		 delete frmSupplierinfo;
		 delete li;*/
}
//---------------------------------------------------------------------------



void __fastcall TfrmStorageReturnMng::BtnViewClick(TObject *Sender)
{
    if (!SaveStorage(1))
	{
		return;
	}
	//DelInvalidNtHeader();
	TControl* con = dynamic_cast<TControl*>(Sender);
	if (con != NULL)
	{
		dbgrdNote->SetFocus();
		ChangeOpmode(con->Tag);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::lblCatalogMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	if (Button == mbLeft ) {
		TPoint  pt;
		GetCursorPos(&pt);
		PM->Popup(pt.x,pt.y);

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::N1Click(TObject *Sender)
{
   	lblCatalog->Caption = "书号";
	m_catalogSearchMode = 1;
	edtCatalog->MaxLength = 20;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::N2Click(TObject *Sender)
{
	lblCatalog->Caption = "自编码";
	m_catalogSearchMode = 2;
	edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::N3Click(TObject *Sender)
{
	lblCatalog->Caption = "书名";
	m_catalogSearchMode  = 3;
	edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::BtnClearClick(TObject *Sender)
{
	if (!SaveStorage(1))
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
		frm->PrintStorage(StrToInt(dsetNtHeader->FieldByName("ID")->AsString));
		frm->DanhaoChange = ChangeDisplay ;                      //change danhao
		frm->RvSystem1->SystemSetups >>ssAllowSetup;
		frm->RvSystem1->SystemSetups >>ssAllowDestPreview;
		frm->RvSystem1->SystemSetups >>ssAllowDestPrinter;
		frm->RvSystem1->SystemSetups >>ssAllowPrinterSetup;
		frm->RvSystem1->SystemSetups >>ssAllowDestFile;
		frm->RvSystem1->DefaultDest  = rdPreview ;
		frm->RvSystem1->SystemSetups<<ssAllowDestPreview;
		 frm->Maker = 	lblOpName->Caption;
		 frm->rkbk = rkbk;
		 frm->printtitle = printtitle;
		 frm->contact = contact;
		 frm->tel = tel;
		 frm->address = address;
		 frm->tuihuo = 1;
                 try
                 {
		 frm->PrintStorageExe(1);
                 }catch(...)
                 {}
		/*if (lbcaption->Caption == "入库单")
		{
			 frm->PrintStorageExe(1);
		}else
		{
			 frm->PrintStorageExe(2);
		}  */

		frm->Close();
		delete frm;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::RzToolButton3Click(TObject *Sender)
{
	TControl* con = dynamic_cast<TControl*>(Sender);
	if (con != NULL)
	{
		dbgrdNote->SetFocus();
		ChangeOpmode(con->Tag);
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmStorageReturnMng::RzToolButton5Click(TObject *Sender)
{
    if (dsetNtHeader->IsEmpty() ) {
		return;
	}
	if (dsetNtHeader->FieldByName("StgNtCode")->AsInteger == 0) {
    	return;
	}
	if (!SaveStorage(1))
	{
		return;
	}
	DelInvalidNtHeader();
	TControl* con = dynamic_cast<TControl*>(Sender);
	if (con != NULL)
	{
		dbgrdNote->SetFocus();
		ChangeOpmode(con->Tag);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::RzToolButton2Click(TObject *Sender)
{
	TControl* con = dynamic_cast<TControl*>(Sender);
	if (con != NULL)
	{
		dbgrdNote->SetFocus();
		ChangeOpmode(con->Tag);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::dblkpcbbSupplierIDKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == VK_RETURN) {
		if (dblkpcbbSupplierID->Text == "") {
			ShowMsg(Handle ,"请选择供应商！",3);
			return;
		}
		else
		{
			/*AnsiString sql = "select Salesman from CUST_CustomerInfo where id = " + IntToStr(dsetSupplier->FieldByName("ID")->AsInteger );
			query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->Open();
			sql = "select * from SYS_StaffInfo where Name = '" + query->FieldByName("Salesman")->AsString + "' and stgID = " + IntToStr(m_storageID) + " and Career = 1";
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
			supplierDI = dsetSupplier->FieldByName("ID")->AsInteger;
			UpdateNtHeader();
			sbnewcustomer->Enabled = false;
			dblkpcbbSupplierID->Enabled = false;
			//dbedtSupplySN->SetFocus();
			edtCatalog->Text = "";
			dbnbedtAmount->Value = 0;
			dbnbedtDiscount->Value = 100.00;
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00";
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "0.00";  */
			BtnSave->Click();
		}
	}
}
//---------------------------------------------------------------------------

void  TfrmStorageReturnMng::FindNote(String code)
{
	DelInvalidNtHeader();
	edtCatalog->Text = "";
	edtQrySupplier->Text = "";
	dblkpcbbSupplierID->Enabled  = false;
	try
	{
		//LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
		QryNtHeader(code);
	}
	__finally
	{
		//LockWindowUpdate(NULL);
	}
	SaveOrNot = true;
	BtnSave->Enabled = false;
	dblkpcbbSupplierID->Enabled = false;
	sbnewcustomer->Enabled = false;
}

//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::dbgrdNoteDblClick(TObject *Sender)
{
	/*if (dsetNote->RecordCount > 0) {
		TfrmNewBookModify * frm = new TfrmNewBookModify(m_app,m_con,dsetNote->FieldByName("BkcatalogID")->AsInteger );
		frm->ShowModal();
		delete frm;
		spQryNtHeader->Active = false;
		spQryNtHeader1->Active = false;
		spQryNtHeader1->Parameters->ParamByName("@NtCode")->Value = dbedtStgNtCode->Text;
		spQryNtHeader1->Parameters->ParamByName("@Bsmode")->Value = 1;
		MYTRACEF(_T("query note header @NtCode=%S"), dbedtStgNtCode->Text.c_str());
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
			if (dsetNote->FieldByName("amount")->AsInteger < 0 ) {
				lbcaption->Caption = "入库退货单";
			}
			dsetNote->AfterScroll = dsetNoteAfterScroll;
		}
		catch(...)
		{
			//ShowMessage("该单不存在！");
		}
	}   */
	if (dsetNote->IsEmpty() ) {
		return;
	}
		TfrmNewBookModify * frm = new TfrmNewBookModify(m_app,m_con,dsetNote->FieldByName("BkcatalogID")->AsInteger,m_storageID,m_userID);
		frm->ShowModal();
		delete frm;
		QryNtHeader();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::dbgrdNoteCellClick(TColumn *Column)
{

	/*if (dsetNote->IsEmpty()) {
		return;
	}
	editshun->Text = dsetNote->FieldByName("harmnum")->AsAnsiString ;
	//delete aq;
	historyview();*/
}
//---------------------------------------------------------------------------
 void TfrmStorageReturnMng::GetHtHeaderTotal()
{
	if (!dsetNtHeader->IsEmpty()) {
		adoGetHeadTotal->Parameters->ParamByName("@mode")->Value = 1;
		adoGetHeadTotal->Parameters->ParamByName("@ID")->Value = dsetNtHeader->FieldByName("ID")->AsInteger;
		if (!adoGetHeadTotal->Active ) {
			adoGetHeadTotal->Active = true;
		}else
		{
			adoGetHeadTotal->Active=false;
			adoGetHeadTotal->Active = true;
		}
	}
}
//---------------------------------------------------------------------------
void TfrmStorageReturnMng::historyview()
{
	String sql;
	if (dsetNote->IsEmpty() ) {
    	return;
	}
	if (dsetNote->RecordCount > 0) {

		DATE datetime = Date();
		datetime = datetime - storageday;
		sql = "select BS_StorageNoteHeader.StgNtCode as Ntcode,BS_StorageNoteHeader.StgNtCodeStr,BS_StorageNote.Amount,BS_StorageNote.Discount,Convert(varchar(20),BS_StorageNoteHeader.HdTime,111) as HdTime,CUST_CustomerInfo.Name,BS_BookCatalog.Price from BS_StorageNote left join BS_StorageNoteHeader on BS_StorageNote.StgNtHeaderID = BS_StorageNoteHeader.ID "
			  "left join BS_BookCatalog on BS_StorageNote.bkcatalogid = BS_BookCatalog.ID left join CUST_CustomerInfo on BS_StorageNoteHeader.SupplierID = CUST_CustomerInfo.id "
			  "WHERE bkcatalogid = " + dsetNote->FieldByName("BkcatalogID")->AsString ;
		sql = sql + " and BS_StorageNoteHeader.HdTime >= '" +  DateToStr(datetime) ;
		sql = sql + "' and BS_StorageNoteHeader.StgID = " + IntToStr(m_storageID)  ;
		if (!allsupplier) {
			sql = sql + " and BS_StorageNoteHeader.SupplierID = " + dsetSupplier->FieldByName("ID")->AsString ;
		}
		qudetail->Close();
		qudetail->SQL->Clear();
		qudetail->SQL->Add(sql);
		qudetail->Open();
		((TFloatField *)dgdetail->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0%";
		((TFloatField *)dgdetail->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "###,###,##0.00";
        int totamount = 0;
		qudetail->DisableControls();
		qudetail->First();
		while(!qudetail->Eof)
		{
			totamount = totamount + qudetail->FieldByName("Amount")->AsInteger ;
			qudetail->Next();
		}
		qudetail->EnableControls();
		edtotamount->Text = IntToStr(totamount);

		 //在数量和折扣框中显示选 中的行

		 dbnbedtAmount->Value  = dsetNote->FieldByName("Amount")->AsInteger;
		 dbnbedtDiscount->Value = dsetNote->FieldByName("Discount")->AsFloat;


	try
		{
			dssetStkAmount->Parameters->ParamByName("@mode")->Value = 1;
			dssetStkAmount->Parameters->ParamByName("@ID")->Value = dsetNote->FieldByName("ID")->AsInteger;

			if (!dssetStkAmount->Active) {
			    dssetStkAmount->Active= true;
			}else
			{
			   dssetStkAmount->Active = false;
               dssetStkAmount->Active= true;
			}

		}
		catch(...)
		{



		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::N5Click(TObject *Sender)
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

void __fastcall TfrmStorageReturnMng::N6Click(TObject *Sender)
{
	lblCatalog->Caption = "定价";
	m_catalogSearchMode  = 6;
	edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::BtnNewClick(TObject *Sender)
{
    if (!SaveStorage(1))
	{
	  return;
	}
	//DelInvalidNtHeader();
	querydan->Active = false;
	querydan->Active = true;
	DBNav->Enabled = false;
	String sql;
	sql = " select * from CUST_CustomerInfo where Type =1 and customerstate =1 and "+QFSupplierTiaoJian+" order by name ";
	dsetSupplier->Active = false;
	dsetSupplier->CommandText = sql;
	dsetSupplier->Active = true;
	//ChangeBsmode(BSNoteSendback);
	RzToolButton5Click(BtnNew);
	edkcedu->Text = "";
	edxyedu->Text = "";
	edbond->Text = "";
	dblkpcbbSupplierID->KeyValue = 0;
	SaveOrNot = false;
	BtnSave->Enabled = true;
	dbnbedtAddCosts->Enabled = true;
	dblkpcbbSupplierID->Enabled = true;
	dsetNtHeader->Edit();
	dsrcNtHeader->DataSet->FieldByName("AddCosts")->Value =  0.0;
	dsrcNtHeader->DataSet->FieldByName("Remarks")->Value =  "";
	dsrcNtHeader->DataSet->FieldByName("SupplySN")->Value =  "";
	dsetNtHeader->UpdateRecord();
	sbnewcustomer->Enabled = true;
	membk->Text = "";
	editdanhao->Text = "";
	dbnbedtAddCosts->Value = 0.0;
	dblkpcbbSupplierID->SetFocus();
	try {
    	qudetail->Active = false;
	} catch (...) {
	}
}
//---------------------------------------------------------------------------


void  TfrmStorageReturnMng::ModifyEnable()
{
	if (m_opmode == OPFind) {
		dbnbedtAmount->Enabled = false;
		dbnbedtDiscount->Enabled = false;
		cbbkstackID->Enabled = false;

	}
	else
	{
		dbnbedtAmount->Enabled = true;
		dbnbedtDiscount->Enabled = true;
		cbbkstackID->Enabled = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::BtnChangeOptionsClick(TObject *Sender)
{

		if (changepassword) {
			if (!CheckOperateAuthority())
					return;
		}
		try {
			beforesupplier = dsetSupplier->FieldByName("ID")->AsInteger;
			beforesuppliername = dsetSupplier->FieldByName("Name")->AsAnsiString ;
		} catch (...) {
		}
		dbnbedtAddCosts->Enabled = true;
		BtnSave->Enabled = true;
		SaveOrNot = false;
		dblkpcbbSupplierID->Enabled = true;
		sbnewcustomer->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
    if (Key == VK_F1)  //查单
	{
		if (!BtnView->Enabled ) {
			return;
		}
		BtnView->Click();
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
		if (!BtnChangeOptions->Enabled ) {
			return;
		}
		BtnChangeOptions->Click();
	}
	if (Key == VK_F5) {   //删行
		if (!RzToolButton2->Enabled ) {
			return;
		}
		RzToolButton2->Click();
	}
	if (Key == VK_F6) {   //统一
		if (!RzToolButton3->Enabled ) {
			return;
		}
		RzToolButton3->Click();
	}
	if (Key == VK_F7) {   //现场付款
		if (!BtnReminder->Enabled ) {
			return;
		}
		BtnReminder->Click();
	}
	if (Key == VK_F8) {   //导出
		if (!RzToolButton6->Enabled ) {
			return;
		}
		RzToolButton6->Click();
	}
	if (Key == VK_F9) {   //删单
		if (!RzToolButton5->Enabled ) {
			return;
		}
		RzToolButton5->Click();
	}
	if (Key == VK_F10) {   //打印
		if (!RzToolButton8->Enabled ) {
			return;
		}
		RzToolButton8->Click();
	}
	if (Key == VK_F11) {   //预览
    	if (!BtnClear->Enabled ) {
			return;
		}
		BtnClear->Click();
	}
	if (Shift.Contains(ssAlt)&& Key == 67) {    //定位
		SpeedButton1->Click();
	}

	if (Shift.Contains(ssCtrl)&& Key ==81  ) {
		RzToolButton9->Click();
	}

	if (Shift.Contains(ssCtrl)&& Key ==78  ) {
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==70  ) {
		BtnView1->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==90) {
		WindowState = wsNormal  ;
	}
}
//---------------------------------------------------------------------------
void TfrmStorageReturnMng::changeInputMode()
{
  switch (m_catalogSearchMode) {
	case 1:
		N2->Click();
		break;
	case 2:
		N3->Click();
		break;
	 case 3:
		N6->Click();
		break;
	 case 6:
		N10->Click();
		break;
	 case 5:
		N1->Click();
		break;
  default:
	  ;
  }
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::N8Click(TObject *Sender)
{
  	if (dsetNote->IsEmpty()) {
    	return;
	}
	AnsiString path;
	AnsiString StgID;
	AnsiString sql;
	StgID = "-1";
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

	adospcopy->ProcedureName = "CopyData";
	adospcopy->Parameters->Clear();
	adospcopy->Parameters->CreateParameter("@mode",ftInteger,pdInput,sizeof(int),1);
	adospcopy->Parameters->CreateParameter("@ID",ftString,pdInput,StgID.Length(),StgID.c_str());
	adospcopy->Parameters->CreateParameter("@userid",ftInteger,pdInput,sizeof(int),linfo.userID );
	adospcopy->ExecProc();

	dsetNote->EnableControls();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::dbgrdNoteMouseUp(TObject *Sender, TMouseButton Button,
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

void __fastcall TfrmStorageReturnMng::N9Click(TObject *Sender)
{
    if (BtnSave->Enabled) {

                ShowMsg(Handle ,"本单还未保存，请先保存！",3);
		return;
	}
	adospcopy->ProcedureName = "StickData";
	adospcopy->Parameters->Clear();
	adospcopy->Parameters->CreateParameter("@return",ftInteger,pdReturnValue,sizeof(int),-2);
	adospcopy->Parameters->CreateParameter("@mode",ftInteger,pdInput,sizeof(int),3);
	adospcopy->Parameters->CreateParameter("@HeadId",ftInteger,pdInput,sizeof(int),dsetNtHeader->FieldByName("ID")->AsInteger);
	adospcopy->Parameters->CreateParameter("@userid",ftInteger,pdInput,sizeof(int),linfo.userID );
    adospcopy->Parameters->CreateParameter("@stgid",ftInteger,pdInput,sizeof(int),linfo.storageID );
	adospcopy->Parameters->CreateParameter("@rksupplierid",ftInteger,pdInput,sizeof(int),dsetNtHeader->FieldByName("SupplierID")->AsInteger);
	adospcopy->ExecProc();
	int ret = adospcopy->Parameters->ParamByName("@return")->Value;
	if (ret == -1) {

                ShowMsg(Handle ,"请确保复制数据是同店同供应商的数据！",3);
		return;
	}
	else
	{
		QryNtHeader(dsetNtHeader->FieldByName("ID")->AsInteger, true);
	}

	Screen->Cursor = crDefault ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::BtnView1Click(TObject *Sender)
{
	Tfrmbookquery * frm = new Tfrmbookquery(Application,linfo.con,linfo.storageID);
	frm->ShowModal();
	delete frm;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::BtnSaveClick(TObject *Sender)
{
	if (!SaveOK()) {
        return;
	}
	edtCatalog->SetFocus();
}
//---------------------------------------------------------------------------

bool TfrmStorageReturnMng::SaveOK()
{
	if (dsetNote->RecordCount > 0) {
	if (dsetSupplier->FieldByName("ID")->AsInteger != beforesupplier) {
		ChangeSupplier();
		if (ChangeDisplay) {
			logmessage = "把入库退货单" + dsetNtHeader->FieldByName("StgNtCodeStr")->AsAnsiString ;
		}
		else
		{
			logmessage = "把入库退货单" + dsetNtHeader->FieldByName("StgNtCode")->AsAnsiString ;
		}
		logmessage = logmessage + "的供应商由" + beforesuppliername + "修改为" + dsetSupplier->FieldByName("Name")->AsAnsiString;
		AddEvent(1,"一般入库退货窗口",m_userID,m_storageID,logmessage,linfo.con);
		beforesupplier = dsetSupplier->FieldByName("ID")->AsInteger;
		UpdateNtHeader();
	}
		SaveOrNot = true;
		BtnSave->Enabled = false;
		dbnbedtAddCosts->Enabled = false;
		//dbedtSupplySN->Enabled = false;
		edtCatalog->SetFocus();
		dblkpcbbSupplierID->Enabled = false;
		sbnewcustomer->Enabled = false;
		return true;
	}
	else if (dsetNote->IsEmpty() && dsetNtHeader->FieldByName("StgNtCode")->AsInteger!= 0  ) {
		UpdateNtHeader();
		SaveOrNot = true;
		BtnSave->Enabled = false;
		dbnbedtAddCosts->Enabled = false;
		//dbedtSupplySN->Enabled = false;
		edtCatalog->SetFocus();
		dblkpcbbSupplierID->Enabled = false;
		sbnewcustomer->Enabled = false;
		return true;
	}
	spsave->Parameters->ParamByName("@MODE")->Value = 1;
	spsave->Parameters->ParamByName("@ID")->Value = dsetNtHeader->FieldByName("ID")->AsInteger ;
	spsave->Parameters->ParamByName("@STGID")->Value = linfo.storageID;
	spsave->Parameters->ParamByName("@TYPE")->Value = 1;
	spsave->Parameters->ParamByName("@CODEMODE")->Value = 1;
	spsave->Parameters->ParamByName("@ReturnCode")->Value = 0;
	spsave->Parameters->ParamByName("@ReturnCode2")->Value = 0;
  	spsave->ExecProc() ;

	if (ChangeDisplay) {
		logmessage = "添加入库退货单" + spsave->Parameters->ParamByName("@ReturnCode2")->Value ;
	}
	else
	{
		logmessage = "添加入库退货单" + spsave->Parameters->ParamByName("@ReturnCode")->Value ;
	}
	AddEvent(1,"一般入库退货窗口",m_userID,m_storageID,logmessage,linfo.con);
	historyview();     //SaveBenDan
	dbedtStgNtCode->Text = spsave->Parameters->ParamByName("@ReturnCode")->Value ;
	editdanhao->Text = spsave->Parameters->ParamByName("@ReturnCode2")->Value ;
	UpdateNtHeader();
	SaveOrNot = true;
	BtnSave->Enabled = false;
	dbnbedtAddCosts->Enabled = false;
  //dbedtSupplySN->Enabled = false;
  	edtCatalog->SetFocus();
	dblkpcbbSupplierID->Enabled = false;
	sbnewcustomer->Enabled = false;
	QryNtHeader();
  	return true;
}
//---------------------------------------------------------------------------

 bool TfrmStorageReturnMng::SaveStorage(int mode)
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
		  if( ShowMsg(Handle ,"本单还未保存，是否需要保存？",1)==1)
		  {
			  if (!SaveOK()) {
				  return false;
			  }
		  }else
		  {
			spsave->Parameters->ParamByName("@MODE")->Value = 2;
			spsave->Parameters->ParamByName("@ID")->Value = dsetNtHeader->FieldByName("ID")->AsInteger ;
			spsave->Parameters->ParamByName("@STGID")->Value = 0;
			spsave->Parameters->ParamByName("@TYPE")->Value = 1;
			spsave->Parameters->ParamByName("@CODEMODE")->Value = 1;
			spsave->Parameters->ParamByName("@ReturnCode")->Value = 0;
			spsave->Parameters->ParamByName("@ReturnCode2")->Value = 0;
			spsave->ExecProc() ;
		  }
	  }
	}else return true;

}
//---------------------------------------------------------------------------


void __fastcall TfrmStorageReturnMng::dbnbedtAddCostsExit(TObject *Sender)
{
	if (dsetNtHeader->RecordCount > 0) {
		AnsiString sql = "update BS_StorageNoteHeader set AddCosts = " + FloatToStr(dsetNtHeader->FieldByName("AddCosts")->AsFloat)  + " where id = " + dsetNtHeader->FieldByName("id")->AsString ;
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->ExecSQL();
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmStorageReturnMng::dbnbedtAddCostsKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		membk->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::BtnReminderClick(TObject *Sender)
{
	TControl* con = dynamic_cast<TControl*>(Sender);
	if (con != NULL)
	{
		dbgrdNote->SetFocus();
		ChangeOpmode(con->Tag);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::DBNavClick(TObject *Sender, TNavigateBtn Button)

{
	AnsiString code ;
   code = querydan->FieldByName("StgNtCode")->AsAnsiString ;
   editdanhao->Text = querydan->FieldByName("StgNtCodeStr")->AsAnsiString ;
	QryNtHeader(code,false);
}
//---------------------------------------------------------------------------
void TfrmStorageReturnMng::ChangeSupplier()
{
	if (dsetNote->IsEmpty() ) {
        return;
	}
	int supplier = dsetSupplier->FieldByName("ID")->AsInteger,supplierid,BkcatalogID;
	String sql;
	int bkid;
	dsetNote->First();
	while (!dsetNote->Eof )
		{
			supplierid = dsetNote->FieldByName("SupplierID")->AsInteger ;

			BkcatalogID =  dsetNote->FieldByName("BkcatalogID")->AsInteger ;
			sql = "select * from STK_BookInfo where BkcatalogID = " + dsetNote->FieldByName("BkcatalogID")->AsString + " and SupplierID = " + IntToStr(supplier) + " and BkstackID = " + dsetNote->FieldByName("BkstackID")->AsString;
			query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->Open();
			if (query->RecordCount > 0) {
				bkid = query->FieldByName("ID")->AsInteger ;
			}
			else
			{
				sql = "insert into STK_BookInfo(Amount,BkcatalogID,BkstackID,SupplierID,stgid) values (0," + dsetNote->FieldByName("BkcatalogID")->AsString + "," + dsetNote->FieldByName("BkstackID")->AsString + "," + IntToStr(supplier) + "," + IntToStr(m_storageID) + ")";
				query->Close();
				query->SQL->Clear();
				query->SQL->Add(sql);
				query->ExecSQL();
				sql = "select max(id) as id from STK_BookInfo";
				query->Close();
				query->SQL->Clear();
				query->SQL->Add(sql);
				query->Open();
				bkid = query->FieldByName("id")->AsInteger ;
			}
			sql = "update BS_StorageNote set BkInfoID = " + IntToStr(bkid) + " where id = " + dsetNote->FieldByName("ID")->AsString ;
            query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->ExecSQL();
			dsetNote->Next();
		}

}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::dbgrdNoteTitleClick(TColumn *Column)
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

void TfrmStorageReturnMng::FormView()
{
	/*AnsiString sql;
	sql = "select * from BS_SYS_Formview where stgid = " + IntToStr(m_storageID) + " and ParentID = 6";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	while (!query->Eof)
	{
		if (query->FieldByName("Name")->AsAnsiString == "查单" ) {
			BtnView->Visible = query->FieldByName("state")->AsBoolean ;
		}
		if (query->FieldByName("Name")->AsAnsiString == "增单" ) {
			BtnNew->Visible = query->FieldByName("state")->AsBoolean ;
		}
		if (query->FieldByName("Name")->AsAnsiString == "保存" ) {
			BtnSave->Visible = query->FieldByName("state")->AsBoolean ;
		}
		if (query->FieldByName("Name")->AsAnsiString == "修改" ) {
			BtnChangeOptions->Visible = query->FieldByName("state")->AsBoolean ;
		}
		if (query->FieldByName("Name")->AsAnsiString == "删单" ) {
			RzToolButton5->Visible = query->FieldByName("state")->AsBoolean ;
		}
		if (query->FieldByName("Name")->AsAnsiString == "删行" ) {
			RzToolButton2->Visible = query->FieldByName("state")->AsBoolean ;
		}
		if (query->FieldByName("Name")->AsAnsiString == "统一" ) {
			RzToolButton3->Visible = query->FieldByName("state")->AsBoolean ;
		}
		if (query->FieldByName("Name")->AsAnsiString == "现场付款" ) {
			BtnReminder->Visible = query->FieldByName("state")->AsBoolean ;
		}
		if (query->FieldByName("Name")->AsAnsiString == "Excel导出" ) {
			RzToolButton6->Visible = query->FieldByName("state")->AsBoolean ;
		}
		if (query->FieldByName("Name")->AsAnsiString == "预览" ) {
			BtnClear->Visible = query->FieldByName("state")->AsBoolean ;
		}
		if (query->FieldByName("Name")->AsAnsiString == "打印" ) {
			RzToolButton8->Visible = query->FieldByName("state")->AsBoolean ;
		}
		if (query->FieldByName("Name")->AsAnsiString == "查书" ) {
			BtnView1->Visible = query->FieldByName("state")->AsBoolean ;
		}
		if (query->FieldByName("Name")->AsAnsiString == "最小化" ) {
			BtnAlignBottom->Visible = query->FieldByName("state")->AsBoolean ;
		}
		query->Next();
	} */
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::dbnbedtDiscountKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r')
	{
		Key = 0;
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
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "0.00";
		historyview();
	}
}
void TfrmStorageReturnMng::tuihuolv()
{
	if (dsetNote->IsEmpty() ) {
        return;
	}
	FLOAT yeartuihuo,timetuihuo;
	yeartuihuo =0.00,
	timetuihuo =0.00;
	int totalamountall;
	   sptuihuo->Parameters->ParamByName("@clientID")->Value =  dsetSupplier->FieldByName("ID")->AsInteger;
	   sptuihuo->Parameters->ParamByName("@timelv")->Value =  0.00;
	   sptuihuo->Parameters->ParamByName("@yearlv")->Value =  0.00;

	   sptuihuo->ExecProc();
	   timetuihuo = sptuihuo->Parameters->ParamByName("@timelv")->Value;
	   yeartuihuo = sptuihuo->Parameters->ParamByName("@yearlv")->Value;

	   edityear->Text = FormatFloat("0.00",yeartuihuo) + "%" ;
	   editbenqi->Text  = FormatFloat("0.00",timetuihuo)+ "%" ;
	   if (yeartuihuo >= 100.00) {
		   edityear->Color = clRed ;
	   }else
	   {
			edityear->Color = clInfoBk ;
	   }
	   if (timetuihuo >= 100.00) {
		  editbenqi->Color = clRed ;
	   }else
	   {
			editbenqi->Color = clInfoBk ;
		}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::N10Click(TObject *Sender)
{
	lblCatalog->Caption = "作者";
	m_catalogSearchMode  = 5;
	edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::editshunExit(TObject *Sender)
{
	 if (editshun->Text == "") {
		editshun->Text = "0";
	}
	UpdateWsaleDiscout(3);
	QryNtHeader();
}
//---------------------------------------------------------------------------
void TfrmStorageReturnMng::UpdateWsaleDiscout(int mode)
{
	if (dsetNote->IsEmpty() ) {
		return;
	}
	if (dsetNote->Active && dsetNote->RecordCount >= 1)
	{
		adospupdatewsaleprice->Parameters->ParamByName("@storageNoteID")->Value
			= dsetNote->FieldByName("ID")->AsInteger;
		adospupdatewsaleprice->Parameters->ParamByName("@mode")->Value
			= 3;
		int harmnum ;
		try {
			harmnum =  StrToInt(editshun->Text);
			if (harmnum > 0) {
				harmnum = 0 - harmnum;
			}
		} catch (...) {
			return;
		}
		adospupdatewsaleprice->Parameters->ParamByName("@harmnum")->Value
			=  harmnum;
		adospupdatewsaleprice->ExecProc();
	}
}
//---------------------------------------------------------------------------
void  TfrmStorageReturnMng::operterview(int operterid)
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

void __fastcall TfrmStorageReturnMng::editshunKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        edtCatalog->SetFocus();
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmStorageReturnMng::membkKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r')
	{
	   /*edtCatalog->Text = "";
	   //edtCatalog->SetFocus();
	   dbnbedtAmount->Value = 0;
	   dbnbedtDiscount->Value = 100.00;
	   ((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00";
	   ((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "0.00";
	   BtnSave->Click(); */

		if (dsetNtHeader->RecordCount > 0) {
			AnsiString sql = "update BS_StorageNoteHeader set Remarks = '" + membk->Text + "' where id = " + dsetNtHeader->FieldByName("id")->AsString ;
			query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->ExecSQL();
		}
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmStorageReturnMng::SpeedButton1Click(TObject *Sender)
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

void __fastcall TfrmStorageReturnMng::chfsluruClick(TObject *Sender)
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

void __fastcall TfrmStorageReturnMng::N11Click(TObject *Sender)
{
	if (dsetNote->IsEmpty() ) {
		return;
	}
	Tfrmbookhistory *frm = new Tfrmbookhistory(Application,m_con,m_storageID,dsetNote->FieldByName("BkcatalogID")->AsInteger );
	frm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::cbbkstackIDSelect(TObject *Sender)
{
	stackchange = true;
	UpdateNote();
	stackchange = false;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------


void __fastcall TfrmStorageReturnMng::CheckBox1Click(TObject *Sender)
{
	if (CheckBox1->Checked ) {
		dgdetail->Visible = true;
	}
	else
	{
    	dgdetail->Visible = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::dsrcNoteDataChange(TObject *Sender, TField *Field)

{
	if (scroll == 1) {
		if (dsetNote->IsEmpty()) {
			editshun->Text = "0";
			dbnbedtAmount->IntValue = 0;
			dbnbedtDiscount->Value = 0.00;
			RzDBNumericEdit1->Text = "";
        	scroll = 0;
			return;
		}
		editshun->Text = dsetNote->FieldByName("harmnum")->AsAnsiString ;
		historyview();
		scroll = 0;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::dsetNoteBeforeScroll(TDataSet *DataSet)
{
	scroll = 1;
}
//---------------------------------------------------------------------------
bool TfrmStorageReturnMng::SupplierCreit()
{
	if (dblkpcbbSupplierID->Text == "") {
		edkcedu->Text = "";
		edxyedu->Text = "";
		return false;
	}
	AnsiString sql;
	sql = "select sum(stk_bookinfo.amount * stk_bookinfo.Cbprice) as shiyang,stk_bookinfo.supplierid, "
		" CUST_CustomerInfo.CreditMoney,CUST_CustomerInfo.Bond from CUST_CustomerInfo left join stk_bookinfo on stk_bookinfo.supplierid = CUST_CustomerInfo.id "
		" WHERE CUST_CustomerInfo.id  = " + dsetSupplier->FieldByName("ID")->AsAnsiString  + " group by CUST_CustomerInfo.CreditMoney,stk_bookinfo.supplierid,CUST_CustomerInfo.Bond";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	edkcedu->Text = FormatFloat("0.00",query->FieldByName("shiyang")->AsFloat);
	edxyedu->Text = query->FieldByName("CreditMoney")->AsAnsiString ;
    edbond->Text = query->FieldByName("Bond")->AsAnsiString ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::dblkpcbbSupplierIDClick(TObject *Sender)
{
	SupplierCreit();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::FormShow(TObject *Sender)
{
	edtQrySupplier->SetFocus();
}
//---------------------------------------------------------------------------


void __fastcall TfrmStorageReturnMng::dbnbedtDiscountExit(TObject *Sender)
{
   //
   	double jinjia;
	double discount;
	double price ;


	if (dsetNote->RecordCount == 0) {
		return;
	}

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
		dsetNote->EnableControls();

		UpdateNote();
		GetHtHeaderTotal();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::RzToolButton1Click(TObject *Sender)
{
    if (RzToolButton1->Caption =="显示\r主菜单")
    {

      HANDLE hWindow = FindWindow("TfrmMain",NULL);
      SendMessage(hWindow ,WM_MYMESSAGE,1,0);
      RzToolButton1->Caption ="隐藏\r主菜单";
    }else

    {
      HANDLE hWindow = FindWindow("TfrmMain",NULL);
      SendMessage(hWindow ,WM_MYMESSAGE,0,0);
      RzToolButton1->Caption ="显示\r主菜单";
    }
}
void  TfrmStorageReturnMng::storageprintxiaopiao(AnsiString ID,int type,int printorpre)
{

    AnsiString sql1;
  AnsiString sqldetail;
  storageqmuildetail->Connection =linfo.con;
   storageqmuilhead->Connection =linfo.con;

  if (type==1) {
     sql1="select D.name +'入库单' as title,A.remarks,D.Address,F.Contact, D.tel,A.Stgntcode,A.stgntcodestr,F.Name,F.address as saddress,F.telephone,A.hdtime,A.totalfixedprice,A.totaldiscountedprice,";
  }else
  {
      sql1="select D.name +'退货单' as title ,A.remarks,D.Address,F.Contact,D.tel,A.Stgntcode,A.stgntcodestr,F.Name,F.address as saddress,F.telephone,A.hdtime,A.totalfixedprice,A.totaldiscountedprice,";
  }
    sql1=sql1+"A.totalamount,A.stgntcodestr,A.addcosts,C.name as op  from BS_StorageNoteHeader A ";
    sql1=sql1+"left join sys_staffinfo B on A.staffid = B.ID ";
    sql1=sql1+"left join sys_user C on A.operatorid = C.ID ";
    sql1=sql1+"left join SYS_StorageInfo D on A.stgID = D.ID ";
    sql1=sql1+"left join CUST_CustomerInfo F on A.supplierid = F.ID ";
    sql1=sql1+"where stgntcode <>0 and A.id="+ID;



    sqldetail="select a.discount,a.amount,a.stgntheaderid,b.name,b.price from dbo.BS_StorageNote a left join dbo.BS_BookCatalog b ";
    sqldetail=sqldetail+" on a.bkcatalogid = b.id where stgntheaderid ="+ID;
  //  sqldetail=format(sqldetail,[ID]);
   storageqmuilhead->Close();
   storageqmuilhead->SQL->Clear();
   storageqmuilhead->SQL->Add(sql1);

   storageqmuildetail->Close();
   storageqmuildetail->SQL->Clear();
   storageqmuildetail->SQL->Add(sqldetail);
   storageqmuildetail->Open();
   storageqmuilhead->Open();

    AnsiString ps = ExtractFilePath(Application->ExeName) +"storagexiaopiao.fr3";
    frxstoragexiaopiao->LoadFromFile(ps);
    frxstoragexiaopiao->PrepareReport(true);
   if (printorpre==1) {//打印

     	frxstoragexiaopiao->PrintOptions->ShowDialog = false;
        frxstoragexiaopiao->Print();


   }else   //预览
   {

      frxstoragexiaopiao->ShowPreparedReport();
   }





}

//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::N16Click(TObject *Sender)

{
  try
{
	if (dsetNote->IsEmpty() || dsetNote->RecordCount == 0 ) {
		return;
	}
	//打印
	if (N11->Checked ) {    //异常打印
	  //
	}
	else                  //一般打印
	{
		if (!SaveStorage(1))
		{
		  return;
		}
		if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1 && dsrcNote->DataSet != NULL)
		{

                         storageprintxiaopiao(StrToInt(dsetNtHeader->FieldByName("ID")->AsString),2,2);


		}
	}
        }catch(...)
        {}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng::N15Click(TObject *Sender)

{
try
{
	if (dsetNote->IsEmpty() || dsetNote->RecordCount == 0 ) {
		return;
	}
	//打印
	if (N11->Checked ) {    //异常打印
	  //
	}
	else                  //一般打印
	{
		if (!SaveStorage(1))
		{
		  return;
		}
		if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1 && dsrcNote->DataSet != NULL)
		{
		                storageprintxiaopiao(StrToInt(dsetNtHeader->FieldByName("ID")->AsString),2,1);

                        	AnsiString sql = "update BS_StorageNoteHeader set printcount = printcount + 1 where id = " + dsetNtHeader->FieldByName("id")->AsString ;
				query->Close();
				query->SQL->Clear();
				query->SQL->Add(sql);
				query->ExecSQL();
				QryNtHeader();
		}
	}
        }catch(...)
        {}
}
//---------------------------------------------------------------------------

