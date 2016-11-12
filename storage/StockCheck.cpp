//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "StockCheck.h"
#include "pdtypes.h"
#include "NoteCode.h"
#include "ModalDialog.h"
#include "QryNoteCodeForm.h"
#include "checkselbook.h"
#include "Unitkucunpandian.h"
#include "Unitpanbook.h"
#include "unitcfpandian.h"
#include "global.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "RzPrgres"
#pragma link "RpCon"
#pragma link "RpConDS"
#pragma link "RpDefine"
#pragma link "RpRave"
#pragma link "RpBase"
#pragma link "RpSystem"
#pragma link "RzDBEdit"
#pragma link "RzEdit"
#pragma resource "*.dfm"
Tfrmcheckstock *frmcheckstock;
//---------------------------------------------------------------------------
__fastcall Tfrmcheckstock::Tfrmcheckstock(TComponent* Owner,TADOConnection* con,LandInfo* li)
	: TForm(Owner)
{
  li->con = con;
  fcon = con;
  checkli = *li;
  dtpstart->Date = Date();
  aquery->Connection = con;
  m_storageID = li->storageID ;
  editusername->Text = li->UserName ;
  atable->Connection = con;
  adosp->Connection = con;
  adocount->Connection = con;
  aqueryupdate->Connection = con;
  aqheader->Connection = con;
  CatalogSearchMode = 1;//
  m_storageID = checkli.storageID ;
  m_local = 0;
  Code = "";
  aquerynotcheckbook->Connection = con;
  aqinsertkuchen->Connection = con;
  connect = con;
  weipanshu = false;

}
void Tfrmcheckstock::ReadData(TADOQuery * aquery)
{
	Store = new TStringList();
	Local = new TStringList();
	AnsiString value;
	AnsiString sql ;
	int LocalID;
	int StorgeID;
	sql = "select SYS_GroupAction.* from SYS_GroupAction join SYS_group on SYS_group.id = SYS_GroupAction.groupid "
			" join SYS_UserGroup on SYS_GroupAction.groupid = SYS_UserGroup.groupid "
			" where  SYS_group.groupname = 'ϵͳ����Ա' and SYS_UserGroup.userid = " + IntToStr(checkli.userID);
    aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Open();
	if (aquery->IsEmpty() ) {
		guanliyuan = 0;
	}
	else
	{
		guanliyuan = 1;
	}

	sql = "select pancount from BS_PandianCount where state = 0 and stgid = " + IntToStr(m_storageID) ;
	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Open();
	if (aquery->IsEmpty() ) {
		count = 0;
		BtnProperties->Enabled = false;
		BtnChangeOptions->Enabled = false;
		if (guanliyuan == 0) {
			Btninit->Enabled = false;
		}
	}
	else
	{
		count = aquery->FieldByName("pancount")->AsInteger ;
		Btninit->Enabled = false;
		if (guanliyuan == 0) {
			BtnHorizontalTile->Enabled = false;
			BtnChangeOptions->Enabled = false;
		}else
                {
                     BtnHorizontalTile->Enabled = true;
			BtnChangeOptions->Enabled = true;

                }
	}

	sql = "select ID , Name,StgID ,state from STK_Bookstackinfo";
	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Open();
	while(!aquery->Eof)
	{
	   Booklocal *bl = new Booklocal(aquery->FieldByName("name")->AsAnsiString ,aquery->FieldByName("StgID")->AsAnsiString ,aquery->FieldByName("id")->AsAnsiString,aquery->FieldByName("state")->AsAnsiString) ;
	   Local->AddObject(bl->ID , (TObject*)bl);
	   aquery->Next();
	}
	sql = "select ID,Name from SYS_storageinfo";
	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Open();
	while(!aquery->Eof)    	//���ص���Ϣ
	{
	   Storage  *st = new Storage(aquery->FieldByName("name")->AsAnsiString,aquery->FieldByName("id")->AsAnsiString);
	   Store->AddObject(st->ID ,(TObject*)st);
	   if (m_storageID==st->ID ) {
			labtitle->Caption = st->Name.Trim();
	   }
   /*	  if (m_storageID = 0) {        //�ܵ�������еĵ���Ϣ
	   cbstore->Items->Add(st->Name);
	  } else
	  {
		if (st->ID == m_storageID) {          //�����ܵ�ֻ���ر�����Ϣ
		  StorgeID = StrToInt(st->ID);
		  cbstore->Items->AddObject(st->Name ,(TObject*)StorgeID);
		}

		}  */
	   aquery->Next();
	  }


	//���ؿ�λ��Ϣ
   for (int i = 0; i < Local->Count ; i++) {

	  if(((Booklocal*)Local->Objects[i])->StgID == m_storageID)
	  {
		LocalID = StrToInt(((Booklocal*)Local->Objects[i])->ID) ;
		cblocal->Items->AddObject(((Booklocal*)Local->Objects[i])->Name,(TObject*)LocalID );
	  }

   }

	 cblocal->ItemIndex = 0;

	}

//---------------------------------------------------------------------------
void __fastcall Tfrmcheckstock::edtcheckinfoKeyPress(TObject *Sender, wchar_t &Key)

{
	if (CatalogSearchMode == 4) {
		if ((Key < '0' || Key > '9') && (Key != '\b') && (Key != '.') && (Key != '\r') ) {
            Key = NULL;
		}
	 }

   if (Key == '\r')                //int m_catalogSearchMode;//1���� 2Ϊ�Ա��� 3Ϊ����  4 ISBN 5 ����
   {
		if (edtcheckinfo->Text == "") {
			ChangeCatalogSearchMode();
			return;
		}
	 //���������Ϣ
	 if (CatalogSearchMode == 4) {
		try {
			float pice = StrToFloat(edtcheckinfo->Text);
		} catch (...) {

                         ShowMsg(Handle ,"��¼����ȷ�Ķ��ۣ���ȷ�ϣ�",3);
			return;
		}
	 }

	 if (cblocal->Text == "") {

                 ShowMsg(Handle ,"��ѡ���λ��",3);
		 return;
	 }

	String sql;
	AnsiString sqlwhere;
	bool zerodisplay;
	int icount;
	float discount;
	if (edtcheckinfo->Text == "") {
        return;
	}

	 //1���� 2Ϊ�Ա��� 3Ϊ����  4 ���� 5 ����

		sql = "select BS_BookCatalog.ID,BS_BookCatalog.Name,BS_BookCatalog.Barcode,STK_BookInfo.Cbprice,"
			"BS_BookCatalog.UserDefCode,BS_BookCatalog.ISBN,STK_BookInfo.ID as STK_BookinfoID,"
			"STK_BookInfo.Amount,STK_BookstackInfo.Name as BkstackName,BS_BookCatalog.Price ,BS_PressInfo.AbbreviatedName ,STK_BookstackInfo.name LocalName "
			"from STK_BookInfo  join BS_BookCatalog on STK_BookInfo.BkcatalogID=BS_BookCatalog.ID "
			"join STK_BookstackInfo on STK_BookInfo.BkstackID=STK_BookstackInfo.ID "
			"left join BS_PressInfo ON BS_BookCatalog.PressID = BS_PressInfo.ID "
			"where STK_BookstackInfo.StgID=" + IntToStr(m_storageID) + " and STK_BookstackInfo.Name = '" + cblocal->Text.Trim() + "' " ;
		  //	+ " and  STK_BookstackInfo.id = " + IntToStr((int )cblocal->Items->Objects[cblocal->ItemIndex]);
    AnsiString ISBN = "",Presscount = "";
	switch (CatalogSearchMode)
	{
	case 1://����
		if (edtcheckinfo->Text.Length() > 13 ) {
			ISBN =  edtcheckinfo->Text.SubString(1,13);
			Presscount = edtcheckinfo->Text.SubString(14,2);
                        sqlwhere = sqlwhere + " and BS_BookCatalog.PressCount like '%" + Presscount + "%' ";
		}
		else
		{
			ISBN =  edtcheckinfo->Text.Trim();
		}
		sqlwhere = sqlwhere + " and BS_BookCatalog.Unavailable=1 and (BS_BookCatalog.Barcode like '%" + ISBN  + "%' or BS_BookCatalog.ISBN like '%" + ISBN + "%') ";

		break;
	case 2://�Ա���
		sqlwhere = sqlwhere + " and BS_BookCatalog.Unavailable=1 and BS_BookCatalog.UserDefCode like '%" + edtcheckinfo->Text.Trim()  + "%'";
		break;
	case 3://����
		sqlwhere = sqlwhere + " and BS_BookCatalog.Unavailable=1 and BS_BookCatalog.Name like '%" + edtcheckinfo->Text.Trim()  + "%'";
		break;
	case 4: //����
		sqlwhere = sqlwhere	+ " and BS_BookCatalog.Unavailable=1 and BS_BookCatalog.Price = " + edtcheckinfo->Text.Trim();
		break;
	case 5://����
		sqlwhere = sqlwhere + " and BS_BookCatalog.Unavailable=1 and BS_BookCatalog.Author like '%" + edtcheckinfo->Text.Trim()  + "%'";
		break;
	default:
		break;
	}
	sql = sql + sqlwhere;

   try
   {

		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->Open();

		if (aquery->RecordCount > 1) {   //������¼

		Tfrmcatalogselect *frm  = new Tfrmcatalogselect(Application, checkli.con , aquery);




		if (mrOk==frm->ShowModal()) {
			//�õ�Ŀǰ����Ŀ�λ�����Ĭ�Ͽ�λ��û��ʾ������ͻ���ʾ
			if (aquery->FieldByName("BkstackName")->AsAnsiString!=cblocal->Text) {


		   AnsiString sql ;
		   sql = "select * from stk_bookinfo A join STK_BookstackInfo B on A.bkstackid = B.ID ";
		   sql = sql + " where bkcatalogid = " +aquery->FieldByName("ID")->AsAnsiString ;
		   sql = sql + " and B.name <> 'Ĭ�Ͽ�λ' and  BkstackID <> " + IntToStr((int)cblocal->Items->Objects[cblocal->ItemIndex]);
		   sql = sql + " and B.stgid = " + IntToStr(m_storageID);
		   AnsiString Msg;
		   Msg = " �����Ѵ���� \n";
		   TADOQuery * aq =  new TADOQuery(NULL);
		   aq->Connection = checkli.con ;
		   aq->Close();
		   aq->SQL->Clear();
		   aq->SQL->Add(sql);
		   aq->Open();
		   if (aq->RecordCount > 0) {
			  for (int i = 0; i < aq->RecordCount; i++) {
				  Msg = Msg + aq->FieldByName("name")->AsAnsiString + " \n";
				  aq->Next();
			  }
			  Msg = Msg + "\n �Ƿ�Ҫ���뱾�⣿";

			 if(ShowMsg(Handle ,Msg.c_str(),1)== 1)
			 {

			 }else
			 {
				return;
			 }

			 }

		   }
			   TLocateOptions   Opts;
			   Opts.Clear();
			   Opts   <<   loPartialKey;
			   String   str   = aquery->FieldByName("STK_BookinfoID")->AsAnsiString;
			   if ( aqueryupdate->Locate("STK_bookInfoID",str,Opts))
			   {
					//MessageBoxA(0,"���������̵�!","����̵����",MB_ICONASTERISK);
					Tfrmcfpandian *frm1 = new Tfrmcfpandian(Application,fcon);
					frm1->stkbkid = aquery->FieldByName("STK_BookinfoID")->AsInteger ;
					frm1->bendan = 1;
					if (frm1->ShowModal() == mrOk  ) {
                    	aqueryupdate->Edit();
						aqueryupdate->FieldByName("shouldamount")->AsInteger  = aqueryupdate->FieldByName("shouldamount")->AsInteger + frm1->addamount ;
						aqueryupdate->FieldByName("balance")->AsInteger =aqueryupdate->FieldByName("shouldamount")->AsInteger - aqueryupdate->FieldByName("actualamount")->AsInteger;
						aqueryupdate->FieldByName("states")->AsInteger = 0;
						aqueryupdate->FieldByName("Fixedprice")->AsFloat = (aqueryupdate->FieldByName("Price")->AsFloat)*(aqueryupdate->FieldByName("shouldamount")->AsInteger);
						aqueryupdate->FieldByName("Discountprice")->AsFloat  = (aqueryupdate->FieldByName("Discount")->AsFloat)*(aqueryupdate->FieldByName("Fixedprice")->AsFloat)/100;
						edtcheckinfo->Text = "";
					}
					delete frm1;
					try {
						aqueryupdate->UpdateBatch(arCurrent);
					} catch (...) {
					}
					return;
			   }
				TADOQuery *aq = new TADOQuery(this);
				aq->Connection = fcon;
				AnsiString sql;
				sql = "select notecode from STK_StockInventories where stk_bookinfoid = " + str + "and notecode in(select codestr from BS_PandianCount where state = 0)";
				aq->Close();
				aq->SQL->Clear();
				aq->SQL->Add(sql);
				aq->Open();
				if (aq->RecordCount > 0) {
					//AnsiString Note;
					//Note = "�������̵㵥" + aq->FieldByName("notecode")->AsAnsiString + "�ڽ����̵�";
					//MessageBoxA(0,Note.c_str() ,"����̵����",MB_ICONASTERISK);
					delete aq;
					Tfrmcfpandian *frm1 = new Tfrmcfpandian(Application,fcon);
					frm1->stkbkid = aquery->FieldByName("STK_BookinfoID")->AsInteger ;
					if (frm1->ShowModal() == mrOk  ) {
						edtcheckinfo->Text = "";
					}
					delete frm1;
					try {
						//aqueryupdate->Refresh();
					} catch (...) {
					}
					return;
				}
				delete aq;


		   aqueryupdate->Active = true;
		   ((TFloatField *)aqueryupdate->FieldByName("Discount"))->DisplayFormat = "0.00%";
		   aqueryupdate->Insert();
		   aqueryupdate->Append();

		   aqueryupdate->FieldByName("bkcatalogid")->AsAnsiString =aquery->FieldByName("ID")->AsAnsiString  ;
		   aqueryupdate->FieldByName("Price")->AsFloat  =aquery->FieldByName("Price")->AsFloat ;
		   discount = aquery->FieldByName("Cbprice")->AsFloat/aquery->FieldByName("Price")->AsFloat*100;
		   aqueryupdate->FieldByName("Discount")->AsFloat =discount;
		   aqueryupdate->FieldByName("bklocalname")->AsAnsiString = aquery->FieldByName("BkstackName")->AsAnsiString ;
		   aqueryupdate->FieldByName("BarCode")->AsAnsiString = aquery->FieldByName("BarCode")->AsAnsiString  ;
		 //  aqueryupdate->FieldByName("suppliername")->AsAnsiString = aquery->FieldByName("SupplierName")->AsAnsiString  ;
		   aqueryupdate->FieldByName("ISBN")->AsAnsiString = aquery->FieldByName("ISBN")->AsAnsiString  ;
		   aqueryupdate->FieldByName("bookname")->AsAnsiString = aquery->FieldByName("name")->AsAnsiString  ;
		   aqueryupdate->FieldByName("AbbreviatedName")->AsAnsiString = aquery->FieldByName("AbbreviatedName")->AsAnsiString  ;
		   aqueryupdate->FieldByName("actualamount")->AsAnsiString = aquery->FieldByName("Amount")->AsAnsiString  ;
		 //  aqueryupdate->FieldByName("supplierid")->AsAnsiString = aquery->FieldByName("SupplierID")->AsAnsiString  ;
		   aqueryupdate->FieldByName("STK_bookInfoID")->AsAnsiString = aquery->FieldByName("STK_BookinfoID")->AsAnsiString  ;
		   aqueryupdate->FieldByName("NoteCode")->AsAnsiString = Code  ;
		   aqueryupdate->FieldByName("shouldamount")->AsInteger  = 0;
		   edtnumber->SetFocus();
		   //icount  = lcount->Caption.ToInt()  ;
		   //lcount->Caption = IntToStr(++icount);

		}

		}
		if (aquery->RecordCount == 1) {    //ֻ��һ����¼

		   /*TADOQuery * aq =  new TADOQuery(NULL);
		   aq->Connection = checkli.con ;
		   sql = "select * from STK_StockInventories where STK_bookInfoID = " +  aquery->FieldByName("STK_BookinfoID")->AsAnsiString ;
		   aq->Close();
		   aq->SQL->Clear();
		   aq->SQL->Add(sql);
		   aq->Open();
		   if (aq->RecordCount > 0) {
			   MessageBoxA(0,"���������̵�!","����̵����",MB_ICONASTERISK);
			   return;
		   }
		   delete aq;
		    */
		   TLocateOptions   Opts;
			   Opts.Clear();
			   Opts   <<   loPartialKey;
			   String   str   = aquery->FieldByName("STK_BookinfoID")->AsAnsiString;
			   if ( aqueryupdate->Locate("STK_bookInfoID",str,Opts))
			   {
					//MessageBoxA(0,"���������̵�!","����̵����",MB_ICONASTERISK);
					Tfrmcfpandian *frm1 = new Tfrmcfpandian(Application,fcon);
					frm1->stkbkid = aquery->FieldByName("STK_BookinfoID")->AsInteger ;
					frm1->bendan = 1;
					if (frm1->ShowModal() == mrOk  ) {
						aqueryupdate->Edit();
						aqueryupdate->FieldByName("shouldamount")->AsInteger  = aqueryupdate->FieldByName("shouldamount")->AsInteger + frm1->addamount ;
						aqueryupdate->FieldByName("balance")->AsInteger =aqueryupdate->FieldByName("shouldamount")->AsInteger - aqueryupdate->FieldByName("actualamount")->AsInteger;
						aqueryupdate->FieldByName("states")->AsInteger = 0;
						aqueryupdate->FieldByName("Fixedprice")->AsFloat = (aqueryupdate->FieldByName("Price")->AsFloat)*(aqueryupdate->FieldByName("shouldamount")->AsInteger);
						aqueryupdate->FieldByName("Discountprice")->AsFloat  = (aqueryupdate->FieldByName("Discount")->AsFloat)*(aqueryupdate->FieldByName("Fixedprice")->AsFloat)/100;
						edtcheckinfo->Text = "";

					}
					delete frm1;
					try {
						aqueryupdate->UpdateBatch(arCurrent);
					} catch (...) {
					}
					return;
			   }

				TADOQuery *aq = new TADOQuery(this);
				aq->Connection = fcon;
				AnsiString sql;
				sql = "select notecode from STK_StockInventories where stk_bookinfoid = " + str + "and notecode in(select codestr from BS_PandianCount where state = 0)";
				aq->Close();
				aq->SQL->Clear();
				aq->SQL->Add(sql);
				aq->Open();
				if (aq->RecordCount > 0) {
					//AnsiString Note;
					//Note = "�������̵㵥" + aq->FieldByName("notecode")->AsAnsiString + "�ڽ����̵�";
					//MessageBoxA(0,Note.c_str() ,"����̵����",MB_ICONASTERISK);
					delete aq;
					Tfrmcfpandian *frm1 = new Tfrmcfpandian(Application,fcon);
					frm1->stkbkid = aquery->FieldByName("STK_BookinfoID")->AsInteger ;
					if (frm1->ShowModal() == mrOk  ) {
						edtcheckinfo->Text = "";
					}
					delete frm1;
					try {
						//aqueryupdate->Refresh();
					} catch (...) {
					}
					return;
				}
				delete aq;


		   aqueryupdate->Active = true;
		   ((TFloatField *)aqueryupdate->FieldByName("Discount"))->DisplayFormat = "0.00%";
		   aqueryupdate->Insert();
		   aqueryupdate->Append();
		   aqueryupdate->FieldByName("bkcatalogid")->AsAnsiString =aquery->FieldByName("ID")->AsAnsiString  ;
		   aqueryupdate->FieldByName("bklocalname")->AsAnsiString = aquery->FieldByName("BkstackName")->AsAnsiString ;
		   aqueryupdate->FieldByName("BarCode")->AsAnsiString = aquery->FieldByName("BarCode")->AsAnsiString  ;
		 //  aqueryupdate->FieldByName("suppliername")->AsAnsiString = aquery->FieldByName("SupplierName")->AsAnsiString  ;
		   aqueryupdate->FieldByName("ISBN")->AsAnsiString = aquery->FieldByName("ISBN")->AsAnsiString  ;
		   aqueryupdate->FieldByName("bookname")->AsAnsiString = aquery->FieldByName("name")->AsAnsiString  ;
		   aqueryupdate->FieldByName("AbbreviatedName")->AsAnsiString = aquery->FieldByName("AbbreviatedName")->AsAnsiString  ;
		   aqueryupdate->FieldByName("actualamount")->AsAnsiString = aquery->FieldByName("Amount")->AsAnsiString  ;
		  // aqueryupdate->FieldByName("supplierid")->AsAnsiString = aquery->FieldByName("SupplierID")->AsAnsiString  ;
		   aqueryupdate->FieldByName("STK_bookInfoID")->AsAnsiString = aquery->FieldByName("STK_BookinfoID")->AsAnsiString  ;
		   aqueryupdate->FieldByName("NoteCode")->AsAnsiString = Code   ;
		   aqueryupdate->FieldByName("Price")->AsFloat  =aquery->FieldByName("Price")->AsFloat ;
		   discount = aquery->FieldByName("Cbprice")->AsFloat/aquery->FieldByName("Price")->AsFloat*100;
		   aqueryupdate->FieldByName("Discount")->AsFloat =discount;
		   aqueryupdate->FieldByName("shouldamount")->AsInteger = 0;
		   edtnumber->SetFocus();
		   //icount  = lcount->Caption.ToInt()  ;
		   //lcount->Caption = IntToStr(++icount);
		}
		bool newbook = false;
		if (aquery->RecordCount == 0) {
			sql = "select *,bs_pressinfo.AbbreviatedName from bs_bookcatalog left join bs_pressinfo on bs_bookcatalog.pressid = bs_pressinfo.id where 1= 1 " + sqlwhere;
			aquery->Close();
			aquery->SQL->Clear();
			aquery->SQL->Add(sql);
			aquery->Open();
			if (aquery->IsEmpty() ) {

                                ShowMsg(Handle ,"û�и����¼��",3);
			}
			else
			{
				if(ShowMsg(Handle ,"��ǰ�̵��λ�޸��飬�Ƿ�������飡",1)== 1)
				{
					if (aquery->RecordCount > 1) {
						Tfrmpanbook *frm = new Tfrmpanbook(Application,aquery);
						if (frm->ShowModal() == mrOk ) {
							newbook = true;
						}
					}
					if (aquery->RecordCount == 1) {
						newbook = true;
					}
					if (newbook) {
						sql = "declare @BkInfoID int; "
								" exec USP_BS_Get_BookInfoByBkcatalogID " + IntToStr(m_storageID) + ",0," + aquery->FieldByName("ID")->AsString + ",@BkInfoID output,1," + IntToStr((int)cblocal->Items->Objects[cblocal->ItemIndex])+ "; "
								" select @BkInfoID as BkInfoID" ;
						adocount->Close();
						adocount->SQL->Clear();
						adocount->SQL->Add(sql);
						adocount->Open();
						if (adocount->FieldByName("BkInfoID")->AsInteger > 0 ) {
                        	aqueryupdate->Active = true;
						   ((TFloatField *)aqueryupdate->FieldByName("Discount"))->DisplayFormat = "0.00%";
						   aqueryupdate->Insert();
						   aqueryupdate->Append();
						   aqueryupdate->FieldByName("bkcatalogid")->AsAnsiString =aquery->FieldByName("ID")->AsAnsiString  ;
						   aqueryupdate->FieldByName("bklocalname")->AsAnsiString = cblocal->Text ;
						   aqueryupdate->FieldByName("BarCode")->AsAnsiString = aquery->FieldByName("Barcode")->AsAnsiString  ;
						//   aqueryupdate->FieldByName("suppliername")->AsAnsiString = "��ͨ��Ӧ��";
						   aqueryupdate->FieldByName("ISBN")->AsAnsiString = aquery->FieldByName("ISBN")->AsAnsiString  ;
						   aqueryupdate->FieldByName("bookname")->AsAnsiString = aquery->FieldByName("name")->AsAnsiString  ;
						   aqueryupdate->FieldByName("AbbreviatedName")->AsAnsiString = aquery->FieldByName("AbbreviatedName")->AsAnsiString  ;
						   aqueryupdate->FieldByName("actualamount")->AsAnsiString = "0";
						 //  aqueryupdate->FieldByName("supplierid")->AsAnsiString = 0;
						   aqueryupdate->FieldByName("STK_bookInfoID")->AsAnsiString = adocount->FieldByName("BkInfoID")->AsInteger  ;
						   aqueryupdate->FieldByName("NoteCode")->AsAnsiString = Code   ;
						   aqueryupdate->FieldByName("Price")->AsFloat  =aquery->FieldByName("Price")->AsFloat ;
						   //discount = aquery->FieldByName("Cbprice")->AsFloat/aquery->FieldByName("Price")->AsFloat*100;
						   aqueryupdate->FieldByName("Discount")->AsFloat =100;
						   aqueryupdate->FieldByName("shouldamount")->AsInteger = 0;
						   edtnumber->SetFocus();
						}
					}
				}
			}


		}
   }

  catch(...)
   {}


	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcheckstock::N2Click(TObject *Sender)
{
	CatalogSearchMode = 3;
	lbsearch->Caption = "����";
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcheckstock::N4Click(TObject *Sender)
{
	CatalogSearchMode = 2;
	lbsearch->Caption = "�Ա���";
	lbsearch->Tag = 2;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcheckstock::N1Click(TObject *Sender)
{
	CatalogSearchMode = 1;
	lbsearch->Caption = "���";
	lbsearch->Tag = 1;
}
//---------------------------------------------------------------------------


void __fastcall Tfrmcheckstock::N3Click(TObject *Sender)
{
	  CatalogSearchMode= 5;
	  lbsearch->Caption = "����";
	  lbsearch->Tag = 5;
}

//---------------------------------------------------------------------------

void Tfrmcheckstock::ChangeCatalogSearchMode()
{
	CatalogSearchMode++;
	if (CatalogSearchMode >= 6)
	{
		CatalogSearchMode = 1;
	}

	switch (CatalogSearchMode)
	{
	case 1:
    	edtcheckinfo->MaxLength = 15;
        lbsearch->Caption = "���";
		lbsearch->Tag = 1;
		break;
	case 2:
		edtcheckinfo->MaxLength = 0;
		lbsearch->Caption = "�Ա���";
		break;
	case 3:
		edtcheckinfo->MaxLength = 0;
		lbsearch->Caption = "����";
		break;
	case 4:
		edtcheckinfo->MaxLength = 0;
		lbsearch->Caption = "����";
		break;
	case 5:
		edtcheckinfo->MaxLength = 0;
		lbsearch->Caption = "����";
		break;
	default:
		break;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcheckstock::FormCreate(TObject *Sender)
{

	 String sql;
	 int stgid,storeid,j,value,count;
	 String StockNum,Note;                     //���ò���Ա�Ƿ���û�н����̵�ĵ���
	 sql = "select checkstocknum,checkstocklocal,checkstore,STK_CheckStockinfo.bk,STK_BookstackInfo.name as stackname from STK_CheckStockinfo left join STK_BookstackInfo "
		   " on STK_CheckStockinfo.checkstocklocal = STK_BookstackInfo.id "
		   " where employ = " + IntToStr(checkli.userID) + " and STK_CheckStockinfo.state = 1" ;
	ReadData(aquery);
	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Open();
	if (aquery->RecordCount >0) {
        ;
		if (ShowMsg(Handle ,"����δ�������̵㵥���Ƿ�����̵㣿ȷ�������̵㣬ȡ�������µ��̵㵥��",1)== 1) {
			if (aquery->RecordCount > 1) {
				Tfrmkucunpandian *frm = new Tfrmkucunpandian(Application,aquery);
				if (frm->ShowModal() ) {

				}
			}
            for (int i=0; i < cblocal->Items->Count ; i++) {
				if ((int )cblocal->Items->Objects[i] ==  aquery->FieldByName("checkstocklocal")->AsInteger ) {
					cblocal->ItemIndex = i;
					cblocal->Enabled = false;
				}
			}
			StockNum = aquery->FieldByName("checkstocknum")->AsString ;
			stgid = aquery->FieldByName("checkstore")->AsInteger ;
			storeid = aquery->FieldByName("checkstocklocal")->AsInteger ;
			Code = StockNum;
			editnum->Text = Code;
			membk->Text = aquery->FieldByName("bk")->AsString;

			j = Store->IndexOf(IntToStr(stgid));
			if (j >=0) {
				labtitle->Caption = ((Storage*)Store->Objects[j])->Name.Trim();
			}

			aqueryupdate->Parameters->ParamByName("stocknum")->Value = StockNum;
			aqueryupdate->Active = true;
			((TFloatField *)aqueryupdate->FieldByName("Discount"))->DisplayFormat = "0.00%";

			sql = "select ID,checkstockNum,totalamount,Fixedprice,Discountprice,checkdate from STK_CheckStockinfo where checkstockNum = '" + StockNum + "'";
			aqheader->Close();
			aqheader->SQL->Clear();
			aqheader->SQL->Add(sql);
			aqheader->Open();
			dtpstart->Date = aqheader->FieldByName("checkdate")->AsDateTime ;
            BtnProperties->Enabled = false;
            BtnViewIcons->Enabled = true;
		}
		else
		{
			sql = "select ID,Name from STK_BookstackInfo where stgid = " + IntToStr(m_storageID) + " and id not in (select checkstocklocal from STK_CheckStockinfo where state = 1 and employ = " + IntToStr(checkli.userID) + " )";
            aquery->Close();
			aquery->SQL->Clear();
			aquery->SQL->Add(sql);
			aquery->Open();
			if (aquery->IsEmpty() ) {

                ShowMsg(Handle ,"�޿��̵�Ŀ�λ��",3);
				Close();
			}
			else
			{
				cblocal->Items->Clear();
				while (!aquery->Eof )
				{
					cblocal->AddItem(aquery->FieldByName("Name")->AsString ,(TObject*)aquery->FieldByName("id")->AsInteger );
					aquery->Next();
				}
				aquery->First();
                cblocal->ItemIndex = cblocal->Items->IndexOfObject((TObject*)aquery->FieldByName("id")->AsInteger );
			}
		}


		/*value = (int )cblocal->Items->Objects[cblocal->ItemIndex];
		adosp->ProcedureName = "LocalCount";    //����ܼ�¼��
		adosp->Parameters->Clear();
		adosp->Parameters->CreateParameter("@localiD",ftInteger ,pdInput,sizeof(int), &value);
		adosp->Parameters->CreateParameter("@count",ftInteger ,pdOutput,sizeof(int), count);
		adosp->ExecProc();

		adosp->ProcedureName = "localProcessCount";    //�Ѿ�����ļ�¼��
		adosp->Parameters->Clear();
		adosp->Parameters->CreateParameter("@NoteCode",ftString ,pdInput,StockNum.Length() , StockNum);
		adosp->Parameters->CreateParameter("@count",ftInteger  ,pdOutput ,sizeof(int), count);
		adosp->ExecProc();
		*/

	  }

	 /*if (Btninit->Enabled ) {
		  BtnViewIcons->Enabled = false ;
		  BtnViewList->Enabled = false;
		  BtnHorizontalTile->Enabled = false;
		  edtcheckinfo->Enabled = false;
		  edtnumber->Enabled = false;
	 }else
	 {
		 BtnViewIcons->Enabled = true ;
		 BtnViewList->Enabled = true;
		 BtnHorizontalTile->Enabled = true;
		 edtcheckinfo->Enabled = true;
		 edtnumber->Enabled = true;
		 editstate->Text = "�����̵�";
		 //memnote->Lines->Add("��ʾ�����̵����ڽ��У���λ����������");
		 //memnote->Lines->Add("            �κζԸÿ�λ�Ĳ���������ֹ��");
	 } */
}


void __fastcall Tfrmcheckstock::lbsearchMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
  if (Button == mbLeft ) {
	TPoint  pt;
	 GetCursorPos(&pt);
	 pm->Popup(pt.x,pt.y);
	}
}
//---------------------------------------------------------------------------


void __fastcall Tfrmcheckstock::edtnumberKeyPress(TObject *Sender, wchar_t &Key)
{
	  if (Key == '\r') {
		//float Discountprice = 0,  Fixedprice = 0
		//Fixedprice = (aqueryupdate->FieldByName("Price")->AsFloat)*StrToInt(edtnumber->Text);
		//Discountprice = Fixedprice*(aqueryupdate->FieldByName("Discount")->AsFloat)/100;
        if (edtnumber->Text == "") {
        	return;
		}
		if (aqueryupdate->IsEmpty() ) {
			return;
		}
		aqueryupdate->Edit();
		aqueryupdate->FieldByName("shouldamount")->AsInteger  = StrToInt(edtnumber->Text);
		aqueryupdate->FieldByName("balance")->AsInteger =aqueryupdate->FieldByName("shouldamount")->AsInteger - aqueryupdate->FieldByName("actualamount")->AsInteger;
		aqueryupdate->FieldByName("states")->AsInteger = 0;
		aqueryupdate->FieldByName("Fixedprice")->AsFloat = (aqueryupdate->FieldByName("Price")->AsFloat)*(aqueryupdate->FieldByName("shouldamount")->AsInteger);
		aqueryupdate->FieldByName("Discountprice")->AsFloat  = (aqueryupdate->FieldByName("Discount")->AsFloat)*(aqueryupdate->FieldByName("Fixedprice")->AsFloat)/100;
		aqueryupdate->UpdateBatch(arCurrent);
		aqueryupdate->Active = false;
		aqueryupdate->Active = true;
		((TFloatField *)aqueryupdate->FieldByName("Discount"))->DisplayFormat = "0.00%";
		aqueryupdate->Last();
		edtcheckinfo->Text = "";
		edtnumber->Text = "";
		aqheader->Active = false;
		aqheader->Active = true;
		edtcheckinfo->SetFocus();
   }
   if (Key != '\b') {
	if((Key<'0')||(Key>'9'))
		  Key=NULL;
   }


}
//---------------------------------------------------------------------------

void __fastcall Tfrmcheckstock::BtnViewListClick(TObject *Sender)
{
	String sql;

	int STKbookID,shouldamount;
	int value;
	int stgid;
   //���Ŀ�
   if (aqueryupdate->State == dsInactive  ) {
	   return;
   }

	aqueryupdate->First();
	aqueryupdate->DisableControls();
	//rprcess->Max  = aqueryupdate->RecordCount ;
	for (int i=0; i < aqueryupdate->RecordCount  ; i++) {
	  if (aqueryupdate->FieldByName("states")->AsInteger !=1 ) {
		STKbookID = aqueryupdate->FieldByName("STK_bookInfoID")->AsInteger;
		shouldamount = aqueryupdate->FieldByName("shouldamount")->AsInteger;
		int bkcatalogid = aqueryupdate->FieldByName("bkcatalogid")->AsInteger ;
	   //	int supplierid = aqueryupdate->FieldByName("Supplierid")->AsInteger;
		int bkstackid = (int )cblocal->Items->Objects[cblocal->ItemIndex];
		int mode=0;
		int siid = aqueryupdate->FieldByName("id")->AsInteger ;
		int harmnum = aqueryupdate->FieldByName("damagenum")->AsInteger ;
		if (aqueryupdate->FieldByName("bklocalname")->AsAnsiString == "Ĭ�Ͽ�λ") {
			mode = 1;
		}
		adosp->ProcedureName = "UpdateStockAmount";
		adosp->Parameters->Clear();
		adosp->Parameters->CreateParameter("@STKbookID",ftInteger ,pdInput,sizeof(int), &STKbookID);
		adosp->Parameters->CreateParameter("@ActualAmount",ftInteger ,pdInput,sizeof(int), &shouldamount);
		adosp->Parameters->CreateParameter("@bkstackid",ftInteger,pdInput,sizeof(int),&bkstackid);
		adosp->Parameters->CreateParameter("@bkcatalogid",ftInteger,pdInput,sizeof(int),&bkcatalogid);
	  //	adosp->Parameters->CreateParameter("@Supplierid",ftInteger,pdInput,sizeof(int),&supplierid);
		adosp->Parameters->CreateParameter("@mode",ftInteger,pdInput,sizeof(int),&mode);
		adosp->Parameters->CreateParameter("@siid",ftInteger,pdInput,sizeof(int),&siid);
		adosp->Parameters->CreateParameter("@harmnum",ftInteger,pdInput,sizeof(int),&harmnum);


		adosp->ExecProc();
		/*aqueryupdate->Edit();
		aqueryupdate->FieldByName("balance")->AsInteger = 0;
		aqueryupdate->FieldByName("ActualAmount")->AsInteger = aqueryupdate->FieldByName("ShouldAmount")->AsInteger;
		aqueryupdate->UpdateBatch(arAll); */
	  }
	  //rprcess->Position ++;

	  aqueryupdate->Next();
	}
	aqueryupdate->EnableControls();

	if (aqueryupdate->RecordCount != 0 ) {
		ShowMsg(Handle ,"�̵��޸Ŀ����ɹ���",3);
	 aqueryupdate->Active = false;
	 aqueryupdate->Active = true;
	 ((TFloatField *)aqueryupdate->FieldByName("Discount"))->DisplayFormat = "0.00%";
	}

	/*
	sql = "insert into STK_CheckStockinfo (checkstockNum ,checkstore,checkstocklocal,checkdate,bk,employ)"
			" values('" + edtchecknum->Text + "'," + IntToStr(m_storageID) + "," + IntToStr(m_local)
		 + ",'" + DateTimeToStr(dtpdate->Date)+"','" + edtbk->Text.Trim()+ "'," + checkli.userID +")";

	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->ExecSQL();

												   //������λ
	stgid = (int)cbstore->Items->Objects[cbstore->ItemIndex];
	value =   (int )cblocal->Items->Objects[cblocal->ItemIndex];
	adosp->ProcedureName = "UnLockLocal";
	adosp->Parameters->Clear();
	adosp->Parameters->CreateParameter("@stgid",ftInteger ,pdInput,sizeof(int), &stgid);
	adosp->Parameters->CreateParameter("@localid",ftInteger ,pdInput,sizeof(int), &value);
	adosp->ExecProc();      */

}
//---------------------------------------------------------------------------

void __fastcall Tfrmcheckstock::dgcheckCellClick(TColumn *Column)
{
	int tag;
	tag = lbsearch->Tag ;
	if (aqueryupdate->State == dsInactive ) {
		return;
	}
	edtnumber->Text = aqueryupdate->FieldByName("shouldamount")->AsAnsiString ;
	edsamount->Text = aqueryupdate->FieldByName("damagenum")->AsAnsiString ;
	edbk->Text = aqueryupdate->FieldByName("bk")->AsAnsiString ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcheckstock::BtnHorizontalTileClick(TObject *Sender)
{
	AnsiString sql;
	int localid;
	localid =   (int )cblocal->Items->Objects[cblocal->ItemIndex];
	localid = 0;//////////
	sql = "select rank() over(order by stk_bookinfo.id) as xuhao,BS_BookCatalog.ID,BS_BookCatalog.Name as bookname,BS_BookCatalog.Barcode,"
			" BS_BookCatalog.UserDefCode,BS_BookCatalog.ISBN,STK_BookInfo.ID as STK_BookinfoID, "
			" STK_BookInfo.Amount as actualamount,STK_BookstackInfo.Name as LocalName,BS_BookCatalog.Price ,BS_PressInfo.AbbreviatedName "
			" from STK_BookInfo JOIN BS_BookCatalog ON STK_BookInfo.BkcatalogID = BS_BookCatalog.ID "
			" JOIN STK_BookstackInfo ON STK_BookInfo.BkstackID = STK_BookstackInfo.ID "
		  //	" JOIN CUST_CustomerInfo ON STK_BookInfo.SupplierID = CUST_CustomerInfo.ID "
			" LEFT JOIN BS_BookType ON BS_BookCatalog.smallBookTypeID = BS_BookType.ID "
			" LEFT JOIN BS_PressInfo ON BS_BookCatalog.PressID = BS_PressInfo.ID "
			" where STK_BookInfo.amount <> 0 and STK_BookInfo.bkstackid = " + IntToStr((int )cblocal->Items->Objects[cblocal->ItemIndex]) + " and STK_BookInfo.id not in "
			" (select STK_BookInfoID from STK_StockInventories join BS_PandianCount "
			" on STK_StockInventories.NoteCode = BS_PandianCount.CodeStr where BS_PandianCount.state = 0 and  "
			" BS_PandianCount.stgid = " + IntToStr(m_storageID) + ") ";
	aquerynotcheckbook->Close();
	aquerynotcheckbook->SQL->Clear();
	aquerynotcheckbook->SQL->Add(sql);
	aquerynotcheckbook->Open();
	int icount;
	//show Not checkbook
	TfrmNotCheckBook *frm = new TfrmNotCheckBook(Application,aquerynotcheckbook);
	if(mrOk == frm->ShowModal())
	{
		AnsiString sql;
		sql = "insert into STK_StockInventories(bkcatalogid,BarCode,ISBN,bookname, "
			" AbbreviatedName,actualamount,STK_bookInfoID,NoteCode,shouldamount,Balance) "
			" select BS_BookCatalog.id,BS_BookCatalog.barcode,BS_BookCatalog.isbn,BS_BookCatalog.name, "
			" BS_PressInfo.AbbreviatedName,STK_BookInfo.amount,STK_BookInfo.id,'" + Code + "',0,0-STK_BookInfo.amount "
			" from STK_BookInfo left join BS_BookCatalog on STK_BookInfo.bkcatalogid = BS_BookCatalog.id "
		   //	" left join CUST_CustomerInfo on STK_BookInfo.supplierid = CUST_CustomerInfo.id "
			" left join BS_PressInfo on BS_BookCatalog.pressid = BS_PressInfo.id "
			" where STK_BookInfo.bkstackid = " + IntToStr((int )cblocal->Items->Objects[cblocal->ItemIndex]) + " and STK_BookInfo.id not in "
			" (select STK_BookInfoID from STK_StockInventories join BS_PandianCount "
			" on STK_StockInventories.NoteCode = BS_PandianCount.CodeStr where BS_PandianCount.state = 0 and "
			" BS_PandianCount.stgid = " + IntToStr(m_storageID) + ")";
		TADOQuery *aq = new TADOQuery(this);
		aq->Connection = fcon;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->ExecSQL();
		delete aq;
		weipanshu = true;
	}
	delete frm;
	aqueryupdate->Active = false;
	aqueryupdate->Active = true;
	((TFloatField *)aqueryupdate->FieldByName("Discount"))->DisplayFormat = "0.00%";
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcheckstock::BtnViewIconsClick(TObject *Sender)
{
	if (editnum->Text == "") {
		ShowMsg(Handle ,"�����̵�����û���޸Ŀ�棬���޸Ŀ�������̵㣡",0);
		return;
	}
	int value;
	AnsiString Note;											   //������λ
	String sql;
	sql = "select * from STK_StockInventories where states = 0 and NoteCode = '" + Code + "'";
    aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Open();
	if (aquery->RecordCount > 0) {
		ShowMsg(Handle ,"�����̵�����û���޸Ŀ�棬���޸Ŀ�������̵㣡",0);
		return;
	}




	Note = "������̵���������Խ���������ҵ��������Ƿ񵼳��̵����ݣ�" ;
        Note = "�Ƿ���������̵㣿";
	if (ShowMsg(Handle ,Note.c_str(),1)== 1) {

            value = (int )cblocal->Items->Objects[cblocal->ItemIndex];
            adosp->ProcedureName = "UnLockLocal";
            adosp->Parameters->Clear();
            adosp->Parameters->CreateParameter("@stgid",ftInteger ,pdInput,sizeof(int), &m_storageID);
            adosp->Parameters->CreateParameter("@localid",ftInteger ,pdInput,sizeof(int), &value);
            adosp->ExecProc();

                                                                     //���ĸò�����Ա�� STK_CheckStockinfo���е�״̬
			sql  =  "update STK_CheckStockinfo set state = 0,checkdate = getdate() where checkstocknum = '"+ Code +"' and employ  = "+ IntToStr(checkli.userID) +"";

			aquery->Close();
			aquery->SQL->Clear();
			aquery->SQL->Add(sql);
			aquery->ExecSQL();
			  //���������̵����
			   sql  =  "update STK_StockInventories set states = 1  where notecode='"+ Code +"'";

			aquery->Close();
			aquery->SQL->Clear();
			aquery->SQL->Add(sql);
			aquery->ExecSQL();






             Note = "�Ƿ񽫵����̵����ݣ�";
            if (ShowMsg(Handle ,Note.c_str(),1)== 1) {
                 BtnExport->Click();
            }else
            {
               Close();
            }
	}


	/*if (!weipanshu) {
		Note = "�Ƿ�δ�������㣿" ;
		if (MessageBox(0,Note.c_str(),"����̵�",MB_ICONQUESTION|MB_OKCANCEL)== 1) {
			BtnHorizontalTile->Click();
			weipanshu = true;
		}
		else
		{
			Note = "������̵���������Խ���������ҵ��������Ƿ񵼳��̵����ݣ�" ;
			if (MessageBox(0,Note.c_str(),"����̵�",MB_ICONQUESTION|MB_OKCANCEL)== 1) {
				BtnExport->Click();
			}
			Close();
		}
	}
	else
	{
		Note = "������̵���������Խ���������ҵ��������Ƿ񵼳��̵����ݣ�" ;
		if (MessageBox(0,Note.c_str(),"����̵�",MB_ICONQUESTION|MB_OKCANCEL)== 1) {
			BtnExport->Click();
		}
		Close();
	} */
}
//---------------------------------------------------------------------------


void __fastcall Tfrmcheckstock::FormClose(TObject *Sender, TCloseAction &Action)
{
   Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcheckstock::BtnExitClick(TObject *Sender)
{
   Close();
}
//---------------------------------------------------------------------------


void __fastcall Tfrmcheckstock::BtnPrintClick(TObject *Sender)
{
	/* Tfrmstoragecheck *frm = new Tfrmstoragecheck(this,);
	frm->RvSystem1->SystemSetups >>ssAllowSetup;
	frm->RvSystem1->SystemSetups >>ssAllowDestPreview;
	frm->RvSystem1->SystemSetups >>ssAllowDestPrinter;
	frm->RvSystem1->SystemSetups >>ssAllowPrinterSetup;
	frm->RvSystem1->SystemSetups >>ssAllowDestFile;
	frm->RvSystem1->DefaultDest   = rdPrinter ;
	frm->RvSystem1->SystemSetups<<ssAllowDestPrinter;     */


}
//---------------------------------------------------------------------------

void __fastcall Tfrmcheckstock::BtnClearClick(TObject *Sender)
{
	String sql;
	String Datestr;
	TADOQuery *aqa = new TADOQuery(this);

	sql = "select Convert(varchar(50),checkdate,111) as d from STK_CheckStockinfo ";
	sql = sql  + " where checkstocknum = '" + Code + "'";
	aqa->Close();
	aqa->SQL->Clear();
	aqa->SQL->Add(sql);
	aqa->Open();
	Datestr = aqa->FieldByName("d")->AsAnsiString ;
    delete aqa;
       //	RvSystem1->SystemSetups >>ssAllowSetup;
       //	RvSystem1->SystemSetups >>ssAllowDestPreview;
       //	RvSystem1->SystemSetups >>ssAllowDestPrinter;
       //	RvSystem1->SystemSetups >>ssAllowPrinterSetup;
       //	RvSystem1->SystemSetups >>ssAllowDestFile;
	RvSystem1->DefaultDest  = rdPreview ;
	RvSystem1->SystemSetups<<ssAllowDestPreview;
	RvProject1->ProjectFile = "Project1.rav";
	RvProject1->Open();
   //	RvProject1->SetParam("danhao",Code);
	//RvProject1->SetParam("storage",edtstore->Text);
   //	RvProject1->SetParam("local",cblocal->Text);
   //	RvProject1->SetParam("bk",edtbk->Text);
   //	RvProject1->SetParam("user",edtemploy->Text);
   //	RvProject1->SetParam("date",Datestr);

	RvProject1->Execute();
	RvProject1->Close();

  /*	Tfrmprint1 *frm = new Tfrmprint1(this,connect);
	::ShowWindow(frm->Handle, SW_HIDE);
	 frm->Activeaq(Code);
 // ShowMessage(frm->aqcheckreport->FieldByName("suppliername")->AsAnsiString);

		paramcode = "'" + Code + "'";
		//frm->RvDataSetConnection2->DataSet =
		// frm->RvDataSetConnection2->DoOpen();
	   //	 frm->aqcheckreport->DataSource->DataSet  =  dgcheck->DataSource->DataSet ;




	  //	frm->stockprint->SetParam("danhao",Code);
	   //	frm->stockprint->SetParam("storage",edtstore->Text);
	   //	frm->stockprint->SetParam("local",cblocal->Text);
	  //	frm->stockprint->SetParam("bk",edtbk->Text);
	  //	frm->stockprint->SetParam("user",edtemploy->Text);
	  //	frm->RvDataSetConnection1->DataSet = frm->aqcheckreport;

	  //	ShowMessage(frm->RvDataSetConnection1->DataSet->FieldByName("suppliername")->AsAnsiString) ;
		 frm->Print(0);
   delete frm;   */
}
bool Tfrmcheckstock::DbgridToExcel(TDBGrid* dbg)
{
 	AnsiString temptext,path;
	int k = dbg->DataSource ->DataSet ->RecordCount ,n=0;

	savedlg->FileName = "ʵ���̵�-" + cblocal->Text ;
	if (savedlg->Execute())
	{
		String DBPath,Name;
		DBPath = Sysutils::ExtractFilePath(savedlg->FileName .c_str()  );
		Name = Sysutils::ExtractFileName(savedlg->FileName .c_str() );
		DBPath = DBPath + Name + ".csv";
		path =  DBPath;
	}
	else
	{
    	return false;
	}
	int  iFileHandle;
	int   iFileLength;
	if(FileExists(path))
	   //iFileHandle = FileOpen(path.c_str() ,fmOpenReadWrite);
	   if (DeleteFileA(path))
			iFileHandle = FileCreate(path.c_str());
	   else
			return false;
	else
		iFileHandle = FileCreate(path.c_str());

	temptext = ",,,ʵ���̵�";
	iFileLength   =   FileSeek(iFileHandle,0,2);
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	temptext = "\n";
	temptext = temptext + "�̵��,'" + labtitle->Caption + ",��λ," + cblocal->Text + ",��ע," + membk->Text ;
	iFileLength   =   FileSeek(iFileHandle,0,2);
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	temptext = "\n\n";

	int t1= 0;
	for(int q=0;q<dbg->FieldCount-1 ;++q)
	{
		if (dbg->Columns->Items[q]->Visible == true) {
			t1++;
			//temptext = "'"+ dbg->Columns ->Items [q]->Title ->Caption;
			//v.OlePropertyGet("Cells",1+n,(t1)).OlePropertySet("Value",temptext .c_str() );
			temptext = temptext + dbg->Columns ->Items [q]->Title ->Caption + ",";
		}
	}
	iFileLength   =   FileSeek(iFileHandle,0,2);
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());


	int t2 = dbg->DataSource ->DataSet ->RecordCount ;
	aqueryupdate->DisableControls();
	dbg->DataSource ->DataSet ->First();
	for(int   i=2+n;i<=t2+1+n ;i++)
	{
		t1=0;
		temptext = "\n";
		for(int j=1;j<dbg->Columns ->Count  ;j++)
		{
			if (dbg->Columns->Items[j-1]->Visible == true) {
				if (dbg->Columns ->Items [j-1]->FieldName == "ISBN") {
					t1++;
					//temptext = "'"+ dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					//v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
					temptext = temptext + "'" + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
				}
				else if (dbg->Columns ->Items [j-1]->FieldName == "BookName") {
					t1++;
					AnsiString bookname;
					int len;
					bookname = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					bookname = StringReplace(bookname , ",",".",TReplaceFlags()<<rfReplaceAll);
					//temptext = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					//v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
					temptext = temptext + bookname + ",";
				}
				else if (dbg->Columns ->Items [j-1]->FieldName == "Discount") {
					t1++;
					//temptext = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					//v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
					temptext = temptext + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + "%,";
				}
				else
				{
					t1++;
					//temptext = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					//v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
					temptext = temptext + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
				}
			}
		}
		iFileLength   =   FileSeek(iFileHandle,0,2);
		FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
		dbg->DataSource ->DataSet ->Next() ;
	}
	aqueryupdate->EnableControls();
	int h =  aqueryupdate->RecordCount + 4;
    temptext = "\n";
	temptext = temptext + "�ϼ�,,,,,,=SUM(G5:G" + IntToStr(h) + "),=SUM(H5:H" + IntToStr(h) + "),=SUM(I5:I" + IntToStr(h) + "),=SUM(J5:J" + IntToStr(h) + "),=SUM(K5:K" + IntToStr(h) + "),=SUM(L5:L" + IntToStr(h) + ")";
	iFileLength   =   FileSeek(iFileHandle,0,2);
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	FileClose(iFileHandle);


        ShowMsg(Handle ,"������ϣ�",3);
	return false;
}
//---------------------------------------------------------------------------


void __fastcall Tfrmcheckstock::BtnExportClick(TObject *Sender)
{
	if (aqueryupdate->Active && aqueryupdate ->RecordCount > 0) {
		DbgridToExcel(dgcheck);
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcheckstock::edtnumberExit(TObject *Sender)
{
  if (edtnumber->Text == "") {
      edtnumber->Text = "0";
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcheckstock::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcheckstock::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F1 && Btninit->Enabled && Btninit->Visible ) {     //�̵��ʼ��
		Btninit->Click();
	}
	if (Key == VK_F2 && BtnProperties->Enabled && BtnProperties->Visible) {     //��ʼ�̵�
		BtnProperties->Click();
	}
	if (Key == VK_F3 && BtnViewList->Enabled && BtnViewList->Visible) {     //�̵��޸Ŀ��
		BtnViewList->Click();
	}
	if (Key == VK_F4 && BtnViewIcons->Enabled && BtnViewIcons->Visible) {     //�����̵�
		BtnViewIcons->Click();
	}
	if (Key == VK_F5 && BtnHorizontalTile->Enabled && BtnHorizontalTile->Visible) {     //δ����
		BtnHorizontalTile->Click();
	}
	if (Key == VK_F6 && BtnChangeOptions->Enabled && BtnChangeOptions->Visible) {     //���������̵�
		BtnChangeOptions->Click();
	}
	if (Key == VK_F8 && BtnExport->Enabled && BtnExport->Visible) {     //����
		BtnExport->Click();
	}
	if (Key == VK_F11 && BtnClear->Enabled && BtnClear->Visible) {     //Ԥ��
		BtnClear->Click();
	}
	if (Key == VK_F10 && BtnPrint->Enabled && BtnPrint->Visible) {     //��ӡ
		BtnPrint->Click();
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

void __fastcall Tfrmcheckstock::edsamountKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		//float Discountprice = 0,  Fixedprice = 0
		//Fixedprice = (aqueryupdate->FieldByName("Price")->AsFloat)*StrToInt(edtnumber->Text);
		//Discountprice = Fixedprice*(aqueryupdate->FieldByName("Discount")->AsFloat)/100;
		if (edsamount->Text == "") {
        	return;
		}
		if (aqueryupdate->IsEmpty() ) {
			return;
		}
		aqueryupdate->Edit();
		aqueryupdate->FieldByName("damagenum")->AsInteger  = StrToInt(edsamount->Text);
		aqueryupdate->FieldByName("balance")->AsInteger =aqueryupdate->FieldByName("shouldamount")->AsInteger - aqueryupdate->FieldByName("actualamount")->AsInteger-aqueryupdate->FieldByName("damagenum")->AsInteger;
		aqueryupdate->UpdateBatch(arAll);
		aqueryupdate->Active = false;
		aqueryupdate->Active = true;
		((TFloatField *)aqueryupdate->FieldByName("Discount"))->DisplayFormat = "0.00%";
		aqueryupdate->Last();
		edsamount->Text = "0";
		aqheader->Active = false;
		aqheader->Active = true;
		edbk->SetFocus();
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcheckstock::edbkKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		if (aqueryupdate->IsEmpty() ) {
			return;
		}
		aqueryupdate->Edit();
		aqueryupdate->FieldByName("bk")->AsString  = edbk->Text;
		aqueryupdate->UpdateBatch(arAll);

        edbk->Text = "";
		aqueryupdate->Last();
		aqheader->Active = false;
		aqheader->Active = true;
		edtcheckinfo->SetFocus();
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcheckstock::membkExit(TObject *Sender)
{
	AnsiString sql ;
	if (Code != "") {
		sql  =  "update STK_CheckStockinfo set bk = '" + membk->Text + "' where checkstocknum = '"+ Code +"' and employ  = "+ IntToStr(checkli.userID) +"";
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->ExecSQL();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcheckstock::N5Click(TObject *Sender)
{
	CatalogSearchMode = 4 ;
	lbsearch->Caption = "����";
	lbsearch->Tag = 4;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcheckstock::BtnPropertiesClick(TObject *Sender)
{
	if (count == 0) {

                ShowMsg(Handle ,"��û�����̵��ʼ����",3);
		return;
	}
	int i ;
	int value;
	int stgid;
	String Note,sql;
	String sqlstr;
	int countrecode;
	Btninit->Enabled = false;
	//Note = cblocal->Text + "��λ�ѱ�����,�κζԸÿ�λ�Ĳ���������ֹ��";

	BtnViewIcons->Enabled = true ;
	BtnViewList->Enabled = true;
	if (guanliyuan == 1) {
		BtnHorizontalTile->Enabled = true;
	}
	edtcheckinfo->Enabled = true;
	edtnumber->Enabled = true;

	cblocal->Enabled =  false;

												 //������λ
	value =   (int )cblocal->Items->Objects[cblocal->ItemIndex];
	adosp->ProcedureName = "LockLocal";
	adosp->Parameters->Clear();
	adosp->Parameters->CreateParameter("@stgid",ftInteger ,pdInput,sizeof(int), &m_storageID);
	adosp->Parameters->CreateParameter("@localid",ftInteger ,pdInput,sizeof(int), &value);
	adosp->ExecProc();

	adosp->ProcedureName = "LocalCount";    //����ܼ�¼��
	adosp->Parameters->Clear();
	adosp->Parameters->CreateParameter("@localiD",ftInteger ,pdInput,sizeof(int), &value);
	adosp->Parameters->CreateParameter("@count",ftInteger  ,pdOutput ,sizeof(int), &countrecode);
	adosp->ExecProc();

	//lbcount->Caption = "��ǰ��λ���� " + adosp->Parameters->ParamByName("@count")->Value+" Ʒ��";

	if (Code =="") {   //�Ƿ���û���̵���ɵĵ���
					  //�µ��̵㿪ʼ
		Code = NoteCode::BuildCode(aquery,GetDBTime(aquery),m_storageID,"STK_CheckStockinfo","checkstockNum");
		sql = "insert into STK_CheckStockinfo (checkstockNum ,checkstore,checkstocklocal,checkdate,bk,employ,state)"
		" values('" + Code + "'," + IntToStr(m_storageID) + "," + IntToStr((int )cblocal->Items->Objects[cblocal->ItemIndex])
		+ ",'" + DateTimeToStr(Now())+"','" + membk->Text.Trim()+ "'," + checkli.userID +",1)";

		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->ExecSQL();
		aqueryupdate->Parameters->ParamByName("stocknum")->Value = Code;
		aqueryupdate->Active = true;
		((TFloatField *)aqueryupdate->FieldByName("Discount"))->DisplayFormat = "0.00%";


		sql = "select ID,checkstockNum,totalamount,Fixedprice,Discountprice from STK_CheckStockinfo where checkstockNum = '" + Code + "'";
		aqheader->Close();
		aqheader->SQL->Clear();
		aqheader->SQL->Add(sql);
		aqheader->Open();

		editnum->Text = Code;
	}
	editstate->Text = "�����̵�";
	BtnProperties->Enabled = false;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	sql = " insert into BS_PandianCount(state,pancount,CodeStr,stgid) values (0," + IntToStr(count) + ",'" + Code + "'," + IntToStr(m_storageID) +")";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	delete aq;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcheckstock::BtninitClick(TObject *Sender)
{
	if (count > 0) {

                 ShowMsg(Handle ,"�̵��Ѿ���ʼ������Ҫ���³�ʼ���̵����Ƚ��������̵㣡",3);
		return;
	}
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	AnsiString sql;
	sql = "select max(pancount) + 1 as count from BS_PandianCount where stgid = " + IntToStr(m_storageID) ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();

	if (aq->FieldByName("count")->AsAnsiString == "" ) {
		count = 1;
	}
	else
	{
		count = aq->FieldByName("count")->AsInteger ;
	}
	sql = " insert into BS_PandianCount(state,pancount,stgid) values (0," + IntToStr(count) + "," + IntToStr(m_storageID) + ")";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	delete aq;
	BtnProperties->Enabled = true;
	BtnChangeOptions->Enabled = true;
	Btninit->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcheckstock::BtnChangeOptionsClick(TObject *Sender)
{
	if (count == 0) {
		ShowMsg(Handle ,"��ǰ���̵���У�",3);
		return;
	}
	AnsiString sql;
	sql = "select STK_CheckStockinfo.* from STK_CheckStockinfo join BS_PandianCount "
			 " on STK_CheckStockinfo.checkstockNum = BS_PandianCount.CodeStr "
			 " and STK_CheckStockinfo.state = 1 and BS_PandianCount.stgid = " +  IntToStr(m_storageID);
	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Open();
	if (aquery->RecordCount > 0) {
		ShowMsg(Handle ,"�����̵㵥δ���������Ƚ����̵㵥��",3);
		return;
	}
	if (ShowMsg(Handle ,"ȷ��Ҫ���������̵㣿",1)!= 1) {
		return;
	}

	if (!weipanshu) {
		if (ShowMsg(Handle ,"�Ƿ�δ�������㣿",1)== 1) {
			BtnHorizontalTile->Click();
			weipanshu = true;
		}
		else
		{
        	EndPandian();
		}
	}
	else
	{
		EndPandian();
	}
}
//---------------------------------------------------------------------------
void  Tfrmcheckstock::EndPandian()
{
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	AnsiString sql;
	sql = " update STK_CheckStockinfo set state = 0 where checkstocknum in (select CodeStr from BS_PandianCount where state = 0 and stgid = " + IntToStr(m_storageID) + ") ";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	sql = " update BS_PandianCount set state = 1 where state = 0 and stgid = " + IntToStr(m_storageID) ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	delete aq;
	Close();
}
//---------------------------------------------------------------------------


void __fastcall Tfrmcheckstock::RzToolButton2Click(TObject *Sender)
{
//�̵�������
String path;
String sql;
AnsiString temptext;

   if (savedlg->Execute()) {
        	String DBPath,Name;
		DBPath = Sysutils::ExtractFilePath(savedlg->FileName .c_str()  );
		Name = Sysutils::ExtractFileName(savedlg->FileName .c_str() );
		DBPath = DBPath + Name + ".csv";
		path =  DBPath;
   }else
	{
    	return ;
	}
	int  iFileHandle;
	int   iFileLength;
	if(FileExists(path))
	  // iFileHandle = FileOpen(path.c_str() ,fmOpenReadWrite);
	   if (DeleteFileA(path))
			iFileHandle = FileCreate(path.c_str());
	   else
			return ;
        else
		iFileHandle = FileCreate(path.c_str());
        //��ʼд����
        temptext="ISBN,����,����,����,����,������";
        	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
     sql = "select * from UV_PanDianQiPort a where a.stk_bookinfoid =(select min(stk_bookinfoid) from UV_PanDianQiPort where barcode = a.barcode and bookname=a.bookname and ";
     sql = sql + " abbreviatedname=a.abbreviatedname and price = a.price and stgid = "+IntToStr(m_storageID)+")and stgid = "+IntToStr(m_storageID);

     aquery->Close();
     aquery->SQL->Clear();
     aquery->SQL->Add(sql);
     aquery->Open();

     while(!aquery->Eof)
     {             temptext="\n";
                temptext=temptext+ aquery->FieldByName("ISBN")->AsAnsiString.Trim()  +","
                   +   aquery->FieldByName("stk_bookinfoid")->AsAnsiString  +","
                +   StringReplace(aquery->FieldByName("bookname")->AsAnsiString.Trim() , ",",".",TReplaceFlags()<<rfReplaceAll)  +","
                +   aquery->FieldByName("author")->AsAnsiString.Trim()   +","
                +   aquery->FieldByName("price")->AsAnsiString  +","
                +   aquery->FieldByName("abbreviatedname")->AsAnsiString.Trim() ;
                iFileLength   =   FileSeek(iFileHandle,0,2);
               	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
        aquery->Next();
     }

 FileClose(iFileHandle);
 ShowMsg(Handle ,"�������",3);
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcheckstock::RzToolButton1Click(TObject *Sender)
{
//����
      AnsiString filepath;
      if (opfile->Execute()) {
            filepath = opfile->FileName;

      } else return;



      String str = " Provider=Microsoft.Jet.OLEDB.4.0;Extended Properties=Excel 8.0;Persist Security Info=false;Data Source=";

        xlsconnect->ConnectionString =  str+filepath ;
        try
        {
	      	 xlsconnect->Connected = true;
       	}
     	catch(...)
     	{
      		ShowMsg(this->Handle,"����Դ���ô���",3);

      		return;
      	}
        try
        {
        TStringList * tablelist;
        tablelist = new TStringList();
        xlsconnect->GetTableNames(tablelist,false);
        aqinput->Connection = xlsconnect;
        AnsiString excelsql;
        excelsql = "select * from ["+tablelist->Strings[0]+"]";
        aqinput->Active = false;
        aqinput->SQL->Clear();
        aqinput->SQL ->Add(excelsql);
        aqinput->Open();


         //����֮ǰ���������ŵ���������

         aqinsertkuchen->Close();
        aqinsertkuchen->SQL->Clear();
        aqinsertkuchen->SQL->Add("delete STK_StockInventories where notecode='"+editnum->Text+"'");
        aqinsertkuchen->ExecSQL();


        aqinsertkuchen->Close();
        aqinsertkuchen->SQL->Clear();
        aqinsertkuchen->SQL->Add("select * from dbo.STK_StockInventories where notecode='"+editnum->Text+"'");
        aqinsertkuchen->Open();





        while(!aqinput->Eof)
        {

          // aqinsertkuchen->Edit();
          if (aqinput->FieldByName("����")->AsAnsiString!="") {


           aqinsertkuchen->Append();

           aqinsertkuchen->FieldByName("stk_bookinfoid")->AsAnsiString= aqinput->FieldByName("����")->AsAnsiString;
           aqinsertkuchen->FieldByName("ShouldAmount")->AsAnsiString  = aqinput->FieldByName("�̵���")->AsAnsiString;
           aqinsertkuchen->FieldByName("notecode")->AsAnsiString  =editnum->Text;
           aqinsertkuchen->Post();

          }
          aqinput->Next();
        }

        AnsiString sql="";
        sql = "exec BS_BanDianDaoRu '"+editnum->Text+"','"+cblocal->Text+"'";

        aqinsertkuchen->Close();
        aqinsertkuchen->SQL->Clear();
        aqinsertkuchen->SQL->Add(sql);
        aqinsertkuchen->ExecSQL();

        aqueryupdate->Active = false;
        aqueryupdate->Parameters->ParamByName("stocknum")->Value = editnum->Text;
        aqueryupdate->Active = true;

        aqinput->Close();
        ShowMsg(this->Handle,"������ɣ�",3);
        xlsconnect->Connected = false;
        }
        catch(...)
        {

            ShowMsg(this->Handle,"����ʧ��,���˳����ԣ�",3);
            xlsconnect->Connected = false;

        }








}
//---------------------------------------------------------------------------

