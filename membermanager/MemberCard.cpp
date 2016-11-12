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
//��Ա��
void __fastcall TfrmMemberCard::edtnameChange(TObject *Sender)
{
	name =  edtname->Text;
}
//---------------------------------------------------------------------------
//��Ա����
void __fastcall TfrmMemberCard::edtcardIDChange(TObject *Sender)
{
	cardID =  edtcardID->Text;
}
//---------------------------------------------------------------------------
//��Ա�Ա�
void __fastcall TfrmMemberCard::edtsexChange(TObject *Sender)
{
	sex =  cbsex->Text ;
	if (sex == "��") {
		memsex = 0;     //0Ϊ����
	}
	else
	{
		memsex = 1;     //1ΪŮ��
	}
}
//---------------------------------------------------------------------------
//��Ա����//��Ա����
//��Ա�绰
void __fastcall TfrmMemberCard::edttelephoneChange(TObject *Sender)
{
	telephone =  edttelephone->Text;
}
//---------------------------------------------------------------------------
//��Ա�ֻ�
void __fastcall TfrmMemberCard::edtmobileChange(TObject *Sender)
{
	mobile =  edtmobile->Text;
}
//---------------------------------------------------------------------------
//��Ա��ַ
void __fastcall TfrmMemberCard::edtaddressChange(TObject *Sender)
{
	address =  edtaddress->Text;
}
//---------------------------------------------------------------------------
//��Ա��ַ�ʱ�
void __fastcall TfrmMemberCard::edtpostalcodeChange(TObject *Sender)
{
	postalcode =  edtpostalcode->Text;
}
//---------------------------------------------------------------------------
//�ۿ�
void __fastcall TfrmMemberCard::edtdiscountChange(TObject *Sender)
{
	discount =  edtdiscount->Text;
}

//---------------------------------------------------------------------------

//����
void __fastcall TfrmMemberCard::BtnSaveClick(TObject *Sender)
{
	int cardsnlen = 0;
	AnsiString sql;
	sex =  cbsex->Text ;
        savebt=false;
	if (sex == "��") {
		memsex = 0;     //0Ϊ����
	}
	else
	{
		memsex = 1;     //1ΪŮ��
	}
	if (edCardCast->Text == "") {
		edCardCast->Text = "0";
	}
	try {
		float cardcast = StrToFloat(edCardCast->Text);
	} catch (...) {
		ShowMsg(Handle ,"��������ȷ�Ĺ�����",3);
		return;
	}
	if (edtname->Text == "") {
		ShowMsg(Handle ,"��Ա���ֲ���Ϊ�գ�",3);
		return;
	}
	else if (edityouxiao->Text=="") {
		ShowMsg(Handle ,"��Ա����Чʱ�䲻��Ϊ�գ�",3);
		return;
	}
	else
	{
		if (cardID == "") {
			ShowMsg(Handle ,"��Ա���Ų���Ϊ�գ�",3);
			return;
		}
		else
		{
			cardsnlen =  cardID.Length();
		      	if (cardsnlen== 0) {
			  	ShowMsg(Handle ,"�������Ա���ţ�",3);
			 	return;
		       	}
			else
			{
				if (quMemberInfo->Active == true) {
                	quMemberInfo->Active = false;
				}
				if (m_modle == 1 ) {     //��ӻ�Ա��Ϣ
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
							if (ShowMsg(Handle ,"��ȷ����Ӹû�Ա��",1)==1)
							{
								quMemberInfo->Post();
                                                                savebt=true;
								this->Close();
							}
						}
					}
					else
					{
						ShowMsg(Handle ,"�û�Ա�����Ѿ����ڣ�",3);
					}

				}
				else {    //�޸Ļ�Ա��Ϣ
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

                                                if (dtpyouxiao->Date>Now() ) {   //��Ч���ڴ��ڽ���
                                                   sql=sql+" ,Available=1";
												}
												if (editjifen->Text=="") {
                                                    editjifen->Text="0";
												}
						sql = sql + " ,Address = '" + address +"',PostalCode = '" + postalcode +"',youxiaodate='"+DateToStr(dtpyouxiao->Date) +"',memberdot="+editjifen->Text+" where id = " + ASMemInfo[0];
							try{

								if(ShowMsg(Handle ,"��ȷ���޸ĸû�Ա��",1)==1)
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
								ShowMsg(Handle ,"�����ݲ��ܸ��£�",3);
							}

					}
					else
					{
						ShowMsg(Handle ,"���µĻ�Ա�����ڣ�",3);
					}
				}
			}
		}
	}
}
//---------------------------------------------------------------------------
//�˳�
void __fastcall TfrmMemberCard::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

//��ʼ������ʾ
void __fastcall TfrmMemberCard::FormShow(TObject *Sender)
{


//------��ѯ��Ա��������ӵ���Ա���͵������б���
	AnsiString sql = "select IDType,Type as T from cust_membertype order by discount desc ";  //��ѯ��Ա�����
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
//------����Ա������
	cbsex->AddItem("��",(TObject*)0) ;  //��Ӧ������ֵΪ0
	cbsex->AddItem("Ů",(TObject*)1); //��Ӧ������ֵΪ1
	cbsex->Text = "��";
	memtype = int(cbtype->Items->Objects[cbtype->ItemIndex]);
//------�ۿ۵ĳ�ʼ��ʾ
	sql = "select IDType,discount from cust_membertype where IDType = ";
	sql = sql +  memtype;
	quMemberType->Close();
	quMemberType->SQL->Clear();
	quMemberType->SQL->Add(sql);
	quMemberType->Open();
	edtdiscount->Text =  quMemberType->FieldByName("discount")->AsString + "%";
	cbtype->ItemIndex = 0;
//------�޸�ʱ����ĳ�ʼֵ�趨
	if (m_modle == 2) {
        edtcardID->Enabled = false;
		edtname->Text =  ASMemInfo[1]; // ��Ա��
		tdtbirthday->DateTime = StrToDateTime(ASMemInfo[2]); // ��Ա����
		cbsex->Text = ASMemInfo[3];    // ��Ա�Ա�
		edttelephone->Text =  ASMemInfo[4]; // ��Ա�绰
		edtmobile->Text =  ASMemInfo[5];  // ��Ա�ֻ�
		edtaddress->Text = ASMemInfo[6];  // ��Ա��ַ
		edtpostalcode->Text =  ASMemInfo[7];  // ��Ա��ַ�ʱ�
		edtcardID->Text =  ASMemInfo[8];  // ��Ա����
		cbtype->ItemIndex = cbtype->Items->IndexOfObject((TObject*)StrToInt(ASMemInfo[11]));  //��Ա����
		edCardCast->Text = ASMemInfo[12];
		rg->ItemIndex = StrToInt(ASMemInfo[13]);
		edbircard->Text = ASMemInfo[14];
		dtpyouxiao->DateTime = StrToDateTime(ASMemInfo[15]);
                editjifen->Text = ASMemInfo[16];
		//-----�ۿ۵���ʾ
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
			ShowMsg(Handle ,"��Ա���ֲ���Ϊ�գ�",3);
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
			ShowMsg(Handle ,"��Ա���Ų���Ϊ�գ�",3);
			return;
		}
		else
		{
			int cardsnlen =  cardID.Length();
		       //	if (cardsnlen!= 13) {
			 //	ShowMsg(Handle ,"������13λ��Ա���ţ�",3);
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
		ShowMsg(Handle ,"��Ч�ڲ���Ϊ0�꣡",3);
		edityouxiao->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberCard::rgClick(TObject *Sender)
{
	if (rg->ItemIndex == 1) {    //ѡ�񹺿�
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
//-----�ۿ۵���ʾ
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

