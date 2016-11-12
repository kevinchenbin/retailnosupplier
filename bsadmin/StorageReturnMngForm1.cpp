//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "GetBsset.h"
#include "StorageReturnMngForm1.h"
#include <systdate.h>
#include "NoteCode.h"
#include "QryNoteCodeForm.h"
#include "SetNotesForm.h"
#include "mytrace.h"
#include "Print.h"
#include "pdtypes.h"
#include "..\catalogadmin\catalogadmin.h"
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
#pragma resource "*.dfm"
TfrmStorageReturnMng1 *frmStorageReturnMng1;
//---------------------------------------------------------------------------
__fastcall TfrmStorageReturnMng1::TfrmStorageReturnMng1(TComponent* Owner)
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

void TfrmStorageReturnMng1::Init(LandInfo* li)
{
	TfrmMDIChild::Init(li);
	linfo.app = li->app ;
	linfo.con = li->con ;
	linfo.userID = li->userID ;
	linfo.UserName = li->UserName ;
	linfo.storageID = li->storageID ;
	linfo.FormatStr = li->FormatStr ;
	lblOpName->Caption = li->UserName ;
	cmdAddNtHeader->Connection = m_con;
	spQryNtHeader->Connection = m_con;
	spQryNtHeader1->Connection = m_con;
	cmdUpdateNtHeader->Connection = m_con;
	cmdAddNote->Connection = m_con;
	cmdUpdateNote->Connection = m_con;
	cmdDelNote->Connection = m_con;
	cmdDelNtHeader->Connection = m_con;
	cmdBatchDelNote->Connection = m_con;
	cmdBatchUpdateNote->Connection = m_con;
	cmdResetNtHeader->Connection = m_con;
	dsetSupplier->Connection = m_con;
	dsetStaff->Connection = m_con;
	adospupdatewsaleprice->Connection = m_con;
	adospcopy->Connection = m_con;
	spsave->Connection = m_con;
	querydan->Connection = m_con;
	sptuihuo->Connection = m_con;
	GetBkStackInfo();
	query->Connection = m_con;
	qudetail->Connection = m_con;
	qrystorge->Connection = m_con;
	dsetSupplier->Active = true;
	dsetStaff->Active = true;
	dblkpcbbSupplierID->KeyValue = 0;
	adoGetHeadTotal->Connection= m_con;
	dssetStkAmount->Connection= m_con;
	AnsiString sql;
	sql = "SELECT NAME,value,bk FROM SYS_BSSET WHERE NAME IN('rkusetuihuo','storageday','xiaoshudian','rktuihuoguanli', ";
	sql = sql+ " 'changeDanHaoDisplay','rkallsupplier','rkusefind','rkusedelete','rkusechange','storagesametishi','storageday')";
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

	//�˻������Ƿ�����



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

	cbstorgename->Text = qrystorge->FieldByName("Name")->AsAnsiString ;
	edStoryNum->Text = IntToStr(m_storageID);

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

	//��ӡ��Ϣ
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



	//�˻����
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
	//���й�Ӧ����ʷ��ϸ
	GetSet->GetSetInfo("rkallsupplier");
	  allsupplier = GetSet->ValueBool;


	//�鵥�����Ƿ�����
	  GetSet->GetSetInfo("rkusefind");
	   findpassword = GetSet->ValueBool;


	//ɾ�������Ƿ�����
		 GetSet->GetSetInfo("rkusedelete");
		  deletepassword = GetSet->ValueBool;



	//�޸ĵ�ͷ�����Ƿ�����
		  GetSet->GetSetInfo("rkusechange");
		 changepassword  = GetSet->ValueBool;


	//�ظ���ʾ
		  GetSet->GetSetInfo("storagesametishi");
		  sameid   = GetSet->ValueBool;

         delete GetSet;
	RzToolButton5Click(BtnNew);
	ChangeOpmode(OPAddNtHeader);
	FormView();
}
//---------------------------------------------------------------------------
void TfrmStorageReturnMng1::GetBkStackInfo()
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
void TfrmStorageReturnMng1::ChangeCatalogSearchMode()
{
		 //
}

void TfrmStorageReturnMng1::ChangeBsmode(BSMode bsmode)
{
//
}

void TfrmStorageReturnMng1::ChangeOpmode(OPMode opmode)
{
	//if (opmode == m_opmode
	//	&& (opmode == OPDelNtHeader))
	//	return;

	//1Ϊ�鵥ģʽ 2Ϊ��ӵ�ͷģʽ 3Ϊɾ����ͷģʽ 4Ϊ��ӵ�ģʽ 5Ϊɾ����ģʽ 6Ϊͳһģʽ 7Ϊ�ֳ��տ�ģʽ
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

			Tfrmcaigouquery* frm = new Tfrmcaigouquery(Application,m_con,m_storageID,2,1);
			if (frm->ShowModal() == mrOk)
			{
				AnsiString sql;
				sql = " select * from CUST_CustomerInfo where Type =1 order by name ";
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
			//����ϴ������ģʽ������û�мӽ��κ����ݣ��������
			if (m_opmode == OPAddNtHeader &&
				dsetNote->Active && dsetNote->RecordCount < 1)
				return;

			if (m_opmode == OPDelNote      //�ϴ���ɾ��ģʽ�������������ݶ�ɾ��
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
				if (MessageBoxA(0,"�Ƿ�Ҫɾ���õ�?","ѯ��",MB_ICONQUESTION|MB_OKCANCEL)!=1 )
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
			if (MessageBoxA(0,"ȷ��Ҫɾ���ü�¼��?","ѯ��",MB_ICONQUESTION|MB_OKCANCEL)==1 )
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
			//ͳһģʽ
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
		//�ֳ�����ģʽ
		if (editdanhao->Text == "") {
			return;
		}
		if (!SaveStorage(1))
		{
			return;
		}
        if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
		{
			//���Ȱ��޸ĵĸ���һ�¹�
			dbgrdNote->SetFocus();
			//��ΰ���������ˢ��һ�¹�
			QryNtHeader();

			AnsiString sql;
			sql = " select datediff(day,getdate(),HdTime) as day from BS_StorageNoteHeader where id = " +  dsetNtHeader->FieldByName("ID")->AsAnsiString;
			query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->Open();
			if (query->FieldByName("day")->AsInteger != 0 ) {
				MessageBox(0,"�ֳ�����ֻ�ܸ����յģ�","����˻���" ,MB_OK);
				return;
			}

			/*if (StrToDate(dsetNtHeader->FieldByName("HdTime")->AsAnsiString ) != Date()  ) {
				MessageBox(0,"�ֳ�����ֻ�ܸ����յģ�","����˻���" ,MB_OK);
				return;
			} */
			TfrmRecMoney* frm = new TfrmRecMoney(this);
			frm->SetDiscountedPrice(dsetNtHeader->FieldByName("TotalDiscountedPrice")->AsFloat);
			frm->SetChecked(dsetNtHeader->FieldByName("Checked")->AsFloat);
			if (mrOk == frm->ShowModal())
			{
				if (frm->numedtUnchecked ->Value > 0) {
					if (MessageBox(0,"�㻹��δ�����Ƿ������","�ֳ�����",MB_ICONQUESTION|MB_OKCANCEL)!=1) {
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
				sql = "insert into FN_CUSEndMoneyDocuments (MoneyCode,date,state,type,userid,CustmerName,ClearingType,Clearingstyle,stgid) values ("+Code+",getdate(),1,1," + IntToStr(m_userID) +",'" + dblkpcbbSupplierID->Text + "','�ֳ�����','�ֽ�'," + IntToStr(m_storageID) + ")";
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

void TfrmStorageReturnMng1::AddNtHeader()//��ӵ�ͷ
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
		//LockWindowUpdate(dbgrdNote->Handle);//����ָ�����ڣ���ֹ�����¡�
		QryNtHeader(id);
	}
	__finally
	{
		//LockWindowUpdate(NULL);
	}
}

void TfrmStorageReturnMng1::QryNtHeader(String code, bool qrybkstack)//��ѯ��ͷ
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

		GetHtHeaderTotal();//ͳ��������
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
		//ShowMessage("�õ������ڣ�");
	}
}

void TfrmStorageReturnMng1::QryNtHeader(bool qrybkstack)//��ѯ��ͷ
{
	//�����ѯ֮ǰ�ĵ�ǰ���¼ID
	int noteID = 0;
	if (dsetNote->Active && dsetNote->RecordCount >= 1)
	{
        noteID = dsetNote->FieldByName("ID")->AsInteger;
	}
	//��ѯ��ͷ
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
			if (noteID > 0)//����ǰ��¼��ID���µ�����noteID
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

			GetHtHeaderTotal();//ͳ��������
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
            //ShowMessage("�õ������ڣ�");
		}
	}
}

void TfrmStorageReturnMng1::QryNtHeader(int id, bool qrybkstack)//��ѯ��ͷ
{
	//��ѯ��ͷ
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
		GetHtHeaderTotal();//ͳ��������
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
    	//ShowMessage("�õ������ڣ�");
    }
}

void TfrmStorageReturnMng1::DelNtHeader()//ɾ����ͷ
{
//iu
}

void TfrmStorageReturnMng1::UpdateNtHeader()//���µ�ͷ
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
			dsetNtHeader->FieldByName("SupplierID")->AsInteger;
		cmdUpdateNtHeader->Parameters->ParamByName("@Bsmode")->Value = 1;
		cmdUpdateNtHeader->Execute();
		try
		{
			//LockWindowUpdate(dbgrdNote->Handle);//����ָ�����ڣ���ֹ�����¡�
			QryNtHeader();
		}
		__finally
		{
			//LockWindowUpdate(NULL);
		}
	}
}

bool TfrmStorageReturnMng1::AddNote(int supplierID, int catalogID)//��ӵ�
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
					msg = "����޸���,���֤���˻���";
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
					msg = "�����ڹ�Ӧ�̣�" + msg + "���п��,���֤���˻���";
				}

				MessageBox(0,msg.c_str() ,"��ʾ",MB_ICONEXCLAMATION);
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

		if (ret > 0)//����ɹ�
		{
			//int bkinfoid = dsetNote->FieldByName("BkInfoID")->AsInteger;
			try
			{
				//LockWindowUpdate(dbgrdNote->Handle);//����ָ�����ڣ���ֹ�����¡�
				QryNtHeader(dsetNtHeader->FieldByName("ID")->AsInteger, true);
				//((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00%";
				//((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "��###,###,##0.00";
				//((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = "��###,###,##0.00";
				//((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = "��###,###,##0.00";
			}
			__finally
			{
				//LockWindowUpdate(NULL);
			}
			//��ʾ������ͬ��Ŀ;
			//ShowMessage(dsetNote->Lookup("BkInfoID", bkinfoid, "BkInfoID").VInteger);
			result = true;
		}
		else if (ret == 0)//���޴���
		{

		}
		else if (ret == -1)//��������
		{

		}
		else 	if (ret == -2) {
			if (sameid) {
				MessageBox(0,"���������ͬĿ¼����!","��ʾ",MB_ICONEXCLAMATION);
			}
            result = true;
		}
	}
	return result;
}

bool TfrmStorageReturnMng1::AddNote(int id)
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
					msg = "�����޽�����¼,���֤���˻���";
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
					msg = "�����ڹ�Ӧ�̣�" + msg + "������,���֤���˻���";
				}

				MessageBox(0,msg.c_str(),"��ʾ",MB_ICONEXCLAMATION);
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
		if (ret > 0)//����ɹ�
		{
			//int bkinfoid = dsetNote->FieldByName("BkInfoID")->AsInteger;
			try
			{
				//LockWindowUpdate(dbgrdNote->Handle);//����ָ�����ڣ���ֹ�����¡�
				//QryNtHeader(dsetNtHeader->FieldByName("ID")->AsInteger, true);
				//((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00%";
				//((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "��###,###,##0.00";
				//((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = "��###,###,##0.00";
				//((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = "��###,###,##0.00";
			}
			__finally
			{
				//LockWindowUpdate(NULL);
			}
			//��ʾ������ͬ��Ŀ;
			//ShowMessage(dsetNote->Lookup("BkInfoID", bkinfoid, "BkInfoID").VInteger);
			result = true;
		}
		else if (ret == 0)//���޴���
		{

		}
		else if (ret == -1)//��������
		{

		}
		else if (ret == -2) {
			MessageBox(0,"���������ͬĿ¼����!","��ʾ",MB_ICONEXCLAMATION);
            result = true;
		}
	}
	return result;
}


void TfrmStorageReturnMng1::UpdateNote()//���µ�
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
			//LockWindowUpdate(dbgrdNote->Handle);//����ָ�����ڣ���ֹ�����¡�
		 //	QryNtHeader();      ���²�ѯ��ͷ


			//((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00";
			//((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "��###,###,##0.00";
			//((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = "��###,###,##0.00";
			//((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = "��###,###,##0.00";
		}
		__finally
		{
			//LockWindowUpdate(NULL);
		}
	}
}


void TfrmStorageReturnMng1::UpdateNote1()//���µ�
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


void TfrmStorageReturnMng1::DelNote()//ɾ����
{
	if (dsetNote->Active && dsetNote->RecordCount >= 1)
	{
		if (dbgrdNote->SelectedRows->Count == 0)
		{
			cmdDelNote->Parameters->ParamByName("@ID")->Value
				= dsetNote->FieldByName("ID")->AsInteger;
			cmdDelNote->Parameters->ParamByName("@Bsmode")->Value = 1;
			if (ChangeDisplay) {
				logmessage = "ɾ������˻���" + dsetNtHeader->FieldByName("StgNtCodeStr")->AsAnsiString ;
			}
			else
			{
				logmessage = "ɾ������˻���" + dsetNtHeader->FieldByName("StgNtCode")->AsAnsiString ;
			}
			logmessage = logmessage + "����Ŀ��" + dsetNote->FieldByName("CatalogName")->AsAnsiString + "��";
			AddEvent(1,"һ������˻�����",m_userID,m_storageID,logmessage,linfo.con);
			cmdDelNote->Execute();
			try
			{
				//LockWindowUpdate(dbgrdNote->Handle);//����ָ�����ڣ���ֹ�����¡�
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
				logmessage = "ɾ������˻���" + dsetNtHeader->FieldByName("StgNtCodeStr")->AsAnsiString ;
			}
			else
			{
				logmessage = "ɾ������˻���" + dsetNtHeader->FieldByName("StgNtCode")->AsAnsiString ;
			}
			logmessage = logmessage + "����Ŀ��" + dsetNote->FieldByName("CatalogName")->AsAnsiString + "��";
			AddEvent(1,"һ������˻�����",m_userID,m_storageID,logmessage,linfo.con);
			for (int i=1; i < dbgrdNote->SelectedRows->Count; i++)
			{
				dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[i];
				ids = ids + "," + dsetNote->FieldByName("ID")->AsString;
				if (ChangeDisplay) {
					logmessage = "ɾ������˻���" + dsetNtHeader->FieldByName("StgNtCodeStr")->AsAnsiString ;
				}
				else
				{
					logmessage = "ɾ������˻���" + dsetNtHeader->FieldByName("StgNtCode")->AsAnsiString ;
				}
				logmessage = logmessage + "����Ŀ��" + dsetNote->FieldByName("CatalogName")->AsAnsiString + "��";
				AddEvent(1,"һ������˻�����",m_userID,m_storageID,logmessage,linfo.con);
			}
			cmdBatchDelNote->Parameters->ParamByName("@IDS")->Value = ids;
			cmdBatchDelNote->Parameters->ParamByName("@Bsmode")->Value = 1;
			cmdBatchDelNote->Execute();
			try
			{
				//LockWindowUpdate(dbgrdNote->Handle);//����ָ�����ڣ���ֹ�����¡�
				QryNtHeader();
			}
			__finally
			{
				//LockWindowUpdate(NULL);
			}
		}
	}
}

void TfrmStorageReturnMng1::BatchSetNotes(int amount, float discount, int mode)
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
						//MessageBox(0,"�˻��������������������","��ʾ" ,MB_OK);
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
						//MessageBox(0,"�˻��������������������","��ʾ" ,MB_OK);
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
							//MessageBox(0,"�˻��������������������","��ʾ" ,MB_OK);
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
			case 1://���߾�����
				cmdBatchUpdateNote->Parameters->ParamByName("@IDS")->Value = ids;
				cmdBatchUpdateNote->Parameters->ParamByName("@Amount")->Value = amount;
				cmdBatchUpdateNote->Parameters->ParamByName("@Discount")->Value = discount;
				cmdBatchUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 1;
				cmdBatchUpdateNote->Execute();
				try
				{
					//LockWindowUpdate(dbgrdNote->Handle);//����ָ�����ڣ���ֹ�����¡�
					QryNtHeader();
				}
				__finally
				{
					//LockWindowUpdate(NULL);
				}
				break;
			case 2://ֻ����Amount
				cmdBatchUpdateNote->Parameters->ParamByName("@IDS")->Value = ids;
				cmdBatchUpdateNote->Parameters->ParamByName("@Amount")->Value = amount;
				cmdBatchUpdateNote->Parameters->ParamByName("@Discount")->Value = "";
				cmdBatchUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 1;
				cmdBatchUpdateNote->Execute();
				try
				{
					//LockWindowUpdate(dbgrdNote->Handle);//����ָ�����ڣ���ֹ�����¡�
					QryNtHeader();
				}
				__finally
				{
					//LockWindowUpdate(NULL);
				}
				break;
			case 3://ֻ����Discount
				cmdBatchUpdateNote->Parameters->ParamByName("@IDS")->Value = ids;
				cmdBatchUpdateNote->Parameters->ParamByName("@Discount")->Value = discount;
				cmdBatchUpdateNote->Parameters->ParamByName("@Amount")->Value = "";
				cmdBatchUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 1;
				cmdBatchUpdateNote->Execute();
				try
				{
					//LockWindowUpdate(dbgrdNote->Handle);//����ָ�����ڣ���ֹ�����¡�
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

void __fastcall TfrmStorageReturnMng1::edtQrySupplierKeyPress(TObject *Sender, wchar_t &Key)
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
		sql = " select * from CUST_CustomerInfo where Type =1 and Name like '%"+ edtQrySupplier->Text.Trim() + "%' order by name";
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

void __fastcall TfrmStorageReturnMng1::dblkpcbbStaffIDKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r')
	{
		Key = 0;
		Perform(WM_NEXTDLGCTL, 0, 0);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng1::edtCatalogKeyPress(TObject *Sender, wchar_t &Key)
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
			MessageBox(0,"���ȱ�������˻�����","����˻�" ,MB_ICONEXCLAMATION);
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
					MessageBox(0,"��������ȷ�Ķ��ۣ�","����˻�" ,MB_ICONEXCLAMATION);
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
					if (lbcaption->Caption == "����˻���") {
					//frm->Supplier   = dblkpcbbSupplierID->Text  ;
					}
					frm->m_supplierID = dsetNtHeader->FieldByName("SupplierID")->AsInteger ;
					frm->SetSearchMode(m_catalogSearchMode, edtCatalog->Text);
					frm->DoModalType = 8;
					//frm->StorageReturnfrm = this;
                                         frm->SelectAll = false;
                                        frm->QryBkInfo();
                                          if (frm->findbooks == 3) {   //�ҵ�������¼
                                          results= frm->ShowModal();
                                        }else if (frm->findbooks==1) {  //ֻ�ҵ�һ�����Ͳ���ʾѡ�񴰿���
                                          results = 1;
                                        }else if ((frm->findbooks==0)||(frm->findbooks==-1)) {  //û���ҵ��򶼳���
                                          results = -1 ;
                                        }

				if (mrOk == results)
				{
				   int bkinfoid = -1,catalogID = -1;
				   frm->GetSelectResult(bkinfoid,catalogID);
					 //supplierID = dsetSupplier->FieldByName("ID")->AsInteger ;
					 if (frm->SelectAll) {                           //ȫѡ
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
								if ( !dsetNote->Locate("BkcatalogID",str,Opts)){
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
									if (sameid) {
										MessageBox(0,"����ͬ��¼���ʵ��","��ʾ" ,MB_ICONEXCLAMATION);
									}
									dbgrdNote->SelectedRows->CurrentRowSelected = true;
									dbgrdNote->SetFocus();
									dbnbedtAmount->SetFocus();
								}

								   //	MessageBox(0,"����޸���!","��ⵥ",MB_ICONEXCLAMATION);
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
void __fastcall TfrmStorageReturnMng1::dbedtSupplySNKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r')
	{
		Key = 0;
		dbnbedtAddCosts->SetFocus();
		//Perform(WM_NEXTDLGCTL, 0, 0);
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmStorageReturnMng1::dbnbedtAmountKeyPress(TObject *Sender, wchar_t &Key)
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

void TfrmStorageReturnMng1::DelInvalidNtHeader()
{
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1
		&& dsetNote->Active && dsetNote->RecordCount < 1 && dsetNtHeader->FieldByName("StgNtCode")->AsInteger  == 0)
	{
    	DelNtHeader();
	}
}

void __fastcall TfrmStorageReturnMng1::FormClose(TObject *Sender, TCloseAction &Action)
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

void __fastcall TfrmStorageReturnMng1::RzToolButton9Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng1::RzToolButton8Click(TObject *Sender)
{
	//��ӡ
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
		/*if (lbcaption->Caption == "��ⵥ")
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

void __fastcall TfrmStorageReturnMng1::dblkpcbbSupplierIDExit(TObject *Sender)
{
	//
	//UpdateNtHeader();
	//dblkpcbbSupplierID->Enabled = sbnewcustomer->Enabled;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng1::RzToolButton6Click(TObject *Sender)
{
	//Excel����
	if (!SaveStorage(1))
	{
		return;
	}
	if (dsetNote->Active && dsetNote->RecordCount >= 1)
	{
		DbgridToExcel(dbgrdNote);
	}
}
bool __fastcall TfrmStorageReturnMng1::DbgridToExcel(TRzDBGrid* dbg)
{
	AnsiString temptext,path  ;
	int k = dbg->DataSource ->DataSet ->RecordCount ,n=0;

	savedlg->FileName = StringReplace(dblkpcbbSupplierID->Text.Trim()+editdanhao->Text.Trim() ,"\\","-",TReplaceFlags()<<rfReplaceAll)+ "����˻���";
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

	/*if(k == 0)
	{
		MessageBox(0,"û�����ݣ�","����ȷ��" ,MB_OK);
		return false;
	}
	Variant     v;
	v   =Variant::CreateObject("Excel.Application");
	v.OlePropertySet("Visible",true);
	v.OlePropertyGet("WorkBooks").OleFunction("Add");
//  ��Excel�г��ַ�����ʾ
	temptext = "'"+ lbcaption->Caption;
	v.OlePropertyGet("Cells",1,5).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",3,1).OlePropertySet("Value","��λ" );
	temptext = "'"+ dblkpcbbSupplierID->Text;
	v.OlePropertyGet("Cells",3,2).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",3,4).OlePropertySet("Value","����" );
	temptext = "'"+ DateToStr(dbdtedtHdTime->Date);
	v.OlePropertyGet("Cells",3,5).OlePropertySet("Value",temptext .c_str());
	v.OlePropertyGet("Cells",3,7).OlePropertySet("Value","����");
	if (ChangeDisplay) {
		temptext = "'"+ editdanhao->Text;
	}
	else
	{
		temptext = "'"+ dbedtStgNtCode->Text;
	}
	v.OlePropertyGet("Cells",3,8).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",4,1).OlePropertySet("Value","�������" );
	temptext = "'"+ dbedtSupplySN->Text;
	v.OlePropertyGet("Cells",4,2).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",4,4).OlePropertySet("Value","�ɹ�Ա" );
  //	temptext = "'"+ cbstaff->Text;
	v.OlePropertyGet("Cells",4,5).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",4,4).OlePropertySet("Value","���ӷ���" );
	temptext = "'"+ dbnbedtAddCosts->Text;
	v.OlePropertyGet("Cells",4,5).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",5,1).OlePropertySet("Value","��ע" );
	temptext = "'"+ dbedtRemarks->Text;
	v.OlePropertyGet("Cells",5,2).OlePropertySet("Value",temptext .c_str() );
	*/
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
				/*else if (dbg->Columns ->Items [j-1]->FieldName == "CatalogName") {
                	AnsiString bookname;
					int len;
					bookname = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					bookname = StringReplace(bookname , ",",".",TReplaceFlags()<<rfReplaceAll);
					temptext = temptext + bookname + ",";
				}*/
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

	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",n+1,1),vSheet.OlePropertyGet("Cells",t2+n+2,t1)); //ȡ�úϲ�������
	R.OlePropertyGet("Borders",2).OlePropertySet("linestyle",1);
	R.OlePropertyGet("Borders",4).OlePropertySet("linestyle",1);


	v.OlePropertyGet("Cells",t2+2+n,1).OlePropertySet("Value","�ϼ�");
	temptext = RzDBNumericEdit2->Text ;
	v.OlePropertyGet("Cells",t2+2+n,9).OlePropertySet("Value",temptext .c_str() );
	temptext = RzDBNumericEdit3->Text ;
	v.OlePropertyGet("Cells",t2+2+n,11).OlePropertySet("Value",temptext .c_str() );
	temptext = RzDBNumericEdit4->Text ;
	v.OlePropertyGet("Cells",t2+2+n,12).OlePropertySet("Value",temptext .c_str() );
	dbg->DataSource ->DataSet->EnableControls();

    try {
		xWorkbook.OleFunction("SaveAs",path.c_str());
	} catch (Exception &E) {
		//ShowMessage(E.Message);
	}

	/*AnsiString rkamount,mayang,shiyang;
	mayang =  RzDBNumericEdit3->Text;
	shiyang = RzDBNumericEdit4->Text;
	rkamount = RzDBNumericEdit2->Text ;
	mayang = StringReplace(mayang , ",","",TReplaceFlags()<<rfReplaceAll);
	shiyang = StringReplace(shiyang , ",","",TReplaceFlags()<<rfReplaceAll);
	rkamount = StringReplace(rkamount , ",","",TReplaceFlags()<<rfReplaceAll);
	temptext = "\n";
	temptext = temptext + "�ϼ�,,,,,,,," + rkamount + ",,'" + mayang + ",'" + shiyang ;

	iFileLength   =   FileSeek(iFileHandle,0,2);
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	FileClose(iFileHandle);

	MessageBox(0,"������ϣ�","��ʾ" ,MB_OK);  */
	return false;
}

//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng1::dbnbedtAmountExit(TObject *Sender)
{
	if ((dsetNote->IsEmpty()) || (dsetNote->RecordCount==0)) {
		return;
	}
	if (rktuihuoguanli) {
		AnsiString sql;
		sql = "select sum(amount) as amount from BS_StorageNote where bkinfoid = " + dsetNote->FieldByName("BkInfoID")->AsString ;
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->Open();
		if (dbnbedtAmount->IntValue > query->FieldByName("amount")->AsInteger - dsetNote->FieldByName("Amount")->AsInteger ) {
			MessageBox(0,"�˻��������ڸù�Ӧ�̿���������","��ʾ" ,MB_OK|MB_ICONWARNING);
			dbnbedtAmount->SetFocus();
			return;
		}
		if (dbnbedtAmount->IntValue > RzDBNumericEdit1->IntValue - dsetNote->FieldByName("Amount")->AsInteger ) {
			MessageBox(0,"�˻��������ڸù�Ӧ�̿��������","��ʾ" ,MB_OK|MB_ICONWARNING);
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
	//������dataset�󣬲Ÿ������ݿ�
	UpdateNote();
	tuihuolv();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng1::mniBsNoteSendbackClick(TObject *Sender)
{
	TMenuItem* mi = dynamic_cast<TMenuItem*>(Sender);
	if (mi != NULL)
	{
		if (mi->Tag == BSNoteSendback && !CheckOperateAuthority())
			return;

		if (mi->Tag == 2) {
			lbcaption->Caption  = "����˻���";
		} else if (mi->Tag == 1) {
              lbcaption->Caption  = "��ⵥ";
			   }
		ChangeBsmode(mi->Tag);

	  RzToolButton5Click(BtnNew);

	}
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


void TfrmStorageReturnMng1::QryBkstack()
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
	//��ݼ�

}

void TfrmStorageReturnMng::ResetNtHeader()
{
	//���õ�ͷ
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
			//LockWindowUpdate(dbgrdNote->Handle);//����ָ�����ڣ���ֹ�����¡�
			QryNtHeader();
		}
		__finally
		{
			//LockWindowUpdate(NULL);
		}
	}
}  */
void __fastcall TfrmStorageReturnMng1::sbnewcustomerClick(TObject *Sender)
{
	//����¹�Ӧ��
	String ID;
	ID = "";

   dsetSupplier->Active = false;
   dsetSupplier->CommandText = "select ID, Name from CUST_CustomerInfo where Type=1";
   dsetSupplier->Active = true;

	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1
		&& dsetNote->Active && dsetNote->RecordCount >= 1)//��ʱ�����޸Ĺ�Ӧ��
	{

	}
	else if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1
		&& dsetNote->Active && dsetNote->RecordCount < 1)//�����޸Ĺ�Ӧ��
	{

		int count1 = dsetSupplier->RecordCount;
		TDetaileForm * frm = new TDetaileForm(m_app,1,1,ID.c_str() ,m_con);
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



void __fastcall TfrmStorageReturnMng1::BtnViewClick(TObject *Sender)
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

void __fastcall TfrmStorageReturnMng1::lblCatalogMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	if (Button == mbLeft ) {
		TPoint  pt;
		GetCursorPos(&pt);
		PM->Popup(pt.x,pt.y);

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng1::N1Click(TObject *Sender)
{
   	lblCatalog->Caption = "���";
	m_catalogSearchMode = 1;
	edtCatalog->MaxLength = 15;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng1::N2Click(TObject *Sender)
{
	lblCatalog->Caption = "�Ա���";
	m_catalogSearchMode = 2;
	edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng1::N3Click(TObject *Sender)
{
	lblCatalog->Caption = "����";
	m_catalogSearchMode  = 3;
	edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng1::BtnClearClick(TObject *Sender)
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
		 frm->PrintStorageExe(1);
		/*if (lbcaption->Caption == "��ⵥ")
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

void __fastcall TfrmStorageReturnMng1::RzToolButton3Click(TObject *Sender)
{
	TControl* con = dynamic_cast<TControl*>(Sender);
	if (con != NULL)
	{
		dbgrdNote->SetFocus();
		ChangeOpmode(con->Tag);
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmStorageReturnMng1::RzToolButton5Click(TObject *Sender)
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

void __fastcall TfrmStorageReturnMng1::RzToolButton2Click(TObject *Sender)
{
	TControl* con = dynamic_cast<TControl*>(Sender);
	if (con != NULL)
	{
		dbgrdNote->SetFocus();
		ChangeOpmode(con->Tag);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng1::dblkpcbbSupplierIDKeyPress(TObject *Sender, wchar_t &Key)

{
   if (Key == VK_RETURN) {
		if (dblkpcbbSupplierID->Text == "") {
			MessageBox(0,"��ѡ��Ӧ�̣�","��ʾ" ,MB_OK);
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
			}*/
			supplierDI = dsetSupplier->FieldByName("ID")->AsInteger;
			UpdateNtHeader();
			sbnewcustomer->Enabled = false;
			dblkpcbbSupplierID->Enabled = false;
			//dbedtSupplySN->SetFocus();
			edtCatalog->Text = "";
			dbnbedtAmount->Value = 0;
			dbnbedtDiscount->Value = 100.00;
			dbnbedt1->Value = 0;
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00";
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "0.00";
			BtnSave->Click();
	   }
   }
}
//---------------------------------------------------------------------------

void  TfrmStorageReturnMng1::FindNote(String code)
{
	DelInvalidNtHeader();
	edtCatalog->Text = "";
	edtQrySupplier->Text = "";
	dblkpcbbSupplierID->Enabled  = false;
	try
	{
		//LockWindowUpdate(dbgrdNote->Handle);//����ָ�����ڣ���ֹ�����¡�
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

void __fastcall TfrmStorageReturnMng1::dbgrdNoteDblClick(TObject *Sender)
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
				lbcaption->Caption = "����˻���";
			}
			dsetNote->AfterScroll = dsetNoteAfterScroll;
		}
		catch(...)
		{
			//ShowMessage("�õ������ڣ�");
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

void __fastcall TfrmStorageReturnMng1::dbgrdNoteCellClick(TColumn *Column)
{

	/*if (dsetNote->IsEmpty()) {
		return;
	}
	editshun->Text = dsetNote->FieldByName("harmnum")->AsAnsiString ;
	//delete aq;
	historyview();*/
}
//---------------------------------------------------------------------------
 void TfrmStorageReturnMng1::GetHtHeaderTotal()
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
void TfrmStorageReturnMng1::historyview()
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
		sql = sql + "' and BS_StorageNoteHeader.StgID = " + edStoryNum->Text ;
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

		 //���������ۿۿ�����ʾѡ �е���

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

void __fastcall TfrmStorageReturnMng1::N5Click(TObject *Sender)
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

void __fastcall TfrmStorageReturnMng1::N6Click(TObject *Sender)
{
	lblCatalog->Caption = "����";
	m_catalogSearchMode  = 6;
	edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng1::BtnNewClick(TObject *Sender)
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
	sql = " select * from CUST_CustomerInfo where Type =1 order by name ";
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


void  TfrmStorageReturnMng1::ModifyEnable()
{
	if (m_opmode == OPFind) {
		dbnbedtAmount->Enabled = false;
		dbnbedtDiscount->Enabled = false;
		cbbkstackID->Enabled = false;
		if (dsetNote->FieldByName("amount")->AsInteger < 0 ) {
			lbcaption->Caption = "����˻���";
		}
		else
		{
			lbcaption->Caption = "��ⵥ";
		}
	}
	else
	{
        lbcaption->Caption = "����˻���";
		dbnbedtAmount->Enabled = true;
		dbnbedtDiscount->Enabled = true;
		cbbkstackID->Enabled = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng1::BtnChangeOptionsClick(TObject *Sender)
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

void __fastcall TfrmStorageReturnMng1::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
    if (Key == VK_F1)  //�鵥
	{
		if (!BtnView->Enabled ) {
			return;
		}
		BtnView->Click();
	}
	if (Key == VK_F2) {   //����
		if (!BtnNew->Enabled ) {
			return;
		}
		BtnNew->Click();
	}
	if (Key == VK_F3) {   //����
		if (!BtnSave->Enabled ) {
			return;
		}
		BtnSave->Click();
	}
	if (Key == VK_F4) {   //�޸ĵ�ͷ
		if (!BtnChangeOptions->Enabled ) {
			return;
		}
		BtnChangeOptions->Click();
	}
	if (Key == VK_F5) {   //ɾ��
		if (!RzToolButton2->Enabled ) {
			return;
		}
		RzToolButton2->Click();
	}
	if (Key == VK_F6) {   //ͳһ
		if (!RzToolButton3->Enabled ) {
			return;
		}
		RzToolButton3->Click();
	}
	if (Key == VK_F7) {   //�ֳ�����
		if (!BtnReminder->Enabled ) {
			return;
		}
		BtnReminder->Click();
	}
	if (Key == VK_F8) {   //����
		if (!RzToolButton6->Enabled ) {
			return;
		}
		RzToolButton6->Click();
	}
	if (Key == VK_F9) {   //ɾ��
		if (!RzToolButton5->Enabled ) {
			return;
		}
		RzToolButton5->Click();
	}
	if (Key == VK_F10) {   //��ӡ
		if (!RzToolButton8->Enabled ) {
			return;
		}
		RzToolButton8->Click();
	}
	if (Key == VK_F11) {   //Ԥ��
    	if (!BtnClear->Enabled ) {
			return;
		}
		BtnClear->Click();
	}
	if (Shift.Contains(ssAlt)&& Key == 67) {    //��λ
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
void TfrmStorageReturnMng1::changeInputMode()
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

void __fastcall TfrmStorageReturnMng1::N8Click(TObject *Sender)
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

void __fastcall TfrmStorageReturnMng1::dbgrdNoteMouseUp(TObject *Sender, TMouseButton Button,
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

void __fastcall TfrmStorageReturnMng1::N9Click(TObject *Sender)
{
    if (BtnSave->Enabled) {
		MessageBoxA(0,"������δ���棬���ȱ��棡","��ʾ",MB_ICONASTERISK);
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
		MessageBoxA(0,"��ȷ������������ͬ��ͬ��Ӧ�̵����ݣ�","��ʾ",MB_ICONASTERISK);
		return;
	}
	else
	{
		QryNtHeader(dsetNtHeader->FieldByName("ID")->AsInteger, true);
	}

	Screen->Cursor = crDefault ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng1::BtnView1Click(TObject *Sender)
{
	Tfrmbookquery * frm = new Tfrmbookquery(Application,linfo.con,linfo.storageID);
	frm->ShowModal();
	delete frm;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng1::BtnSaveClick(TObject *Sender)
{
	if (!SaveOK()) {
        return;
	}
	edtCatalog->SetFocus();
}
//---------------------------------------------------------------------------

bool TfrmStorageReturnMng1::SaveOK()
{
  if (dsetNote->RecordCount > 0) {
  	if (dsetSupplier->FieldByName("ID")->AsInteger != beforesupplier) {
		ChangeSupplier();
		if (ChangeDisplay) {
			logmessage = "������˻���" + dsetNtHeader->FieldByName("StgNtCodeStr")->AsAnsiString ;
		}
		else
		{
			logmessage = "������˻���" + dsetNtHeader->FieldByName("StgNtCode")->AsAnsiString ;
		}
		logmessage = logmessage + "�Ĺ�Ӧ����" + beforesuppliername + "�޸�Ϊ" + dsetSupplier->FieldByName("Name")->AsAnsiString;
		AddEvent(1,"һ������˻�����",m_userID,m_storageID,logmessage,linfo.con);
		beforesupplier = dsetSupplier->FieldByName("ID")->AsInteger;
		UpdateNtHeader();
	}
		SaveOrNot = true;
		BtnSave->Enabled = false;
		dbnbedtAddCosts->Enabled = false;
		//dbedtSupplySN->Enabled = false;
		dblkpcbbSupplierID->Enabled = false;
		sbnewcustomer->Enabled = false;
		return true;
	}
	else if (dsetNote->IsEmpty() && dsetNtHeader->FieldByName("StgNtCode")->AsInteger  != 0  ) {
		UpdateNtHeader();
		SaveOrNot = true;
		BtnSave->Enabled = false;
		dbnbedtAddCosts->Enabled = false;
		//dbedtSupplySN->Enabled = false;
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
		logmessage = "�������˻���" + spsave->Parameters->ParamByName("@ReturnCode2")->Value ;
	}
	else
	{
		logmessage = "�������˻���" + spsave->Parameters->ParamByName("@ReturnCode")->Value ;
	}
	AddEvent(1,"һ������˻�����",m_userID,m_storageID,logmessage,linfo.con);
	historyview();     //SaveBenDan
	dbedtStgNtCode->Text = spsave->Parameters->ParamByName("@ReturnCode")->Value ;
	editdanhao->Text = spsave->Parameters->ParamByName("@ReturnCode2")->Value ;
	UpdateNtHeader();
	SaveOrNot = true;
	BtnSave->Enabled = false;
	dbnbedtAddCosts->Enabled = false;
  //dbedtSupplySN->Enabled = false;
	dblkpcbbSupplierID->Enabled = false;
	sbnewcustomer->Enabled = false;
	QryNtHeader();
  	return true;
}
//---------------------------------------------------------------------------

 bool TfrmStorageReturnMng1::SaveStorage(int mode)
{
	if (dsrcNote->DataSet == NULL) {
		return true;
	}
	if (dsetNote->IsEmpty() ) {
    	return true;
	}
	int recordRN = dbgrdNote->DataSource->DataSet->RecordCount;
	if ((!SaveOrNot)&& (recordRN != 0)) {                      //SaveBenDan
	if (mode == 1) {                      //��ӡ��Ԥ

		MessageBoxA(0,"������δ���棬���ȱ��棡","��ʾ",MB_ICONASTERISK);
		return false;

	}else
	{
		  if( MessageBoxA(0,"������δ���棬�Ƿ���Ҫ���棿","��ʾ",MB_ICONQUESTION||MB_YESNO)==1)
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


void __fastcall TfrmStorageReturnMng1::dbnbedtAddCostsExit(TObject *Sender)
{
	if (dsetNtHeader->RecordCount > 0) {
		AnsiString sql = "update BS_StorageNoteHeader set AddCosts = " + FloatToStr(abs(dsetNtHeader->FieldByName("AddCosts")->AsFloat))  + " where id = " + dsetNtHeader->FieldByName("id")->AsString ;
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->ExecSQL();
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmStorageReturnMng1::dbnbedtAddCostsKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		membk->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng1::BtnReminderClick(TObject *Sender)
{
	TControl* con = dynamic_cast<TControl*>(Sender);
	if (con != NULL)
	{
		dbgrdNote->SetFocus();
		ChangeOpmode(con->Tag);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng1::DBNavClick(TObject *Sender, TNavigateBtn Button)

{
	AnsiString code ;
   code = querydan->FieldByName("StgNtCode")->AsAnsiString ;
   editdanhao->Text = querydan->FieldByName("StgNtCodeStr")->AsAnsiString ;
	QryNtHeader(code,false);
}
//---------------------------------------------------------------------------
void TfrmStorageReturnMng1::ChangeSupplier()
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

void __fastcall TfrmStorageReturnMng1::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng1::dbgrdNoteTitleClick(TColumn *Column)
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

void TfrmStorageReturnMng1::FormView()
{
	AnsiString sql;
	sql = "select * from BS_SYS_Formview where stgid = " + IntToStr(m_storageID) + " and ParentID = 6";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	while (!query->Eof)
	{
		if (query->FieldByName("Name")->AsAnsiString == "�鵥" ) {
			BtnView->Visible = query->FieldByName("state")->AsBoolean ;
		}
		if (query->FieldByName("Name")->AsAnsiString == "����" ) {
			BtnNew->Visible = query->FieldByName("state")->AsBoolean ;
		}
		if (query->FieldByName("Name")->AsAnsiString == "����" ) {
			BtnSave->Visible = query->FieldByName("state")->AsBoolean ;
		}
		if (query->FieldByName("Name")->AsAnsiString == "�޸�" ) {
			BtnChangeOptions->Visible = query->FieldByName("state")->AsBoolean ;
		}
		if (query->FieldByName("Name")->AsAnsiString == "ɾ��" ) {
			RzToolButton5->Visible = query->FieldByName("state")->AsBoolean ;
		}
		if (query->FieldByName("Name")->AsAnsiString == "ɾ��" ) {
			RzToolButton2->Visible = query->FieldByName("state")->AsBoolean ;
		}
		if (query->FieldByName("Name")->AsAnsiString == "ͳһ" ) {
			RzToolButton3->Visible = query->FieldByName("state")->AsBoolean ;
		}
		if (query->FieldByName("Name")->AsAnsiString == "�ֳ�����" ) {
			BtnReminder->Visible = query->FieldByName("state")->AsBoolean ;
		}
		if (query->FieldByName("Name")->AsAnsiString == "Excel����" ) {
			RzToolButton6->Visible = query->FieldByName("state")->AsBoolean ;
		}
		if (query->FieldByName("Name")->AsAnsiString == "Ԥ��" ) {
			BtnClear->Visible = query->FieldByName("state")->AsBoolean ;
		}
		if (query->FieldByName("Name")->AsAnsiString == "��ӡ" ) {
			RzToolButton8->Visible = query->FieldByName("state")->AsBoolean ;
		}
		if (query->FieldByName("Name")->AsAnsiString == "����" ) {
			BtnView1->Visible = query->FieldByName("state")->AsBoolean ;
		}
		if (query->FieldByName("Name")->AsAnsiString == "��С��" ) {
			BtnAlignBottom->Visible = query->FieldByName("state")->AsBoolean ;
		}
		query->Next();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng1::dbnbedtDiscountKeyPress(TObject *Sender, wchar_t &Key)

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
void TfrmStorageReturnMng1::tuihuolv()
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

void __fastcall TfrmStorageReturnMng1::N10Click(TObject *Sender)
{
	lblCatalog->Caption = "����";
	m_catalogSearchMode  = 5;
	edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng1::editshunExit(TObject *Sender)
{
	 if (editshun->Text == "") {
		editshun->Text = "0";
	}
	UpdateWsaleDiscout(3);
	QryNtHeader();
}
//---------------------------------------------------------------------------
void TfrmStorageReturnMng1::UpdateWsaleDiscout(int mode)
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
void  TfrmStorageReturnMng1::operterview(int operterid)
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

void __fastcall TfrmStorageReturnMng1::editshunKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        edtCatalog->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng1::membkExit(TObject *Sender)
{
	if (dsetNtHeader->RecordCount > 0) {
		AnsiString sql = "update BS_StorageNoteHeader set Remarks = '" + membk->Text + "' where id = " + dsetNtHeader->FieldByName("id")->AsString ;
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->ExecSQL();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng1::membkKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r')
	{
	   edtCatalog->Text = "";
	   //edtCatalog->SetFocus();
	   dbnbedtAmount->Value = 0;
	   dbnbedtDiscount->Value = 100.00;
	   dbnbedt1->Value = 0;
	   ((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00";
	   ((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "0.00";
	   BtnSave->Click();
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmStorageReturnMng1::SpeedButton1Click(TObject *Sender)
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

void __fastcall TfrmStorageReturnMng1::chfsluruClick(TObject *Sender)
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

void __fastcall TfrmStorageReturnMng1::N11Click(TObject *Sender)
{
	if (dsetNote->IsEmpty() ) {
		return;
	}
	Tfrmbookhistory *frm = new Tfrmbookhistory(Application,m_con,m_storageID,dsetNote->FieldByName("BkcatalogID")->AsInteger );
	frm->ShowModal();
	delete frm;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng1::cbbkstackIDSelect(TObject *Sender)
{
	stackchange = true;
	UpdateNote();
	stackchange = false;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------


void __fastcall TfrmStorageReturnMng1::CheckBox1Click(TObject *Sender)
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

void __fastcall TfrmStorageReturnMng1::dsrcNoteDataChange(TObject *Sender, TField *Field)

{
	if (scroll == 1) {
		if (dsetNote->IsEmpty()) {
			editshun->Text = "0";
			dbnbedtAmount->IntValue = 0;
			dbnbedtDiscount->Value = 0.00;
			RzDBNumericEdit1->Text = "";
			dbnbedt1->Text = "";
        	scroll = 0;
			return;
		}
		editshun->Text = dsetNote->FieldByName("harmnum")->AsAnsiString ;
		historyview();
		scroll = 0;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageReturnMng1::dsetNoteBeforeScroll(TDataSet *DataSet)
{
	scroll = 1;
}
//---------------------------------------------------------------------------
bool TfrmStorageReturnMng1::SupplierCreit()
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

void __fastcall TfrmStorageReturnMng1::dblkpcbbSupplierIDClick(TObject *Sender)
{
	SupplierCreit();
}
//---------------------------------------------------------------------------

