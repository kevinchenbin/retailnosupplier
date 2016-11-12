//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "suppmanage.h"
#include "detailemessage.h"
#include "CoustomerImport.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma link "RzButton"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzCmboBx"
#pragma link "RzDBGrid"
#pragma resource "*.dfm"
TSuppMana *SuppMana;
//---------------------------------------------------------------------------
__fastcall TSuppMana::TSuppMana(TComponent* Owner,int Type,TADOConnection *cnn,int stgid,bool sup,bool client)
	: TForm(Owner)
{
DBGridrecord->OnDrawColumnCell=DBGridrecordDrawColumnCell;
	type = Type;
    cn = cnn;
        fstgid=stgid;
	aqinit->Connection = cnn;
	aqrecord->Connection = cnn;
	query->Connection = cnn;
        qfsupplier=sup;


        qfclient=client;

	if (type == 1) {
		this->Caption = "��Ӧ�̹���";
	   //	DBGridrecord->Columns ->Items[5]->Title->Caption = "�ɹ�Ա";
		RzLabel1->Caption = "��Ӧ������" ;
	}
	if (type == 2) {
		this->Caption = "�ͻ�����";
		RzLabel1->Caption = "�ͻ�����"  ;
		Label3->Caption = "ҵ��Ա";
	}
     /*	AnsiString sql;
	int maxid;
	sql = "select max(ID) as id from cust_customerinfo where stgid="+IntToStr(fstgid);
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	maxid = query->FieldByName("id")->AsInteger ;

		sql = "select A.Type,A.ID,A.name,A.contact,A.telephone,A.fax,A.Salesman,A.code,A.date,Convert(varchar(20),A.date,111) as date1,A.address,A.local,A.Balance,A.BusinessLessBookstore,A.BookstoreLessBusiness  from cust_customerinfo A left join Sys_local B on "
			  "A.Local = b.Local left join SYS_User C on A.salesman = C.Name "
			  " where A.ID > " + IntToStr(maxid) ;

	aqrecord->Close();
	aqrecord->SQL->Clear();
	aqrecord->SQL->Add(sql); */
}
//---------------------------------------------------------------------------
void TSuppMana::Initsalesman()
{  	//��ʼ��������Ա
	AnsiString sql ,value;
	if (type == 1) {
		sql = "select * from SYS_StaffInfo where career = 1";
	}
	else
	{
		sql = "select * from SYS_StaffInfo where career = 2";
	}

	aqinit->Close();
	aqinit->SQL->Clear();
	aqinit->SQL->Add(sql);
	aqinit->Open();
	while(!aqinit->Eof)
	{
		cbsale->AddItem(aqinit->FieldByName("Name")->AsAnsiString,(TObject*)aqinit->FieldByName("ID")->AsInteger );
		aqinit->Next();
	}
}
 int TSuppMana::getsalemanid(AnsiString name)
 {
	   int i;

	  // i= CBsale->Items->IndexOf(name) ;
	  // if (i!=-1) {
	  //      return (int)CBsale->Items->Objects[i];
	 //  }else return -1;


 }
//---------------------------------------------------------------------------
void TSuppMana::InitLocalinfo()
{
	//��ʼ������
	AnsiString sql ,value;
	sql = "select ID,local from SYS_local";
	aqinit->Close();
	aqinit->SQL->Clear();
	aqinit->SQL->Add(sql);
	aqinit->Open();
	while(!aqinit->Eof)
	{
		cblocal->AddItem(aqinit->FieldByName("local")->AsString,(TObject*)aqinit->FieldByName("ID")->AsInteger);
		aqinit->Next();
	}
}
//---------------------------------------------------------------------------
void __fastcall TSuppMana::BtnViewClick(TObject *Sender)
{
	AnsiString sql,sqlwhere;
	sql = "select rank() over(order by A.id) as xuhao,A.Type,A.ID,A.name,A.stgid,A.contact,A.customerstate as cstate, case A.customerstate when 1 then '����' when 0 then 'ͣ��' end as customerstate,A.Mobile,A.CreditMoney,A.Bond,A.telephone,A.fax,A.Salesman,A.code,A.date,Convert(varchar(20),A.date,111) as date1,A.address,A.local ,A.Balance,A.BusinessLessBookstore,A.BookstoreLessBusiness,A.bk,CUST_Customertype.name as typename from cust_customerinfo A  " ;
	sql = sql + "  left join CUST_Customertype on A.customertype = CUST_Customertype.id ";// left join SYS_StaffInfo C on A.salesman = C.name ";


	sqlwhere = " where A.type  = " + IntToStr(type);
	if (edquery->Text != "") {
		sqlwhere = sqlwhere + " and A.name like '%" + edquery->Text.Trim() + "%'";
	}
	if (etcontax->Text != "") {
		sqlwhere = sqlwhere +  " and A.Contact like '%" + etcontax->Text + "%'";
	}
	if (cblocal->Text != "") {
		sqlwhere = sqlwhere + " and A.Local = '" + IntToStr((int)(cblocal->Items->Objects[cblocal->ItemIndex])) +"'";
	}
	if (cbsale->Text !="") {
		sqlwhere = sqlwhere + " and c.name = '" + cbsale->Text.Trim() +"'";
	}
        if (qfsupplier) {
          sqlwhere =sqlwhere+ " and A.stgid="+IntToStr(fstgid);
        }

        if (qfclient) {
           sqlwhere =sqlwhere+ " and A.stgid="+IntToStr(fstgid);
        }


        if (cbstates->Text !="ȫ��") {
            if (cbstates->ItemIndex==1) {
              sqlwhere =sqlwhere+ " and A.customerstate=1";
            }else
            if (cbstates->ItemIndex==2 ) {
               sqlwhere =sqlwhere+ " and A.customerstate=0";
            }

        }

	aqrecord->Close();
	aqrecord->SQL->Clear();
	aqrecord->SQL->Add(sql+sqlwhere);
	aqrecord->DisableControls();
	aqrecord->EnableControls();
	aqrecord->Open();
}
//---------------------------------------------------------------------------
void __fastcall TSuppMana::BtnNewClick(TObject *Sender)
{
	TDetaileForm * frm = new TDetaileForm(Application,type,1,"",cn,fstgid);
	frm->ShowModal() ;
	delete frm;
	//aqrecord->Close();
	//aqrecord->Open();
	aqrecord->Active = false;
	aqrecord->DisableControls();
	aqrecord->EnableControls();
	aqrecord->Active = true;
}
//---------------------------------------------------------------------------
void __fastcall TSuppMana::BtnFinishClick(TObject *Sender)
{
	if (aqrecord->IsEmpty() ) {
    	return;
	}
	if (aqrecord->FieldByName("name")->AsString == "��ͨ��Ӧ��" ) {
		ShowMsg(Handle ,"��ͨ��Ӧ�̲����޸ģ�",3);
		return;
	}
	if (aqrecord->FieldByName("name")->AsString == "��ͨ�ͻ�" ) {
		ShowMsg(Handle ,"��ͨ�ͻ������޸ģ�",3);
		return;
	}
	AnsiString sql;
	if (type == 1) {
		sql = "select * From BS_StorageNoteHeader where (cwstate > 0 or Checked <> 0) and SupplierID = " + aqrecord->FieldByName("ID")->AsAnsiString ;
	}
	else
	{
		sql = "select * From BS_WsaleNoteHeader where (cwstate > 0 or Checked <> 0) and VendorID = " + aqrecord->FieldByName("ID")->AsAnsiString ;
	}
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	if (query->RecordCount > 0) {
		ShowMsg(Handle ,"����������ز����¼��������޸ģ�",3);
		//return;
	}
	TDetaileForm * frmffff = new TDetaileForm(Application,type,2,aqrecord->FieldByName("ID")->AsString,cn,fstgid);
	frmffff->ShowModal() ;
	delete frmffff;
	aqrecord->Active = false;
	aqrecord->DisableControls();
	aqrecord->EnableControls();
	aqrecord->Active = true;
}
//---------------------------------------------------------------------------
void __fastcall TSuppMana::BtnDeleteClick(TObject *Sender)
{
	AnsiString sqlSM,sqlCUS,sdf;
	if (aqrecord->IsEmpty() ) {
    	return;
	}
	if (aqrecord->FieldByName("name")->AsString == "��ͨ��Ӧ��" ) {
		ShowMsg(Handle ,"��ͨ��Ӧ�̲���ɾ����",3);
		return;
	}
	if (aqrecord->FieldByName("name")->AsString == "��ͨ�ͻ�" ) {
		ShowMsg(Handle ,"��ͨ�ͻ�����ɾ����",3);
		return;
	}
	sqlSM = "delete from CUST_CustomerStartMoney where CustomerID = " + aqrecord->FieldByName("ID")->AsString ;
	sqlCUS = "delete from CUST_CustomerInfo where ID = " + aqrecord->FieldByName("ID")->AsString ;
	if (type == 1) {
		sdf = "ȷ��ɾ����Ӧ��"+aqrecord->FieldByName("name")->AsString +"��" ;
	}
	if (type == 2) {
		sdf = "ȷ��ɾ���ͻ�"+aqrecord->FieldByName("name")->AsString +"��" ;
	}
	if (ShowMsg(Handle ,sdf.c_str(),1)==1) {
		try {
			aqinit->Close();
			aqinit->SQL->Clear();
			aqinit->SQL->Add(sqlSM);
			aqinit->ExecSQL();
			aqinit->Close();
			aqinit->SQL->Clear();
			aqinit->SQL->Add(sqlCUS);
			aqinit->ExecSQL();
		} catch (Exception &E) {
			ShowMsg(Handle ,"�����ݸ�ϵͳ���������й���������ɾ����",3);
		}
	}
	aqrecord->Active = false;
	aqrecord->DisableControls();
	aqrecord->EnableControls();
	aqrecord->Active = true;
}
//---------------------------------------------------------------------------
void __fastcall TSuppMana::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TSuppMana::FormShow(TObject *Sender)
{
	Initsalesman();
	InitLocalinfo();
	if (type == 1) {
		DBGridrecord->Columns->Items[1]->Title->Caption = "��Ӧ������";
	}
	if (type == 2) {
		DBGridrecord->Columns->Items[1]->Title->Caption = "�ͻ�����";
		DBGridrecord->Columns->Items[9]->Title->Caption = "ҵ��Ա";
	}
        BtnView->Click();
}
//---------------------------------------------------------------------------

void __fastcall TSuppMana::BtnExportClick(TObject *Sender)
{
	if (!aqrecord->IsEmpty() ) {
    	DbgridToExcel(DBGridrecord);
	}
}
//---------------------------------------------------------------------------

//Excel��������
bool __fastcall TSuppMana::DbgridToExcel(TRzDBGrid* dbg)
{
	AnsiString temptext ;
	int k = dbg->DataSource ->DataSet ->RecordCount ,n=0;
	if(k == 0)
	{
		ShowMsg(Handle ,"û�����ݣ�",3);
		return false;
	}
	Variant     v;
	v   =Variant::CreateObject("Excel.Application");
	v.OlePropertySet("Visible",true);
	v.OlePropertyGet("WorkBooks").OleFunction("Add");
//  ��Excel�г��ַ�����ʾ
	if (type == 1) {
		v.OlePropertyGet("Cells",1,5).OlePropertySet("Value","��Ӧ�̲�ѯ��¼" );
	}
	else
	{
		v.OlePropertyGet("Cells",1,5).OlePropertySet("Value","�ͻ���ѯ��¼" );
	}

/*v.OlePropertyGet("Cells",2,1).OlePropertySet("Value","��λ����" );
	temptext = "'"+ etname->Text;
	v.OlePropertyGet("Cells",2,2).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",2,4).OlePropertySet("Value","��ϵ��" );
	temptext = "'"+ etcontax->Text;
	v.OlePropertyGet("Cells",2,5).OlePropertySet("Value",temptext .c_str());
	v.OlePropertyGet("Cells",3,1).OlePropertySet("Value","��������" );
	temptext = "'"+ CBlocal->Text;
	v.OlePropertyGet("Cells",3,2).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",3,4).OlePropertySet("Value","�ɹ�Ա" );
	temptext = "'"+ CBsale->Text;
	v.OlePropertyGet("Cells",3,5).OlePropertySet("Value",temptext .c_str());  */

	n=1;

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
		for(int j=1;j<dbg->Columns ->Count+1  ;j++)
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
//---------------------------------------------------------------------------

void __fastcall TSuppMana::etcontaxKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
		BtnView->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall TSuppMana::BtnImportClick(TObject *Sender)
{
	aqrecord->Active = true;
	TFormCousImport *frm = new TFormCousImport(Application,aqrecord,type,fstgid);
	frm->ShowModal();
	delete frm;
}
//---------------------------------------------------------------------------

void __fastcall TSuppMana::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TSuppMana::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall TSuppMana::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F2) {     //�µ�
		BtnNew->Click();
	}
	if (Key == VK_F3) {     //�޸�
		BtnFinish->Click();
	}
	if (Key == VK_F5) {     //ɾ��
		BtnDelete->Click();
	}
	if (Key == VK_F6) {     //����
		BtnExport->Click();
	}
	if (Key == VK_F7) {     //����
		BtnImport->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 70 ) {    //��ѯ
		BtnView->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 78 ) {    //��С��
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 81 ) {    //�˳�
		BtnExit->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==90) {   //�ָ�����
		WindowState = wsNormal  ;
	}
}
//---------------------------------------------------------------------------

void __fastcall TSuppMana::edqueryKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
    if (Key == VK_RETURN) {
		BtnView->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall TSuppMana::cbsaleKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
		BtnView->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall TSuppMana::cblocalKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
		BtnView->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall TSuppMana::DBGridrecordTitleClick(TColumn *Column)
{
	if (aqrecord->IsEmpty() ) {
    	return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (aqrecord->Sort == "") {
		aqrecord->Sort =  Column->FieldName + " ASC";
	}
	else if (aqrecord->Sort == qusort) {
		aqrecord->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		aqrecord->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------

void __fastcall TSuppMana::DBGridrecordDrawColumnCell(TObject *Sender, const TRect &Rect,
		  int DataCol, TColumn *Column, Grids::TGridDrawState State)
{
       //
       if (DBGridrecord->DataSource->DataSet->RecordCount>0) {
         if (!DBGridrecord->DataSource->DataSet->FieldByName("cstate")->AsBoolean)
        {
          ((TDBGrid*)Sender)->Canvas->Font->Color=clRed;
       }
	  ((TDBGrid*)Sender)->DefaultDrawColumnCell(Rect,DataCol,Column,State);
       }
}
//---------------------------------------------------------------------------

void __fastcall TSuppMana::PopupMenu1Popup(TObject *Sender)
{
	//                                    dsOpening
                                          // TDataSetState
        if (aqrecord->State == dsOpening) {
            if (DBGridrecord->DataSource->DataSet->FieldByName("cstate")->AsBoolean) {
              N1->Enabled = false;
              N2->Enabled = true;
           }else
           {
              N1->Enabled = true;
              N2->Enabled = false;

           }
        }

}
//---------------------------------------------------------------------------
void TSuppMana::updatestate(int type)
{

        if ((aqrecord->FieldByName("name")->AsAnsiString=="��ͨ��Ӧ��")||(aqrecord->FieldByName("name")->AsAnsiString=="��ͨ�ͻ�")) {

           ShowMsg(Handle ,"Ĭ�Ͽͻ���Ӧ�̣�����ͣ�ã�",3);
          return ;
        }
        AnsiString sql ;
        sql = "update CUST_CustomerInfo set customerstate = "+IntToStr(type)+" where id = "+aqrecord->FieldByName("ID")->AsAnsiString ;

        TADOQuery *aq = new TADOQuery(NULL);
        aq->Connection = cn;
        aq->Close();
        aq->SQL->Clear();
        aq->SQL->Add(sql);
        aq->ExecSQL();


        BtnView->Click();



}
//---------------------------------------------------------------------------

void __fastcall TSuppMana::N1Click(TObject *Sender)
{
  if (DBGridrecord->DataSource->DataSet->RecordCount<=0) {
            return ;
   }
    if( type == 1)
    {
      if (Supplierpower) {
        updatestate(1);
      } else
      {
         ShowMsg(Handle,"û�й�Ӧ����ͣ��Ȩ��",3);
      }

    }else if (type==2){
          if (Clientpower) {
            updatestate(1);
          }else
          {
            ShowMsg(Handle,"û�й�Ӧ����ͣ��Ȩ��",3);
          }

    }
}
//---------------------------------------------------------------------------

void __fastcall TSuppMana::N2Click(TObject *Sender)
{
if (DBGridrecord->DataSource->DataSet->RecordCount<=0) {
            return ;
   }
 if( type == 1)
    {
      if (Supplierpower) {
        updatestate(0);
      } else
      {
         ShowMsg(Handle,"û�пͻ���ͣ��Ȩ��",3);
      }

    }else if (type==2){
          if (Clientpower) {
            updatestate(0);
          }else
          {
            ShowMsg(Handle,"û�й�Ӧ����ͣ��Ȩ��",3);
          }

    }
}
//---------------------------------------------------------------------------

