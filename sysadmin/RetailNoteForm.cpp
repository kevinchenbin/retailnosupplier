//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <Printers.hpp>

#include "RetailNoteForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzChkLst"
#pragma link "RzDBEdit"
#pragma link "RzDBList"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzLstBox"
#pragma link "RzPanel"
#pragma link "RzLine"
#pragma link "RzCmboBx"
#pragma link "RzDBCmbo"
#pragma link "RzButton"
#pragma link "RzDBChk"
#pragma link "RzRadChk"
#pragma link "MDIChild"
#pragma link "RzBckgnd"
#pragma link "frxClass"
#pragma resource "*.dfm"
TfrmRetailNote *frmRetailNote;
HINSTANCE hl;
FARPROC lpFarProc1,lpFarProc2,lpFarProc3,lpFarProc4,lpFarProc5;
bool (*com_init)(int);
bool (*com_rest)();
bool (*com_send)(String,int);
bool (*com_clearDisplay)();
bool (*com_changebr)();
//---------------------------------------------------------------------------
__fastcall TfrmRetailNote::TfrmRetailNote(TComponent* Owner)
	: TfrmMDIChild(Owner)
{
	m_module = MTSysadmin;
	TRegistry *my = new TRegistry;
	my->RootKey=HKEY_LOCAL_MACHINE;
	my->OpenKey("HARDWARE\\DEVICEMAP\\SERIALCOMM",true);
	cbcomnum->Sorted=false;
	my->GetValueNames(cbcomnum->Items);
	cbcomnum->Items->BeginUpdate();
	for(int   i=0;i<cbcomnum->Items->Count;i++)
	cbcomnum->Items->Strings[i]=my->ReadString(cbcomnum->Items->Strings[i]);
	cbcomnum->Items->EndUpdate();
	cbcomnum->Sorted=true;
	AnsiString configfile;
	//configfile =  ExtractFilePath(Application->ExeName) + "dbconfig" +  ".INI" ;
	configfile = "U:\\pddata\\config.ini";
	if (!FileExists(configfile) ) {
    	configfile =  ExtractFilePath(Application->ExeName) + "config.ini" ;
	}
	TIniFile *ini;
	ini   = new    TIniFile(configfile);
	AnsiString comnum = ini->ReadString("dbserver","ComNum","0");
	AnsiString display = ini->ReadString("dbserver","Display","0");
	AnsiString print =  ini->ReadString("dbserver","Print","0");
	delete ini;
	cbcomnum->Text = "COM" + comnum;
	if (display == "1") {
		ch1->Checked = true;
	}
	else
	{
		ch1->Checked = false;
	}

	if (print == "1") {
		chprint->Checked = true;
	}
	else
	{
		chprint->Checked = false;
	}
        strlistusb = new TStringList();
}
/*
void __fastcall TfrmRetailNote::WndProc(TMessage &Msg)
{
if (Msg.Msg == WM_SYSCOMMAND)
{
if(Msg.WParam == (HTCAPTION | SC_MOVE))
{
Msg.WParam = 0;
}
}
TForm::WndProc(Msg);
}   */
//---------------------------------------------------------------------------
void __fastcall TfrmRetailNote::FormClose(TObject *Sender, TCloseAction &Action)
{
	if (dsetRetailNote->State == dsEdit || dsetRetailNote->State == dsInsert)
	{
		dsetRetailNote->Post();
	}
	dsetRetailNote->Active = false;
	Action = caFree;
}
//--------------------------------------------------------------------------
void TfrmRetailNote::Init(TApplication* app, TADOConnection* cn)
{        //ShowMessage("wesdf");
	TfrmMDIChild::Init(app, cn);
		qryRetailNoteName->Connection = m_con;
		dsretail->Connection=m_con;
		dsPrint->Connection=m_con;
		con = cn ;
	 qryRetailNoteName->SQL->Add("select id,Name from SYS_StorageInfo where id = " + IntToStr(stgid) );
	 qryRetailNoteName->Open();
	 labstorage->Caption = "当前店：" + qryRetailNoteName->FieldByName("Name")->AsString;
	 //-----------------------打印设置-----------------------------
	 dbedtWelcomeMessage->DataField="RetailNoteWelcomeMessage";
	 dbedtAddress->DataField="RetailNoteAddress";
	 dbedtTel->DataField="RetailNoteTel";
	 //dbcbbPort->DataField="RetailNotePort";
	 dbedtRemarks->DataField="RetailNoteRemarks";
	 chprintmayang->DataField = "printmayang";
	 chprintdiscount->DataField = "printdiscount";
	 chjiaojieprint->DataField = "jiaojieprint";

	  //------------------------单据列设置----------------------------
	 CHKBookName->DataField="ShowRetailNoteBookName";
	 CHKPrice->DataField="ShowRetailNotePricing";
	 CHKDiscount->DataField="ShowRetailNoteDiscount";
	 CHKtotalamount->DataField = "ShowRetailAmount";
	 CHKjine->DataField = "ShowRetaildisprice";
	 CHKCardrec->DataField = "ShowRetailCardRec";
	 CHKtotalhang->DataField = "ShowRetailtotalhang";
	 chkpostcard->DataField = "printposcard";
	 chkyouhuiquan->DataField = "printyouhuiquan";
	 chprintjifen->DataField = "printjifen";
	 chprintcard->DataField = "printcard";
	 chprintname->DataField = "printname";
         chprint->DataField = "retailprint";

	 qryRetailNoteName->Close();
	 dsetRetailNote->Connection = m_con;
	 dsetRetailNote->CommandText = "select * from SYS_StorageInfo where id = " + IntToStr(stgid) ;
	 dsetRetailNote->Active = true;
	 dbcbbPort->Text =  dsetRetailNote->FieldByName("retailprintcom")->AsAnsiString.Trim();
	 rgtype->ItemIndex = dsetRetailNote->FieldByName("retailxptype")->AsInteger ;

	AnsiString sql;
        AnsiString MoneyBoxSufi;
	sql = "select * from sys_bsset where name in('yuying','OpenMoneyBoxByUSB')" ;
	TADOQuery *aq = new  TADOQuery(this);
	aq->Connection = con;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
        aq->First();
	chyuying->Checked = aq->FieldByName("value")->AsBoolean ;
        aq->Next();
        cbopenmoneybox->Checked= aq->FieldByName("value")->AsBoolean ;   //是否开启钱箱
        MoneyBoxSufi =  aq->FieldByName("bk")->AsAnsiString;
        if (MoneyBoxSufi.Length()>5) {
            cbmoneybox->ItemIndex = 1;
            cbinterfacetype->Clear();
            cbinterfacetype->Items->Add("USB001");
            cbinterfacetype->ItemIndex=0;
        }else
        {

        }


	delete aq;

	try
	{
		hl = ::LoadLibrary("ClientDisplay.dll");
		lpFarProc1 = GetProcAddress(hl,"com_init");
		lpFarProc2 = GetProcAddress(hl,"com_rest");
		lpFarProc3 = GetProcAddress(hl,"com_send");
		lpFarProc4 = GetProcAddress(hl,"com_clearDisplay");
		lpFarProc5 = GetProcAddress(hl,"com_changebr");

		com_init = (bool(__cdecl *)(int))lpFarProc1;
		com_rest = (bool(__cdecl *)())lpFarProc2;
		com_send = (bool(__cdecl *)(String,int))lpFarProc3;
		com_clearDisplay = (bool(__cdecl *)())lpFarProc4;
		com_changebr = (bool(__cdecl *)())lpFarProc5;
	}
	catch(Exception &e)
	{
		::FreeLibrary(hl);
		ShowMsg(Handle,e.Message,3);
	}
}
//--------------------------------------------------------------------------

void __fastcall TfrmRetailNote::btn1Click(TObject *Sender)
{
	//if (dsetRetailNote->State == dsEdit || dsetRetailNote->State == dsInsert)
	//{
		if (dbcbbPort->Text == "") {

                     ShowMsg(Handle ,"请选择打印端口！",3);
			return;
		}
		if (cbcomnum->Text == "") {

                        ShowMsg(Handle ,"请选择顾显端口！",3);
			return;
		}
		int num;
		try {
			num = StrToInt(cbcomnum->Text.SubString(4,1));
		} catch (...) {

                        ShowMsg(Handle ,"请选择正确顾显端口！",3);
			return;
		}

		AnsiString sql;
		sql = "update SYS_StorageInfo set retailprintcom = '" + dbcbbPort->Text + "',retailxptype = " + IntToStr(rgtype->ItemIndex) + " where id = " + IntToStr(stgid);
		TADOQuery *aq = new  TADOQuery(this);
		aq->Connection = con;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->ExecSQL();

                AnsiString sql1,sql2;
		if (chyuying->Checked ) {
			sql = "update sys_bsset set value = 1 where name = 'yuying'";
		}
		else
		{
			sql = "update sys_bsset set value = 0 where name = 'yuying'";
		}

                   if(cbopenmoneybox->Checked)
                {
                  sql1 = "update sys_bsset set value = 1 where name = 'OpenMoneyBoxByUSB'";
                }else
                {
                  sql1 = "update sys_bsset set value = 0 where name = 'OpenMoneyBoxByUSB'";
                }
                if (cbmoneybox->Text =="LPT") {
                   // cbinterfacetype->Text
                    sql2 = "update sys_bsset set bk = '"+cbinterfacetype->Text+"' where name = 'OpenMoneyBoxByUSB'";

                }
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
                aq->SQL->Add(sql1);
                aq->SQL->Add(sql2);
		aq->ExecSQL();


             

		delete aq;
		if (dsetRetailNote->State == dsEdit ) {
        	try {
				dsetRetailNote->Post();
			} catch (...) {
			}
		}

	     /*	AnsiString configfile;
		configfile = "U:\\pddata\\config.ini";
		if (!FileExists(configfile) ) {
			configfile =  ExtractFilePath(Application->ExeName) + "config.ini" ;
		}
		//configfile =  ExtractFilePath(Application->ExeName) + "dbconfig" +  ".INI" ;
		TIniFile *ini;
	      //	ini	= new TIniFile(configfile);
	       //	ini->WriteString("dbserver","ComNum",IntToStr(num));
		if (ch1->Checked) {
			ini->WriteString("dbserver","Display","1");
		}
		else
		{
			ini->WriteString("dbserver","Display","0");
		}
		if (chprint->Checked) {
			ini->WriteString("dbserver","Print","1");
		}
		else
		{
			ini->WriteString("dbserver","Print","0");
		}
	      //	delete ini;
                   */
                if (cbmoneybox->ItemIndex ==1) {
                  if (strlistusb->Count ==0) {

                        strlistusb->Clear();
                        strlistusb->Delimiter='$';
                        strlistusb->DelimitedText =  aGetUSBInfos();
                  }
                sql = "update SYS_BSSET set bk = '" + strlistusb->Strings[cbmoneybox->ItemIndex] +"' where name='OpenMoneyBoxByUSB'" ;
		TADOQuery *aq1 = new  TADOQuery(this);
		aq1->Connection = con;
		aq1->Close();
		aq1->SQL->Clear();
		aq1->SQL->Add(sql);
		aq1->ExecSQL();
                delete aq1;

                }

	        ShowMsg(Handle ,"保存成功！",3);

}
//---------------------------------------------------------------------------
//-----------------小票打印，传入小票单ID和一个con连接实现写一个文本文件然后把文本文件送往并口lpt1打印------------------------------
void   TfrmRetailNote::print()
{

		AnsiString sql;

	   if (dsPrint->Active) {
		   dsPrint->Active=false;
	   }
	   sql = "select RetailNoteTitle,RetailNoteWelcomeMessage,RetailNoteAddress,RetailNoteTel,RetailNoteRemarks,ShowRetailNoteISBN,ShowRetailNoteBookName,ShowRetailNotePricing,ShowRetailNoteDiscount,ShowRetailCardRec,printdiscount,printmayang,ShowRetailtotalhang,ShowRetailAmount,ShowRetaildisprice,printposcard,printyouhuiquan,retailprint from SYS_StorageInfo where id = " + IntToStr(stgid) ;
	   dsPrint->CommandText = sql;
	   dsPrint->Active = true;


		  String bookbk = "                                                                       ";
		  int n = 0,namelen = 16;
		  if (dsPrint->FieldByName("ShowRetailNotePricing")->AsString==1 ) {
			  n = n+ 1;
		   }
		   if (dsPrint->FieldByName("ShowRetailAmount")->AsString==1 ) {
			 n = n+ 1;
		   }
			if (dsPrint->FieldByName("ShowRetailNoteDiscount")->AsString==1 ) {
			 n = n+ 1;
		   }
		   if (dsPrint->FieldByName("ShowRetaildisprice")->AsString==1 ) {
			 n = n+ 1;
		   }


    TStrings* ss = new TStringList();
		 dsPrint->First();
	String s="\n  -----"+dsPrint->FieldByName("RetailNoteWelcomeMessage")->AsString+"-----\n" ;
		  s=s+"单号:"+"2010052000005";
		  s=s+"\n日期:"+ DateTimeToStr(Date()) +"\n收银员:"+ "Admin"+"\n";
		   s=s+"--------------------------------\n";
		   if (dsPrint->FieldByName("ShowRetailNoteBookName")->AsString==1 ) {
				namelen = 16-3*n;
				s = s + "书名    " + bookbk.SubString(1,(4-n)*5+2);
		   }
			if (dsPrint->FieldByName("ShowRetailNotePricing")->AsString==1 ) {
			 s=s+" 定价 ";
		   }
		   if (dsPrint->FieldByName("ShowRetailAmount")->AsString==1 ) {
			 s=s+"数量 ";
		   }
			if (dsPrint->FieldByName("ShowRetailNoteDiscount")->AsString==1 ) {
			 s=s+"折扣 ";
		   }
		   if (dsPrint->FieldByName("ShowRetaildisprice")->AsString==1 ) {
			 s=s+"金额 ";
		   }
		   s=s+"\n";
		 String stemp;

		 bool huanhang = false,first = true;
		   String bookname="蓝猫淘气3000问可爱的太阳光(打印测试)";

					 bookname = bookname.TrimRight();
						//控制书名每行输出6个字
						  huanhang = false;
						  first = true;
						  int len=bookname.Length();
						if (len>48) {
							stemp=bookname.SubString(1,16)+"\n"+bookname.SubString(17,16)+"\n"+bookname.SubString(33,16)+"\n"+bookname.SubString(49,16);
							stemp =  stemp + "\n";
							huanhang = true;
						  }
						  else	if (len>32) {
							stemp=bookname.SubString(1,16)+"\n"+bookname.SubString(17,16)+"\n"+bookname.SubString(33,16);

							stemp =  stemp + "\n";
							huanhang = true;
						  }
						   else	if (len>16) {
							stemp=bookname.SubString(1,16)+"\n"+bookname.SubString(17,16);
							stemp =  stemp + "\n";
							huanhang = true;
						  }
						   else	if (len>namelen) {
							stemp=bookname + "\n";
							huanhang = true;
						  }
						   else	if (len == namelen) {
							stemp=bookname + bookbk.SubString(1,2*((namelen-len))-2);
						  }
						  else	if (len < namelen) {
							stemp=bookname + bookbk.SubString(1,2*(namelen-len));
						  }
					 if (dsPrint->FieldByName("ShowRetailNoteBookName")->AsString==1 ) {
						s=s+stemp;
					}
					if (dsPrint->FieldByName("ShowRetailNotePricing")->AsString==1 ) {
						AnsiString Price;
						Price = "5.8";
						Price = bookbk.SubString(1,5-Price.Length()) + Price;
						if (dsPrint->FieldByName("ShowRetailNoteBookName")->AsString==1 && huanhang) {
								s=s+ bookbk.SubString(1,namelen*2+1) + Price;
							}
							else
							{
								s=s+ " " + Price;
							}
							first = false;
					}
					if (dsPrint->FieldByName("ShowRetailAmount")->AsString==1) {
						AnsiString Amount;
						Amount = "1";
						if (first) {
							Amount = bookbk.SubString(1,3-Amount.Length()) + Amount;
						}
						else
						{
							Amount = bookbk.SubString(1,4-Amount.Length()) + Amount;
						}
						if (first && huanhang) {
							s=s+ bookbk.SubString(1,namelen*2+1) + Amount;
						}
						else
						{
							s=s+ " " + Amount;
						}
						first = false;
					}

					if (dsPrint->FieldByName("ShowRetailNoteDiscount")->AsString==1 ) {
						AnsiString discountprint;
						discountprint = "100";
						discountprint = bookbk.SubString(1,3-discountprint.Length()) + discountprint +"%";
						if (first && huanhang) {
							s=s+ bookbk.SubString(1,namelen*2) + discountprint;
						}
						else if (first) {
								s = s + discountprint;
						}
						else if (dsPrint->FieldByName("ShowRetailAmount")->AsString==1) {
                        	s = s + "  "+ discountprint;
						}
						else
						{
							s = s + " "+ discountprint;
						}
						first = false;
				   }
				   if (dsPrint->FieldByName("ShowRetaildisprice")->AsString==1) {
                        if (first && huanhang) {
							s=s+ "                         " + "5.8";
						}
						else if (first) {
							s=s + "5.8";
						}
						else
						{
							s=s+ " " + "5.8";
						}
				   }

			if (dsPrint->FieldByName("ShowRetailtotalhang")->AsString==1) {
				s=s+"\n--------------------------------\n";
				s=s+ "合计:" ;
				if (dsPrint->FieldByName("ShowRetailAmount")->AsString==1 && dsPrint->FieldByName("ShowRetailNotePricing")->AsString==1) {
					AnsiString TotalAmount;
					TotalAmount = "1";
					TotalAmount = bookbk.SubString(1,3-TotalAmount.Length()) + TotalAmount;
					s=s +bookbk.SubString(1,(6-n)*5+1) + TotalAmount;
				}
				else if (dsPrint->FieldByName("ShowRetailAmount")->AsString==1) {
					AnsiString TotalAmount;
					TotalAmount = "1";
					TotalAmount = bookbk.SubString(1,3-TotalAmount.Length()) + TotalAmount;
					if (dsPrint->FieldByName("ShowRetaildisprice")->AsString==1) {
						s=s +bookbk.SubString(1,(5-n)*5) + TotalAmount;
					}
					else
					{
						s=s +bookbk.SubString(1,(5-n)*5+1) + TotalAmount;
					}
				}
				if (dsPrint->FieldByName("ShowRetaildisprice")->AsString==1 && dsPrint->FieldByName("ShowRetailAmount")->AsString==1 && dsPrint->FieldByName("ShowRetailNoteDiscount")->AsString==1 ) {
					s = s + "       " + "5.8";
				}
				else if (dsPrint->FieldByName("ShowRetaildisprice")->AsString==1 && dsPrint->FieldByName("ShowRetailAmount")->AsString==1) {
					s = s + " " + "5.8";
				}
				else if (dsPrint->FieldByName("ShowRetaildisprice")->AsString==1) {
					s = s + bookbk.SubString(1,(5-n)*5+1) + "5.8";
				}
				s = s + "\n";

			}
		   s=s+"\n--------------------------------\n";
		   float total= 6;

		   s=s+"总应收:"+"5.8";
		   if (dsPrint->FieldByName("printmayang")->AsString==1) {
				s = s + "      原价合计:5.8";
		   }
			s=s+"\n收款:"+FloatToStr(total);
			if (dsPrint->FieldByName("printdiscount")->AsString==1) {
				s = s + bookbk.SubString(1,10) + "折扣金额:0.0";
			}
			if (dsPrint->FieldByName("ShowRetailCardRec")->AsString==1) {
				s=s+"\n其中会员卡消费:0";
			}
			if (dsPrint->FieldByName("printposcard")->AsString==1) {
				s=s+"\n其中银行卡消费:0";
			}
			if (dsPrint->FieldByName("printyouhuiquan")->AsString==1) {
				s=s+"\n其中优惠券消费:0";
			}

		   s=s+"\n找零:"+ "0.2" +"\n";
		   s=s+"--------------------------------\n";
			s=s+"地址:"+dsPrint->FieldByName("RetailNoteAddress")->AsString+"\n";
			s=s+"电话:"+dsPrint->FieldByName("RetailNoteTel")->AsString+"\n";
		        s=s+"备注:"+dsPrint->FieldByName("RetailNoteRemarks")->AsString+"\n\n\n\n\n\n";

	ss->Text=s;
     printcount=s;
     if (dbcbbPort->Text=="USB") {
          /****************************************************************/
        	frxretail->LoadFromFile(Sysutils::ExtractFilePath(Application->ExeName) + "retailxiaopiao.fr3");
                	((TfrxMemoView *)frxretail->FindObject("Memo1"))->Memo->Add(s);
		frxretail->PrepareReport(true);

			frxretail->PrintOptions->ShowDialog = false;
                   //  frxretail->ShowPreparedReport();
	frxretail->Print();

       /****************************************************************/
        return;
     }

	// ss->SaveToFile("d:\\pddata.txt");

	TStringList *lst = new TStringList;

	DCB dd;
	DWORD dwWrited;
	HANDLE m_hComm;
	LPCTSTR  strCom = dbcbbPort->Text.t_str() ;
	COMMTIMEOUTS comtimeout;

	int nLpt  ;
	try
	{

		m_hComm=CreateFile(TEXT(strCom),GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
		if (m_hComm==INVALID_HANDLE_VALUE)
		{
			ShowMsg(this->Handle,"此通讯口已被占用或损坏!",3);
		       	m_hComm=NULL;
		      	return ;
		}
		comtimeout.ReadIntervalTimeout =10;
		comtimeout.ReadTotalTimeoutConstant =10;
		comtimeout.ReadTotalTimeoutMultiplier =10;
		comtimeout.WriteTotalTimeoutConstant =100;
		comtimeout.WriteTotalTimeoutMultiplier =500;
		SetCommTimeouts(m_hComm,&comtimeout);

		DWORD dwSize = 0;
		lst->AddStrings(ss);
		AnsiString strAnsiLine;

		for (int i = 0; i < lst->Count; i++)
		{
			strAnsiLine =AnsiString(lst->Strings[i]) + AnsiString("\r\n");

			if (!WriteFile(m_hComm,strAnsiLine.c_str(),strAnsiLine.Length() ,&dwSize,NULL))
			{
				FlushFileBuffers(m_hComm);
				CloseHandle(m_hComm);
				return;
			}
		}

		FlushFileBuffers(m_hComm);
		CloseHandle(m_hComm);
	}
	__finally
	{
		ShowMsg(this->Handle,"此通讯口已被占用或损坏!",3);
	}

   /*	String   LogPath,nowtime;
   int  iFileHandle;
   Sysutils::TBytes ByteOrderMark = TEncoding::Unicode->GetPreamble();
   LogPath=ExtractFilePath(Application->ExeName)+"CDRFTP.Log";
   if(FileExists(LogPath))
   {
      iFileHandle=FileOpen(LogPath,fmOpenWrite);
   }
   else
   {
      iFileHandle=FileCreate(LogPath);
   }
   FileSeek(iFileHandle,0,2);
   nowtime = Now().FormatString("YYYY-MM-DD HH:mm:SS");
   //FileWrite( iFileHandle,&UnicodeBytes[0], UnicodeBytes.Length );
   String WriteStr=nowtime+" "+"111"+"\r\n" ;
   FileWrite(iFileHandle,WriteStr.c_str(),WriteStr.Length());
   FileClose(iFileHandle);*/



	/*int nLpt = FileOpen(TEXT("LPT1"), fmOpenWrite);
	  //	ShowMessage(IntToStr(nLpt));
	if (nLpt <= 0) return;

	TStringList *lst = new TStringList;
    try
	{
	 // lst->LoadFromFile(strTxtFile);
		lst->AddStrings(ss);

		AnsiString strAnsiLine;

		for (int i = 0; i < lst->Count; i++)
        {
			strAnsiLine = AnsiString(lst->Strings[i]) + AnsiString("\r\n");
			FileWrite(nLpt, strAnsiLine.c_str(), strAnsiLine.Length());
		}
    }
	__finally
    {
		delete lst;

		FileClose(nLpt);
	}      */
}
//---------------------------------------------------------------------------
void __fastcall TfrmRetailNote::btn2Cick(TObject *Sender)
{
     print();

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void __fastcall TfrmRetailNote::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
				if (Shift.Contains(ssCtrl)&&Key==90) {   //Z
			this->btn2->Click();

		}
				if (Shift.Contains(ssCtrl)&&Key==83) {   //S
			this->btn1->Click() ;

		}
				if (Key==0x1B) {   //esc
				this->btn3->Click();

		}

}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailNote::Button1Click(TObject *Sender)
{
      if (cbmoneybox->ItemIndex ==0) {
        int nLpt = FileOpen(TEXT(cbinterfacetype->Text), fmOpenWrite);
	  //	ShowMessage(IntToStr(nLpt));
	if (nLpt <= 0) return;
	try
	{
		String strAnsiLine;
		char p[5]= {27,112,0,60,255};
		FileWrite(nLpt, p , 5);
	}
	__finally
	{
		FileClose(nLpt);
	}
      }else if (cbmoneybox->ItemIndex==1) {
         // ShowMessage(strlistusb->Strings[cbmoneybox->ItemIndex]);
            OpenMoneyBoxUSB(strlistusb->Strings[cbmoneybox->ItemIndex]);
      }

}
//---------------------------------------------------------------------------
 void   TfrmRetailNote::OpenMoneyBoxUSB(AnsiString USBInfoOpenBOX)
{
FARPROC  lpFarProc1box,lpFarProc1usb;
//char *(*GetUSBInfos)();
bool (*OpenMoneyBox)(char *);
char * usbinfo;

  try
	{
		hl = ::LoadLibrary("USBCUM.dll");
        lpFarProc1usb = GetProcAddress(hl,"OpenMoneyBox");

        //com_init = (bool(__cdecl *)(int))lpFarProc1;
		OpenMoneyBox = (bool (__cdecl *)(char *))lpFarProc1usb;
	       //	com_send = (bool(__cdecl *)(String,int))lpFarProc3;
     //   com_clearDisplay = (bool(__cdecl *)())lpFarProc4;
      //  com_changebr = (bool(__cdecl *)())lpFarProc5;

        // usbinfo = GetUSBInfos();
           OpenMoneyBox(USBInfoOpenBOX.c_str());
         FreeLibrary(hl);
	}
	catch(Exception &e)
	{
		ShowMessage(e.Message);
	}


}
void __fastcall TfrmRetailNote::Button2Click(TObject *Sender)
{
	int nLpt = FileOpen(TEXT("LPT1"), fmOpenWrite);
	  //	ShowMessage(IntToStr(nLpt));
	if (nLpt <= 0) return;
	try
	{
		String strAnsiLine;
		char p[5]= {27,112,1,60,255};
		FileWrite(nLpt, p , 5);
	}
	__finally
	{
		FileClose(nLpt);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailNote::cbcomnumChange(TObject *Sender)
{
	if (cbcomnum->Text != "") {
		try {
			int num = StrToInt(cbcomnum->Text.SubString(4,1));
			com_init(num);
			com_changebr();
			com_send("0.00",0);
			Label3->Caption="打开"+cbcomnum->Text+"成功!";

		} catch (...) {
			Label3->Caption="打开"+cbcomnum->Text+"失败!";
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailNote::Button3Click(TObject *Sender)
{
	try {
		com_send(edtest->Text,rg1->ItemIndex);
	} catch (Exception &e) {
		 MessageBox(0,"请检查顾客显示屏是否正确安装，稍后重试!","先行者提示",MB_OK|MB_ICONINFORMATION);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmRetailNote::btn3Click(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------



void __fastcall TfrmRetailNote::cbmoneyboxChange(TObject *Sender)
{
  //

  if (cbmoneybox->ItemIndex==0) {
       cbinterfacetype->Items->Clear();
       cbinterfacetype->Items->Add("LPT1");
       cbinterfacetype->Items->Add("LPT2");
       cbinterfacetype->Items->Add("LPT3");
       cbinterfacetype->ItemIndex=0;
  }else if (cbmoneybox->ItemIndex==1) {
       cbinterfacetype->Items->Clear();
       AnsiString usbinfo;
       usbinfo = aGetUSBInfos();

       strlistusb->Clear();
       strlistusb->Delimiter='$';
       strlistusb->DelimitedText =  usbinfo;
         cbinterfacetype->Items->Clear();
       for (int i=0; i < strlistusb->Count-1; i++) {
              cbinterfacetype->Items->Add("USB00"+IntToStr(i+1));
       }
         cbinterfacetype->ItemIndex=0;
      // ShowMessage(strlistusb->Strings[0]);

 }

}
  AnsiString TfrmRetailNote::aGetUSBInfos()
  {
   FARPROC  lpFarProc1box,lpFarProc1usb;
   char *(*GetUSBInfo)();
   char * usbinfo;
   AnsiString usbinfo_str;
    try
	{
		hl = ::LoadLibrary("USBCUM.dll");
        lpFarProc1usb = GetProcAddress(hl,"GetUSBInfo");

        //com_init = (bool(__cdecl *)(int))lpFarProc1;
		GetUSBInfo = (char *(__cdecl *)())lpFarProc1usb;
	       //	com_send = (bool(__cdecl *)(String,int))lpFarProc3;
     //   com_clearDisplay = (bool(__cdecl *)())lpFarProc4;
      //  com_changebr = (bool(__cdecl *)())lpFarProc5;

         usbinfo = GetUSBInfo();
         usbinfo_str = AnsiString(usbinfo);
         FreeLibrary(hl);
        // strcpy(usbinfo_str,usbinfo);

         return  usbinfo_str;
	}
	catch(Exception &e)
	{
	       //	ShowMessage(e.Message);
	}



  }
//---------------------------------------------------------------------------

