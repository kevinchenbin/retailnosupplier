//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "OrderMngForm.h"
#include "NoteCode.h"
#include "QryNoteCodeForm.h"
#include "SetNotesForm.h"
#include "mytrace.h"
#include "SelectCustomerForm.h"
#include "RecMoneyForm.h"
#include "SelectCatalogForm.h"
#include "..\supplier\detailemessage.h"

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
#pragma resource "*.dfm"
TfrmOrderMng *frmOrderMng;
//---------------------------------------------------------------------------
__fastcall TfrmOrderMng::TfrmOrderMng(TComponent* Owner)
	: TfrmMDIChild(Owner)
	, m_catalogSearchMode(0)
	, m_bsmode(BSUnknown)
	, m_opmode(OPUnknown)
	, m_supplierID(-1)
{
	m_module = MTOrder;
	this->WindowState = wsMaximized ;
}
//---------------------------------------------------------------------------
void TfrmOrderMng::Init(LandInfo* li)
{
	TfrmMDIChild::Init(li);
	m_storageID = li->storageID ;
	if (li->storageID != 0) {       //总店

	   dblkpcbbVendorID->Enabled = false;
	   RzButton1->Enabled = false;
	   dblkpcbbStaffID->Enabled = false;
	   cborder->Enabled = false;
	}else
	{
	  cborder->ItemIndex = 1;
	}
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
	dsetBkstack->Active = true;
	dsetVendor->Active = true;
	dsetStaff->Active = true;
	bearsaledataset->Connection = m_con;
	bearsaledataset->Active = true;
	dsetStaff->Connection = m_con;
	ChangeCatalogSearchMode();
	chckbxSwitch->Checked = false;
	ChangeBsmode(BSNote);
	ChangeOpmode(OPAddNtHeader);
	addnotereturnvalue = 0;
	Sbutfirst->Enabled = false;
	Sbutbefore->Enabled = false;
	Sbutnext->Enabled = false;
	Sbutend->Enabled = false;
}

void __fastcall TfrmOrderMng::FormClose(TObject *Sender, TCloseAction &Action)
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

void __fastcall TfrmOrderMng::tlbtn1Click(TObject *Sender)
{
	//删除
	TControl* con = dynamic_cast<TControl*>(Sender);
	if (con)
	{
		ChangeOpmode(con->Tag);
	}

}
//---------------------------------------------------------------------------


void __fastcall TfrmOrderMng::tlbtn7Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmOrderMng::edtQryVendorKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r')
	{
		if (!dsetNtHeader->Active
			|| !dsetNote->Active
			|| (dsetNtHeader->Active && dsetNtHeader->RecordCount < 1))
        	return;

		dsetLkpVendor->Active = false;
		String sql;
		sql = Format("select * from CUST_CustomerInfo where (ID=0 or (ID>0 and Type=2)) and Name='%s'",
			ARRAYOFCONST((edtQryVendor->Text.c_str())));
        dsetLkpVendor->CommandText = sql;
		dsetLkpVendor->Active = true;
		if (dsetLkpVendor->RecordCount > 1 && dblkpdlgVendor->Execute())//找到
		{
			dsetNtHeader->Edit();
			dsetNtHeader->FieldByName("VendorID")->AsInteger
				= dsetLkpVendor->FieldByName("ID")->AsInteger;
			UpdateNtHeader();
			Key = 0;
			Perform(WM_NEXTDLGCTL, 0, 0);
		}
		else if (dsetLkpVendor->RecordCount == 1)//
		{
			dsetNtHeader->Edit();
			dsetNtHeader->FieldByName("VendorID")->AsInteger
				= dsetLkpVendor->FieldByName("ID")->AsInteger;
			UpdateNtHeader();
			Key = 0;
			Perform(WM_NEXTDLGCTL, 0, 0);
		}
		else//未能找到批销商
		{

        }
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmOrderMng::edtCatalogKeyPress(TObject *Sender, wchar_t &Key)
{
	//
    if (m_catalogSearchMode == 6) {
		if ((Key < '0' || Key > '9') && (Key != '\b') && (Key != '.') && (Key != '\r') ) {
            Key = NULL;
		}
	}
	if (Key == '\r')
	{
		if (!dsetNote->Active || !dsetNtHeader->Active
			|| (dsetNtHeader->Active && dsetNtHeader->RecordCount < 1))
			return;

		if (edtCatalog->Text == "")
		{
			ChangeCatalogSearchMode();
		}
		else
		{
			switch (m_catalogSearchMode)
			{
			case 1:
			 //	if (edtCatalog->Text.Length() != 13)
			  //	{
			   //		ShowMessage("条码输入错误！");
			  //		return;
			 //	}
			case 6:
			case 2:
			case 3:
            	{
					TfrmSelectCatalog* frm = new TfrmSelectCatalog(Application,m_con);
					LandInfo li;
					li.app = m_app;
					li.con = m_con;
					li.userID = m_userID;
					li.storageID = m_storageID;
					frm->Init(&li);
					frm->DoModalType = 4;
					frm->orderfrm = this;
					frm->SetSearchMode(m_catalogSearchMode, edtCatalog->Text);
					if (mrOk == frm->ShowModal())
					{
						int supplierID = -1,catalogID = -1;
						if (frm->SelectAll) {
                        	supplierID = dsetVendor->FieldByName("ID")->AsInteger ;
							 for (int i = 0; i < frm->lengthint  ; i++) {
								 if (AddNote(supplierID,frm->BkcatalogiD[i])) {
									 Key = 0;
									 Perform(WM_NEXTDLGCTL, 0, 0);
								 }  else
								 {
								 }
							 }

						}else
						{
							frm->GetSelectResult(supplierID, catalogID);
							supplierID = dsetVendor->FieldByName("ID")->AsInteger ;
							if (supplierID >= 0 && catalogID >= 0)
							{
								if (AddNote(supplierID, catalogID))
								{
									if (addnotereturnvalue == -2) {
									   //	 MessageBox(0,"不充许负库存销售！","批销" ,MB_ICONEXCLAMATION);
                                         addnotereturnvalue = 0;
										} else
										{
											Key=0;
											Perform(WM_NEXTDLGCTL, 0, 0);
										 }
								}
								else

									ShowMessage("库存无该书!");
							}
						}
					}
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

void TfrmOrderMng::ChangeCatalogSearchMode()
{
	if (!chckbxSwitch->Checked)
	{
        return;
	}

	m_catalogSearchMode++;
	if (m_catalogSearchMode >= 4)
	{
		m_catalogSearchMode = 1;
	}

	switch (m_catalogSearchMode)
	{
	case 1:
        edtCatalog->MaxLength = 13;
		lblCatalog->Caption = "书        号";
		break;
	case 2:
		edtCatalog->MaxLength = 0;
    	lblCatalog->Caption = "自  编  码";
		break;
	case 3:
        edtCatalog->MaxLength = 0;
    	lblCatalog->Caption = "书        名";
    	break;
    default:
        break;
	}
}

void TfrmOrderMng::ChangeBsmode(BSMode bsmode)
{
	if (bsmode != m_bsmode)
	{
        m_bsmode = bsmode;
    }

	if (m_bsmode == BSNote)
	{
		grpbxNtHeader->Caption = "订单信息";
		grpbxNote->Caption = "图书订单信息";
		Label2->Caption = "订单";
		mniBsNote->Checked = true;
		mniBsNoteSendback->Checked = false;
	}
	else if (m_bsmode == BSNoteSendback)
	{
		grpbxNtHeader->Caption = "订单撤消单信息";
		grpbxNote->Caption = "图书订单撤消单信息";
		Label2->Caption = "订单撤消单";
		mniBsNote->Checked = false;
		mniBsNoteSendback->Checked = true;
	}
}

void TfrmOrderMng::ChangeOpmode(OPMode opmode)
{
	if (opmode == m_opmode
		&& (opmode == OPDelNtHeader))
		return;

	//1为查单模式 2为添加单头模式 3为删除单头模式 4为添加单模式 5为删除单模式 6为统一模式 7为现场收款模式
	switch (opmode)
	{
	case OPFind:
		{
			if (!CheckOperateAuthority())
				return;

			TfrmQryNoteCode* frm = new TfrmQryNoteCode(this,0);
			LandInfo li;
			li.app = m_app;
			li.con = m_con;
			li.userID = m_userID;
			li.storageID = m_storageID;
			frm->Init(&li);
			if (frm->ShowModal() == mrOk)
			{
            	DelInvalidNtHeader();
				edtCatalog->Text = "";
				edtQryVendor->Text = "";
				String code = frm->GetNoteCode();
				try
				{
					LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
					QryNtHeader(code);
					cbstate->ItemIndex = dsetNtHeader->FieldByName("state")->AsInteger ;
					String sql,codetmp;
					codetmp = code;
					if (codetmp != "") {
						codetmp = codetmp.SubString(0,10);
						int codenext = StrToInt(codetmp) + 1;
						sql = "select OrderNtCode from BS_OrderNoteHeader where OrderNtCode >= " +  codetmp + "00000 and OrderNtCode < " + IntToStr(codenext) + "00000";
						query->Close();
						query->SQL->Clear();
						query->SQL->Add(sql);
						query->Open();
						query->Last();
						codetmp = query->FieldByName("OrderNtCode")->AsString ;
					}
					MaxNote = codetmp;
				}
				__finally
				{
					LockWindowUpdate(NULL);
				}
			}
			m_opmode = opmode;
			delete frm;
        }
		break;
	case OPAddNtHeader:
		{
			//如果上次是添加模式，并且没有加进任何数据，则不能添加
			if (m_opmode == OPAddNtHeader &&
				dsetNote->Active && dsetNote->RecordCount < 1)
				return;

			if (m_opmode == OPDelNote
				&& dsetNote->Active && dsetNote->RecordCount < 1)
				return;

			edtCatalog->Text = "";
			edtQryVendor->Text = "";
			AddNtHeader();
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
		if (!CheckOperateAuthority())
			return;

		DelNote();
		ResetNtHeader();
		m_opmode = opmode;
		break;
	case OPSetNotes:
    	if (dsetNote->Active && dsetNote->RecordCount >= 1)
		{
			//统一模式
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
		//现场收款模式
	 /*	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
		{
			//首先把修改的更新一下哈
			dbgrdNote->SetFocus();
			//其次把最新数据刷新一下哈
			QryNtHeader();
			//
			TfrmRecMoney* frm = new TfrmRecMoney(this);
			frm->SetDiscountedPrice(dsetNtHeader->FieldByName("DiscountedPrice")->AsFloat);
			frm->SetChecked(dsetNtHeader->FieldByName("Checked")->AsFloat);
			if (mrOk == frm->ShowModal())
			{
				dsetNtHeader->Edit();
				dsetNtHeader->FieldByName("Checked")->AsFloat =
					dsetNtHeader->FieldByName("Checked")->AsFloat + frm->GetReceived();
				UpdateNtHeader();
			}
			delete frm;
		}
    	m_opmode = opmode;
		break;*/
    default:
        break;
	}
	try {
		NtCodeChange();
	} catch (...) {
	}
}

void TfrmOrderMng::BatchSetNotes(int amount, float discount, int mode)
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
		case 1://两者均更新
			cmdBatchUpdateNote->Parameters->ParamByName("@IDS")->Value = ids;
			cmdBatchUpdateNote->Parameters->ParamByName("@Amount")->Value = amount;
			cmdBatchUpdateNote->Parameters->ParamByName("@Discount")->Value = discount;
			cmdBatchUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 4;
			cmdBatchUpdateNote->Execute();
			try
			{
				LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
				QryNtHeader();
			}
			__finally
			{
				LockWindowUpdate(NULL);
			}
			break;
		case 2://只更新Amount
			cmdBatchUpdateNote->Parameters->ParamByName("@IDS")->Value = ids;
			cmdBatchUpdateNote->Parameters->ParamByName("@Amount")->Value = amount;
			cmdBatchUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 4;
			cmdBatchUpdateNote->Execute();
			try
			{
				LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
				QryNtHeader();
			}
			__finally
			{
				LockWindowUpdate(NULL);
			}
			break;
		case 3://只更新Discount
			cmdBatchUpdateNote->Parameters->ParamByName("@IDS")->Value = ids;
			cmdBatchUpdateNote->Parameters->ParamByName("@Discount")->Value = discount;
			cmdBatchUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 4;
			cmdBatchUpdateNote->Execute();
			try
			{
				LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
				QryNtHeader();
			}
			__finally
			{
				LockWindowUpdate(NULL);
			}
			break;
		default:
			break;
		}
	}
}

void __fastcall TfrmOrderMng::mniBsNoteSendbackClick(TObject *Sender)
{
	//添加单据类型
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
void __fastcall TfrmOrderMng::tlbtn4Click(TObject *Sender)
{
	//Excel导出
	//Excel导出
	if (dsetNote->Active && dsetNote->RecordCount >= 1)
	{
        DbgridToExcel(dbgrdNote);
	}
}//Excel导出函数
bool __fastcall TfrmOrderMng::DbgridToExcel(TRzDBGrid* dbg)
{
	AnsiString temptext  ;
	int k = dbg->DataSource ->DataSet ->RecordCount ,n=0;
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
	temptext = "'"+ Label2->Caption;
	v.OlePropertyGet("Cells",1,5).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",3,1).OlePropertySet("Value","单位" );
	temptext = "'"+ dblkpcbbVendorID->Text;
	v.OlePropertyGet("Cells",3,2).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",3,4).OlePropertySet("Value","单号" );
	temptext = "'"+ dbedtWsaleNtCode->Text;
	v.OlePropertyGet("Cells",3,5).OlePropertySet("Value",temptext .c_str());
	v.OlePropertyGet("Cells",3,7).OlePropertySet("Value","日期");
	temptext = "'"+ DateToStr(dbdtedtHdTime->Date);
	v.OlePropertyGet("Cells",3,8).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",4,1).OlePropertySet("Value","业务员" );
	temptext = "'"+ dblkpcbbStaffID->Text;
	v.OlePropertyGet("Cells",4,2).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",4,4).OlePropertySet("Value","附加费用" );
	temptext = "'"+ dbnbedtAddCosts->Text;
	v.OlePropertyGet("Cells",4,5).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",5,1).OlePropertySet("Value","备注" );
	temptext = "'"+ dbedtRemarks->Text;
	v.OlePropertyGet("Cells",5,2).OlePropertySet("Value",temptext .c_str() );

	n=6;

	int t1= 0;
	for(int q=0;q<dbg->FieldCount ;++q)
	{
		if (dbg->Columns->Items[q]->Visible == true) {
			t1++;
			temptext = "'"+ dbg->Columns ->Items [q]->Title ->Caption;
			v.OlePropertyGet("Cells",1+n,(t1)).OlePropertySet("Value",temptext .c_str() );
		}
	}



	int t2 = dbg->DataSource ->DataSet ->RecordCount ;

	dbg->DataSource ->DataSet ->First();
	for(int   i=2+n;i<=t2+1+n ;i++)
	{
		t1=0;
		for(int j=1;j<dbg->Columns ->Count  ;j++)
		{
			if (dbg->Columns->Items[j-1]->Visible == true) {
				t1++;
				temptext = "'"+ dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
				v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
			}
		}
		dbg->DataSource ->DataSet ->Next() ;
	}
	return false;
}
//---------------------------------------------------------------------------}
//---------------------------------------------------------------------------
void TfrmOrderMng::QryNtHeader(String code, bool qrybkstack)
{
	spQryNtHeader->Active = false;
	spQryNtHeader1->Active = false;
	spQryNtHeader1->Parameters->ParamByName("@NtCode")->Value = code;
	spQryNtHeader1->Parameters->ParamByName("@Bsmode")->Value = 4;
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
		cborder->ItemIndex = dsetNote->FieldByName("type")->AsInteger ;
	if (dsetNote->FieldByName("amount")->AsInteger < 0 ) {
			   Label2->Caption = "订单撤消单";
			   m_bsmode = BSNoteSendback;
		}
		dsetNote->AfterScroll = dsetNoteAfterScroll;
		if (qrybkstack)
		{
            QryBkstack();
		}
	}
	catch(...)
	{
		//ShowMessage("该单不存在！");
	}
}

void TfrmOrderMng::QryNtHeader(bool qrybkstack)
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
		spQryNtHeader->Parameters->ParamByName("@Bsmode")->Value = 4;
		try
		{
			spQryNtHeader->Active = true;
			dsrcNtHeader->DataSet = NULL;
			dsetNtHeader->Recordset = spQryNtHeader->Recordset;
			cborder->ItemIndex = dsetNtHeader->FieldByName("type")->AsInteger ;
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
			if (qrybkstack)
			{
				QryBkstack();
			}
		}
		catch(...)
		{
			//ShowMessage("该单不存在！");
		}
	}
}

void TfrmOrderMng::QryNtHeader(int id, bool qrybkstack)
{
	//查询单头
	spQryNtHeader1->Active = false;
	spQryNtHeader->Active = false;
	spQryNtHeader->Parameters->ParamByName("@ID")->Value = id;
	spQryNtHeader->Parameters->ParamByName("@Bsmode")->Value = 4;
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
		if (qrybkstack)
		{
			QryBkstack();
		}
	}
	catch(...)
	{
    	//ShowMessage("该单不存在！");
    }
}

void TfrmOrderMng::AddNtHeader()
{
	spQryNtHeader->Active = false;
	spQryNtHeader1->Active = false;
	cmdAddNtHeader->Parameters->ParamByName("@StgID")->Value = m_storageID;
	cmdAddNtHeader->Parameters->ParamByName("@OperatorID")->Value = m_userID;
	cmdAddNtHeader->Parameters->ParamByName("@Bsmode")->Value = 4;     //订 单
	cmdAddNtHeader->Parameters->ParamByName("@type")->Value = cborder->ItemIndex ;
	MYTRACEF(_T("add note header @StgID=%d,@OperatorID=%d,@Bsmode=%d,@type=%d"),m_storageID,m_userID,4,cborder->ItemIndex);
	cmdAddNtHeader->Execute();
	int id = cmdAddNtHeader->Parameters->ParamByName("@RETURN_VALUE")->Value;
	try
	{
		LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
		QryNtHeader(id);
	}
	__finally
	{
		LockWindowUpdate(NULL);
	}
}

void TfrmOrderMng::DelInvalidNtHeader()
{
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1
		&& dsetNote->Active && dsetNote->RecordCount < 1
		&& dsetNtHeader->FieldByName("State")->AsInteger == 0)
	{
        DelNtHeader();
    }
}

void TfrmOrderMng::DelNtHeader()
{
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		cmdDelNtHeader->Parameters->ParamByName("@ID")->Value
			= dsetNtHeader->FieldByName("ID")->AsInteger;
		int id = dsetNtHeader->FieldByName("ID")->AsInteger;
		cmdDelNtHeader->Parameters->ParamByName("@Bsmode")->Value = 4;
		MYTRACEF(_T("del note header @ID=%d,@Bsmode=%d"), id, 4);
		cmdDelNtHeader->Execute();
		try
		{
			LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
			QryNtHeader(id);
		}
		__finally
		{
			LockWindowUpdate(NULL);
		}
	}
}

void TfrmOrderMng::UpdateNtHeader()
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


			cmdUpdateNtHeader->Parameters->ParamByName("@State")->Value =  cbstate->ItemIndex ;



		cmdUpdateNtHeader->Parameters->ParamByName("@Bsmode")->Value = 4;
		cmdUpdateNtHeader->Execute();

		try
		{
			LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
			QryNtHeader();
		}
		__finally
		{
			LockWindowUpdate(NULL);
		}
	}
}

bool TfrmOrderMng::AddNote(int supplierID, int catalogID)
{
	bool result = false;
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		cmdAddNote->Parameters->ParamByName("@NtHeaderID")->Value
			= dsetNtHeader->FieldByName("ID")->AsInteger;
		cmdAddNote->Parameters->ParamByName("@BkcatalogID")->Value
			= catalogID;
		cmdAddNote->Parameters->ParamByName("@SupplierID")->Value = supplierID;
			cmdAddNote->Parameters->ParamByName("@Bsmode")->Value = 4;
				cmdAddNote->Parameters->ParamByName("@NoteMode")->Value = -1;

		cmdAddNote->Execute();
		int ret = cmdAddNote->Parameters->ParamByName("@RETURN_VALUE")->Value;
		if (ret > 0)//插入成功
		{
			try
			{
				LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。

				QryNtHeader(dsetNtHeader->FieldByName("ID")->AsInteger, true);
			}
			__finally
			{
				LockWindowUpdate(NULL);
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
				  addnotereturnvalue = -2;
                        //负库存
				  result = true;

			 }

	}
	return result;
}
void TfrmOrderMng::UpdateNote()
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
			= abs(dsetNote->FieldByName("Discount")->AsFloat);
		cmdUpdateNote->Parameters->ParamByName("@Bsmode")->Value = 4;
		cmdUpdateNote->Execute();
	}
	try
	{
		LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
		QryNtHeader();
	}
	__finally
	{
		LockWindowUpdate(NULL);
	}
}
void TfrmOrderMng::DelNote()
{
	if (dsetNote->Active && dsetNote->RecordCount >= 1)
	{
		if (dbgrdNote->SelectedRows->Count == 0)
		{
			cmdDelNote->Parameters->ParamByName("@ID")->Value
				= dsetNote->FieldByName("ID")->AsInteger;
			cmdDelNote->Parameters->ParamByName("@Bsmode")->Value = 4;
			cmdDelNote->Execute();
		}
		else if (dbgrdNote->SelectedRows->Count > 0)
		{
			String ids = "";
			dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[0];
			ids = ids + dsetNote->FieldByName("ID")->AsString;
			for (int i=1; i < dbgrdNote->SelectedRows->Count; i++)
			{
				dsetNote->Bookmark = dbgrdNote->SelectedRows->Items[i];
				ids = ids + "," + dsetNote->FieldByName("ID")->AsString;
			}
			cmdBatchDelNote->Parameters->ParamByName("@IDS")->Value = ids;
			cmdBatchDelNote->Parameters->ParamByName("@Bsmode")->Value = 4;
			cmdBatchDelNote->Execute();
		}
		try
		{
			LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
			QryNtHeader();
		}
		__finally
		{
			LockWindowUpdate(NULL);
		}
	}
}

void __fastcall TfrmOrderMng::dblkpcbbBkstackIDKeyPress(TObject *Sender, wchar_t &Key)
{
	//
	if (Key == '\r')
	{
		tlbtn1Click(tlbtnAddNote);
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmOrderMng::dblkpcbbVendorIDKeyPress(TObject *Sender, wchar_t &Key)
{
	//
	if (Key == '\r')
	{
		Key = 0;
		if (dbnbedtAmount->Text == "") {
		dbnbedtAmount->Text ="0";

		}
	/*  if (Label2->Caption="批销退货单") {
		  bearsaledataset->First();
		  bearsaledataset->Next();
		  if (bearsaledataset->FieldByName("value")->AsBoolean  ) {  //退货数据控制
			  String sql;
			  sql = "select * from ";
			  TADOQuery *aq = new TADOQuery(this);
			  aq->Connection = m_con ;
			  aq->Close();
			  aq->SQL->Clear();
			  aq->SQL->Add(sql);
				退货是以前的总数量吗？

		  }

	   }  */

		if ((StrToInt(ReplaceStr(dbnbedtAmount->Text,",",""))-StrToInt(ReplaceStr(dbnbedtTotalAmount->Text,",","")))>0) {
			bearsaledataset->First();
		   if (!bearsaledataset->FieldByName("value")->AsBoolean) {     //false 不能销售空库存
			 MessageBoxA(0,"销售数据大于当前库存数量！","警告",MB_ICONEXCLAMATION);
			 dbnbedtAmount->Text =  dbnbedtTotalAmount->Text ;
		   }else
		   {

		   Perform(WM_NEXTDLGCTL, 0, 0);
		   }
		}else
		{
		  Perform(WM_NEXTDLGCTL, 0, 0);
		}


	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmOrderMng::dbedtRemarksKeyPress(TObject *Sender, wchar_t &Key)
{
	//
	if (Key == '\r')
	{
		tlbtn1Click(tlbtnAddNote);
	}
}
//---------------------------------------------------------------------------



void __fastcall TfrmOrderMng::dblkpcbbStaffIDExit(TObject *Sender)
{
	UpdateNtHeader();
}
//---------------------------------------------------------------------------


void __fastcall TfrmOrderMng::dbnbedtAmountExit(TObject *Sender)
{
	UpdateNote();
}
//---------------------------------------------------------------------------


void __fastcall TfrmOrderMng::tlbtn5Click(TObject *Sender)
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
		frm->PrintType = 1;//订单
		frm->InputPara(dsetNtHeader->FieldByName("ID")->AsString);

		frm->RvSystem1->SystemSetups >>ssAllowSetup;
		frm->RvSystem1->SystemSetups >>ssAllowDestPreview;
		frm->RvSystem1->SystemSetups >>ssAllowDestPrinter;
		frm->RvSystem1->SystemSetups >>ssAllowPrinterSetup;
		frm->RvSystem1->SystemSetups >>ssAllowDestFile;

		frm->RvSystem1->DefaultDest   = rdPrinter ;

		 frm->RvSystem1->SystemSetups<<ssAllowDestPrinter;
        	frm->previewprint(1,3);
		frm->Close();
		delete frm;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmOrderMng::RzButton1Click(TObject *Sender)
{
	String ID;
	ID = "";
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
	{
		int count1 = dsetVendor->RecordCount;

		TDetaileForm * frm = new TDetaileForm(m_app,2,1,ID.c_str() ,m_con);
		frm->ShowModal();
		delete frm;

		dsetVendor->Active = false;
		dsetVendor->Active = true;
		int count2 = dsetVendor->RecordCount;
		if (count2 > count1)
		{
			dsetVendor->Last();
			dsetNtHeader->Edit();
			dsetNtHeader->FieldByName("VendorID")->AsInteger = dsetVendor->FieldByName("ID")->AsInteger;
			UpdateNtHeader();
		}
	}
}
//---------------------------------------------------------------------------

void TfrmOrderMng::QryBkstack()
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

void __fastcall TfrmOrderMng::dsetNoteAfterScroll(TDataSet *DataSet)
{
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1)
        QryBkstack();
}
//---------------------------------------------------------------------------

void TfrmOrderMng::ResetNtHeader()
{
	//重置单头
	if (dsetNtHeader->Active && dsetNtHeader->RecordCount >= 1
		&& dsetNote->Active && dsetNote->RecordCount < 1
	)
	{
		cmdResetNtHeader->Parameters->ParamByName("@ID")->Value =
			dsetNtHeader->FieldByName("ID")->AsInteger;
		cmdResetNtHeader->Parameters->ParamByName("@Bsmode")->Value = 4;
		cmdResetNtHeader->Execute();
		try
		{
			LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
			QryNtHeader();
		}
		__finally
		{
			LockWindowUpdate(NULL);
		}
	}
}


void __fastcall TfrmOrderMng::N1Click(TObject *Sender)
{
		lblCatalog->Caption = "书        号";
		m_catalogSearchMode=1;
}
//---------------------------------------------------------------------------

void __fastcall TfrmOrderMng::N2Click(TObject *Sender)
{
lblCatalog->Caption = "自  编  码";
m_catalogSearchMode=2;
}
//---------------------------------------------------------------------------

void __fastcall TfrmOrderMng::N3Click(TObject *Sender)
{
lblCatalog->Caption = "书        名";
m_catalogSearchMode=3;
}
//---------------------------------------------------------------------------

void __fastcall TfrmOrderMng::lblCatalogMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	if (Button == mbLeft ) {
		TPoint  pt;
		GetCursorPos(&pt);
		pm->Popup(pt.x,pt.y);

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmOrderMng::N11Click(TObject *Sender)
{
  tlbtn5->Click();
}
//---------------------------------------------------------------------------

void __fastcall TfrmOrderMng::N21Click(TObject *Sender)
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



		if (Label2->Caption == "批销单")
		{
			frm->previewprint(1,2);
		}else
		{
		   frm->previewprint(2,2);
		}
		  //1,批销单 2.批销退货单 //1打印格式1 2 打印格式2
		frm->Close();
		delete frm;
	}*/
}
//---------------------------------------------------------------------------


void __fastcall TfrmOrderMng::BtnClearClick(TObject *Sender)
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
		frm->PrintType = 1;//订单
		frm->InputPara(dsetNtHeader->FieldByName("ID")->AsString);

		frm->RvSystem1->SystemSetups >>ssAllowSetup;
		frm->RvSystem1->SystemSetups >>ssAllowDestPreview;
		frm->RvSystem1->SystemSetups >>ssAllowDestPrinter;
		frm->RvSystem1->SystemSetups >>ssAllowPrinterSetup;
		frm->RvSystem1->SystemSetups >>ssAllowDestFile;



		frm->RvSystem1->DefaultDest  = rdPreview ;
		frm->RvSystem1->SystemSetups<<ssAllowDestPreview;


			frm->previewprint(1,3);

		frm->Close();
		delete frm;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmOrderMng::N22Click(TObject *Sender)
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
		if (Label2->Caption == "批销单")
		{
			frm->previewprint(1,2);
		}else
		{
		   frm->previewprint(2,2);
		}
		  //1,批销单 2.批销退货单 //1打印格式1 2 打印格式2
		frm->Close();
		delete frm;
	} */
}
//---------------------------------------------------------------------------

void __fastcall TfrmOrderMng::N12Click(TObject *Sender)
{
  BtnClear->Click();
}
//---------------------------------------------------------------------------

void __fastcall TfrmOrderMng::dbnbedtDiscountKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r')
	{
	 // Perform(WM_NEXTDLGCTL, 0, 0);
	  edtCatalog->Text = "";
	  edtCatalog->SetFocus();

	}
}
//---------------------------------------------------------------------------



void __fastcall TfrmOrderMng::FormResize(TObject *Sender)
{
 dbgrdNote->Height = 389;
  dbgrdNote->Width = 846;

}
//---------------------------------------------------------------------------

void __fastcall TfrmOrderMng::N4Click(TObject *Sender)
{
lblCatalog->Caption = "定 价";
m_catalogSearchMode=6;
}
//---------------------------------------------------------------------------

void __fastcall TfrmOrderMng::dbnbedtTotalAmountKeyPress(TObject *Sender, wchar_t &Key)

{
       if (Key == '\r')
	{
	  Perform(WM_NEXTDLGCTL, 0, 0);

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmOrderMng::cbstateChange(TObject *Sender)
{
UpdateNtHeader();
}
//---------------------------------------------------------------------------

void  TfrmOrderMng::FindNote(String code)
{
	DelInvalidNtHeader();
	edtCatalog->Text = "";
	edtQryVendor->Text = "";
	try
	{
		LockWindowUpdate(dbgrdNote->Handle);//锁定指定窗口，禁止它更新。
		QryNtHeader(code);
	}
	__finally
	{
		LockWindowUpdate(NULL);
	}
}

//---------------------------------------------------------------------------
void TfrmOrderMng::NtCodeChange()
{
  	AnsiString sql;
	int max,index;
	String code = dbedtWsaleNtCode->Text;
	if (code != "" && MaxNote != "") {
        max = StrToInt(MaxNote.SubString(11,5));
		index = StrToInt(code.SubString(9,5));
		if (index == 0 && max == 0) {
			Sbutfirst->Enabled = true;
			Sbutbefore->Enabled = false;
			Sbutnext->Enabled = false;
			Sbutend->Enabled = false;
		}
		if (index == 0 && max != 0) {
			Sbutfirst->Enabled = false;
			Sbutbefore->Enabled = false;
			Sbutnext->Enabled = true;
			Sbutend->Enabled = true;
		}
		if (index != 0 && index < max) {
			Sbutfirst->Enabled = true;
			Sbutbefore->Enabled = true;
			Sbutnext->Enabled = true;
			Sbutend->Enabled = true;
		}
		if (index != 0 && index == max) {
			Sbutfirst->Enabled = true;
			Sbutbefore->Enabled = true;
			Sbutnext->Enabled = false;
			Sbutend->Enabled = false;
		}
		if (index != 0 && index == max + 1) {
			Sbutfirst->Enabled = true;
			Sbutbefore->Enabled = true;
			Sbutnext->Enabled = false;
			Sbutend->Enabled = false;
		}
		if (index != 0 && index > max + 1) {
			Sbutfirst->Enabled = true;
			Sbutbefore->Enabled = false;
			Sbutnext->Enabled = false;
			Sbutend->Enabled = false;
		}
	}
}

//---------------------------------------------------------------------------


void __fastcall TfrmOrderMng::SbutfirstClick(TObject *Sender)
{
	if (dbedtWsaleNtCode->Text == "") {
		return;
	}
	String correntcode = dbedtWsaleNtCode->Text.Trim() ;
	String code = correntcode.SubString(0,8);
	code = code + "00000";
	dbedtWsaleNtCode->Text = code;
	code = "00" + code;
	FindNote(code);
	NtCodeChange();
}
//---------------------------------------------------------------------------

void __fastcall TfrmOrderMng::SbutbeforeClick(TObject *Sender)
{
	if (dbedtWsaleNtCode->Text == "") {
		return;
	}
	String correntcode = dbedtWsaleNtCode->Text.Trim() ;
	int code = StrToInt(correntcode.SubString(9,5) );
	code = code - 1;
	if (code < 10) {
		correntcode = correntcode.SubString(0,8) + "0000" + IntToStr(code);
	}
	else if (code < 100) {
		correntcode = correntcode.SubString(0,8) + "000" + IntToStr(code);
	}
	else if (code < 1000) {
		correntcode = correntcode.SubString(0,8) + "00" + IntToStr(code);
	}
	else if (code < 10000) {
		correntcode = correntcode.SubString(0,8) + "0" + IntToStr(code);
	}
	else if (code < 100000) {
		correntcode = correntcode.SubString(0,8) + IntToStr(code);
	}
	//QryNtHeader(correntcode);
	dbedtWsaleNtCode->Text = correntcode;
	correntcode = "00" + correntcode;
	FindNote(correntcode);
	NtCodeChange();
}
//---------------------------------------------------------------------------

void __fastcall TfrmOrderMng::SbutnextClick(TObject *Sender)
{
	if (dbedtWsaleNtCode->Text == "") {
		return;
	}
	String correntcode = dbedtWsaleNtCode->Text.Trim() ;
	int code = StrToInt(correntcode.SubString(9,5) );
	code = code + 1;
	if (code < 10) {
		correntcode = correntcode.SubString(0,8) + "0000" + IntToStr(code);
	}
	else if (code < 100) {
		correntcode = correntcode.SubString(0,8) + "000" + IntToStr(code);
	}
	else if (code < 1000) {
		correntcode = correntcode.SubString(0,8) + "00" + IntToStr(code);
	}
	else if (code < 10000) {
		correntcode = correntcode.SubString(0,8) + "0" + IntToStr(code);
	}
	else if (code < 100000) {
		correntcode =  correntcode.SubString(0,8) + IntToStr(code);
	}
	//QryNtHeader(correntcode);
	dbedtWsaleNtCode->Text = correntcode;
	correntcode = "00" + correntcode;
	FindNote(correntcode);
	NtCodeChange();
}
//---------------------------------------------------------------------------

void __fastcall TfrmOrderMng::SbutendClick(TObject *Sender)
{
	if (dbedtWsaleNtCode->Text == "") {
		return;
	}
	String correntcode = MaxNote ;
	dbedtWsaleNtCode->Text = correntcode;
	correntcode = "00" + correntcode;
	FindNote(correntcode);
	NtCodeChange();
}
//---------------------------------------------------------------------------

void __fastcall TfrmOrderMng::N6Click(TObject *Sender)
{
	for (int i = 1; i <= dsetNote->RecordCount ; i++) {
		dbgrdNote->DataSource->DataSet->RecNo = i;
		dbgrdNote->SelectedRows->CurrentRowSelected = true;
	}
}
//---------------------------------------------------------------------------

