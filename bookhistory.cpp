//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "bookhistory.h"
#include "Addsyslog.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma resource "*.dfm"
Tfrmbookhistory *frmbookhistory;
//---------------------------------------------------------------------------
__fastcall Tfrmbookhistory::Tfrmbookhistory(TComponent* Owner,TADOConnection *con,int stgid,int catalogid)
	: TForm(Owner)
{
	fcon = con;
	fstgid = stgid;
	m_catalogSearchMode = 0;
	dtpstart->Date = Date();
	dtpend->Date = Date();
	aq1->Connection = con;
	aq2->Connection = con;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	AnsiString sql;
	sql = "select * from SYS_BSSET where name in ('changeDanHaoDisplay','versiontongyi') ";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
        aq->First();
        while(!aq->Eof)
        {
            if (aq->FieldByName("name")->AsAnsiString=="versiontongyi") {
               version= aq->FieldByName("value")->AsBoolean;
            }
            if (aq->FieldByName("name")->AsAnsiString=="changeDanHaoDisplay") {
               ChangeDisplay  = aq->FieldByName("value")->AsBoolean ;
            }

            aq->Next();
        }



	sql = "select sum(amount) as amount from stk_bookinfo where bkcatalogid = " + IntToStr(catalogid);
	if (stgid != -1) {
		sql = sql + " and stgid = " + IntToStr(stgid);
	}
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	edamount->Text = aq->FieldByName("amount")->AsAnsiString ;

	sql = "select name,barcode,type,pressid from bs_bookcatalog where id = " + IntToStr(catalogid);
    aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	bookname = aq->FieldByName("name")->AsAnsiString ;
        if (aq->FieldByName("type")->AsInteger ==1) {
             qikan=true;
             cbwangqi->Visible =true;
             Label2->Visible = true;

             //如何取得期刊名前面部分用于选择往期

             AnsiString sqlstr,qikanname;
             qikanname = GetExtr(bookname);

             sqlstr = "select id,presscount from bs_bookcatalog where name like '"+qikanname+"%'";
             TADOQuery *aq1 =new TADOQuery(Application);
             aq1->Connection = fcon;
             aq1->Close();
             aq1->SQL->Clear();
             aq1->SQL->Add(sqlstr);
             aq1->Open();


             while(!aq1->Eof)
             {

             if (aq1->FieldByName("presscount")->AsAnsiString!="") {
               cbwangqi->AddItem("第"+aq1->FieldByName("presscount")->AsAnsiString+"期",(TObject*)aq1->FieldByName("id")->AsInteger);

             }
                 aq1->Next();
             }
             delete aq1;

        } else
        {
        qikan=false;
           cbwangqi->Visible =false;
             Label2->Visible = false;

        }


         //是否区分供应商
        sql="select value,name from sys_bsset where name in('Qufensupplier','Qufenclient')";
        aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();

        while(!aq->Eof)
        {
           if (aq->FieldByName("name")->AsAnsiString =="Qufensupplier") {
               qfsupplier=aq->FieldByName("value")->AsBoolean;
           }
           if (aq->FieldByName("name")->AsAnsiString =="Qufenclient") {
             qfclient=aq->FieldByName("value")->AsBoolean;
           }
           aq->Next();
        }





	delete aq;
	bkcatalogid = catalogid;
        ReadData();
	Query();
}
void Tfrmbookhistory::ReadData()
{
        AnsiString sql;
        if (qfclient) {
         sql = "select ID,Name from CUST_CustomerInfo where type in(2,3) and customerstate=1 and stgid = "+IntToStr(fstgid)+"order by name";
        }else sql = "select ID,Name from CUST_CustomerInfo where type in(2,3) and customerstate=1 order by name";

        TADOQuery *aq = new TADOQuery(this);
        aq->Connection = fcon;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof )
	{
		cbboxclient->AddItem(aq->FieldByName("Name")->AsString ,(TObject*)aq->FieldByName("ID")->AsInteger );
		aq->Next();
	}
        if (qfsupplier) {
         sql = "select ID,Name from CUST_CustomerInfo where type in(1) and customerstate=1 and stgid = "+IntToStr(fstgid)+"order by name";
        }else sql = "select ID,Name from CUST_CustomerInfo where type in(1) and customerstate=1 order by name";

      //  sql = "select ID,Name from CUST_CustomerInfo where type in(1) and customerstate=1 and stgid = "+IntToStr(fstgid)+"order by name";
       	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof )
	{
		cbboxsupplier->AddItem(aq->FieldByName("Name")->AsString ,(TObject*)aq->FieldByName("ID")->AsInteger );
		aq->Next();
	}




        if(version)
        {
            rg->Items->Add("省代采购");

        }else
        {
        sql="select name from dbo.SYS_StorageInfo where id = "+IntToStr(fstgid);
          	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();

           editcurrent->Text =aq->FieldByName("Name")->AsString ;
        }
        delete aq;
}
//---------------------------------------------------------------------------
AnsiString Tfrmbookhistory::GetExtr(AnsiString context)
{



        return LeftStr(context,context.Length()-2);

        char* t;
	char t2;
	String t1,t3,t4;
        String currentstr;
        currentstr = FormatDateTime("yyyy",Now());
        int suzhi;
	t1 = context;//.TrimLeft().TrimLeft()  ;//.TrimRight();//  .TrimLeft()  ;
	int t5=1,i = context.Length()  ;
	for( int j=1;j<=i;j++)
	{
	t3 = t1.SubString(j,1);
	t = t3.t_str();
	Word k = int (t[0])<<8;
	k = k >> 8;

        if (k<=58&&k>=48) {    //数字

                          break;
        }

        t = t3.t_str();
        t4=t4+t;
          }

	return t4;





}
void __fastcall Tfrmbookhistory::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------
void Tfrmbookhistory::Query()
{
	AnsiString sql;
	switch (rg->ItemIndex ) {
		case 0://订单
			sql = "select distinct A.id,convert (nvarchar(10),B.HdTime,120) as HdTime,B.orderstr AS Code,dbo.UF_BS_GetClientName(B.VendorID) as Name,"
					" A.Amount,A.Discount,A.FixedPrice,A.DiscountedPrice,A.SendAmount,A.UnsendAmount,sys_user.name as opname,A.class "
					" from BS_OrderNote A left join BS_OrderNoteHeader B on A.OrderNtHeaderID = B.id left join sys_user on B.OperatorID = sys_user.id where A.state = 0 and A.BkcatalogID = " + IntToStr(bkcatalogid) ;

			if (fstgid != -1) {
				sql = sql + " and B.StgID = " + IntToStr(fstgid);
			}

			if (chstart->Checked ) {
				sql = sql + " and datediff(day,'" + DateToStr(dtpstart->Date) + "',B.HdTime) >= 0";
			}
			if (chend->Checked ) {
				sql = sql + " and datediff(day,'" + DateToStr(dtpend->Date) + "',B.HdTime) <= 0";
			}

                        if (cbclient->Checked) {
                             sql = sql +" and B.VendorID="+IntToStr((int)cbboxclient->Items->Objects[cbboxclient->ItemIndex]);
                        }
			aq1->Close();
			aq1->SQL->Clear();
			aq1->SQL->Add(sql);
			aq1->Open();
			dg1->Columns->Items[0]->Title->Caption = "客户名称";
			dg1->Columns->Items[1]->Title->Caption = "订货数量";
			dg1->Columns->Items[5]->Title->Caption = "已发数量";
			dg1->Columns->Items[6]->Title->Caption = "未发数量";
                         dg1->Columns->Items[5]->Width = 80;
                         dg1->Columns->Items[6]->Width = 80;
			dg1->Columns->Items[7]->Visible = false;
                         dg1->Columns->Items[5]->Visible = true;
			dg1->Columns->Items[6]->Visible = true;


			dg1->Columns->Items[10]->Visible = false;
			dg1->Visible = true;
		break;
		case 1: //采购
			sql = "select distinct A.id,convert (nvarchar(10),B.HdTime,120) as HdTime,B.procurestr AS Code,CUST_CustomerInfo.Name as Name,"
					" A.Amount,A.Discount,A.FixedPrice,A.DiscountedPrice,A.RecAmount as SendAmount,A.UnrecAmount as UnsendAmount,sys_user.name as opname "
					" from BS_ProcureNote A left join BS_ProcureNoteHeader B on A.ProcureNtHeaderID = B.id "
					" left join sys_user on B.OperatorID = sys_user.id "
					" left join CUST_CustomerInfo on B.SupplierID = CUST_CustomerInfo.id where A.BkcatalogID = " + IntToStr(bkcatalogid);
			if (fstgid != -1) {
				sql = sql + " and B.StgID = " + IntToStr(fstgid);
			}

			if (chstart->Checked ) {
				sql = sql + " and datediff(day,'" + DateToStr(dtpstart->Date) + "',B.HdTime) >= 0";
			}
			if (chend->Checked ) {
				sql = sql + " and datediff(day,'" + DateToStr(dtpend->Date) + "',B.HdTime) <= 0";
			}
                        if (cbsupplier->Checked) {
                           sql = sql +" and B.supplierid="+IntToStr((int)cbboxsupplier->Items->Objects[cbboxsupplier->ItemIndex]);
                        }

			aq1->Close();
			aq1->SQL->Clear();
			aq1->SQL->Add(sql);
			aq1->Open();
			dg1->Columns->Items[0]->Title->Caption = "供应商名称";

			dg1->Columns->Items[1]->Title->Caption = "采购数量";
                        dg1->Columns->Items[1]->Width = 80;
			dg1->Columns->Items[5]->Title->Caption = "已到数量";
                        dg1->Columns->Items[5]->Width = 80;
			dg1->Columns->Items[6]->Title->Caption = "未到数量";
                        dg1->Columns->Items[6]->Width = 80;
                        dg1->Columns->Items[5]->Visible = true;
                        dg1->Columns->Items[6]->Visible = true;
			dg1->Columns->Items[7]->Visible = false;

			dg1->Columns->Items[10]->Visible = false;
			dg1->Visible = true;

		break;
		case 2://入库
			if (ChangeDisplay) {
				sql = "select distinct A.id,convert (nvarchar(10),B.HdTime,120) as HdTime,B.StgNtCodeStr AS Code,CUST_CustomerInfo.Name as Name,"
					" A.Amount,A.Discount,A.FixedPrice,A.DiscountedPrice,sys_user.name as opname,0 as SendAmount,0 as UnsendAmount "
					" from BS_StorageNote A left join BS_StorageNoteHeader B on A.StgNtHeaderID = B.id "
					" left join CUST_CustomerInfo on B.SupplierID = CUST_CustomerInfo.id "
					" left join sys_user on B.OperatorID = sys_user.id "
					" left join STK_BookInfo on A.BkInfoID = STK_BookInfo.id where STK_BookInfo.BkcatalogID = " + IntToStr(bkcatalogid);
			}
			else
			{
				sql = "select distinct A.id,convert (nvarchar(10),B.HdTime,120) as HdTime,B.StgNtCode AS Code,CUST_CustomerInfo.Name as Name,"
					" A.Amount,A.Discount,A.FixedPrice,A.DiscountedPrice,sys_user.name as opname,0 as SendAmount,0 as UnsendAmount "
					" from BS_StorageNote A left join BS_StorageNoteHeader B on A.StgNtHeaderID = B.id "
					" left join CUST_CustomerInfo on B.SupplierID = CUST_CustomerInfo.id "
					" left join sys_user on B.OperatorID = sys_user.id "
					" left join STK_BookInfo on A.BkInfoID = STK_BookInfo.id where STK_BookInfo.BkcatalogID = " + IntToStr(bkcatalogid);
			}
            if (fstgid != -1) {
				sql = sql + " and B.StgID = " + IntToStr(fstgid);
			}

			if (chstart->Checked ) {
				sql = sql + " and datediff(day,'" + DateToStr(dtpstart->Date) + "',B.HdTime) >= 0";
			}
			if (chend->Checked ) {
				sql = sql + " and datediff(day,'" + DateToStr(dtpend->Date) + "',B.HdTime) <= 0";
			}

                        if (cbsupplier->Checked) {
                           sql = sql +" and B.supplierid="+IntToStr((int)cbboxsupplier->Items->Objects[cbboxsupplier->ItemIndex]);
                        }
			aq1->Close();
			aq1->SQL->Clear();
			aq1->SQL->Add(sql);
			aq1->Open();
			dg1->Columns->Items[0]->Title->Caption = "供应商名称";
                        // dg1->Columns->Items[0]->Field = aq1->FieldByName("name");
			dg1->Columns->Items[1]->Title->Caption = "入库数量";
                        dg1->Columns->Items[1]->Width = 80;
                        dg1->Columns->Items[5]->Visible = false;
			dg1->Columns->Items[6]->Visible = false;
			dg1->Columns->Items[7]->Visible = false;
                        dg1->Columns->Items[8]->Visible = true;
			dg1->Columns->Items[9]->Visible = true;
			dg1->Visible = true;
		break;
		case 3://发货
			if (ChangeDisplay) {
				sql = "select distinct A.id,convert (nvarchar(10),B.HdTime,120) as HdTime,B.WsaleNtCodeStr AS Code,dbo.UF_BS_GetClientName(B.VendorID) as Name,"
					" A.Amount,A.Discount,A.FixedPrice,A.DiscountedPrice,sys_user.name as opname,0 as SendAmount,0 as UnsendAmount,CUST_CustomerInfo.name as suppliername "
					" from BS_WsaleNote A left join BS_WsaleNoteHeader B on A.WsaleNtHeaderID = B.id "
					" left join sys_user on B.OperatorID = sys_user.id "
					" left join stk_bookinfo on  A.BkInfoID = STK_BookInfo.id "
					" left join CUST_CustomerInfo on stk_bookinfo.supplierid = CUST_CustomerInfo.id where STK_BookInfo.BkcatalogID = " + IntToStr(bkcatalogid);
			}
			else
			{
				sql = "select distinct A.id,convert (nvarchar(10),B.HdTime,120) as HdTime,B.WsaleNtCode AS Code,dbo.UF_BS_GetClientName(B.VendorID) as Name,"
					" A.Amount,A.Discount,A.FixedPrice,A.DiscountedPrice,sys_user.name as opname,0 as SendAmount,0 as UnsendAmount,CUST_CustomerInfo.name as suppliername "
					" from BS_WsaleNote A left join BS_WsaleNoteHeader B on A.WsaleNtHeaderID = B.id "
					" left join sys_user on B.OperatorID = sys_user.id "
					" left join STK_BookInfo on A.BkInfoID = STK_BookInfo.id "
					" left join CUST_CustomerInfo on stk_bookinfo.supplierid = CUST_CustomerInfo.id where STK_BookInfo.BkcatalogID = " + IntToStr(bkcatalogid);
			}
			if (fstgid != -1) {
				sql = sql + " and B.StgID = " + IntToStr(fstgid);
			}
			if (chstart->Checked ) {
				sql = sql + " and datediff(day,'" + DateToStr(dtpstart->Date) + "',B.HdTime) >= 0";
			}
			if (chend->Checked ) {
				sql = sql + " and datediff(day,'" + DateToStr(dtpend->Date) + "',B.HdTime) <= 0";
			}

                         if (cbclient->Checked) {
                             sql = sql +" and B.VendorID="+IntToStr((int)cbboxclient->Items->Objects[cbboxclient->ItemIndex]);
                        }
			aq1->Close();
			aq1->SQL->Clear();
			aq1->SQL->Add(sql);
			aq1->Open();
			dg1->Columns->Items[0]->Title->Caption = "客户名称";
			dg1->Columns->Items[1]->Title->Caption = "发货数量";
                       // dg1->Columns->Items[0]->Field = aq1->FieldByName("name");
                        dg1->Columns->Items[1]->Width = 80;
                        dg1->Columns->Items[5]->Visible = false;
			dg1->Columns->Items[6]->Visible = false;
			dg1->Columns->Items[7]->Visible = false;
                        dg1->Columns->Items[9]->Visible = true;
			dg1->Columns->Items[8]->Field = aq1->FieldByName("Code");
			dg1->Columns->Items[8]->Visible = true;
			dg1->Visible = true;
		break;
		case 4://零售
			sql = "select distinct A.id,convert (nvarchar(10),B.HdTime,120) as HdTime,B.RetailNtCode AS Code,CUST_MemberInfo.Name as Name,"
					" A.Amount,A.Discount,A.FixedPrice,A.DiscountedPrice,sys_user.name as opname,0 as SendAmount,0 as UnsendAmount "
					" from BS_RetailNote A left join BS_RetailNoteHeader B on A.RetailNtHeaderID = B.id "
					" left join CUST_MemberInfo on B.MemberID = CUST_MemberInfo.ID "
					" left join sys_user on B.OperatorID = sys_user.id "
					" left join STK_BookInfo on A.BkInfoID = STK_BookInfo.id where STK_BookInfo.BkcatalogID = " + IntToStr(bkcatalogid);
			if (fstgid != -1) {
				sql = sql + " and B.StgID = " + IntToStr(fstgid);
			}
			if (chstart->Checked ) {
				sql = sql + " and datediff(day,'" + DateToStr(dtpstart->Date) + "',B.HdTime) >= 0";
			}
			if (chend->Checked ) {
				sql = sql + " and datediff(day,'" + DateToStr(dtpend->Date) + "',B.HdTime) <= 0";
			}
                         if (cbsupplier->Checked) {
                           sql = sql +" and STK_BookInfo.supplierid="+IntToStr((int)cbboxsupplier->Items->Objects[cbboxsupplier->ItemIndex]);
                        }
			aq1->Close();
			aq1->SQL->Clear();
			aq1->SQL->Add(sql);
			aq1->Open();
			dg1->Columns->Items[0]->Title->Caption = "会员名称";
			dg1->Columns->Items[1]->Title->Caption = "零售数量";
			dg1->Columns->Items[6]->Visible = false;
			dg1->Columns->Items[7]->Visible = false;
			dg1->Columns->Items[8]->Visible = false;
                        dg1->Columns->Items[5]->Visible = false;
			dg1->Visible = true;
		break;
		case 5: //配送
			sql = "select distinct A.id,outstorage,instorage,convert (nvarchar(10),B.HdTime,120) as HdTime,isnull(B.stgntCodeStr,B.zndiaontcode) AS Code,C.Name +'---------->'+D.name  as name,"
					" A.amountbk as amount,A.Discount,A.FixedPrice,A.DiscountedPrice,sys_user.name as opname,0 as SendAmount,0 as UnsendAmount "
					" from BS_ZN_DiaoNote A left join BS_ZN_DiaoNoteHeader B on A.DiaoNtHeaderID = B.id "
					" left join SYS_StorageInfo C on B.outstorage = C.ID "
					" left join SYS_StorageInfo D on B.instorage = D.ID "
					" left join sys_user on B.OperatorID = sys_user.id "
					" left join STK_BookInfo on A.Bkinfoid = STK_BookInfo.id where STK_BookInfo.BkcatalogID = " + IntToStr(bkcatalogid) ;
			if (fstgid != -1) {
				sql = sql + " and (B.outstorage = " + IntToStr(fstgid) + " or B.instorage = " + IntToStr(fstgid) + ")";
			}
			if (chstart->Checked ) {
				sql = sql + " and datediff(day,'" + DateToStr(dtpstart->Date) + "',B.HdTime) >= 0";
			}
			if (chend->Checked ) {
				sql = sql + " and datediff(day,'" + DateToStr(dtpend->Date) + "',B.HdTime) <= 0";
			}
                         if (cbsupplier->Checked) {
                           sql = sql +" and STK_BookInfo.supplierid="+IntToStr((int)cbboxsupplier->Items->Objects[cbboxsupplier->ItemIndex]);
                        }
			aq1->Close();
			aq1->SQL->Clear();
			aq1->SQL->Add(sql);
			aq1->Open();
			dg1->Columns->Items[0]->Title->Caption = "调出入店";
		       	dg1->Columns->Items[0]->Width = 240;
			dg1->Columns->Items[1]->Title->Caption = "实配数量";

			dg1->Columns->Items[6]->Visible = false;
			dg1->Columns->Items[7]->Visible = false;

                        dg1->Columns->Items[5]->Visible = false;
			dg1->Visible = true;
		break;
            case 6:      //省代采购
                  sql =" select distinct A.id,convert (nvarchar(10),A.HdTime,120) as HdTime,A.Daixiaocode as Code,c.name,a.TotalAmount as Amount,a.FixedPrice,A.DiscountedPrice, ";
                  sql = sql +" A.RecAmount as SendAmount,A.caigoudiscount as Discount,A.UnrecAmount as UnsendAmount, d.name as opname from BS_DaixiaoHeader A join BS_DaixiaoNote B on a.id = b.daixiaoheadid ";
                  sql = sql +" left join CUST_CustomerInfo c on A.supplierid = c.id left join sys_user d on d.id = A.userid  where A.BkcatalogID = " + IntToStr(bkcatalogid);;

			if (fstgid != -1) {
				sql = sql + " and A.StgID = " + IntToStr(fstgid);
			}

			if (chstart->Checked ) {
				sql = sql + " and datediff(day,'" + DateToStr(dtpstart->Date) + "',A.HdTime) >= 0";
			}
			if (chend->Checked ) {
				sql = sql + " and datediff(day,'" + DateToStr(dtpend->Date) + "',A.HdTime) <= 0";
			}
                          if (cbsupplier->Checked) {
                           sql = sql +" and A.supplierid="+IntToStr((int)cbboxsupplier->Items->Objects[cbboxsupplier->ItemIndex]);
                        }

			aq1->Close();
			aq1->SQL->Clear();
			aq1->SQL->Add(sql);
			aq1->Open();
			dg1->Columns->Items[0]->Title->Caption = "供应商名称";

			dg1->Columns->Items[1]->Title->Caption = "采购数量";
                        dg1->Columns->Items[1]->Width = 80;
			dg1->Columns->Items[5]->Title->Caption = "已到数量";
                        dg1->Columns->Items[5]->Width = 80;
			dg1->Columns->Items[6]->Title->Caption = "未到数量";
                        dg1->Columns->Items[6]->Width = 80;
                        dg1->Columns->Items[5]->Visible = true;
                        dg1->Columns->Items[6]->Visible = true;
			dg1->Columns->Items[7]->Visible = false;

			dg1->Columns->Items[10]->Visible = false;
			dg1->Visible = true;

            break;
    default:
        ;
	}

        int aamount,bamount;
        float adisamount,bdiscount;
        float adiscountamount,bdiscountamount;
        int sendamount,unsendamount;
         aamount=0;
         bamount=0;
         adisamount=0;
         bdiscount=0;
         adiscountamount=0;
         bdiscountamount=0;
        sendamount=0;
        unsendamount=0;

        //统计
        aq1->DisableControls();

        for (int i=0; i < aq1->RecordCount; i++) {

           if (rg->ItemIndex==5) { //配送
                  if (aq1->FieldByName("instorage")->AsInteger==fstgid) {
                 aamount=aamount+aq1->FieldByName("amount")->AsInteger;
                 adisamount=adisamount+aq1->FieldByName("fixedprice")->AsFloat;
                 adiscountamount=adiscountamount+aq1->FieldByName("discountedprice")->AsFloat;

               }

               if (aq1->FieldByName("outstorage")->AsInteger==fstgid) {
                  bamount=bamount+aq1->FieldByName("amount")->AsInteger;
                 bdiscount=bdiscount+aq1->FieldByName("fixedprice")->AsFloat;
                 bdiscountamount=bdiscountamount+aq1->FieldByName("discountedprice")->AsFloat;
               }




                sendamount= sendamount + aq1->FieldByName("sendamount")->AsInteger;
                unsendamount= unsendamount + aq1->FieldByName("unsendamount")->AsInteger;
           }else
           {
               if (aq1->FieldByName("amount")->AsInteger>=0) {
                 aamount=aamount+aq1->FieldByName("amount")->AsInteger;
               }else bamount=bamount+aq1->FieldByName("amount")->AsInteger;

               if (aq1->FieldByName("fixedprice")->AsFloat>=0) {
                 adisamount=adisamount+aq1->FieldByName("fixedprice")->AsFloat;
               }else bdiscount=bdiscount+aq1->FieldByName("fixedprice")->AsFloat;

               if (aq1->FieldByName("discountedprice")->AsFloat>=0) {
                 adiscountamount=adiscountamount+aq1->FieldByName("discountedprice")->AsFloat;
               }else bdiscountamount=bdiscountamount+aq1->FieldByName("discountedprice")->AsFloat;

                sendamount= sendamount + aq1->FieldByName("sendamount")->AsInteger;
                unsendamount= unsendamount + aq1->FieldByName("unsendamount")->AsInteger;
           }
           aq1->Next();

        }
         aq1->EnableControls();

         if(rg->ItemIndex==5)  //如果是配送
         {
               bamount=bamount*-1;
               bdiscount=bdiscount*-1;
               bdiscountamount=bdiscountamount*-1;
         }





        dg1->Columns->Items[1]->Footers->Items[0]->Value =aamount ;
        dg1->Columns->Items[1]->Footers->Items[1]->Value =bamount ;
        dg1->Columns->Items[1]->Footers->Items[2]->Value =bamount+aamount;

        dg1->Columns->Items[3]->Footers->Items[0]->Value = FormatFloat("0.00",adisamount);
        dg1->Columns->Items[3]->Footers->Items[1]->Value = FormatFloat("0.00",bdiscount);
        dg1->Columns->Items[3]->Footers->Items[2]->Value = FormatFloat("0.00",bdiscount+adisamount);

        dg1->Columns->Items[4]->Footers->Items[0]->Value = FormatFloat("0.00",adiscountamount);
        dg1->Columns->Items[4]->Footers->Items[1]->Value = FormatFloat("0.00",bdiscountamount);
        dg1->Columns->Items[4]->Footers->Items[2]->Value = FormatFloat("0.00",bdiscountamount+adiscountamount);

}
//---------------------------------------------------------------------------
void __fastcall Tfrmbookhistory::rgClick(TObject *Sender)
{
	dg1->Columns->Items[1]->Field = NULL;
	//dg1->Columns->Items[1]->Visible = false;
	dg1->Columns->Items[8]->Field = NULL;
	//dg1->Columns->Items[8]->Visible = false;
	Query();
}
//---------------------------------------------------------------------------



void __fastcall Tfrmbookhistory::cbwangqiChange(TObject *Sender)
{
    bkcatalogid = (int)cbwangqi->Items->Objects[cbwangqi->ItemIndex];
    Query();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbookhistory::edsupplierKeyPress(TObject *Sender, wchar_t &Key)

{
    	if (Key == '\r') {

		AnsiString sql;
		TADOQuery *aq = new TADOQuery(this);
		aq->Connection = fcon;

                if(qfsupplier)
                {
                   sql = "select ID,Name from CUST_CustomerInfo where type in(1) and customerstate=1 and stgid="+IntToStr(fstgid)+" and name like '%" + edsupplier->Text.Trim() + "%' order by name";

                }else sql = "select ID,Name from CUST_CustomerInfo where type in(1) and customerstate=1 and  name like '%" + edsupplier->Text.Trim() + "%' order by name";


		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		cbboxsupplier->Clear();
		while (!aq->Eof )
		{
			cbboxsupplier->AddItem(aq->FieldByName("Name")->AsString ,(TObject*)aq->FieldByName("ID")->AsInteger );
			aq->Next();
		}
		aq->First();
		cbboxsupplier->ItemIndex = cbboxsupplier->Items->IndexOfObject((TObject*)aq->FieldByName("ID")->AsInteger );
	      //	ClientID = aq->FieldByName("ID")->AsInteger;
		cbboxsupplier->SetFocus();
		delete aq;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbookhistory::edclientKeyPress(TObject *Sender, wchar_t &Key)
{
   	if (Key == '\r') {

		AnsiString sql;
		TADOQuery *aq = new TADOQuery(this);
		aq->Connection = fcon;

                if(qfclient)
                {
                  sql = "select ID,Name from CUST_CustomerInfo where type in(2,3) and customerstate=1 and stgid="+IntToStr(fstgid)+" and name like '%" + edclient->Text.Trim() + "%' order by name";
                }else sql = "select ID,Name from CUST_CustomerInfo where type in(2,3) and customerstate=1  and name like '%" + edclient->Text.Trim() + "%' order by name";



		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		cbboxclient->Clear();
		while (!aq->Eof )
		{
			cbboxclient->AddItem(aq->FieldByName("Name")->AsString ,(TObject*)aq->FieldByName("ID")->AsInteger );
			aq->Next();
		}
		aq->First();
		cbboxclient->ItemIndex = cbboxclient->Items->IndexOfObject((TObject*)aq->FieldByName("ID")->AsInteger );
		//ClientID = aq->FieldByName("ID")->AsInteger;
		cbboxclient->SetFocus();
		delete aq;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbookhistory::cbsupplierClick(TObject *Sender)
{
     if (cbsupplier->Checked ) {
       cbclient->Checked=false;
      cbclient->Enabled = false;
     }else
     {

      cbclient->Checked=false;
      cbclient->Enabled = true;
     }


}
//---------------------------------------------------------------------------

void __fastcall Tfrmbookhistory::cbclientClick(TObject *Sender)
{
     if (cbclient->Checked) {
       cbsupplier->Checked=false;
      cbsupplier->Enabled = false;
     }else
     {
        cbsupplier->Checked=false;
      cbsupplier->Enabled = true;

     }

}
//---------------------------------------------------------------------------

void __fastcall Tfrmbookhistory::cbboxclientChange(TObject *Sender)
{
     if (cbclient->Checked) {
        Query();
     }

}
//---------------------------------------------------------------------------

void __fastcall Tfrmbookhistory::cbboxsupplierChange(TObject *Sender)
{
   if (cbsupplier->Checked) {
        Query();
     }
}
//---------------------------------------------------------------------------

