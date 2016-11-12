//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ProcureMng.h"
#include "NoteCode.h"
#include "QryNoteCodeForm.h"
#include "SetNotesForm.h"
#include "mytrace.h"
//#include "SelectCustomerForm.h"
#include "RecMoneyForm.h"
#include "SelectCatalogForm.h"
#include "..\supplier\detailemessage.h"
#include "bookup.h"
#include "Addsyslog.h"
#include "NewBookinput1.h"
#include "bookQuery.h"
#include "NewBookModify.h"
#include "Unitcaigouquery.h"
#include "Unitorderquery.h"
#include "UnitBIOrder.h"
#include "unitinorder.h"
#include "bookhistory.h"
#include "retailbookup.h"
#include   <math.h>

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
TfrmProcureMng *frmProcureMng;
//---------------------------------------------------------------------------
__fastcall TfrmProcureMng::TfrmProcureMng(TComponent* Owner)
	: TfrmMDIChild(Owner)
	, m_catalogSearchMode(0)
	, m_bsmode(BSUnknown)
	, m_opmode(OPUnknown)
	, m_supplierID(-1)
{
	m_module = MTPur;

	this->WindowState = wsMaximized ;
	//::SetParent(this->Handle,panhandle);
}
//---------------------------------------------------------------------------
void TfrmProcureMng::Init(LandInfo* li)
{
	TfrmMDIChild::Init(li);
	userid = li->userID ;
	stgid = li->storageID ;
	//m_storageID = li->storageID ;
	lblOpName->Caption = m_opName;
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
	spQryNtHeader1->Connection = m_con;
	cmdDelNote->Connection = m_con;
	dsetVendor->Connection = m_con;
	dsetStaff->Connection = m_con;
	dsetLkpVendor->Connection = m_con;
	dsetBkstack->Connection = m_con;
	query->Connection = m_con;
	aq2->Connection = m_con;
	aqheader->Connection = m_con;
	dsetBkstack->Active = true;

           QFClientTiaoJian=" 1=1 ";
        QFSupplierTiaoJian=" 1=1 ";
          fqfsupplier=li->qfsupply;
         if (li->qfsupply) {
            QFSupplierTiaoJian=" stgid ="+IntToStr(stgid);
       }


        dsetVendor->CommandText=" select * from CUST_CustomerInfo where  Type=1 and customerstate=1 and "+QFSupplierTiaoJian+" order by name";
	dsetVendor->Active = true;
	dsetStaff->Active = true;
	dblkpcbbVendorID->KeyValue = 0;
	bearsaledataset->Connection = m_con;
	bearsaledataset->Active = true;
	dsetStaff->Connection = m_con;
	ChangeCatalogSearchMode();
	ChangeBsmode(BSNote);
	ChangeOpmode(OPAddNtHeader);
	addnotereturnvalue = 0;
	AnsiString sql;
	sql = "select * from sys_bsset where name = 'procurefindpwd'";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	findpwd = query->FieldByName("Value")->AsBoolean ;
	sql = "select * from sys_bsset where name = 'procuredeletepwd'";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	deletepwd = query->FieldByName("Value")->AsBoolean ;
	sql = "select ID,Name,Master from SYS_StorageInfo where id = " + IntToStr(stgid);
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	labtitle->Caption = query->FieldByName("Name")->AsString.Trim();
	if (!query->FieldByName("Master")->AsBoolean  ) {
       //	BtnWeekView->Enabled = false;
	}

	sql = "select catalogmodle from BS_Fastelurustyle where Name = '�ɹ�' and stgid = " + IntToStr(li->storageID);
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	if (query->RecordCount > 0) {
		m_catalogSearchMode = query->FieldByName("catalogmodle")->AsInteger;
		switch (m_catalogSearchMode) {
			case 1:
				lblCatalog->Caption = "��  ��";
				break;
			case 2:
				lblCatalog->Caption = "�Ա���";
				break;
			case 3:
				lblCatalog->Caption = "��  ��";
				break;
			case 5:
				lblCatalog->Caption = "��  ��";
				break;
			case 6:
				lblCatalog->Caption = "��  ��";
				break;
		default:
			;
		}
	}

	sql = "select cgprinttitle,cgcontact,cgtel,cgaddress,cgprintbk,shaddress,shcontact,shtel from sys_printtitle where stgid = " + IntToStr(m_storageID);
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();

	printbk = query->FieldByName("cgprintbk")->AsAnsiString ;
	printtitle = query->FieldByName("cgprinttitle")->AsAnsiString ;
	contact = query->FieldByName("cgcontact")->AsAnsiString ;
	tel = query->FieldByName("cgtel")->AsAnsiString ;
	address = query->FieldByName("cgaddress")->AsAnsiString ;
	shaddress = query->FieldByName("shaddress")->AsAnsiString ;
	shtel = query->FieldByName("shtel")->AsAnsiString ;
	shcontact = query->FieldByName("shcontact")->AsAnsiString ;

	sql = "select tel from sys_user where id = " + IntToStr(userid);
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	usertel = query->FieldByName("tel")->AsAnsiString ;
}
//---------------------------------------------------------------------------
void __fastcall TfrmProcureMng::FormClose(TObject *Sender, TCloseAction &Action)
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

void __fastcall TfrmProcureMng::tlbtn1Click(TObject *Sender)
{
	try
    {
	//ɾ��
	TControl* con = dynamic_cast<TControl*>(Sender);
	if (con)
	{
		ChangeOpmode(con->Tag);
	}
    }catch(...)
    {}
}
//---------------------------------------------------------------------------


void __fastcall TfrmProcureMng::tlbtn7Click(TObject *Sender)
{
	Close();
        HANDLE hWindow = FindWindow("TfrmMain",NULL);
        SendMessage(hWindow ,WM_MYMESSAGE,0,0);
}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::edtQryVendorKeyPress(TObject *Sender, wchar_t &Key)
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
		sql = " select * from CUST_CustomerInfo where Type =1 and customerstate=1 and "+QFSupplierTiaoJian+" and Name like '%"+ edtQryVendor->Text.Trim() + "%' order by name";
		dsetVendor->Active = false;
		dsetVendor->CommandText = sql;
		dsetVendor->Active = true;
		dsetVendor->First();
		dblkpcbbVendorID->KeyValue = dsetVendor->FieldByName("ID")->AsInteger ;
		dsetNtHeader->Edit();
		dsetNtHeader->FieldByName("VendorID")->AsInteger = dsetVendor->FieldByName("ID")->AsInteger;
		dsetNtHeader->Post();
		dblkpcbbVendorID->SetFocus();
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmProcureMng::edtCatalogKeyPress(TObject *Sender, wchar_t &Key)
{       int results;
	if (m_catalogSearchMode == 6) {
		if ((Key < '0' || Key > '9') && (Key != '\b') && (Key != '.') && (Key != '\r') ) {
            Key = NULL;
		}
	}
	//
	if (Key == '\r')
	{
		if (!dsetNote->Active || !dsetNtHeader->Active
			|| (dsetNtHeader->Active && dsetNtHeader->RecordCount < 1))
			return;
		if (dblkpcbbVendorID->Enabled) {

                         ShowMsg(Handle ,"�ڹ�Ӧ�̴�ʹ�ûس���ȷ����ѡ��Ĺ�Ӧ�̣�",3);
			return;
		}
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

                                          ShowMsg(Handle ,"��������ȷ�Ķ��ۣ�",3);
					return;
				}
			}

			TfrmSelectCatalog* frm = new TfrmSelectCatalog(Application,m_con);
			LandInfo li;
			li.app = m_app;
			li.con = m_con;
			li.userID = userid;
			li.storageID = stgid;
			frm->Init(&li);
			frm->DoModalType = 5;
			frm->Procurefrm  = this;
			frm->SetSearchMode(m_catalogSearchMode, edtCatalog->Text);

                        frm->SelectAll = false;


                            //�ڿ�����
                            if (edtCatalog->Text.Trim().Length()>13) {

                                frm->qikan= true;
                                frm->qikanhao =edtCatalog->Text.SubString(14,edtCatalog->Text.Trim().Length()-13) ;
                            }
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
				if (frm->SelectAll) {
					 for (int i = 0; i < frm->lengthint  ; i++) {
						 AddNote(1,frm->BkcatalogiD[i]) ;
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
						if ( !dsetNote->Locate("BkcatalogID",str,Opts))
						{
							if (AddNote(0, catalogID))
							{
								if (addnotereturnvalue == -2) {
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
										else if (chfsluru->Checked) {
											edtCatalog->SetFocus();
										}
									}
									else
									{
										dbnbedtAmount ->SetFocus();
									}
								}
							}
							else
								ShowMessage("����޸���!");
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
			else {
				if (!frm->findbook) {     //��������
					if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
					{
						Tfrmnewbook1 *frma = new Tfrmnewbook1(m_app,m_con);
						frma->ProcureMng = this;
						frma->modle = 3;

						frma->editcode->Text = edtCatalog->Text ;
						PostMessage(frma->editcode->Handle, WM_KEYDOWN,VK_RETURN,0);
						if (mbOK == frma->ShowModal())
						{

						}
						delete frma;
						dbnbedtAmount->SetFocus();
					}
				}
			}
			edtCatalog->Text = "";
			delete frm;
                                        //��ѯ���ܿ��
		}
	}
}
//---------------------------------------------------------------------------

void TfrmProcureMng::ChangeCatalogSearchMode()
{
	if(m_catalogSearchMode==3) {
		m_catalogSearchMode=6;
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
		lblCatalog->Caption = "���";
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

void TfrmProcureMng::ChangeBsmode(BSMode bsmode)
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

void TfrmProcureMng::ChangeOpmode(OPMode opmode)
{
	if (opmode == m_opmode
		&& (opmode == OPDelNtHeader))
		return;

	//1Ϊ�鵥ģʽ 2Ϊ���ӵ�ͷģʽ 3Ϊɾ����ͷģʽ 4Ϊ���ӵ�ģʽ 5Ϊɾ����ģʽ 6Ϊͳһģʽ 7Ϊ�ֳ��տ�ģʽ
	switch (opmode)
	{
	case OPFind:
		{
			if (findpwd) {
				if (!CheckOperateAuthority())
					return;
			}

			Tfrmcaigouquery *frm = new Tfrmcaigouquery(Application,m_con,stgid,1,0,fqfsupplier);
			if (frm->ShowModal() == mrOk)
			{
				VendorView();
				DelInvalidNtHeader();
				edtCatalog->Text = "";
				edtQryVendor->Text = "";
				AnsiString code = frm->GetNoteCode();
				AnsiString sqlwhere = frm->GetWhere();
				try
				{
					//LockWindowUpdate(dbgrdNote->Handle);//����ָ�����ڣ���ֹ�����¡�
					QryNtHeader(code);
					DBNavigator1->Enabled = true;
					//cbstate->ItemIndex = dsetNtHeader->FieldByName("state")->AsInteger ;
					AnsiString sql;
					if (sqlwhere != "") {
						sql = "select * from BS_ProcureNoteHeader " + sqlwhere ;
						aqheader->Close();
						aqheader->SQL->Clear();
						aqheader->SQL->Add(sql);
						aqheader->Open();
						TLocateOptions Opts;
						Opts.Clear();
						Opts << loPartialKey;
						aqheader->Locate("ProcureNtCode", code, Opts);
					}
				}
				__finally
				{
					//LockWindowUpdate(NULL);
				}
			}

			m_opmode = opmode;
			delete frm;
		}
		break;
	case OPAddNtHeader:
		{
			//����ϴ�������ģʽ������û�мӽ��κ����ݣ���������
			if (m_opmode == OPAddNtHeader &&
				dsetNote->Active && dsetNote->RecordCount < 1)
				return;

			if (m_opmode == OPDelNote
				&& dsetNote->Active && dsetNote->RecordCount < 1)
				return;
			dblkpcbbVendorID->Enabled = true;
			edtQryVendor->Enabled = true;
			spnewbook->Enabled = false;
			VendorView();
			dblkpcbbVendorID->KeyValue = 0;
			edtCatalog->Text = "";
			edtQryVendor->Text = "";
			AddNtHeader();
			DBNavigator1->Enabled = false;
			m_opmode = opmode;
            edtQryVendor->SetFocus();
        }
		break;
	case OPDelNtHeader:
		{
			if (!CheckOperateAuthority())
				return;

			edtCatalog->Text = "";
			edtQryVendor->Text = "";
//			DelNtHeader();
			m_opmode = opmode;
        }
		break;
	case OPAddNote:
    	edtCatalog->Text = "";
		edtCatalog->SetFocus();
		m_opmode = opmode;
		break;
	case OPDelNote:
		if (deletepwd) {
        	if (!CheckOperateAuthority())
				return;
		}
		else
		{
			if (dbgrdNote->DataSource->DataSet->RecordCount!=0 ) {
				if (MessageBoxA(0,"ȷ��Ҫɾ���ü�¼��?","ѯ��",MB_ICONQUESTION|MB_OKCANCEL)!=1 )
					return;
			}
		}

		DelNote();
		ResetNtHeader();
    	m_opmode = opmode;
		break;
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
		break;
	case OPRecCash:

    default:
        break;
	}
}

void TfrmProcureMng::BatchSetNotes(int amount, float discount, int mode)
{
	if (dsetNote->Active && dsetNote->RecordCount >= 1)
	{
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
		else
			return;

		switch(mode)
		{
		case 1://���߾�����
			cmdBatchUpdateNote->Parameters->ParamByName("@IDS")->Value = ids;
			cmdBatchUpdateNote->Parameters->ParamByName("@Amount")->Value = amount;
			cmdBatchUpdateNote->Parameters->ParamByName("@Discount")->Value = discount;
			cmdBatchUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 5;
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
			cmdBatchUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 5;
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
			cmdBatchUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 5;
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

void __fastcall TfrmProcureMng::mniBsNoteSendbackClick(TObject *Sender)
{
	//���ӵ�������
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
void __fastcall TfrmProcureMng::tlbtn4Click(TObject *Sender)
{
	//Excel����
	//Excel����
	if (dsetNote->Active && dsetNote->RecordCount >= 1)
	{
        DbgridToExcel(dbgrdNote);
	}
}//Excel��������
bool __fastcall TfrmProcureMng::DbgridToExcel(TRzDBGrid* dbg)
{
	AnsiString temptext,path;
	int k = dbg->DataSource ->DataSet ->RecordCount ,n=0;

	savedlg->FileName = StringReplace(dblkpcbbVendorID->Text.Trim() +dbedtWsaleNtCode->Text.Trim() ,"\\","-",TReplaceFlags()<<rfReplaceAll) + "�ɹ���";
	if (savedlg->Execute())
	{
		String DBPath,Name;
		DBPath = Sysutils::ExtractFilePath(savedlg->FileName .c_str()  );
		Name = Sysutils::ExtractFileName(savedlg->FileName .c_str() );
		DBPath = DBPath + Name + ".xls";
		path =  DBPath;
	}else return false;
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
		iFileHandle = FileCreate(path.c_str());
	*/

    Variant  v,vSheet,R,xWorkbook;
	v   =Variant::CreateObject("Excel.Application");
	v.OlePropertySet("Visible",true);
	v.OlePropertyGet("WorkBooks").OleFunction("Add");
	xWorkbook = v.OlePropertyGet("ActiveWorkBook");
	vSheet =  xWorkbook.OlePropertyGet("ActiveSheet");

	int t2 = dbg->DataSource ->DataSet ->RecordCount ;

	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",1,1),vSheet.OlePropertyGet("Cells",t2+11,14)); //ȡ�úϲ�������
	R.OlePropertyGet("Borders",2).OlePropertySet("linestyle",1);
	R.OlePropertyGet("Borders",4).OlePropertySet("linestyle",1);
                                                               printtitle=labtitle->Caption+ Label2->Caption;
	v.OlePropertyGet("Cells",1,1).OlePropertySet("Value",printtitle .c_str() );

	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",1,1),vSheet.OlePropertyGet("Cells",2,14)); //ȡ�úϲ�������
	R.OleProcedure("Merge");
	R.OlePropertyGet("Cells").OlePropertyGet("Font").OlePropertySet("Bold",true);
	R.OlePropertyGet("Cells").OlePropertyGet("Font").OlePropertySet("Name","����");   //����
	R.OlePropertyGet("Cells").OlePropertyGet("Font").OlePropertySet("size",16);
	R.OlePropertySet("HorizontalAlignment",3);

	temptext = "��ϵ�ˣ�" + lblOpName->Caption ;
	v.OlePropertyGet("Cells",3,1).OlePropertySet("Value",temptext.c_str() );
	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",3,1),vSheet.OlePropertyGet("Cells",3,4)); //ȡ�úϲ�������
	R.OleProcedure("Merge");

	temptext = "�绰��" + usertel ;
	v.OlePropertyGet("Cells",3,5).OlePropertySet("Value",temptext.c_str() );
	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",3,5),vSheet.OlePropertyGet("Cells",3,14)); //ȡ�úϲ�������
	R.OleProcedure("Merge");

	temptext = "��ַ��" + address ;
	v.OlePropertyGet("Cells",4,1).OlePropertySet("Value",temptext.c_str() );
	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",4,1),vSheet.OlePropertyGet("Cells",4,14)); //ȡ�úϲ�������
	R.OleProcedure("Merge");

    temptext = "�ɹ����ţ�" + dbedtWsaleNtCode->Text ;
	v.OlePropertyGet("Cells",5,1).OlePropertySet("Value",temptext.c_str() );
	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",5,1),vSheet.OlePropertyGet("Cells",5,4)); //ȡ�úϲ�������
	R.OleProcedure("Merge");

	temptext = "��Ӧ�����ƣ�" + dblkpcbbVendorID->Text ;
	v.OlePropertyGet("Cells",5,5).OlePropertySet("Value",temptext.c_str() );
	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",5,5),vSheet.OlePropertyGet("Cells",5,8)); //ȡ�úϲ�������
	R.OleProcedure("Merge");

	temptext = "��ϵ�ˣ�"+ dsetVendor->FieldByName("Contact")->AsString ;
	v.OlePropertyGet("Cells",5,9).OlePropertySet("Value",temptext.c_str() );
	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",5,9),vSheet.OlePropertyGet("Cells",5,14)); //ȡ�úϲ�������
	R.OleProcedure("Merge");

	temptext = "�ɹ����ڣ�" +  DateToStr(dbdtedtHdTime->Date ) ;
	v.OlePropertyGet("Cells",6,1).OlePropertySet("Value",temptext.c_str() );
	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",6,1),vSheet.OlePropertyGet("Cells",6,4)); //ȡ�úϲ�������
	R.OleProcedure("Merge");

	temptext = "��Ӧ�̵绰��" + dsetVendor->FieldByName("Telephone")->AsString ;
	v.OlePropertyGet("Cells",6,5).OlePropertySet("Value",temptext.c_str() );
	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",6,5),vSheet.OlePropertyGet("Cells",6,8)); //ȡ�úϲ�������
	R.OleProcedure("Merge");

	temptext = "���棺"+ dsetVendor->FieldByName("Fax")->AsString ;
	v.OlePropertyGet("Cells",6,9).OlePropertySet("Value",temptext.c_str() );
	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",6,9),vSheet.OlePropertyGet("Cells",6,14)); //ȡ�úϲ�������
	R.OleProcedure("Merge");

	temptext = "��ע��" + membk->Text;
	v.OlePropertyGet("Cells",7,1).OlePropertySet("Value",temptext.c_str() );
	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",7,1),vSheet.OlePropertyGet("Cells",7,14)); //ȡ�úϲ�������
	R.OleProcedure("Merge");

	temptext = "��Ӧ�̵�ַ��"+ dsetVendor->FieldByName("Address")->AsString ;
	v.OlePropertyGet("Cells",8,1).OlePropertySet("Value",temptext.c_str() );
	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",8,1),vSheet.OlePropertyGet("Cells",8,14)); //ȡ�úϲ�������
	R.OleProcedure("Merge");

	temptext = "��Ʒ�֣�" +  IntToStr(t2) ;
	v.OlePropertyGet("Cells",9,1).OlePropertySet("Value",temptext.c_str() );
	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",9,1),vSheet.OlePropertyGet("Cells",9,4)); //ȡ�úϲ�������
	R.OleProcedure("Merge");

	temptext = "��������" + dbnbedt2->Text ;
	v.OlePropertyGet("Cells",9,5).OlePropertySet("Value",temptext.c_str() );
	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",9,5),vSheet.OlePropertyGet("Cells",9,8)); //ȡ�úϲ�������
	R.OleProcedure("Merge");

	temptext = "������"+ dbnbedt3->Text ;
	v.OlePropertyGet("Cells",9,9).OlePropertySet("Value",temptext.c_str() );
	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",9,9),vSheet.OlePropertyGet("Cells",9,14)); //ȡ�úϲ�������
	R.OleProcedure("Merge");

    n = 9;
	int t1= 0;
	for(int q=0;q<dbg->FieldCount-2 ;++q)
	{
		if (dbg->Columns->Items[q]->Visible == true) {
			t1++;
			temptext = "'"+ dbg->Columns ->Items [q]->Title ->Caption;
			v.OlePropertyGet("Cells",1+n,(t1)).OlePropertySet("Value",temptext .c_str() );
			temptext = temptext + dbg->Columns ->Items [q]->Title ->Caption + ",";
		}
	}
	//iFileLength   =   FileSeek(iFileHandle,0,2);
	//FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	dsetNote->DisableControls();
	dbg->DataSource ->DataSet ->First();
	for(int   i=2+n;i<=t2+1+n ;i++)
	{
		t1=0;
		temptext = "\n";
		for(int j=1;j<dbg->Columns ->Count-2  ;j++)
		{
			if (dbg->Columns->Items[j-1]->Visible == true) {
				if (dbg->Columns ->Items [j-1]->FieldName == "ISBN") {
					t1++;
					temptext = "'"+ dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
					//temptext = temptext + "'" + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
				}
				/*else if (dbg->Columns ->Items [j-1]->FieldName == "CatalogName") {
					t1++;
					AnsiString bookname;
					int len;
					bookname = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					bookname = StringReplace(bookname , ",",".",TReplaceFlags()<<rfReplaceAll);
					//temptext = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					//v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
					temptext = temptext + bookname + ",";
				} */
				else if (dbg->Columns ->Items [j-1]->FieldName == "Discount") {
					t1++;
					temptext = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
					//temptext = temptext + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + "%,";
				}
				else  if (dbg->Columns ->Items [j-1]->FieldName == "PressCount") {
                                        	t1++;
					temptext = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
                                        v.OlePropertyGet("Cells",i,t1).OlePropertySet("NumberFormatLocal","@");
					v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
                                      }
				else {
					t1++;
                                        if (dbg->Columns ->Items [j-1]->FieldName!="stkamount") {
                                          temptext = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );
                                        }
					 // AsString .c_str()
					//temptext = temptext + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
				}
			}
		}
		//iFileLength   =   FileSeek(iFileHandle,0,2);
		//FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
		dbg->DataSource ->DataSet ->Next() ;
	}
	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",10,3),vSheet.OlePropertyGet("Cells",t2+10,3)); //ȡ�úϲ�������  ��
	R.OlePropertySet("WrapText", true);//����ָ�����������еĵ�Ԫ���е��ı��Զ�����

	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",10,14),vSheet.OlePropertyGet("Cells",t2+10,14)); //ȡ�úϲ�������  ��
	R.OlePropertySet("WrapText", true);//����ָ�����������еĵ�Ԫ���е��ı��Զ�����

	v.OlePropertyGet("Cells",t2+2+n,1).OlePropertySet("Value","�ϼ�");
	temptext = dbnbedt2->Text ;
	v.OlePropertyGet("Cells",t2+2+n,6).OlePropertySet("Value",temptext .c_str() );
	temptext = dbnbedt3->Text ;
	v.OlePropertyGet("Cells",t2+2+n,8).OlePropertySet("Value",temptext .c_str() );
	temptext = dbnbedt4->Text ;
	v.OlePropertyGet("Cells",t2+2+n,9).OlePropertySet("Value",temptext .c_str() );

	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",10,11),vSheet.OlePropertyGet("Cells",t2+11,12)); //ȡ�úϲ�������  ��
	R.OlePropertySet("NumberFormatLocal", "0.00");//����ָ�������е����е�Ԫ���ʽΪС���ٷֱ�

	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",10,7),vSheet.OlePropertyGet("Cells",t2+11,7)); //ȡ�úϲ�������  ��
	R.OlePropertySet("NumberFormatLocal", "0.00");//����ָ�������е����е�Ԫ���ʽΪС���ٷֱ�

	temptext = "�Ƶ�Ա��" + lblOpName->Caption ;
	v.OlePropertyGet("Cells",t2+3+n,1).OlePropertySet("Value",temptext .c_str() );
	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",t2+3+n,1),vSheet.OlePropertyGet("Cells",t2+3+n,14)); //ȡ�úϲ�������
	R.OleProcedure("Merge");

	temptext = "�ջ���ϵ�ˣ�" + shcontact ;
	v.OlePropertyGet("Cells",t2+4+n,1).OlePropertySet("Value",temptext .c_str() );
	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",t2+4+n,1),vSheet.OlePropertyGet("Cells",t2+4+n,14)); //ȡ�úϲ�������
	R.OleProcedure("Merge");

	temptext = "�ջ���ϵ�绰��" + shtel ;
	v.OlePropertyGet("Cells",t2+5+n,1).OlePropertySet("Value",temptext .c_str() );
	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",t2+5+n,1),vSheet.OlePropertyGet("Cells",t2+5+n,14)); //ȡ�úϲ�������
	R.OleProcedure("Merge");

	temptext = "�ջ���ַ��" + shaddress ;
	v.OlePropertyGet("Cells",t2+6+n,1).OlePropertySet("Value",temptext .c_str() );
	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",t2+6+n,1),vSheet.OlePropertyGet("Cells",t2+6+n,14)); //ȡ�úϲ�������
	R.OleProcedure("Merge");

	v.OlePropertyGet("Cells",t2+7+n,1).OlePropertySet("Value",printbk .c_str() );
	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",t2+7+n,1),vSheet.OlePropertyGet("Cells",t2+7+n,14)); //ȡ�úϲ�������
	R.OleProcedure("Merge");

	dsetNote->EnableControls();

	try {
		xWorkbook.OleFunction("SaveAs",path.c_str());
	} catch (Exception &E) {
		//ShowMessage(E.Message);
	}

	/*temptext = "\n";
	AnsiString tamount,mayang,shiyang;
	tamount =  dbnbedt2->Text;
	mayang = dbnbedt3->Text;
	shiyang = dbnbedt4->Text;
	mayang = StringReplace(mayang , ",","",TReplaceFlags()<<rfReplaceAll);
	shiyang = StringReplace(shiyang , ",","",TReplaceFlags()<<rfReplaceAll);
	tamount = StringReplace(tamount , ",","",TReplaceFlags()<<rfReplaceAll);

	temptext = temptext + "�ϼ�,,,,,,,," + tamount + ",," + mayang + "," + shiyang ;

	temptext = temptext + "�ϼ�,,,,,," + RzDBNumericEdit1->Text + ",," + mayang + "," + shiyang;
	temptext = temptext + "�ϼ�,,,,,," + RzDBNumericEdit1->Text + ",," + RzDBNumericEdit2->Text + "," + RzDBNumericEdit3->Text;
	iFileLength   =   FileSeek(iFileHandle,0,2);
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	FileClose(iFileHandle);

	MessageBox(0,"������ϣ�","��ʾ" ,MB_OK);     */
	return false;
}
//---------------------------------------------------------------------------}
//---------------------------------------------------------------------------
void TfrmProcureMng::QryNtHeader(String code, bool qrybkstack)
{
	spQryNtHeader->Active = false;
	spQryNtHeader1->Active = false;
	spQryNtHeader1->Parameters->ParamByName("@NtCode")->Value = code;
	spQryNtHeader1->Parameters->ParamByName("@Bsmode")->Value = 5;
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
		if (dsetNote->RecordCount > 0) {
        	dblkpcbbVendorID->Enabled = false;
			spnewbook->Enabled = true;
		}
		dsrcNote->DataSet = dsetNote;
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "0.00";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = "0.00";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = "0.00";

		if (dsetNtHeader->RecordCount > 0) {
			dbdtedtHdTime->Date = dsetNtHeader->FieldByName("HdTime")->AsDateTime ;
			dbdtedtHdyujiTime->Date = dsetNtHeader->FieldByName("yujidate")->AsDateTime ;
		}
		operterview(dsetNtHeader->FieldByName("OperatorID")->AsInteger );
		membk->Text =  dsetNtHeader->FieldByName("Remarks")->AsString;
		dsetNote->Last();
		/*if (dsetNote->FieldByName("amount")->AsInteger < 0 ) {
			   Label2->Caption = "�ɹ�������";
			   m_bsmode = BSNoteSendback;
		} */
		dsetNote->AfterScroll = dsetNoteAfterScroll;
		if (dsetNtHeader->FieldByName("Procurestr")->AsAnsiString != "") {
			edtQryVendor->Enabled = false;
			dblkpcbbVendorID->Enabled = false;
			dblkpcbbStaffID->Enabled = false;
			dbnbedtAddCosts->Enabled = false;
			RzButton1->Enabled = false;
			dbdtedtHdTime->Enabled = false;
			dbdtedtHdyujiTime->Enabled = false;
			GroupBox2->Enabled = true;
			spnewbook->Enabled = true;
		}
		else
		{
			edtQryVendor->Enabled = true;
			dblkpcbbVendorID->Enabled = true;
			dblkpcbbStaffID->Enabled = true;
			dbnbedtAddCosts->Enabled = true;
			RzButton1->Enabled = true;
			dbdtedtHdTime->Enabled = true;
			dbdtedtHdyujiTime->Enabled = true;
			GroupBox2->Enabled = false;
			spnewbook->Enabled = false;
		}
		if (qrybkstack)
		{
            QryBkstack();
		}
	}
	catch(Exception &E)
	{
		//ShowMessage(E.Message);
		//ShowMessage("�õ������ڣ�");
	}
}

void TfrmProcureMng::QryNtHeader(bool qrybkstack)
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
		spQryNtHeader->Parameters->ParamByName("@Bsmode")->Value =5;
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
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00";
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "0.00";
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = "0.00";
			((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = "0.00";
			if (dsetNtHeader->RecordCount > 0) {
				dbdtedtHdTime->Date = dsetNtHeader->FieldByName("HdTime")->AsDateTime ;
				dbdtedtHdyujiTime->Date = dsetNtHeader->FieldByName("yujidate")->AsDateTime ;
			}
			operterview(dsetNtHeader->FieldByName("OperatorID")->AsInteger );
			membk->Text =  dsetNtHeader->FieldByName("Remarks")->AsString;
			dsetNote->AfterScroll = dsetNoteAfterScroll;
			if (dsetNtHeader->FieldByName("Procurestr")->AsAnsiString != "") {
				edtQryVendor->Enabled = false;
				//dblkpcbbVendorID->Enabled = false;
				dblkpcbbStaffID->Enabled = false;
				dbnbedtAddCosts->Enabled = false;
				RzButton1->Enabled = false;
				dbdtedtHdTime->Enabled = false;
				dbdtedtHdyujiTime->Enabled = false;
				GroupBox2->Enabled = true;
				spnewbook->Enabled = true;
			}
			else
			{
				edtQryVendor->Enabled = true;
				dblkpcbbVendorID->Enabled = true;
				dblkpcbbStaffID->Enabled = true;
				dbnbedtAddCosts->Enabled = true;
				RzButton1->Enabled = true;
				dbdtedtHdTime->Enabled = true;
				dbdtedtHdyujiTime->Enabled = true;
				GroupBox2->Enabled = false;
				spnewbook->Enabled = false;
			}
			if (qrybkstack)
			{
				QryBkstack();
			}
		}
		catch(...)
		{
			//ShowMessage("�õ������ڣ�");
		}
	}
}

void TfrmProcureMng::QryNtHeader(int id, bool qrybkstack)
{
	//��ѯ��ͷ
	spQryNtHeader1->Active = false;
	spQryNtHeader->Active = false;
	spQryNtHeader->Parameters->ParamByName("@ID")->Value = id;
	spQryNtHeader->Parameters->ParamByName("@Bsmode")->Value = 5;
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
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "0.00";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = "0.00";
		((TFloatField *)dbgrdNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = "0.00";
		dsetNote->AfterScroll = dsetNoteAfterScroll;
        if (dsetNtHeader->RecordCount > 0) {
			dbdtedtHdTime->Date = dsetNtHeader->FieldByName("HdTime")->AsDateTime ;
			dbdtedtHdyujiTime->Date = dsetNtHeader->FieldByName("yujidate")->AsDateTime ;
		}
		operterview(dsetNtHeader->FieldByName("OperatorID")->AsInteger );
		membk->Text =  dsetNtHeader->FieldByName("Remarks")->AsString;
		if (dsetNtHeader->FieldByName("Procurestr")->AsAnsiString != "") {
			edtQryVendor->Enabled = false;
			dblkpcbbVendorID->Enabled = false;
			dblkpcbbStaffID->Enabled = false;
			dbnbedtAddCosts->Enabled = false;
			RzButton1->Enabled = false;
			dbdtedtHdTime->Enabled = false;
			dbdtedtHdyujiTime->Enabled = false;
			GroupBox2->Enabled = true;
			spnewbook->Enabled = true;
		}
		else
		{
			edtQryVendor->Enabled = true;
			dblkpcbbVendorID->Enabled = true;
			dblkpcbbStaffID->Enabled = true;
			dbnbedtAddCosts->Enabled = true;
			RzButton1->Enabled = true;
			dbdtedtHdTime->Enabled = true;
			dbdtedtHdyujiTime->Enabled = true;
			GroupBox2->Enabled = false;
			spnewbook->Enabled = false;
		}
		if (qrybkstack)
		{
			QryBkstack();
		}
	}
	catch(...)
	{
    	//ShowMessage("�õ������ڣ�");
    }
}

void TfrmProcureMng::AddNtHeader()
{
	spQryNtHeader->Active = false;
	spQryNtHeader1->Active = false;
	cmdAddNtHeader->Parameters->ParamByName("@StgID")->Value = stgid;
	cmdAddNtHeader->Parameters->ParamByName("@OperatorID")->Value = userid;
	cmdAddNtHeader->Parameters->ParamByName("@Bsmode")->Value = 5;     //�ɹ�
	MYTRACEF(_T("add note header @StgID=%d,@OperatorID=%d,@Bsmode=%d"),stgid,userid,5);
	cmdAddNtHeader->Execute();
	int id = cmdAddNtHeader->Parameters->ParamByName("@RETURN_VALUE")->Value;
	try
	{
		//LockWindowUpdate(dbgrdNote->Handle);//����ָ�����ڣ���ֹ�����¡�
		QryNtHeader(id);
		logmessage = "����һ��ɹ���" + dsetNtHeader->FieldByName("ProcureNtCode")->AsString ;
		AddEvent(1,"һ��ɹ�����",userid,stgid,logmessage,m_con);
	}
	__finally
	{
		//LockWindowUpdate(NULL);
	}
}

void TfrmProcureMng::DelInvalidNtHeader()
{
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1
		&& dsetNtHeader->FieldByName("Procurestr")->AsAnsiString == "")
	{
        DelNtHeader();
    }
}

void TfrmProcureMng::DelNtHeader()
{
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		cmdDelNtHeader->Parameters->ParamByName("@ID")->Value
			= dsetNtHeader->FieldByName("ID")->AsInteger;
		int id = dsetNtHeader->FieldByName("ID")->AsInteger;
		cmdDelNtHeader->Parameters->ParamByName("@Bsmode")->Value = 5;
		MYTRACEF(_T("del note header @ID=%d,@Bsmode=%d"), id, 5);
		cmdDelNtHeader->Execute();
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
}
void TfrmProcureMng::UpdateNtHeader(int mode)
{
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		cmdUpdateNtHeader->Parameters->ParamByName("@ID")->Value =
			dsetNtHeader->FieldByName("ID")->AsInteger;
		cmdUpdateNtHeader->Parameters->ParamByName("@HdTime")->Value =
			dbdtedtHdTime->DateTime ;
		cmdUpdateNtHeader->Parameters->ParamByName("@StgID")->Value =
			dsetNtHeader->FieldByName("StgID")->AsInteger;
		if (dsetNtHeader->FieldByName("StaffID")->AsString != "")
			cmdUpdateNtHeader->Parameters->ParamByName("@StaffID")->Value =
				dsetNtHeader->FieldByName("StaffID")->AsInteger;
		cmdUpdateNtHeader->Parameters->ParamByName("@AddCosts")->Value =
			abs(dsetNtHeader->FieldByName("AddCosts")->AsFloat);
		cmdUpdateNtHeader->Parameters->ParamByName("@Remarks")->Value =
        	membk->Text ;
			//dsetNtHeader->FieldByName("Remarks")->AsWideString;
		cmdUpdateNtHeader->Parameters->ParamByName("@CustomerID")->Value =
			dsetVendor->FieldByName("ID")->AsInteger;
		//cmdUpdateNtHeader->Parameters->ParamByName("@State")->Value =  cbstate->ItemIndex ;
		cmdUpdateNtHeader->Parameters->ParamByName("@Bsmode")->Value = mode;   //ֻ������õĴ洢����
		cmdUpdateNtHeader->Parameters->ParamByName("@yijidate")->Value =
			dbdtedtHdyujiTime->Date ;
			//ShowMessage(DateToStr(dsetNtHeader->FieldByName("yujidate")->AsDateTime));
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
void TfrmProcureMng::UpdateNtHeader()
{
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		cmdUpdateNtHeader->Parameters->ParamByName("@ID")->Value =
			dsetNtHeader->FieldByName("ID")->AsInteger;
		cmdUpdateNtHeader->Parameters->ParamByName("@HdTime")->Value =
			dbdtedtHdTime->DateTime ;
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
		//cmdUpdateNtHeader->Parameters->ParamByName("@State")->Value =  cbstate->ItemIndex ;
		cmdUpdateNtHeader->Parameters->ParamByName("@Bsmode")->Value = 5;
		cmdUpdateNtHeader->Parameters->ParamByName("@yijidate")->Value =
			dsetNtHeader->FieldByName("yujidate")->AsDateTime ;
			//ShowMessage(DateToStr(dsetNtHeader->FieldByName("yujidate")->AsDateTime));
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

int TfrmProcureMng::AddNote(int modle, int catalogID)
{
	int result = 0;
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		cmdAddNote->Parameters->ParamByName("@NtHeaderID")->Value
			= dsetNtHeader->FieldByName("ID")->AsInteger;
		cmdAddNote->Parameters->ParamByName("@BkcatalogID")->Value
			= catalogID;
		//cmdAddNote->Parameters->ParamByName("@SupplierID")->Value = supplierID;
		cmdAddNote->Parameters->ParamByName("@Bsmode")->Value = 5;
		cmdAddNote->Parameters->ParamByName("@NoteMode")->Value = -1;

		cmdAddNote->Execute();
		int ret = cmdAddNote->Parameters->ParamByName("@RETURN_VALUE")->Value;
		if (ret > 0)//����ɹ�
		{
			try
			{
				if (modle == 0) {   //һ�������Ҫ��ѯ��ȫѡ����²���Ҫ��ѯ
					QryNtHeader(dsetNtHeader->FieldByName("ID")->AsInteger, true);
				}
			}
			__finally
			{
			}
			result = 1;
		}
		else if (ret == 0)//���޴���
		{

		}
		else if (ret == -1)//��������
		{

		}
		else if (ret == -2) {
        	TLocateOptions   Opts;
			Opts.Clear();
			Opts   <<   loPartialKey;
			String   str   = AnsiString(catalogID);
			dsetNote->Locate("BkcatalogID",str,Opts);
			//ShowMsg(Handle ,"�����������ɹ���",3);
			result = 2;
				  //addnotereturnvalue = -2;
                        //�����
				  //result = true;
		}
	}
	return result;
}
int TfrmProcureMng::GetTotalNum(int ID)
{
  String sql;
  int totalnum;
  sql = " select isnull(sum(amount),0) as totalkuchen from dbo.STK_BookInfo where bkcatalogid in( ";
  sql = sql + " select bkcatalogid from BS_ProcureNote where id = "+IntToStr(ID)+") ";
  TADOQuery *aq;
  aq = new TADOQuery(NULL);
  aq->Connection= m_con;
  aq->SQL->Clear();
  aq->SQL->Add(sql);
  aq->Open();
  totalnum = aq->FieldByName("totalkuchen")->AsInteger;
  delete aq;
  return totalnum;

}
void TfrmProcureMng::UpdateNote()
{
	if (dsetNote->Active && dsetNote->RecordCount >= 1)
	{
		cmdUpdateNote->Parameters->ParamByName("@ID")->Value
			= dsetNote->FieldByName("ID")->AsInteger;
		if (m_bsmode == BSNote)
		{
			cmdUpdateNote->Parameters->ParamByName("@Amount")->Value
				= abs(dsetNote->FieldByName("Amount")->AsInteger);
		}
		else
		{
			cmdUpdateNote->Parameters->ParamByName("@Amount")->Value
				= - abs(dsetNote->FieldByName("Amount")->AsInteger);
		}
		cmdUpdateNote->Parameters->ParamByName("@Discount")->Value
			= fabs(dsetNote->FieldByName("Discount")->AsFloat);
		cmdUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 5;
		cmdUpdateNote->Execute();
                //��ѯ���ܿ��
                //edittotal->Text = StrToInt(GetTotalNum(dsetNote->FieldByName("ID")->AsInteger));

	}
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
void TfrmProcureMng::DelNote()
{
	if (dsetNote->Active && dsetNote->RecordCount >= 1)
	{
		if (dbgrdNote->SelectedRows->Count == 0)
		{
			cmdDelNote->Parameters->ParamByName("@ID")->Value
				= dsetNote->FieldByName("ID")->AsInteger;
			cmdDelNote->Parameters->ParamByName("@Bsmode")->Value = 5;
			logmessage = "ɾ��һ��ɹ���" + dsetNtHeader->FieldByName("ProcureNtCode")->AsString + "����Ŀ��" + dsetNote->FieldByName("CatalogName")->AsString + "��";
			AddEvent(1,"һ��ɹ�����",userid,stgid,logmessage,m_con);
			cmdDelNote->Execute();
		}
		else if (dbgrdNote->SelectedRows->Count > 0)
		{
			String ids = "";
			dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[0];
			ids = ids + dsetNote->FieldByName("ID")->AsString;
			logmessage = "ɾ��һ��ɹ���" + dsetNtHeader->FieldByName("ProcureNtCode")->AsString + "����Ŀ��" + dsetNote->FieldByName("CatalogName")->AsString + "��";
			AddEvent(1,"һ��ɹ�����",userid,stgid,logmessage,m_con);
			for (int i=1; i < dbgrdNote->SelectedRows->Count; i++)
			{
				dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[i];
				ids = ids + "," + dsetNote->FieldByName("ID")->AsString;
				logmessage = "ɾ��һ��ɹ���" + dsetNtHeader->FieldByName("ProcureNtCode")->AsString + "����Ŀ��" + dsetNote->FieldByName("CatalogName")->AsString + "��";
				AddEvent(1,"һ��ɹ�����",userid,stgid,logmessage,m_con);
			}
                         dsetNote->Next();
			cmdBatchDelNote->Parameters->ParamByName("@IDS")->Value = ids;
			cmdBatchDelNote->Parameters->ParamByName("@Bsmode")->Value = 5;
			cmdBatchDelNote->Execute();
		}
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
void __fastcall TfrmProcureMng::dblkpcbbVendorIDKeyPress(TObject *Sender, wchar_t &Key)
{
	//
	if (Key == '\r')
	{
		if (dblkpcbbVendorID->Text == "") {
			ShowMsg(Handle ,"��ѡ��Ӧ�̣�",3);
			return;
		}
		//BtnSave->Click();
		UpdateNtHeader(10);

		//spnewbook->Enabled = true;
		edtCatalog->SetFocus();
		if (!edtQryVendor->Enabled ) {
			dblkpcbbVendorID->Enabled = false;
		}
		edtCatalog->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::dbnbedtAmountExit(TObject *Sender)
{
	UpdateNote();
}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::tlbtn5Click(TObject *Sender)
{
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1 && dsetNote->Active && dsetNote->RecordCount > 0)
	{
		Tfrmwsaleprinta* frm = new Tfrmwsaleprinta(this,m_con);
		::ShowWindow(frm->Handle, SW_HIDE);
		LandInfo li;
		li.app = m_app;
		li.con = m_con;
		li.userID = userid;
		li.storageID = stgid;
		frm->PrintType = 2;//�ɹ�
		frm->InputPara(dsetNtHeader->FieldByName("ID")->AsString);

		frm->RvSystem1->SystemSetups >>ssAllowSetup;
		frm->RvSystem1->SystemSetups >>ssAllowDestPreview;
		frm->RvSystem1->SystemSetups >>ssAllowDestPrinter;
		frm->RvSystem1->SystemSetups >>ssAllowPrinterSetup;
		frm->RvSystem1->SystemSetups >>ssAllowDestFile;

		frm->RvSystem1->DefaultDest   = rdPrinter ;

		frm->RvSystem1->SystemSetups<<ssAllowDestPrinter;
		frm->pxbk = printbk;
		frm->printtitle = printtitle;
		frm->contact = contact;
		frm->tel = tel;
		frm->address = address;
		frm->shaddress = shaddress;
		frm->shtel = shtel;
		frm->shcontact = shcontact;
		frm->previewprint(0,4);
		frm->Close();
		delete frm;
		dsetNtHeader->Edit();
		dsetNtHeader->FieldByName("printcount")->AsInteger = dsetNtHeader->FieldByName("printcount")->AsInteger + 1;
		dsetNtHeader->Post();
		QryNtHeader();
	}
}
//---------------------------------------------------------------------------


void TfrmProcureMng::QryBkstack()
{
  /*	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1
		&& dsetNote->Active && dsetNote->RecordCount >= 1)
	{
   /*		String sql;
		sql = " SELECT STK_BookstackInfo.ID, STK_BookstackInfo.Name "
			" FROM STK_BookInfo LEFT OUTER JOIN"
			" STK_BookstackInfo ON STK_BookInfo.BkstackID = STK_BookstackInfo.ID"
			" where SupplierID=" + dsetNote->FieldByName("SupplierID")->AsString
			 + " and BkcatalogID=" + dsetNote->FieldByName("BkcatalogID")->AsString
			 + " and StgID=" + dsetNtHeader->FieldByName("StgID")->AsString;
	  //	dsetBkstack->Active = false;
	 //	dblkpcbbBkstackID->ListSource = NULL;
	 //	dblkpcbbBkstackID->DataSource = NULL;
	  //	dsetBkstack->CommandText = sql;
	  //	dsetBkstack->Active = true;
	 //	dblkpcbbBkstackID->ListSource = dsrcBkstack;
	//	dblkpcbbBkstackID->DataSource = dsrcNote;
		//ShowMessage("OK");
	}    */
}

void __fastcall TfrmProcureMng::dsetNoteAfterScroll(TDataSet *DataSet)
{
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
        QryBkstack();
}
//---------------------------------------------------------------------------

void TfrmProcureMng::ResetNtHeader()
{
	//���õ�ͷ
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1
		&& dsetNote->Active && dsetNote->RecordCount < 1
	)
	{
		cmdResetNtHeader->Parameters->ParamByName("@ID")->Value =
			dsetNtHeader->FieldByName("ID")->AsInteger;
		cmdResetNtHeader->Parameters->ParamByName("@Bsmode")->Value = 5;
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

void __fastcall TfrmProcureMng::N1Click(TObject *Sender)
{
	lblCatalog->Caption = "���";
	m_catalogSearchMode=1;
	edtCatalog->MaxLength = 20;
}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::N2Click(TObject *Sender)
{
	lblCatalog->Caption = "�Ա���";
	m_catalogSearchMode=2;
	edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::N3Click(TObject *Sender)
{
	lblCatalog->Caption = "����";
	m_catalogSearchMode=3;
	edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::lblCatalogMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	if (Button == mbLeft ) {
		TPoint  pt;
		GetCursorPos(&pt);
		pm->Popup(pt.x,pt.y);

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::N11Click(TObject *Sender)
{
  tlbtn5->Click();
}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::N21Click(TObject *Sender)
{
  /* if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
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



		if (Label2->Caption == "������")
		{
			frm->previewprint(1,2);
		}else
		{
		   frm->previewprint(2,2);
		}
		  //1,������ 2.�����˻��� //1��ӡ��ʽ1 2 ��ӡ��ʽ2
		frm->Close();
		delete frm;
	}*/
}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::BtnClearClick(TObject *Sender)
{
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1 && dsetNote->Active && dsetNote->RecordCount > 0)
	{
		Tfrmwsaleprinta* frm = new Tfrmwsaleprinta(this,m_con);
		::ShowWindow(frm->Handle, SW_HIDE);
		LandInfo li;
		li.app = m_app;
		li.con = m_con;
		li.userID = userid;
		li.storageID = stgid;
		frm->PrintType = 2;//�ɹ�
		frm->InputPara(dsetNtHeader->FieldByName("ID")->AsString);

		/*frm->RvSystem1->SystemSetups >>ssAllowSetup;
		frm->RvSystem1->SystemSetups >>ssAllowDestPreview;
		frm->RvSystem1->SystemSetups >>ssAllowDestPrinter;
		frm->RvSystem1->SystemSetups >>ssAllowPrinterSetup;
		frm->RvSystem1->SystemSetups >>ssAllowDestFile;

                try


		frm->RvSystem1->DefaultDest  = rdPreview ;
		frm->RvSystem1->SystemSetups<<ssAllowDestPrinter;   */
		dsetNote->Last();
		frm->num = dsetNote->FieldByName("xuhao")->AsAnsiString ;
        frm->pxbk = printbk;
		frm->printtitle = printtitle;
		frm->contact = contact;
		frm->tel = tel;
		frm->address = address;
		frm->shaddress = shaddress;
		frm->shtel = shtel;
		frm->shcontact = shcontact;

                try
                {
		frm->previewprint(1,4);
                  }
                  catch(...)
                  {}
		frm->Close();
		delete frm;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::N22Click(TObject *Sender)
{
  /*	 if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
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
		if (Label2->Caption == "������")
		{
			frm->previewprint(1,2);
		}else
		{
		   frm->previewprint(2,2);
		}
		  //1,������ 2.�����˻��� //1��ӡ��ʽ1 2 ��ӡ��ʽ2
		frm->Close();
		delete frm;
	} */
}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::N12Click(TObject *Sender)
{
  BtnClear->Click();
}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::dbnbedtDiscountKeyPress(TObject *Sender, wchar_t &Key)

{
	if ((Key < '0' || Key > '9') && (Key != '\b') && (Key != '.') && (Key != '\r') ) {
    	Key = NULL;
	}
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


void __fastcall TfrmProcureMng::N4Click(TObject *Sender)
{
	lblCatalog->Caption = "����";
	m_catalogSearchMode=6;
	edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::dbnbedtTotalAmountKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r')
	{
		Perform(WM_NEXTDLGCTL, 0, 0);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::cbstateChange(TObject *Sender)
{
	UpdateNtHeader();
}
//---------------------------------------------------------------------------

void  TfrmProcureMng::FindNote(String code)
{
	DelInvalidNtHeader();
	edtCatalog->Text = "";
	edtQryVendor->Text = "";
	VendorView();
	try
	{
		//LockWindowUpdate(dbgrdNote->Handle);//����ָ�����ڣ���ֹ�����¡�
		QryNtHeader(code);
		//cbstate->ItemIndex = dsetNtHeader->FieldByName("state")->AsInteger ;
	}
	__finally
	{
		//LockWindowUpdate(NULL);
	}
}


//---------------------------------------------------------------------------







void __fastcall TfrmProcureMng::N6Click(TObject *Sender)
{
	for (int i = 1; i <= dsetNote->RecordCount; i++) {
		dbgrdNote->DataSource->DataSet->RecNo = i;
		dbgrdNote->SelectedRows->CurrentRowSelected = true;
	}
}
//---------------------------------------------------------------------------



void __fastcall TfrmProcureMng::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F1) {    //�鵥
		if (!RzToolButton1->Enabled ) {
			return;
		}
		RzToolButton1->Click();
	}
	if (Key == VK_F2) {   //����
		if (!mtbbtnAddNtHeader->Enabled ) {
			return;
		}
		mtbbtnAddNtHeader->Click();
	}
	if (Key == VK_F3) {   //����
		if (!BtnSave->Enabled ) {
			return;
		}
		BtnSave->Click();
	}
	if (Key == VK_F4) {   //�޸�
		if (!BtnProperties->Enabled ) {
			return;
		}
		BtnProperties->Click();
	}
	if (Key == VK_F5) {  //ɾ��
		if (!tlbtn2->Enabled ) {
			return;
		}
		tlbtn2->Click();
	}
	if (Key == VK_F6) {   //ͳһ
		if (!tlbtn3->Enabled ) {
			return;
		}
		tlbtn3->Click();
	}
	if (Key == VK_F7) {   //�ֳ��տ�
		if (!RzToolButton2->Enabled ) {
			return;
		}
		RzToolButton2->Click();
	}
	if (Key == VK_F8) {   //����
		if (!tlbtn4->Enabled ) {
			return;
		}
		tlbtn4->Click();
	}
	if (Key == VK_F9) {   //ɾ��
		if (!tlbtn1->Enabled ) {
			return;
		}
		tlbtn1->Click();
	}
	if (Key == VK_F10) {  //��ӡ
		if (!tlbtn5->Enabled ) {
			return;
		}
		tlbtn5->Click();
	}
	if (Key == VK_F11) {  //Ԥ��
		if (!BtnClear->Enabled ) {
			return;
		}
		BtnClear->Click();
	}
	if (Shift.Contains(ssAlt)&& Key == 67) {    //��λ
		SpeedButton1->Click();
	}
	if (Shift.Contains(ssAlt)&& Key ==90) {
		WindowState = wsNormal  ;
	}
	if (Shift.Contains(ssAlt)&& Key ==81  ) {
	   tlbtn7->Click();
	}
	if (Shift.Contains(ssAlt)&& Key == 70 ) {   //����
	   BtnView->Click();
	}
	if (Shift.Contains(ssAlt)&& Key == 78 ) {
	   BtnAlignBottom->Click();
	}
}
//---------------------------------------------------------------------------
void TfrmProcureMng::VendorView()
{
		edtQryVendor->Text = "";
		AnsiString sql;
		sql = " select * from CUST_CustomerInfo where Type =1 and customerstate=1 and "+QFSupplierTiaoJian+" order by name";
		dsetVendor->Active = false;
		dsetVendor->CommandText = sql;
		dsetVendor->Active = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::dbnbedtAmountKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
    	if (chfoceset->Checked) {
			if (chfsdiscount->Checked) {
				dbnbedtDiscount->SetFocus();
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
			dbnbedtDiscount->SetFocus();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::RzButton1Click(TObject *Sender)
{
	String ID;
        int supplierid;
	ID = "";
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
        dsetVendor->Active = false;
                	dsetVendor->CommandText = "select ID,Name,salesman from CUST_CustomerInfo where Type in (1)  and customerstate =1 and "+QFSupplierTiaoJian+" order by ID";
               	dsetVendor->Active = true;
		int count1 = dsetVendor->RecordCount;

	   //	TDetaileForm * frm = new TDetaileForm(m_app,2,1,ID.c_str() ,m_con);
	   TDetaileForm * frm = new TDetaileForm(m_app,1,1,ID.c_str() ,m_con,stgid);
		frm->ShowModal();

		delete frm;

		dsetVendor->Active = false;
                	dsetVendor->CommandText = "select ID,Name,salesman from CUST_CustomerInfo where Type in (1)  and customerstate =1 and "+QFSupplierTiaoJian+" order by ID";
		dsetVendor->Active = true;
		int count2 = dsetVendor->RecordCount;
		if (count2 > count1)
		{
                        dsetVendor->Last() ;
                        supplierid= dsetVendor->FieldByName("ID")->AsInteger ;
			dblkpcbbVendorID->KeyValue = supplierid;
			dsetNtHeader->Edit();
			dsetNtHeader->FieldByName("VendorID")->AsInteger = supplierid;
			UpdateNtHeader();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::spnewbookClick(TObject *Sender)
{
	//����Ŀ
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
	   Tfrmnewbook1 *frm = new Tfrmnewbook1(m_app,m_con);
	   frm->ProcureMng = this;
	   frm->modle = 3;//�ɹ�
	   if (mbOK == frm->ShowModal())
	   {
			edtCatalog->Text  = "";
			dbnbedtAmount->Text = "0";
			dbnbedtDiscount->Text = "100";
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

void __fastcall TfrmProcureMng::BtnViewClick(TObject *Sender)
{
	Tfrmbookquery * frm = new Tfrmbookquery(Application,m_con,m_storageID);
	frm->ShowModal();
	delete frm;
}
//---------------------------------------------------------------------------

void TfrmProcureMng::historyview()
{
	AnsiString sql;
	sql = "select BS_ProcureNote.Amount,BS_ProcureNote.RecAmount,BS_ProcureNote.Discount,BS_ProcureNoteHeader.ProcureNtCode,"
		" BS_ProcureNoteHeader.HdTime,CUST_CustomerInfo.Name "
		" from BS_ProcureNote left join BS_ProcureNoteHeader on BS_ProcureNote.ProcureNtHeaderID = BS_ProcureNoteHeader.id "
		" left join CUST_CustomerInfo on BS_ProcureNoteHeader.SupplierID = CUST_CustomerInfo.id "
		" where BS_ProcureNoteHeader.stgid = " + IntToStr(stgid)  + " and BS_ProcureNote.BkcatalogID =  " + dsetNote->FieldByName("BkcatalogID")->AsString ;
	aq2->Close();
	aq2->SQL->Clear();
	aq2->SQL->Add(sql);
	aq2->Open();
}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::dbgrdNoteCellClick(TColumn *Column)
{
	if (dsetNote->IsEmpty() ) {
		return;
	}
	editdetailbk->Text = dsetNote->FieldByName("detailbk")->AsAnsiString ;
	editjingjia->Text = FormatFloat("0.00",dsetNote->FieldByName("price")->AsFloat * dsetNote->FieldByName("Discount")->AsFloat * 0.01);
	historyview();
}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::DBNavigator1Click(TObject *Sender, TNavigateBtn Button)

{
	QryNtHeader(aqheader->FieldByName("id")->AsInteger);
}
//---------------------------------------------------------------------------
void  TfrmProcureMng::operterview(int operterid)
{
	AnsiString sql;
	sql = "select name from sys_user where id = " + IntToStr(operterid);
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	lblOpName->Caption = query->FieldByName("name")->AsString;
}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::membkExit(TObject *Sender)
{
	
	//UpdateNtHeader();
}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::SpeedButton1Click(TObject *Sender)
{
	if (GroupBox3->Visible) {
		GroupBox3->Visible = false;
	}
	else
	{
    	GroupBox3->Visible = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::BtnPropertiesClick(TObject *Sender)
{

	GroupBox1->Enabled = true;
	dblkpcbbVendorID->Enabled = true;
	edtQryVendor->Enabled = true;
	dblkpcbbStaffID->Enabled = true;
	dbnbedtAddCosts->Enabled = true;
	//cbstate->Enabled = true;
	RzButton1->Enabled = true;
	dbdtedtHdTime->Enabled = true;
	dbdtedtHdyujiTime->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::BtnSaveClick(TObject *Sender)
{
	if (!edtQryVendor->Enabled) {
		return;
	}
	try
	{
		//dsetNtHeader->Edit();
		//dsetNtHeader->FieldByName("Remarks")->AsAnsiString = membk->Text ;
		UpdateNtHeader(10);
	}
	catch(...)
	{
		ShowMsg(this->Handle,"����ʧ�ܣ�������!",3);
		return;
	}
	dblkpcbbVendorID->Enabled = false;
  //	edtCatalog->SetFocus();
	//cbstate->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::chfsluruClick(TObject *Sender)
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

void __fastcall TfrmProcureMng::N7Click(TObject *Sender)
{
	lblCatalog->Caption = "����";
	m_catalogSearchMode=5;
	edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------


void __fastcall TfrmProcureMng::BtnWeekViewClick(TObject *Sender)
{
		/*Tfrmorderquery *frm = new Tfrmorderquery(Application,m_con,0,100,0);     //���ö����еĲ鵥ģ��
		if (frm->ShowModal()==mrOk ) {
		  //	dbn->Enabled = true;
		  LandInfo li;
		  li.app = Application;
		  li.con =m_con;
		  li.userID = userid ;
		  li.storageID = stgid ;
		   AnsiString code = frm->GetNoteCode();
			delete frm;
		   TfrmBIorder * frmorder = new TfrmBIorder(NULL);
		   frmorder->init(&li);
		   frmorder->RefreshHead(code);
		   frmorder->cbtype->Enabled = false;
		   frmorder->Show();
	if (dsetNtHeader->FieldByName("id")->AsAnsiString == "" ) {
		return;
	}  */
      //	if (dbedtWsaleNtCode->Text == "") {
	   //	return;
      //	}
	Tfrminorder *frm = new Tfrminorder(Application,m_con,m_storageID,m_userID,dsetNtHeader->FieldByName("id")->AsInteger );
	frm->pro = this;
	frm->supplierid = dsetNtHeader->FieldByName("VendorID")->AsInteger;
	frm->ShowModal();
	delete frm;
}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::dbgrdNoteDblClick(TObject *Sender)
{
	if (dsetNote->IsEmpty() ) {
		return;
	}
	TfrmNewBookModify * frm = new TfrmNewBookModify(Application,m_con,dsetNote->FieldByName("BkcatalogID")->AsInteger,m_storageID,m_userID);
	frm->ShowModal();
	delete frm;
	QryNtHeader();
}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::N8Click(TObject *Sender)
{
	if (dsetNote->IsEmpty() ) {
		return;
	}
	Tfrmbookhistory *frm = new Tfrmbookhistory(Application,m_con,m_storageID,dsetNote->FieldByName("BkcatalogID")->AsInteger );
frm->Show();
}
//---------------------------------------------------------------------------


void __fastcall TfrmProcureMng::BtnFinishClick(TObject *Sender)
{
	//if (dbedtWsaleNtCode->Text == "") {
       //		return;
       //	}
	Tfrmretailbookup *frm = new Tfrmretailbookup(Application,m_con,m_storageID);
	frm->pro  = this;
	frm->modle = 3;
        frm->fuserid = userid;
        frm->iscaigou=true;
	frm->ShowModal();
	delete frm;
}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::editdetailbkKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == VK_RETURN) {
		if (dsetNote->IsEmpty() ) {
			return;
		}
		dsetNote->Edit() ;
		dsetNote->FieldByName("detailbk")->AsAnsiString  = editdetailbk->Text ;
		dsetNote->UpdateBatch(arCurrent);
		if (edtCatalog->Enabled ) {
			edtCatalog->SetFocus();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::dbnbedtDiscountExit(TObject *Sender)
{
	if (dsetNote->IsEmpty() ) {
    	return;
	}
	UpdateNote();

	//������� dsetNote->FieldByName("ID")->AsInteger
	editjingjia->Text = FormatFloat("0.00",dsetNote->FieldByName("price")->AsFloat * dbnbedtDiscount->Value* 0.01);
}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::editjingjiaExit(TObject *Sender)
{
	if (dsetNote->IsEmpty() ) {
    	return;
	}
	Double jinjia,discount;
	try {
		jinjia = StrToFloat(editjingjia->Text);
	} catch (...) {
		return;
	}
    if (dsetNote->FieldByName("price")->AsFloat == 0) {
		discount = 100;
	}
	else
	{
		discount = jinjia *100 / dsetNote->FieldByName("price")->AsFloat;
	}

	dsetNote->Edit();
	dsetNote->FieldByName("Discount")->AsFloat = discount;
	dsetNote->Post();
	UpdateNote();
}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::editjingjiaKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        edtCatalog->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::CheckBox1Click(TObject *Sender)
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

void __fastcall TfrmProcureMng::FormShow(TObject *Sender)
{
	SetWindowPos(Handle,HWND_TOPMOST,0,0,0,0,SWP_NOACTIVATE|SWP_NOMOVE|SWP_NOSIZE);
}
//---------------------------------------------------------------------------
void __fastcall TfrmProcureMng::CreateParams(TCreateParams & Param)
{
	//���û���
    TForm::CreateParams(Param);
    //ȥ�����ڱ�����   ��Ȼ��Ҳ���Բ�ȥ��   ������ο�����
	//Param.Style=Param.Style & WS_CAPTION;
	//Param.Style=Param.Style | WS_POPUP;
	//��Ϊ����������
	Param.ExStyle=Param.ExStyle   |   WS_EX_TOPMOST;
    //   ��Windows   OwnerΪDesktop   Window   ������   �������Ͳ������������������   �൱�ڰ������̸�������
	Param.WndParent=GetDesktopWindow();
}
//---------------------------------------------------------------------------



void __fastcall TfrmProcureMng::membkKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        dsetNtHeader->Edit();
		dsetNtHeader->FieldByName("Remarks")->AsAnsiString = membk->Text ;
		dsetNtHeader->UpdateBatch(arAll);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmProcureMng::toolshowmainmenuClick(TObject *Sender)
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
