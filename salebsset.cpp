//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "salebsset.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzCmboBx"
#pragma resource "*.dfm"
Tfrmsalebsset *frmsalebsset;
//---------------------------------------------------------------------------
__fastcall Tfrmsalebsset::Tfrmsalebsset(TComponent* Owner,TADOConnection* con)
	: TForm(Owner)
{
   aquery->Connection = con;
   qryretairange->Connection = con;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsalebsset::sbokClick(TObject *Sender)
{
   AnsiString sql,bk;
   int bit,defaultdiscount;
   //优先级别判断
   if ((cb1->ItemIndex == cb2->ItemIndex ) || (cb1->ItemIndex == cb3->ItemIndex) ||
	   (cb1->ItemIndex == cb4->ItemIndex ) || (cb2->ItemIndex == cb3->ItemIndex) ||
	   (cb2->ItemIndex == cb4->ItemIndex ) || (cb3->ItemIndex == cb4->ItemIndex ) ||
	   (cb1->ItemIndex == cb5->ItemIndex ) || (cb2->ItemIndex == cb5->ItemIndex ) ||
	   (cb3->ItemIndex == cb5->ItemIndex ) || (cb4->ItemIndex == cb5->ItemIndex )  ||
           (cb1->ItemIndex == cb6->ItemIndex)  || (cb2->ItemIndex == cb6->ItemIndex )  ||
           (cb3->ItemIndex == cb6->ItemIndex ) || (cb4->ItemIndex == cb6->ItemIndex ) ||
           (cb5->ItemIndex == cb6->ItemIndex )
           ) {
		ShowMsg(Handle ,"同一打折方式不能同时被选择！",0);
		return;
   }
   int id;
	try {
		id = (int)(cb1->Items->Objects[cb1->ItemIndex]);
	} catch (...) {
		ShowMsg(this->Handle,"请选择正确的第一级打折方式！",3);
		return;
	}

	try {
		id = (int)(cb2->Items->Objects[cb2->ItemIndex]);
	} catch (...) {
		ShowMsg(this->Handle,"请选择正确的第二级打折方式！",3);
		return;
	}

	try {
		id = (int)(cb3->Items->Objects[cb3->ItemIndex]);
	} catch (...) {
		ShowMsg(this->Handle,"请选择正确的第三级打折方式！",3);
		return;
	}

	try {
		id = (int)(cb4->Items->Objects[cb4->ItemIndex]);
	} catch (...) {
		ShowMsg(this->Handle,"请选择正确的第四级打折方式！",3);
		return;
	}

	try {
		id = (int)(cb5->Items->Objects[cb5->ItemIndex]);
	} catch (...) {
		ShowMsg(this->Handle,"请选择正确的第五级打折方式！",3);
		return;
	}
        try {
		id = (int)(cb6->Items->Objects[cb6->ItemIndex]);
	} catch (...) {
		ShowMsg(this->Handle,"请选择正确的第六级打折方式！",3);
		return;
	}
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
   //默认批销折扣
   try {
		defaultdiscount = StrToFloat(eddefaultdiscount->Text);
   } catch (...) {

                ShowMsg(Handle ,"请输入正确的折扣！",0);
		return;
   }
   if (defaultdiscount > 100) {

                ShowMsg(Handle ,"折扣不能大于100！",0);
		return;
   }
   if (defaultdiscount < 0) {

                ShowMsg(Handle ,"折扣不能小于0！",0);
		return;
   }
   bk = "0";
   if (bit > 0) {
		bk = bk + ".";
		for (int i = 0; i < bit; i++) {
			bk = bk + "0";
		}
   }
   sql = "update sys_bsset set bk = '" + bk + "' where name = 'salexiaoshudian'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();

   sql = "update sys_bsset set bk = '1' where id = " + IntToStr((int)(cb1->Items->Objects[cb1->ItemIndex])) ;
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   sql = "update sys_bsset set bk = '2' where id = " + IntToStr((int)(cb2->Items->Objects[cb2->ItemIndex])) ;
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   sql = "update sys_bsset set bk = '3' where id = " + IntToStr((int)(cb3->Items->Objects[cb3->ItemIndex])) ;
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   sql = "update sys_bsset set bk = '4' where id = " + IntToStr((int)(cb4->Items->Objects[cb4->ItemIndex])) ;
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   sql = "update sys_bsset set bk = '5' where id = " + IntToStr((int)(cb5->Items->Objects[cb5->ItemIndex])) ;
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   sql = "update sys_bsset set bk = '6' where id = " + IntToStr((int)(cb6->Items->Objects[cb6->ItemIndex])) ;
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();


   //是否允许负库存输入
   if (cbbear->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'bear'";
   }
   else
   {
       sql = "update sys_bsset set value = 0 where name = 'bear'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //批销历史明细
   if (cbwosalehistory->Checked ) {
		sql = "update sys_bsset set value = 1,bk = '" + edwosaleday->Text + "' where name = 'wosaleday'";
   }
   else
   {
		sql = "update sys_bsset set value = 0,bk = '" + edwosaleday->Text + "' where name = 'wosaleday'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //当前客户结/欠款情况显示
   if (cbcheckedview->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'checkedview'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'checkedview'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //是否允许无销售退货
   if (cbwosalereturn->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'wosalereturn'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'wosalereturn'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //批销跟踪上次折扣
   if (chpxlastdiscount->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'pxlastdiscount'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'pxlastdiscount'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //低于成本折扣提醒
   if (cblowcostalter->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'lowcostalter'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'lowcostalter'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //低于成本折扣是否发货
   if (cblowcostenable->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'lowcostenable'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'lowcostenable'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //低于正常折扣提醒
   if (cblownormalalter->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'lownormalalter'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'lownormalalter'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //低于正常折扣是否发货
   if (cblownormalenable->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'lownormalenable'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'lownormalenable'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //允许修改折扣的设置
   if (cbwsaledisscountchange->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'WsalelDiscountChange'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'WsalelDiscountChange'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //批销退货监管
   if (cbpxtuihuocatch->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'pxtuihuocatch'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'pxtuihuocatch'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //现场收款是否可用
   if (chxianchangrecive->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'xianchangrecive'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'xianchangrecive'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //批销明细显示所以客户历史记录
   if (cbpxallclientdetail->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'pxallclientdetail'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'pxallclientdetail'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //批销删行密码是否启用
   if (cbpxdeleteusepassword->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'pxdeleteusepassword'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'pxdeleteusepassword'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //批销查单密码是否启用
   if (cbpxfindusepassword->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'pxfindusepassword'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'pxfindusepassword'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //批销退货密码是否启用
   if (cbpxtuihuousepassword->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'pxtuihuousepassword'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'pxtuihuousepassword'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //无库存销售
   if (cbpxnobkinfosale->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'pxnobkinfosale'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'pxnobkinfosale'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //无库存批销退货
   if (cbpxnobkinfotuihuo->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'pxnobkinfotuihuo'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'pxnobkinfotuihuo'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //批销打印备注
   /*if (cbpxprintbk->Checked ) {
		sql = "update sys_bsset set value = 1,bk = '" + edpxprintbk->Text + "' where name = 'pxprintbk'";
   }
   else
   {
		sql = "update sys_bsset set value = 0,bk = '" + edpxprintbk->Text + "' where name = 'pxprintbk'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL(); */
   //批销默认折扣
   if (cbpxdefaultdiscount->Checked ) {
		sql = "update sys_bsset set value = 1,boundmax = " + eddefaultdiscount->Text + " where name = 'pxdefaultdiscount'";
   }
   else
   {
		sql = "update sys_bsset set value = 0,boundmax = '" + eddefaultdiscount->Text + "' where name = 'pxdefaultdiscount'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //无库存批销退货
   if (chnokucunpxth->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'nokucunpxth'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'nokucunpxth'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //退货率计算时间
   if (edmonth->Text == "" ) {
		edmonth->Text == "0" ;
   }
   sql = "update sys_bsset set bk = " + edmonth->Text + "where name = 'pxbenqituihuolv'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //批销修改单头密码是否启用
   if (chpxusechange->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'pxusechange'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'pxusechange'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //重复录入提示
   if (chwsalesametishi->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'wsalesametishi'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'wsalesametishi'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();

   //客户加点折扣
   if (chpxclientadddot->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'pxclientadddot'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'pxclientadddot'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();

   //入库预计批销折扣
   if (chpxrkyjdiscount->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'pxrkyjdiscount'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'pxrkyjdiscount'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();

   //附加折扣
   if (chpxaddcost->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'pxaddcost'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'pxaddcost'";
   }

   AnsiString sql2;
 //  批销退货允许重复录入

   if (cbpxtuihuo->Checked) {
       sql2 = "update sys_bsset set value = 1 where name = 'wsalesametuihuotishi';";
   }else
   {

      sql2 = "update sys_bsset set value = 0 where name = 'wsalesametuihuotishi';";

   }



   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->SQL->Add(sql2);
   aquery->ExecSQL();



   //发货打印抬头
   /*sql = "update sys_bsset set bk = '" + edwsprinttitle->Text.Trim() + "' where name = 'wsprinttitle'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //联系人
   sql = "update sys_bsset set bk = '" + edwscontact->Text.Trim() + "' where name = 'wscontact'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //电话
   sql = "update sys_bsset set bk = '" + edwstel->Text.Trim() + "' where name = 'wstel'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //地址
   sql = "update sys_bsset set bk = '" + edwsaddress->Text.Trim() + "' where name = 'wsaddress'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();   */
   //打折方式
   if (RadioGroup1->ItemIndex == 0 ) {
		sql = "update sys_bsset set value = 1 where name = 'pxpriordiscount'";
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->ExecSQL();
		sql = "update sys_bsset set value = 0 where name = 'pxmindiscount'";
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->ExecSQL();
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'pxpriordiscount'";
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->ExecSQL();
		sql = "update sys_bsset set value = 1 where name = 'pxmindiscount'";
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->ExecSQL();
   }
   ShowMsg(Handle ,"业务设置成功！",3);
   Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsalebsset::FormShow(TObject *Sender)
{
	Readydata();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsalebsset::sbcancelClick(TObject *Sender)
{
   Close();
}
void Tfrmsalebsset::Readydata()
{
  String sql= "select * from sys_bsset",bk;
  int bit;
  aquery->Close();
  aquery->SQL->Clear();
  aquery->SQL->Add(sql);
  aquery->Open();
  while (!aquery->Eof)
  {
	if (aquery->FieldByName("name")->AsAnsiString == "bear")
	{
		cbbear->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "wosaleday" ) {
		cbwosalehistory->Checked = aquery->FieldByName("value")->AsBoolean ;
		edwosaleday->Text = aquery->FieldByName("bk")->AsString ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "checkedview" ) {
		cbcheckedview->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "wosalereturn" ) {
		cbwosalereturn->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "lowcostalter" ) {
		cblowcostalter->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "lowcostenable" ) {
		cblowcostenable->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "lownormalalter" ) {
		cblownormalalter->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "lownormalenable" ) {
    	cblownormalenable->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "pxlastdiscount" ) {
		chpxlastdiscount->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "WsalelDiscountChange" ) {
		cbwsaledisscountchange->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "pxtuihuocatch" ) {
		cbpxtuihuocatch->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "salexiaoshudian" ) {
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
	if (aquery->FieldByName("name")->AsAnsiString == "xianchangrecive" ) {
		chxianchangrecive->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "pxallclientdetail" ) {
		cbpxallclientdetail->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "pxdeleteusepassword" ) {
		cbpxdeleteusepassword->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "pxfindusepassword" ) {
		cbpxfindusepassword->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "pxtuihuousepassword" ) {
		cbpxtuihuousepassword->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "pxnobkinfosale" ) {
		cbpxnobkinfosale->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "pxnobkinfotuihuo" ) {
		cbpxnobkinfotuihuo->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "pxusechange" ) {
		chpxusechange->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	//批销打印备注
	/*if (aquery->FieldByName("name")->AsAnsiString == "pxprintbk" ) {
		cbpxprintbk->Checked = aquery->FieldByName("value")->AsBoolean ;
		edpxprintbk->Text = aquery->FieldByName("bk")->AsString ;
	}   */
	//批销默认折扣
	if (aquery->FieldByName("name")->AsAnsiString == "pxdefaultdiscount" ) {
		cbpxdefaultdiscount->Checked = aquery->FieldByName("value")->AsBoolean ;
		eddefaultdiscount->Text = aquery->FieldByName("boundmax")->AsString ;
	}
	//批销打折方式
	if (aquery->FieldByName("name")->AsAnsiString == "pxpriordiscount" ) {
		if (aquery->FieldByName("value")->AsBoolean) {
			RadioGroup1->ItemIndex = 0;
		}
		else
		{
        	RadioGroup1->ItemIndex = 1;
		}
	}
	//无库存批销退货
	if (aquery->FieldByName("name")->AsAnsiString == "nokucunpxth" ) {
		chnokucunpxth->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	//重复录入提示
	if (aquery->FieldByName("name")->AsAnsiString == "wsalesametishi" ) {
		chwsalesametishi->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
        if (aquery->FieldByName("name")->AsAnsiString == "wsalesametuihuotishi" ) {
		cbpxtuihuo->Checked = aquery->FieldByName("value")->AsBoolean ;
	}

	//退货率计算时间
	if (aquery->FieldByName("name")->AsAnsiString == "pxbenqituihuolv")
	{
		edmonth->Text = aquery->FieldByName("bk")->AsAnsiString ;
	}

	//客户 加点折扣
	if (aquery->FieldByName("name")->AsAnsiString == "pxclientadddot" ) {
		chpxclientadddot->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	//入库预计批销折扣
	if (aquery->FieldByName("name")->AsAnsiString == "pxrkyjdiscount" ) {
		chpxrkyjdiscount->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	//附加折扣
	if (aquery->FieldByName("name")->AsAnsiString == "pxaddcost")
	{
		chpxaddcost->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	 aquery->Next();

  }
  //优先级别
  sql = "select id,case when name = 'pxlastdiscount' then '跟踪上次折扣' "
		" when name = 'pxdefaultdiscount' then '批销默认折扣' when name = 'pxrkyjdiscount' then '入库预计批销折扣' "
		" when name = 'pxaddcost' then '附加折扣' when name = 'pxclientadddot' then '客户加点折扣'  when name ='pxclientdis' then '客户单品折扣' end as name,bk "
		" from sys_bsset where name in('pxlastdiscount','pxdefaultdiscount','pxrkyjdiscount','pxaddcost','pxclientadddot','pxclientdis') order by bk";
  aquery->Close();
  aquery->SQL->Clear();
  aquery->SQL->Add(sql);
  aquery->Open();
  aquery->First();
  while (!aquery->Eof )
  {
	cb1->AddItem(aquery->FieldByName("name")->AsAnsiString ,(TObject*)aquery->FieldByName("id")->AsInteger );
	cb2->AddItem(aquery->FieldByName("name")->AsAnsiString ,(TObject*)aquery->FieldByName("id")->AsInteger );
	cb3->AddItem(aquery->FieldByName("name")->AsAnsiString ,(TObject*)aquery->FieldByName("id")->AsInteger );
	cb4->AddItem(aquery->FieldByName("name")->AsAnsiString ,(TObject*)aquery->FieldByName("id")->AsInteger );
	cb5->AddItem(aquery->FieldByName("name")->AsAnsiString ,(TObject*)aquery->FieldByName("id")->AsInteger );
        cb6->AddItem(aquery->FieldByName("name")->AsAnsiString ,(TObject*)aquery->FieldByName("id")->AsInteger );
	aquery->Next();
  }

  aquery->First();
  cb1->ItemIndex = cb1->Items->IndexOfObject((TObject*)aquery->FieldByName("id")->AsInteger );
  aquery->Next();
  cb2->ItemIndex = cb2->Items->IndexOfObject((TObject*)aquery->FieldByName("id")->AsInteger );
  aquery->Next();
  cb3->ItemIndex = cb3->Items->IndexOfObject((TObject*)aquery->FieldByName("id")->AsInteger );
  aquery->Next();
  cb4->ItemIndex = cb4->Items->IndexOfObject((TObject*)aquery->FieldByName("id")->AsInteger );
  aquery->Next();
  cb5->ItemIndex = cb5->Items->IndexOfObject((TObject*)aquery->FieldByName("id")->AsInteger );
  aquery->Next();
  cb6->ItemIndex = cb6->Items->IndexOfObject((TObject*)aquery->FieldByName("id")->AsInteger );
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsalebsset::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree;
}
//---------------------------------------------------------------------------


void __fastcall Tfrmsalebsset::eddefaultdiscountKeyPress(TObject *Sender, wchar_t &Key)

{
	if ((Key < '0' || Key > '9') && (Key != '\b') && (Key != '.') && (Key != '\r') ) {
		Key = NULL;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsalebsset::cbpxtuihuocatchClick(TObject *Sender)
{
	if (cbpxtuihuocatch->Checked ) {
		cbwosalereturn->Checked = false;
	}
	else
	{
    	cbwosalereturn->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsalebsset::etdotExit(TObject *Sender)
{
    if (StrToInt(etdot->Text)>3 ) {
       ShowMsg(Handle ,"小数点最多2位！",3);
       etdot->SetFocus();
       etdot->Text = "2";
    }
}
//---------------------------------------------------------------------------

