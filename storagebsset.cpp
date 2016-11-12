//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "storagebsset.h"
#include "Unittuihuoset.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrmstoragebsset *frmstoragebsset;
//---------------------------------------------------------------------------
__fastcall Tfrmstoragebsset::Tfrmstoragebsset(TComponent* Owner,TADOConnection* con,int stgid)
	: TForm(Owner)
{
   aquery->Connection = con;
   qryretairange->Connection = con;
   fcon=con;
   fstgid=stgid;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmstoragebsset::sbokClick(TObject *Sender)
{
   AnsiString sql,bk;
   int bit;
   //小数点位数
   if (etdot->Text == "") {
		bit = 0;
   }
   else
   {
		bit = StrToInt(etdot->Text.Trim() );
   }
   if (bit > 4) {
           ShowMsg(Handle ,"小数位数最高只能设置4位！",0);
	   return;
   }
   bk = "0";
   if (bit > 0) {
		bk = bk + ".";
		for (int i = 0; i < bit; i++) {
			bk = bk + "0";
		}
   }
   sql = "update sys_bsset set bk = '" + bk + "' where name = 'xiaoshudian'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();

   //是否允许重复录入
   if (cbsameid->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'sameid'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'sameid'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //是否自动注销采购记录
   if (cbauto->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'autologout'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'autologout'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //有订货记录提示
   if (cborder->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'ordernote'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'ordernote'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //跟踪上次入库折扣
   if (cbtrace->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'tracediscount'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'tracediscount'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //入库进/退货明细
   if (cbstoragehistory->Checked ) {
		sql = "update sys_bsset set value = 1,bk = '" + edstorageday->Text + "' where name = 'storageday'";
   }
   else
   {
		sql = "update sys_bsset set value = 0,bk = '" + edstorageday->Text + "' where name = 'storageday'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //预计批销折扣是否启用附加点设置
   if (cbadddotenable->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'adddotenable'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'adddotenable'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //跟踪上次预计批销折扣
   if (cblastyjpxdiscount->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'lastyjpxdiscount'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'lastyjpxdiscount'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //预计批销折扣以何种优先
   if (cblastyjpx->Checked ) {
		sql = "update sys_bsset set bk = 'lastyjpxdiscount' where name = 'yjpxfirstkind'";
   }
   else
   {
		sql = "update sys_bsset set bk = 'adddotenable' where name = 'yjpxfirstkind'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //入库明细显示所有供应商的历史记录
   if (cbrkallsupplier->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'rkallsupplier'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'rkallsupplier'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //入库查单密码
   if (cbrkusefind->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'rkusefind'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'rkusefind'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //入库删单密码
   if (cbrkusedelete->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'rkusedelete'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'rkusedelete'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //入库退货密码
   if (cbrkusetuihuo->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'rkusetuihuo'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'rkusetuihuo'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //入库打印备注
   /*if (cbrkprintbk->Checked ) {
		sql = "update sys_bsset set value = 1,bk = '" + edrkprintbk->Text + "' where name = 'rkprintbk'";
   }
   else
   {
		sql = "update sys_bsset set value = 0,bk = '" + edrkprintbk->Text + "' where name = 'rkprintbk'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();   */
   //是否启用多货源
   if (chmutisupplier->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'mutisupplier'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'mutisupplier'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //有库存引用可删除库位
   if (chdeletestack->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'deletestack'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'deletestack'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //入库退货率计算时间
   if (edmonth->Text == "" ) {
		edmonth->Text == "0";
   }
   sql = "update sys_bsset set bk = " + edmonth->Text + "where name = 'rkbenqituihuolv'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //入库修改单头密码
   if (cbrkusechange->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'rkusechange'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'rkusechange'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //跟踪上次预计零售折扣
   if (cblastyjlsdiscount->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'lastyjlsdiscount'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'lastyjlsdiscount'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //重复录入提示
   if (chstoragesametishi->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'storagesametishi'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'storagesametishi'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   /*//入库打印抬头
   sql = "update sys_bsset set bk = '" + edrkprinttitle->Text.Trim() + "' where name = 'rkprinttitle'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //联系人
   sql = "update sys_bsset set bk = '" + edrkcontact->Text.Trim() + "' where name = 'rkcontact'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //电话
   sql = "update sys_bsset set bk = '" + edrktel->Text.Trim() + "' where name = 'rktel'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //地址
   sql = "update sys_bsset set bk = '" + edrkaddress->Text.Trim() + "' where name = 'rkaddress'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL(); */
   //退货监管
   if (chrktuihuoguanli->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'rktuihuoguanli'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'rktuihuoguanli'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //入库退货默认周期
   if (edtkmouth->Text == "" ) {
		edtkmouth->Text == "0";
   }
   sql = "update sys_bsset set bk = " + edtkmouth->Text + "where name = 'tkmouth'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //出库顺序
   sql = "update sys_bsset set bk = " + IntToStr(rg->ItemIndex + 1)  + "where name = 'chuohuoyouxian'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //自动产生附加条码
   if (chcrtuserbarcode->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'crtuserbarcode'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'crtuserbarcode'";
   }
   AnsiString sql1,sql2,sql3,sql4,sql5;
   if (cbcaigoucayi->Checked) {
     	sql1 = "update sys_bsset set value = 1 where name = 'caigoucayi';";
   }else
   {
   	sql1 = "update sys_bsset set value = 0 where name = 'caigoucayi';";
   }
   if (cbsamerkyx->Checked) {      //出库重复录入
    	sql2 = "update sys_bsset set value = 1 where name = 'cbsamerkyx';";
   }else
   {
      	sql2 = "update sys_bsset set value = 0 where name = 'cbsamerkyx';";
   }
   if (cbsamerkts->Checked) {      //出库重复提示
     	sql3 = "update sys_bsset set value = 1 where name = 'cbsamerkts';";
   }else
   {
      	sql3 = "update sys_bsset set value = 0 where name = 'cbsamerkts';";
   }

   if (cbcaigoudiscount->Checked) {      //跟踪采购折扣
     	sql4 = "update sys_bsset set value = 1 where name = 'rukucaigoudiscount';";
                              //cbcaigoudiscount
      }else
      {
      	sql4 = "update sys_bsset set value = 0 where name = 'rukucaigoudiscount';";

   }
      if (cbrukufeishendaicaigou->Checked) {      //跟踪采购折扣
     	sql5 = "update sys_bsset set value = 1 where name = 'cbrukufeishendaicaigou';";

      }else
      {
      	sql5 = "update sys_bsset set value = 0 where name = 'cbrukufeishendaicaigou';";

   }
   //是否区分供应商和客户
   AnsiString sql6,sql7;


   if (cbqfclient->Checked) {
      sql6 = "update sys_bsset set value = 1 where name = 'Qufenclient';";
   }else
   {
      sql6 = "update sys_bsset set value = 0 where name = 'Qufenclient';";

   }

    if (cbqfsupplier->Checked) {
       sql7 = "update sys_bsset set value = 1 where name = 'Qufensupplier';";
   }else
   {
       sql7 = "update sys_bsset set value = 0 where name = 'Qufensupplier';";

   }


   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql1);
   aquery->SQL->Add(sql);
   aquery->SQL->Add(sql2);
   aquery->SQL->Add(sql3);
   aquery->SQL->Add(sql4);
   aquery->SQL->Add(sql5);
    aquery->SQL->Add(sql6);
    aquery->SQL->Add(sql7);
   aquery->ExecSQL();
   ShowMsg(Handle ,"业务设置成功！",3);
   Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmstoragebsset::FormShow(TObject *Sender)
{
	Readydata();
        if (0==version) {
            cbcaigoudiscount->Checked =false;
                cbcaigoudiscount->Visible=false;
            cbrukufeishendaicaigou->Caption="跟踪采购折扣";
        }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmstoragebsset::sbcancelClick(TObject *Sender)
{
   Close();
}
void Tfrmstoragebsset::Readydata()
{
  String sql= "select * from sys_bsset",bk;
  int bit;
  aquery->Close();
  aquery->SQL->Clear();
  aquery->SQL->Add(sql);
  aquery->Open();
  while (!aquery->Eof)
  {                                     //入库允许重复录入
	if (aquery->FieldByName("name")->AsAnsiString == "sameid")
	{
		cbsameid->Checked = aquery->FieldByName("value")->AsBoolean ;

	}
	if (aquery->FieldByName("name")->AsAnsiString == "tracediscount")
	{
		cbtrace->Checked = aquery->FieldByName("value")->AsBoolean ;

	}
	if (aquery->FieldByName("name")->AsAnsiString == "autologout")
	{
		cbauto->Checked = aquery->FieldByName("value")->AsBoolean ;

	}
	if (aquery->FieldByName("name")->AsAnsiString == "ordernote")
	{
		cborder->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "adddotenable")
	{
		cbadddotenable->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "lastyjpxdiscount")
	{
		cblastyjpxdiscount->Checked = aquery->FieldByName("value")->AsBoolean ;

	}
	if (aquery->FieldByName("name")->AsAnsiString == "yjpxfirstkind")
	{
		if (aquery->FieldByName("bk")->AsString == "lastyjpxdiscount" ) {
			cblastyjpx ->Checked = true;
			cbadddot->Checked = false;
		}
		else
		{
			cblastyjpx ->Checked = false;
			cbadddot->Checked = true;
		}

	}
	if (aquery->FieldByName("name")->AsAnsiString == "xiaoshudian" ) {
		bk = aquery->FieldByName("bk")->AsString;
		if (bk.Pos(".") == 0 ) {
			bit = 0;
		}
		else
		{
			bit = bk.Length() - bk.Pos(".");
		}
        etdot->Text = IntToStr(bit);
	}
	if (aquery->FieldByName("name")->AsAnsiString == "storageday" ) {
		cbstoragehistory->Checked = aquery->FieldByName("value")->AsBoolean ;
		edstorageday->Text = aquery->FieldByName("bk")->AsString ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "rkallsupplier")
	{
		cbrkallsupplier->Checked = aquery->FieldByName("value")->AsBoolean ;

	}
	//查单
	if (aquery->FieldByName("name")->AsAnsiString == "rkusefind")
	{
		cbrkusefind->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	//删单
	if (aquery->FieldByName("name")->AsAnsiString == "rkusedelete")
	{
		cbrkusedelete->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	//退货
	if (aquery->FieldByName("name")->AsAnsiString == "rkusetuihuo")
	{
		cbrkusetuihuo->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	//入库打印备注
	/*if (aquery->FieldByName("name")->AsAnsiString == "rkprintbk" ) {
		cbrkprintbk->Checked = aquery->FieldByName("value")->AsBoolean ;
		edrkprintbk->Text = aquery->FieldByName("bk")->AsString ;
	} */
	//是否启用多货源
	if (aquery->FieldByName("name")->AsAnsiString == "mutisupplier")
	{
		chmutisupplier->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	//有库存引用可删除库位
	if (aquery->FieldByName("name")->AsAnsiString == "deletestack")
	{
		chdeletestack->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	//退货率计算时间
	if (aquery->FieldByName("name")->AsAnsiString == "rkbenqituihuolv")
	{
		edmonth->Text = aquery->FieldByName("bk")->AsAnsiString ;
	}
	//修改单头
	if (aquery->FieldByName("name")->AsAnsiString == "rkusechange")
	{
		cbrkusechange->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	//上次预计零售折扣
	if (aquery->FieldByName("name")->AsAnsiString == "lastyjlsdiscount")
	{
		cblastyjlsdiscount->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	//入库重复录入提示
	if (aquery->FieldByName("name")->AsAnsiString == "storagesametishi")
	{
		chstoragesametishi->Checked = aquery->FieldByName("value")->AsBoolean ;
	}




        	//出库重复录入提示
	if (aquery->FieldByName("name")->AsAnsiString == "cbsamerkts")
	{
		cbsamerkts->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
        	//出库允许重复录入
	if (aquery->FieldByName("name")->AsAnsiString == "cbsamerkyx")
	{
		cbsamerkyx->Checked = aquery->FieldByName("value")->AsBoolean ;
	}

	//地址
	/*if (aquery->FieldByName("name")->AsAnsiString == "rkaddress")
	{
		edrkaddress->Text = aquery->FieldByName("bk")->AsAnsiString ;
	}
	//抬头
	if (aquery->FieldByName("name")->AsAnsiString == "rkprinttitle")
	{
		edrkprinttitle->Text = aquery->FieldByName("bk")->AsAnsiString ;
	}
	//联系人
	if (aquery->FieldByName("name")->AsAnsiString == "rkcontact")
	{
		edrkcontact->Text = aquery->FieldByName("bk")->AsAnsiString ;
	}
	//电话
	if (aquery->FieldByName("name")->AsAnsiString == "rktel")
	{
		edrktel->Text = aquery->FieldByName("bk")->AsAnsiString ;
	}  */
	//退货监管
	if (aquery->FieldByName("name")->AsAnsiString == "rktuihuoguanli")
	{
		chrktuihuoguanli->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	//入库退货默认周期
	if (aquery->FieldByName("name")->AsAnsiString == "tkmouth")
	{
		edtkmouth->Text = aquery->FieldByName("bk")->AsAnsiString ;
	}
	//出库优先
	if (aquery->FieldByName("name")->AsAnsiString == "chuohuoyouxian")
	{
		rg->ItemIndex = aquery->FieldByName("bk")->AsInteger -1;
	}
	//附加条码自动生成
	if (aquery->FieldByName("name")->AsAnsiString == "crtuserbarcode")
	{
		chcrtuserbarcode->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
        //采购入库提醒
        if (aquery->FieldByName("name")->AsAnsiString =="caigoucayi") {
          cbcaigoucayi->Checked = aquery->FieldByName("value")->AsBoolean ;
        }
                    //rukucaigoudiscount
       if (aquery->FieldByName("name")->AsAnsiString =="rukucaigoudiscount") {
          cbcaigoudiscount->Checked = aquery->FieldByName("value")->AsBoolean ;
        }
        //非省代
        if (aquery->FieldByName("name")->AsAnsiString =="cbrukufeishendaicaigou") {
          cbrukufeishendaicaigou->Checked = aquery->FieldByName("value")->AsBoolean ;
        }                                                              // cbrukufeishendaicaigou
       //区分客户和供应商


       if (aquery->FieldByName("name")->AsAnsiString =="Qufenclient" ) {
          cbqfclient->Checked = aquery->FieldByName("value")->AsBoolean ;
       }
        if (aquery->FieldByName("name")->AsAnsiString =="Qufensupplier" ) {
          cbqfsupplier->Checked = aquery->FieldByName("value")->AsBoolean ;
       }

	aquery->Next();
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmstoragebsset::cblastyjpxClick(TObject *Sender)
{
	if (cblastyjpx->Checked) {
		cbadddot->Checked = false;
	}
	else
	{
		cbadddot->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmstoragebsset::cbadddotClick(TObject *Sender)
{
	if (cbadddot->Checked) {
		cblastyjpx->Checked = false;
	}
	else
	{
    	cblastyjpx->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmstoragebsset::FormClose(TObject *Sender, TCloseAction &Action)

{
	Action = caFree;
}
//---------------------------------------------------------------------------


void __fastcall Tfrmstoragebsset::sbsettuihuozhouqiClick(TObject *Sender)
{
//设置退货周期
   Tfrmtuihuoset *frm = new Tfrmtuihuoset(Application,fcon,fstgid);
   frm->ShowModal();
   delete frm;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmstoragebsset::sbsetClick(TObject *Sender)
{
//更新
     int index;
     AnsiString sql;
     index = cbyouxian->ItemIndex;

      switch (cbtuihuo->ItemIndex)
      {
          case 0:
                 sql = "update sys_bsset set bk = '" + IntToStr(index) + "' where name = 'rukuzhouqisupplier'";
                 break;
          case 1:
                 sql = "update sys_bsset set bk = '" + IntToStr(index)  + "' where name = 'rukuzhouqiclass'";
                 break;
          case 2:
                 sql = "update sys_bsset set bk = '" + IntToStr(index)  + "' where name = 'rukuzhouqitongyi'";
                 break;
          default:
          break;

      }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
}
//---------------------------------------------------------------------------

