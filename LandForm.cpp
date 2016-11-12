//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Dog.h"
#include "LandForm.h"
#include "global.h"
//#include "Stockalarm.h"
#include "Unit1.h"
#include <inifiles.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzBmpBtn"
#pragma resource "*.dfm"
#pragma resource "pdres.RES"
TfrmLand *frmLand;
//---------------------------------------------------------------------------
__fastcall TfrmLand::TfrmLand(TComponent* Owner)
	: TForm(Owner)
	, m_user(-1)
	, m_storage(-1)
	, m_master(-1)
{
	AnsiString constr;
	 AnsiString configfile;
         AnsiString v;
	  configfile =  ExtractFilePath(Application->ExeName) + "dbconfig" +  ".INI" ;
	  TIniFile *ini;
	   ini   = new    TIniFile(configfile);
	   dbServer = ini->ReadString("dbserver","Server","4e3");
	   UserName = ini->ReadString("dbserver","Username","sa");
	   Zhangtao = ini->ReadString("dbserver","Zhangtao ","默认帐套");
	   Provider = ini->ReadString("dbserver","Provider","SQLOLEDB.1");//
           v = ini->ReadString("dbserver","Version","0");
	   pd = ini->ReadString("dbserver","pd","");
	   delete ini;
           version = StrToInt(v);
//read dog
        TPngImage * imag;
      	imag = new TPngImage();
        imag->LoadFromResourceName((unsigned int)HInstance,"login");

      	Image1->Picture->Graphic = imag;

         TPngImage * imag2;
	imag2 = new TPngImage();

		imag2->LoadFromResourceName((unsigned int)HInstance,"pwchan");

	Image2->Picture->Graphic = imag2;

	  AnsiString DogInfo;

		  if (version==0) {     //零售版

			  ReadDog *Dog = new ReadDog();

		   //	 ;//	FindSeier

	   if (0!= Dog->OpenDog())
	   {
		 MessageBoxA(0,"加密狗ASIC芯片数据校验错误！","错误",MB_ICONERROR);

		 Dog->CloseDog();
		  delete Dog;
		 Application->Terminate();

		 return;

	   }

		int DevNumberNew= Dog->ReadDevNumber();
	   if (DevNumber != DevNumberNew)
	   {
		if (!Dog->FindSeier()) {


		 if ( DevNumberNew=1128550468) {
			  MessageBoxA(0,"加密狗ASIC芯片数据校验错误！","错误",MB_ICONERROR);
			  Dog->CloseDog();
			  delete Dog;
			  return ;    }
		   else
			  {
				 MessageBoxA(0,"无效的加密狗！请与管理员联系","错误",MB_ICONERROR);
				 Dog->CloseDog();
				 delete Dog;
				 return;

			  }
		 }
	   } else
		 {
		   DogInfo =  Dog->ReadDogInfo();
		 Dog->CloseDog();
		  delete Dog;

		 }
         Dog->CloseDog();
		  delete Dog;
		DogInfo="$z@chf@UY4!0P%we";
	   }


	   //	//   }else
	   //	   {
	  // /
	   //		DogInfo="Legend123";

	  //	   }
		 // }
	   //	 DogInfo="pdz@c3$9w4!0tb19";
		  //	DogInfo="Legend123";
	  // constr = "Provider=" + Provider +";Password=" + DogInfo + ";Persist Security Info=True;User ID="+UserName+";Data Source=";
	  // constr = constr +dbServer+";Initial Catalog=book;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=LEOMA;Use Encryption for Data=False;Tag with column collation when possible=False";
	  // constr = "Provider=SQLOLEDB.1;Password=pdz@c3$9w4!0tb19;Persist Security Info=True;User ID=sa;Initial Catalog=book;Data Source="+dbServer;

		 // Memo1->Lines->Add(constr);
		 // Memo1->Lines->SaveToFile("D:\log.txt");
	   //constr = "Provider=SQLOLEDB.1;Password=pdz@c3$9w4!0tb19;Persist Security Info=True;User ID="+UserName+";Data Source=";
	//   constr = "Provider=SQLOLEDB.1;Password=pddataabc;Persist Security Info=True;User ID="+UserName+";Data Source=";
   //	   constr = constr +dbServer+";Initial Catalog=pddbinfo;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=LEOMA;Use Encryption for Data=False;Tag with column collation when possible=False";
	 // try
	//  {
	 //	   conaccount->ConnectionString = constr;
	 //	   if (!conaccount->Connected ) {
	 //		  conaccount->Connected = true;
	 //	   }
	 //  }
	//   catch(...)
	 //  {
	 //	 MessageBoxA(0,"数据库连接错误！请与管理员联系","错误",MB_ICONERROR);
	   //	 lbzhangtao->Visible = false;
		 // cbzhangtao->Visible = false;
		//  sbchangepd->Top = 150;
	   //	  sblogcancel->Top = 150;
	   //	  sblogin->Top = 150;
	  //	 return;
	 //  }
	//   String sqlgetzhangtao = "select * from pdinfo where state = '已启用' and security = '" + Zhangtao + "'";

	//   TADOQuery *aq = new TADOQuery(this);
	 //  aq->Connection = conaccount ;
	 //  aq->Close();
	//   aq->SQL->Clear();
	//   aq->SQL->Add(sqlgetzhangtao);
	 //  aq->Open();
	//       ShiJiZhangTao =   aq->FieldByName("name")->AsAnsiString;
	 //  cbzhangtao->Items->Add(aq->FieldByName("name")->AsAnsiString);
	  // cbzhangtao->Items->Add("book");
	  // cbzhangtao->ItemIndex = 0;
	//   delete aq;    //取得默认帐套

	   char Temp[MAX_PATH]="";
	   char TempName[MAX_PATH] = "";
	try
	 {
	  // GetProfileString("DataIntegrity","path","",Temp,MAX_PATH);
	 //  GetProfileString("DataIntegrity","AccountSetName","",TempName,MAX_PATH);
	 //  if (!FileExists(AnsiString(Temp) + ".mdf") ) {

		  //如果有安全帐套则显示选择帐套

		//  lbzhangtao->Visible = false;
	 //	  cbzhangtao->Visible = false;
	 //	  sbchangepd->Top = 130;
	 //	  sblogcancel->Top = 130;
	 //	  sblogin->Top = 130;
												  //登录默认帐套
			  LoginConstr = "Provider=" + Provider + ";Password=" + DogInfo + ";Persist Security Info=True;User ID="+UserName+";Data Source=";
		 LoginConstr = LoginConstr +dbServer+";Initial Catalog="+Zhangtao+";Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=LEOMA;Use Encryption for Data=False;Tag with column collation when possible=False";
		// LoginConstr = "Provider=SQLOLEDB.1;Password=pddataabc;Persist Security Info=True;User ID="+UserName+";Data Source=";
		// LoginConstr = "Provider=SQLOLEDB.1;Password=pdz@c3$9w4!0tb19;Persist Security Info=True;User ID="+UserName+";Data Source=";
		// LoginConstr = LoginConstr +dbServer+";Initial Catalog="+cbzhangtao->Text.Trim() +";Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=LEOMA;Use Encryption for Data=False;Tag with column collation when possible=False";
		  conLand->ConnectionString = LoginConstr ;
		  try
		  {
			  if (!conLand->Connected ) {
				  conLand->Connected = true;
			  }
		   }
		   catch(...)
		   {
			  MessageBoxA(0,"数据库连接错误！请与管理员联系","错误",MB_ICONERROR);

		   }
		   String sql;
		   TADOQuery *aq = new TADOQuery(this);
		   aq->Connection = conLand ;
		   sql = "select ID,Name,Master from SYS_StorageInfo ";
		   aq->Close();
		   aq->SQL->Clear();
		   aq->SQL->Add(sql);
		   aq->Open();
		   cbstorage->Clear();
		   while (!aq->Eof )
		   {
				cbstorage->AddItem(aq->FieldByName("Name")->AsString,(TObject*)aq->FieldByName("ID")->AsInteger );
				aq->Next();
		   }
		   cbstorage->ItemIndex =  cbstorage->Items->IndexOfObject(0);
		   m_storage = 0;
		   UserView();
	}
   catch(...)
   {}
}
//---------------------------------------------------------------------------

int TfrmLand::GetUserID()
{
	return m_user;
}

int TfrmLand::GetStorageID()
{
	return m_storage;
}

bool TfrmLand::GetMaster()
{
	//m_storage = (int)(cbstorage->Items->Objects[cbstorage->ItemIndex]);
	String sql;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = conLand ;
	sql = "select ID,Master from SYS_StorageInfo where id = " + IntToStr(m_storage);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	m_master = aq->FieldByName("Master")->AsBoolean ;
	delete aq;
	return m_master;

}
AnsiString TfrmLand::GetUserName()
{
	AnsiString sql,username;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = conLand ;
	sql = "select ID,name from sys_user where ID = " + IntToStr(userid) ;//用户名列表
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	username = aq->FieldByName("name")->AsAnsiString ;
	delete aq;
	return  username;
}


void __fastcall TfrmLand::cbNameKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r')
	{
		Key = 0;
		sblogin->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmLand::sbloginClick(TObject *Sender)
{
	if (!Login(cbName->Text, edtPassword->Text, userid, stgid))

                ShowMsg(Handle ,"用户名或密码错误！",3);
	else
	{
		m_storage = stgid;
                m_user = userid;
		AddEvent(1,"登录窗口",GetUserID(),GetStorageID(),"登录");
		String sql;
		TADOQuery *aq = new TADOQuery(this);
		aq->Connection = conLand ;
		sql = "select bk from sys_bsset where name = 'softversion'";
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();

                softversion = aq->FieldByName("bk")->AsAnsiString ;
		delete aq;




		ModalResult = mrOk;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmLand::sbchangepdClick(TObject *Sender)
{
	if (cbName->Text == "") {

                ShowMsg(Handle ,"请选择一个用户！",3);
		return;
	}
	edtoldpd->Text = "";
	edtnewpd->Text = "";
	edtconfirmpd->Text = "";
       //	pchangepd->Visible = false;
       //	plogin->Visible = true;
	pchangepd->Visible  = true;
	plogin->Visible = False ;
}
//---------------------------------------------------------------------------


void __fastcall TfrmLand::sbokClick(TObject *Sender)
{
	String getuserinfo = "select count(*) as d from sys_user where name = '" + cbName->Text + "' and password = '"+edtoldpd->Text.Trim() +"' and stgID = " + IntToStr(stgid);
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = conLand ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(getuserinfo);

	aq->Open();
	if (aq->FieldByName("d")->AsInteger ==0 ) {

                ShowMsg(Handle ,"旧密码错误！",3);
		return;
	}
	if (edtnewpd->Text != edtconfirmpd->Text) {

                ShowMsg(Handle ,"两次输入的密码不相符！",3);
		return;
	}
	String updatepd  = "update sys_user set password = '" + edtconfirmpd->Text + "' where name = '" + cbName->Text + "' and stgID = " + IntToStr(stgid) ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(updatepd);
	if (aq->ExecSQL())
	{

                ShowMsg(Handle ,"密码更改成功！",3);
	}else
	{

                  ShowMsg(Handle ,"密码更改失败！",3);
		return;
	}
	delete aq;
	pchangepd->Visible = false;
	plogin->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmLand::cbzhangtaoChange(TObject *Sender)
{
	 try
	 {
		  LoginConstr = "Provider=SQLOLEDB.1;Password=pddataabc;Persist Security Info=True;User ID="+UserName+";Data Source=";
		 // LoginConstr = LoginConstr +dbServer+";Initial Catalog="+cbzhangtao->Text.Trim() +";Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=LEOMA;Use Encryption for Data=False;Tag with column collation when possible=False";
		  conLand->Connected = false;
		  conLand->ConnectionString = LoginConstr ;
		  try
		  {
			  if (!conLand->Connected ) {
				  conLand->Connected = true;
			  }
		   }
		   catch(...)
		   {


                            ShowMsg(Handle ,"数据库连接错误！请与管理员联系！",3);
			  return;
		   }

		   String sql;
		   TADOQuery *aq = new TADOQuery(this);
		   aq->Connection = conLand ;
		   sql = "select ID,Name from SYS_StorageInfo ";
		   aq->Close();
		   aq->SQL->Clear();
		   aq->SQL->Add(sql);
		   aq->Open();
		   cbstorage->Clear();
		   while (!aq->Eof )
		   {
				cbstorage->AddItem(aq->FieldByName("Name")->AsString,(TObject*)aq->FieldByName("ID")->AsInteger );
				aq->Next();
		   }
		   cbstorage->ItemIndex =  cbstorage->Items->IndexOfObject(0);
		   UserView();
		   }
		  catch(...)
		  {}

}
//---------------------------------------------------------------------------

void __fastcall TfrmLand::sbcancelClick(TObject *Sender)
{
	  pchangepd->Visible = false;
	  plogin->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmLand::sblogcancelClick(TObject *Sender)
{
  	// this->Close();
	ModalResult = mrCancel  ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmLand::edtoldpdKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
		Perform(WM_NEXTDLGCTL, 0, 0);
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmLand::edtconfirmpdKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
    	sbok->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmLand::cbstorageChange(TObject *Sender)
{
	if (cbstorage->Text == "") {
		MessageBoxA(0,"请选择店名","错误",MB_ICONERROR);
		return;
	}
	stgid = int(cbstorage->Items->Objects[cbstorage->ItemIndex]);
	UserView();
}
//---------------------------------------------------------------------------

void __fastcall TfrmLand::UserView()
{
	AnsiString sql;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = conLand ;
	sql = "select ID,name from sys_user where stgID = " + IntToStr(stgid) +" and userstate=1";//用户名列表
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	cbName->Clear();
	while(!aq->Eof)
	{
		cbName->Items->Add(aq->FieldByName("name")->AsAnsiString ) ;
		aq->Next();
	}
	delete aq;
	cbName->ItemIndex =0;
	userid = (int)(cbName->Items->Objects[cbName->ItemIndex]);
}
//---------------------------------------------------------------------------

void __fastcall TfrmLand::cbNameChange(TObject *Sender)
{
	userid = (int)(cbName->Items->Objects[cbName->ItemIndex]);
}
//---------------------------------------------------------------------------

