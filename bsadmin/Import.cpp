//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Import.h"
#include "pdutil.h"
#include "global.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzDBEdit"
#pragma link "RzDBGrid"
#pragma link "RzEdit"
#pragma link "RzPanel"
#pragma link "ModalDialog"
#pragma link "RzRadChk"
#pragma link "RzRadGrp"
#pragma link "RzShellDialogs"
#pragma link "RzPrgres"
#pragma link "RzCmboBx"
#pragma resource "*.dfm"
TfrmImport *frmImport;
//---------------------------------------------------------------------------
__fastcall TfrmImport::TfrmImport(TComponent* Owner,TADOConnection *con,int headid,int userid,int stgid)
	: TForm(Owner)
{
   Import= true;
   aq->Connection = con;
   aq->Active = false;
   aq->Active = true;
   headerid = headid;
   query->Connection = con;
   comAddcatalog->Connection = con;
   comaddnote->Connection = con;
   fuserid = userid;
   fstgid = stgid;
   cn = con;
}

//---------------------------------------------------------------------------

void __fastcall TfrmImport::spselectpathClick(TObject *Sender)
{
	if (opndlgExcelPath->Execute())
	{
		String DBPath,Name,filepath;
		DBPath = ExtractFilePath(opndlgExcelPath->FileName .c_str()  );
		Name = ExtractFileName(opndlgExcelPath->FileName .c_str() );
		DBPath = DBPath + Name;
		edtExcelPath->Text = DBPath;
                filepath=opndlgExcelPath->FileName;
	}
}
//---------------------------------------------------------------------------
void TfrmImport::xianxingze()
{
  	if(edtExcelPath->Text == "")
		return;
    if (!chisbn->Checked && !chname->Checked && !chprice->Checked && !chauthor->Checked && !chpress->Checked ) {
		MessageBoxA(0,"请选择匹配项！","批量导入",MB_ICONEXCLAMATION);
		return;
	}
       String str = " Provider=Microsoft.Jet.OLEDB.4.0;Extended Properties=Excel 8.0;Persist Security Info=false;Data Source=";
              str = str +opndlgExcelPath->FileName;
       AnsiString sql;

	con1->ConnectionString = "";
	try
	{
		con1->ConnectionString =  str ;
	}
	catch(...)
	{
		MessageBoxA(0,"该数据已经导入！","Excel导入",MB_ICONEXCLAMATION);
		Import = true;
		return;
	}
	con1->LoginPrompt = false;
	con1->ConnectOptions = coConnectUnspecified ;
	con1->KeepConnection = true;
	con1->Mode = cmRead;
	try
	{
		 con1->Connected = true;
	}
	catch(...)
	{
		MessageBoxA(0,"数据源配置错误！","Excel导入",MB_ICONHAND);
		Import= true;
		return;
	}
        TStringList * tablelist;
        tablelist = new TStringList();
        con1->GetTableNames(tablelist,false);
     	qry->Connection = con1;
          AnsiString excelsql;
          excelsql = "select * from ["+tablelist->Strings[0]+"]";
      	qry->Active = false;
	qry->SQL->Clear();
       	qry->SQL ->Add(excelsql);
       	qry->Open();
	qry->Active = true;
	ds->DataSet = qry;

	Import= false;
	Label1->Caption = "总共出记录" + IntToStr(qry->RecordCount) + "条";
	Label2->Visible = true;
	Sleep(10);
	int inportamount = 0;
	int n = 0;
	bool tishi = true;
	AnsiString Stack;

        int bkstackid;
          //return;
          Screen->Cursor = crHourGlass ;
	while (!qry->Eof)
	{
                if ((qry->FieldByName("序")->AsAnsiString =="合计")||(qry->FieldByName("序")->AsAnsiString =="")) {
                           qry->Next();
                           continue;

                }

		int bkcatalogid = -1,amount = 0;
		bool newbook = false;
		double discount = 100.00,FixedPrice = 0.0,DiscountedPrice = 0.0,jprice = 0.0,Price = 0.0;
		AnsiString ISBN,ISBN1,Name,PressName,Author,remarks,Presscount,barcode,selfcode;
		try {
			Name = qry->FieldByName("书名")->AsAnsiString ;
			Name = Name.Trim();
		} catch (...) {
			MessageBoxA(0,"请确认查询源文件中是否存在'书名'列！","查询出错",MB_ICONEXCLAMATION);
			qry->Close();
			con1->Connected =false;

			Screen->Cursor = crDefault ;
			return;
		}

		try {
			ISBN = qry->FieldByName("ISBN")->AsAnsiString.Trim() ;

		} catch (...) {
        	if (chisbn->Checked ) {
				MessageBoxA(0,"请确认查询源文件中是否存在'ISBN'列！","查询出错",MB_ICONEXCLAMATION);
				qry->Close();
				con1->Connected =false;

				Screen->Cursor = crDefault ;
				return;
			}
		}


                try
                {
		if (ISBN != "") {
        	ISBN = ISBN.SubString(0,13);
			ISBN = GetNum(ISBN);
			ISBN1 = ISBN;
			if (ISBN1.Length()==10 || ISBN1.Length()==13 ) {
				ISBN1 = ISBN1.Delete(ISBN1.Length(),1);
			}
		}
                  }catch(...)
                  {}


		if ((mode == 1)||(mode == 2)) {





		try {
			Price = qry->FieldByName("定价")->AsFloat ;
		} catch (...) {
			if (chprice->Checked ) {
				MessageBoxA(0,"请确认查询源文件中是否存在'定价'列或定价是否正确！","查询出错",MB_ICONEXCLAMATION);
				qry->Close();
				con1->Connected =false;

				Screen->Cursor = crDefault ;
				return;
			}
			Price = 0;
		}

		try {
			Author = qry->FieldByName("作者")->AsAnsiString.Trim();
		} catch (...) {
			if (chauthor->Checked ) {
				MessageBoxA(0,"请确认查询源文件中是否存在'作者'列！","查询出错",MB_ICONEXCLAMATION);
				qry->Close();
				con1->Connected =false;

				Screen->Cursor = crDefault ;
				return;
			}
		}

		try {
                if (chpress->Checked ) {
			PressName = qry->FieldByName("出版社")->AsAnsiString.Trim() ;
			PressName = PressName.Trim();  }
		} catch (...) {
        	if (chpress->Checked ) {
				MessageBoxA(0,"请确认查询源文件中是否存在'出版社'列！","查询出错",MB_ICONEXCLAMATION);
				qry->Close();
				con1->Connected =false;

				Screen->Cursor = crDefault ;
				return;
			}
		}

        try {          if (chpresscount->Checked ) {
			Presscount = qry->FieldByName("版次")->AsAnsiString.Trim() ; }
		} catch (...) {
			if (chpresscount->Checked ) {
				MessageBoxA(0,"请确认查询源文件中是否存在'版次'列！","查询出错",MB_ICONEXCLAMATION);
				qry->Close();
				con1->Connected =false;

				Screen->Cursor = crDefault ;
				return;
			}
		}
                try
                {
                if (cbselfma->Checked ) {
                     selfcode = qry->FieldByName("自编码")->AsAnsiString.Trim() ;
                      }
                }catch(...)
                {

                    	if (cbselfma->Checked ) {
				MessageBoxA(0,"请确认查询源文件中是否存在'自编码'列！","查询出错",MB_ICONEXCLAMATION);
				qry->Close();
				con1->Connected =false;

				Screen->Cursor = crDefault ;
				return;
			}


                }



		try {
			amount = qry->FieldByName("数量")->AsInteger ;
		} catch (...) {
			amount = 0;
		}

		try {
			discount = qry->FieldByName("折扣%")->AsFloat ;
		} catch (...) {
			discount = 0.00;
		}

	       //	try {
		//	remarks = qry->FieldByName("备注")->AsAnsiString ;
	       //	} catch (...) {
	      //	}
		if (mode == 1) {
			sql = "select B.id,B.ISBN,B.Name,B.Author,B.Price,B.PressCount,B.Pressdate,C.AbbreviatedName,convert(nvarchar(10),B.Date,120) as date,0 as amount from bs_bookcatalog B left join BS_PressInfo C on B.pressid = C.id where 1 = 1 " ;
		}
		else
		{
			sql = "select B.id,B.ISBN,B.Name,B.Author,B.Price,B.PressCount,B.Pressdate,C.AbbreviatedName,convert(nvarchar(10),B.Date,120) as date,sum(A.amount) as amount from stk_bookinfo A left join bs_bookcatalog B on A.BkcatalogID = B.id left join BS_PressInfo C on B.pressid = C.id where A.stgid = " + IntToStr(fstgid) ;
		}

		if (chisbn->Checked ) {
                       if (ISBN1=="") {
                         sql = sql + " and (B.ISBN ='' or B.Barcode is null) ";
                       }
			sql = sql + " and (B.ISBN like '%" + ISBN1 + "%' or B.Barcode like '%" + ISBN1 + "%')";
		}
		if (chname->Checked ) {
			sql = sql + " and B.name like '%" + Name + "%'";
		}
		if (chprice->Checked ) {
			sql = sql + " and B.price = " + FloatToStr(Price);
		}
		if (chauthor->Checked ) {
                         if (Author=="") {
                            sql = sql + " and (B.Author = '' or B.Author is null) ";
                         }else
			sql = sql + " and B.Author = '" + Author + "'";
		}
		if (chpress->Checked ) {
                       if (PressName=="") {
                            	sql = sql + " and (C.AbbreviatedName = '' or C.FULLNAME = '' or C.AbbreviatedName is null or C.FULLNAME is null)";
                       }else
			sql = sql + " and (C.AbbreviatedName = '" + PressName + "' or C.FULLNAME = '" + PressName + "')";
		}
		if (chpresscount->Checked ) {
			sql = sql  + " and (B.PressCount = '" + Presscount + "' or B.PressCount ='0"+Presscount+"') ";
		}
                if (cbselfma->Checked ) {
                    if (selfcode=="") {
                     sql = sql  + " and (B.userdefcode = '' or B.userdefcode is null)";
                    }
                    sql = sql  + " and B.userdefcode = '" + selfcode + "'";
                }
		sql = sql + " group by B.id,B.ISBN,B.Name,B.Author,B.Price,B.PressCount,B.Pressdate,C.AbbreviatedName,B.Date";
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->Open();
		if (query->RecordCount == 0) {

					if (chtishi->Checked) {
						AnsiString msg;
						msg = "是否新建书目:\n\nISBN:" + ISBN + "\n书名:" + Name + "\n定价:" + FloatToStr(Price) + "\n作者:" + Author + "\n出版社:" +  PressName + "\n版次:" +  Presscount ;

                                          // if (ShowMsg(Handle ,msg,1)==1) {


                                          // }

                                         }




							if (ISBN != "") {
								try {
									barcode = ISBNToBarcode(ISBN);
								} catch (...) {
								}
							}

							comAddcatalog->Parameters->ParamByName("@ISBN")->Value = ISBN;
							comAddcatalog->Parameters->ParamByName("@Name")->Value = Name;
							comAddcatalog->Parameters->ParamByName("@Price")->Value = Price;
							comAddcatalog->Parameters->ParamByName("@Author")->Value = Author;
							comAddcatalog->Parameters->ParamByName("@PressCount")->Value = Presscount;
							comAddcatalog->Parameters->ParamByName("@Press")->Value = PressName;
							comAddcatalog->Parameters->ParamByName("@pressindex")->Value = 0;
						     	comAddcatalog->Parameters->ParamByName("@barcode")->Value = barcode;
                                                        comAddcatalog->Parameters->ParamByName("@selfcode")->Value = selfcode;

							comAddcatalog->Parameters->ParamByName("@newbook")->Value = 0;

							try {
								comAddcatalog->Execute();
								bkcatalogid =  comAddcatalog->Parameters->ParamByName("@return_value")->Value;
								if (comAddcatalog->Parameters->ParamByName("@newbook")->Value == 1) {
									newbook = true;
                                                                     comaddnote->Parameters->ParamByName("@NtHeaderID")->Value = headerid;
                                                                            comaddnote->Parameters->ParamByName("@BkcatalogID")->Value = bkcatalogid ;
                                                                            comaddnote->Parameters->ParamByName("@Bsmode")->Value = mode;
                                                                            comaddnote->Parameters->ParamByName("@Amount")->Value = amount;
                                                                            comaddnote->Parameters->ParamByName("@Discount")->Value = discount;
                                                                            comaddnote->Parameters->ParamByName("@Stgid")->Value = fstgid;
                                                                            comaddnote->Parameters->ParamByName("@StackName")->Value = stackname;
                                                                         try {
                                                                            comaddnote->Execute();


                                                        } catch (...) {
                                                        }
								}


							} catch (...) {

							}






               }else if (query->RecordCount >= 1)
		{

				         	bkcatalogid =  query->FieldByName("id")->AsInteger ;

				        if (bkcatalogid  > -1) {
                                                        comaddnote->Parameters->ParamByName("@NtHeaderID")->Value = headerid;
                                                        comaddnote->Parameters->ParamByName("@BkcatalogID")->Value = bkcatalogid ;
                                                        comaddnote->Parameters->ParamByName("@Bsmode")->Value = mode;
                                                        comaddnote->Parameters->ParamByName("@Amount")->Value = amount;
                                                        comaddnote->Parameters->ParamByName("@Discount")->Value = discount;
                                                        comaddnote->Parameters->ParamByName("@Stgid")->Value = fstgid;
                                                        comaddnote->Parameters->ParamByName("@StackName")->Value = stackname;

                                                        try {
                                                                comaddnote->Execute();
                                                                inportamount++;

                                                        } catch (...) {
                                                        }
				            }
                 }

                }
		qry->Next();
		n = n + 1;
	}
	//dsdg->Append();
	Label1->Caption = "总共出记录" + IntToStr(qry->RecordCount) + "条，导入" + IntToStr(inportamount) + "条记录。" ;
	Label2->Visible = false;
	AnsiString message;
	message = "数据导入成功！";//总共导入" + IntToStr(inportamount) + "条记录。" ;
	MessageBoxA(0,message.c_str(),"Excel导入",MB_ICONEXCLAMATION);
	Import= true;
	con1->Connected = false;
	Screen->Cursor = crDefault ;
	ModalResult = mrOk ;

}void TfrmImport::qingchuangExcel()
{
  	if(edtExcelPath->Text == "")
		return;
    if (!chisbn->Checked && !chname->Checked && !chprice->Checked && !chauthor->Checked && !chpress->Checked ) {
		MessageBoxA(0,"请选择匹配项！","批量导入",MB_ICONEXCLAMATION);
		return;
	}
       String str = " Provider=Microsoft.Jet.OLEDB.4.0;Extended Properties=Excel 8.0;Persist Security Info=false;Data Source=";
              str = str +opndlgExcelPath->FileName;
       AnsiString sql;

	con1->ConnectionString = "";
	try
	{
		con1->ConnectionString =  str ;
	}
	catch(...)
	{
		MessageBoxA(0,"该数据已经导入！","Excel导入",MB_ICONEXCLAMATION);
		Import = true;
		return;
	}
	con1->LoginPrompt = false;
	con1->ConnectOptions = coConnectUnspecified ;
	con1->KeepConnection = true;
	con1->Mode = cmRead;
	try
	{
		 con1->Connected = true;
	}
	catch(...)
	{
		MessageBoxA(0,"数据源配置错误！","Excel导入",MB_ICONHAND);
		Import= true;
		return;
	}
        TStringList * tablelist;
        tablelist = new TStringList();
        con1->GetTableNames(tablelist,false);
     	qry->Connection = con1;
          AnsiString excelsql;
          excelsql = "select * from ["+tablelist->Strings[0]+"]";
      	qry->Active = false;
	qry->SQL->Clear();
       	qry->SQL ->Add(excelsql);
       	qry->Open();
	qry->Active = true;
	ds->DataSet = qry;

	Import= false;
	Label1->Caption = "总共出记录" + IntToStr(qry->RecordCount) + "条";
	Label2->Visible = true;
	Sleep(10);
	int inportamount = 0;
	int n = 0;

	AnsiString Stack;

        int bkstackid;
          //return;
          Screen->Cursor = crHourGlass ;
          qry->First();
          qry->Next();
	while (!qry->Eof)
	{        //F2(条码),F3名称,价格(定价),数量金额(数量),F6(折扣),F7(码洋),F8(实洋)

		int bkcatalogid = -1,amount = 0;
		bool newbook = false;
		double discount = 100.00,FixedPrice = 0.0,DiscountedPrice = 0.0,jprice = 0.0,Price = 0.0;
		AnsiString ISBN,ISBN1,Name,PressName,Author,remarks,Presscount,barcode,selfcode;
		try {
			Name = qry->FieldByName("F3")->AsAnsiString ;
			Name = Name.Trim();
                        if (Name=="") {
                            //书名为空，到了最后一行
                            qry->Next();
                            continue;
                        }
		} catch (...) {
		       	MessageBoxA(0,"请确认查询源文件中是否存在'书名'列！","查询出错",MB_ICONEXCLAMATION);
			qry->Close();
			con1->Connected =false;

			Screen->Cursor = crDefault ;
			return;
		}

		try {
			ISBN = qry->FieldByName("F2")->AsAnsiString.Trim() ;
                        if (ISBN=="无") {
                            ISBN="";
                        }
		} catch (...) {
        	if (chisbn->Checked ) {
				MessageBoxA(0,"请确认查询源文件中是否存在'ISBN'列！","查询出错",MB_ICONEXCLAMATION);
				qry->Close();
				con1->Connected =false;

				Screen->Cursor = crDefault ;
				return;
			}
		}
		if (ISBN != "") {
        	ISBN = ISBN.SubString(0,13);
			ISBN = GetNum(ISBN);
			ISBN1 = ISBN;
			if (ISBN1.Length()==10 || ISBN1.Length()==13 ) {
				ISBN1 = ISBN1.Delete(ISBN1.Length(),1);
			}
		}
		if ((mode == 1)||(mode == 2)) {





		try {
			Price = qry->FieldByName("价格")->AsFloat ;
		} catch (...) {
			if (chprice->Checked ) {
				MessageBoxA(0,"请确认查询源文件中是否存在'定价'列或定价是否正确！","查询出错",MB_ICONEXCLAMATION);
				qry->Close();
				con1->Connected =false;

				Screen->Cursor = crDefault ;
				return;
			}
			Price = 0;
		}


              	try {
                    if (cbselfma->Checked) {
                      selfcode = qry->FieldByName("自编码")->AsAnsiString ;
                    }

		} catch (...) {

		}

		try {
			amount = qry->FieldByName("数量金额")->AsInteger ;
		} catch (...) {
			amount = 0;
		}

		try {
			discount = qry->FieldByName("F6")->AsFloat ;
		} catch (...) {
			discount = 0.00;
		}


		if (mode == 1) {
			sql = "select B.id,B.ISBN,B.Name,B.Author,B.Price,B.PressCount,B.Pressdate,C.AbbreviatedName,convert(nvarchar(10),B.Date,120) as date,0 as amount from bs_bookcatalog B left join BS_PressInfo C on B.pressid = C.id where 1 = 1 " ;
		}
		else
		{
			sql = "select B.id,B.ISBN,B.Name,B.Author,B.Price,B.PressCount,B.Pressdate,C.AbbreviatedName,convert(nvarchar(10),B.Date,120) as date,sum(A.amount) as amount from stk_bookinfo A left join bs_bookcatalog B on A.BkcatalogID = B.id left join BS_PressInfo C on B.pressid = C.id where A.stgid = " + IntToStr(fstgid) ;
		}

		if (chisbn->Checked ) {
                       if (ISBN1=="") {
                         sql = sql + " and (B.ISBN ='' or B.Barcode is null) ";
                       }
			sql = sql + " and (B.ISBN like '%" + ISBN1 + "%' or B.Barcode like '%" + ISBN1 + "%')";
		}
		if (chname->Checked ) {
			sql = sql + " and B.name like '%" + Name + "%'";
		}
		if (chprice->Checked ) {
			sql = sql + " and B.price = " + FloatToStr(Price);
		}





		sql = sql + " group by B.id,B.ISBN,B.Name,B.Author,B.Price,B.PressCount,B.Pressdate,C.AbbreviatedName,B.Date";
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->Open();
		if (query->RecordCount == 0) {

					if (false) {
						AnsiString msg;
						msg = "是否新建书目:\n\nISBN:" + ISBN + "\n书名:" + Name + "\n定价:" + FloatToStr(Price) + "\n作者:" + Author + "\n出版社:" +  PressName + "\n版次:" +  Presscount ;

						if (ShowMsg(Handle ,msg,1)==1) {

							if (ISBN != "") {
								try {
									barcode = ISBNToBarcode(ISBN);
								} catch (...) {
								}
							}

							comAddcatalog->Parameters->ParamByName("@ISBN")->Value = ISBN;
							comAddcatalog->Parameters->ParamByName("@Name")->Value = Name;
							comAddcatalog->Parameters->ParamByName("@Price")->Value = Price;
							comAddcatalog->Parameters->ParamByName("@Author")->Value = Author;
							comAddcatalog->Parameters->ParamByName("@PressCount")->Value = Presscount;
							comAddcatalog->Parameters->ParamByName("@Press")->Value = PressName;
							comAddcatalog->Parameters->ParamByName("@pressindex")->Value = 0;
						     	comAddcatalog->Parameters->ParamByName("@barcode")->Value = barcode;
                                                       comAddcatalog->Parameters->ParamByName("@selfcode")->Value = selfcode;
							comAddcatalog->Parameters->ParamByName("@newbook")->Value = 0;

							try {
								comAddcatalog->Execute();
								bkcatalogid =  comAddcatalog->Parameters->ParamByName("@return_value")->Value;
								if (comAddcatalog->Parameters->ParamByName("@newbook")->Value == 1) {
									newbook = true;
                                                                     comaddnote->Parameters->ParamByName("@NtHeaderID")->Value = headerid;
                                                                            comaddnote->Parameters->ParamByName("@BkcatalogID")->Value = bkcatalogid ;
                                                                            comaddnote->Parameters->ParamByName("@Bsmode")->Value = mode;
                                                                            comaddnote->Parameters->ParamByName("@Amount")->Value = amount;
                                                                            comaddnote->Parameters->ParamByName("@Discount")->Value = discount;
                                                                            comaddnote->Parameters->ParamByName("@Stgid")->Value = fstgid;
                                                                            comaddnote->Parameters->ParamByName("@StackName")->Value = stackname;
                                                                         try {
                                                                            comaddnote->Execute();


                                                        } catch (...) {
                                                        }
								}


							} catch (...) {

							}
						}


			}


               }else if (query->RecordCount >= 1)
		{

				         	bkcatalogid =  query->FieldByName("id")->AsInteger ;

				        if (bkcatalogid  > -1) {
                                                        comaddnote->Parameters->ParamByName("@NtHeaderID")->Value = headerid;
                                                        comaddnote->Parameters->ParamByName("@BkcatalogID")->Value = bkcatalogid ;
                                                        comaddnote->Parameters->ParamByName("@Bsmode")->Value = mode;
                                                        comaddnote->Parameters->ParamByName("@Amount")->Value = amount;
                                                        comaddnote->Parameters->ParamByName("@Discount")->Value = discount;
                                                        comaddnote->Parameters->ParamByName("@Stgid")->Value = fstgid;
                                                        comaddnote->Parameters->ParamByName("@StackName")->Value = stackname;

                                                        try {
                                                                comaddnote->Execute();
                                                                inportamount++;

                                                        } catch (...) {
                                                        }
				            }
                 }

                }
		qry->Next();
		n = n + 1;
	}

	Label1->Caption = "总共出记录" + IntToStr(qry->RecordCount) + "条，导入" + IntToStr(inportamount) + "条记录。" ;
	Label2->Visible = false;
	AnsiString message;
	message = "数据导入成功！";//总共导入" + IntToStr(inportamount) + "条记录。" ;
	MessageBoxA(0,message.c_str(),"Excel导入",MB_ICONEXCLAMATION);
	Import= true;
	con1->Connected = false;
	Screen->Cursor = crDefault ;
	ModalResult = mrOk ;




}
//---------------------------------------------------------------------------
 AnsiString TfrmImport::GetSelfCode(AnsiString bookname)
 {

                	char* t;
			char t2;
			String t1,t3,t4;
			t1 = bookname;//.TrimLeft().TrimLeft()  ;//.TrimRight();//  .TrimLeft()  ;
			int t5=1,i = bookname.Length();
			for( int j=1;j<=i;j++)
			{

			t3 = t1.SubString(j,1);
			t = t3.t_str();

			Word k = int (t[0])<<8;
			k = k >> 8;
                        if (k<=58&&k>=48) {    //数字
                          t4=t4+t3;
                        }
			if(k<160) continue;
			t5++;
			if (t5 == 9) break;
			t = t3.t_str();
			t2 = GetPYIndexChar(t);
			t4 = t4 + t2;
			}

 }
char TfrmImport::GetPYIndexChar(char *str)
 {
   Word x = 0;
	Word y = 0;//int y = 0;
	 x = (int(str[0]))<<8;
	 y = (int(str[1]))<<8;
	 y = y>>8;
	 x = x + y;//str[1];
	Word Address[] = { 0xB0C4,0xB2C0,0xB4ED,0xB6E9,0xB7A1,
	0xB8C0,0xB9FD,0xBBF6,0xBFA5,0xC0AB,
	0xC2E7,0xC4C2,0xC5B5,0xC5BD,0xC6D9,
	0xC8BA,0xC8F5,0xCBF9,0xCDD9,0xCEF3,
	0xD188,0xD4D0,0xD7F9 };
	char Rchar[25] = "ABCDEFGHJKLMNOPQRSTWXYZ ";
	int i=0;
	for(;i<24;i++)
	if(Address[i] >= x) break;
	return Rchar[i];

 }
void __fastcall TfrmImport::BtnExitClick(TObject *Sender)
{
	if (Import) {
	  	Close();
	}else
	{
		MessageBoxA(0,"正在导入中，不能退出！","Excel导入",MB_ICONASTERISK);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmImport::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F7) {     //导入
		BtnImport->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 81 ) {    //退出
		BtnExit->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==90) {   //恢复窗口
		WindowState = wsNormal  ;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmImport::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------
AnsiString TfrmImport::GetNum(AnsiString Anstr)
{	AnsiString strnum;	for(int i=1;i<=Anstr.Length();i++)	{		if((Anstr[i] >= '0' && Anstr[i] <= '9') || Anstr[i] == 'X' || Anstr[i] == 'x' )		{		 	strnum = strnum + Anstr[i];		}	}	return strnum;}//---------------------------------------------------------------------------



void __fastcall TfrmImport::BtnImportClick(TObject *Sender)
{
      switch(radiogroup->ItemIndex)
      {
         case 0:
               xianxingze();
          break;
         case 1:
                yihuadaoru();
         break;
         case 2:
                qingchuangExcel();
         break;



      }
}
void TfrmImport::yihuadaoru()
{
if(edtExcelPath->Text == "")
		return;
    if (!chisbn->Checked && !chname->Checked && !chprice->Checked && !chauthor->Checked && !chpress->Checked ) {
		MessageBoxA(0,"请选择匹配项！","批量导入",MB_ICONEXCLAMATION);
		return;
	}
       String str = " Provider=Microsoft.Jet.OLEDB.4.0;Extended Properties=Excel 8.0;Persist Security Info=false;Data Source=";
              str = str +opndlgExcelPath->FileName;
       AnsiString sql;
       AnsiString selfcode;

	con1->ConnectionString = "";
	try
	{
		con1->ConnectionString =  str ;
	}
	catch(...)
	{
		MessageBoxA(0,"该数据已经导入！","Excel导入",MB_ICONEXCLAMATION);
		Import = true;
		return;
	}
	con1->LoginPrompt = false;
	con1->ConnectOptions = coConnectUnspecified ;
	con1->KeepConnection = true;
	con1->Mode = cmRead;
	try
	{
		 con1->Connected = true;
	}
	catch(...)
	{
		MessageBoxA(0,"数据源配置错误！","Excel导入",MB_ICONHAND);
		Import= true;
		return;
	}
        TStringList * tablelist;
        tablelist = new TStringList();
        con1->GetTableNames(tablelist,false);
     	qry->Connection = con1;
          AnsiString excelsql;
          excelsql = "select * from ["+tablelist->Strings[0]+"]";
      	qry->Active = false;
	qry->SQL->Clear();
       	qry->SQL ->Add(excelsql);
       	qry->Open();
	qry->Active = true;
	ds->DataSet = qry;

	Import= false;
	Label1->Caption = "总共出记录" + IntToStr(qry->RecordCount) + "条";
	Label2->Visible = true;
	Sleep(10);
	int inportamount = 0;
	int n = 0;

	AnsiString Stack;


        int bkstackid;
          //return;
          Screen->Cursor = crHourGlass ;
          qry->First();
          qry->Next();
	while (!qry->Eof)
	{        //书号 图书名称 出版社    数量  定价 折扣

		int bkcatalogid = -1,amount = 0;
		bool newbook = false;
		double discount = 100.00,FixedPrice = 0.0,DiscountedPrice = 0.0,jprice = 0.0,Price = 0.0;
		AnsiString ISBN,ISBN1,Name,PressName,Author,remarks,Presscount,barcode,selfcode;
		try {
			Name = qry->FieldByName("图书名称")->AsAnsiString ;
			Name = Name.Trim();
                        if (Name=="") {
                            //书名为空，到了最后一行
                            qry->Next();
                            continue;
                        }
		} catch (...) {
		       	MessageBoxA(0,"请确认查询源文件中是否存在'图书名称'列！","查询出错",MB_ICONEXCLAMATION);
			qry->Close();
			con1->Connected =false;

			Screen->Cursor = crDefault ;
			return;
		}

		try {
                       if (chisbn->Checked) {
                        	ISBN = qry->FieldByName("ISBN号")->AsAnsiString.Trim() ;

                       }// else ISBN ='';
		//if (ISBN=="") {
                         //   ISBN="";
                       // }
		} catch (...) {
        	if (chisbn->Checked ) {
				MessageBoxA(0,"请确认查询源文件中是否存在'书号'列！","查询出错",MB_ICONEXCLAMATION);
				qry->Close();
				con1->Connected =false;

				Screen->Cursor = crDefault ;
				return;
			}
		}
		if (ISBN != "") {
        	ISBN = ISBN.SubString(0,13);
			ISBN = GetNum(ISBN);
			ISBN1 = ISBN;
			if (ISBN1.Length()==10 || ISBN1.Length()==13 ) {
				ISBN1 = ISBN1.Delete(ISBN1.Length(),1);
			}
		}
		if ((mode == 1)||(mode == 2)) {





		try {
			Price = qry->FieldByName("定价")->AsFloat ;
                        if (Price<=1) {
                           Price = Price*100;
                        }
		} catch (...) {
			if (chprice->Checked ) {
				MessageBoxA(0,"请确认查询源文件中是否存在'定价'列或定价是否正确！","查询出错",MB_ICONEXCLAMATION);
				qry->Close();
				con1->Connected =false;

				Screen->Cursor = crDefault ;
				return;
			}
			Price = 0;
		}

		try {
			amount = qry->FieldByName("数量")->AsInteger ;
		} catch (...) {
			amount = 0;
		}

		try {
			discount = qry->FieldByName("折扣")->AsFloat ;
                        discount = discount * 100;
		} catch (...) {
			discount = 100.00;
		}


		if (mode == 1) {
			sql = "select B.id,B.ISBN,B.Name,B.Author,B.Price,B.PressCount,B.Pressdate,C.AbbreviatedName,convert(nvarchar(10),B.Date,120) as date,0 as amount from bs_bookcatalog B left join BS_PressInfo C on B.pressid = C.id where 1 = 1 " ;
		}
		else
		{
			sql = "select B.id,B.ISBN,B.Name,B.Author,B.Price,B.PressCount,B.Pressdate,C.AbbreviatedName,convert(nvarchar(10),B.Date,120) as date,sum(A.amount) as amount from stk_bookinfo A left join bs_bookcatalog B on A.BkcatalogID = B.id left join BS_PressInfo C on B.pressid = C.id where A.stgid = " + IntToStr(fstgid) ;
		}

		if (chisbn->Checked ) {
                       if (ISBN1=="") {
                         sql = sql + " and (B.ISBN ='' or B.Barcode is null) ";
                       }
			sql = sql + " and (B.ISBN like '%" + ISBN1 + "%' or B.Barcode like '%" + ISBN1 + "%')";
		}
		if (chname->Checked ) {
			sql = sql + " and B.name like '%" + Name + "%'";
		}
		if (chprice->Checked ) {
			sql = sql + " and B.price = " + FloatToStr(Price);
		}

                try
                {

                 if (chpress->Checked) {
                   PressName = qry->FieldByName("出版社")->AsAnsiString ;

                 }

                }
                catch(...)
                {
                }
                  try
                {

                 if (cbselfma->Checked) {
                   selfcode = qry->FieldByName("自编码")->AsAnsiString ;

                 }

                }
                catch(...)
                {
                }


		sql = sql + " group by B.id,B.ISBN,B.Name,B.Author,B.Price,B.PressCount,B.Pressdate,C.AbbreviatedName,B.Date";
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->Open();
		if (query->RecordCount == 0) {

					if (chtishi->Checked) {
						AnsiString msg;
						msg = "是否新建书目:\n\nISBN:" + ISBN + "\n书名:" + Name + "\n定价:" + FloatToStr(Price) + "\n作者:" + Author + "\n出版社:" +  PressName + "\n版次:" +  Presscount ;

						if (ShowMsg(Handle ,msg,1)==1) {

							if (ISBN != "") {
								try {
									barcode = ISBNToBarcode(ISBN);
								} catch (...) {
								}
							}
                                                }
                                                }
							comAddcatalog->Parameters->ParamByName("@ISBN")->Value = ISBN;
							comAddcatalog->Parameters->ParamByName("@Name")->Value = Name;
							comAddcatalog->Parameters->ParamByName("@Price")->Value = Price;
							comAddcatalog->Parameters->ParamByName("@Author")->Value = Author;
							comAddcatalog->Parameters->ParamByName("@PressCount")->Value = Presscount;
							comAddcatalog->Parameters->ParamByName("@Press")->Value = PressName;
							comAddcatalog->Parameters->ParamByName("@pressindex")->Value = 0;
						     	comAddcatalog->Parameters->ParamByName("@barcode")->Value = barcode;
                                                        comAddcatalog->Parameters->ParamByName("@selfcode")->Value = selfcode;
							comAddcatalog->Parameters->ParamByName("@newbook")->Value = 0;


							try {
								comAddcatalog->Execute();
								bkcatalogid =  comAddcatalog->Parameters->ParamByName("@return_value")->Value;
								if (comAddcatalog->Parameters->ParamByName("@newbook")->Value == 1) {
									newbook = true;
                                                                     comaddnote->Parameters->ParamByName("@NtHeaderID")->Value = headerid;
                                                                            comaddnote->Parameters->ParamByName("@BkcatalogID")->Value = bkcatalogid ;
                                                                            comaddnote->Parameters->ParamByName("@Bsmode")->Value = mode;
                                                                            comaddnote->Parameters->ParamByName("@Amount")->Value = amount;
                                                                            comaddnote->Parameters->ParamByName("@Discount")->Value = discount;
                                                                            comaddnote->Parameters->ParamByName("@Stgid")->Value = fstgid;
                                                                            comaddnote->Parameters->ParamByName("@StackName")->Value = stackname;
                                                                         try {
                                                                            comaddnote->Execute();


                                                        } catch (...) {
                                                        }
								}


							} catch (...) {

							}






               }else if (query->RecordCount >= 1)
		{

				         	bkcatalogid =  query->FieldByName("id")->AsInteger ;

				        if (bkcatalogid  > -1) {
                                                        comaddnote->Parameters->ParamByName("@NtHeaderID")->Value = headerid;
                                                        comaddnote->Parameters->ParamByName("@BkcatalogID")->Value = bkcatalogid ;
                                                        comaddnote->Parameters->ParamByName("@Bsmode")->Value = mode;
                                                        comaddnote->Parameters->ParamByName("@Amount")->Value = amount;
                                                        comaddnote->Parameters->ParamByName("@Discount")->Value = discount;
                                                        comaddnote->Parameters->ParamByName("@Stgid")->Value = fstgid;
                                                        comaddnote->Parameters->ParamByName("@StackName")->Value = stackname;

                                                        try {
                                                                comaddnote->Execute();
                                                                inportamount++;

                                                        } catch (...) {
                                                        }
				            }
                 }

                }
		qry->Next();
		n = n + 1;
	}

	Label1->Caption = "总共出记录" + IntToStr(qry->RecordCount) + "条，导入" + IntToStr(inportamount) + "条记录。" ;
	Label2->Visible = false;
	AnsiString message;
	message = "数据导入成功！";//总共导入" + IntToStr(inportamount) + "条记录。" ;
	MessageBoxA(0,message.c_str(),"Excel导入",MB_ICONEXCLAMATION);
	Import= true;
	con1->Connected = false;
	Screen->Cursor = crDefault ;
	ModalResult = mrOk ;





}
//---------------------------------------------------------------------------


void __fastcall TfrmImport::radiogroupClick(TObject *Sender)
{
  if (radiogroup->ItemIndex==1) {
    chpress->Checked=false;

  }
}
//---------------------------------------------------------------------------

