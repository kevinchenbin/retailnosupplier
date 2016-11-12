//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
 #include "WholesaleMngForm.h"
#include "unitorder.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma resource "*.dfm"
Tfrmunitorder *frmunitorder;
//---------------------------------------------------------------------------
__fastcall Tfrmunitorder::Tfrmunitorder(TComponent* Owner,TADOConnection *con,int headerid,int flag): TfrmMDIChild(Owner)
{
	fcon = con;
	AnsiString sql;
        danid = headerid;
        aflag = flag;
        if (aflag==1) {


	sql = "select distinct DENSE_RANK() over (order by BS_BookCatalog.id) as xuhao,BS_OrderNote.id,BS_BookCatalog.isbn,BS_BookCatalog.name,BS_BookCatalog.price,BS_BookCatalog.author,BS_BookCatalog.presscount,BS_OrderNoteHeader.HdTime,BS_StorageNote.amount as stgamount, "
			" BS_PressInfo.AbbreviatedName,dbo.UF_BS_GetClientName(BS_OrderNoteHeader.VendorID) as clientname,BS_OrderNote.Amount,BS_OrderNote.SendAmount,BS_OrderNote.UnsendAmount,order_lock.stkamount,BS_OrderNote.localnum,order_lock.usableamount "
			" ,STK_BookInfo.id as BkInfoID,BS_BookCatalog.id as bkcatalogid,BS_OrderNoteHeader.VendorID,BS_OrderNote.amount as OrderAmount,BS_OrderNote.ID as OrderDetailid ,BS_OrderNoteHeader.id as ORDERID,BS_OrderNoteHeader.OrderStr from BS_StorageNote left join STK_BookInfo on BS_StorageNote.BkInfoID = STK_BookInfo.id "
			" left join BS_BookCatalog on STK_BookInfo.BkcatalogID = BS_BookCatalog.id "
			" left join BS_OrderNote on STK_BookInfo.BkcatalogID = BS_OrderNote.BkcatalogID "
			" left join BS_OrderNoteHeader on BS_OrderNote.OrderNtHeaderID = BS_OrderNoteHeader.id "
			" left join BS_PressInfo on BS_BookCatalog.pressid = BS_PressInfo.id "
			" left join order_lock on BS_BookCatalog.id = order_lock.bkcatalogid "
			" where BS_OrderNote.UnsendAmount > 0 and BS_OrderNote.state = 0 and BS_OrderNoteHeader.type = 0 and dbo.BS_OrderNoteHeader.shenheistate = 1 and BS_StorageNote.StgNtHeaderID = " + IntToStr(headerid) ;
         //sql ="";
          }else if (aflag==2) {

         	sql = "select distinct DENSE_RANK() over (order by BS_BookCatalog.id) as xuhao,BS_OrderNote.id,BS_BookCatalog.isbn,BS_BookCatalog.name,BS_BookCatalog.price,BS_BookCatalog.author,BS_BookCatalog.presscount,BS_OrderNoteHeader.HdTime, "
			" BS_PressInfo.AbbreviatedName,dbo.UF_BS_GetClientName(BS_OrderNoteHeader.VendorID) as clientname,BS_OrderNote.Amount,BS_OrderNote.SendAmount,BS_OrderNote.UnsendAmount,order_lock.stkamount,BS_OrderNote.localnum,order_lock.usableamount "
			" ,STK_BookInfo.id as BkInfoID,BS_BookCatalog.id as bkcatalogid,BS_OrderNoteHeader.VendorID,BS_OrderNote.amount as OrderAmount,BS_OrderNote.ID as OrderDetailid ,BS_OrderNoteHeader.id as ORDERID,BS_OrderNoteHeader.OrderStr from BS_WsaleNote left join STK_BookInfo on BS_WsaleNote.BkInfoID = STK_BookInfo.id "
			" left join BS_BookCatalog on STK_BookInfo.BkcatalogID = BS_BookCatalog.id "
			" left join BS_OrderNote on STK_BookInfo.BkcatalogID = BS_OrderNote.BkcatalogID "
			" left join BS_OrderNoteHeader on BS_OrderNote.OrderNtHeaderID = BS_OrderNoteHeader.id "
			" left join BS_PressInfo on BS_BookCatalog.pressid = BS_PressInfo.id "
			" left join order_lock on BS_BookCatalog.id = order_lock.bkcatalogid "
			" where BS_OrderNote.UnsendAmount > 0 and BS_OrderNote.state = 0 and BS_OrderNoteHeader.type = 0 and dbo.BS_OrderNoteHeader.shenheistate = 1 and BS_WsaleNote.wsalentheaderid = " + IntToStr(headerid) ;
         DBGrid1->Columns->Items[11]->Visible = false;
         BtnOK->Visible = false;
          }


	query->Connection = con;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
        aq->Connection = fcon;
        cmdAddNote->Connection = fcon;
		adoexec->Connection = fcon;
		DBGrid1->OnDrawColumnCell= DBGrid1DrawColumnCell;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmunitorder::DBGrid1DrawColumnCell(TObject *Sender, const TRect &Rect,
          int DataCol, TColumn *Column, Grids::TGridDrawState State)
{
	if (DBGrid1->DataSource->DataSet->FieldByName("xuhao")->AsInteger%2  == 0) {
		//DBGrid1->Canvas->Brush->Color = clBtnFace;
	 //	DBGrid1->Canvas->FillRect(Rect);
	      //	DBGrid1->Canvas->Font->Color = clBlue ;
		//DBGrid1->Canvas->Font->Style =  TFontStyles()<<fsBold;
	      //	DBGrid1->DefaultDrawColumnCell(Rect,DataCol,Column,State);
	}
	if (DBGrid1->DataSource->DataSet->FieldByName("xuhao")->AsInteger%2  == 1 ) {
		//DBGrid1->Canvas->Brush->Color = clBtnFace;
	    //	DBGrid1->Canvas->FillRect(Rect);
	     //	DBGrid1->Canvas->Font->Color = clBlack ;
		//DBGrid1->Canvas->Font->Style =  TFontStyles()<<fsBold;
	     //	DBGrid1->DefaultDrawColumnCell(Rect,DataCol,Column,State);
	}
}      /*
void __fastcall Tfrmunitorder::WndProc(TMessage &Msg)
{
if (Msg.Msg == WM_SYSCOMMAND)
{
if(Msg.WParam == (HTCAPTION | SC_MOVE))
{
Msg.WParam = 0;
}
}
Tfrmunitorder::WndProc(Msg);
} */
//---------------------------------------------------------------------------
  void Tfrmunitorder::init(LandInfo* li)
  {     TfrmMDIChild::Init(li);
        linfo.app = li->app ;
        linfo.con = li->con ;
        linfo.userID = li->userID ;
        linfo.UserName = li->UserName ;
        linfo.storageID = li->storageID ;
        linfo.FormatStr = li->FormatStr ;

  }
void __fastcall Tfrmunitorder::BtnOKClick(TObject *Sender)
{
//

 if (query->IsEmpty()) {
          return;
       }
   	AnsiString sql ;
	TBookmark bm;
	Screen->Cursor = crHourGlass ;
	sql = "delete BS_TmpOrderForWsale where  userid = " + IntToStr(fuserid);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
       bool tt= false;
       sql= "select * from BS_TmpOrderForWsale where 1=2";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	TLocateOptions   Opts;
	Opts.Clear();
	Opts   <<   loPartialKey;
	String   str ;
	try
	{
           if (DBGrid1->SelectedRows->Count==0) {
                MessageBox(NULL,"请先选择订单书目！","提示",MB_OK|MB_ICONINFORMATION);
		Screen->Cursor = crDefault ;
		return;
             }
		DBGrid1->DataSource->DataSet->DisableControls();
		for (int i = 0 ; i < DBGrid1->SelectedRows->Count ; i++) {

	       	 DBGrid1->DataSource->DataSet->Bookmark = DBGrid1->SelectedRows->Items[i];
	       	 bm = DBGrid1->DataSource->DataSet->GetBookmark();
	       	 DBGrid1->DataSource->DataSet->GotoBookmark(bm);
                   tt =true;
		 //amount 实际采购数量，bkamount 未发数量
		   /*	sql = "select sum(BS_Tmporder.bkamount) as bkamount,sum(BS_Tmporder.amount) as amount,sum(BS_OrderNote.localnum) as localnum from BS_Tmporder join BS_OrderNote on BS_Tmporder.ordernoteid = BS_OrderNote.id where groupid = 0 and BS_Tmporder.bkcatalogid = " + DBGrid2->DataSource->DataSet->FieldByName("Bkcatalogid")->AsAnsiString ;
			query2->Close();
			query2->SQL->Clear();
			query2->SQL->Add(sql);
			query2->Open();
                   */
			int cc = 0;

			if (aq->State != dsInsert) {
				aq->Append();
			}



			aq->FieldByName("VendorID")->AsInteger = DBGrid1->DataSource->DataSet->FieldByName("VendorID")->AsInteger;
			aq->FieldByName("ORDERID")->AsInteger = DBGrid1->DataSource->DataSet->FieldByName("ORDERID")->AsInteger;
                        aq->FieldByName("bkcatalogid")->AsInteger = DBGrid1->DataSource->DataSet->FieldByName("bkcatalogid")->AsInteger;

                        aq->FieldByName("BkInfoID")->AsAnsiString =  DBGrid1->DataSource->DataSet->FieldByName("BkInfoID")->AsAnsiString;
                     //   aq->FieldByName("catalogid")->AsAnsiString =  DBGrid1->DataSource->DataSet->FieldByName("catalogid")->AsAnsiString;
			aq->FieldByName("OrderDetailid")->AsInteger =  DBGrid1->DataSource->DataSet->FieldByName("OrderDetailid")->AsInteger;
			aq->FieldByName("stkamount")->AsFloat  = DBGrid1->DataSource->DataSet->FieldByName("stkamount")->AsFloat;
			aq->FieldByName("usableamount")->AsAnsiString = DBGrid1->DataSource->DataSet->FieldByName("usableamount")->AsAnsiString;
			aq->FieldByName("OrderAmount")->AsAnsiString = DBGrid1->DataSource->DataSet->FieldByName("OrderAmount")->AsAnsiString;
                         aq->FieldByName("stgid")->AsAnsiString=fstgid;
			aq->FieldByName("userid")->AsInteger = fuserid;
			aq->Post();
                        DBGrid1->DataSource->DataSet->Next();
		 //}
	}
	DBGrid1->DataSource->DataSet->EnableControls() ;
	}catch(...)
	{
		MessageBox(NULL,"生成发货单失败！","提示",MB_OK|MB_ICONINFORMATION);
		Screen->Cursor = crDefault ;
		return;
	}
        if (!tt) {
           Screen->Cursor = crDefault ;
           return;
        }


              ///////////////////////////////////////////////////开始生成导出单///////////////////////

        if(!createproc())
        {
          MessageBox(NULL, "生成发货单失败!","先行者软件提醒",MB_OK|MB_ICONINFORMATION);
          Screen->Cursor = crDefault;
          return;
        }
         Screen->Cursor = crDefault;
         AnsiString caigoudanstr;
          caigoudanstr = "已成功生成"+returncode+"发货单！"+" 是否查看?";
         if(MessageBox(NULL, caigoudanstr.c_str(),"先行者软件提醒",MB_YESNO|MB_ICONQUESTION)==6)
         {
            AnsiString awhere;
            awhere = " where wsaleNtCodeint in("+returncodeint+")";
            TfrmWholesaleMng* frm = new TfrmWholesaleMng(Application,1);
            frm->Init(&linfo);
            frm->SearchDanHao(awhere);
            frm->FindNote(oldcode);
            Close();
         }else
         {
           Close();
         }



}
 bool Tfrmunitorder::createproc()
 {           try
 {

         AnsiString sql,sql1;
      //   USP_BS_OrderToWsale 0,@StgID = 0,@ReturnCode = @ReturnCode OUTPUT,@ReturnCodeint = @ReturnCodeint OUTPUT
          sql = "exec USP_BS_OrderToWsale "+IntToStr(fuserid)+","+IntToStr(fstgid)+","+"@ReturnCode = @ReturnCode OUTPUT,@ReturnCodeint = @ReturnCodeint OUTPUT,@ReturnCodeold=@ReturnCodeold OUTPUT";
          sql1=" SELECT	@ReturnCode as N'@ReturnCode',@ReturnCodeint as N'@ReturnCodeint',@ReturnCodeold as N'@ReturnCodeold'" ;
          adoexec->Close();
          adoexec->SQL->Clear();         //@ReturnCodeold
          adoexec->SQL->Add("DECLARE	@ReturnCode nvarchar(max)");
          adoexec->SQL->Add("DECLARE @ReturnCodeint nvarchar(max) ");
          adoexec->SQL->Add("DECLARE @ReturnCodeold nvarchar(max) ");
          adoexec->SQL->Add(sql);
          adoexec->SQL->Add(sql1);
         // adoexec->SQL->SaveToFile("C:\\ts.txt");
          adoexec->Open();
           returncode = adoexec->FieldByName("@ReturnCode")->AsAnsiString ;
           returncodeint =  adoexec->FieldByName("@ReturnCodeint")->AsAnsiString ;
           oldcode =  adoexec->FieldByName("@ReturnCodeold")->AsAnsiString ;
           return true;
 }catch(...)
 {
        return false;
 }
 }
//---------------------------------------------------------------------------

void __fastcall Tfrmunitorder::BtnNewClick(TObject *Sender)
{
WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmunitorder::BtnNew1Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmunitorder::BtnNew2Click(TObject *Sender)
{
 	AnsiString sql;
        if (aflag==1) {

        	sql = "select distinct DENSE_RANK() over (order by BS_BookCatalog.id) as xuhao,BS_OrderNote.id,BS_BookCatalog.isbn,BS_BookCatalog.name,BS_BookCatalog.price,BS_BookCatalog.author,BS_BookCatalog.presscount,BS_OrderNoteHeader.HdTime,BS_StorageNote.amount as stgamount, "
			" BS_PressInfo.AbbreviatedName,dbo.UF_BS_GetClientName(BS_OrderNoteHeader.VendorID) as clientname,BS_OrderNote.Amount,BS_OrderNote.SendAmount,BS_OrderNote.UnsendAmount,order_lock.stkamount,BS_OrderNote.localnum,order_lock.usableamount "
			" ,STK_BookInfo.id as BkInfoID,BS_BookCatalog.id as bkcatalogid,BS_OrderNoteHeader.VendorID,BS_OrderNote.amount as OrderAmount,BS_OrderNote.ID as OrderDetailid ,BS_OrderNoteHeader.id as ORDERID,BS_OrderNoteHeader.OrderStr from BS_StorageNote left join STK_BookInfo on BS_StorageNote.BkInfoID = STK_BookInfo.id "
			" left join BS_BookCatalog on STK_BookInfo.BkcatalogID = BS_BookCatalog.id "
			" left join BS_OrderNote on STK_BookInfo.BkcatalogID = BS_OrderNote.BkcatalogID "
			" left join BS_OrderNoteHeader on BS_OrderNote.OrderNtHeaderID = BS_OrderNoteHeader.id "
			" left join BS_PressInfo on BS_BookCatalog.pressid = BS_PressInfo.id "
			" left join order_lock on BS_BookCatalog.id = order_lock.bkcatalogid "
			" where order_lock.usableamount >= BS_OrderNote.unsendamount and BS_OrderNote.state = 0 and BS_OrderNoteHeader.type = 0 and dbo.BS_OrderNoteHeader.shenheistate = 1 and BS_StorageNote.StgNtHeaderID = " + IntToStr(danid) ;

        }else if(aflag==2)
        {
         	sql = "select distinct DENSE_RANK() over (order by BS_BookCatalog.id) as xuhao,BS_OrderNote.id,BS_BookCatalog.isbn,BS_BookCatalog.name,BS_BookCatalog.price,BS_BookCatalog.author,BS_BookCatalog.presscount,BS_OrderNoteHeader.HdTime,0 as stgamount, "
			" BS_PressInfo.AbbreviatedName,dbo.UF_BS_GetClientName(BS_OrderNoteHeader.VendorID) as clientname,BS_OrderNote.Amount,BS_OrderNote.SendAmount,BS_OrderNote.UnsendAmount,order_lock.stkamount,BS_OrderNote.localnum,order_lock.usableamount "
			" ,STK_BookInfo.id as BkInfoID,BS_BookCatalog.id as bkcatalogid,BS_OrderNoteHeader.VendorID,BS_OrderNote.amount as OrderAmount,BS_OrderNote.ID as OrderDetailid ,BS_OrderNoteHeader.id as ORDERID,BS_OrderNoteHeader.OrderStr from BS_WsaleNote left join STK_BookInfo on BS_WsaleNote.BkInfoID = STK_BookInfo.id "
			" left join BS_BookCatalog on STK_BookInfo.BkcatalogID = BS_BookCatalog.id "
			" left join BS_OrderNote on STK_BookInfo.BkcatalogID = BS_OrderNote.BkcatalogID "
			" left join BS_OrderNoteHeader on BS_OrderNote.OrderNtHeaderID = BS_OrderNoteHeader.id "
			" left join BS_PressInfo on BS_BookCatalog.pressid = BS_PressInfo.id "
			" left join order_lock on BS_BookCatalog.id = order_lock.bkcatalogid "
			" where order_lock.usableamount >= BS_OrderNote.unsendamount and BS_OrderNote.state = 0 and BS_OrderNoteHeader.type = 0 and dbo.BS_OrderNoteHeader.shenheistate = 1 and BS_WsaleNote.wsalentheaderid = " + IntToStr(danid) ;




        }

	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmunitorder::BtnNew3Click(TObject *Sender)
{
   
     	AnsiString sql;
        if (aflag==1) {
            	sql = "select distinct DENSE_RANK() over (order by BS_BookCatalog.id) as xuhao,BS_OrderNote.id,BS_BookCatalog.isbn,BS_BookCatalog.name,BS_BookCatalog.price,BS_BookCatalog.author,BS_BookCatalog.presscount,BS_OrderNoteHeader.HdTime,BS_StorageNote.amount as stgamount, "
			" BS_PressInfo.AbbreviatedName,dbo.UF_BS_GetClientName(BS_OrderNoteHeader.VendorID) as clientname,BS_OrderNote.Amount,BS_OrderNote.SendAmount,BS_OrderNote.UnsendAmount,order_lock.stkamount,BS_OrderNote.localnum,order_lock.usableamount "
			" ,STK_BookInfo.id as BkInfoID,BS_BookCatalog.id as bkcatalogid,BS_OrderNoteHeader.VendorID,BS_OrderNote.amount as OrderAmount,BS_OrderNote.ID as OrderDetailid ,BS_OrderNoteHeader.id as ORDERID,BS_OrderNoteHeader.OrderStr from BS_StorageNote left join STK_BookInfo on BS_StorageNote.BkInfoID = STK_BookInfo.id "
			" left join BS_BookCatalog on STK_BookInfo.BkcatalogID = BS_BookCatalog.id "
			" left join BS_OrderNote on STK_BookInfo.BkcatalogID = BS_OrderNote.BkcatalogID "
			" left join BS_OrderNoteHeader on BS_OrderNote.OrderNtHeaderID = BS_OrderNoteHeader.id "
			" left join BS_PressInfo on BS_BookCatalog.pressid = BS_PressInfo.id "
			" left join order_lock on BS_BookCatalog.id = order_lock.bkcatalogid "
			" where order_lock.usableamount < BS_OrderNote.unsendamount and order_lock.usableamount >0 and BS_OrderNote.state = 0 and BS_OrderNoteHeader.type = 0 and dbo.BS_OrderNoteHeader.shenheistate = 1 and BS_StorageNote.StgNtHeaderID = " + IntToStr(danid) ;

        }else if (aflag==2) {
                  sql = "select distinct DENSE_RANK() over (order by BS_BookCatalog.id) as xuhao,BS_OrderNote.id,BS_BookCatalog.isbn,BS_BookCatalog.name,BS_BookCatalog.price,BS_BookCatalog.author,BS_BookCatalog.presscount,BS_OrderNoteHeader.HdTime,0 as stgamount, "
			" BS_PressInfo.AbbreviatedName,dbo.UF_BS_GetClientName(BS_OrderNoteHeader.VendorID) as clientname,BS_OrderNote.Amount,BS_OrderNote.SendAmount,BS_OrderNote.UnsendAmount,order_lock.stkamount,BS_OrderNote.localnum,order_lock.usableamount "
			" ,STK_BookInfo.id as BkInfoID,BS_BookCatalog.id as bkcatalogid,BS_OrderNoteHeader.VendorID,BS_OrderNote.amount as OrderAmount,BS_OrderNote.ID as OrderDetailid ,BS_OrderNoteHeader.id as ORDERID,BS_OrderNoteHeader.OrderStr from BS_WsaleNote left join STK_BookInfo on BS_WsaleNote.BkInfoID = STK_BookInfo.id "
			" left join BS_BookCatalog on STK_BookInfo.BkcatalogID = BS_BookCatalog.id "
			" left join BS_OrderNote on STK_BookInfo.BkcatalogID = BS_OrderNote.BkcatalogID "
			" left join BS_OrderNoteHeader on BS_OrderNote.OrderNtHeaderID = BS_OrderNoteHeader.id "
			" left join BS_PressInfo on BS_BookCatalog.pressid = BS_PressInfo.id "
			" left join order_lock on BS_BookCatalog.id = order_lock.bkcatalogid "
			" where order_lock.usableamount < BS_OrderNote.unsendamount and BS_OrderNote.state = 0 and BS_OrderNoteHeader.type = 0 and dbo.BS_OrderNoteHeader.shenheistate = 1 and BS_WsaleNote.wsalentheaderid = " + IntToStr(danid) ;

        }



	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
}
void __fastcall Tfrmunitorder::WndProc(TMessage &Msg)
{
if (Msg.Msg == WM_SYSCOMMAND)
{
if(Msg.WParam == (HTCAPTION | SC_MOVE))
{
Msg.WParam = 0;
}
}
TForm::WndProc(Msg);
}
//---------------------------------------------------------------------------

void __fastcall Tfrmunitorder::FormClose(TObject *Sender, TCloseAction &Action)
{
Action =  caFree;
}
//---------------------------------------------------------------------------

