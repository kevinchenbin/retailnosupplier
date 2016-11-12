//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "bookQuery.h"
#include "MemberOrder.h"
#include "PwdForm.h"
#include "global.h"
#include "SelectCatalogForm.h"
#include "NewBookinput1.h"
#include "..\membermanager\MemberForm.h"
#include "SetNotesForm.h"
#include "Unitmutilprint.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzDBEdit"
#pragma link "RzDBGrid"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzPanel"
#pragma link "RzRadChk"
#pragma link "frxClass"
#pragma link "frxDBSet"
#pragma resource "*.dfm"
Tfrmmemberorder *frmmemberorder;
//---------------------------------------------------------------------------
__fastcall Tfrmmemberorder::Tfrmmemberorder(TComponent* Owner)
	: TForm(Owner)
{
}
void Tfrmmemberorder::init(TADOConnection *cn,int auserid,int astgid)
{
    fcn=cn;
    UserID=auserid;
    StgID =astgid;
    adoaqnote->Connection = fcn;
    aqheader->Connection = fcn;
    aq->Connection = fcn;

     MemberID=-1;
    m_catalogSearchMode = 1;
    modyoradd= true;
    olderordermondy=0;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmmemberorder::edcardKeyPress(TObject *Sender, wchar_t &Key)
{
//
  //判断是否是手机号
  if (Key == '\r')
	{
               AnsiString sn,cardNum;
                sn = edcard->Text.Trim();
                bool cardyesornot=true;//是会员卡号或手机号
           try {     if (sn.Length()!=11) {
                    //会员卡号
                     lbl2->Caption="卡号[F4]";
                   // cardNum=dsetNtHeader->FieldByName("CardSN")->AsAnsiString;
                }else if (sn.Length()==11) {
                       //手机号
                     //  cardNum = dsetNtHeader->FieldByName("mobile")->AsAnsiString;
                       cardyesornot = false;
                       lbl2->Caption="手机号[F4]";
                }else
                {
                    	ShowMsg(this->Handle,"输入的会员卡号或手机号无效，请核对后重输！",3);
                         return;
                }

	       //	if (cardNum!=sn) {
			AnsiString sql;
                        if (cardyesornot) {
                          	sql = "select ID,name,PassWord,Available,datediff(d,getdate(),youxiaodate) as t ,balance,TotalConsumption,memberdot,cardcast,t.type,CONVERT(varchar(10), GETDATE(), 120) as youxiaoqi from CUST_MemberInfo c ";
                                sql  =sql + " left join CUST_MemberType t on c.membertype=t.idtype where cardsn = '" + edcard->Text + "'" ;

                        }else  {	sql = "select ID,name,PassWord,Available,datediff(d,getdate(),youxiaodate) as t ,balance,TotalConsumption,memberdot,cardcast,t.type,CONVERT(varchar(10), GETDATE(), 120) as youxiaoqi from CUST_MemberInfo c ";
                                sql  =sql + "  left join CUST_MemberType t on c.membertype=t.idtype where mobile = '" + sn + "'" ;
                        }
                        TADOQuery *aq = new TADOQuery(Application);
                        aq->Connection = fcn;
                       	aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();

                   	if (aq->RecordCount > 0) {
				if (!aq->FieldByName("Available")->AsBoolean ) {
					ShowMsg(this->Handle,"会员卡已无效！",3);
					return;
				}
				if (aq->FieldByName("t")->AsInteger < 0 ) {
					sql = "update CUST_MemberInfo set Available = 0 where ID = " + aq->FieldByName("ID")->AsAnsiString ;
					aq->Close();
					aq->SQL->Clear();
					aq->SQL->Add(sql);
					aq->ExecSQL();
					ShowMsg(Handle ,"会员卡已过期，请重新核发！",3);
					return;
				}

				if (aq->FieldByName("PassWord")->AsAnsiString != "" ) {
					TfrmPwd *frm = new TfrmPwd(Application);
					if (frm->ShowModal() == mrOk ) {
						if (frm->GetPassword()!= aq->FieldByName("PassWord")->AsAnsiString) {
                                                        ShowMsg(this->Handle,"密码错误",3);
							return;
						}
					}
					else
					{
						return;
					}
				}
				MemberID = aq->FieldByName("id")->AsInteger ;

                                edname->Text = aq->FieldByName("name")->AsAnsiString ;
                                edtype->Text=  aq->FieldByName("type")->AsAnsiString ;
                                edyue->Text=  aq->FieldByName("balance")->AsAnsiString ;
                                edjifen->Text=  aq->FieldByName("memberdot")->AsAnsiString ;
                                edyouxiaodate->Text=  aq->FieldByName("youxiaoqi")->AsAnsiString ;
                                edTotalConsumption->Text = aq->FieldByName("TotalConsumption")->AsAnsiString;
                                delete aq;
                                ///生成会员卡后

                                    edtCatalog->SetFocus();


                                }else {

                                MemberID = -1;
                                delete aq;
                                }

				} catch (...) {
				}
             //   }
                  }
}
//---------------------------------------------------------------------------
void __fastcall Tfrmmemberorder::tlbtn1Click(TObject *Sender)
{
//保存
AnsiString sql,sql1;
if (edcard->Text =="") {
ShowMsg(Handle ,"请先输入会员卡号！",3);
    return;
}
  if (MemberID!=-1) {
     if (modyoradd) {   //增加
           sql1 = "exec InsertNewMemberOrder "+IntToStr(StgID)+","+IntToStr(UserID)+","+IntToStr(MemberID)+","+FloatToStr(numorder->Value)+",'"+membk->Text+"',-1";

          }else   //修改模式
          {
          sql1 = "exec InsertNewMemberOrder "+IntToStr(StgID)+","+IntToStr(UserID)+","+IntToStr(MemberID)+","+FloatToStr(numorder->Value-olderordermondy)+",'"+membk->Text+"',"+aqheader->FieldByName("id")->AsAnsiString ;
          olderordermondy =   numorder->Value;
          }

  }else {
            ShowMsg(Handle ,"请选选择会员！",3);
            return ;
  }
      try
      {

        aqheader->Close();
        aqheader->SQL->Clear();
        aqheader->SQL->Add(sql1);
        aqheader->Open();
        RefreshDetail();
        ShowMsg(Handle ,"保存成功！",3);
        tlbtn1->Enabled = false;
        buttonstate(2);

        edtCatalog->SetFocus();
      }catch(...)
      {

       ShowMsg(Handle ,"保存失败！",3);
      }
}

 
//---------------------------------------------------------------------------
void __fastcall Tfrmmemberorder::edtCatalogKeyPress(TObject *Sender, wchar_t &Key)

{
   //
   	if (m_catalogSearchMode == 6) {
		if ((Key < '0' || Key > '9') && (Key != '\b') && (Key != '.') && (Key != '\r') ) {
            Key = NULL;
		}
	}

	if (Key == '\r')
	{
                if (dbedtRetailNtCode->Text.IsEmpty()) {
                       	ShowMsg(Handle ,"请先保存！",3);
                        return ;
                }
		if (edtCatalog->Text == "") {
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
			int results;

			TfrmSelectCatalog* frm = new TfrmSelectCatalog(Application,fcn);
			LandInfo li;
			li.app = Application;
			li.con = fcn;
			li.userID = UserID ;
			li.storageID = StgID ;
			frm->Init(&li);
                        frm->disableduoxuan();
			frm->DoModalType = 4;
			frm->memberorder  = this;
			frm->SetSearchMode(m_catalogSearchMode, edtCatalog->Text);
			frm->SelectAll = false;

                        //期刊处理
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
				if (frm->SelectAll) {
					 for (int i = 0; i < frm->lengthint; i++) {
						// if (chongfutishi(frm->BkcatalogiD[i])) {
							AddNote(1,frm->BkcatalogiD[i]);
					     //	 }
					 }
                     RefreshDetail();
				}else
				{
					frm->GetSelectResult(bkinfoid,catalogID);
					if (catalogID >= 0)
					{
						TLocateOptions   Opts;
						Opts.Clear();
						Opts   <<   loPartialKey;
						String   str   = AnsiString(catalogID);
						if ( !adoaqnote->Locate("bkcatalogid",str,Opts))
						{
						       //	if (chongfutishi(catalogID)) {
								AddNote(0, catalogID);
								dbnbedtAmount->Enabled = true;
								dbnbedtDiscount->Enabled = true;
								edtCatalog->Text  = "";


						      //	}   dbnbedtAmount
						      //	else
						      //	{
						      //		edtCatalog->Text  = "";
						       //		edtCatalog->SetFocus();
						      //	}
						}
						else
						{
                            ShowMsg(Handle ,"有相同记录请核实！",3);
						     //	adoaqnote->SetFocus();
						       //	adoaqnote->SelectedRows->CurrentRowSelected = true;
							edtCatalog->Text  = "";
							dbnbedtAmount->SetFocus();
						}
					}
				}
			}
			else
			{
				if (!frm->findbook) {     //产生新书
					if (aqheader->Active && aqheader->RecordCount >= 1)
					{
						Tfrmnewbook1 *frma = new Tfrmnewbook1(Application,fcn);
						frma->memberorder = this;
						frma->modle = 4;

						frma->editcode->Text = edtCatalog->Text ;
                                                //处理期刊新书
                                                if ( edtCatalog->Text.Trim().Length()>13) {
                                                         frma->cbsaletype->Text = "期刊";
                                                         frma->editqikanmao->Text =edtCatalog->Text.Trim();
                                                         frma->cbsaletypeChange(this);
                                                         PostMessage(frma->editqikanmao->Handle, WM_KEYDOWN,VK_RETURN,0);
                                                }

						if (mbOK == frma->ShowModal())
						{

						}
						delete frma;
                                                dbnbedtAmount->Enabled= true;
                                                dbnbedtDiscount->Enabled = true;
						dbnbedtAmount->SelectAll();
                                                dbnbedtAmount->SetFocus();

					}
				}
			}
			delete frm;
		}
	}
}
void Tfrmmemberorder::ChangeCatalogSearchMode()
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
		edtCatalog->MaxLength = 15;
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
void Tfrmmemberorder::AddNote(int ai,int bkcatalogid)
{

	if (!aqheader->Active) {
		return;
	}
	TLocateOptions Opts;
	Opts.Clear();
	Opts   <<   loPartialKey;
	String   str   = AnsiString(bkcatalogid);
	if ( !adoaqnote->Locate("bkcatalogid",str,Opts))
	{

                adoaqnote->Append();
  		adoaqnote->FieldByName("MemberOrderHeaderId")->AsInteger = aqheader->FieldByName("ID")->AsInteger ;
		adoaqnote->FieldByName("bkcatalogid")->AsInteger = bkcatalogid;
		adoaqnote->UpdateBatch(arCurrent);
                RefreshDetail();
                dbnbedtAmount->Text = "0";
                dbnbedtAmount->SelectAll();
                dbnbedtAmount->SetFocus();

                dbnbedtDiscount->Text = "100";
        }

}

 void Tfrmmemberorder::RefreshDetail()
 {
      	adoaqnote->Active = false;
                AnsiString sql;

        if (aqheader->FieldByName("ID")->AsAnsiString =="") {
            sql = "select TotalAmount,TotalFixedPrice,TotalDiscountedPrice from BS_MemberOrderHeader where id =-1" ;
           adoaqnote->Parameters->ParamByName("HeaderID")->Value =-1;
        }else
        {
	   adoaqnote->Parameters->ParamByName("HeaderID")->Value = aqheader->FieldByName("ID")->AsInteger ;

        }
	adoaqnote->Connection = fcn;
	adoaqnote->Active = true;

        //
           GetTotal();
          //总数量，实洋码洋




       ((TFloatField *)adoaqnote->FieldByName("Discount"))->DisplayFormat = "0.00";
       	((TFloatField *)adoaqnote->FieldByName("fixedprice"))->DisplayFormat = "0.00";
       	((TFloatField *)adoaqnote->FieldByName("discountedprice"))->DisplayFormat = "0.00";
 }
void Tfrmmemberorder::GetTotal()
{       if (aqheader->FieldByName("ID")->AsAnsiString =="") {
             return;
        }
        AnsiString sql = "select TotalAmount,TotalFixedPrice,TotalDiscountedPrice from BS_MemberOrderHeader where id ="+aqheader->FieldByName("ID")->AsAnsiString  ;
        TADOQuery *aqdelete = new TADOQuery(Application);
        aqdelete->Connection = fcn;
        aqdelete->Close();
        aqdelete->SQL->Clear();
        aqdelete->SQL->Add(sql);
        aqdelete->Open();
        Edit1->Text = aqdelete->FieldByName("TotalAmount")->AsAnsiString ;
        Edit2->Text = aqdelete->FieldByName("TotalFixedPrice")->AsAnsiString ;
        Edit3->Text = aqdelete->FieldByName("TotalDiscountedPrice")->AsAnsiString ;
        delete aqdelete;
}
 void Tfrmmemberorder::UpdateNote(int amount,int discount)
 {
      float price;
      price = adoaqnote->FieldByName("price")->AsFloat;

      adoaqnote->Edit();

      adoaqnote->FieldByName("amount")->AsInteger =amount;
       adoaqnote->FieldByName("discount")->AsFloat= discount;
        adoaqnote->FieldByName("fixedprice")->AsFloat= amount*price;
         adoaqnote->FieldByName("discountedprice")->AsFloat= amount*price*0.01*discount;
      adoaqnote->UpdateBatch(arCurrent);
 }
//---------------------------------------------------------------------------

void __fastcall Tfrmmemberorder::lblCatalogMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	if (Button == mbLeft ) {
		TPoint  pt;
		GetCursorPos(&pt);
		pm->Popup(pt.x,pt.y);

	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmmemberorder::N1Click(TObject *Sender)
{

	lblCatalog->Caption = "书号";
	m_catalogSearchMode=1;
	edtCatalog->MaxLength = 15;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmmemberorder::N2Click(TObject *Sender)
{
	lblCatalog->Caption = "自编码";
	m_catalogSearchMode=2;
	edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmmemberorder::N3Click(TObject *Sender)
{
	lblCatalog->Caption = "书名";
	m_catalogSearchMode=3;
	edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmmemberorder::N4Click(TObject *Sender)
{
	lblCatalog->Caption = "定价";
	m_catalogSearchMode=6;
	edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------


void __fastcall Tfrmmemberorder::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmmemberorder::tlbtn7Click(TObject *Sender)
{
  Close();


}
//---------------------------------------------------------------------------

void __fastcall Tfrmmemberorder::FormClose(TObject *Sender, TCloseAction &Action)

{
    Action =  caFree;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmmemberorder::BtnNewClick(TObject *Sender)
{
    edcard->Enabled = true;
    edcard->SetFocus();
    tlbtn1->Enabled = true;
     aqheader->Close();
        aqheader->SQL->Clear();
        aqheader->SQL->Add("select * from BS_MemberOrderHeader where 1=2");
        aqheader->Open();
          edcard->Text = "";
          edname->Text = "";
          edtype->Text = "";
          numorder->Text = "";
          edyue->Text = "";
          edjifen->Text = "";
          edTotalConsumption->Text = "";
          edyouxiaodate->Text = "";
          modyoradd= true;
          numorder->Enabled = true;
          dbnbedtAmount->Text = "0";
             Edit1->Text = "0" ;
        Edit2->Text = "0"  ;
        Edit3->Text = "0"  ;
        RefreshDetail();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmmemberorder::dbnbedtAmountKeyPress(TObject *Sender, wchar_t &Key)

{
      //
      if (Key == '\r')
	{
        if (!adoaqnote->Active) {
             return;
        }
        if (adoaqnote->RecordCount>0) {


        int amountstr;
        double discountstr;
        if ((dbnbedtAmount->Text!="")||(dbnbedtDiscount->Text!="")) {

            amountstr =StrToInt(dbnbedtAmount->Text);
            discountstr= StrToFloat(dbnbedtDiscount->Text);
           UpdateNote(amountstr,StrToFloat(FormatFloat("0.00",discountstr)));

            dbnbedtDiscount->SetFocus();
            GetTotal();
        }
        }


        }

}
//---------------------------------------------------------------------------

void __fastcall Tfrmmemberorder::dbnbedtDiscountKeyPress(TObject *Sender, wchar_t &Key)

{
//
if (Key == '\r')
	{
         if (!adoaqnote->Active) {
             return;
        }
          if (adoaqnote->RecordCount>0) {

          int amountstr;
        double discountstr;
        if ((dbnbedtAmount->Text!="")||(dbnbedtDiscount->Text!="")) {

           amountstr =StrToInt(dbnbedtAmount->Text);
            discountstr= StrToFloat(dbnbedtDiscount->Text);
           UpdateNote(amountstr,StrToFloat(FormatFloat("0.00",discountstr)));

           edtCatalog->SetFocus();
           GetTotal();
        }

        }
        }

}
//---------------------------------------------------------------------------

void __fastcall Tfrmmemberorder::dbgrdNoteCellClick(TColumn *Column)
{
//
if (!adoaqnote->IsEmpty()) {
  dbnbedtAmount->Text = adoaqnote->FieldByName("amount")->AsInteger;
  dbnbedtDiscount->Text = adoaqnote->FieldByName("Discount")->AsFloat;
}

}
//---------------------------------------------------------------------------

void __fastcall Tfrmmemberorder::tlbtn2Click(TObject *Sender)
{
//
if (!adoaqnote->Active) {
    return;
}
if (adoaqnote->IsEmpty()) {
    return;
}
int id;
 if (ShowMsg(Handle,"确定删除吗？",1)==1) {
        id = adoaqnote->FieldByName("id")->AsInteger ;
        AnsiString sql;
        sql = "delete BS_MemberOrderNote where id ="+IntToStr(id);
        TADOQuery *aqdelete = new TADOQuery(Application);
        aqdelete->Connection = fcn;
        aqdelete->Close();
        aqdelete->SQL->Clear();
        aqdelete->SQL->Add(sql);
        aqdelete->ExecSQL();

        delete aqdelete;
        RefreshDetail();
 }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmmemberorder::BtnAttachFilesClick(TObject *Sender)
{
     try
       {
	TfrmMember * frm = new TfrmMember(Application,fcn);
	frm->Show() ;
       }catch(...)
       {

       }
}
//---------------------------------------------------------------------------



void __fastcall Tfrmmemberorder::RzButton1Click(TObject *Sender)
{       String *ID;
        wchar_t c='\r';
    	TfrmMemberCard * frm = new TfrmMemberCard(Application,1,ID ,fcn);
	frm->ShowModal();
        edcard->Text = frm->cardID;
        if ((edcard->Text !="")&&(frm->savebt)) {
         edcard->OnKeyPress(Sender,c);
        }
      delete frm;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmmemberorder::tlbtn3Click(TObject *Sender)
{
	//统一模式
        AnsiString idstr;
        TBookmark bm;
        if (!aqheader->Active ) {
          return;  
        }
        if (!adoaqnote->Active) {
         return;
        }
			if (dbgrdNote->SelectedRows->Count == 0 || dbgrdNote->SelectedRows->Count == 1) {
                 	for (int i = 1; i <= adoaqnote->RecordCount ; i++) {
					dbgrdNote->DataSource->DataSet->RecNo = i;
					dbgrdNote->SelectedRows->CurrentRowSelected = true;
				}
                        }

                        dbgrdNote->DataSource->DataSet->DisableControls();
                        for (int i = 0 ; i < dbgrdNote->SelectedRows->Count ; i++) {

                        dbgrdNote->DataSource->DataSet->Bookmark = dbgrdNote->SelectedRows->Items[i];
                        bm = dbgrdNote->DataSource->DataSet->GetBookmark();
                        dbgrdNote->DataSource->DataSet->GotoBookmark(bm);

                        idstr = idstr+dbgrdNote->DataSource->DataSet->FieldByName("ID")->AsAnsiString+",";

                        }
                        dbgrdNote->DataSource->DataSet->EnableControls();
                        idstr=idstr+"-1";

			TfrmSetNotes* frm = new TfrmSetNotes(this);

			frm->ChangeBsmode(1);
			if (frm->ShowModal() == mrOk)
			{
				int amount = 0;
				float discount = 0;
				bool bsetAmount = frm->GetAmount(amount);
				bool bsetDiscount = frm->GetDiscount(discount);
				if (bsetAmount && bsetDiscount)
				{
					BatchSetNotes(amount, discount, 1,idstr);
				}
				else if (bsetAmount && !bsetDiscount)
				{
					BatchSetNotes(amount, discount, 2,idstr);
				}
				else if (!bsetAmount && bsetDiscount)
				{
                             	BatchSetNotes(amount, discount, 3,idstr);
				}
			}
			delete frm;
}
void Tfrmmemberorder::BatchSetNotes(int amount,float discount,int type,AnsiString strid )
{

  AnsiString sql,wherestr;
  wherestr = " where id in("+strid+")";
  sql = "update BS_MemberOrderNote ";
  if (type==1) {
        sql = sql+" set amount = "+IntToStr(amount)+", discount="+FloatToStr(discount);

  }else if (type==2) {
       sql = sql+" set amount = "+IntToStr(amount);

  }else if (type==3) {
       sql = sql+" set discount = "+FloatToStr(discount);
  }
  sql = sql +wherestr;

   TADOQuery *aqupdate = new TADOQuery(Application);
  aqupdate->Connection = fcn;
  aqupdate->Close();
  aqupdate->SQL->Clear();
  aqupdate->SQL->Add(sql);
  aqupdate->ExecSQL();

  delete aqupdate;
  RefreshDetail();


}
//---------------------------------------------------------------------------


void __fastcall Tfrmmemberorder::tlbtn8Click(TObject *Sender)
{
   //查单

   Tfrmmembersearch *frm = new Tfrmmembersearch(Application,fcn,StgID);

   if (frm->ShowModal()==mrOk) {


    	AnsiString code = frm->GetNoteCode();
		AnsiString sql = frm->Getsql();

                sql = "select BS_MemberOrderHeader.*,c.name as membername,c.id as memberid,c.cardid,c.CardSN,t.type,c.balance,c.memberdot,convert(nvarchar(10),c.youxiaodate,120) as youxiaoqi,c.TotalConsumption from BS_MemberOrderHeader join CUST_MemberInfo c on BS_MemberOrderHeader.memberid = c.id left join CUST_MemberType t on t.idtype=c.membertype where BS_MemberOrderHeader.id in(select id from ("+sql+")as T )";
                aqheader->Close();
                aqheader->SQL->Clear();
                aqheader->SQL->Add(sql);
                aqheader->Open();
                TLocateOptions Opts;
                Opts.Clear();
                Opts << loPartialKey;
                aqheader->Locate("memberntcode", code, Opts);
                edcard->Enabled = false;
                numorder->Enabled = false;
                RzToolButton1->Enabled = true;
                tlbtn1->Enabled = false;

                edtCatalog->SetFocus();
                refreshmember();
                 RefreshDetail();

   }
}
//---------------------------------------------------------------------------
void Tfrmmemberorder::refreshmember()
{

if (!aqheader->Active) {
       return;
}
        MemberID = aqheader->FieldByName("memberid")->AsInteger ;

       edcard->Text = aqheader->FieldByName("cardid")->AsAnsiString ;
        edname->Text = aqheader->FieldByName("membername")->AsAnsiString ;
        edtype->Text=  aqheader->FieldByName("type")->AsAnsiString ;
        edyue->Text=  aqheader->FieldByName("balance")->AsAnsiString ;
        edjifen->Text=  aqheader->FieldByName("memberdot")->AsAnsiString ;
        edyouxiaodate->Text=  aqheader->FieldByName("youxiaoqi")->AsAnsiString ;
        edTotalConsumption->Text = aqheader->FieldByName("TotalConsumption")->AsAnsiString;
        numorder->Value =   aqheader->FieldByName("ordermoney")->AsFloat;
}

void __fastcall Tfrmmemberorder::dbhdClick(TObject *Sender, TNavigateBtn Button)
{
if (aqheader->RecordCount>1) {
    refreshmember();
     RefreshDetail();
}
}
void Tfrmmemberorder::buttonstate(int type)
{
   if (type==1) {   //修改
       RzToolButton1->Enabled = true;
               RzButton1->Enabled = true;
        edcard->Enabled = true;
        numorder->Enabled = true;
           tlbtn1->Enabled = true;
           modyoradd= false;

   }else if (type==2) {  //保存
          tlbtn1->Enabled =false;
          RzToolButton1->Enabled =true;
                  RzButton1->Enabled = false;
        edcard->Enabled = false;
         //numorder->Enabled = false;
   }





}
//---------------------------------------------------------------------------

void __fastcall Tfrmmemberorder::numorderKeyPress(TObject *Sender, wchar_t &Key)
{
  if (Key=='\r') {

         AnsiString sql,sql1;
          if (!aqheader->Active) {
              return;
          }
          if (MemberID==-1) {
             return; 
          }
          sql = "update BS_MemberOrderHeader set ordermoney ="+numorder->Text+" where id ="+aqheader->FieldByName("ID")->AsAnsiString;
           sql1 = "update CUST_MemberInfo set balance = balance + "+FloatToStr(numorder->Value-olderordermondy)+" where id ="+IntToStr(MemberID);


            TADOQuery *aqupdate = new TADOQuery(Application);
            aqupdate->Connection = fcn;
            aqupdate->Close();
            aqupdate->SQL->Clear();
            aqupdate->SQL->Add(sql);
            aqupdate->SQL->Add(sql1);
            aqupdate->ExecSQL();
            olderordermondy =   numorder->Value;
            edtCatalog->SetFocus();
     //  tlbtn1->Click();
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmmemberorder::RzToolButton1Click(TObject *Sender)
{
buttonstate(1);
olderordermondy = numorder->Value;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmmemberorder::BtnPrintClick(TObject *Sender)
{
//打印

if (!adoaqnote->Active) {
    return;
}
        AnsiString sql;
        sql = "select wsprinttitle,wscontact,wstel,wsaddress,wsprintbk from sys_printtitle where stgid = " + IntToStr(StgID);


        TADOQuery *query = new TADOQuery(Application);
        query->Connection = fcn;
        query->Close();
        query->SQL->Clear();
        query->SQL->Add(sql);
        query->Open();

        pxbk = query->FieldByName("wsprintbk")->AsAnsiString ;
        printtitle = query->FieldByName("wsprinttitle")->AsAnsiString ;
        contact = query->FieldByName("wscontact")->AsAnsiString ;
        tel = query->FieldByName("wstel")->AsAnsiString ;
        address = query->FieldByName("wsaddress")->AsAnsiString ;
        riqi = FormatDateTime("yyyy-mm-dd",aqheader->FieldByName("HdTime")->AsDateTime);

        delete query;

         print(1);

    //    AnsiString pxbk,printtitle,contact,tel,address
}
void Tfrmmemberorder::print(int type)
{
       AnsiString ps = ExtractFilePath(Application->ExeName) +"MemberOrder.fr3";
        frxmemberorder->LoadFromFile(ps);
        frxmemberorder->PrepareReport(true);

   if (type==1) {      //打应
      frxmemberorder->PrintOptions->ShowDialog = false;
        frxmemberorder->Print();
   }else
   {
     frxmemberorder->ShowPreparedReport();


   }

}
//---------------------------------------------------------------------------


void __fastcall Tfrmmemberorder::frxmemberorderGetValue(const UnicodeString VarName,
          Variant &Value)
{
//
    if (CompareText(VarName,"\"Title\"")==0  ) {  //序号
         Value = printtitle+"订阅单";
    }
    if (CompareText(VarName,"\"contect\"")==0  ) {  //序号
         Value =  contact;
    }
        if (CompareText(VarName,"\"tel\"")==0  ) {  //序号
         Value =tel;
    }
        if (CompareText(VarName,"\"address\"")==0  ) {  //序号
         Value =  address;
    }
        if (CompareText(VarName,"\"bk\"")==0  ) {  //序号
         Value =  membk->Text+pxbk ;
    }
        if (CompareText(VarName,"\"danhao\"")==0  ) {  //序号
         Value = dbedtRetailNtCode->Text ;
    }
        if (CompareText(VarName,"\"riqi\"")==0  ) {  //序号
         Value =riqi;
    }
        if (CompareText(VarName,"\"membername\"")==0  ) {  //序号
         Value =   edname->Text ;
    }
        if (CompareText(VarName,"\"kahao\"")==0  ) {  //序号
         Value = edcard->Text ;
    }
        if (CompareText(VarName,"\"totalmount\"")==0  ) {  //序号
         Value =  Edit1->Text ;
    }
        if (CompareText(VarName,"\"dingjing\"")==0  ) {  //序号
         Value =     numorder->Text ;
    }
        if (CompareText(VarName,"\"totalma\"")==0  ) {  //序号
         Value = Edit2->Text ;
    }
        if (CompareText(VarName,"\"totalshiyang\"")==0  ) {  //序号
         Value =  Edit3->Text;
    }

}
//---------------------------------------------------------------------------

void __fastcall Tfrmmemberorder::RzToolButton2Click(TObject *Sender)
{


if (!adoaqnote->Active) {
    return;
}
  AnsiString sql;
        sql = "select wsprinttitle,wscontact,wstel,wsaddress,wsprintbk from sys_printtitle where stgid = " + IntToStr(StgID);


        TADOQuery *query = new TADOQuery(Application);
        query->Connection = fcn;
        query->Close();
        query->SQL->Clear();
        query->SQL->Add(sql);
        query->Open();

        pxbk = query->FieldByName("wsprintbk")->AsAnsiString ;
        printtitle = query->FieldByName("wsprinttitle")->AsAnsiString ;
        contact = query->FieldByName("wscontact")->AsAnsiString ;
        tel = query->FieldByName("wstel")->AsAnsiString ;
        address = query->FieldByName("wsaddress")->AsAnsiString ;
        riqi = FormatDateTime("yyyy-mm-dd",aqheader->FieldByName("HdTime")->AsDateTime);

        delete query;

         print(2);
}
//---------------------------------------------------------------------------


void __fastcall Tfrmmemberorder::BtnViewClick(TObject *Sender)
{
 	Tfrmbookquery * frm = new Tfrmbookquery(Application,fcn,StgID);
	frm->ShowModal();
	delete frm;
}
//---------------------------------------------------------------------------

