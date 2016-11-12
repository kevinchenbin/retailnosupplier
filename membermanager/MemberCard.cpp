//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MemberCard.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "RzCmboBx"
#pragma resource "*.dfm"
TfrmMemberCard *frmMemberCard;
//---------------------------------------------------------------------------
__fastcall TfrmMemberCard::TfrmMemberCard(TComponent* Owner,int mdole,String *ASMemberInfo,TADOConnection *cn)
	: TForm(Owner)
{
	m_modle = mdole;
	ASMemInfo = ASMemberInfo;
	quMemberCard->Connection  = cn;
	quMemberType->Connection = cn;
	ADOCommand1->Connection = cn;
	quMemberInfo->Connection = cn;
	tdtbirthday->Date = Date();
	tdtbirthday->Date = Date();
	if (mdole == 2) {
        edpassword->Enabled = false;

	}else {

         Label8->Visible = false;
        editjifen->Visible=false;
        }
	dtpyouxiao->Date = Date() + 50*365;
}
//---------------------------------------------------------------------------
//会员名
void __fastcall TfrmMemberCard::edtnameChange(TObject *Sender)
{
	name =  edtname->Text;
}
//---------------------------------------------------------------------------
//会员卡号
void __fastcall TfrmMemberCard::edtcardIDChange(TObject *Sender)
{
	cardID =  edtcardID->Text;
}
//---------------------------------------------------------------------------
//会员性别
void __fastcall TfrmMemberCard::edtsexChange(TObject *Sender)
{
	sex =  cbsex->Text ;
	if (sex == "男") {
		memsex = 0;     //0为男性
	}
	else
	{
		memsex = 1;     //1为女性
	}
}
//---------------------------------------------------------------------------
//会员生日//会员类型
//会员电话
void __fastcall TfrmMemberCard::edttelephoneChange(TObject *Sender)
{
	telephone =  edttelephone->Text;
}
//---------------------------------------------------------------------------
//会员手机
void __fastcall TfrmMemberCard::edtmobileChange(TObject *Sender)
{
	mobile =  edtmobile->Text;
}
//---------------------------------------------------------------------------
//会员地址
void __fastcall TfrmMemberCard::edtaddressChange(TObject *Sender)
{
	address =  edtaddress->Text;
}
//---------------------------------------------------------------------------
//会员地址邮编
void __fastcall TfrmMemberCard::edtpostalcodeChange(TObject *Sender)
{
	postalcode =  edtpostalcode->Text;
}
//---------------------------------------------------------------------------
//折扣
void __fastcall TfrmMemberCard::edtdiscountChange(TObject *Sender)
{
	discount =  edtdiscount->Text;
}

//---------------------------------------------------------------------------

//保存
void __fastcall TfrmMemberCard::BtnSaveClick(TObject *Sender)
{
	int cardsnlen = 0;
	AnsiString sql;
	sex =  cbsex->Text ;
        savebt=false;
	if (sex == "男") {
		memsex = 0;     //0为男性
	}
	else
	{
		memsex = 1;     //1为女性
	}
	if (edCardCast->Text == "") {
		edCardCast->Text = "0";
	}
	try {
		float cardcast = StrToFloat(edCardCast->Text);
	} catch (...) {
		ShowMsg(Handle ,"请输入正确的购卡金额！",3);
		return;
	}
	if (edtname->Text == "") {
		ShowMsg(Handle ,"会员名字不能为空！",3);
		return;
	}
	else if (edityouxiao->Text=="") {
		ShowMsg(Handle ,"会员卡有效时间不能为空！",3);
		return;
	}
	else
	{
		if (cardID == "") {
			ShowMsg(Handle ,"会员卡号不能为空！",3);
			return;
		}
		else
		{
			cardsnlen =  cardID.Length();
		      	if (cardsnlen== 0) {
			  	ShowMsg(Handle ,"请输入会员卡号！",3);
			 	return;
		       	}
			else
			{
				if (quMemberInfo->Active == true) {
                	quMemberInfo->Active = false;
				}
				if (m_modle == 1 ) {     //添加会员信息
					AnsiString sql = "select * from CUST_MemberInfo where CardID = '" ;
					sql = sql +  cardID + "'";
					quMemberInfo->Close();
					quMemberInfo->SQL->Clear();
					quMemberInfo->SQL->Add(sql);
					quMemberInfo->Open();

					if (quMemberInfo->IsEmpty() ) {
						if (quMemberInfo->State != dsInsert ) {
							quMemberInfo->Append();
						}
						if (quMemberInfo->State == dsInsert)
						{
							quMemberInfo->FieldByName("Name")->AsString = edtname->Text;
							quMemberInfo->FieldByName("Birthday")->AsDateTime = tdtbirthday->DateTime;
							quMemberInfo->FieldByName("CardID")->AsString = edtcardID->Text;
							quMemberInfo->FieldByName("MemberType")->AsInteger =  memtype;
							quMemberInfo->FieldByName("Sex")->AsInteger = memsex;
							quMemberInfo->FieldByName("Tel")->AsString = edttelephone->Text;
							quMemberInfo->FieldByName("Mobile")->AsString = edtmobile->Text;
							quMemberInfo->FieldByName("Address")->AsString = edtaddress->Text;
							quMemberInfo->FieldByName("PostalCode")->AsString = edtpostalcode->Text;
							quMemberInfo->FieldByName("CardSN")->AsString = edtcardID->Text;
							quMemberInfo->FieldByName("CardType")->AsInteger = rg->ItemIndex ;
							quMemberInfo->FieldByName("bircard")->AsString = edbircard->Text;
							quMemberInfo->FieldByName("CardCast")->AsString = edCardCast->Text ;
							quMemberInfo->FieldByName("PassWord")->AsString = edpassword->Text.Trim();
							quMemberInfo->FieldByName("youxiaodate")->AsDateTime= dtpyouxiao->Date ;
                                                       quMemberInfo->FieldByName("stgidex")->AsInteger =stgid;
							if (ShowMsg(Handle ,"您确认添加该会员！",1)==1)
							{
								quMemberInfo->Post();
                                                                savebt=true;
								this->Close();
							}
						}
					}
					else
					{
						ShowMsg(Handle ,"该会员卡号已经存在！",3);
					}

				}
				else {    //修改会员信息
					AnsiString sql = "select ID,createdate from CUST_MemberInfo where ID = " ;
					sql = sql +  ASMemInfo[0];
					quMemberInfo->Close();
					quMemberInfo->SQL->Clear();
					quMemberInfo->SQL->Add(sql);
					quMemberInfo->Open();
					if (!quMemberInfo->IsEmpty() ) {
						sql = "update CUST_MemberInfo set CardType = " + IntToStr(rg->ItemIndex) ;
						sql = sql + ", Name = '"+name+"',Birthday = '" + DateToStr(tdtbirthday->Date)  + "',MemberType = " +memtype +",Sex = "
						+memsex +",CardID = '" +cardID +"',Tel = '" + telephone +"',Mobile ='" +mobile + "',CardCast = " + edCardCast->Text + ",bircard = '" + edbircard->Text+"'" ;

                                                if (dtpyouxiao->Date>Now() ) {   //有效日期大于今天
                                                   sql=sql+" ,Available=1";
												}
												if (editjifen->Text=="") {
                                                    editjifen->Text="0";
												}
						sql = sql + " ,Address = '" + address +"',PostalCode = '" + postalcode +"',youxiaodate='"+DateToStr(dtpyouxiao->Date) +"',memberdot="+editjifen->Text+" where id = " + ASMemInfo[0];
							try{

								if(ShowMsg(Handle ,"您确认修改该会员！",1)==1)
								{
									quMemberInfo->Close();
									quMemberInfo->SQL->Clear();
									quMemberInfo->SQL->Add(sql);
									quMemberInfo->ExecSQL();
                                                                        savebt=true;
									this->Close();
								}
							}
							catch(Exception &E)
							{
								ShowMsg(Handle ,"此数据不能更新！",3);
							}

					}
					else
					{
						ShowMsg(Handle ,"更新的会员不存在！",3);
					}
				}
			}
		}
	}
}
//---------------------------------------------------------------------------
//退出
void __fastcall TfrmMemberCard::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

//初始界面显示
void __fastcall TfrmMemberCard::FormShow(TObject *Sender)
{


//------查询会员的类型添加到会员类型的下拉列表中
	AnsiString sql = "select IDType,Type as T from cust_membertype order by discount desc ";  //查询会员的类别
	quMemberType->Close();
	quMemberType->SQL->Clear();
	quMemberType->SQL->Add(sql);
	quMemberType->Open();
	quMemberType->First();
	while(!quMemberType->Eof )
	{
		cbtype->AddItem(quMemberType->FieldByName("T")->AsAnsiString,(TObject*)quMemberType->FieldByName("IDType")->AsInteger);
		quMemberType->Next();
	}
	cbtype->ItemIndex = 0;
//------添加性别的属性
	cbsex->AddItem("男",(TObject*)0) ;  //对应的整数值为0
	cbsex->AddItem("女",(TObject*)1); //对应的整数值为1
	cbsex->Text = "男";
	memtype = int(cbtype->Items->Objects[cbtype->ItemIndex]);
//------折扣的初始显示
	sql = "select IDType,discount from cust_membertype where IDType = ";
	sql = sql +  memtype;
	quMemberType->Close();
	quMemberType->SQL->Clear();
	quMemberType->SQL->Add(sql);
	quMemberType->Open();
	edtdiscount->Text =  quMemberType->FieldByName("discount")->AsString + "%";
	cbtype->ItemIndex = 0;
//------修改时画面的初始值设定
	if (m_modle == 2) {
        edtcardID->Enabled = false;
		edtname->Text =  ASMemInfo[1]; // 会员名
		tdtbirthday->DateTime = StrToDateTime(ASMemInfo[2]); // 会员生日
		cbsex->Text = ASMemInfo[3];    // 会员性别
		edttelephone->Text =  ASMemInfo[4]; // 会员电话
		edtmobile->Text =  ASMemInfo[5];  // 会员手机
		edtaddress->Text = ASMemInfo[6];  // 会员地址
		edtpostalcode->Text =  ASMemInfo[7];  // 会员地址邮编
		edtcardID->Text =  ASMemInfo[8];  // 会员卡号
		cbtype->ItemIndex = cbtype->Items->IndexOfObject((TObject*)StrToInt(ASMemInfo[11]));  //会员类型
		edCardCast->Text = ASMemInfo[12];
		rg->ItemIndex = StrToInt(ASMemInfo[13]);
		edbircard->Text = ASMemInfo[14];
		dtpyouxiao->DateTime = StrToDateTime(ASMemInfo[15]);
                editjifen->Text = ASMemInfo[16];
		//-----折扣的显示
		memtype = int(cbtype->Items->Objects[cbtype->ItemIndex]);
		sql = "select IDType,discount from cust_membertype where IDType = ";
		sql = sql + memtype;
		quMemberType->Close();
		quMemberType->SQL->Clear();
		quMemberType->SQL->Add(sql);
		quMemberType->Open();
		edtdiscount->Text =  quMemberType->FieldByName("discount")->AsString + "%";
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberCard::edtnameKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
        if (edtname->Text == "") {
			ShowMsg(Handle ,"会员名字不能为空！",3);
			return;
		}
		cbsex->SetFocus();

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberCard::edtcardIDKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	String cardID =  edtcardID->Text ;
	if (Key == VK_RETURN) {
		if (cardID == "") {
			ShowMsg(Handle ,"会员卡号不能为空！",3);
			return;
		}
		else
		{
			int cardsnlen =  cardID.Length();
		       //	if (cardsnlen!= 13) {
			 //	ShowMsg(Handle ,"请输入13位会员卡号！",3);
			//	return;
		       //	}
		}
		edtname->SetFocus();
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmMemberCard::edttelephoneKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
    	edtpostalcode->SetFocus();
	}
}
//---------------------------------------------------------------------------



void __fastcall TfrmMemberCard::edtpostalcodeKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
        BtnSave->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberCard::edCardCastKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
		tdtbirthday->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberCard::edpasswordKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
        if (rg->ItemIndex==0) {
         edCardCast->SetFocus();
        }else{
          edtdiscount->SetFocus();
        }

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberCard::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F4) {
		BtnSave->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==81  ) {
		BtnExit->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberCard::edbircardKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
		edtaddress->SetFocus();
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmMemberCard::edityouxiaoExit(TObject *Sender)
{
	if (edityouxiao->Text == "0") {
		ShowMsg(Handle ,"有效期不能为0年！",3);
		edityouxiao->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberCard::rgClick(TObject *Sender)
{
	if (rg->ItemIndex == 1) {    //选择购卡
		edCardCast->Enabled = false;
	}else if (rg->ItemIndex == 0 ) {
		edCardCast->Enabled = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberCard::edCardCastKeyPress(TObject *Sender, wchar_t &Key)
          
{
	if ((Key < '0' || Key > '9')&& (Key != '.')&&(Key!='\b'))
	{
		Key   =   0;
		return   ;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberCard::cbtypeKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {

		if (m_modle == 1) {
			edpassword->SetFocus();
		}
		else
			edtdiscount->SetFocus();
	}

}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberCard::cbtypeSelect(TObject *Sender)
{
	type =  cbtype->Text  ;
//-----折扣的显示
	memtype = int(cbtype->Items->Objects[cbtype->ItemIndex]);
	AnsiString sql = "select IDType,discount from cust_membertype where IDType = ";
	sql = sql + memtype;
	quMemberType->Close();
	quMemberType->SQL->Clear();
	quMemberType->SQL->Add(sql);
	quMemberType->Open();
	edtdiscount->Text =  quMemberType->FieldByName("discount")->AsString + "%";
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberCard::ComboBox1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
		cbtype->SetFocus();
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmMemberCard::edtaddressKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
   if (Key == '\r') {
        BtnSave->Click();
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmMemberCard::edtdiscountKeyPress(TObject *Sender, wchar_t &Key)

{
   if (Key == VK_RETURN) {

   if (edCardCast->Enabled) {
       edCardCast->SetFocus();
   }else tdtbirthday->SetFocus();

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberCard::tdtbirthdayKeyPress(TObject *Sender, wchar_t &Key)

{
if (Key == VK_RETURN) {

		dtpyouxiao->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberCard::dtpyouxiaoKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        edttelephone->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberCard::edtmobileKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
        edbircard->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberCard::edtpostalcodeKeyPress(TObject *Sender, wchar_t &Key)

{
   	if (Key == VK_RETURN) {
        edtmobile->SetFocus();
	}
}
//---------------------------------------------------------------------------

