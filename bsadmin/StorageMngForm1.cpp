//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "StorageMngForm1.h"
#include "GetBsset.h"
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
#include "NewBookinput1.h"
#include "NewBookModify.h"
#include "UnitExcelImport.h"
#include "SelectCatalogForm.h"
#include "bookQuery.h"
#include "RecMoneyForm.h"
#include "QueryDanHao.h"
#include "Addsyslog.h"
#include "Unitdistribute.h"
#include   <math.h>
#include "Unitcaigouquery.h"
#include "unitorder.h"
#include "unitinorderfenfa.h"
#include "bookhistory.h"
#include "RkFenfa.h"
#include "Unitprintbarcode.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "MDIChild"
#pragma link "RzCommon"
#pragma link "RzDBLook"
#pragma link "RzRadChk"
#pragma link "RzDTP"
#pragma link "RzDBDTP"
#pragma resource "*.dfm"
TfrmStorageMng1 *frmStorageMng1;
//---------------------------------------------------------------------------
__fastcall TfrmStorageMng1::TfrmStorageMng1(TComponent* Owner)
	: TfrmMDIChild(Owner)
	, m_catalogSearchMode(0)
	, m_bsmode(BSUnknown)
	, m_opmode(OPUnknown)
{
	m_module = MTStorageMng;
	m_catalogSearchMode = 1;
	this->WindowState = wsMaximized ;
	stackchange = false;
	blSelect = false;//shilf ��ѡ
	dtpbackdate->Date = Date();
}
//---------------------------------------------------------------------------
void TfrmStorageMng1::Init(LandInfo* li)
{
	TfrmMDIChild::Init(li);
	linfo.app = li->app ;
	linfo.con = li->con ;
	linfo.userID = li->userID ;
	linfo.UserName = li->UserName ;
	linfo.storageID = li->storageID ;
	linfo.FormatStr = li->FormatStr ;
	lblOpName->Caption = li->UserName;
	cmdAddNtHeader->Connection = m_con;
	spQryNtHeader->Connection = m_con;
	spQryNtHeader1->Connection = m_con;
	cmdUpdateNtHeader->Connection = m_con;
	cmdAddNote->Connection = m_con;
	cmdUpdateNote->Connection = m_con;
	adospcopy->Connection = m_con;
	cmdDelNote->Connection = m_con;
	cmdDelNtHeader->Connection = m_con;
	cmdBatchDelNote->Connection = m_con;
	cmdBatchUpdateNote->Connection = m_con;
	cmdResetNtHeader->Connection = m_con;
	dsetSupplier->Connection = m_con;
	dsetStaff->Connection = m_con;
	adospupdatewsaleprice->Connection = m_con;
	spsave->Connection = m_con;
	querydan->Connection = m_con;
	GetBkStackInfo();
	query->Connection = m_con;
	qudetail->Connection = m_con;
	qrystorge->Connection = m_con;
	dsetGetHtHeaderTotal->Connection = m_con;
	dssetStkAmount->Connection = m_con;
	dsetSupplier->Active = true;
	dsetStaff->Active = true;
	//dblkpcbbSupplierID->KeyValue = 0;
	AnsiString sql;
	sql = "select ID,Name from SYS_StorageInfo where id = " + IntToStr(m_storageID) ;
	qrystorge->Close();
	qrystorge->SQL->Clear();
	qrystorge->SQL->Add(sql);
	qrystorge->Open();
	cbstorgename->Text = qrystorge->FieldByName("Name")->AsAnsiString ;
	edStoryNum->Text = IntToStr(m_storageID);

	//��
	ChangeOpmode(OPAddNtHeader);

	//��ʷ�����Ƿ���ʾ
	SYSSet * BSSET = new SYSSet();

	sql = "select name,value,bk from dbo.SYS_BSSET where name in ('storageday','storagesametishi','changeDanHaoDisplay','crtuserbarcode', ";
	sql = sql + " 'xiaoshudian','adddotenable','lastyjpxdiscount','yjpxfirstkind','rkallsupplier','rkusefind','rkusedelete','rkusechange','storageday') " ;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	while(!query->Eof)
	{
	   SYSSet *Note = new SYSSet();
	   Note->Name = query->FieldByName("NAME")->AsAnsiString;

	 if (query->FieldByName("NAME")->AsAnsiString=="xiaoshudian"||
		 query->FieldByName("NAME")->AsAnsiString=="storageday" ||
		 query->FieldByName("NAME")->AsAnsiString=="yjpxfirstkind" ||
		 query->FieldByName("NAME")->AsAnsiString=="changeDanHaoDisplay"||
		 query->FieldByName("NAME")->AsAnsiString=="storageday"
		 )

		  Note->ValueStr = query->FieldByName("bk")->AsAnsiString;
		else
		  Note->ValueBool = query->FieldByName("value")->AsBoolean;

		 BSSET->Add(query->FieldByName("NAME")->AsAnsiString,(TObject*)Note);

       query->Next();
	}
	// storageday
	BSSET->GetSetInfo("storageday");
	storageday = StrToInt(BSSET->ValueStr);

	//�ظ���ʾ

	BSSET->GetSetInfo("storagesametishi");
	sameid = BSSET->ValueBool;

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

	//������ʾ
	BSSET->GetSetInfo("changeDanHaoDisplay");
	ChangeDisplay = BSSET->ValueBool;

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

	//�ӵ�
	BSSET->GetSetInfo("adddotenable");
	addnote = BSSET->ValueBool;

	//�ϴ�Ԥ�������ۿ�

	BSSET->GetSetInfo("lastyjpxdiscount");
	lastjypxdiscount = BSSET->ValueBool;

	//Ԥ�������ۿۺ�������

	if (lastjypxdiscount && addnote) {
		BSSET->GetSetInfo("yjpxfirstkind");
		yjpxkind = BSSET->ValueStr;
	}

	//С����
	BSSET->GetSetInfo("xiaoshudian");
	format = "###,###,##" + BSSET->ValueStr ;

	RzDBNumericEdit3->DisplayFormat = format;
	RzDBNumericEdit4->DisplayFormat = format;// format;
	//���й�Ӧ����ʷ��ϸ

	BSSET->GetSetInfo("rkallsupplier");
	allsupplier = BSSET->ValueBool;

	//�鵥�����Ƿ�����
	BSSET->GetSetInfo("rkusefind");
	findpassword = BSSET->ValueBool;


	//ɾ�������Ƿ�����
	BSSET->GetSetInfo("rkusedelete");
	deletepassword = BSSET->ValueBool;


	//�޸ĵ�ͷ�����Ƿ�����
	BSSET->GetSetInfo("rkusechange");
	changepassword = BSSET->ValueBool;

	//�޸ĵ�ͷ�����Ƿ�����
	BSSET->GetSetInfo("crtuserbarcode");
	userbarcode = BSSET->ValueBool;
	if (userbarcode) {
		dbgrdNote->Columns->Items[3]->Visible = true;
	}
	else
	{
    	dbgrdNote->Columns->Items[3]->Visible = false;
	}

    delete BSSET;
	FormView();
}

void TfrmStorageMng1::GetBkStackInfo()
{
	AnsiString sql= "select name, ID from STK_BookstackInfo where StgID = " + IntToStr(m_storageID);
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


void TfrmStorageMng1::ChangeOpmode(OPMode opmode)
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

			Tfrmcaigouquery* frm = new Tfrmcaigouquery(Application,m_con,m_storageID,2,0);
				if (frm->ShowModal() == mrOk)
				{
                    String sql;
					sql = " select * from CUST_CustomerInfo where Type =1 order by name ";
					dsetSupplier->Active = false;
					dsetSupplier->CommandText = sql;
					dsetSupplier->Active = true;
					dsetSupplier->First();
					dblkpcbbSupplierID->KeyValue = dsetSupplier->FieldByName("ID")->AsInteger ;

					DelInvalidNtHeader();
					edtCatalog->Text = "";
					AnsiString code = frm->GetNoteCode();
					AnsiString sqlwhere = frm->GetWhere();
					try
					{
						QryNtHeader(code);
						String sql,codetmp;
						codetmp = code;
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
					//dbnbedtAddCosts->Enabled = false;
				}
		}
		break;
	case OPAddNtHeader:
		{
			//����ϴ������ģʽ������û�мӽ��κ����ݣ��������
			if (m_opmode == OPAddNtHeader &&
				dsetNote->Active && dsetNote->RecordCount < 1)
				return;
			//����ϴ���ɾ��ģʽ������ɾ�����е���ϸ
			if (m_opmode == OPDelNote
				&& dsetNote->Active && dsetNote->RecordCount < 1)
			{
            	return;
			}

			edtCatalog->Text = "";
			AddNtHeader();
			m_opmode = opmode;
        }
		break;
	case OPDelNtHeader:    //ɾ��
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
			DelNtHeader();
			m_opmode = opmode;
		}     */
		break;
	case OPAddNote:
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
			//���ֻ��һ�У��������ж�ѡ��
        	if (dbgrdNote->SelectedRows->Count == 0 || dbgrdNote->SelectedRows->Count == 1) {
            	for (int i = 1; i <= dsetNote->RecordCount ; i++) {
					dbgrdNote->DataSource->DataSet->RecNo = i;
					dbgrdNote->SelectedRows->CurrentRowSelected = true;
				}
			}
			TfrmSetNotes* frm = new TfrmSetNotes(this);
			frm->salediscount = 1;
			frm->ChangeBsmode(1);
			if (frm->ShowModal() == mrOk)
			{
				int amount = 0;
				float discount = 0;
				pixiaodiscount = 0.00;
				lsdiscount = 0.00;
				bool bsetAmount = frm->GetAmount(amount);
				bool bsetDiscount = frm->GetDiscount(discount);
				bsetpixiaodiscount = frm->GetpixiaoDiscount(pixiaodiscount);
				bsetlsdiscount = frm->GetlsDiscount(lsdiscount);
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
				else if (bsetpixiaodiscount) {
					BatchSetNotes(amount, discount, 0);
				}
				else if (bsetlsdiscount) {
					BatchSetNotes(amount, discount, 4);
				}
				QryNtHeader();

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
			//
			/*String NtHeader = dbedtStgNtCode->Text.Trim(),Headerdate;
			if (NtHeader == "" || NtHeader == "0") {
				return;
			}
			if (NtHeader.Length() == 13) {
				Headerdate = NtHeader.SubString(0,4)+ "-" + NtHeader.SubString(5,2) + "-" + NtHeader.SubString(7,2);
			}
			else if (NtHeader.Length() == 14)
			{
				Headerdate = NtHeader.SubString(1,4)+ "-" + NtHeader.SubString(6,2) + "-" + NtHeader.SubString(8,2);
			}
			else if (NtHeader.Length() == 15) {
				Headerdate = NtHeader.SubString(2,4)+ "-" + NtHeader.SubString(7,2) + "-" + NtHeader.SubString(9,2);
			}
			if (StrToDate(Headerdate) != Date()) {
				MessageBox(0,"�ֳ�����ֻ�ܸ����յģ�","��ⵥ" ,MB_OK);
				return;
			}*/
			TADOQuery *aq = new TADOQuery(this);
			aq->Connection = m_con ;
			AnsiString sql;
			sql = " select datediff(day,getdate(),HdTime) as day from BS_StorageNoteHeader where id = " +  dsetNtHeader->FieldByName("ID")->AsAnsiString;
            aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();
			if (aq->FieldByName("day")->AsInteger != 0 ) {
				MessageBox(0,"�˹��ܽ��޽��㵱�쵥�ݣ���������뵽��������д���","��ⵥ" ,MB_OK);
				return;
			}

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
				aq->Close();
				aq->SQL->Clear();
				aq->SQL->Add(sql);
				aq->ExecSQL();
				AnsiString Code = NoteCode::BuildCode(aq, GetDBTime(aq), 0, "FN_CUSEndMoneyDocuments", "MoneyCode");
				sql = "insert into FN_CUSEndMoneyDocuments (MoneyCode,date,state,type,userid,CustmerName,ClearingType,Clearingstyle,stgid) values ("+Code+",getdate(),1,1," + IntToStr(m_userID) +",'" + dblkpcbbSupplierID->Text + "','�ֳ�����','�ֽ�'," + IntToStr(m_storageID) + ")";
				aq->Close();
				aq->SQL->Clear();
				aq->SQL->Add(sql);
				aq->ExecSQL();
				sql = "insert into FN_CUSEndMoneyDtails(EndMoneyDocumentID,stgntcode,thistime,type,CodeStr) values(" + Code + "," + dsetNtHeader->FieldByName("StgNtCode")->AsAnsiString + "," + FloatToStr(frm->GetReceived()) + ",1,'" + dsetNtHeader->FieldByName("StgNtCodeStr")->AsAnsiString + "')";
				aq->Close();
				aq->SQL->Clear();
				aq->SQL->Add(sql);
				aq->ExecSQL();
				QryNtHeader();
			}
			delete aq;
			delete frm;
		}
		m_opmode = opmode;
		break;
    default:
		break;
	}
}

void TfrmStorageMng1::AddNtHeader()//��ӵ�ͷ
{
	spQryNtHeader->Active = false;
	spQryNtHeader1->Active = false;
	cmdAddNtHeader->Parameters->ParamByName("@StgID")->Value = m_storageID;
	cmdAddNtHeader->Parameters->ParamByName("@Bsmode")->Value = 1;
	cmdAddNtHeader->Parameters->ParamByName("@OperatorID")->Value = m_userID;
	cmdAddNtHeader->Parameters->ParamByName("@CODEMODE")->Value = 0;
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

void TfrmStorageMng1::QryNtHeader(String code, bool qrybkstack)//��ѯ��ͷ
{
	spQryNtHeader->Active = false;
	spQryNtHeader1->Active = false;
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
		//dsetNote->AfterScroll = dsetNoteAfterScroll;
		GetHtHeaderTotal();//ͳ��������ĺϼ�
		grdCellClick();
		/*if (qrybkstack)
		{
			QryBkstack();
		} */
		editdanhao->Text = dsetNtHeader->FieldByName("StgNtCodeStr")->AsAnsiString ;
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "###,###,##0.00";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = "###,###,##0.00";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = "###,###,##0.00";
		operterview(dsetNtHeader->FieldByName("OperatorID")->AsInteger );
		membk->Text =  dsetNtHeader->FieldByName("Remarks")->AsString;
		//�Ѷ���
		if (dsetNtHeader->FieldByName("cwstate")->AsInteger == 1 || dsetNtHeader->FieldByName("Checked")->AsFloat != 0.00 ) {
			grpbxNote->Enabled = false;
			BtnChangeOptions->Enabled = false;
			RzToolButton2->Enabled = false;
			RzToolButton3->Enabled = false;
			dbnbedtAddCosts->Enabled = false;
			Image1->Visible = true;
			SupplierCreit(0);
		}
		else
		{
			if (SupplierCreit(1)) {
				grpbxNote->Enabled = true;
			}
			else
			{
            	grpbxNote->Enabled = false;
			}

			BtnChangeOptions->Enabled = true;
			RzToolButton2->Enabled = true;
			RzToolButton3->Enabled = true;
			dbnbedtAddCosts->Enabled = true;
			Image1->Visible = false;
		}
	}
	catch(Exception &E)
	{
		logmessage = E.Message ;
		AddEvent(3,"һ����ⴰ��",m_userID,m_storageID,logmessage,linfo.con);
	}
}


void TfrmStorageMng1::QryNtHeader(bool qrybkstack)//��ѯ��ͷ
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
			//dsetNote->AfterScroll = dsetNoteAfterScroll;

				GetHtHeaderTotal();//ͳ��������ĺϼ�
			grdCellClick();
			/*if (qrybkstack)
			{
				QryBkstack();
			}*/
			editdanhao->Text = dsetNtHeader->FieldByName("StgNtCodeStr")->AsAnsiString ;
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00";
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "###,###,##0.00";
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = "###,###,##0.00";
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = "###,###,##0.00";
			operterview(dsetNtHeader->FieldByName("OperatorID")->AsInteger );
			membk->Text =  dsetNtHeader->FieldByName("Remarks")->AsString;
			if (dsetNtHeader->FieldByName("cwstate")->AsInteger == 1 || dsetNtHeader->FieldByName("Checked")->AsFloat != 0.00 ) {
				grpbxNote->Enabled = false;
				BtnChangeOptions->Enabled = false;
				RzToolButton2->Enabled = false;
				RzToolButton3->Enabled = false;
				dbnbedtAddCosts->Enabled = false;
				Image1->Visible = true;
			}
			else
			{
				grpbxNote->Enabled = true;
				BtnChangeOptions->Enabled = true;
				RzToolButton2->Enabled = true;
				RzToolButton3->Enabled = true;
				dbnbedtAddCosts->Enabled = true;
				Image1->Visible = false;
			}
		}
		catch(Exception &E)
		{
			//ShowMessage("�õ������ڣ�");
			logmessage = E.Message;
			AddEvent(3,"һ����ⴰ��",m_userID,m_storageID,logmessage,linfo.con);
		}
	}
}

void TfrmStorageMng1::QryNtHeader(int id, bool qrybkstack)//��ѯ��ͷ
{
	//��ѯ��ͷ
	spQryNtHeader1->Active = false;
	spQryNtHeader->Active = false;
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

		GetHtHeaderTotal();//ͳ��������ĺϼ�
		grdCellClick();

		editdanhao->Text = dsetNtHeader->FieldByName("StgNtCodeStr")->AsAnsiString ;
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "###,###,##0.00";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = "###,###,##0.00";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = "###,###,##0.00";
		operterview(dsetNtHeader->FieldByName("OperatorID")->AsInteger );
		membk->Text =  dsetNtHeader->FieldByName("Remarks")->AsString;
		if (dsetNtHeader->FieldByName("cwstate")->AsInteger == 1 || dsetNtHeader->FieldByName("Checked")->AsFloat != 0.00 ) {
			grpbxNote->Enabled = false;
			BtnChangeOptions->Enabled = false;
			RzToolButton2->Enabled = false;
			RzToolButton3->Enabled = false;
			dbnbedtAddCosts->Enabled = false;
			Image1->Visible = true;
		}
		else
		{
			grpbxNote->Enabled = true;
			BtnChangeOptions->Enabled = true;
			RzToolButton2->Enabled = true;
			RzToolButton3->Enabled = true;
			dbnbedtAddCosts->Enabled = true;
			Image1->Visible = false;
		}
	}
	catch(Exception &E)
	{
		logmessage = E.Message;
		AddEvent(3,"һ����ⴰ��",m_userID,m_storageID,logmessage,linfo.con);
	}
}

void TfrmStorageMng1::DelNtHeader()//ɾ����ͷ
{
	//
}

void TfrmStorageMng1::UpdateNtHeader()//���µ�ͷ
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
				dsetNtHeader->FieldByName("StaffID")->AsString;
		cmdUpdateNtHeader->Parameters->ParamByName("@AddCosts")->Value =
			abs(dsetNtHeader->FieldByName("AddCosts")->AsFloat);
		cmdUpdateNtHeader->Parameters->ParamByName("@Remarks")->Value =
			membk->Text ;
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

bool TfrmStorageMng1::AddNote(int supplierID, int catalogID)//һ����ӵ�ͷ��Ϣ����ͷ��Ϣ
{
	bool result = false;
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
        AnsiString sql;
		sql = "select CUST_CustomerInfo.Name from CUST_CustomerInfo left join stk_bookinfo on CUST_CustomerInfo.id = stk_bookinfo.supplierid "
			"where stk_bookinfo.stgid = " + IntToStr(m_storageID) + " and SupplierID <> " + dsetNtHeader->FieldByName("SupplierID")->AsAnsiString + " and BkcatalogID = " + IntToStr(catalogID);
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->Open();
		if (!query->IsEmpty() ) {
			AnsiString msg;
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
			msg = "�����Ѿ����ڹ�Ӧ�̣�" + msg + "  �Ƿ������";
			if (MessageBoxA(0,msg.c_str() ,"ѯ��",MB_ICONQUESTION|MB_OKCANCEL)!=1 )
			{
				return true;
			}
		}

		cmdAddNote->Parameters->ParamByName("@NtHeaderID")->Value
			= dsetNtHeader->FieldByName("ID")->AsInteger;
		cmdAddNote->Parameters->ParamByName("@STKinfoID")->Value
			= -1;
		cmdAddNote->Parameters->ParamByName("@BkcatalogID")->Value
			= catalogID;//	= dsetCatalog->FieldByName("ID")->AsInteger;
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
				/*((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00%";
				((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "��###,###,##0.00";
				((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = "��###,###,##0.00";
				((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = "��###,###,##0.00"; */
				editjingjiaprice->Text = dbgrdNote->DataSource->DataSet->FieldByName("Price")->AsAnsiString ;
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
        	if (sameid) {
				MessageBox(0,"���������ͬĿ¼����!","��ʾ",MB_ICONEXCLAMATION);
			}
			result = true;
		}
	}
	return result;
}

bool TfrmStorageMng1::AddNote(int id)     //ȫѡ��ʱ���д˺�������ӽ�ȥ�󲻲�ѯ
{
	bool result = false;
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
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
		MYTRACEF(_T("add note @NtHeaderID=%d,@BkcatalogID=%d,@STKinfoID=%d,@SupplierID=%d,@Bsmode=%d,@bkstackID=%d")
			, dsetNtHeader->FieldByName("ID")->AsInteger
			,-1
			, dsetNtHeader->FieldByName("SupplierID")->AsInteger
			, 1);
		cmdAddNote->Execute();
		int ret = cmdAddNote->Parameters->ParamByName("@RETURN_VALUE")->Value;
		if (ret > 0)//����ɹ�
		{
			//int bkinfoid = dsetNote->FieldByName("BkInfoID")->AsInteger;
			/*try
			{
				//LockWindowUpdate(dbgrdNote->Handle);//����ָ�����ڣ���ֹ�����¡�
				QryNtHeader(dsetNtHeader->FieldByName("ID")->AsInteger, true);
				((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00%";
				((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "��###,###,##0.00";
				((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = "��###,###,##0.00";
				((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = "��###,###,##0.00";
			}
			__finally
			{
				//LockWindowUpdate(NULL);
			} */
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
void TfrmStorageMng1::UpdateNote()//���µ�
{
	if (dsetNote->Active && dsetNote->RecordCount >= 1)
	{
		cmdUpdateNote->Parameters->ParamByName("@ID")->Value
			= dsetNote->FieldByName("ID")->AsInteger;

		cmdUpdateNote->Parameters->ParamByName("@Amount")->Value
				= abs(dsetNote->FieldByName("Amount")->AsInteger);

	 //	 ShowMessage(dsetNote->FieldByName("Discount")->AsAnsiString);
		cmdUpdateNote->Parameters->ParamByName("@Discount")->Value
			= fabs(dsetNote->FieldByName("Discount")->AsFloat);
		cmdUpdateNote->Parameters->ParamByName("@bkstackID")->Value = (int)(cbbkstackID->Items->Objects[cbbkstackID->ItemIndex]);
		if (stackchange) {
			cmdUpdateNote->Parameters->ParamByName("@bkchange")->Value = 1;
		}
		else
		{
			cmdUpdateNote->Parameters->ParamByName("@bkchange")->Value = 0;
		}
		cmdUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 1;

		try
		{
        	cmdUpdateNote->Execute();
		 // dbgrdNote->DataSource->DataSet->UpdateRecord()
			//LockWindowUpdate(dbgrdNote->Handle);//����ָ�����ڣ���ֹ�����¡�
			//if (stackchange) {
            //	QryNtHeader();
			//}
			QryNtHeader();
			/*((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00";
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "��###,###,##0.00";
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = "###,###,##0.00";
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = "###,###,##0.00";  */
		}
		__finally
		{
			//LockWindowUpdate(NULL);
		}
	}
}

void TfrmStorageMng1::DelNote()//ɾ����ϸ
{
	if (dsetNote->IsEmpty() )
	{
		return;
	}
	if (dbgrdNote->SelectedRows->Count == 0)
	{
		cmdDelNote->Parameters->ParamByName("@ID")->Value
			= dsetNote->FieldByName("ID")->AsInteger;
		cmdDelNote->Parameters->ParamByName("@Bsmode")->Value = 1;
		if (ChangeDisplay) {
			logmessage = "ɾ����ⵥ" + dsetNtHeader->FieldByName("StgNtCodeStr")->AsAnsiString ;
		}
		else
		{
			logmessage = "ɾ����ⵥ" + dsetNtHeader->FieldByName("StgNtCode")->AsAnsiString ;
		}
		logmessage = logmessage + "����Ŀ��" + dsetNote->FieldByName("CatalogName")->AsAnsiString + "��";
		AddEvent(1,"һ����ⴰ��",m_userID,m_storageID,logmessage,linfo.con);
		cmdDelNote->Execute();
		try
		{
			QryNtHeader();
		}
		__finally
		{
		}
	}
	else if (dbgrdNote->SelectedRows->Count > 0)
	{
		String ids = "";
		dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[0];
		ids = ids + dsetNote->FieldByName("ID")->AsString;
		if (ChangeDisplay) {
			logmessage = "ɾ����ⵥ" + dsetNtHeader->FieldByName("StgNtCodeStr")->AsAnsiString ;
		}
		else
		{
			logmessage = "ɾ����ⵥ" + dsetNtHeader->FieldByName("StgNtCode")->AsAnsiString ;
		}
		logmessage = logmessage + "����Ŀ��" + dsetNote->FieldByName("CatalogName")->AsAnsiString + "��";
		AddEvent(1,"һ����ⴰ��",m_userID,m_storageID,logmessage,linfo.con);
		for (int i=1; i < dbgrdNote->SelectedRows->Count; i++)
		{
			dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[i];
			ids = ids + "," + dsetNote->FieldByName("ID")->AsString;
			if (ChangeDisplay) {
				logmessage = "ɾ����ⵥ" + dsetNtHeader->FieldByName("StgNtCodeStr")->AsAnsiString ;
			}
			else
			{
				logmessage = "ɾ����ⵥ" + dsetNtHeader->FieldByName("StgNtCode")->AsAnsiString ;
			}
			logmessage = logmessage + "����Ŀ��" + dsetNote->FieldByName("CatalogName")->AsAnsiString + "��";
			AddEvent(1,"һ����ⴰ��",m_userID,m_storageID,logmessage,linfo.con);
		}
		cmdBatchDelNote->Parameters->ParamByName("@IDS")->Value = ids;
		cmdBatchDelNote->Parameters->ParamByName("@Bsmode")->Value = 1;
		cmdBatchDelNote->Execute();
		try
		{
			QryNtHeader();
		}
		__finally
		{
		}
	}
}

void TfrmStorageMng1::BatchSetNotes(int amount, float discount, int mode)
{
	if (dsetNote->Active && dsetNote->RecordCount >= 1)
	{
		String ids = "";
		if (dbgrdNote->SelectedRows->Count == 0)
		{
			ids = ids + dsetNote->FieldByName("ID")->AsString;
			if (bsetpixiaodiscount) {
				BatchsetWsaleDiscout(pixiaodiscount);
			}
			if (bsetlsdiscount) {
				BatchsetLsDiscout(lsdiscount);
			}
		}
		else if (dbgrdNote->SelectedRows->Count > 0)
		{
			dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[0];
			if (bsetpixiaodiscount) {
				BatchsetWsaleDiscout(pixiaodiscount);
			}
			if (bsetlsdiscount) {
				BatchsetLsDiscout(lsdiscount);
			}
			ids = dsetNote->FieldByName("ID")->AsString;
			for (int i=1; i < dbgrdNote->SelectedRows->Count; i++)
			{

				dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[i];
				if (bsetpixiaodiscount) {
					BatchsetWsaleDiscout(pixiaodiscount);
				}
				if (bsetlsdiscount) {
					BatchsetLsDiscout(lsdiscount);
				}
				ids = ids + "," + dsetNote->FieldByName("ID")->AsString;
			}
		}
		else
			return;

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

void __fastcall TfrmStorageMng1::edtQrySupplierKeyPress(TObject *Sender, wchar_t &Key)
{
	/*if (Key == '\r')
	{
		if (!dsetNtHeader->Active
			|| !dsetNote->Active
			|| (dsetNtHeader->Active && dsetNtHeader->RecordCount < 1))
        	return;

		AnsiString sql;
		sql = Sysutils::Format("select * from CUST_CustomerInfo where (ID>0 and Type=1) and Name='%s'",
			ARRAYOFCONST((dblkpcbbSupplierID->Text.c_str())));
		dsetLkpSupplier->Active = true;
		if (dsetLkpSupplier->RecordCount > 1
			 && dblkpdlgSupplier->Execute())//�ҵ������Ӧ��
		{
			dsetNtHeader->Edit();
			dsetNtHeader->FieldByName("SupplierID")->AsInteger
				= dsetLkpSupplier->FieldByName("ID")->AsInteger;
			UpdateNtHeader();
			Key = 0;
			Perform(WM_NEXTDLGCTL, 0, 0);
		}
		else if (dsetLkpSupplier->RecordCount == 1)//�ҵ�һ����Ӧ��
		{
			dsetNtHeader->Edit();
			dsetNtHeader->FieldByName("SupplierID")->AsInteger
				= dsetLkpSupplier->FieldByName("ID")->AsInteger;
			UpdateNtHeader();
			Key = 0;
			Perform(WM_NEXTDLGCTL, 0, 0);
		}
		else//δ���ҵ�������
		{

        }
	} */
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng1::dblkpcbbStaffIDKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r')
	{
		Key = 0;
		Perform(WM_NEXTDLGCTL, 0, 0);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng1::edtCatalogKeyPress(TObject *Sender, wchar_t &Key)
{
	if (m_catalogSearchMode == 6) {
		if ((Key < '0' || Key > '9') && (Key != '\b') && (Key != '.') && (Key != '\r') ) {
            Key = NULL;
		}
	}
	if (Key == '\r')
	{
		if (BtnSave->Enabled) {
			MessageBox(0,"���ȱ�����ⵥ��","���" ,MB_ICONEXCLAMATION);
			return;
		}
		if (edtCatalog->Text == "") {
			changeInputMode();
			return;
		}
		float price;
		if (m_catalogSearchMode == 6) {
			try {
				price = StrToFloat(edtCatalog->Text.Trim());
			} catch (...) {
				MessageBox(0,"��������ȷ�Ķ��ۣ�","���" ,MB_ICONEXCLAMATION);
				AddEvent(3,"һ����ⴰ��",m_userID,m_storageID,"�������벻�淶",linfo.con);
				return;
			}
		}

		if (dsetNtHeader->IsEmpty())
			return;

		AnsiString ISBN;
		bool exec = true;
		int results;

		TfrmSelectCatalog* frm = new TfrmSelectCatalog(Application,m_con);
		LandInfo li;
		li.app = m_app;
		li.con = m_con;
		li.userID = m_userID;
		li.storageID = m_storageID;
		frm->Init(&li);

		frm->SetSearchMode(m_catalogSearchMode, edtCatalog->Text);
		frm->DoModalType = 3; //���ģʽ
		//frm->Storagefrm = this;
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
			frm->GetSelectResult(bkinfoid,catalogID);
			//supplierID = dsetSupplier->FieldByName("ID")->AsInteger ;
			if (frm->SelectAll) {                           //ȫѡ
				for (int i = 0; i < frm->lengthint  ; i++) {
					if (AddNote(frm->BkcatalogiD[i])) {
					}
				}
				QryNtHeader();
			}
			else {
				if (catalogID >= 0)
				{
					TLocateOptions   Opts;
					Opts.Clear();
					Opts   <<   loPartialKey;
					String   str   = AnsiString(catalogID);
					if ( !dsetNote->Locate("BkcatalogID",str,Opts))    //û����ͬ��¼��
					{
						if (AddNote(0, catalogID))
						{
							Key=0;
							//yjpxdiscount();
							if (chfoceset->Checked) {     //��궨λ
								if (chfsamount->Checked ) {
									dbnbedtAmount->SetFocus();
								}
								else if (chfsdiscount->Checked ) {
									dbnbedtDiscount->SetFocus();
								}
								else if (chjinjia->Checked ) {
									editjingjiaprice->SetFocus();
								}
								else if (chpxdiscount->Checked ) {
                                	editpxdiscount->SetFocus();
								}
								else if (chpxprice->Checked ) {
                                	editpxprice->SetFocus();
								}
								else if (chlsdiscount->Checked ) {
									edlsdiscount->SetFocus();
								}
								else if (chlsprice->Checked ) {
                                	edtlsprice->SetFocus();
								}
								else if (chfsluru->Checked) {
									edtCatalog->SetFocus();
								}
							}
							else
							{
								dbnbedtAmount ->SetFocus();
							}
						}else
						{
						}
					}
					else   //����ͬ��¼����
					{
						if (sameid) {    //��̨������Ҫ��ʾ
							MessageBox(0,"����ͬ��¼���ʵ��","��ʾ" ,MB_ICONEXCLAMATION);
						}
						dbgrdNote->SelectedRows->CurrentRowSelected = true;
						dbgrdNote->SetFocus();
						dbnbedtAmount->SetFocus();
					}
				}
			}
		}else {
			if (!frm->findbook) {     //��������
				if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
				{
					Tfrmnewbook1 *frma = new Tfrmnewbook1(m_app,m_con);
					//frma->StorageMng = this;
					frma->modle = 1;
					AnsiString ss = edtCatalog->Text.Trim();
					if (m_catalogSearchMode == 1) {
						if (ss.SubString(1,1) == "6") {
							frma->cbsaletype->ItemIndex = 2;
							frma->cbsaletype->OnChange(this);
							frma->editwenjutiaomao->Text = edtCatalog->Text ;
							PostMessage(frma->editwenjutiaomao->Handle, WM_KEYDOWN,VK_RETURN,0);
						}
						else if (ss.SubString(1,3) == "977") {
							frma->cbsaletype->ItemIndex = 1;
							frma->cbsaletype->OnChange(this);
							frma->editqikanmao->Text = edtCatalog->Text ;
							PostMessage(frma->editqikanmao->Handle, WM_KEYDOWN,VK_RETURN,0);
						}
						else
						{
                        	frma->editcode->Text = edtCatalog->Text ;
							PostMessage(frma->editcode->Handle, WM_KEYDOWN,VK_RETURN,0);
						}
					}
					else
					{
						frma->editcode->Text = edtCatalog->Text ;
						PostMessage(frma->editcode->Handle, WM_KEYDOWN,VK_RETURN,0);
					}

					//frma->editcode->Text = edtCatalog->Text ;
					//PostMessage(frma->editcode->Handle, WM_KEYDOWN,VK_RETURN,0);
					if (mbOK == frma->ShowModal())
					{

					}
					delete frma;
					dbnbedtAmount->SetFocus();
				}
			}
		}
		Key=0;
		edtCatalog->Text = "";
		editshun->Text = "0";
		editque->Text = "0";
		//	 editpxdiscount->Text = "100.00";
		editjingjiaprice->Text = FormatFloat("0.00", dbgrdNote->DataSource->DataSet->FieldByName("price")->AsFloat * dbnbedtDiscount->Value * 0.01);
		editpxprice->Text =  FormatFloat("0.00", dbgrdNote->DataSource->DataSet->FieldByName("price")->AsFloat);
		delete frm;

	  //	dbgrdNote->DataSource->DataSet->
		historyview();
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmStorageMng1::dbedtSupplySNKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r')
	{
		if (dbnbedtAddCosts->Enabled ) {
			dbnbedtAddCosts->SetFocus();
		}
		else
		{
			membk->SetFocus();
		}
	}
}

//---------------------------------------------------------------------------

void TfrmStorageMng1::DelInvalidNtHeader()
{
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1
		&& dsetNote->Active && dsetNote->RecordCount < 1 && dsetNtHeader->FieldByName("StgNtCode")->AsInteger == 0)
	{
    	DelNtHeader();
	}
}

void __fastcall TfrmStorageMng1::FormClose(TObject *Sender, TCloseAction &Action)
{
	DelInvalidNtHeader();
	spQryNtHeader->Active = false;
	spQryNtHeader1->Active = false;
	dsetSupplier->Active = false;
	dsetStaff->Active = false;
	dsetSupplier->Active = false;
	TfrmMDIChild::FormClose(Sender, Action);
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng1::RzToolButton9Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng1::RzToolButton8Click(TObject *Sender)
{
	//��ӡ
	if (N11->Checked ) {    //�쳣��ӡ
	  //
	}
	else                  //һ���ӡ
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
			frm->RvSystem1->DefaultDest   = rdPrinter ;
			frm->RvSystem1->SystemSetups<<ssAllowDestPrinter;
			frm->Maker = lblOpName->Caption ;
			frm->rkbk = rkbk;
			frm->printtitle = printtitle;
			frm->contact = contact;
			frm->tel = tel;
			frm->address = address;
			frm->supplycode = dbedtSupplySN->Text ;
			frm->PrintStorageExe(0);

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
}
//---------------------------------------------------------------------------


void __fastcall TfrmStorageMng1::RzToolButton6Click(TObject *Sender)
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

//---------------------------------------------------------------------------
bool __fastcall TfrmStorageMng1::DbgridToExcel(TRzDBGrid* dbg)
{
	AnsiString temptext,path  ;
	int k = dbg->DataSource ->DataSet ->RecordCount ,n=0;

	savedlg->FileName = StringReplace(dblkpcbbSupplierID->Text.Trim() +editdanhao->Text ,"\\","-",TReplaceFlags()<<rfReplaceAll) + "��ⵥ";
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
//  ��Excel�г��ַ�����ʾ

	n=0;

	int t1= 0;
	temptext = "\n";
	for(int q=0;q<dbg->FieldCount-1 ;++q)
	{
		if (dbg->Columns->Items[q]->Visible == true) {
			t1++;
			temptext = dbg->Columns ->Items [q]->Title ->Caption;
			v.OlePropertyGet("Cells",1+n,(t1)).OlePropertySet("Value",temptext .c_str() );
			//temptext = temptext + dbg->Columns ->Items [q]->Title ->Caption + ",";
		}

	}
	//FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	int t2 = dbg->DataSource ->DataSet ->RecordCount ;

	dbg->DataSource ->DataSet ->First();
	dbg->DataSource ->DataSet->DisableControls();
	for(int   i=2+n;i<=t2+1+n ;i++)
	{
		t1=0;
		//temptext = "\n";
		for(int j=1;j<dbg->Columns ->Count;j++)
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


	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",n+1,1),vSheet.OlePropertyGet("Cells",t2+n+2,t1)); //ȡ�úϲ�������
	R.OlePropertyGet("Borders",2).OlePropertySet("linestyle",1);
	R.OlePropertyGet("Borders",4).OlePropertySet("linestyle",1);

	v.OlePropertyGet("Cells",t2+2,1).OlePropertySet("Value","�ϼ�");

	temptext = RzDBNumericEdit2->Text ;
	v.OlePropertyGet("Cells",t2+2,7).OlePropertySet("Value",temptext .c_str() );

	temptext = RzDBNumericEdit3->Text ;
	v.OlePropertyGet("Cells",t2+2,9).OlePropertySet("Value",temptext .c_str() );

	temptext = RzDBNumericEdit4->Text ;
	v.OlePropertyGet("Cells",t2+2,10).OlePropertySet("Value",temptext .c_str() );
	dbg->DataSource ->DataSet->EnableControls();

	try {
		xWorkbook.OleFunction("SaveAs",path.c_str());
	} catch (...) {
	}
	return false;
}

//---------------------------------------------------------------------------



//---------------------------------------------------------------------------

void TfrmStorageMng1::QryBkstack()
{
   //
}


void TfrmStorageMng1::ResetNtHeader()
{
	//���õ�ͷ
}
void __fastcall TfrmStorageMng1::sbnewcustomerClick(TObject *Sender)
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
			if (!SupplierCreit(0)) {
				return;
			}
			dsetNtHeader->Edit();
			dsetNtHeader->FieldByName("SupplierID")->AsInteger = dsetSupplier->FieldByName("ID")->AsInteger;
			UpdateNtHeader();
			dblkpcbbSupplierID->SetFocus();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng1::spnewbookClick(TObject *Sender)
{
	//����Ŀ
	if (dblkpcbbSupplierID->Enabled ) {
        return;
	}
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		Tfrmnewbook1 *frm = new Tfrmnewbook1(m_app,m_con);
		//frm->StorageMng = this;
		frm->modle = 1;//���

		if (mbOK == frm->ShowModal())
		{
			edtCatalog->Text  = "";
			dbnbedtAmount->Text = "0";
			dbnbedtDiscount->Text = "100";
			editpxdiscount->Text = "100";
			edlsdiscount->Text = "100";
			editshun->Text = "0";
			editque->Text = "0";
			editjingjiaprice->Text = "0.00";
			editpxprice->Text = "0.00";
			edtlsprice->Text = "0.00";
			dbnbedtAmount->SetFocus();
		}else
		{
		 	edtCatalog->SetFocus();
		}
		delete frm;
	   	return;
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmStorageMng1::BtnViewClick(TObject *Sender)
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

void __fastcall TfrmStorageMng1::lblCatalogMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	if (Button == mbLeft ) {
		TPoint  pt;
		GetCursorPos(&pt);
		PM->Popup(pt.x,pt.y);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng1::N1Click(TObject *Sender)
{
    lblCatalog->Caption = "���";
	m_catalogSearchMode = 1;
	edtCatalog->MaxLength = 16;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng1::N2Click(TObject *Sender)
{
	lblCatalog->Caption = "�Ա���";
	m_catalogSearchMode = 2;
	edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng1::N3Click(TObject *Sender)
{
	lblCatalog->Caption = "����";
	m_catalogSearchMode  = 3;
	edtCatalog->MaxLength = 0;
}
void TfrmStorageMng1::changeInputMode()
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
	 case 5:
		N1->Click();
		break;
	 case 6:
		N10->Click();
		break;
  	default:
      ;
	}
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng1::BtnClearClick(TObject *Sender)
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
		frm->Maker = lblOpName->Caption ;
		frm->rkbk = rkbk;
		frm->printtitle = printtitle;
		frm->contact = contact;
		frm->tel = tel;
		frm->address = address;
		frm->supplycode = dbedtSupplySN->Text ;
		frm->PrintStorageExe(1);
		/*if (lbcaption->Caption == "��ⵥ")
		{
			 frm->PrintStorageExe(1);
		}else
		{
			 frm->PrintStorageExe(2);
		} */

		frm->Close();
		delete frm;


	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng1::RzToolButton3Click(TObject *Sender)
{
	TControl* con = dynamic_cast<TControl*>(Sender);
	if (con != NULL)
	{
		dbgrdNote->SetFocus();
		ChangeOpmode(con->Tag);
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmStorageMng1::RzToolButton5Click(TObject *Sender)
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

void __fastcall TfrmStorageMng1::RzToolButton2Click(TObject *Sender)
{
	TControl* con = dynamic_cast<TControl*>(Sender);
	if (con != NULL)
	{
		dbgrdNote->SetFocus();
		ChangeOpmode(con->Tag);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng1::FormResize(TObject *Sender)
{
	 //dbgrdNote->Width = 720;
	 //dbgrdNote->Height = 352;
}
//---------------------------------------------------------------------------
void __fastcall TfrmStorageMng1::dblkpcbbSupplierIDKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == VK_RETURN) {
		if (dblkpcbbSupplierID->Text == "") {
			MessageBox(0,"��ѡ��Ӧ�̣�","��ʾ" ,MB_OK);
			return;
		}
		else
		{
            dblkpcbbSupplierID->Enabled = false;
			TADOQuery *aq = new TADOQuery(this);
			aq->Connection = m_con ;
			AnsiString sql = "select Salesman from CUST_CustomerInfo where id = " + IntToStr(dsetSupplier->FieldByName("ID")->AsInteger );
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();
			sql = "select * from SYS_StaffInfo where Name = '" + aq->FieldByName("Salesman")->AsString + "' and stgID = " + IntToStr(m_storageID) + " and Career = 1";
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();
			if (!aq->IsEmpty()) {
				int staff = aq->FieldByName("ID")->AsInteger;
				dblkpcbbStaffID->KeyValue = staff;
				dsetNtHeader->Edit();
				dsetNtHeader->FieldByName("StaffID")->AsInteger = staff;
				dsetNtHeader->FieldByName("SupplierID")->AsInteger = dsetSupplier->FieldByName("ID")->AsInteger;
				dsetNtHeader->Post();
			}


			delete aq;
			//���¹�Ӧ��

	

			sbnewcustomer->Enabled = false;

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

void  TfrmStorageMng1::FindNote(String code)
{
	/*DelInvalidNtHeader();
	edtCatalog->Text = "";
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
	sbnewcustomer->Enabled = false;   */
}

//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng1::dbgrdNoteDblClick(TObject *Sender)
{
	if (dsetNote->IsEmpty() ) {
		return;
	}
	TfrmNewBookModify * frm = new TfrmNewBookModify(m_app,m_con,dsetNote->FieldByName("BkcatalogID")->AsInteger,m_storageID,m_userID);
	frm->ShowModal();
	delete frm;
	QryNtHeader();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng1::dbgrdNoteCellClick(TColumn *Column)
{
  // ShowMessage(dsetNote->FieldByName("xuhao")->AsAnsiString);
  	//grdCellClick();
}
//---------------------------------------------------------------------------
void TfrmStorageMng1::grdCellClick()
{
	if (dsetNote->IsEmpty() ) {
		dbnbedtAmount->IntValue = 0;
		dbnbedtDiscount->Value = 0.00;
		editshun->Text = "0";
		editque->Text = "0";
		editjingjiaprice->Text = "0.00";
		editpxdiscount->Text = "100";
		editpxprice->Text = "0.00";
		edlsdiscount->Text = "100";
		edtlsprice->Text = "0.00";
		edtotalamount->Text = "";
		dbnbedt1->Text = "";
		return;
	}
	if (dsetNote->RecordCount > 0) {
		cbbkstackID->ItemIndex = cbbkstackID->Items->IndexOfObject((TObject*)dsetNote->FieldByName("BkstackID")->AsInteger ) ;
		AnsiString sql;
		if (dsetNote->FieldByName("returndate")->AsAnsiString != "") {
        	dtpbackdate->Date = dsetNote->FieldByName("returndate")->AsDateTime ;
		}
		else
		{
			dtpbackdate->Date = StrToDate("1900-01-01");
		}

		editpxdiscount->Text = dsetNote->FieldByName("wsalediscount")->AsAnsiString ;
		edlsdiscount->Text = dsetNote->FieldByName("lsdiscount")->AsAnsiString ;
		editshun->Text = dsetNote->FieldByName("harmnum")->AsAnsiString ;
		editque->Text = dsetNote->FieldByName("damagenum")->AsAnsiString ;
		cbreturn->Checked = dsetNote->FieldByName("returnflag")->AsBoolean ;
		//ֵ

		dbnbedtAmount->Value = dsetNote->FieldByName("Amount")->AsFloat;   //����
		dbnbedtDiscount->Value =  dsetNote->FieldByName("Discount")->AsFloat;  //�ۿ�

		double jinjia;
		double discount;
		double price ;
		if (editjingjiaprice->Text == "") {
			editjingjiaprice->Text = "0.00";
		}
		try {
			price =  dbgrdNote->DataSource->DataSet->FieldByName("price")->AsFloat ;
			jinjia = price * dbnbedtDiscount->Value * 0.01 ;
			editjingjiaprice->Text =  FormatFloat("0.00",jinjia);
			editpxprice->Text = FormatFloat("0.00",price*dsetNote->FieldByName("wsalediscount")->AsFloat*0.01);
			edtlsprice->Text = FormatFloat("0.00",price*dsetNote->FieldByName("lsdiscount")->AsFloat*0.01);
		} catch (Exception &E) {
			logmessage = E.Message;
			AddEvent(3,"һ����ⴰ��",m_userID,m_storageID,logmessage,linfo.con);
		}
		historyview();
	}
}
//---------------------------------------------------------------------------

void TfrmStorageMng1::historyview()
{
	AnsiString sql;
	if (dsetNote->IsEmpty() ) {
    	return;
	}
	if (dsetNote->RecordCount > 0) {

		DATE datetime = Date();
		datetime = datetime - storageday;
		sql = "select BS_StorageNoteHeader.StgNtCode as Ntcode,BS_StorageNoteHeader.StgNtCodeStr,BS_StorageNote.Amount,BS_StorageNote.Discount,Convert(varchar(20),BS_StorageNoteHeader.HdTime,111) as HdTime,CUST_CustomerInfo.Name,BS_BookCatalog.Price from BS_StorageNote left join BS_StorageNoteHeader on BS_StorageNote.StgNtHeaderID = BS_StorageNoteHeader.ID "
			  "left join BS_BookCatalog on BS_StorageNote.bkcatalogID = BS_BookCatalog.ID left join CUST_CustomerInfo on BS_StorageNoteHeader.SupplierID = CUST_CustomerInfo.id "
			  "WHERE BS_BookCatalog.ID = " + dsetNote->FieldByName("BkcatalogID")->AsString ;
		sql = sql + " and BS_StorageNoteHeader.HdTime >= '" +  DateToStr(datetime) ;
		sql = sql + "' and BS_StorageNoteHeader.StgID = " + edStoryNum->Text ;
		if (!allsupplier) {
			sql = sql + " and BS_StorageNoteHeader.SupplierID = " + dsetSupplier->FieldByName("ID")->AsString ;
		}
		qudetail->Close();
		qudetail->SQL->Clear();
		qudetail->SQL->Add(sql);
		qudetail->Open();

		((TFloatField *)dgdetail->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00";
	  //	((TFloatField *)dgdetail->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "��###,###,##0.00";
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

void __fastcall TfrmStorageMng1::N5Click(TObject *Sender)
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



void __fastcall TfrmStorageMng1::mniBsNoteClick(TObject *Sender)
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

	  RzToolButton5Click(BtnNew);

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng1::N6Click(TObject *Sender)
{
	lblCatalog->Caption = "����";
	m_catalogSearchMode  = 6;
	edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng1::BtnNewClick(TObject *Sender)
{
	if (!SaveStorage(1))
	{
		return;
	}

	//search dan
   	// DelInvalidNtHeader();
	querydan->Active = false;
	querydan->Active = true;
	DBNav->Enabled = false;
	String sql;
	sql = " select ID,Name from CUST_CustomerInfo where Type =1 order by name ";
	dsetSupplier->Active = false;
	dsetSupplier->CommandText = sql;
	dsetSupplier->Active = true;
	/*if (m_opmode == OPAddNtHeader && autologout) {
		AutologPro();
		UpdateProHeader();
	}*/

	RzToolButton5Click(BtnNew);
	edkcedu->Text = "";
	edxyedu->Text = "";
	edbond->Text = "";
	dblkpcbbSupplierID->KeyValue = 0;
	SaveOrNot = false;
	BtnSave->Enabled = true;
	dbnbedtAddCosts->Enabled = true;
	dblkpcbbSupplierID->Enabled = true;
	sbnewcustomer->Enabled = true;
	dbedtSupplySN->Enabled = true;
	dsetNtHeader->Edit();
	dsrcNtHeader->DataSet->FieldByName("AddCosts")->Value =  0.0;
	dsrcNtHeader->DataSet->FieldByName("Remarks")->Value =  "";
	dsrcNtHeader->DataSet->FieldByName("SupplySN")->Value =  "";
	dsetNtHeader->UpdateRecord();
	membk->Text = "";
	dbedtSupplySN->Text = "";
	RzEdit1->Text = "";
	editdanhao->Text = "";
	dbnbedtAddCosts->Value = 0.0;
	dblkpcbbStaffID->KeyValue = -1;
	dblkpcbbSupplierID->SetFocus();
	try {
    	qudetail->Active = false;
	} catch (...) {
	}
}
//---------------------------------------------------------------------------

void  TfrmStorageMng1::ModifyEnable()
{
	//

}
//---------------------------------------------------------------------------

void TfrmStorageMng1::UpdateWsaleDiscout(int mode)
{
	if (dsetNote->IsEmpty() ) {
		return;
	}
	if (dsetNote->Active && dsetNote->RecordCount >= 1)
	{
		adospupdatewsaleprice->Parameters->ParamByName("@storageNoteID")->Value
			= dsetNote->FieldByName("ID")->AsInteger;
		if (mode == 2) {
			adospupdatewsaleprice->Parameters->ParamByName("@mode")->Value
			= 2;
			adospupdatewsaleprice->Parameters->ParamByName("@stockprice")->Value
			= StrToFloat(editjingjiaprice->Text);
		}
		if (mode == 1) {
         	adospupdatewsaleprice->Parameters->ParamByName("@mode")->Value
			= 1;
			adospupdatewsaleprice->Parameters->ParamByName("@wsalediscount")->Value
			=  StrToFloat(editpxdiscount->Text);
		}
		if (mode == 0) {
			adospupdatewsaleprice->Parameters->ParamByName("@mode")->Value
			= 0;
			adospupdatewsaleprice->Parameters->ParamByName("@wsaleprice")->Value
			=  StrToFloat(editpxprice->Text);
		}
		if (mode == 3) {
			adospupdatewsaleprice->Parameters->ParamByName("@mode")->Value
			= 3;
			adospupdatewsaleprice->Parameters->ParamByName("@harmnum")->Value
			=  StrToFloat(editshun->Text);
		}
		if (mode == 4) {
			adospupdatewsaleprice->Parameters->ParamByName("@mode")->Value
			= 4;
			adospupdatewsaleprice->Parameters->ParamByName("@damagenum")->Value
			=  StrToFloat(editque->Text);
		}
		if (mode == 5) {
			 adospupdatewsaleprice->Parameters->ParamByName("@mode")->Value
			= 5;
			adospupdatewsaleprice->Parameters->ParamByName("@returnflag")->Value
			= cbreturn->Checked ;
		}
		if (mode == 6) {
			 adospupdatewsaleprice->Parameters->ParamByName("@mode")->Value
			= 6;
			adospupdatewsaleprice->Parameters->ParamByName("@lsdiscount")->Value
			= StrToFloat(edlsdiscount->Text);
		}
		if (mode == 7) {
			adospupdatewsaleprice->Parameters->ParamByName("@mode")->Value
			= 7;
			adospupdatewsaleprice->Parameters->ParamByName("@lsprice")->Value
			=  StrToFloat(edtlsprice->Text);
		}
		 adospupdatewsaleprice->ExecProc();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng1::editpxdiscountExit(TObject *Sender)
{
	double price;
	double pxprice;
	if (editpxdiscount->Text == "") {
		editpxdiscount->Text = "0.00";
	}
	price =  dbgrdNote->DataSource->DataSet->FieldByName("price")->AsFloat ;
	pxprice = price * StrToFloat(editpxdiscount->Text) * 0.01 ;
	editpxprice->Text =  FormatFloat("0.00",pxprice);

	UpdateWsaleDiscout(1);
	try
	{
		dsetNote->Edit();
		dsetNote->FieldByName("wsalediscount")->AsFloat = StrToFloat(editpxdiscount->Text);
	}catch(...)
	{}
	  //	dsetNote->
	  //	dsetNote->FieldByName("lsdiscount")->AsInteger =  totalfix;
	  //	dsetNote->Post();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng1::dbnbedtDiscountExit(TObject *Sender)
{


	double jinjia;
	double discount;
	double price ;
	UpdateNote();

	if (!dsetNote->IsEmpty() ) {
		if (editjingjiaprice->Text == "") {
			editjingjiaprice->Text = "0.00";
		}
		try {
			price =  dbgrdNote->DataSource->DataSet->FieldByName("price")->AsFloat ;
			jinjia = price * dbnbedtDiscount->Value * 0.01 ;
			editjingjiaprice->Text =  FormatFloat("0.00",jinjia);
			//yjpxdiscount();
		} catch (Exception &E) {
			logmessage = E.Message;
			AddEvent(3,"һ����ⴰ��",m_userID,m_storageID,logmessage,linfo.con);
		}
	}
		int amount;
		double totaldis,totalfix;

		price = dsetNote->FieldByName("price")->AsFloat ;
		discount =  dbnbedtDiscount->Value;
		amount = dbnbedtAmount->Value;
		totaldis = amount * price * discount * 0.01;
		totalfix = amount * price;


}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng1::editjingjiapriceExit(TObject *Sender)
{
	if (dsetNote->RecordCount == 0) {
		return;
	}
	if (editjingjiaprice->Text == ""){
		editjingjiaprice->Text = "0.00";
	}
	float price ;
	float discount;
	price = dbgrdNote->DataSource->DataSet->FieldByName("price")->AsFloat ;
	if (price != 0) {
		discount = StrToFloat(editjingjiaprice->Text)/price;

		dbnbedtDiscount->Value =  discount*100 ;
		//����DataSource
                 //.ToDouble()
		int amount;
		double totaldis,totalfix;
		amount = dbnbedtAmount->Value;

		totaldis = amount * StrToFloat(editjingjiaprice->Text) ;
		totalfix = amount * price;
		dsetNote->DisableControls();
		dsetNote->Edit();
		dsetNote->FieldByName("Discount")->AsFloat = discount*100;
		dsetNote->FieldByName("FixedPrice")->AsFloat =  totalfix;
		dsetNote->FieldByName("DiscountedPrice")->AsFloat = totaldis;
		dsetNote->Post();
		dsetNote->EnableControls();

		UpdateNote();
		GetHtHeaderTotal();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng1::editjingjiapriceKeyPress(TObject *Sender, wchar_t &Key)

{
    if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key !='.')&&(Key != '\b')) {
		Key = NULL;
	}

	if (Key == '\r')
	{
		Key = 0;
		if (chfoceset->Checked) {

			if (chpxdiscount->Checked ) {
				editpxdiscount->SetFocus();
			}
			else if (chpxprice->Checked ) {
				editpxprice->SetFocus();
			}
			else if (chlsdiscount->Checked ) {
				 edlsdiscount->SetFocus();
			}
			else if (chlsprice->Checked ) {
				edtlsprice->SetFocus();
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
			else if (chfsdiscount->Checked) {
				if (!dsetNote->Eof) {
					dbgrdNote->SetFocus();
					dsetNote->Next();
					dbgrdNote->SelectedRows->CurrentRowSelected = true;
					dbnbedtDiscount->SetFocus();
				}
			}
			else if (chjinjia->Checked ) {
            	if (!dsetNote->Eof) {
					dbgrdNote->SetFocus();
					dsetNote->Next();
					dbgrdNote->SelectedRows->CurrentRowSelected = true;
					editjingjiaprice->SetFocus();
				}
			}
		}
		else
		{
			Perform(WM_NEXTDLGCTL, 0, 0);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng1::editpxdiscountKeyPress(TObject *Sender, wchar_t &Key)

{
	if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key !='.')&&(Key != '\b')) {
		Key = NULL;
	}
	if (Key == '\r')
	{
		Key = 0;
		if (chfoceset->Checked) {
			if (chpxprice->Checked ) {
				editpxprice->SetFocus();
			}
			else if (chlsdiscount->Checked ) {
				 edlsdiscount->SetFocus();
			}
			else if (chlsprice->Checked ) {
				edtlsprice->SetFocus();
			}
			else if (chfsluru->Checked) {
				edtCatalog->SetFocus();
			}
			else if (chfsamount->Checked) {
				if (!dsetNote->Eof) {
					dbgrdNote->SetFocus();
					dsetNote->Next();
					dbgrdNote->SelectedRows->CurrentRowSelected = true;
					dbgrdNote->SetFocus();
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
			else if (chjinjia->Checked ) {
            	if (!dsetNote->Eof) {
					dbgrdNote->SetFocus();
					dsetNote->Next();
					dbgrdNote->SelectedRows->CurrentRowSelected = true;
					editjingjiaprice->SetFocus();
				}
			}
			else if (chpxdiscount->Checked) {
				if (!dsetNote->Eof) {
					dbgrdNote->SetFocus();
					dsetNote->Next();
					dbgrdNote->SelectedRows->CurrentRowSelected = true;
					editpxdiscount->SetFocus();
				}
			}
		}
		else
		{
			edlsdiscount->SetFocus();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng1::editpxpriceExit(TObject *Sender)
{
	if (dsetNote->RecordCount == 0 || editpxprice->Text == "") {
		return;
	}

	float price ;
	float discount;
	price = dbgrdNote->DataSource->DataSet->FieldByName("price")->AsFloat ;
	if (price != 0) {
		discount = StrToFloat(editpxprice->Text)/price;
		editpxdiscount->Text =  FormatFloat("0.00",discount*100).ToDouble();
		//editpxdiscount->Value =  FormatFloat("0.00",discount*100).ToDouble() ;
		//����DataSource

		UpdateWsaleDiscout(1);
		try
		{
			dsetNote->Edit();
			dsetNote->FieldByName("wsalediscount")->AsFloat = StrToFloat(editpxdiscount->Text);
		}catch(...)
		{}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng1::editpxpriceKeyPress(TObject *Sender, wchar_t &Key)
{
	if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key !='.')&&(Key != '\b')) {
		Key = NULL;
	}
	if (Key == '\r')
	{
		Key = 0;
		if (chfoceset->Checked) {
			if (chlsdiscount->Checked ) {
				 edlsdiscount->SetFocus();
			}
			else if (chlsprice->Checked ) {
				edtlsprice->SetFocus();
			}
			else if (chfsluru->Checked) {
				edtCatalog->SetFocus();
			}
			else if (chfsamount->Checked) {
				if (!dsetNote->Eof) {
					//dbgrdNote->SetFocus();
					dsetNote->Next();
					dbgrdNote->SelectedRows->CurrentRowSelected = true;
					dbgrdNote->SetFocus();
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
			else if (chjinjia->Checked ) {
            	if (!dsetNote->Eof) {
					dbgrdNote->SetFocus();
					dsetNote->Next();
					dbgrdNote->SelectedRows->CurrentRowSelected = true;
					editjingjiaprice->SetFocus();
				}
			}
			else if (chpxdiscount->Checked) {
				if (!dsetNote->Eof) {
					dbgrdNote->SetFocus();
					dsetNote->Next();
					dbgrdNote->SelectedRows->CurrentRowSelected = true;
					editpxdiscount->SetFocus();
				}
			}
			else if (chpxprice->Checked ) {
				if (!dsetNote->Eof) {
					dbgrdNote->SetFocus();
					dsetNote->Next();
					dbgrdNote->SelectedRows->CurrentRowSelected = true;
					editpxprice->SetFocus();
				}
			}
		}
		else
		{
			edlsdiscount->SetFocus();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng1::editshunExit(TObject *Sender)
{
	if (editshun->Text == "") {
		editshun->Text = "0";
	}
	UpdateWsaleDiscout(3);
   //	QryNtHeader();
   	try
	{
		dsetNote->Edit();
		dsetNote->FieldByName("harmnum")->AsFloat = StrToFloat(editshun->Text);
	}catch(...)
	{}

}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng1::editqueExit(TObject *Sender)
{
	if (editque->Text == "") {
		editque->Text = "0";
	}
	UpdateWsaleDiscout(4);
   //	QryNtHeader();
   	try
	{
		dsetNote->Edit();
		dsetNote->FieldByName("damagenum")->AsFloat = StrToFloat(editque->Text);
	}catch(...)
	{}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng1::editqueKeyPress(TObject *Sender, wchar_t &Key)
{
   if (Key == '\r')
	{
		Key = 0;

	   edtCatalog->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng1::editshunKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r')
	{
		Key = 0;
		Perform(WM_NEXTDLGCTL, 0, 0);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng1::cbreturnExit(TObject *Sender)
{
	UpdateWsaleDiscout(5);
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng1::cbbkstackIDSelect(TObject *Sender)
{
	/*stackchange = true;
	UpdateNote();
	stackchange = false;     */
	int stackid = (int)(cbbkstackID->Items->Objects[cbbkstackID->ItemIndex]);
	if (dsetNote->Active && dsetNote->RecordCount >= 1)
	{
        if (dbgrdNote->SelectedRows->Count == 0)
		{
			cmdUpdateNote->Parameters->ParamByName("@ID")->Value
				= dsetNote->FieldByName("ID")->AsInteger;
			cmdUpdateNote->Parameters->ParamByName("@Amount")->Value
				= abs(dsetNote->FieldByName("Amount")->AsInteger);
			cmdUpdateNote->Parameters->ParamByName("@Discount")->Value
				= fabs(dsetNote->FieldByName("Discount")->AsFloat);
			cmdUpdateNote->Parameters->ParamByName("@bkstackID")->Value = stackid;
			cmdUpdateNote->Parameters->ParamByName("@bkchange")->Value = 1;
			cmdUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 1;
			try
			{
				cmdUpdateNote->Execute();
			}
			__finally
			{
			}
		}
		else if (dbgrdNote->SelectedRows->Count > 0)
		{
			dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[0];
			cmdUpdateNote->Parameters->ParamByName("@ID")->Value
				= dsetNote->FieldByName("ID")->AsInteger;
			cmdUpdateNote->Parameters->ParamByName("@Amount")->Value
				= abs(dsetNote->FieldByName("Amount")->AsInteger);
			cmdUpdateNote->Parameters->ParamByName("@Discount")->Value
				= fabs(dsetNote->FieldByName("Discount")->AsFloat);
			cmdUpdateNote->Parameters->ParamByName("@bkstackID")->Value = stackid;
			cmdUpdateNote->Parameters->ParamByName("@bkchange")->Value = 1;
			cmdUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 1;
			try
			{
				cmdUpdateNote->Execute();
			}
			__finally
			{
			}
			for (int i=1; i < dbgrdNote->SelectedRows->Count; i++)
			{

				dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[i];
				cmdUpdateNote->Parameters->ParamByName("@ID")->Value
					= dsetNote->FieldByName("ID")->AsInteger;
				cmdUpdateNote->Parameters->ParamByName("@Amount")->Value
					= abs(dsetNote->FieldByName("Amount")->AsInteger);
				cmdUpdateNote->Parameters->ParamByName("@Discount")->Value
					= fabs(dsetNote->FieldByName("Discount")->AsFloat);
				cmdUpdateNote->Parameters->ParamByName("@bkstackID")->Value = stackid;
				cmdUpdateNote->Parameters->ParamByName("@bkchange")->Value = 1;
				cmdUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 1;
				try
				{
					cmdUpdateNote->Execute();
				}
				__finally
				{
				}
			}
		}
		else
			return;
		try {
        	QryNtHeader();
        } catch (...) {
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng1::BtnChangeOptionsClick(TObject *Sender)
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
		dbedtSupplySN->Enabled = true;
		dbnbedtAddCosts->Enabled = true;
		BtnSave->Enabled = true;
		SaveOrNot = false;
		BtnSave->Enabled = true;
		dblkpcbbSupplierID->Enabled = true;
		sbnewcustomer->Enabled = true;
}
//---------------------------------------------------------------------------

void  TfrmStorageMng1::AutologProA()
{
//
}
//---------------------------------------------------------------------------

void  TfrmStorageMng1::AutologProS(int supplier,int BkcatalogID)
{
	/*if (dsetNote->IsEmpty() ) {
        return;
	}

	}  */
}
//---------------------------------------------------------------------------

void  TfrmStorageMng1::AutologPro()
{
	/*if (dsetNote->IsEmpty() ) {
		return;
	}
	dsetNote->First();
	dsetNote->DisableControls();
	while (!dsetNote->Eof )
	{
		AutologProA();
		dsetNote->Next();
	}
	dsetNote->EnableControls();  */
}
//---------------------------------------------------------------------------

void  TfrmStorageMng1::UpdateProHeader()
{
	//
}
//---------------------------------------------------------------------------
void __fastcall TfrmStorageMng1::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

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


	if (Shift.Contains(ssAlt)&& Key ==81  ) {
		RzToolButton9->Click();
	}

	if (Shift.Contains(ssAlt)&& Key ==78  ) {
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssAlt)&& Key ==70  ) {
		BtnView1->Click();
	}
	if (Shift.Contains(ssAlt)&& Key ==90) {
		WindowState = wsNormal  ;
	}
}
//---------------------------------------------------------------------------
void TfrmStorageMng1::BatchsetWsaleDiscout(float pidiscount)
{

				adospupdatewsaleprice->Parameters->ParamByName("@storageNoteID")->Value
				= dsetNote->FieldByName("ID")->AsInteger;
				adospupdatewsaleprice->Parameters->ParamByName("@mode")->Value
				= 1;
				adospupdatewsaleprice->Parameters->ParamByName("@wsalediscount")->Value
				=  pidiscount;
				adospupdatewsaleprice->ExecProc();
}

//---------------------------------------------------------------------------
void TfrmStorageMng1::BatchsetLsDiscout(float lsdiscount)
{

				adospupdatewsaleprice->Parameters->ParamByName("@storageNoteID")->Value
				= dsetNote->FieldByName("ID")->AsInteger;
				adospupdatewsaleprice->Parameters->ParamByName("@mode")->Value
				= 6;
				adospupdatewsaleprice->Parameters->ParamByName("@lsdiscount")->Value
				=  lsdiscount;
				adospupdatewsaleprice->ExecProc();
}

//---------------------------------------------------------------------------



void __fastcall TfrmStorageMng1::dbgrdNoteMouseUp(TObject *Sender, TMouseButton Button,
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


void __fastcall TfrmStorageMng1::N9Click(TObject *Sender)
{
 //   dsetNote->SaveToFile("D:\\sd",pfADTG);
	if (BtnSave->Enabled) {
		MessageBoxA(0,"������δ���棬���ȱ��棡","��ʾ",MB_ICONASTERISK);
		return;
	}
	adospcopy->ProcedureName = "StickData";
	adospcopy->Parameters->Clear();
	adospcopy->Parameters->CreateParameter("@return",ftInteger,pdReturnValue,sizeof(int),-2);
	adospcopy->Parameters->CreateParameter("@mode",ftInteger,pdInput,sizeof(int),1);
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



void __fastcall TfrmStorageMng1::N8Click(TObject *Sender)
{
  	if (dsetNote->IsEmpty() ) {
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
void TfrmStorageMng1::addwsalediscount()
{
	AnsiString sql;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = m_con ;
	sql = "select wsaletype from BS_WsaleDiscount where stgid = " + IntToStr(m_storageID) + " and active = 1";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	float wsalediscount = 100;
	switch (aq->FieldByName("wsaletype")->AsInteger ) {
		case 1:
			sql = "select * from BS_WsaletypeDiscountInfo where type = 1 and stgid = " + IntToStr(m_storageID);
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();
			wsalediscount = dbnbedtDiscount->Value + aq->FieldByName("alldot")->AsFloat ;
			if (wsalediscount > 100) {
				wsalediscount = 100;
			}
			editpxdiscount->Text = FloatToStr(wsalediscount);
		break;
		case 2:
			if (dsetNote->FieldByName("PressID")->AsString != "") {
            	sql = "select * from BS_WsaletypeDiscountInfo where type = 2 and stgid = " + IntToStr(m_storageID) + " and pressid = " + dsetNote->FieldByName("PressID")->AsString ;
				aq->Close();
				aq->SQL->Clear();
				aq->SQL->Add(sql);
				aq->Open();
				wsalediscount = dbnbedtDiscount->Value + aq->FieldByName("pressdot")->AsFloat ;
            	if (wsalediscount > 100) {
					wsalediscount = 100;
				}
				editpxdiscount->Text = FloatToStr(wsalediscount);
			}
		break;
		case 3:
			if (dsetNote->FieldByName("smallBookTypeID")->AsString != "") {
            	sql = "select * from BS_WsaletypeDiscountInfo where type = 3 and stgid = " + IntToStr(m_storageID) + " and typeid = " + dsetNote->FieldByName("smallBookTypeID")->AsString ;
				aq->Close();
				aq->SQL->Clear();
				aq->SQL->Add(sql);
				aq->Open();
				wsalediscount = dbnbedtDiscount->Value + aq->FieldByName("typedot")->AsFloat ;
            	if (wsalediscount > 100) {
					wsalediscount = 100;
				}
				editpxdiscount->Text = FloatToStr(wsalediscount);
			}
		break;
		case 4:
			sql = "select * from BS_WsaletypeDiscountInfo where type = 4 and stgid = " + IntToStr(m_storageID) + " and supplierid = " + dsetSupplier->FieldByName("ID")->AsString ;
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();
			wsalediscount = dbnbedtDiscount->Value + aq->FieldByName("supplierdot")->AsFloat ;
			if (wsalediscount > 100) {
				wsalediscount = 100;
			}
			editpxdiscount->Text = FloatToStr(wsalediscount);
		break;
	default:
		;
	}
	delete aq;
}
//---------------------------------------------------------------------------

void TfrmStorageMng1::lastyjpxdiscount()
{
	AnsiString sql;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = m_con ;
	sql = "select top 1 wsalediscount from BS_StorageNote where BkInfoID = " + dsetNote->FieldByName("BkInfoID")->AsString + " and wsalediscount <> 0 order by ID DESC";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	float wsalediscount = 100;
	if (aq->RecordCount > 0) {
		wsalediscount =  aq->FieldByName("wsalediscount")->AsFloat;
	}
	delete aq;
	editpxdiscount->Text = FloatToStr(wsalediscount);
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


void __fastcall TfrmStorageMng1::BtnView1Click(TObject *Sender)
{
	Tfrmbookquery * frm = new Tfrmbookquery(Application,linfo.con,linfo.storageID);
	frm->ShowModal();
	delete frm;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng1::dbedtSupplySNExit(TObject *Sender)
{
	//UpdateNtHeader();
	dsetNtHeader->Edit();
	dsetNtHeader->FieldByName("SupplySN")->AsAnsiString = dbedtSupplySN->Text;
	dsetNtHeader->Post();
}
//---------------------------------------------------------------------------

void TfrmStorageMng1::GetHtHeaderTotal()
{
if (!dsetNtHeader->IsEmpty()) {

	  dsetGetHtHeaderTotal->Parameters->ParamByName("@mode")->Value = 1;
	  dsetGetHtHeaderTotal->Parameters->ParamByName("@ID")->Value = dsetNtHeader->FieldByName("ID")->AsInteger;
	  if (!dsetGetHtHeaderTotal->Active ) {
		dsetGetHtHeaderTotal->Active = true;
	  }else
	  {
		 dsetGetHtHeaderTotal->Active=false;
		 dsetGetHtHeaderTotal->Active = true;
	  }

}



}
void __fastcall TfrmStorageMng1::BtnSaveClick(TObject *Sender)
{
	if (!SaveOK()) {
		return;
	}
	edtCatalog->SetFocus();
}
//---------------------------------------------------------------------------
bool TfrmStorageMng1::SaveOK()
{
	if (dblkpcbbSupplierID->Text == "") {
		MessageBoxA(0,"��ѡ��Ӧ�̣�","��ʾ",MB_ICONASTERISK);
		return false;
	}
	if (!SupplierCreit(1)) {
		return false;
	}

			dsetNtHeader->Edit();
			dsetNtHeader->FieldByName("SupplierID")->AsInteger = dsetSupplier->FieldByName("ID")->AsInteger;
			dsetNtHeader->Post();

	if (dsetNote->RecordCount > 0) {



		if (dsetSupplier->FieldByName("ID")->AsInteger != beforesupplier) {
			ChangeSupplier();
			if (ChangeDisplay) {
				logmessage = "����ⵥ" + dsetNtHeader->FieldByName("StgNtCodeStr")->AsAnsiString ;
			}
			else
			{
				logmessage = "����ⵥ" + dsetNtHeader->FieldByName("StgNtCode")->AsAnsiString ;
			}
			logmessage = logmessage + "�Ĺ�Ӧ����" + beforesuppliername + "�޸�Ϊ" + dsetSupplier->FieldByName("Name")->AsAnsiString;
			AddEvent(1,"һ����ⴰ��",m_userID,m_storageID,logmessage,linfo.con);
			beforesupplier = dsetSupplier->FieldByName("ID")->AsInteger;
			UpdateNtHeader();
		}
		SaveOrNot = true;
		BtnSave->Enabled = false;
		dbnbedtAddCosts->Enabled = false;

		dblkpcbbSupplierID->Enabled = false;
		sbnewcustomer->Enabled = false;
		return true;
	}
	if (dsetNtHeader->FieldByName("StgNtCode")->AsInteger    != 0 ) {    //��һ���ǿհ׵�

		SaveOrNot = true;
		BtnSave->Enabled = false;
		dbnbedtAddCosts->Enabled = false;
		dblkpcbbSupplierID->Enabled = false;
		sbnewcustomer->Enabled = false;
			QryNtHeader();
		return true;
	}
	spsave->Parameters->ParamByName("@MODE")->Value = 1;
	spsave->Parameters->ParamByName("@ID")->Value = dsetNtHeader->FieldByName("ID")->AsInteger ;
	spsave->Parameters->ParamByName("@STGID")->Value = linfo.storageID;
	spsave->Parameters->ParamByName("@TYPE")->Value = 1;
	spsave->Parameters->ParamByName("@CODEMODE")->Value = 0;
	spsave->Parameters->ParamByName("@ReturnCode")->Value = 0;
	spsave->Parameters->ParamByName("@ReturnCode2")->Value = 0;
	spsave->ExecProc() ;

	if (ChangeDisplay) {
		logmessage = "�����ⵥ" + spsave->Parameters->ParamByName("@ReturnCode2")->Value ;
	}
	else
	{
		logmessage = "�����ⵥ" + spsave->Parameters->ParamByName("@ReturnCode")->Value ;
	}
	AddEvent(1,"һ����ⴰ��",m_userID,m_storageID,logmessage,linfo.con);
	historyview();     //SaveBenDan
	dbedtStgNtCode->Text = spsave->Parameters->ParamByName("@ReturnCode")->Value ;
	editdanhao->Text = spsave->Parameters->ParamByName("@ReturnCode2")->Value ;

	SaveOrNot = true;
	BtnSave->Enabled = false;
	dbnbedtAddCosts->Enabled = false;

	dblkpcbbSupplierID->Enabled = false;
	sbnewcustomer->Enabled = false;
	QryNtHeader();
	return true;
}

//---------------------------------------------------------------------------

 bool TfrmStorageMng1::SaveStorage(int mode)
{
    if (dsrcNote->DataSet->IsEmpty() ) {
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
            if (ChangeDisplay) {
				logmessage = "ȡ��������ⵥ" + dsetNtHeader->FieldByName("StgNtCodeStr")->AsAnsiString ;
			}
			else
			{
				logmessage = "ȡ��������ⵥ" + dsetNtHeader->FieldByName("StgNtCode")->AsAnsiString ;
			}
			AddEvent(1,"һ����ⴰ��",m_userID,m_storageID,logmessage,linfo.con);

			spsave->Parameters->ParamByName("@MODE")->Value = 2;
			spsave->Parameters->ParamByName("@ID")->Value = dsetNtHeader->FieldByName("ID")->AsInteger ;
			spsave->Parameters->ParamByName("@STGID")->Value = 0;
			spsave->Parameters->ParamByName("@TYPE")->Value = 1;
			spsave->Parameters->ParamByName("@CODEMODE")->Value = 0;
			spsave->Parameters->ParamByName("@ReturnCode")->Value = 0;
			spsave->Parameters->ParamByName("@ReturnCode2")->Value = 0;
			spsave->ExecProc() ;
		  }
	  }
	}else return true;

}
//---------------------------------------------------------------------------


void __fastcall TfrmStorageMng1::RzEdit1KeyPress(TObject *Sender, wchar_t &Key)
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
		sql = " select * from CUST_CustomerInfo where Type =1 and Name like '%"+ RzEdit1->Text.Trim() + "%' order by name";
		dsetSupplier->Active = false;
		dsetSupplier->CommandText = sql;
		dsetSupplier->Active = true;
		dsetSupplier->First();
		dblkpcbbSupplierID->KeyValue = dsetSupplier->FieldByName("ID")->AsInteger ;
		if (!SupplierCreit(1)) {
			return;
		}
		dsetNtHeader->Edit();
		dsetNtHeader->FieldByName("SupplierID")->AsInteger = dsetSupplier->FieldByName("ID")->AsInteger;
		dsetNtHeader->Post();
		dblkpcbbSupplierID->SetFocus();
	}
}
//---------------------------------------------------------------------------
bool TfrmStorageMng1::SupplierCreit(int modle)
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
	if (modle == 0) {
		return true;
	}
	else
	{
		if (query->FieldByName("shiyang")->AsFloat > query->FieldByName("CreditMoney")->AsFloat && query->FieldByName("CreditMoney")->AsFloat > 0 ) {
			if (MessageBoxA(0,"�ù�Ӧ�̵Ŀ��ʵ�󳬹����ö�ȣ��Ƿ����?","ѯ��",MB_ICONQUESTION|MB_OKCANCEL)==1 )
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
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmStorageMng1::dblkpcbbSupplierIDExit(TObject *Sender)
{
	//dblkpcbbSupplierID->Enabled = sbnewcustomer->Enabled ;

}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng1::dbnbedtAddCostsExit(TObject *Sender)
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


void __fastcall TfrmStorageMng1::dbnbedtAddCostsKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		membk->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng1::BtnReminderClick(TObject *Sender)
{
	TControl* con = dynamic_cast<TControl*>(Sender);
	if (con != NULL)
	{
		dbgrdNote->SetFocus();
		ChangeOpmode(con->Tag);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng1::DBNavClick(TObject *Sender, TNavigateBtn Button)
{
   AnsiString code ;
   code = querydan->FieldByName("StgNtCode")->AsAnsiString ;
   editdanhao->Text = querydan->FieldByName("StgNtCodeStr")->AsAnsiString ;
   QryNtHeader(code,false);

}
//---------------------------------------------------------------------------
void TfrmStorageMng1::ChangeSupplier()
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
			/*if (autologout) {
				AutologProS(supplierid,BkcatalogID);
			} */
			sql = "select ID from STK_BookInfo where BkcatalogID = " + dsetNote->FieldByName("BkcatalogID")->AsString + " and SupplierID = " + IntToStr(supplier) + " and BkstackID = " + dsetNote->FieldByName("BkstackID")->AsString;
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

void __fastcall TfrmStorageMng1::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng1::dbgrdNoteTitleClick(TColumn *Column)
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

void __fastcall TfrmStorageMng1::edlsdiscountExit(TObject *Sender)
{
	float price;
	float lsprice;
	if (edlsdiscount->Text == "") {
		edlsdiscount->Text = "0.00";
	}
	price =  dbgrdNote->DataSource->DataSet->FieldByName("price")->AsFloat ;
	lsprice = price * StrToFloat(edlsdiscount->Text) * 0.01 ;
	edtlsprice->Text =  FormatFloat("0.00",lsprice);

	UpdateWsaleDiscout(6);
	try
	{
		dsetNote->Edit();
		dsetNote->FieldByName("lsdiscount")->AsFloat = StrToFloat(edlsdiscount->Text);
	}catch(...)
	{}
}
//---------------------------------------------------------------------------

void TfrmStorageMng1::FormView()
{
	/*AnsiString sql;
	sql = "select name,state from BS_SYS_Formview where stgid = " + IntToStr(m_storageID) + " and ParentID = 5";
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
	} */
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng1::dbnbedtDiscountKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r')
	{
		Key = 0;
		if (chfoceset->Checked) {
			if (chpxdiscount->Checked ) {
				editpxdiscount->SetFocus();
			}
			else if (chpxprice->Checked ) {
				editpxprice->SetFocus();
			}
			else if (chlsdiscount->Checked ) {
				 edlsdiscount->SetFocus();
			}
			else if (chlsprice->Checked ) {
				edtlsprice->SetFocus();
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
			Perform(WM_NEXTDLGCTL, 0, 0);
		}
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "0.00";
		historyview();
	}
}
//---------------------------------------------------------------------------

void  TfrmStorageMng1::operterview(int operterid)
{
	TADOQuery *aq  = new TADOQuery(Application);
	aq->Connection = m_con ;
	AnsiString sql;
	sql = "select name from sys_user where id = " + IntToStr(operterid);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	lblOpName->Caption = aq->FieldByName("name")->AsString;
	delete aq;
}
//---------------------------------------------------------------------------



void __fastcall TfrmStorageMng1::membkExit(TObject *Sender)
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

void __fastcall TfrmStorageMng1::membkKeyPress(TObject *Sender, wchar_t &Key)
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


void __fastcall TfrmStorageMng1::SpeedButton1Click(TObject *Sender)
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

void __fastcall TfrmStorageMng1::chfsluruClick(TObject *Sender)
{
	if (!chfsluru->Checked && !chfsamount->Checked && !chfsdiscount->Checked && !chpxdiscount->Checked && !chpxprice->Checked && !chlsdiscount->Checked && !chlsprice->Checked && !chjinjia->Checked ) {
		chfoceset->Checked = false;
	}
	else
	{
		chfoceset->Checked = true;
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmStorageMng1::N10Click(TObject *Sender)
{
	lblCatalog->Caption = "����";
	m_catalogSearchMode  = 5;
	edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------


void __fastcall TfrmStorageMng1::FormShow(TObject *Sender)
{
	RzEdit1->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng1::edlsdiscountKeyPress(TObject *Sender, wchar_t &Key)

{
	if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key !='.')&&(Key != '\b')) {
	  	Key = NULL;
	}
	if (Key == '\r')
	{
		Key = 0;

		if (chfoceset->Checked) {
			if (chlsprice->Checked ) {
				edtlsprice->SetFocus();
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
			else if (chfsdiscount->Checked) {
				if (!dsetNote->Eof) {
					dbgrdNote->SetFocus();
					dsetNote->Next();
					dbgrdNote->SelectedRows->CurrentRowSelected = true;
					dbnbedtDiscount->SetFocus();
				}
			}
			else if (chjinjia->Checked ) {
				if (!dsetNote->Eof) {
					dbgrdNote->SetFocus();
					dsetNote->Next();
					dbgrdNote->SelectedRows->CurrentRowSelected = true;
					editjingjiaprice->SetFocus();
				}
			}
			else if (chpxdiscount->Checked) {
				if (!dsetNote->Eof) {
					dbgrdNote->SetFocus();
					dsetNote->Next();
					dbgrdNote->SelectedRows->CurrentRowSelected = true;
					editpxdiscount->SetFocus();
				}
			}
            else if (chpxprice->Checked ) {
				if (!dsetNote->Eof) {
					dbgrdNote->SetFocus();
					dsetNote->Next();
					dbgrdNote->SelectedRows->CurrentRowSelected = true;
					editpxprice->SetFocus();
				}
			}
			else if (chlsdiscount->Checked ) {
				if (!dsetNote->Eof) {
					dbgrdNote->SetFocus();
					dsetNote->Next();
					dbgrdNote->SelectedRows->CurrentRowSelected = true;
					edlsdiscount->SetFocus();
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

void __fastcall TfrmStorageMng1::edtlspriceKeyPress(TObject *Sender, wchar_t &Key)

{
	if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key !='.')&&(Key != '\b')) {
		Key = NULL;
	}
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
			else if (chjinjia->Checked ) {
            	if (!dsetNote->Eof) {
					dbgrdNote->SetFocus();
					dsetNote->Next();
					dbgrdNote->SelectedRows->CurrentRowSelected = true;
					editjingjiaprice->SetFocus();
				}
			}
			else if (chpxdiscount->Checked) {
				if (!dsetNote->Eof) {
					dbgrdNote->SetFocus();
					dsetNote->Next();
					dbgrdNote->SelectedRows->CurrentRowSelected = true;
					editpxdiscount->SetFocus();
				}
			}
			else if (chpxprice->Checked ) {
				if (!dsetNote->Eof) {
					dbgrdNote->SetFocus();
					dsetNote->Next();
					dbgrdNote->SelectedRows->CurrentRowSelected = true;
					editpxprice->SetFocus();
				}
			}
			else if (chlsdiscount->Checked ) {
				if (!dsetNote->Eof) {
					dbgrdNote->SetFocus();
					dsetNote->Next();
					dbgrdNote->SelectedRows->CurrentRowSelected = true;
					edlsdiscount->SetFocus();
				}
			}
			else if (chlsprice->Checked ) {
				if (!dsetNote->Eof) {
					dbgrdNote->SetFocus();
					dsetNote->Next();
					dbgrdNote->SelectedRows->CurrentRowSelected = true;
					edtlsprice->SetFocus();
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

void __fastcall TfrmStorageMng1::BtnBulletsClick(TObject *Sender)
{
	/*if (dsetNtHeader->IsEmpty() || dsetNote->IsEmpty()) {
		return;
	}
	AnsiString sql;
	sql = "exec USP_BS_fenfa " +  IntToStr(m_storageID) + ",0,0," + dsetNtHeader->FieldByName("id")->AsString ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	Tfrmunitorder * frm = new Tfrmunitorder(Application,m_con,dsetNtHeader->FieldByName("id")->AsInteger );
	frm->rkcode = editdanhao->Text;
	frm->ShowModal();
	delete frm;    */
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng1::N11Click(TObject *Sender)
{
	/*if (N11->Checked ) {
		N11->Checked = false;
	}
	else
	{
		N11->Checked = true;
	}   */
}
//---------------------------------------------------------------------------
void __fastcall TfrmStorageMng1::dbgrdNoteDrawColumnCell(TObject *Sender, const TRect &Rect,
          int DataCol, TColumn *Column, TGridDrawState State)
{
	/*if (strlist->IndexOf(dbgrdNote->DataSource->DataSet->FieldByName("BkcatalogID")->AsString) != -1) {
		dbgrdNote->Canvas->Font->Color = clRed ;
		dbgrdNote->Canvas->FillRect(Rect);
		dbgrdNote->DefaultDrawColumnCell(Rect,DataCol,Column,State);
	}
	else
	{
		dbgrdNote->DefaultDrawColumnCell(Rect,DataCol,Column,State);
	}   */
}
//---------------------------------------------------------------------------


void __fastcall TfrmStorageMng1::N12Click(TObject *Sender)
{
	if (dsetNote->IsEmpty() ) {
		return;
	}
	Tfrmbookhistory *frm = new Tfrmbookhistory(Application,m_con,m_storageID,dsetNote->FieldByName("BkcatalogID")->AsInteger );
	frm->ShowModal();
	delete frm;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng1::BtnTileClick(TObject *Sender)
{
	if (dsetNtHeader->IsEmpty() || dsetNote->IsEmpty()) {
		return;
	}
	AnsiString sql;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = m_con ;
	sql = "delete from BS_StorageFenfa where userid = " + IntToStr(m_userID) ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	sql = "insert into BS_StorageFenfa(Bkinfoid,userid,Stkamount,Amount,Outstgid) "
			" select BS_StorageNote.bkinfoid," + IntToStr(m_userID) + ",stk_bookinfo.amount as stkamount,BS_StorageNote.amount," + IntToStr(m_storageID) +
			" from BS_StorageNote left join stk_bookinfo on BS_StorageNote.bkinfoid = stk_bookinfo.id "
			" where BS_StorageNote.StgNtHeaderID = " + dsetNtHeader->FieldByName("ID")->AsAnsiString ;
    aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	delete aq;
	TfrmRkFenfa * frm = new TfrmRkFenfa(Application,m_con,m_userID,m_storageID);
	frm->CodeStr = editdanhao->Text ;
	frm->ShowModal();
	delete frm;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng1::dtpbackdateCloseUp(TObject *Sender)
{
	if (dsetNote->IsEmpty() )
	{
		return;
	}
	String ids = "";
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
	if (ids == "") {
		return;
	}
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = m_con ;
	AnsiString sql;
	sql = "update bs_storagenote set returndate = '" + DateToStr(dtpbackdate->Date) + "' where id in (" + ids + ")";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	delete aq;
	QryNtHeader();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng1::dblkpcbbStaffIDExit(TObject *Sender)
{
	dsetNtHeader->Edit();
	dsetNtHeader->FieldByName("StaffID")->AsInteger = dsetStaff->FieldByName("ID")->AsInteger;
	dsetNtHeader->Post();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng1::neamountExit(TObject *Sender)
{
		  if (dsetNote->RecordCount== 0) {
           return;
	  }


		double price,discount;
		int amount;
		double totaldis,totalfix;

		price = dsetNote->FieldByName("price")->AsFloat ;
		discount =  dsetNote->FieldByName("Discount")->AsFloat;
		amount = dbnbedtAmount->Value;
		totaldis = amount * price * discount * 0.01;
		totalfix = amount * price;
	  // // dsetNote->Post()
	  // dsetNote->DisableControls();
		dsetNote->Edit();
		dsetNote->FieldByName("Amount")->AsInteger = amount;
		dsetNote->FieldByName("FixedPrice")->AsInteger =  totalfix;
		dsetNote->FieldByName("DiscountedPrice")->AsInteger = totaldis;
		dsetNote->Post();
	//	dsetNote->EnableControls();
		 UpdateNote();
		GetHtHeaderTotal();


}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng1::nediscountExit(TObject *Sender)
{

	double jinjia;
	double discount;
	double price ;


	if (dsetNote->RecordCount == 0) {
		return;
	}
	if (!dsetNote->IsEmpty() ) {
		if (editjingjiaprice->Text == "") {
			editjingjiaprice->Text = "0.00";
		}
		try {
			price =  dbgrdNote->DataSource->DataSet->FieldByName("price")->AsFloat ;
			jinjia = price * dbnbedtDiscount->Value * 0.01 ;
			editjingjiaprice->Text =  FormatFloat("0.00",jinjia);
		} catch (Exception &E) {
			logmessage = E.Message;
			AddEvent(3,"һ����ⴰ��",m_userID,m_storageID,logmessage,linfo.con);
		}
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
//---------------------------------------------------1------------------------

void __fastcall TfrmStorageMng1::neamountKeyPress(TObject *Sender, wchar_t &Key)
{
		if (Key == '\r')
	{
		Key = 0;

		if (chfoceset->Checked) {
			if (chfsdiscount->Checked) {
				Perform(WM_NEXTDLGCTL, 0, 0);
			}
			else if (chjinjia->Checked ) {
            	editjingjiaprice->SetFocus();
			}
			else if (chpxdiscount->Checked ) {
				editpxdiscount->SetFocus();
			}

			else if (chpxprice->Checked ) {
				editpxprice->SetFocus();
			}
			else if (chlsdiscount->Checked ) {
				 edlsdiscount->SetFocus();
			}
			else if (chlsprice->Checked ) {
            	edtlsprice->SetFocus();
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
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng1::nediscountKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r')
	{
		Key = 0;
		if (chfoceset->Checked) {
			if (chjinjia->Checked ) {
				editjingjiaprice->SetFocus();
			}
			else if (chpxdiscount->Checked ) {
				editpxdiscount->SetFocus();
			}
			else if (chpxprice->Checked ) {
				editpxprice->SetFocus();
			}
			else if (chlsdiscount->Checked ) {
				 edlsdiscount->SetFocus();
			}
			else if (chlsprice->Checked ) {
				edtlsprice->SetFocus();
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
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng1::edtlspriceExit(TObject *Sender)
{
	if (dsetNote->RecordCount == 0 || edtlsprice->Text == "") {
		return;
	}

	float price ;
	float discount;
	price = dbgrdNote->DataSource->DataSet->FieldByName("price")->AsFloat ;
	if (price != 0) {
		discount = StrToFloat(edtlsprice->Text)/price;
		edlsdiscount->Text =  FormatFloat("0.00",discount*100).ToDouble();
		//editpxdiscount->Value =  FormatFloat("0.00",discount*100).ToDouble() ;
		//����DataSource

		UpdateWsaleDiscout(6);
		try
		{
			dsetNote->Edit();
			dsetNote->FieldByName("lsdiscount")->AsFloat = StrToFloat(edlsdiscount->Text);
		}catch(...)
		{}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng1::BtnSetTabsClick(TObject *Sender)
{
	if (dsetNtHeader->IsEmpty() || dsetNote->IsEmpty()) {
		return;
	}

	Tfrmunitinorder * frm = new Tfrmunitinorder(Application,m_con,dsetNtHeader->FieldByName("id")->AsInteger,m_storageID );
	frm->userid = m_userID ;
	frm->rkcode = editdanhao->Text;
	frm->ShowModal();
	delete frm;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng1::N13Click(TObject *Sender)
{
	if (dsetNote->IsEmpty() ) {
		return;
	}
	AnsiString catalogid,sql;
	catalogid = "-1";
	dsetNote->DisableControls();
	if (dbgrdNote->SelectedRows->Count > 0) {
		for (int i=0; i < dbgrdNote->SelectedRows->Count; i++)
		{
			dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[i];
			catalogid = catalogid + "," + dsetNote->FieldByName("ID")->AsString;
		}
	}
	else
	{
		catalogid = catalogid + "," + dsetNote->FieldByName("ID")->AsString;
	}
	dsetNote->EnableControls();
	sql = "delete from bs_userbarcode where userid = " + IntToStr(m_userID);
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->ExecSQL();
	sql = "insert into bs_userbarcode(Name,UserBarcode,amount,userid,Price) select bs_bookcatalog.name,bs_bookcatalog.userbarcode,bs_storagenote.amount," + IntToStr(m_userID) +
		",bs_bookcatalog.price from bs_storagenote left join stk_bookinfo on bs_storagenote.bkinfoid = stk_bookinfo.id "
		" left join bs_bookcatalog on stk_bookinfo.bkcatalogid = bs_bookcatalog.id where bs_storagenote.id in(" + catalogid + ")";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->ExecSQL();
	Tfrmprintbarcode *frm = new Tfrmprintbarcode(Application,m_con,m_userID);
	frm->ShowModal();
	delete frm;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng1::CheckBox1Click(TObject *Sender)
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

void __fastcall TfrmStorageMng1::dsetNoteBeforeScroll(TDataSet *DataSet)
{
	scroll = 1;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng1::dsrcNoteDataChange(TObject *Sender, TField *Field)

{
	if (scroll == 1) {
		grdCellClick();
		//ShowMessage("DataChange");
		scroll = 0;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStorageMng1::dblkpcbbSupplierIDClick(TObject *Sender)
{
	SupplierCreit(0);
}
//---------------------------------------------------------------------------



