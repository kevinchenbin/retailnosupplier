//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "RetailMngForm.h"
#include "SetNotesForm.h"
#include "mytrace.h"
#include <StrUtils.hpp>
//#include "customer\customer.h"
//#include "SelectCustomerForm.h"
#include "MixedRecMoneyForm.h"
#include "SelectMemberForm.h"
#include "..\common\Print.h"
#include "SelectCatalogForm.h"
#include "..\membermanager\MemberCard.h"
#include "bookup.h"
#include "WholesaleMngForm.h"
#include   <math.h>
#include "bookQuery.h"
#include "..\membermanager\MemberForm.h"
#include "sendbookselect.h"
#include "Addsyslog.h"
#include "retailbookup.h"
#include "GetBsset.h"
#include "MemberResult.h"
#include "QryCodeForm.h"
 #include<string>
#include "MemberOrder.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "MDIChild"
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "RzDBCmbo"
#pragma link "RzDBEdit"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzDBGrid"
#pragma link "RzDBLbl"
#pragma link "RzCommon"
#pragma link "RzDBLook"
#pragma link "RzRadChk"
#pragma link "frxClass"
#pragma link "frxDBSet"
#pragma resource "*.dfm"
TfrmRetailMng *frmRetailMng;
//---------------------------------------------------------------------------

__fastcall TfrmRetailMng::TfrmRetailMng(TComponent* Owner)
	: TfrmMDIChild(Owner)
	, m_catalogSearchMode(0)
	, m_bsmode(0)
	, m_opmode(0)
	, m_supplierID(-1)
	, m_cash(0)
	, m_card(0)
	,m_weixi(0)
	,m_zfb(0)
{
	m_module = MTRetailMng;
	retaildiscountchange = true;
	WriteConfig();
	shoukuan = 0.00;
	tishi = true;
	//dblkpcbbBkstackID->Enabled = false;
	dbgrdNote->OnDrawColumnCell=dbgrdNoteDrawColumnCell;
	IsFirst=true;
}
//---------------------------------------------------------------------------
void   TfrmRetailMng::OpenMoneyBoxUSB()
{
FARPROC  lpFarProc1box,lpFarProc1usb;
//char *(*GetUSBInfos)();
bool (*OpenMoneyBox)(char *);
char * usbinfo;

  try
	{
		hl = ::LoadLibrary("USBCUM.dll");
		lpFarProc1usb = GetProcAddress(hl,"OpenMoneyBox");

        //com_init = (bool(__cdecl *)(int))lpFarProc1;
		OpenMoneyBox = (bool (__cdecl *)(char *))lpFarProc1usb;
		   //	com_send = (bool(__cdecl *)(String,int))lpFarProc3;
     //   com_clearDisplay = (bool(__cdecl *)())lpFarProc4;
	  //  com_changebr = (bool(__cdecl *)())lpFarProc5;

		// usbinfo = GetUSBInfos();
           OpenMoneyBox(USBInfoOpenBOX.c_str());
         FreeLibrary(hl);
	}
	catch(Exception &e)
	{
		ShowMessage(e.Message);
	}


}
void TfrmRetailMng::init_ClientDisplay(int ComNum)//��ʼ���˿���ʾ��
{
	try
	{
		hl = ::LoadLibrary("ClientDisplay.dll");
		lpFarProc1 = GetProcAddress(hl,"com_init");
		lpFarProc2 = GetProcAddress(hl,"com_rest");
		lpFarProc3 = GetProcAddress(hl,"com_send");
		lpFarProc4 = GetProcAddress(hl,"com_clearDisplay");
		lpFarProc5 = GetProcAddress(hl,"com_changebr");

		com_init = (bool(__cdecl *)(int))lpFarProc1;
		com_rest = (bool(__cdecl *)())lpFarProc2;
		com_send = (bool(__cdecl *)(String,int))lpFarProc3;
		com_clearDisplay = (bool(__cdecl *)())lpFarProc4;
		com_changebr = (bool(__cdecl *)())lpFarProc5;
	//	  com_send("8.9.9.9",1);
	//  int a=	com_init(ComNum);
	  // 	com_changebr();
	  //	com_send("0.00",0);
			//	FreeLibrary(hl);
	}
	catch(Exception &e)
	{
		ShowMessage(e.Message);
	}
}
//---------------------------------------------------------------------------

void TfrmRetailMng::BatchSetNotes(int amount, float discount, int mode)
{
	if (Label2->Caption == "��������") {
		amount = abs(amount);
	}
	else
	{
    	amount = -abs(amount);
	}
	if (dsetNote->Active && dsetNote->RecordCount >= 1)
	{
    	String ids = "";
		if (dbgrdNote->SelectedRows->Count == 0)
		{
			if (mode != 3) {
				if (dsetNote->FieldByName("Amount")->AsInteger < 0 && Label2->Caption == "��������") {
					ShowMsg(Handle ,"��ǰ����״̬�����˻����ݣ�",3);
					return;
				}
				if (dsetNote->FieldByName("Amount")->AsInteger > 0 && Label2->Caption == "�����˻�") {
					ShowMsg(Handle ,"��ǰ�˻�״̬�����������ݣ�",3);
					return;
				}
			}
			if (mode != 2) {
				if (DiscountEnable(discount,dsetNote->FieldByName("BkcatalogID")->AsInteger)) {
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
			if (mode != 3) {
				if (dsetNote->FieldByName("Amount")->AsInteger < 0 && Label2->Caption == "��������") {
					ShowMsg(Handle ,"��ǰ����״̬�����˻����ݣ�",3);
					return;
				}
				if (dsetNote->FieldByName("Amount")->AsInteger > 0 && Label2->Caption == "�����˻�") {
					ShowMsg(Handle ,"��ǰ�˻�״̬�����������ݣ�",3);
					return;
				}
			}
			if (mode != 2) {
				if (DiscountEnable(discount,dsetNote->FieldByName("BkcatalogID")->AsInteger)) {
					ids = ids + dsetNote->FieldByName("ID")->AsString;
				}
			}
			else
			{
				ids = dsetNote->FieldByName("ID")->AsString;
			}

			for (int i=1; i < dbgrdNote->SelectedRows->Count; i++)
			{
				dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[i];
                if (mode != 3) {
					if (dsetNote->FieldByName("Amount")->AsInteger < 0 && Label2->Caption == "��������") {
						ShowMsg(Handle ,"��ǰ����״̬�����˻����ݣ�",3);
						return;
					}
					if (dsetNote->FieldByName("Amount")->AsInteger > 0 && Label2->Caption == "�����˻�") {
						ShowMsg(Handle ,"��ǰ�˻�״̬�����������ݣ�",3);
						return;
					}
				}

				if (mode != 2) {
					if (DiscountEnable(discount,dsetNote->FieldByName("BkcatalogID")->AsInteger)) {
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

		switch(mode)
		{
		case 1://���߾�����
			cmdBatchUpdateNote->Parameters->ParamByName("@IDS")->Value = ids;
			cmdBatchUpdateNote->Parameters->ParamByName("@Amount")->Value = amount;
			cmdBatchUpdateNote->Parameters->ParamByName("@Discount")->Value = discount;
            cmdBatchUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 3;
			cmdBatchUpdateNote->Execute();
			try
			{
			  //	LockWindowUpdate(dbgrdNote->Handle);//����ָ�����ڣ���ֹ�����¡�
				QryNtHeader();
			}
			__finally
			{
			  //	LockWindowUpdate(NULL);
			}
			break;
		case 2://ֻ����Amount
			cmdBatchUpdateNote->Parameters->ParamByName("@IDS")->Value = ids;
			cmdBatchUpdateNote->Parameters->ParamByName("@Amount")->Value = amount;
			cmdBatchUpdateNote->Parameters->ParamByName("@Discount")->Value = "";
			cmdBatchUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 3;
			cmdBatchUpdateNote->Execute();
			try
			{
			   //	LockWindowUpdate(dbgrdNote->Handle);//����ָ�����ڣ���ֹ�����¡�
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
			cmdBatchUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 3;
			cmdBatchUpdateNote->Execute();
			try
			{
			  //	LockWindowUpdate(dbgrdNote->Handle);//����ָ�����ڣ���ֹ�����¡�
				QryNtHeader();
			}
			__finally
			{
			  //	LockWindowUpdate(NULL);
			}
			break;
		default:
			break;
		}
	}
}
//---------------------------------------------------------------------------
void TfrmRetailMng::QryNtHeader(String code, bool qrybkstack)
{
	spQryNtHeader->Active = false;
	spQryNtHeader1->Active = false;
	spQryNtHeader1->Parameters->ParamByName("@NtCode")->Value = code;
	spQryNtHeader1->Parameters->ParamByName("@Bsmode")->Value = 3;
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
		dsetNote->AfterScroll = dsetNoteAfterScroll;
		nummayang->Value = dsetNtHeader->FieldByName("TotalFixedPrice")->AsExtended;
		numceshu->Value = dsetNtHeader->FieldByName("TotalAmount")->AsInteger;
		edname->Text = dsetNtHeader->FieldByName("MemberName")->AsAnsiString ;
		edyue->Text = FormatFloat("0.0",dsetNtHeader->FieldByName("Balance")->AsFloat);
		edtype->Text = dsetNtHeader->FieldByName("typename")->AsAnsiString ;
		edcard->Text =  dsetNtHeader->FieldByName("CardSN")->AsAnsiString ;
		edjifen->Text = dsetNtHeader->FieldByName("Memberdot")->AsAnsiString ;
		edyouxiaodate->Text = dsetNtHeader->FieldByName("youxiaodate")->AsAnsiString ;
		edTotalConsumption->Text = dsetNtHeader->FieldByName("TotalConsumption")->AsAnsiString ;
		/*if (qrybkstack)
		{
			QryBkstack();
		} */
		/*if (dsetNtHeader->FieldByName("State")->AsInteger == 1 ) {

			dbnbedtReceivableMoney->Value = dsetNtHeader->FieldByName("TotalDiscountedPrice")->AsExtended;
			numedtOdd->Value = 0.00;
			numedtPaidinMoney->Value = 0.00;
		}
		else
		{
			dbnbedtReceivableMoney->Value = dsetNtHeader->FieldByName("nochecked")->AsExtended ;
			numedtOdd->Value = 0.00;
			numedtPaidinMoney->Value = 0.00;
		} */
		if (dsetNtHeader->FieldByName("State")->AsInteger == 1 ) {
				dbnbedtReceivableMoney->Value = dsetNtHeader->FieldByName("TotalDiscountedPrice")->AsExtended ;
				numedtPaidinMoney->Enabled = false;
				//numedtOdd->Value = 0.00;
				//numedtPaidinMoney->Value = 0.00;
			}
			else
			{
				dbnbedtReceivableMoney->Value = dsetNtHeader->FieldByName("nochecked")->AsExtended ;
                numedtPaidinMoney->Enabled = true;
				//numedtOdd->Value = 0.00;
				//numedtPaidinMoney->Value = 0.00;
			}
		/*if (dsetNtHeader->FieldByName("nochecked")->AsFloat != 0 ) {
			dbnbedtReceivableMoney->Value =  dsetNtHeader->FieldByName("nochecked")->AsFloat ;
		}
		else
		{
			dbnbedtReceivableMoney->Value = dsetNtHeader->FieldByName("TotalDiscountedPrice")->AsFloat ;
		}  */
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "##0.00";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = "0.00";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = "0.00";
		operterview(dsetNtHeader->FieldByName("OperatorID")->AsInteger );
		membk->Text = dsetNtHeader->FieldByName("Remarks")->AsAnsiString ;
		ShowPrice();
		if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
		{
			/*if (IsChecked() == 0)
			{
				numedtPaidinMoney->Enabled = true;
			}
			else
			{
				numedtPaidinMoney->Enabled = false;
			} */
			m_card = dsetNtHeader->FieldByName("RecCardMoney")->AsFloat;
			m_cash = dsetNtHeader->FieldByName("RecCash")->AsFloat;
			m_poscard = dsetNtHeader->FieldByName("poscard")->AsFloat;
			m_youhuiquan = dsetNtHeader->FieldByName("youhuiquan")->AsFloat;
			m_weixi =dsetNtHeader->FieldByName("weixi")->AsFloat;
			m_zfb = dsetNtHeader->FieldByName("zfb")->AsFloat;
			numedtOdd->Value = (m_card + m_cash + m_poscard + m_youhuiquan+m_weixi+m_zfb)
				- dsetNtHeader->FieldByName("TotalDiscountedPrice")->AsFloat;
			if (numedtOdd->Value < 0) {
				numedtOdd->Value = 0;
			}
			numedtPaidinMoney->Value = m_card + m_cash + m_poscard + m_youhuiquan+m_weixi+m_zfb;
		}
		if (IsChecked() == 1)
		{
			edcard->Enabled = false;
			dbnbedtAmount->Enabled = false;
			dbnbedtDiscount->Enabled = false;
		}
		else
		{
			edcard->Enabled = true;
			dbnbedtAmount->Enabled = true;
			if (retaildiscountchange) {
				dbnbedtDiscount->Enabled = true;
			}
			else
			{
				dbnbedtDiscount->Enabled = false;
			}
		}
		//MoneyChange();
	}
	catch(...)
	{
		//ShowMessage("�õ������ڣ�");
	}
}

void TfrmRetailMng::QryNtHeader(bool qrybkstack)
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
		spQryNtHeader->Parameters->ParamByName("@Bsmode")->Value = 3;
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
			dsetNote->AfterScroll = dsetNoteAfterScroll;
			nummayang->Value = dsetNtHeader->FieldByName("TotalFixedPrice")->AsExtended;
			numceshu->Value = dsetNtHeader->FieldByName("TotalAmount")->AsInteger;
			edname->Text = dsetNtHeader->FieldByName("MemberName")->AsAnsiString ;
			edyue->Text = FormatFloat("0.0",dsetNtHeader->FieldByName("Balance")->AsFloat);
			edtype->Text = dsetNtHeader->FieldByName("typename")->AsAnsiString ;
			edcard->Text =  dsetNtHeader->FieldByName("CardSN")->AsAnsiString ;
			edjifen->Text = dsetNtHeader->FieldByName("Memberdot")->AsAnsiString ;
			edyouxiaodate->Text = dsetNtHeader->FieldByName("youxiaodate")->AsAnsiString ;
			edTotalConsumption->Text = dsetNtHeader->FieldByName("TotalConsumption")->AsAnsiString ;
			/*if (qrybkstack)
			{
				QryBkstack();
			} */
			if (dsetNtHeader->FieldByName("State")->AsInteger == 1 ) {
				dbnbedtReceivableMoney->Value = dsetNtHeader->FieldByName("TotalDiscountedPrice")->AsExtended ;
				numedtPaidinMoney->Enabled = false;
				numedtOdd->Value = 0.00;
				numedtPaidinMoney->Value = 0.00;
			}
			else
			{
				dbnbedtReceivableMoney->Value = dsetNtHeader->FieldByName("nochecked")->AsExtended ;
				numedtPaidinMoney->Enabled = true;
				numedtOdd->Value = 0.00;
				numedtPaidinMoney->Value = 0.00;
			}
			/*if (dsetNtHeader->FieldByName("nochecked")->AsFloat < 0 ) {
				dbnbedtReceivableMoney->Value =  dsetNtHeader->FieldByName("nochecked")->AsFloat ;
			}
			else
			{
				dbnbedtReceivableMoney->Value = dsetNtHeader->FieldByName("TotalDiscountedPrice")->AsFloat ;
			} */
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00";
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "##0.00";
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = "0.00";
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = "0.00";
			operterview(dsetNtHeader->FieldByName("OperatorID")->AsInteger );
			membk->Text = dsetNtHeader->FieldByName("Remarks")->AsAnsiString ;
			ShowPrice();

			if (IsChecked() == 1)
			{
				edcard->Enabled = false;
				dbnbedtAmount->Enabled = false;
				dbnbedtDiscount->Enabled = false;
			}
			else
			{
				edcard->Enabled = true;
				dbnbedtAmount->Enabled = true;
				if (retaildiscountchange) {
					dbnbedtDiscount->Enabled = true;
				}
				else
				{
					dbnbedtDiscount->Enabled = false;
				}
			}
			//MoneyChange();
		}
		catch(...)
		{
			//ShowMessage("�õ������ڣ�");
		}
	}
}

void TfrmRetailMng::QryNtHeader(int id, bool qrybkstack)
{
	//��ѯ��ͷ
	spQryNtHeader1->Active = false;
	spQryNtHeader->Active = false;
	spQryNtHeader->Parameters->ParamByName("@ID")->Value = id;
	spQryNtHeader->Parameters->ParamByName("@Bsmode")->Value = 3;
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
		/*if (qrybkstack)
		{
			QryBkstack();
		}*/
		nummayang->Value = dsetNtHeader->FieldByName("TotalFixedPrice")->AsExtended;
		numceshu->Value = dsetNtHeader->FieldByName("TotalAmount")->AsInteger;
		edname->Text = dsetNtHeader->FieldByName("MemberName")->AsAnsiString ;
		edyue->Text = FormatFloat("0.0",dsetNtHeader->FieldByName("Balance")->AsFloat);
		edtype->Text = dsetNtHeader->FieldByName("typename")->AsAnsiString ;
		edcard->Text =  dsetNtHeader->FieldByName("CardSN")->AsAnsiString ;
		edjifen->Text = dsetNtHeader->FieldByName("Memberdot")->AsAnsiString ;
		edyouxiaodate->Text = dsetNtHeader->FieldByName("youxiaodate")->AsAnsiString ;
		edTotalConsumption->Text = dsetNtHeader->FieldByName("TotalConsumption")->AsAnsiString ;
		if (dsetNtHeader->FieldByName("State")->AsInteger == 1 ) {

			dbnbedtReceivableMoney->Value = dsetNtHeader->FieldByName("TotalDiscountedPrice")->AsExtended ;
        	numedtOdd->Value = 0.00;
			numedtPaidinMoney->Value = 0.00;
            numedtPaidinMoney->Enabled = false;
		}
		else
		{
			dbnbedtReceivableMoney->Value = dsetNtHeader->FieldByName("nochecked")->AsExtended ;
        	numedtOdd->Value = 0.00;
			numedtPaidinMoney->Value = 0.00;
			numedtPaidinMoney->Enabled = true;
		}
		/*if (dsetNtHeader->FieldByName("nochecked")->AsFloat < 0 ) {
			dbnbedtReceivableMoney->Value =  dsetNtHeader->FieldByName("nochecked")->AsFloat ;
		}
		else
		{
			dbnbedtReceivableMoney->Value = dsetNtHeader->FieldByName("TotalDiscountedPrice")->AsFloat ;
		} */
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "##0.00";;
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = "0.00";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = "0.00";
		operterview(dsetNtHeader->FieldByName("OperatorID")->AsInteger );
		membk->Text = dsetNtHeader->FieldByName("Remarks")->AsAnsiString ;
		ShowPrice();

		if (IsChecked() == 1)
		{
			edcard->Enabled = false;
			dbnbedtAmount->Enabled = false;
			dbnbedtDiscount->Enabled = false;
		}
		else
		{
			edcard->Enabled = true;
			dbnbedtAmount->Enabled = true;
			if (retaildiscountchange) {
				dbnbedtDiscount->Enabled = true;
			}
			else
			{
				dbnbedtDiscount->Enabled = false;
			}
		}

		//MoneyChange();
	}
	catch(...)
	{
    	//ShowMessage("�õ������ڣ�");
    }
}

void TfrmRetailMng::AddNtHeader()
{
	RzButton2->Caption = "�˻�(&E)";
	Label2->Caption = "��������";
	spQryNtHeader->Active = false;
	spQryNtHeader1->Active = false;
	cmdAddNtHeader->Parameters->ParamByName("@StgID")->Value = m_storageID;
	cmdAddNtHeader->Parameters->ParamByName("@OperatorID")->Value = m_userID;
	cmdAddNtHeader->Parameters->ParamByName("@Bsmode")->Value = 3;
	cmdAddNtHeader->Execute();
	int id = cmdAddNtHeader->Parameters->ParamByName("@RETURN_VALUE")->Value;
	try
	{
	   //	LockWindowUpdate(dbgrdNote->Handle);//����ָ�����ڣ���ֹ�����¡�
		QryNtHeader(id);
		logmessage = "������۵�" + dsetNtHeader->FieldByName("RetailNtCode")->AsString ;
		AddEvent(1,"POS����",m_userID,m_storageID,logmessage,linfo.con);
	}
	__finally
	{
	   //	LockWindowUpdate(NULL);
	}
}

void TfrmRetailMng::DelNtHeader()
{
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		cmdDelNtHeader->Parameters->ParamByName("@ID")->Value
			= dsetNtHeader->FieldByName("ID")->AsInteger;
		int id = dsetNtHeader->FieldByName("ID")->AsInteger;
		cmdDelNtHeader->Parameters->ParamByName("@Bsmode")->Value = 3;
		cmdDelNtHeader->Execute();
		try
		{
		  //	LockWindowUpdate(dbgrdNote->Handle);//����ָ�����ڣ���ֹ�����¡�
			QryNtHeader(id);
		}
		__finally
		{
		  //	LockWindowUpdate(NULL);
		}
	}
}

void TfrmRetailMng::UpdateNtHeader()
{
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		cmdUpdateNtHeader->Parameters->ParamByName("@ID")->Value =
			dsetNtHeader->FieldByName("ID")->AsInteger;
		cmdUpdateNtHeader->Parameters->ParamByName("@HdTime")->Value =
			dsetNtHeader->FieldByName("HdTime")->AsDateTime;
		cmdUpdateNtHeader->Parameters->ParamByName("@StgID")->Value =
			dsetNtHeader->FieldByName("StgID")->AsInteger;
		cmdUpdateNtHeader->Parameters->ParamByName("@CustomerID")->Value =
			dsetNtHeader->FieldByName("MemberID")->AsInteger;
		cmdUpdateNtHeader->Parameters->ParamByName("@Cash")->Value =
			dsetNtHeader->FieldByName("RecCash")->AsFloat;
		cmdUpdateNtHeader->Parameters->ParamByName("@CardMoney")->Value =
			dsetNtHeader->FieldByName("RecCardMoney")->AsFloat;
		cmdUpdateNtHeader->Parameters->ParamByName("@Postcard")->Value =
			dsetNtHeader->FieldByName("poscard")->AsFloat;
		cmdUpdateNtHeader->Parameters->ParamByName("@Youhuiquan")->Value =
			dsetNtHeader->FieldByName("youhuiquan")->AsFloat ;
	   cmdUpdateNtHeader->Parameters->ParamByName("@weixi")->Value =
			dsetNtHeader->FieldByName("weixi")->AsFloat ;
		cmdUpdateNtHeader->Parameters->ParamByName("@zfb")->Value =
			dsetNtHeader->FieldByName("zfb")->AsFloat ;
		 cmdUpdateNtHeader->Parameters->ParamByName("@zhaolin")->Value =
			dsetNtHeader->FieldByName("zhaolin")->AsFloat ;
		cmdUpdateNtHeader->Parameters->ParamByName("@Remarks")->Value =
			dsetNtHeader->FieldByName("Remarks")->AsWideString;
		cmdUpdateNtHeader->Parameters->ParamByName("@State")->Value =
			dsetNtHeader->FieldByName("State")->AsInteger;
		cmdUpdateNtHeader->Parameters->ParamByName("@Bsmode")->Value = 3;
		cmdUpdateNtHeader->Execute();
		try
		{
		   //	LockWindowUpdate(dbgrdNote->Handle);//����ָ�����ڣ���ֹ�����¡�
			QryNtHeader();
		}
		__finally
		{
		  //	LockWindowUpdate(NULL);
		}
	}
}

bool TfrmRetailMng::AddNote(int bkinfoid, int catalogID,int mod)   //mod 1ȫѡ����ѯ��0��ѯ  ,3����
{
	bool result = false;
	if (!nobear()) {      //�Ƿ������������
		return false;
	}
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		cmdAddNote->Parameters->ParamByName("@NtHeaderID")->Value
        	= dsetNtHeader->FieldByName("ID")->AsInteger;
		cmdAddNote->Parameters->ParamByName("@BkcatalogID")->Value
        	= catalogID;
		cmdAddNote->Parameters->ParamByName("@STKinfoID")->Value
			= bkinfoid;
		//cmdAddNote->Parameters->ParamByName("@bkstackID")->Value = (int)(cbbkstackID->Items->Objects[cbbkstackID->ItemIndex]);
		if (Label2->Caption == "��������")
		{
        	cmdAddNote->Parameters->ParamByName("@NoteMode")->Value = 1;
        }
		else if (Label2->Caption == "�����˻�")
		{
        	cmdAddNote->Parameters->ParamByName("@NoteMode")->Value = 2;
		}
		cmdAddNote->Parameters->ParamByName("@Bsmode")->Value = 3;
		cmdAddNote->Execute();
		int ret = cmdAddNote->Parameters->ParamByName("@RETURN_VALUE")->Value;
		if (ret > 0)//����ɹ�
		{
			try
			{
                          catalogidStr = catalogidStr+ IntToStr(catalogID)+",";//��¼��Ŀ�ɣ��Ա��ѯ�Ƿ��Ƕ��Ŀͻ�
				//LockWindowUpdate(dbgrdNote->Handle);//����ָ�����ڣ���ֹ�����¡�
				if (mod == 0) {
					if (dbedtRetailNtCode->Text == "0") {
						AnsiString sql;
						sql = "update BS_RetailNoteHeader set RetailNtCode = dbo.UF_BS_BuildNtCode(" + IntToStr(m_storageID) + ", getdate(), 3,0) where id = " + dsetNtHeader->FieldByName("id")->AsAnsiString ;
						aq->Close();
						aq->SQL->Clear();
						aq->SQL->Add(sql);
						aq->ExecSQL();

					}
					QryNtHeader(dsetNtHeader->FieldByName("ID")->AsInteger, true);
					//��ʾ����
					if (Display) {
						com_send(dsetNote->FieldByName("DiscountedPrice")->AsAnsiString,1);
					}
				}
				/*((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00%";
				((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = format;
				((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = format;
				((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = format;*/
			}
			__finally
			{
				//LockWindowUpdate(NULL);
			}
			result = true;
		}
		else if (ret == 0)//���޴���
		{

		}
		else if (ret == -1)//��������
		{

		}
		else if (ret == -2) {
			addnotereturnvalue = -2;
			result = false;
		}
	}
	return result;
}
void TfrmRetailMng::UpdateNote()
{
	if (dsetNote->Active && dsetNote->RecordCount >= 1)
	{
		cmdUpdateNote->Parameters->ParamByName("@ID")->Value
			= dsetNote->FieldByName("ID")->AsInteger;
		AnsiString sql = "select amount from BS_RetailNote where id = " + dsetNote->FieldByName("ID")->AsAnsiString ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		if (aq->FieldByName("amount")->AsInteger > 0 || (aq->FieldByName("amount")->AsInteger == 0 && Label2->Caption == "��������")) {
			cmdUpdateNote->Parameters->ParamByName("@Amount")->Value
			= abs(dbnbedtAmount->Value);
			   //	= abs(dsetNote->FieldByName("Amount")->AsInteger);
		}
		else if (aq->FieldByName("amount")->AsInteger < 0 || (aq->FieldByName("amount")->AsInteger == 0 && Label2->Caption == "�����˻�")) {
			cmdUpdateNote->Parameters->ParamByName("@Amount")->Value
			   //	= - abs(dsetNote->FieldByName("Amount")->AsInteger);
					= - abs(dbnbedtAmount->Value);
		}
		cmdUpdateNote->Parameters->ParamByName("@Discount")->Value
		   //	= fabs(dsetNote->FieldByName("Discount")->AsFloat);
			= fabs(dbnbedtDiscount->Value);
		cmdUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 3;
		cmdUpdateNote->Execute();
		try
		{
		   //	LockWindowUpdate(dbgrdNote->Handle);//����ָ�����ڣ���ֹ�����¡�
			QryNtHeader();
			/*((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00%";
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = format;
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = format;
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = format; */
		}
		__finally
		{
		 //	LockWindowUpdate(NULL);
		}
	}
}
void TfrmRetailMng::DelNote()
{
	if (dsetNote->Active && dsetNote->RecordCount >= 1)
	{
        TReplaceFlags rf;
        rf << rfReplaceAll;
		if (dbgrdNote->SelectedRows->Count == 0)
		{
			cmdDelNote->Parameters->ParamByName("@ID")->Value
				= dsetNote->FieldByName("ID")->AsInteger;
			cmdDelNote->Parameters->ParamByName("@Bsmode")->Value = 3;
			logmessage = "ɾ�����۵�" + dsetNtHeader->FieldByName("RetailNtCode")->AsString + "����Ŀ��" + dsetNote->FieldByName("CatalogName")->AsString + "��";
			AddEvent(1,"POS����",m_userID,m_storageID,logmessage,linfo.con);
			cmdDelNote->Execute();

                        catalogidStr=Sysutils::StringReplace(catalogidStr,dsetNote->FieldByName("ID")->AsString,"-1",rf);
		}
		else if (dbgrdNote->SelectedRows->Count > 0)
		{
			String ids = "";
			dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[0];
			ids = ids + dsetNote->FieldByName("ID")->AsString;
			logmessage = "ɾ�����۵�" + dsetNtHeader->FieldByName("RetailNtCode")->AsString + "����Ŀ��" + dsetNote->FieldByName("CatalogName")->AsString + "��";
			AddEvent(1,"POS����",m_userID,m_storageID,logmessage,linfo.con);
			for (int i=1; i < dbgrdNote->SelectedRows->Count; i++)
			{
				dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[i];
				ids = ids + "," + dsetNote->FieldByName("ID")->AsString;
                logmessage = "ɾ�����۵�" + dsetNtHeader->FieldByName("RetailNtCode")->AsString + "����Ŀ��" + dsetNote->FieldByName("CatalogName")->AsString + "��";
				AddEvent(1,"POS����",m_userID,m_storageID,logmessage,linfo.con);
                            catalogidStr=Sysutils::StringReplace(catalogidStr,dsetNote->FieldByName("ID")->AsString,"-1",rf);
			}
			cmdBatchDelNote->Parameters->ParamByName("@IDS")->Value = ids;
			cmdBatchDelNote->Parameters->ParamByName("@Bsmode")->Value = 3;
			cmdBatchDelNote->Execute();
		}
		try
		{
		  //	LockWindowUpdate(dbgrdNote->Handle);//����ָ�����ڣ���ֹ�����¡�
			QryNtHeader();
		}
		__finally
		{
		  //	LockWindowUpdate(NULL);
		}
	}
}
void __fastcall TfrmRetailMng::dsrcNtHeaderDataChange(TObject *Sender, TField *Field)
{
	//��������
	//UpdateNtHeader();
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailMng::dsrcNoteDataChange(TObject *Sender, TField *Field)
{
	//��������
	//UpdateNote();
   //	ShowMessage(dsetNote->FieldByName("Amount")->AsAnsiString);
}
//---------------------------------------------------------------------------
 bool TfrmRetailMng::IsNumber(const char *ps)
 {
	int dot_count = 0;
	if(*ps == '.')return false;  // С���㲻���ǵ�һλ
	for(const char *p=ps;*p;++p)
	{
		if(*p == '.')++dot_count;
		else if(*p <'0' || *p > '9')return false;
	}
	if(dot_count > 1)return false;  // С����ֻ����һ��
	return true;
 }
 bool TfrmRetailMng::IsNumberExt(const char *ps)
 {  //ȫ����

	for(const char *p=ps;*p;++p)
	{
		 if(*p <'0' || *p > '9')return false;
	}

	return true;

 }
int TfrmRetailMng::GetInputMean(AnsiString inputstr)
{
	AnsiString firstchar,shengyu;
	firstchar= inputstr.SubString(1,1);
	shengyu=inputstr.SubString(2,inputstr.Length()-1);
	int returncode;
        returncode=0;
		if ((firstchar=='s')||(firstchar=='S')) {  //�������s��ͷ���ַ��� ����
		   returncode=1;
		}
		if ((firstchar=='d')||(firstchar=='D')) {  //�������d��ͷ���ַ��� �ۿ�
		   returncode=2;
		}
		if ((firstchar=='b')||(firstchar=='B')) {  //�������s��ͷ���ַ��� �ۼ�
		   returncode=3;
		}
		if ((firstchar=='g')||(firstchar=='G')) {  //�������g
		   returncode=4;
		}

		char *str,*str1;
		str=inputstr.c_str();
		str1=shengyu.c_str();
	   if (returncode==0) {
		 if(IncludeChinese(str)) //�Ƿ�ȫ�Ǻ���
		 {
			 returncode=5;//������Ǻ��֣����� ����
		 }
		 if(Includeaz(str)) {  //ȫ����ĸ
			 returncode=6; //�Ա���
		 }
		 if(IsNumberExt(str)) { //ȫ������ �������
			 returncode=8;  //��������
		 }
	   }else if (returncode!=0) {
		 if (!IsNumber(str1)) {   //�Ƿ�������
		   if (Includeaz(str1)) {
			 returncode=6;//��������Ա���
		   }else if(IncludeChinese(str1)) {//�Ƿ��к���
			  returncode=5;
		   }
		 }
	   }


	  return returncode;
}
bool TfrmRetailMng::Includeazext(char *str)
{
  //��ĸ���ֻ��
  	char ch;
   while(1)
   {
	   ch=*str++;
	   if (ch==0) break;
	if( (ch <'A' && ch > 'Z') || (ch < 'a' && ch > 'z')||(ch<'0'&&ch>'9') )
	{
	  return false;
	}
   }
   return true;
}
bool TfrmRetailMng::Includeaz(char *str)
{
//ȫ��ĸ
	char ch;
	bool zimu;
   while(1)
   {
	   ch=*str++;
	   if (ch==0) break;
	if(ch>='A'&&ch<='Z'||ch<='z'&&ch>='a')
	{
	  zimu=true;
	}else
	{
	  zimu=false;
	  break;
	}
   }
   return zimu;


}
bool TfrmRetailMng::IncludeChinese(char *str)
{
	 char c;
   while(1)
   {
	   c=*str++;
	   if (c==0) break;  //������ַ���β��˵�����ַ���û�������ַ�
	   if (c&0x80)        //����ַ���λΪ1����һ�ַ���λҲ��1���������ַ�
	   if (*str & 0x80) return true;
   }
   return false;
}

void __fastcall TfrmRetailMng::edtCatalogKeyPress(TObject *Sender, wchar_t &Key)
{
	int results;
	 wchar_t psw = '\r';
	if (m_catalogSearchMode == 6) {
		if ((Key < '0' || Key > '9') && (Key != '\b') && (Key != '.') && (Key != '\r') ) {
            Key = NULL;
		}
	}
	if (Key == '\r')
	{
		/*if (dbedtRetailNtCode->Text == "0") {
			MessageBox(0,"���ȱ���õ���","������ʾ" ,MB_OK);
			return;
		}*/
		if (!dsetNote->Active || !dsetNtHeader->Active
			|| (dsetNtHeader->Active && dsetNtHeader->RecordCount < 1))
			return;

		if (IsChecked() == 1)
		{
			ShowMsg(Handle ,"�ѽᵥ�ݲ����޸ģ�",3);
			return;
		}

		if (edtCatalog->Text == "")
		{
			ChangeCatalogSearchMode();
		}
		else
		{
			switch (m_catalogSearchMode)
			{
                            case 1:
                            case 6:
                            case 5:
                            case 2:
                            case 3:
								{
									if (m_catalogSearchMode==6) {
										FLOAT price;
										try
										{
											price = StrToFloat(edtCatalog->Text);
										}
										catch(...)
										{
											ShowMsg(Handle ,"��������ȷ�ļ۸�",3);
											return ;
										}
									  }

								AnsiString inputstr,houinputstr;
								inputstr =  edtCatalog->Text.Trim();
								houinputstr=inputstr.SubString(2,inputstr.Length()-1);
							   if (!dsetNote->IsEmpty()) {


							   //Ϊ��û����ϸ
								switch(GetInputMean(inputstr))
								{
								   case 1:
										  //��������
										  { //powerchangdiscount,powerguadan,powertuihuan,powerinputprice;

										  	dbnbedtAmount->Value= StrToFloat(houinputstr);



										   //	SendMessage(dbnbedtAmount->Handle,EM_SETSEL,NULL,-1);
										  //	SendMessage(dbnbedtAmount->Handle,EM_REPLACESEL,1,(LPARAM)"5");//(LPARAM)
										  //	SendMessage(dbnbedtAmount->Handle,WM_KEYDOWN ,VK_RETURN,1);
										  //	SendMessage(dbnbedtAmount->Handle,WM_KEYUP,VK_RETURN,1);
                                            dbnbedtAmountExit(dbnbedtAmount);
											dbnbedtAmountKeyPress(dbnbedtAmount,psw);

											edtCatalog->SetFocus();
											edtCatalog->SelectAll();
											return;
											break;
										  }
								   case 2: //�����ۿ�
										 {
										  if (powerchangdiscount) {
                                            dbnbedtDiscount->Value= StrToFloat(houinputstr);

										  dbnbedtDiscountExit(dbnbedtDiscount);
										  dbnbedtDiscountKeyPress(dbnbedtDiscount,psw);
										   //	PostMessage(dbnbedtDiscount->Handle,WM_KEYDOWN ,VK_RETURN,1);
										   //	PostMessage(dbnbedtDiscount->Handle,WM_KEYUP,VK_RETURN,1);
										  edtCatalog->SetFocus();
										  edtCatalog->SelectAll();
										  }

										   return;
											break;
										 }
								   case 3: //�����ۼ�
										 {
										 if (powerinputprice) {
											edprice->Text= houinputstr;
											edpriceKeyPress(edprice,psw);

											edtCatalog->SetFocus();
											edtCatalog->SelectAll();
										 }

										return;
										 break;
										 }
								   case 4://�����տ�
										 {
                                            numedtPaidinMoney->SetFocus();
											numedtPaidinMoney->Text= houinputstr;

											numedtPaidinMoney->OnChange;

                                          return;
											break;

										  }
								   case 5:   //������Ǻ��ִ�������
										 {

										   m_catalogSearchMode= 3;

										  break;

										 }
								   case 6:   //���������ĸ�����Ա���
								   {
										   m_catalogSearchMode= 2;
										  break;
								   }
								   case 8:  //��������
								   {
                                     m_catalogSearchMode= 1;
                                     break;
								   }
								} }

							  /*   if (m_catalogSearchMode!=6) {

									   FLOAT price;

										 if(IsNumber(edtCatalog->Text.t_str())&& (!dbgrdNote->DataSource->DataSet->IsEmpty()))
										 {
											//�տ�
										   	if (StrToFloat(edtCatalog->Text)<=2000) {


										  numedtPaidinMoney->SetFocus();
										  numedtPaidinMoney->Text= edtCatalog->Text.Trim();

										   numedtPaidinMoney->OnChange;
										   //	AnsiString inputmondy ;
										 //	price = StrToFloat(edtCatalog->Text.t_str());
										  //	SendMessage(numedtPaidinMoney->Handle,EM_SETSEL,NULL,-1);
										  //	SendMessage(numedtPaidinMoney->Handle,EM_REPLACESEL,1,price);//(LPARAM)
										  //	PostMessage(numedtPaidinMoney->Handle,WM_KEYDOWN ,VK_RETURN,1);
										  //	PostMessage(numedtPaidinMoney->Handle,WM_KEYUP,VK_RETURN,1);
											return;

											}
										 }
									}    */






					TfrmSelectCatalog* frm = new TfrmSelectCatalog(Application,m_con);
					LandInfo li;
					li.app = m_app;
					li.con = m_con;
					li.userID = m_userID;
					li.storageID = m_storageID;
					frm->Init(&li);
					frm->SetSearchMode(m_catalogSearchMode, edtCatalog->Text);
					frm->DoModalType = 1;//����ģʽ
					frm->Retailfrm = this;

					frm->SelectAll = false;
					frm->QryBkInfo();
					if (frm->findbooks == 3) {    //�ҵ�������¼
						results= frm->ShowModal();
					}else if (frm->findbooks==1) {     //ֻ�ҵ�һ�����Ͳ���ʾѡ�񴰿���
						results = 1;
					}else if ((frm->findbooks==0)||(frm->findbooks==-1)) {    //û���ҵ��򶼳���
						results = -1 ;
					}

					if (mrOk == results)
					{
						int bkinfoid = -1,catalogID = -1;
						frm->GetSelectResult(bkinfoid, catalogID);
						/*if (!retailreturn(catalogID)) {
							return;
						}*/
						if (bkinfoid >= 0 && catalogID >= 0)
						{
							if (frm->SelectAll) {
								for (int i = 0; i < frm->lengthint; i++) {
								//cbbkstackID->ItemIndex = cbbkstackID->Items->IndexOfObject((TObject*)frm->BKSKid[i]);
								if (saleenable(frm->stkbkid[i])) {
									Amount = frm->skAmount[i];
									AddNote(frm->stkbkid[i],frm->BkcatalogiD[i],1);
								}
							 }
							 if (dbedtRetailNtCode->Text == "0") {
								AnsiString sql;
								sql = "update BS_RetailNoteHeader set RetailNtCode = dbo.UF_BS_BuildNtCode(" + IntToStr(m_storageID) + ", getdate(), 3,0) where id = " + dsetNtHeader->FieldByName("id")->AsAnsiString ;
								aq->Close();
								aq->SQL->Clear();
								aq->SQL->Add(sql);
								aq->ExecSQL();
							 }
							 QryNtHeader();
						}else
						{
							//cbbkstackID->ItemIndex = cbbkstackID->Items->IndexOfObject((TObject*)frm->BSKid);
							Amount = frm->Amount ;
                            if (!saleenable(frm->BKinfoid)) {
								return;
							}
							if (AddNote(bkinfoid, catalogID,0))
							{
								if (Label2->Caption == "�����˻�") {
                                                                ;
									if (ShowMsg(Handle ,"�Ƿ�����˻�?",1) != 6){
										Label2->Caption = "��������";
										RzButton2->Caption = "�˻�(&E)";
									}
								}
								if (addnotereturnvalue == -2) {
									addnotereturnvalue = 0;
									ShowMsg(Handle ,"������������ۣ�",3);
								} else
								{
									Key=0;
									edtCatalog->Text = "";
							  //	Perform(WM_NEXTDLGCTL, 0, 0);
							 	}
							}
							//else
								//MessageBox(0,"����޸��飡","������ʾ" ,MB_OK);
						}     }
					}
						Key=0;
						edtCatalog->Text = "";
					delete frm;
				}
				break;
			default:
				;
			}
		}
	}
}
//---------------------------------------------------------------------------

void TfrmRetailMng::ChangeCatalogSearchMode()
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
		lblCatalog->Caption = "���";
		edtCatalog->MaxLength = 15;
		break;
	case 2:
		edtCatalog->MaxLength = 0;
		lblCatalog->Caption = "�Ա���";
		break;
	case 3:
		edtCatalog->MaxLength = 0;
		lblCatalog->Caption = "����";
		break;
	case 5:
		edtCatalog->MaxLength = 0;
		lblCatalog->Caption = "����";
		break;
	case 6:
		edtCatalog->MaxLength = 0;
		lblCatalog->Caption = "����";
		break;
    default:
        break;
	}
}

//---------------------------------------------------------------------------
void TfrmRetailMng::ChangeBsmode(BSMode bsmode)
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
}
//---------------------------------------------------------------------------
void TfrmRetailMng::ChangeOpmode(OPMode opmode)
{
	if (opmode == m_opmode
		&& (opmode == OPDelNtHeader))
		return;

	//1Ϊ�鵥ģʽ 2Ϊ��ӵ�ͷģʽ 3Ϊɾ����ͷģʽ 4Ϊ��ӵ�ģʽ 5Ϊɾ����ģʽ 6Ϊͳһģʽ 7Ϊ�ֳ��տ�ģʽ
	switch (opmode)
	{
	case OPFind:
		{
			if (IsChecked() == 0)
			{
				ShowMsg(Handle ,"����δ�ӵ���,���ܲ�ѯ��",3);
				numedtPaidinMoney->Enabled = true;
				return;
			}

			if (findpassword) {
            	if (!CheckOperateAuthority())
					return;
			}
			TfrmQryCode* frm = new TfrmQryCode(Application,m_con,m_storageID,0,0);
			if (frm->ShowModal() == mrOk)
			{
                DelInvalidNtHeader();
				edtCatalog->Text = "";
				String code = frm->GetNoteCode();
				try
				{
				 //	LockWindowUpdate(dbgrdNote->Handle);//����ָ�����ڣ���ֹ�����¡�
					QryNtHeader(code);
					AnsiString sql ;

					sql = "select * from BS_RetailNoteHeader " + frm->sqlwhere;
					aqhd->Close();
					aqhd->SQL->Clear();
					aqhd->SQL->Add(sql);
					aqhd->Open();
					dbhd->Enabled = true;
					TLocateOptions Opts;
					Opts.Clear();
					Opts << loPartialKey;
					aqhd->Locate("RetailNtCode", code, Opts);
				}
				__finally
				{

				}
				
			}
			delete frm;
			GroupBox2->Visible = false;
			m_opmode = opmode;
		}
		break;
	case OPAddNtHeader:
		{
			//����ϴ������ģʽ������û�мӽ��κ����ݣ��������
			GroupBox2->Visible = false;
			if (m_opmode == OPAddNtHeader &&
				dsetNote->Active && dsetNote->RecordCount < 1)
				return;

			if (m_opmode == OPDelNote
				&& dsetNote->Active && dsetNote->RecordCount < 1)
				return;

			if (IsChecked() == 0)
			{
				if (dsetNtHeader->FieldByName("State")->AsInteger != 2) {
					ShowMsg(Handle ,"����δ�ӵ���,������ӣ�",3);
					numedtPaidinMoney->Enabled = true;
					return;
				}
			}

			m_cash = 0;
			m_card = 0;
			m_poscard = 0;
			m_youhuiquan = 0;
			edtCatalog->Text = "";
			edprice->Text = "";
			numedtPaidinMoney->Value = 0.00;
			numedtOdd->Value = 0;

			AddNtHeader();

                        catalogidStr="-1,";
			dbhd->Enabled = false;
			dblkpcbbMemberID->Enabled = true;
			//dblkpcbbMemberID->SetFocus();
			edtCatalog->SetFocus();
			m_opmode = opmode;
		}
		break;
	case OPDelNtHeader:
		{
			if (IsChecked() == 0)
			{

                                 ShowMsg(Handle ,"����δ�ӵ���,����ɾ����",3);
				numedtPaidinMoney->Enabled = true;
				return;
			}

			if (!CheckOperateAuthority())
				return;

			edtCatalog->Text = "";
			if (IsChecked() == 1)
			{

                                ShowMsg(Handle ,"�ѽᵥ�ݲ���ɾ����",3);
				return;
			}
			//DelNtHeader();
			m_opmode = opmode;
        }
		break;
	case OPAddNote:
		edtCatalog->Text = "";
		edtCatalog->SetFocus();
		m_opmode = opmode;
		break;
	case OPDelNote:

		if (IsChecked() == 1)
		{

                        ShowMsg(Handle ,"�ѽᵥ�ݲ����޸ģ�",3);
			return;
		}
		if (deletepassword) {
            if (!CheckOperateAuthority())
				return;
		}
		else
		{
			if (ShowMsg(Handle ,"ȷ��Ҫɾ���ü�¼��?",1)!=1 )
				return;
		}

		DelNote();

                //

		//ResetNtHeader();
		numedtOdd->Value = numedtPaidinMoney->Value - dbnbedtReceivableMoney->Value  ;//������Ӧ��һ��
		if (numedtOdd->Value < 0) {
        	numedtOdd->Value = 0;
		}
		m_opmode = opmode;
		break;
	case OPSetNotes:
		if (IsChecked() == 1)
		{

                         ShowMsg(Handle ,"�ѽᵥ�ݲ����޸ģ�",3);
			return;
		}

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
			frm->ChangeBsmode(m_bsmode);
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
			//numedtOdd->Value = 0
			//numedtPaidinMoney->Value = 0;
		break;
	case OPRecCash:
    	//�ֳ��տ�ģʽ
    	m_opmode = opmode;
		break;
    default:
        break;
	}
	m_opmode == OPFind;
	ModifyEnable();
}

int TfrmRetailMng::IsChecked()
{
	int ret = -1;
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1
		&& dsetNote->Active && dsetNote->RecordCount >= 1
		&& dsetNtHeader->FieldByName("State")->AsInteger == 0)//δ��
	{
        ret = 0;
	}
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1
		&& dsetNote->Active && dsetNote->RecordCount >= 1
		&& dsetNtHeader->FieldByName("State")->AsInteger == 1)//�ѽ�
	{
    	ret = 1;
	}
	return ret;
}

void TfrmRetailMng::DelInvalidNtHeader()
{
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1
		&& dsetNote->Active && dsetNote->RecordCount < 1
		&& dsetNtHeader->FieldByName("State")->AsInteger == 0
		&& dsetNtHeader->FieldByName("RetailNtCode")->AsAnsiString == "0")//�˵����κμ�¼
	{
		DelNtHeader();
	}
}


void __fastcall TfrmRetailMng::FormClose(TObject *Sender, TCloseAction &Action)
{
	DelInvalidNtHeader();

	if (IsChecked() == 0) //����δ����״̬���������˳�
	{
		ShowMsg(Handle ,"�е�δ���㣬��ᵥ���˳���",3);
		numedtPaidinMoney->Enabled = true;
		Action = caNone;
		return;
	}
	if (!aq1->IsEmpty() && guadantishi && tishi ) {
		tishi = false;
		if (ShowMsg(Handle ,"�е��������Ƿ�鿴��",1)==1) {
			DelInvalidNtHeader();
			GroupBox2->Visible = true;
			Action = caNone;
			return;
		}
	}

	spQryNtHeader->Active = false;
	spQryNtHeader1->Active = false;
	dsetBkstack->Active = false;
	dsetMember->Active = false;
	TfrmMDIChild::FormClose(Sender, Action);
}
//---------------------------------------------------------------------------


void __fastcall TfrmRetailMng::mniBsNoteSendbackClick(TObject *Sender)
{
	//��ӵ�������
	if (IsChecked() == 0)
	{
		ShowMsg(Handle ,"����δ�ӵ���,������ӣ�",3);
		numedtPaidinMoney->Enabled = true;
		return;
	}

	TMenuItem* item = dynamic_cast<TMenuItem*>(Sender);
	if (item != NULL)
	{
		if (item->Tag == BSNoteSendback && !CheckOperateAuthority())
			return;

		ChangeBsmode(item->Tag);
		ChangeOpmode(OPAddNtHeader);
	}
}
//---------------------------------------------------------------------------
void TfrmRetailMng::Init(LandInfo* li)
{

	TfrmMDIChild::Init(li);
	//
    Amount = 0;
	linfo.app = li->app ;
	linfo.con = li->con ;
	linfo.userID = li->userID ;
	linfo.UserName = li->UserName ;
	linfo.storageID = li->storageID ;
        fstgid =  li->storageID ;
	linfo.FormatStr = li->FormatStr ;
	//lblOpName->Caption = m_opName;
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
	cmdDelNote->Connection = linfo.con;
	dsetMember->Connection = linfo.con;
	dsetBkstack->Connection = linfo.con;
	dsetbear->Connection = linfo.con;
	query->Connection = linfo.con;
	aquery->Connection = linfo.con;
	aq->Connection = linfo.con;
	aq1->Connection = linfo.con;
	aqhd->Connection = linfo.con ;
        a5aq->Connection = linfo.con;
    dsetbear->Active = true;
	dsetMember->Active = true;
	ChangeCatalogSearchMode();
    chckbxSwitch->Checked = false;
	ChangeBsmode(BSNote);
	ChangeOpmode(OPAddNtHeader);
	addnotereturnvalue = 0;
	ReadConfig();
	GetBkStackInfo();

		//��ȡ�����ļ�
	AnsiString configfile;
	configfile = "U:\\pddata\\config.ini";
	if (!FileExists(configfile)) {
		configfile =  ExtractFilePath(Application->ExeName) + "config.ini" ;
	}
	TIniFile *ini;
	ini   = new    TIniFile(configfile);
	ComNum = StrToInt(ini->ReadString("dbserver","ComNum","1"));
	Display = StrToBool(ini->ReadString("dbserver","Display","0"));
	xiaopiaoprint = StrToBool(ini->ReadString("dbserver","Print","0"));
	delete ini;
	if (Display)
	{
		init_ClientDisplay(ComNum);
	}

	AnsiString sql;
   //	sql = "select * from SYS_BSSET where name = 'RetailDiscountChange'";

	sql = "select * from SYS_BSSET ";//where name in('RetailDiscountChange','retailxiaoshudian','Memberdiscountyouxian','lsdiscount','Retailsingle','Retaitype', ";
   //	sql = sql + " 'lsusefind','lsusedelete','lsusetuihuo','retailbear','huankoupwd','huanjiapwd','minlsdiscount','minlsqikandiscount','guadan','guadantishi','retailtuihuan','retailprice','Retaiview','yuying','OpenMoneyBoxByUSB','membershengritishi','diyuchenbennosale')";

	SYSSet * BSSET = new SYSSet();

	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();

	while(!query->Eof)
	 {

		  SYSSet * Note = new SYSSet();
		  Note->Name = query->FieldByName("NAME")->AsAnsiString;

		  if (query->FieldByName("NAME")->AsAnsiString=="minlsdiscount") {

		  	  Note->ValueStr =query->FieldByName("bk")->AsAnsiString;
		          BSSET->Add("minlsdiscount_bk",(TObject*)Note);

		          SYSSet * Note1 = new SYSSet();
		          Note1->ValueStr =query->FieldByName("boundmix")->AsAnsiString;
			  BSSET->Add("minlsdiscount_boundmax",(TObject*)Note1);

			  SYSSet * Note2 = new SYSSet();
			  Note2->ValueBool =query->FieldByName("value")->AsBoolean;
			  BSSET->Add("minlsdiscount_value",(TObject*)Note2);



		  }else if (query->FieldByName("NAME")->AsAnsiString=="OpenMoneyBoxByUSB" ) {
                          SYSSet * Note1 = new SYSSet();
		          Note1->ValueStr =query->FieldByName("bk")->AsAnsiString;
			  BSSET->Add("OpenMoneyBoxByUSB",(TObject*)Note1);

                          SYSSet * Note4 = new SYSSet();
                           Note4->ValueBool =query->FieldByName("value")->AsBoolean;
			  BSSET->Add("OpenMoneyBoxByUSB_OpenMoneyBox",(TObject*)Note4);


		  }else if (query->FieldByName("NAME")->AsAnsiString=="minlsqikandiscount") {
							 SYSSet * Note6 = new SYSSet();
                              Note6->ValueStr =query->FieldByName("bk")->AsAnsiString;
		          BSSET->Add("minqikandiscount_bk",(TObject*)Note6);

		          SYSSet * Note7 = new SYSSet();
		          Note7->ValueStr =query->FieldByName("boundmix")->AsAnsiString;
			  BSSET->Add("minqikandiscount_boundmax",(TObject*)Note7);

			  SYSSet * Note8 = new SYSSet();
			  Note8->ValueBool =query->FieldByName("value")->AsBoolean;
			  BSSET->Add("minqikandiscount_value",(TObject*)Note8);



		  }
		  else  if (query->FieldByName("NAME")->AsAnsiString=="diyuchenbennosale")
		  {
            Note->ValueStr =query->FieldByName("bk")->AsAnsiString;
			Note->ValueBool=  query->FieldByName("value")->AsBoolean;
			BSSET->Add(query->FieldByName("NAME")->AsAnsiString,(TObject*)Note);
		  }
		  else
		  {

			 if (query->FieldByName("NAME")->AsAnsiString=="retailxiaoshudian")
			 {
				 Note->ValueStr =query->FieldByName("bk")->AsAnsiString;
				 BSSET->Add(query->FieldByName("NAME")->AsAnsiString,(TObject*)Note);
			 }else
			 {
				 Note->ValueBool=  query->FieldByName("value")->AsBoolean;
				 BSSET->Add(query->FieldByName("NAME")->AsAnsiString,(TObject*)Note);
			 }


		  }
		 query->Next();
	 }
    // delete query;

		BSSET->GetSetInfo("RetailDiscountChange");
	   //	if (!BSSET->ValueBool) {
		  if (!powerchangdiscount) {
				dbnbedtDiscount->Enabled = false;
				retaildiscountchange = false;
				RzButton3->Enabled = false;
		}
		else
		{
				RzButton3->Enabled = true;
		}



	BSSET->GetSetInfo("retailxiaoshudian");
	format = "###,###,##" + BSSET->ValueStr ;
	dbnbedtReceivableMoney->DisplayFormat =  format;
	numedtOdd->DisplayFormat = format;
	if (BSSET->ValueStr == "0") {
		xiaoshubit = 0;
	}
	else if (BSSET->ValueStr == "0.0") {
		xiaoshubit = 1;
	}
	else if (BSSET->ValueStr == "0.00") {
		xiaoshubit = 2;
	}
	//�鵥����
	BSSET->GetSetInfo("lsusefind");
	findpassword = BSSET->ValueBool ;
	//ɾ������
	BSSET->GetSetInfo("lsusedelete");
	deletepassword = BSSET->ValueBool ;
	//�˻�����
	BSSET->GetSetInfo("lsusetuihuo");
	tuihuopassword = BSSET->ValueBool ;
	//�����������
	BSSET->GetSetInfo("retailbear");
	retailbear = BSSET->ValueBool ;
	//��������
	BSSET->GetSetInfo("huankoupwd");
	huankoupwd = BSSET->ValueBool ;
	//��������
	BSSET->GetSetInfo("huanjiapwd");
	huajiapwd = BSSET->ValueBool ;
        //�Ƿ�������ʾ

         BSSET->GetSetInfo("yuying");
        talk = BSSET->ValueBool ;

	//���ͼ���ۿ�


 	BSSET->GetSetInfo("minlsdiscount_value");
    mindiscount =  BSSET->ValueBool;
	//��͵��ڳɱ��ۿ۶���

	BSSET->GetSetInfo("diyuchenbennosale");
	isblow =  BSSET->ValueBool;
	if (BSSET->ValueStr=="") {
	 BSSET->ValueStr='20';
	}
	chenbendiscount=StrToFloat(BSSET->ValueStr);



	BSSET->GetSetInfo("minlsdiscount_bk");
	if (BSSET->ValueStr  == "1" ) {
		minstorage = true;
	}
	else
	{
		minstorage = false;
	}
	BSSET->GetSetInfo("minlsdiscount_boundmax");
	if (BSSET->ValueStr=="") {
         BSSET->ValueStr='80';
	}
	mixdiscount = StrToFloat(BSSET->ValueStr);

         //����ڿ��ۿ�

        BSSET->GetSetInfo("minqikandiscount_value");
        minqikandiscount =  BSSET->ValueBool;
        BSSET->GetSetInfo("minqikandiscount_bk");
	if (BSSET->ValueStr  == "1" ) {
		minstorage = true;
	}
	else
	{
		minstorage = false;
	}
	BSSET->GetSetInfo("minqikandiscount_boundmax");
		if (BSSET->ValueStr=="") {
         BSSET->ValueStr="80";
	}
	mixqikandiscount = StrToFloat(BSSET->ValueStr);


	//dbnbedt3->DisplayFormat = format;
	//dbnbedt4->DisplayFormat = format;
	dbnbedtReceivableMoney->DisplayFormat = format;
	numedtDiscountedMoney->DisplayFormat = format;
	numedtOdd->DisplayFormat = format;
	numedtPaidinMoney->DisplayFormat =  format;
	numedtCheck->DisplayFormat = format;
	numedtRec->DisplayFormat = format;
	//������ʾ
	sql = "select id,Name,retailprint from SYS_StorageInfo where ID = " + IntToStr(li->storageID) ;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	edstoragename->Text = query->FieldByName("id")->AsString + query->FieldByName("Name")->AsString  ;
        xiaopiaoprint =  query->FieldByName("retailprint")->AsBoolean;       //�Ƿ�ֱ�Ӵ�ӡСƱ

        mniPrintNtHeader->Checked = xiaopiaoprint;

	sql = "select BS_RetailNoteHeader.RetailNtCode,BS_RetailNoteHeader.HdTime,CUST_MemberInfo.Name from BS_RetailNoteHeader inner join BS_RetailNote on BS_RetailNote.RetailNtHeaderID = BS_RetailNoteHeader.id left join CUST_MemberInfo on  BS_RetailNoteHeader.MemberID = CUST_MemberInfo.id where BS_RetailNoteHeader.State = 2 and stgid = " + IntToStr(m_storageID) + " group by RetailNtCode,HdTime,Name";
	aq1->Close();
	aq1->SQL->Clear();
	aq1->SQL->Add(sql);
	aq1->Open();

        //�Ƿ���USB����Ǯ��
        BSSET->GetSetInfo("OpenMoneyBoxByUSB");
        USBInfoOpenBOX = BSSET->ValueStr;
        /////////////////////////////////////

        //�Ƿ����տ��Ǯ��

         BSSET->GetSetInfo("OpenMoneyBoxByUSB_OpenMoneyBox");
         OpenMoneyBox = BSSET->ValueBool;

        BSSET->GetSetInfo("guadan");
	//if (BSSET->ValueBool) {
		if (powerguadan) {
		RzButton4->Enabled = true;
		RzButton5->Enabled = true;
                BSSET->GetSetInfo("guadan");
		guadantishi = BSSET->ValueBool;
	}
	else
	{
		RzButton4->Enabled = false;
		RzButton5->Enabled = false;
		guadantishi = false;
	}


		BSSET->GetSetInfo("retailtuihuan");

	if (powertuihuan) {
		RzButton2->Enabled = true;
	}
	else
	{
		RzButton2->Enabled = false;
	}


        BSSET->GetSetInfo("retailprice");

	if (powerinputprice) {
		RzButton6->Enabled = true;
	}
	else
	{
		RzButton6->Enabled = false;
	}



        //��Ա��������
        BSSET->GetSetInfo("membershengritishi");
        membertisi= BSSET->ValueBool;


		BSSET->GetSetInfo("Retaiview");




	if (BSSET->ValueBool) {
		RzButton7->Enabled = true;

		AnsiString labelcaption;
		bool Memberdiscountyouxian,lsdiscount,Retailsingle,Retaitype;

				BSSET->GetSetInfo("Memberdiscountyouxian");
		Memberdiscountyouxian = BSSET->ValueBool;

				BSSET->GetSetInfo("lsdiscount");
		lsdiscount = BSSET->ValueBool;


				BSSET->GetSetInfo("Retailsingle");
		Retailsingle = BSSET->ValueBool;

				BSSET->GetSetInfo("Retaitype");
		Retaitype = BSSET->ValueBool;


		sql = "select id,value,case when name = 'membertype' then '��Ա���ۿ�' "
			" when name = 'danping' then '�����ۿ�' when name = 'shumutype' then '��Ŀ����ۿ�' "
			" when name = 'rukuzhekou' then '���Ԥ�������ۿ�' end as name,bk "
			" from sys_bsset where name in('membertype','danping','shumutype','rukuzhekou') "
			" and value = 1 order by bk ";
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->Open();
		labelcaption = query->FieldByName("name")->AsAnsiString ;
		query->Next();
		while (!query->Eof)
		{
			labelcaption = labelcaption + "->" + query->FieldByName("name")->AsAnsiString ;
			query->Next();
		}
		labdiscountstyle->Caption = "��ǰ���۷�����" + labelcaption;
	}
	else
	{
		RzButton7->Enabled = false;
	}
	FormView();
}
//---------------------------------------------------------------------------
void __fastcall TfrmRetailMng::dbnbedtAmountKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r')
	{

		Key = 0;
        if (dsetNote->IsEmpty() ) {
			return;
		}
		if (dbnbedtAmount->Text == "") {
			dbnbedtAmount->Text  = "0";
		}

		if (!dsetbear->FieldByName("value")->AsBoolean && Label2->Caption == "��������") {  //�������������ͬʱ������״̬
			if (dbnbedtAmount->Value > dsetNote->FieldByName("TotalAmount")->AsInteger + dsetNote->FieldByName("Amount")->AsInteger  ) {
				MessageBoxA(0,"�������ݴ��ڵ�ǰ���������","����",MB_ICONASTERISK);
				dbnbedtAmount->Value = dsetNote->FieldByName("TotalAmount")->AsInteger + dsetNote->FieldByName("Amount")->AsInteger;
				if (dbnbedtAmount->Value < 0) {
                	dbnbedtAmount->Value  = 0;
				}
			}
		}
		if (chdingwei->Checked && !dsetNote->Eof ) {
			dbgrdNote->SetFocus();
			dsetNote->Next();
			dbgrdNote->SelectedRows->CurrentRowSelected = true;
			dbnbedtAmount->SetFocus();
		}
		else
		{
			if (dbnbedtDiscount->Enabled ) {
				dbnbedtDiscount->SetFocus();
			}
			else
			{
				edtCatalog->SetFocus();
			}
		}
		  //	ShowMessage("dbnbedtAmountKeyPress "+dsetNote->FieldByName("Amount")->AsAnsiString);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailMng::tlbtn4Click(TObject *Sender)
{
	/*if (IsChecked() == 1)
	{
		ShowMsg(Handle ,"�ѽᵥ�ݲ����޸ģ�",3);
		return;
	}


	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		TfrmSelectMember* frm = new TfrmSelectMember(Application);
		LandInfo li;
		li.app = m_app;
		li.con = m_con;
		li.userID = m_userID;
		li.storageID = m_storageID;
		frm->Init(&li);

		if (mrOk == frm->ShowModal())
		{
			int id = frm->GetMemberID();
			if (id > 0)
			{
				dsetNtHeader->Edit();
				dsetNtHeader->FieldByName("MemberID")->AsInteger = id;
				UpdateNtHeader();
			}
		}
		delete frm;
		if (!dsetNote->IsEmpty() ) {
			int *Bkcatalogid,*bkinfoid,*amount,Recount;
			Recount = dsetNote->RecordCount ;
			Bkcatalogid = new int[Recount];
			bkinfoid = new int[Recount];
			amount = new int[Recount];
			for (int i = 0; i < Recount; i++) {
				Bkcatalogid[i] = dsetNote->FieldByName("BkcatalogID")->AsInteger ;
				bkinfoid[i] = dsetNote->FieldByName("BkInfoID")->AsInteger ;
				amount[i] = dsetNote->FieldByName("Amount")->AsInteger ;
				DelNote();
			}
			for (int i = 0; i < Recount; i++) {
				AddNote(bkinfoid[i],Bkcatalogid[i],1);
				if (dsetNote->Active && dsetNote->RecordCount >= 1)
				{
					cmdUpdateNote->Parameters->ParamByName("@ID")->Value
						= dsetNote->FieldByName("ID")->AsInteger;
					cmdUpdateNote->Parameters->ParamByName("@Amount")->Value = amount[i];
					//cmdUpdateNote->Parameters->ParamByName("@Discount")->Value
						//= fabs(dsetNote->FieldByName("Discount")->AsFloat);
					cmdUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 3;
					cmdUpdateNote->Execute();
				}
			}
			QryNtHeader();
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00%";
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = format;
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = format;
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = format;
		}
	} */
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailMng::tlbtnRecMoneyClick(TObject *Sender)
{
	//�տ�
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1
		&& dsetNote->Active && dsetNote->RecordCount >= 1)
	{
    	//���Ȱ��޸ĵĸ���һ�¹�
		dbgrdNote->SetFocus();
		//��ΰ���������ˢ��һ�¹�
		QryNtHeader();
		if (IsChecked() == 1)
		{
			ShowMsg(Handle ,"�ѽᵥ�ݲ����޸ģ�",3);
			return;
		}
		if (dsetNtHeader->FieldByName("TotalDiscountedPrice")->AsFloat > 0)
		{
			m_card = 0;
			m_cash = dsetNtHeader->FieldByName("TotalDiscountedPrice")->AsFloat;
			numedtPaidinMoney->Value = m_card + m_cash;
		}
		else
		{
			numedtPaidinMoney->Value =0;// dsetNtHeader->FieldByName("TotalDiscountedPrice")->AsFloat;;
			numedtOdd->Value = (m_card + m_cash + m_poscard + m_youhuiquan+m_weixi+m_zfb)
				- dsetNtHeader->FieldByName("TotalDiscountedPrice")->AsFloat;
		}
		//��ʾ�ܼ�
		if (Display) {
			com_send(ReplaceStr(dbnbedtReceivableMoney->Text,"��",""),2);
		}

		if (pnl1->Visible ) {
			numedtPaidinMoney->SetFocus();
		}
    }
}
//---------------------------------------------------------------------------
void TfrmRetailMng::mixshoukuan(int type)
{
   	//����տ�
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1
		&& dsetNote->Active && dsetNote->RecordCount >= 1)
	{
		//���Ȱ��޸ĵĸ���һ�¹�
		dbgrdNote->SetFocus();
		//��ΰ���������ˢ��һ�¹�
		QryNtHeader();
		if (IsChecked() == 1)
		{
			ShowMsg(Handle ,"�ѽᵥ�ݲ����޸ģ�",3);
		}
		else if (dsetNtHeader->FieldByName("TotalDiscountedPrice")->AsFloat > 0)
		{
			TfrmMixedRecMoney* frm = new TfrmMixedRecMoney(this);
			if (dblkpcbbMemberID->Text == "��ͨ��Ա" || dsetNtHeader->FieldByName("Balance")->AsFloat <= 0) {
				frm->numedtCard->Enabled = false;
			}
			if (pnl1->Visible) {
				//frm->SetMustRec(dsetNtHeader->FieldByName("nochecked")->AsFloat);
				frm->SetMustRec(dbnbedtReceivableMoney->Value);
                                if (type==2) {   //������Ӧ��
                                    if (dsetNtHeader->FieldByName("Balance")->AsFloat>=dbnbedtReceivableMoney->Value) {
									   frm->SetRecCard(dbnbedtReceivableMoney->Value);
									 //  frm->SetRecCash(m_cash);
                                       frm->SetCardRemain(dsetNtHeader->FieldByName("Balance")->AsFloat);
                                    }else
									{
                                       frm->SetRecCard(dsetNtHeader->FieldByName("Balance")->AsFloat);
									  // frm->SetRecCash(m_cash);
                                       frm->SetCardRemain(0);



                                    }
                                   
                                }else
                                {
                                    frm->SetRecCard(m_card);
								  //  frm->SetRecCash(m_cash);
                                    frm->SetCardRemain(dsetNtHeader->FieldByName("Balance")->AsFloat);
                                }
				if (mrOk == frm->ShowModal())
				{                                                      //	float m_weixi;//΢��   	float m_zfb;//֧����

					frm->GetRecMoney(m_card, m_cash,m_poscard,m_youhuiquan,m_weixi,m_zfb);
					numedtPaidinMoney->Value = m_card + m_cash + m_poscard + m_youhuiquan+m_weixi+m_zfb;
					numedtOdd->Value = dbnbedtReceivableMoney->Value -  numedtPaidinMoney->Value;
				}
			}

			delete frm;
			if (pnl1->Visible ) {
				numedtPaidinMoney->SetFocus();
			}
		}
    }

}
void __fastcall TfrmRetailMng::tlbtnMixedClick(TObject *Sender)
{
   mixshoukuan(1);
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailMng::tlbtn7Click(TObject *Sender)
{
	Close();
        HANDLE hWindow = FindWindow("TfrmMain",NULL);
        SendMessage(hWindow ,WM_MYMESSAGE,0,0);
}

//---------------------------------------------------------------------------
void __fastcall TfrmRetailMng::numedtPaidinMoneyChange(TObject *Sender)
{
  //	MoneyChange();
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		if (dsetNtHeader->FieldByName("nochecked")->AsFloat >= 0)
		{
			if ((numedtPaidinMoney->Value <= m_card) &&  (numedtPaidinMoney->Value != 0))
			{
				numedtPaidinMoney->Value = m_card;
				m_cash = 0;
			}
			else
			{
				m_cash = numedtPaidinMoney->Value - m_card - m_poscard - m_youhuiquan-m_weixi-m_zfb;
				if (m_card + m_cash + m_poscard + m_youhuiquan +m_youhuiquan-m_weixi+m_zfb - dbnbedtReceivableMoney->Value > 0.0) {
					numedtOdd->Value = (m_card + m_cash + m_poscard + m_youhuiquan+m_weixi-m_zfb)
					//	- dsetNtHeader->FieldByName("nochecked")->AsFloat;
					- dbnbedtReceivableMoney->Value ;
				}
				else
				{
					numedtOdd->Value = 0.0;
				}
			}
		}
		else//��Ӧ������
		{
			m_card = 0;
			m_cash = 0;
			m_poscard = 0;
			m_youhuiquan = 0;
			m_weixi = 0;
			m_zfb=0;
			numedtPaidinMoney->Value = dsetNtHeader->FieldByName("nochecked")->AsFloat;
			if (m_card + m_cash - dbnbedtReceivableMoney->Value > 0) {
				numedtOdd->Value = (m_card + m_cash)
			   - dbnbedtReceivableMoney->Value ;
			}
			else
			{
				numedtOdd->Value = 0;
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailMng::numedtPaidinMoneyKeyPress(TObject *Sender, wchar_t &Key)
{
	AnsiString sql;
	if (Key == '\r')
	{
 		if (IsChecked() == 1)
		{
			ShowMsg(Handle ,"�ѽᵥ�ݲ����޸ģ�",3);
			return;
		}
		//��ΰ���������ˢ��һ�¹�
		//QryNtHeader();

		if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1
			&& dsetNote->Active && dsetNote->RecordCount >= 1)
		{

				  //��ʼ�ж��Ƿ��Ƕ��Ŀͻ�
                   	float price = dsetNtHeader->FieldByName("TotalDiscountedPrice")->AsFloat;

                 sql = "  select a.orderMoney,bkcatalogid from dbo.BS_MemberOrderHeader a join dbo.BS_MemberOrderNote b on a.id = b.MemberOrderHeaderId ";
                 sql = sql +" where b.bkcatalogid in("+catalogidStr+"-1) and b.amount >b.yifa and a.memberid ="+dsetNtHeader->FieldByName("memberid")->AsAnsiString+"  and stgid = "+IntToStr(linfo.storageID);
                aquery->Close();
                aquery->SQL->Clear();
                aquery->SQL->Add(sql);
				aquery->Open();
                if (aquery->RecordCount!=0) {

                 if (ShowMsg(Handle ,"�û�Ա�ж���ͼ�飬�Ƿ񶩽����!",1)==1) {
                 /*  if (price <= aquery->FieldByName("orderMoney")->AsFloat)
                   {
                       m_card=price;

                   }else
                   {
                      m_card=aquery->FieldByName("orderMoney")->AsFloat;

                   }     */
				   mixshoukuan(2);

                   //���¶���


                 }
                         sql = "update dbo.BS_MemberOrderNote set yifa =yifa+a.amount from  BS_RetailNote a join BS_MemberOrderNote b on a.bkcatalog = b.bkcatalogid join dbo.BS_MemberOrderHeader c on b.memberorderHeaderid = c.id ";
                   sql = sql +" where a.retailNtHeaderID ="+dsetNtHeader->FieldByName("id")->AsAnsiString + " and  c.memberid="+dsetNtHeader->FieldByName("memberid")->AsAnsiString;
                     aquery->Close();
                aquery->SQL->Clear();
                aquery->SQL->Add(sql);
                aquery->ExecSQL();


                }










				if (dsetNtHeader->FieldByName("TotalDiscountedPrice")->AsFloat < 0 ) {
					ShowMsg(Handle ,"�������С��������Ľ�",3);
					return;
				}

				sql = "select * from SYS_BSSET where name = 'retairangge' and value = 'True'";
				aquery->Close();
				aquery->SQL->Clear();
				aquery->SQL->Add(sql);
				aquery->Open();
				while (!aquery->Eof)
				{
					if (aquery->FieldByName("boundmix")->AsFloat < price && price <= aquery->FieldByName("boundmax")->AsFloat ) {
						break;
					}
					aquery->Next();
				}
				float retairange;
				if (aquery->FieldByName("boundmix")->AsFloat < price && price <= aquery->FieldByName("boundmax")->AsFloat) {
					retairange = aquery->FieldByName("bk")->AsFloat ;
				}
				else
				{
					retairange = 0.0;
				}
				retairange = 0-retairange;
				if (numedtPaidinMoney->Value > dsetNtHeader->FieldByName("nochecked")->AsFloat + 100.00) {
					ShowMsg(Handle ,"�տ�����࣬��ȷ���տ����Ƿ���ȷ��",3);
					return;
				}
				if (numedtPaidinMoney->Value - dbnbedtReceivableMoney->Value < retairange) {
					ShowMsg(Handle ,"ʵ��С��Ӧ�գ��������տ",3);
					numedtPaidinMoney->SetFocus();
				}
				else if (numedtPaidinMoney->Value - dbnbedtReceivableMoney->Value >= -0.1) {
					numedtDiscountedMoney->Value = dbnbedtReceivableMoney->Value;
					numedtTotalAmount->IntValue = dsetNtHeader->FieldByName("TotalAmount")->AsInteger;
					numyueshoukuan->Value = m_card;
					numyue->Value = dsetNtHeader->FieldByName("Balance")->AsFloat - m_card;
					numedtCheck->Value = numedtOdd->Value;
					numedtRec->Value = m_cash;
					dsetNtHeader->Edit();
					dsetNtHeader->FieldByName("RecCardMoney")->AsFloat = m_card;
					dsetNtHeader->FieldByName("RecCash")->AsFloat = m_cash;
					dsetNtHeader->FieldByName("poscard")->AsFloat = m_poscard;
					dsetNtHeader->FieldByName("youhuiquan")->AsFloat = m_youhuiquan;
						dsetNtHeader->FieldByName("weixi")->AsFloat = m_weixi;
					dsetNtHeader->FieldByName("zfb")->AsFloat = m_zfb;
					dsetNtHeader->FieldByName("zhaolin")->AsFloat = numedtOdd->Value;;
					//dsetNtHeader->FieldByName("RecCash")->AsFloat = m_cash;
					//dsetNtHeader->FieldByName("RecCardMoney")->AsFloat = m_card + dsetNtHeader->FieldByName("checked")->AsFloat;
					dsetNtHeader->FieldByName("State")->AsInteger = 1;
					UpdateNtHeader();

					///���»�Ա��������
					String sql = "update CUST_MemberInfo set totalconsumption = totalconsumption + " + FloatToStr(dsetNtHeader->FieldByName("TotalDiscountedPrice")->AsFloat) ;
								 sql = sql + " where id =  " + dsetNtHeader->FieldByName("memberid")->AsAnsiString  ;
						 TADOQuery * aq = new TADOQuery(this);
						 aq->Connection  = m_con ;
						 aq->Close();
						 aq->SQL->Clear();
						 aq->SQL->Add(sql);
						 aq->ExecSQL();
						 delete aq;
					Addbook();
					//��ʾ����
					if(Display)
					{
						com_send(ReplaceStr(numedtOdd->Text,"��",""),4);
					}
					if (talk) {
						 //	Speck();
					}
					PrintNtHeader();
					mniPrintNtHeader->Checked = xiaopiaoprint;
					tlbtn8Click(BtnNew);
										   if (OpenMoneyBox) {
										   BtnUpOneLevel->Click();
										}
                                     //
				}
				else
				{
					TMsgDlgButtons btns;
					btns << mbOK << mbCancel;

					if (ShowMsg(Handle ,"�տ���㣬�Ƿ������",1)==1) {
						numedtDiscountedMoney->Value = dbnbedtReceivableMoney->Value;
						numedtTotalAmount->IntValue = dsetNtHeader->FieldByName("TotalAmount")->AsInteger;
						numedtCheck->Value = numedtOdd->Value;
						numedtRec->Value = numedtPaidinMoney->Value;
						dsetNtHeader->Edit();
						dsetNtHeader->FieldByName("RecCardMoney")->AsFloat = m_card;
						dsetNtHeader->FieldByName("RecCash")->AsFloat = m_cash;
						dsetNtHeader->FieldByName("poscard")->AsFloat = m_poscard;
						dsetNtHeader->FieldByName("youhuiquan")->AsFloat = m_youhuiquan;
						dsetNtHeader->FieldByName("weixi")->AsFloat = m_weixi;
						dsetNtHeader->FieldByName("zfb")->AsFloat = m_zfb;
						dsetNtHeader->FieldByName("zhaolin")->AsFloat = numedtOdd->Value; ;
						//dsetNtHeader->FieldByName("RecCash")->AsFloat = m_cash;
						//dsetNtHeader->FieldByName("RecCardMoney")->AsFloat = m_card + dsetNtHeader->FieldByName("checked")->AsFloat;
						dsetNtHeader->FieldByName("State")->AsInteger = 1;
						UpdateNtHeader();
						Addbook();
						if (talk) {
						       //	Speck();
						}
						PrintNtHeader();
						mniPrintNtHeader->Checked = xiaopiaoprint;
							String sql = "update CUST_MemberInfo set totalconsumption = totalconsumption + " + FloatToStr(m_cash + m_card) ;
							sql = sql + " where id =  " + dsetNtHeader->FieldByName("memberid")->AsAnsiString  ;
							TADOQuery * aq = new TADOQuery(this);
							aq->Connection  = m_con ;
							aq->Close();
							aq->SQL->Clear();
							aq->SQL->Add(sql);
							aq->ExecSQL();
							delete aq;

							///���»�Ա��������
						tlbtn8Click(BtnNew);
					}
				}
		}
		aq1->Active = false;
		aq1->Active = true;
                lbl2->Caption = "����[F4]";
	}
}
//---------------------------------------------------------------------------
void TfrmRetailMng::Speck()
{
	//������ʾ
	AnsiString talkstr;
	//Ӧ��
	talkstr = "Ӧ��"+ FloatToStr(dbnbedtReceivableMoney->Value)+"Ԫ";
	//����
	talkstr =talkstr +"�տ�"+ FloatToStr(numedtRec->Value)+"Ԫ";
	talkstr =talkstr +"����"+ FloatToStr(numedtCheck->Value)+"Ԫ";

	SpeckTxt(talkstr.c_str());
	//�ҿ�SpeckTxt

}
//---------------------------------------------------------------------------
void __fastcall TfrmRetailMng::numedtAmountKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r')
	{
		Key = 0;
		Perform(WM_NEXTDLGCTL, 0, 0);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailMng::dbnbedtAmountExit(TObject *Sender)
{
	//
	   //	ShowMessage("dbnbedtAmountExit "+dsetNote->FieldByName("Amount")->AsAnsiString);
	if (dsetNote->IsEmpty() ) {
    	return;
	}
	if (IsChecked() == 1)
	{
		ShowMsg(Handle ,"�ѽᵥ�ݲ����޸ģ�",3);
		return;
	}
	UpdateNote();
	if (numedtPaidinMoney->Value != 0.00) {
		MoneyChange();
	}

	if (!retaildiscountchange) {
	   dbnbedtDiscount->Enabled = false;
	}
}
//---------------------------------------------------------------------------
void TfrmRetailMng::OnHotKeyPress(DWORD vkCode)
{
	if (vkCode == VK_F12)
	{
		tlbtnRecMoneyClick(NULL);
	}
}

void TfrmRetailMng::QryBkstack()
{
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1
		&& dsetNote->Active && dsetNote->RecordCount >= 1)
	{
		String sql;
		sql = " SELECT STK_BookstackInfo.ID, STK_BookstackInfo.Name "
			" FROM STK_BookInfo LEFT OUTER JOIN"
			" STK_BookstackInfo ON STK_BookInfo.BkstackID = STK_BookstackInfo.ID"
			" where BkcatalogID="
			  + dsetNote->FieldByName("BkcatalogID")->AsString
			 + " and STK_BookstackInfo.StgID=" + dsetNtHeader->FieldByName("StgID")->AsString;
		dsetBkstack->Active = false;
		//dblkpcbbBkstackID->ListSource = NULL;
		//dblkpcbbBkstackID->DataSource = NULL;
		dsetBkstack->CommandText = sql;
		dsetBkstack->Active = true;
		//dblkpcbbBkstackID->ListSource = dsrcBkstack;
		//dblkpcbbBkstackID->DataSource = dsrcNote;
		//ShowMessage("OK");
	}
}

//---------------------------------------------------------------------------

void __fastcall TfrmRetailMng::dsetNoteAfterScroll(TDataSet *DataSet)
{
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
    	QryBkstack();
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailMng::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if (Key == VK_F1) {   // �鵥
		tlbtn8->Click();
	}
	if (Key == VK_F2) {   // ����
		BtnNew->Click();
	}
	if (Key == VK_F3) {   // Ǯ��
		BtnUpOneLevel->Click();
	}
	if (Key == VK_F4) {   // ��Ա��
		if (edcard->Enabled) {
			edcard->Text = "";
			edcard->SetFocus();
		}
	}
	if (Key == VK_F5) {   // ɾ��
		tlbtn2->Click();
	}
	if (Key == VK_F6) {   // ͳһ
		tlbtn3->Click();
	}
	if (Key == VK_F7) {   // ��Ա��Ϣ����
		BtnAttachFiles->Click();
	}
	if (Key == VK_F8) {   // ����տ�
		tlbtnMixed->Click();
	}
	if (Key == VK_F9) {   // ɾ��
		tlbtn1->Click();
	}
	if (Key == VK_F10) {  // ��ӡ
		BtnPrint->Click();
	}
	if (Key == VK_F11) {  //�����ϼ�
		BtnFinish->Click();
	}
	if (Key == VK_F12) {   //����տ�
		tlbtnRecMoney->Click();
	}

	if (Shift.Contains(ssAlt)&& Key ==81  ) {   //�˳�
	   tlbtn7->Click();
	}
	if (Shift.Contains(ssAlt)&& Key ==78  ) {  //��С��
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssAlt)&& Key ==70  ) {  //����
		BtnView->Click();
	}
	if (Shift.Contains(ssAlt)&& Key ==90) {  //��ԭ���ڴ�С
		WindowState = wsNormal  ;
	}
	if (Shift.Contains(ssAlt)&& Key ==65) {   //�ҵ�
		RzButton4->Click();
	}
	if (Shift.Contains(ssAlt)&& Key ==83) {    //����
		dbnbedtAmount->SetFocus();
	}
	if (Shift.Contains(ssAlt)&& Key ==68) {   //�ۿ�
		if (dbnbedtDiscount->Enabled ) {
			dbnbedtDiscount->SetFocus();
		}
	}
	if (Shift.Contains(ssAlt)&& Key == 87) {    //�ᵥ
		RzButton5->Click();
	}
	if (Shift.Contains(ssAlt)&& Key == 69) {   //�˻�
		RzButton2->Click();
	}
	if (Shift.Contains(ssAlt)&& Key ==71) {    //����
		RzButton3->Click();
	}
	if (Shift.Contains(ssAlt)&& Key ==66) {   //����
		RzButton6->Click();
	}
	if (Shift.Contains(ssAlt)&& Key ==67) {   //��Ա��ֵ
		RzToolButton1->Click();
	}
}
//---------------------------------------------------------------------------

void TfrmRetailMng::ResetNtHeader()
{
	//���õ�ͷ
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1
		&& dsetNote->Active && dsetNote->RecordCount < 1
		&& dsetNtHeader->FieldByName("State")->AsInteger == 0)
	{
		cmdResetNtHeader->Parameters->ParamByName("@ID")->Value =
		dsetNtHeader->FieldByName("ID")->AsInteger;
		cmdResetNtHeader->Parameters->ParamByName("@Bsmode")->Value = 3;
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
}

//---------------------------------------------------------------------------

void TfrmRetailMng::PrintNtHeader()
{
	if (mniPrintNtHeader->Checked)
	{
    	BtnPrintClick(NULL);
	}
	else
	{
		if (MessageBox(this->Handle,"�Ƿ��ӡСƱ��","��������ҵ�ǹ�ƽ̨-ѯ��",MB_ICONQUESTION|MB_SYSTEMMODAL|MB_YESNO|MB_DEFBUTTON2) == 6) {
			BtnPrintClick(NULL);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmRetailMng::mniPrintNtHeaderClick(TObject *Sender)
{
	WriteConfig();
}
//---------------------------------------------------------------------------

void TfrmRetailMng::ReadConfig()
{
	String inipath = ExtractFilePath(Application->ExeName) + "/config.ini";
	if (FileExists(inipath))
	{
    	TIniFile* file = new TIniFile(inipath);
		try
		{
			bool print = false;
			file->ReadBool("Retail","PrintOnRetail",print);
			mniPrintNtHeader->Checked = true;
		}
		catch(...)
		{
        	file->WriteBool("Retail","PrintOnRetail",mniPrintNtHeader->Checked);
		}
		delete file;
	}
	else
	{
    	TIniFile* file = new TIniFile(inipath);
		try
		{
			file->WriteBool("Retail","PrintOnRetail",mniPrintNtHeader->Checked);

		}
		catch(...)
		{

		}
		delete file;
    }
}

void TfrmRetailMng::WriteConfig()
{
	//дini�ļ�
	String inipath = ExtractFilePath(Application->ExeName) + "/config.ini";
	TIniFile* file = new TIniFile(inipath);
	try
	{
		file->WriteBool("Retail","PrintOnRetail",mniPrintNtHeader->Checked );
	}
	catch(...)
	{

	}
	delete file;
}
void __fastcall TfrmRetailMng::N1Click(TObject *Sender)
{
   lblCatalog->Caption = "���";
   m_catalogSearchMode = 1;
   edtCatalog->MaxLength = 15;
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailMng::N2Click(TObject *Sender)
{
	 lblCatalog->Caption = "�Ա���";
	 m_catalogSearchMode = 2;
	 edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailMng::N3Click(TObject *Sender)
{
	  lblCatalog->Caption = "����";
	  m_catalogSearchMode  = 3;
	  edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailMng::lblCatalogMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	if (Button == mbLeft ) {
		TPoint  pt;
		GetCursorPos(&pt);
		pm->Popup(pt.x,pt.y);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailMng::dbnbedtDiscountKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r')
	{
    	/*if (chdingwei->Checked && !dsetNote->Eof ) {
			dbgrdNote->SetFocus();
			dsetNote->Next();
			dbgrdNote->SelectedRows->CurrentRowSelected = true;
			dbnbedtDiscount->SetFocus();
		}
		else
		{
        	edtCatalog->SetFocus();
		} */






		if (chdingwei->Checked && !dsetNote->Eof ) {
			dbgrdNote->SetFocus();
			dsetNote->Next();
			dbgrdNote->SelectedRows->CurrentRowSelected = true;


			dbnbedtDiscount->Enabled = true;
			dbnbedtDiscount->SetFocus();
		}
		else
		{
			if (edtCatalog->Enabled) {
			  edtCatalog->SetFocus();
			}else
			{          //�������ֵ������ͳɱ�ֵ,��ô��true
			  if (dbnbedtDiscount->Value  >=chenbendiscount)
			  {

				  edtCatalog->Enabled=true;
                   edtCatalog->SetFocus();

			  }




			}

		}	
	}
	//yingshouview();
	//MoneyChangetui();
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailMng::N4Click(TObject *Sender)
{
	lblCatalog->Caption = "����";
	m_catalogSearchMode  = 6;
	edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------

void  TfrmRetailMng::FindNote(String code)
{
	/*if (IsChecked() == 0)
	{
		ShowMessage("����δ�ӵ���,���ܲ�ѯ!");
		return;
	}*/

	DelInvalidNtHeader();
	if (IsChecked() == 0)
	{
		ShowMsg(Handle ,"����δ�ӵ���,���ܲ�ѯ��",3);
		numedtPaidinMoney->Enabled = true;
		return;
	}
	try
	{
		//LockWindowUpdate(dbgrdNote->Handle);//����ָ�����ڣ���ֹ�����¡�
		QryNtHeader(code);
	}
	__finally
	{
		//LockWindowUpdate(NULL);
	}
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		if (IsChecked() == 0)
		{
			numedtPaidinMoney->Enabled = true;
		}
		else
		{
			numedtPaidinMoney->Enabled = false;
		}
		m_card = dsetNtHeader->FieldByName("RecCardMoney")->AsFloat;
		m_cash = dsetNtHeader->FieldByName("RecCash")->AsFloat;
		m_poscard = dsetNtHeader->FieldByName("poscard")->AsFloat;
		m_youhuiquan = dsetNtHeader->FieldByName("youhuiquan")->AsFloat;
		m_weixi =dsetNtHeader->FieldByName("weixi")->AsFloat;
		m_zfb =   dsetNtHeader->FieldByName("zfb")->AsFloat;
		numedtPaidinMoney->Value = m_card + m_cash + m_poscard + m_youhuiquan+m_zfb+m_weixi;
		numedtOdd->Value = (m_card + m_cash + m_poscard + m_youhuiquan+m_weixi+m_zfb)
				- dsetNtHeader->FieldByName("TotalDiscountedPrice")->AsFloat;
	}
}

//---------------------------------------------------------------------------
void __fastcall TfrmRetailMng::N6Click(TObject *Sender)
{
	for (int i = 1; i <= dsetNote->RecordCount ; i++) {
		dbgrdNote->DataSource->DataSet->RecNo = i;
		dbgrdNote->SelectedRows->CurrentRowSelected = true;
	}
}
//---------------------------------------------------------------------------

void TfrmRetailMng::MoneyChange()
{
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		if (dsetNtHeader->FieldByName("nochecked")->AsFloat >= 0)
		{
			if ((numedtPaidinMoney->Value <= m_card) &&  (numedtPaidinMoney->Value != 0))
			{
				numedtPaidinMoney->Value = m_card;
				m_cash = 0;
			}
			else
			{
				m_cash = numedtPaidinMoney->Value - m_card - m_poscard - m_youhuiquan-m_weixi-m_zfb;
				numedtOdd->Value = (m_card + m_cash + m_poscard + m_youhuiquan+m_weixi+m_zfb)
					- dsetNtHeader->FieldByName("nochecked")->AsFloat;
			}
		}
		else//��Ӧ������
		{
			m_card = 0;
			m_cash = 0;
			m_poscard = 0;
			m_youhuiquan = 0;
			m_zfb=0;
			m_weixi=0;
			numedtPaidinMoney->Value = 0;
			numedtOdd->Value = (m_card + m_cash)
				- dsetNtHeader->FieldByName("nochecked")->AsFloat;
		}
	}
}
//---------------------------------------------------------------------------


/*bool TfrmRetailMng::retailreturn(int catalogID)
{
	if (lbtitle->Caption == "�����˻���") {
	String sql;
	sql = "select value from SYS_BSSET where name = 'nosalereturn'";
	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Open();
	if (!aquery->FieldByName("value")->AsBoolean) {
		sql = "select count(*) as count from BS_RetailNote left join STK_BookInfo on BS_RetailNote.BkInfoID = STK_BookInfo.ID "
		" left join BS_BookCatalog on STK_BookInfo.BkcatalogID = BS_BookCatalog.ID where BS_BookCatalog.ID = " + IntToStr(catalogID);
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->Open();
		int count = aquery->FieldByName("count")->AsInteger ;
		if (count == 0) {
			MessageBox(0,"����û�����۹��������˻���","�����˻�" ,MB_OK);
			return false;
		}
	}
	}
	return true;
} */
//---------------------------------------------------------------------------

void __fastcall TfrmRetailMng::tlbtn8Click(TObject *Sender)
{
	//ɾ��
        try
        {
	TControl* con = dynamic_cast<TControl*>(Sender);
	if (con)
	{
		ChangeOpmode(con->Tag);
	}
        }catch(...)
        {}
}
//---------------------------------------------------------------------------

void TfrmRetailMng::ModifyEnable()
{
	/*if (m_opmode == OPFind) {
		dbnbedtAmount->Enabled = false;
		dbnbedtDiscount->Enabled = false;
		//numedtPaidinMoney->Enabled = false;
		cbbkstackID->Enabled = false;
		if (dsetNote->FieldByName("amount")->AsInteger < 0 ) {
        	dsrcNote->DataSet = NULL;
			dsetNote->AfterScroll = NULL;
		   //	lbtitle->Caption = "�����˻���";
		}
	}
	else
	{
		dbnbedtAmount->Enabled = true;
		if (retaildiscountchange) {
			dbnbedtDiscount->Enabled = true;
		}
		numedtPaidinMoney->Enabled = true;
	  ///	cbbkstackID->Enabled = true;
	}   */
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailMng::cbbkstackIDExit(TObject *Sender)
{
	if (IsChecked() == 1)
	{

                ShowMsg(Handle ,"�ѽᵥ�ݲ����޸ģ�",3);
		return;
	}
	UpdateNote();
	MoneyChange();
}
//---------------------------------------------------------------------------

void TfrmRetailMng::GetBkStackInfo()
{
	AnsiString sql= "select  CAST(stgid as varchar(10)) + ' �� ' + name  as name, ID from STK_BookstackInfo where StgID = " + IntToStr(m_storageID);
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

void __fastcall TfrmRetailMng::BtnFinishClick(TObject *Sender)
{
	Tfrmretailbookup *frm = new Tfrmretailbookup(Application,linfo.con,m_storageID);
	frm->ShowModal();
	delete frm;
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailMng::Addbook()
{
	String sql;
	AnsiString Message;
	float Money = -1;
	float Receivmoney = dbnbedtReceivableMoney->Value ;
	sql = "select Money from Money_Discount where StgID = " + IntToStr(m_storageID) + " group by Money order by Money asc";
	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Open();
	while (!aquery->Eof )
	{
		if (Receivmoney < aquery->FieldByName("Money")->AsInteger) {
			break;
		}
		else
		{
			Money = aquery->FieldByName("Money")->AsFloat  ;
			aquery->Next();
		}
	}
	if (Money == -1) {
    	return;
	}
	sql = "select BCatalogid,Money_Discount.Amount,bs_bookcatalog.name,"
		" stk_bookinfo.id as bkinfoid,stk_bookinfo.amount as stkamount from Money_Discount "
	  //	" join stk_bookinfo on stk_bookinfo.supplierid = Money_Discount.supplierid "
		" and Money_Discount.bcatalogid = stk_bookinfo.bkcatalogid "
		" join bs_bookcatalog on Money_Discount.bcatalogid = bs_bookcatalog.id "
		" where Money = 100 and stk_bookinfo.StgID = " + IntToStr(m_storageID) + " and Money_Discount.stgid = " + IntToStr(m_storageID) +
		" and getdate() between startdate and enddate ";
	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Open();
	Message = "�Ƿ�����������Ʒ��\n";
	while (!aquery->Eof)
	{
		if (Message != "�Ƿ�����������Ʒ��\n") {
			Message = Message + "\n";
		}
		Message = Message + aquery->FieldByName("Amount")->AsAnsiString + "��" + aquery->FieldByName("name")->AsAnsiString ;
		aquery->Next();
	}
	aquery->First();

	if (Message != "�Ƿ�����������Ʒ��\n") {
		if(ShowMsg(Handle ,Message.c_str(),1)==1)
		{
			while (!aquery->Eof)
			{
				Amount = aquery->FieldByName("stkamount")->AsInteger;
				if (AddNote(aquery->FieldByName("bkinfoid")->AsInteger , aquery->FieldByName("BCatalogid")->AsInteger,0)) {
					cmdUpdateNote->Parameters->ParamByName("@ID")->Value
					= dsetNote->FieldByName("ID")->AsInteger;
					if (m_bsmode == BSNote)
					{
						cmdUpdateNote->Parameters->ParamByName("@Amount")->Value
						= abs(aquery->FieldByName("Amount")->AsInteger );
					}
					cmdUpdateNote->Parameters->ParamByName("@Discount")->Value
					= 0.00;
					cmdUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 3;
					cmdUpdateNote->Execute();
				}
				aquery->Next();
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailMng::BtnViewClick(TObject *Sender)
{
	Tfrmbookquery * frm = new Tfrmbookquery(Application,linfo.con,linfo.storageID);
	frm->ShowModal();
	delete frm;
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailMng::BtnAttachFilesClick(TObject *Sender)
{
       try
       {
	TfrmMember * frm = new TfrmMember(Application,linfo.con);
	frm->Show() ;
       }catch(...)
       {

       }
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailMng::tlbtnAddNoteClick(TObject *Sender)
{
   	if (!CheckOperateAuthority())
		return;
	dbnbedtDiscount->Enabled = true;
	dbnbedtDiscount->SetFocus();
}
//---------------------------------------------------------------------------

void TfrmRetailMng::Sendonebook(int catalogid)
{
	AnsiString sql;
	sql = "select * from BS_BuyoneSendone where BS_BuyoneSendone.Starttime <= getdate() and BS_BuyoneSendone.Endtime >= getdate() and buycatalogid = " + IntToStr(catalogid) + " and stgid = " + IntToStr(m_storageID);
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	if (query->RecordCount > 0) {

		if(ShowMsg(Handle ,"���������飬�Ƿ�����",1)==1)
		{
			Tfrmsendbookselect * frm = new Tfrmsendbookselect(Application,linfo.con,linfo.storageID);
			if (mrOk == frm->ShowModal()) {
				AddNote(frm->aq->FieldByName("SupplierID")->AsInteger,frm->aq->FieldByName("ID")->AsInteger,0);
				if (dsetNote->Active && dsetNote->RecordCount >= 1)
					{

						cmdUpdateNote->Parameters->ParamByName("@ID")->Value
						= dsetNote->FieldByName("ID")->AsInteger;
						if (m_bsmode == BSNote)
						{
							cmdUpdateNote->Parameters->ParamByName("@Amount")->Value
							= abs(aquery->FieldByName("Amount")->AsInteger );
						}
						cmdUpdateNote->Parameters->ParamByName("@Discount")->Value
						= 0.00;
						cmdUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 3;
						cmdUpdateNote->Execute();
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
			delete frm;
		}
	}
}
//---------------------------------------------------------------------------

bool  TfrmRetailMng::saleenable(int stkid)
{

	AnsiString sql;
	sql = "select * from STK_StockInventories where states = 0 and STK_bookInfoID = " + IntToStr(stkid);
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	if (query->RecordCount > 0) {

        ShowMsg(Handle ,"���������̵㣬�������ۣ�",3);
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

                ShowMsg(Handle ,"���������̵㣬�������ۣ�",3);
			return false;
		}
		else
		{
        	return true;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmRetailMng::N7Click(TObject *Sender)
{
	if (dsetNote->IsEmpty() ) {
		return;
	}

	if (shoukuan == 0.00 && dsetNtHeader->FieldByName("State")->AsInteger == 1) {
		shoukuan = dsetNtHeader->FieldByName("TotalDiscountedPrice")->AsFloat;
	}
	dsetNtHeader->Edit();
	dsetNtHeader->FieldByName("State")->AsInteger = 0;
	dsetNtHeader->UpdateBatch(arCurrent);
	int amount;
	if (dbgrdNote->SelectedRows->Count == 0)
	{
		amount = dsetNote->FieldByName("Amount")->AsInteger ;
		dsetNote->Edit();
		dsetNote->FieldByName("Amount")->AsInteger = 0;
		dsetNote->UpdateBatch(arCurrent);
	}
	else if (dbgrdNote->SelectedRows->Count > 0)
	{
		dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[0];
		amount = dsetNote->FieldByName("Amount")->AsInteger ;
		dsetNote->Edit();
		dsetNote->FieldByName("Amount")->AsInteger = 0;
		dsetNote->UpdateBatch(arCurrent);
		for (int i=1; i < dbgrdNote->SelectedRows->Count; i++)
		{
			dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[i];
			amount = dsetNote->FieldByName("Amount")->AsInteger ;
			dsetNote->Edit();
			dsetNote->FieldByName("Amount")->AsInteger = 0 ;
			dsetNote->UpdateBatch(arCurrent);
		}
	}
	//pnl1->Visible = false;
	//pnl2->Visible = true;
	dbnbedtAmount->Enabled = true;
	dbnbedtDiscount->Enabled = true;
	logmessage = "�������۵�" + dsetNtHeader->FieldByName("RetailNtCode")->AsString + "����Ŀ��" + dsetNote->FieldByName("CatalogName")->AsString + "��";
	AddEvent(1,"POS����",m_userID,m_storageID,logmessage,linfo.con);
	QryNtHeader();
	//yingshouview();
	//MoneyChangetui();
	numedtPaidinMoney->Enabled = true;
	numedtPaidinMoney->Value = 0;
	MoneyChange();
}

//---------------------------------------------------------------------------

void __fastcall TfrmRetailMng::rzshoukuanKeyPress(TObject *Sender, wchar_t &Key)
{
	String sql;
	if (Key == '\r')
	{
		if (IsChecked() == 1)
		{

                            ShowMsg(Handle ,"�ѽᵥ�ݲ����޸ģ�",3);
			return;
		}

		//��ΰ���������ˢ��һ�¹�
		QryNtHeader();

		if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1
			&& dsetNote->Active && dsetNote->RecordCount >= 1)
		{
				float price = dbnbedtReceivableMoney->Value ;

				sql = "select * from SYS_BSSET where name = 'retairangge' and value = 'True'";
				aquery->Close();
				aquery->SQL->Clear();
				aquery->SQL->Add(sql);
				aquery->Open();
				while (!aquery->Eof)
				{
					if (aquery->FieldByName("boundmix")->AsFloat < price && price <= aquery->FieldByName("boundmax")->AsFloat ) {
						break;
					}
					aquery->Next();
				}
				float retairange;
				if (aquery->FieldByName("boundmix")->AsFloat < price && price <= aquery->FieldByName("boundmax")->AsFloat) {
					retairange = aquery->FieldByName("bk")->AsFloat ;
				}
				else
				{
					retairange = 0.0;
				}
				retairange = 0-retairange;
				m_cash = m_cash +  shoukuan;
				if (numedtOdd->Value < retairange) {

                                        ShowMsg(Handle ,"�������㣡",3);
				}
				else if (numedtOdd->Value >= 0) {
					numedtDiscountedMoney->Value = dbnbedtReceivableMoney->Value;
					numedtTotalAmount->IntValue = dsetNtHeader->FieldByName("TotalAmount")->AsInteger;
					numedtCheck->Value = numedtOdd->Value;
					numedtRec->Value = numedtPaidinMoney->Value;
					dsetNtHeader->Edit();
					dsetNtHeader->FieldByName("RecCash")->AsFloat = m_cash;
					dsetNtHeader->Edit();
					dsetNtHeader->FieldByName("RecCardMoney")->AsFloat = m_card;
					dsetNtHeader->Edit();
					dsetNtHeader->FieldByName("State")->AsInteger = 1;
					UpdateNtHeader();
					///���»�Ա��������
					 String sql = "update CUST_MemberInfo set totalconsumption = totalconsumption + " + FloatToStr(dbnbedtReceivableMoney->Value) ;
								 sql = sql + " where id =  " + dsetNtHeader->FieldByName("memberid")->AsAnsiString  ;
						 TADOQuery * aq = new TADOQuery(this);
						 aq->Connection  = m_con ;
						 aq->Close();
						 aq->SQL->Clear();
						 aq->SQL->Add(sql);
						 aq->ExecSQL();
						 delete aq;

					 Addbook();
					PrintNtHeader();
					mniPrintNtHeader->Checked = xiaopiaoprint;
					tlbtn8Click(BtnNew);
					shoukuan = 0.00;
				}
				else
				{
            		TMsgDlgButtons btns;
					btns << mbOK << mbCancel;

					if (ShowMsg(Handle ,"������Ľ��㣬�Ƿ������",1)==1) {
						numedtDiscountedMoney->Value = dbnbedtReceivableMoney->Value;
						numedtTotalAmount->IntValue = dsetNtHeader->FieldByName("TotalAmount")->AsInteger;
						numedtCheck->Value = numedtOdd->Value;
						numedtRec->Value = numedtPaidinMoney->Value;
						dsetNtHeader->Edit();
						dsetNtHeader->FieldByName("RecCash")->AsFloat = m_cash;
						dsetNtHeader->Edit();
						dsetNtHeader->FieldByName("RecCardMoney")->AsFloat = m_card;
						dsetNtHeader->Edit();
						dsetNtHeader->FieldByName("State")->AsInteger = 1;
						UpdateNtHeader();
						Addbook();
						PrintNtHeader();
						mniPrintNtHeader->Checked = xiaopiaoprint;
							String sql = "update CUST_MemberInfo set totalconsumption = totalconsumption + " + FloatToStr(m_cash + m_card) ;
							sql = sql + " where id =  " + dsetNtHeader->FieldByName("memberid")->AsAnsiString  ;
							TADOQuery * aq = new TADOQuery(this);
							aq->Connection  = m_con ;
							aq->Close();
							aq->SQL->Clear();
							aq->SQL->Add(sql);
							aq->ExecSQL();
							delete aq;
						tlbtn8Click(BtnNew);
						shoukuan = 0.00;
					}
				}


		}
	}	
}
//---------------------------------------------------------------------------




void __fastcall TfrmRetailMng::DBGrid1DblClick(TObject *Sender)
{
	if (aq1->IsEmpty() ) {
        return;
	}
	DelInvalidNtHeader();
	QryNtHeader(aq1->FieldByName("RetailNtCode")->AsString );
	GroupBox2->Visible = false;
	dbnbedtAmount->Enabled = true;
	dbnbedtDiscount->Enabled = retaildiscountchange;
	numedtPaidinMoney->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailMng::RzButton1Click(TObject *Sender)
{
   	String *ID;
   //	ID = "";
	if (IsChecked() == 1)
	{

                ShowMsg(Handle ,"�ѽᵥ�ݲ����޸ģ�",3);
		return;
	}
	TfrmMemberCard * frm = new TfrmMemberCard(m_app,1,ID ,m_con);
	frm->ShowModal();
    delete frm;

	int count1 = dsetMember->RecordCount;
	dsetMember->Active = false;
	dsetMember->Active = true;
	int count2 = dsetMember->RecordCount;
	if (count2 > count1)
	{
		dsetMember->Last();
		dsetNtHeader->Edit();
		dsetNtHeader->FieldByName("MemberID")->AsInteger = dsetMember->FieldByName("ID")->AsInteger;
		UpdateNtHeader();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailMng::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void TfrmRetailMng::FormView()
{
	/*AnsiString sql;
	sql = "select * from BS_SYS_Formview where stgid = " + IntToStr(m_storageID) + " and ParentID = 1";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof)
	{
		if (aq->FieldByName("Name")->AsAnsiString == "�鵥" ) {
			tlbtn8->Visible = aq->FieldByName("state")->AsBoolean ;
		}
		if (aq->FieldByName("Name")->AsAnsiString == "����" ) {
			BtnNew->Visible = aq->FieldByName("state")->AsBoolean ;
		}
		if (aq->FieldByName("Name")->AsAnsiString == "ɾ��" ) {
			tlbtn1->Visible = aq->FieldByName("state")->AsBoolean ;
		}
		if (aq->FieldByName("Name")->AsAnsiString == "ɾ��" ) {
			tlbtn2->Visible = aq->FieldByName("state")->AsBoolean ;
		}
		if (aq->FieldByName("Name")->AsAnsiString == "ͳһ" ) {
			tlbtn3->Visible = aq->FieldByName("state")->AsBoolean ;
		}
		if (aq->FieldByName("Name")->AsAnsiString == "��Ա��" ) {
			tlbtn4->Visible = aq->FieldByName("state")->AsBoolean ;
		}
		if (aq->FieldByName("Name")->AsAnsiString == "��Ա��Ϣ����" ) {
			BtnAttachFiles->Visible = aq->FieldByName("state")->AsBoolean ;
		}
		if (aq->FieldByName("Name")->AsAnsiString == "ֱ���տ�" ) {
			tlbtnRecMoney->Visible = aq->FieldByName("state")->AsBoolean ;
		}
		if (aq->FieldByName("Name")->AsAnsiString == "����տ�" ) {
			tlbtnMixed->Visible = aq->FieldByName("state")->AsBoolean ;
		}
		if (aq->FieldByName("Name")->AsAnsiString == "��ӡ" ) {
			BtnPrint->Visible = aq->FieldByName("state")->AsBoolean ;
		}
		if (aq->FieldByName("Name")->AsAnsiString == "����" ) {
			BtnView->Visible = aq->FieldByName("state")->AsBoolean ;
		}
		if (aq->FieldByName("Name")->AsAnsiString == "��С��" ) {
			BtnAlignBottom->Visible = aq->FieldByName("state")->AsBoolean ;
		}
		if (aq->FieldByName("Name")->AsAnsiString == "Ǯ��" ) {
			BtnUpOneLevel->Visible = aq->FieldByName("state")->AsBoolean ;
		}
		if (aq->FieldByName("Name")->AsAnsiString == "�����ϼ�" ) {
			BtnFinish->Visible = aq->FieldByName("state")->AsBoolean ;
		}
		aq->Next();
	}   */
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailMng::RzButton2Click(TObject *Sender)
{
	if (RzButton2->Caption == "����(&E)") {
		RzButton2->Caption = "�˻�(&E)" ;
		Label2->Caption = "��������";
	}
	else
	{
		RzButton2->Caption = "����(&E)" ;
		Label2->Caption = "�����˻�";
	}
	/*if (dsetNote->IsEmpty() ) {
		return;
	}
	if (dsetNtHeader->FieldByName("State")->AsInteger == 1) {
		return;
	}
    if (tuihuopassword) {
    	if (!CheckOperateAuthority()) {
			return;
		}
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
	dbnbedtAmount->Enabled = true;
	dbnbedtDiscount->Enabled = true;


	AnsiString remarks = dsetNtHeader->FieldByName("Remarks")->AsAnsiString;
	if (remarks.Pos("(���鵥)")<=0 ) {
    	dsetNtHeader->Edit();
		dsetNtHeader->FieldByName("Remarks")->AsAnsiString  = dsetNtHeader->FieldByName("Remarks")->AsAnsiString + "(���鵥)";
		dsetNtHeader->UpdateBatch(arCurrent);
	}
	QryNtHeader();
	MoneyChange(); */
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailMng::N9Click(TObject *Sender)
{
	lblCatalog->Caption = "����";
	m_catalogSearchMode  = 5;
	edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailMng::BtnUpOneLevelClick(TObject *Sender)
{
	if ((USBInfoOpenBOX =="") || (USBInfoOpenBOX =="LPT1")||(USBInfoOpenBOX =="LPT2")||(USBInfoOpenBOX =="LPT3")) {

		int nLpt  ;
	char p[5]= {27,112,0,60,255};
	nLpt = FileOpen(TEXT("LPT1"), fmOpenWrite);
	try {
    	if (nLpt <= 0) return;
		FileWrite(nLpt, p , 5);
	}
	__finally
	{
		FileClose(nLpt);
	}
    	try
		{
			TfrmPrint *frm = new TfrmPrint(Application);
			frm->moneyboxopen();
			delete frm;
			//TfrmPrint::RetailPrint(dsetNtHeader->FieldByName("ID")->AsString, m_con);
		}
		catch(...)
		{
			  //	ShowMsg(Handle ,"��ӡʧ�ܣ�",3);
                  }

	}else
	 {
	   OpenMoneyBoxUSB();
	  }

}
//---------------------------------------------------------------------------


void __fastcall TfrmRetailMng::BtnPrintClick(TObject *Sender)
{
	//��ӡ
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1
		&& dsetNote->Active && dsetNote->RecordCount >= 1)
	{
		try
		{
			TfrmPrint *frm = new TfrmPrint(Application);
			frm->RetailPrint(dsetNtHeader->FieldByName("ID")->AsString, m_con,m_storageID);
			delete frm;
			//TfrmPrint::RetailPrint(dsetNtHeader->FieldByName("ID")->AsString, m_con);
		}
		catch(...)
		{
			ShowMsg(Handle ,"��ӡʧ�ܣ�",3);
        }
	}
}
//---------------------------------------------------------------------------
void  TfrmRetailMng::operterview(int operterid)
{
	AnsiString sql;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = linfo.con ;
	sql = "select name from sys_user where id = " + IntToStr(operterid);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	//lblOpName->Caption = aq->FieldByName("name")->AsString;
	edopername->Text = aq->FieldByName("name")->AsString;
	delete aq;
}
//---------------------------------------------------------------------------

bool  TfrmRetailMng::nobear()
{
	if (Amount <= 0 && !retailbear && Label2->Caption == "��������") {
		ShowMsg(Handle ,"������������ۣ�",3);
		return false;
	}
	return true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailMng::RzButton3Click(TObject *Sender)
{
    if (IsChecked() == 1)
	{
		return;
	}
	if (dbnbedtDiscount->Enabled) {
        return;
	}
	if (huankoupwd) {
		if (!CheckOperateAuthority())
			return;
	}

	dbnbedtDiscount->Enabled = true;
	dbnbedtDiscount->SetFocus();
}
//---------------------------------------------------------------------------
double TfrmRetailMng::DRound(double Value,int P)
{
	int Result = int(Value);
	double Tmp = Value -Result;
	if (Tmp == 0 ) return Value;
	for (int i =0; i < P; i++)Tmp*=10;
	if (Value>0) {
		Tmp = int(Tmp +0.5);
	}
	else
	{
		Tmp = int(Tmp -0.5);
	}
	for (int i =0; i < P; i++) {
		Tmp/=10;
	}
	return Result +Tmp;
}

//---------------------------------------------------------------------------

void __fastcall TfrmRetailMng::membkExit(TObject *Sender)
{
	if (IsChecked() == 1)
	{
		ShowMsg(Handle ,"�ѽᵥ�ݲ����޸�!",3);
		return;
	}
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		dsetNtHeader->Edit();
		dsetNtHeader->FieldByName("Remarks")->AsString = membk->Text ;
		dsetNtHeader->UpdateBatch(arAll);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailMng::RzButton4Click(TObject *Sender)
{
	if (dsetNtHeader->IsEmpty() ) {
    	return;
	}
	if (dsetNote->IsEmpty() ) {
		ShowMsg(Handle ,"�յ�����Ҫ�ҵ�!",3);
		return;
	}
	if (IsChecked() == 1)
	{
		ShowMsg(Handle ,"�ѽᵥ�ݲ��ܹҵ�!",3);
		return;
	}
	dsetNtHeader->Edit();
	dsetNtHeader->FieldByName("State")->AsInteger = 2;
	UpdateNtHeader();
	aq1->Active = false;
	aq1->Active = true;
	tlbtn8Click(BtnNew);
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailMng::RzButton5Click(TObject *Sender)
{
	if (IsChecked() == 0)
	{
		ShowMsg(Handle ,"���ڿ���״̬�²��ܽ����ᵥ!",3);
		return;
	}
	if (aq1->IsEmpty() ) {
		ShowMsg(Handle ,"Ŀǰû�е�����!",3);
		return;
	}

	if (GroupBox2->Visible == true) {
    	GroupBox2->Visible = false;
	}
	else
	{
    	GroupBox2->Visible = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailMng::RzButton6Click(TObject *Sender)
{
    if (IsChecked() == 1)
	{
		return;
	}
	if (!dbnbedtDiscount->Enabled) {
    	if (dbnbedtDiscount->Enabled) {
			return;
		}
	}
	if (huajiapwd) {
    	if (!CheckOperateAuthority())
			return;
	}

	edprice->Enabled = true;
	edprice->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailMng::dbnbedtDiscountExit(TObject *Sender)
{
	if (dsetNote->IsEmpty() ) {
    	return;
	}
	if (IsChecked() == 1)
	{
		ShowMsg(Handle ,"�ѽᵥ�ݲ����޸�!",3);
		return;
	}
	float discount =  dsetNote->FieldByName("DiscountedPrice")->AsFloat*100/dsetNote->FieldByName("FixedPrice")->AsFloat;
	if (!DiscountEnable(dbnbedtDiscount->Value,dsetNote->FieldByName("BkcatalogID")->AsInteger)) {
		ShowMsg(Handle ,"��������ۿۣ�",3);

		dsetNote->Edit();
		dsetNote->FieldByName("discount")->AsFloat = discount;
		dsetNote->Post();
		return;
	}
	//���ڳɱ����پͽ�ֹ����
	try
	{
	   if(Discountislow(dbnbedtDiscount->Value,32,dsetNote->FieldByName("price")->AsFloat))
	   {                          //"+FloatToStr(chenbendiscount)+"
		 ShowMsg(Handle ,"���ڸ���涨�ĳɱ��ۿۣ�",3);



		 numedtPaidinMoney->Enabled=false;
		 edtCatalog->Enabled=false;


		 tlbtnMixed->Enabled=false;
		 tlbtnRecMoney->Enabled=false;
		 return;

	   }else
		{ numedtPaidinMoney->Enabled=true;
		edtCatalog->Enabled=true;
		tlbtnMixed->Enabled=true;
		tlbtnRecMoney->Enabled=true;

	   }
	}catch(...){


	}

	try {
		edprice->Text = FormatFloat("0.00",dsetNote->FieldByName("Price")->AsFloat * dbnbedtDiscount->Value * 0.01 );
    } catch (...) {
	}

	UpdateNote();
	//��ʾ����
	if (Display) {
	   com_send(dsetNote->FieldByName("DiscountedPrice")->AsAnsiString,1);
	}
	if (numedtPaidinMoney->Value != 0.00) {
		MoneyChange();
	}

	if (!retaildiscountchange) {
	   dbnbedtDiscount->Enabled = false;
	}
}
//---------------------------------------------------------------------------
bool TfrmRetailMng::Discountislow(float discount,float cbprice,float price)
{
 int id;
 AnsiString sql,temp1;
 float stor;
  id= dsetNote->FieldByName("ID")->AsInteger;
  if (isblow) {   //�����ۿ�*����<�ɱ�*�޶��ۿ۲�������
		sql = "select a.zuidizk from  dbo.BS_StorageNote a left join   dbo.BS_RetailNote  b on a.bkcatalogID=b.bkcatalog";
		sql = sql +" where b.id ="+ IntToStr(id) +" order by a.id desc ";
		TADOQuery *aq3 = new TADOQuery(this);
	aq3->Connection = linfo.con ;

	aq3->Close();
	aq3->SQL->Clear();
	aq3->SQL->Add(sql);
	aq3->Open();
	temp1 =aq3->FieldByName("zuidizk")->AsAnsiString;
	if (temp1!="")
	{
		  stor =aq3->FieldByName("zuidizk")->AsFloat;
	   if (discount<stor ) {
		 return true;
	   }else return false;

	}
		   delete aq;
  }else return false;

}

void __fastcall TfrmRetailMng::edpriceKeyPress(TObject *Sender, wchar_t &Key)
{
	if ((Key < '0' || Key > '9') && (Key != '\b') && (Key != '.') && (Key != '\r') ) {
		Key = NULL;
	}
	if (Key == '\r') {
		if (dsetNote->IsEmpty() ) {
			return;
		}
		if (IsChecked() == 1)
		{
			ShowMsg(Handle ,"�ѽᵥ�ݲ����޸ģ�",3);
			return;
		}

		try {
            float discount;
			discount =  StrToFloat(edprice->Text)*100/dsetNote->FieldByName("Price")->AsFloat;
			if (!DiscountEnable(discount,dsetNote->FieldByName("BkcatalogID")->AsInteger)) {
				ShowMsg(Handle ,"��������ۿۣ�",3);
				return;
			}

			if (StrToFloat(edprice->Text) > dsetNote->FieldByName("Price")->AsFloat ) {
                ShowMsg(Handle ,"�ۼ۲��ܴ��ڸ��鶨�ۣ�",3);
				return;
			}

			dbnbedtDiscount->Value = discount;

			edprice->Text = FormatFloat("0.00",StrToFloat(edprice->Text));

			dsetNote->Edit();
			dsetNote->FieldByName("Discount")->AsFloat = discount;
			dsetNote->Post();
			UpdateNote();
			if (numedtPaidinMoney->Value != 0.00) {
				MoneyChange();
			}

		} catch (...) {
		}

		if (chdingwei->Checked && !dsetNote->Eof) {
			dbgrdNote->SetFocus();
			dsetNote->Next();
			dbgrdNote->SelectedRows->CurrentRowSelected = true;
			edprice->Enabled = true;
			edprice->SetFocus();
		}
		else
		{
			edtCatalog->SetFocus();
		}	
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailMng::dbgrdNoteCellClick(TColumn *Column)
{
	amount = dsetNote->FieldByName("Amount")->AsInteger ;
	ShowPrice();
}
//---------------------------------------------------------------------------

void TfrmRetailMng::ShowPrice()
{
	if (dsetNote->IsEmpty() ) {
		edprice->Text = "";
	}
	try {
		edprice->Text = FormatFloat("0.00",dsetNote->FieldByName("Price")->AsFloat *dsetNote->FieldByName("Discount")->AsFloat * 0.01);
	} catch (...) {
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmRetailMng::RzButton7Click(TObject *Sender)
{
	if (GroupBox5->Visible ) {
		GroupBox5->Visible = false;
	}
	else
	{
    	GroupBox5->Visible = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailMng::dbhdClick(TObject *Sender, TNavigateBtn Button)
{
	if (aqhd->IsEmpty() ) {
        return;
	}
	QryNtHeader(aqhd->FieldByName("RetailNtCode")->AsAnsiString );
}

//---------------------------------------------------------------------------

bool TfrmRetailMng::DiscountEnable(float discount,int catalogid)
{
  int booktype;
  float fdiscount;
        if ((mindiscount)||(minqikandiscount)) {  //���û�д�������
             AnsiString sql;
			 sql = "select type from BS_BookCatalog where id ="+IntToStr(catalogid);
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();
           booktype = aq->FieldByName("type")->AsInteger ;
		}else return true;

	if ((mindiscount)&&(booktype==0)) {  //ͼ������ۿ۴��ˣ������Ȿ��ͼ��
            //ͼ������ۿ�
			  fdiscount= mixdiscount;
		}
	else if ((minqikandiscount)&&(booktype==1)) {
             fdiscount=mixqikandiscount;

        }
        else
	{
		return true;
	}



		if (minstorage) {
			AnsiString sql;
			sql = "select case when sum(FixedPrice) <> 0 then sum(DiscountedPrice)/sum(FixedPrice) else 0 end as discount from BS_StorageNote "
				" join stk_bookinfo on BS_StorageNote.BkInfoID = stk_bookinfo.id "
				" join BS_BookCatalog on stk_bookinfo.BkcatalogID = BS_BookCatalog.id where BS_BookCatalog.id = " + IntToStr(catalogid);
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();
			if (aq->FieldByName("discount")->AsFloat == 0.00 ) {
				if (discount >= fdiscount) return true;
				else return false;

			}
			else
			{
				if (discount >= aq->FieldByName("discount")->AsFloat  )	return true;
				else return false;

			}
		}
		else
		{
                    	if (discount >= fdiscount) return true;
                        else return false;

		}

}

//---------------------------------------------------------------------------

void __fastcall TfrmRetailMng::dbgrdNoteDrawColumnCell(TObject *Sender, const TRect &Rect,
		  int DataCol, TColumn *Column, Grids::TGridDrawState State)
{
	if (dbgrdNote->DataSource->DataSet->FieldByName("Amount")->AsInteger < 0 ) {
		dbgrdNote->Canvas->FillRect(Rect);
		dbgrdNote->Canvas->Font->Color  = clRed;
		dbgrdNote->DefaultDrawColumnCell(Rect,DataCol,Column,State);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailMng::dbgrdNoteTitleClick(TColumn *Column)
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

void __fastcall TfrmRetailMng::numedtPaidinMoneyKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift)
{
	if(Display && dsetNote->RecordCount >= 1)
	{
		com_send(ReplaceStr(ReplaceStr(numedtPaidinMoney->Text,"-",""),"��",""),3);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailMng::RzToolButton1Click(TObject *Sender)
{
	TfrmMemberResult *frm = new TfrmMemberResult(Application,m_con);
	frm->userid = m_userID ;
	frm->stgid = m_storageID ;
	frm->Show();
}
//---------------------------------------------------------------------------
bool TfrmRetailMng::isContainEng(AnsiString ID)       //�ж�Ϊ����
{
   bool   rtn   =   false;
                  try
                  {
                                  AnsiString::TStringMbcsByteType   temp;
                                  for   (int   i=0;i   <   ID.Length();i++)
                                  {
                                                  temp   =   ID.ByteType(i);
                                                  if(temp   !=   mbSingleByte)
                                                  {
                                                                  rtn   =   true;
                                                                  break;
                                                  }
                                  }
                  }
                  catch(...)
                  {
                  }
                  return   rtn;

}
void __fastcall TfrmRetailMng::edcardKeyPress(TObject *Sender, wchar_t &Key)
{

			if (IsFirst) {   //�����һ���ַ�
			  StartTime =    GetTickCount();

			  IsFirst=false;
			}else
			{
			   
			   if (GetTickCount()-StartTime>100) {
				   edcard->Text="";
			   }
				IsFirst=true;
				return;
			}







	if (Key == '\r') {
		if (dsetNtHeader->IsEmpty() ) {
			return;
		}
		AnsiString sql;
                AnsiString talktxt;

                //�ж��Ƿ����ֻ���
                AnsiString sn,cardNum;
				sn = edcard->Text.Trim();
				if (sn.Length()<5) {
				 return;
				}
				bool cardyesornot=true;//�ǻ�Ա���Ż��ֻ���

                bool nameyesornot = false;

              if (sn.Length()!=0) {
                    //��Ա����
                     lbl2->Caption="����[F4]";
                    cardNum=dsetNtHeader->FieldByName("CardSN")->AsAnsiString;

                     if (sn.Length()==11) {
                           //�ֻ���
                           cardNum = dsetNtHeader->FieldByName("mobile")->AsAnsiString;
                           cardyesornot = false;
                           lbl2->Caption="�ֻ���[F4]";
                    }
                     if (isContainEng(sn)) { //�ж��Ƿ��Ǻ���

                          cardNum = edname->Text.Trim(); //dsetNtHeader->FieldByName("name")->AsAnsiString;;
                          lbl2->Caption="����[F4]";
                          nameyesornot = true;
                    }
                 }
                else{
                    	ShowMsg(this->Handle,"����Ļ�Ա���Ż��ֻ�����Ч����˶Ժ����䣡",3);
                         return;
                }

                AnsiString membstr;
                if (0==version) { //���۰�
                membstr=" 1=1 and ";
                    //membstr=" CUST_MemberInfo.stgidex = "+IntToStr(fstgid)+" and ";
                }else membstr=" 1=1 and ";

		if (cardNum!=sn) {
			AnsiString sql;
                        if (cardyesornot) {
							sql = "select ID,balance,PassWord,Available,datediff(d,getdate(),youxiaodate) as t from CUST_MemberInfo where "+membstr+" cardsn = '" + edcard->Text + "'" ;
						}else 	sql = "select ID,balance,PassWord,Available,datediff(d,getdate(),youxiaodate) as t from CUST_MemberInfo where "+membstr+" mobile = '" + sn + "'" ;
						 if (nameyesornot) {
                           	sql = "select ID,balance,PassWord,Available,datediff(d,getdate(),youxiaodate) as t from CUST_MemberInfo where "+membstr+" name = '" + edcard->Text.Trim() + "'" ;
                        }
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();
			if (aq->RecordCount > 0) {
				if (!aq->FieldByName("Available")->AsBoolean ) {
					ShowMsg(this->Handle,"��Ա������Ч��",3);
					return;
				}
				if (aq->FieldByName("t")->AsInteger < 0 ) {
					sql = "update CUST_MemberInfo set Available = 0 where ID = " + aq->FieldByName("ID")->AsAnsiString ;
					aq->Close();
					aq->SQL->Clear();
					aq->SQL->Add(sql);
					aq->ExecSQL();
					ShowMsg(Handle ,"��Ա���ѹ��ڣ������º˷���",3);
					return;
				}

				if (aq->FieldByName("PassWord")->AsAnsiString != "" ) {
                                    try
                                    {
					TfrmPwd *frm = new TfrmPwd(Application);
					if (frm->ShowModal() == mrOk ) {
						if (frm->GetPassword()!= aq->FieldByName("PassWord")->AsAnsiString) {
                            ShowMsg(this->Handle,"�������",3);
							return;
						}
					}
					else
					{
						return;
					}

                                        }catch(...)
                                        {}

				}


                               talktxt = "�������Ϊ"+aq->FieldByName("balance")->AsAnsiString+"Ԫ��";


				dsetNtHeader->Edit();
				dsetNtHeader->FieldByName("MemberID")->AsInteger = aq->FieldByName("ID")->AsInteger ;
				dsetNtHeader->UpdateBatch(arCurrent);
                             /*
				if (!dsetNote->IsEmpty() ) {
					int *Bkcatalogid,*bkinfoid,*amount,Recount;
					Recount = dsetNote->RecordCount ;
					Bkcatalogid = new int[Recount];
					bkinfoid = new int[Recount];
					amount = new int[Recount];
					for (int i = 0; i < Recount; i++) {
						Bkcatalogid[i] = dsetNote->FieldByName("BkcatalogID")->AsInteger ;
						bkinfoid[i] = dsetNote->FieldByName("BkInfoID")->AsInteger ;
						amount[i] = dsetNote->FieldByName("Amount")->AsInteger ;
						DelNote();
					}
					for (int i = 0; i < Recount; i++) {
						Amount = abs(amount[i]) + 1;
						AddNote(bkinfoid[i],Bkcatalogid[i],1);
						if (dsetNote->Active && dsetNote->RecordCount >= 1)
						{
							cmdUpdateNote->Parameters->ParamByName("@ID")->Value
							= dsetNote->FieldByName("ID")->AsInteger;
							cmdUpdateNote->Parameters->ParamByName("@Amount")->Value = amount[i];
							cmdUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 3;
							cmdUpdateNote->Execute();
						}
					}
				}     */
                             try {
					QryNtHeader();
					aq1->Active = false;
					aq1->Active = true;
				} catch (...) {
				}
				edtCatalog->SetFocus();


                                //��������
                                if (talk) {
                                   SpeckTxt(talktxt);
                                }


			}
			else
			{
				ShowMsg(this->Handle ,"�޴˻�Ա��Ϣ�����ʵ��",3);
			}
		}
		/*if (dsetNtHeader->FieldByName("RetailNtCode")->AsAnsiString != "0" ) {

		}
		else
		{
			sql = "update BS_RetailNoteHeader set RetailNtCode = dbo.UF_BS_BuildNtCode(" + IntToStr(m_storageID) + ", getdate(), 3,0) where id = " + dsetNtHeader->FieldByName("id")->AsAnsiString ;
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->ExecSQL();
		} */

	}
}
//---------------------------------------------------------------------------

void TfrmRetailMng::SpeckTxt(AnsiString txt)
{


        void (__stdcall*LC)(char *);
        HINSTANCE DLLInst = NULL;
        DLLInst = LoadLibrary("talk.dll");
        if (DLLInst) {
        LC = (void (__stdcall*)(char *)) GetProcAddress(DLLInst,
                                            "speack");
        }
        if (LC) LC(txt.c_str());
        else ShowMessage("������,������!");



}
void __fastcall TfrmRetailMng::edpriceExit(TObject *Sender)
{
	edprice->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailMng::edcardClick(TObject *Sender)
{
   edcard->SelectAll();
}
//---------------------------------------------------------------------------



void __fastcall TfrmRetailMng::btnorderClick(TObject *Sender)
{
//

//���Ȩ��

        AnsiString sql;
        sql = " select A.ID from sys_usergroup A join SYS_group B On A.GroupID = B.ID ";
        sql = sql +" join SYS_GroupAction C on B.ID = C.GroupID join sys_action D on C.ActionID = D.Code";
        sql = sql +" where actionname='��Ա����' and B.stgid = "+IntToStr(linfo.storageID)+" and userid = "+IntToStr(linfo.userID);
       TADOQuery *aq = new TADOQuery(NULL);
         aq->Connection = linfo.con;
         aq->Close();
         aq->SQL->Clear();
         aq->SQL->Add(sql);
         aq->Open();
         if (aq->RecordCount==0) {
              MessageBoxA(0,"��Ȩ�޲�����ģ��,�������Ա��ϵ!","����",MB_ICONASTERISK);
         return;
         }
          delete aq;


  Tfrmmemberorder * frm = new Tfrmmemberorder(Application);
  frm->init(linfo.con,linfo.userID,linfo.storageID);
  frm->Show();


}
//---------------------------------------------------------------------------
void TfrmRetailMng::CheckBirthDay()
{
   if (membertisi) {


   AnsiString sql;
   AnsiString todaystr;
   AnsiString huiyuan;
   todaystr = FormatDateTime("yyyy-mm-dd",Now());
   sql = " select * from dbo.CUST_MemberInfo where datediff(d,birthday,'"+todaystr+"')=0  ";

   TADOQuery *aqbirday = new TADOQuery(Application);
   aqbirday->Connection = linfo.con;
    aqbirday->Close();
    aqbirday->SQL->Clear();
    aqbirday->SQL->Add(sql);
    aqbirday->Open();
    while(!aqbirday->Eof)
    {

       huiyuan= "��Ա"+aqbirday->FieldByName("name")->AsString+"��������!";
    ShowMsg(this->Handle,huiyuan,3);

      aqbirday->Next();
    }

    Timer1->Enabled = false;
    delete aqbirday;


  }


}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailMng::Timer1Timer(TObject *Sender)
{
    CheckBirthDay();
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailMng::toolshowmainmenuClick(TObject *Sender)
{
    if (toolshowmainmenu->Caption =="��ʾ\r���˵�")
    {

      HANDLE hWindow = FindWindow("TfrmMain",NULL);
      SendMessage(hWindow ,WM_MYMESSAGE,1,0);
      toolshowmainmenu->Caption ="����\r���˵�";
    }else

    {
    HANDLE hWindow = FindWindow("TfrmMain",NULL);
    SendMessage(hWindow ,WM_MYMESSAGE,0,0);
      toolshowmainmenu->Caption ="��ʾ\r���˵�";

    }
}
//---------------------------------------------------------------------------
void TfrmRetailMng::pixiaoprint(int type)
{
AnsiString ps,sql;
try
{
        sql = " select '' Remarks,U.wsprinttitle+'������' as printName,"
        " U.wscontact,U.wstel,U.wsaddress,U.wsprintbk,F.name as clientname, "
        " A.retailntcode as WsaleNtCodeStr,A.hdtime ,A.hdtime  as maketime ,A.totalfixedprice fixedprice,A.totaldiscountedprice discountedprice "
         " ,0 addcosts,C.name as maker ,W.amount,W.discount discount, "
         "  Z.name as bookname,Z.price,A.totalamount "
         " from BS_RetailNoteHeader A  "
        " left join sys_user C on A.operatorid = C.ID  "
        " left join SYS_StorageInfo D on A.stgID = D.ID  "
        " left join CUST_MemberInfo F on A.memberid = F.ID "
        " left join dbo.BS_RetailNote W on W.retailntheaderid=A.ID  "
        " left join dbo.BS_BookCatalog Z on W.bkcatalog =Z.ID "
        " left join sys_printtitle U on D.id=U.stgid ";
        sql = sql + " where A.id in("+dsetNtHeader->FieldByName("ID")->AsString+")";
        a5aq->Close();
        a5aq->SQL->Clear();
        a5aq->SQL->Add(sql);
        a5aq->Open();

        ps = ExtractFilePath(Application->ExeName) +"wsaleA5.fr3";

        frxa5report->LoadFromFile(ps);

        frxa5report->PrepareReport(true);
        frxa5report->PrintOptions->ShowDialog = false;

if (type == 1) {      //Ԥ������ӡ
       frxa5report->ShowPreparedReport();
}else
{

   frxa5report->Print();

}

          }catch(...)
          {}


}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailMng::Y1Click(TObject *Sender)
{
pixiaoprint(1);
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailMng::P1Click(TObject *Sender)
{
pixiaoprint(2);
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailMng::FormShow(TObject *Sender)
{
	//
    if(0==version)
    {

       btnorder->Visible = false;


    }
}
//---------------------------------------------------------------------------


void __fastcall TfrmRetailMng::edcardContextPopup(TObject *Sender, TPoint &MousePos,
		  bool &Handled)
{
	  Handled = True;
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailMng::edcardKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == 'V' && Shift.Contains(ssCtrl))

	{


		 Clipboard()->Clear();


	}
}
//---------------------------------------------------------------------------

