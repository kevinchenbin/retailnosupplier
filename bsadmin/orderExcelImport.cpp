//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "orderExcelImport.h"
#include "orderimportselect.h"
#include "pdutil.h"
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
TfrmExcelImport *frmExcelImport;
//---------------------------------------------------------------------------
__fastcall TfrmExcelImport::TfrmExcelImport(TComponent* Owner,TADOConnection *con,int headid)
	: TForm(Owner)
{
   Import= true;
   aq->Connection = con;
   aq->Active = false;
   aq->Active = true;
   headerid = headid;
   query->Connection = con;
   comAddcatalog->Connection = con;
}

//---------------------------------------------------------------------------

void __fastcall TfrmExcelImport::spselectpathClick(TObject *Sender)
{
	if (opndlgExcelPath->Execute())
	{
		String DBPath,Name;
		DBPath = ExtractFilePath(opndlgExcelPath->FileName .c_str()  );
		Name = ExtractFileName(opndlgExcelPath->FileName .c_str() );
		DBPath = DBPath + Name;
		edtExcelPath->Text = DBPath;
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmExcelImport::BtnImportClick(TObject *Sender)
{
	if(edtExcelPath->Text == "")
		return;
	/*if (!chisbn->Checked && !chname->Checked && !chprice->Checked && !chauthor->Checked && !chpress->Checked && !chpresscount->Checked && !chamount->Checked && !chdiscount->Checked && !chbk->Checked  ) {
		return;
	} */
	if (!chname->Checked ) {
        MessageBoxA(0,"书名为必选项！","导入",MB_ICONEXCLAMATION);
		return;
	}

	Variant vExcelApp,vSheet,Wb;
	vExcelApp = Variant::CreateObject("Excel.Application");
	AnsiString s = ExtractFilePath(opndlgExcelPath->FileName .c_str());
	s = s + ExtractFileName(opndlgExcelPath->FileName .c_str() );
	vExcelApp.OlePropertyGet("WorkBooks").OleProcedure("Open",s.c_str()   );// opndlgExcelPath->f  FileName .c_str() );
	Wb = vExcelApp.OlePropertyGet("ActiveWorkBook");
	vSheet = Wb.OlePropertyGet("ActiveSheet");
	vSheet.OlePropertySet("name","11");
	Wb.OleProcedure("Save");


	//String sql = "select * from " + ExtractFileName(opndlgExcelPath->FileName .c_str() ) ;
	//EXCEL导入
	String sql = "select * from [11$]";

	String str = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=";
	//EXCEL导入
	str = str + edtExcelPath->Text ;
	str = str + ";Mode=Read;Extended Properties=\"Excel 8.0;HDR=Yes;IMEX=1\";" ;

	//CSV导入
	//str = str + ExtractFilePath(opndlgExcelPath->FileName .c_str()) ;
	//str = str + ";Mode=Read;Extended Properties=\"text;HDR=Yes;IMEX=1;FMT=Delimited\";" ;

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
	qry->Connection = con1;
	qry->Active = false;
	qry->SQL->Clear();
	qry->SQL ->Add(sql);
	qry->Active = true;
	ds->DataSet = qry;


  //	con1->Connected =false;
   //	vExcelApp.OlePropertyGet("ActiveWorkBook").OleProcedure("Close");
  //	vExcelApp.OleFunction("Quit");



	Import= false;
	Label1->Caption = "总载出记录" + IntToStr(qry->RecordCount) + "条";
	Label2->Visible = true;
	Sleep(10);
	int inportamount = 0;
	int n = 0;
	while (!qry->Eof)
	{
		int bkcatalogid = -1,amount = 0,  pressindex = 2;
		bool newbook = false;
		float discount = 100.00,FixedPrice = 0.0,DiscountedPrice = 0.0,jprice = 0.0,Price = 0.0;
		AnsiString ISBN,Name,PressName,Author,remarks,xuexiao,classname,barcode,Num,xiaoqu,xueyuan,course,incode,teacher,telphone;
		try {
			Name = qry->FieldByName("书名")->AsString ;
			Name = Name.Trim();
		} catch (...) {
			MessageBoxA(0,"请确认导入文件中是否存在'书名'列！","导入出错",MB_ICONEXCLAMATION);
			Import= true;
			Label2->Visible = false;
			qry->Close();
			con1->Connected =false;
			vExcelApp.OleProcedure("Quit");
			vExcelApp = Unassigned;
			return;
		}
		if (chxuexuao->Checked ) {
			try {
				xuexiao = qry->FieldByName("学校序号")->AsAnsiString ;
			} catch (...) {

			}
		}
		if (chclass->Checked ) {
			try {
				classname = qry->FieldByName("班级")->AsAnsiString ;
			} catch (...) {

			}
		}
		if (chisbn->Checked ) {
			try {
				ISBN = qry->FieldByName("ISBN")->AsString ;
				int len = ISBN.Pos('/');
				if (len > 3) {
					ISBN = ISBN.SubString(0,len-1);
				}
				if (ISBN != "") {
					ISBN = GetNum(ISBN);
				}

			} catch (...) {

			}
		}
		if (chprice->Checked ) {
			try {
				Price = qry->FieldByName("定价")->AsFloat ;
			} catch (...) {
				Price = 0;
			}
		}
		if (chauthor->Checked ) {
			try {
				Author = qry->FieldByName("作者")->AsAnsiString;
			} catch (...) {

			}
		}
		if (chpress->Checked ) {
			try {
				PressName = qry->FieldByName("出版社")->AsAnsiString ;
				PressName = PressName.Trim();
			} catch (...) {

			}
		}

	       //	try {
		//	pressindex = qry->FieldByName("版别识别")->AsInteger ;
		//} catch (...) {
	       //		pressindex = 2;
		//}
                pressindex=2;

		if (chpresscount->Checked ) {
			try {
				Num = qry->FieldByName("版次")->AsAnsiString ;
			} catch (...) {

			}
		}
		if (chamount->Checked ) {
			try {
				if (qry->FieldByName("数量")->AsAnsiString != "") {
					amount = qry->FieldByName("数量")->AsInteger ;
				}
			} catch (...) {
				MessageBoxA(0,"请确认导入文件中是否存在'数量'列或数量是否正确！","导入出错",MB_ICONEXCLAMATION);
				Import= true;
				Label2->Visible = false;
				qry->Close();
				con1->Connected =false;
				vExcelApp.OleProcedure("Quit");
				vExcelApp = Unassigned;
				return;
			}
		}
		if (chdiscount->Checked ) {
			try {
				discount = qry->FieldByName("折扣")->AsFloat ;
			} catch (...) {
				discount = 100;
			}
		}
		if (chbk->Checked ) {
			try {
				remarks = qry->FieldByName("备注")->AsString ;
			} catch (...) {

			}
		}
		if (chxiaoqu->Checked ) {
			try {
				xiaoqu = qry->FieldByName("校区")->AsAnsiString;
			} catch (...) {

			}
		}
		if (chxueyuan->Checked ) {
			try {
				xueyuan = qry->FieldByName("学院")->AsAnsiString;
			} catch (...) {

			}
		}
		if (chcourse->Checked ) {
			try {
				course = qry->FieldByName("课程名称")->AsAnsiString;
			} catch (...) {

			}
		}
		if (chincode->Checked ) {
			try {
				incode = qry->FieldByName("内部识别码")->AsAnsiString;
			} catch (...) {

			}
		}
		if (chteacher->Checked ) {
			try {
				teacher = qry->FieldByName("任课教师")->AsAnsiString;
			} catch (...) {

			}
		}
		if (chtelphone->Checked ) {
			try {
				telphone = qry->FieldByName("联系方式")->AsAnsiString;
			} catch (...) {

			}
		}
		if (Name != "") {
			sql = "select A.id,A.ISBN,A.Name,A.Author,A.Price,A.PressCount,A.Pressdate,B.AbbreviatedName,convert(nvarchar(10),A.Date,120) as date from BS_BookCatalog A left join BS_PressInfo B on A.PressID = B.id where A.Name like '%" + Name + "%'";
			if (pressindex == 1) {
				sql = sql + " and B.FULLNAME = '" + PressName + "' order by A.id desc";
			}
			else
			{
				sql = sql + " and isnull(B.AbbreviatedName,'') = '" + PressName + "' order by A.id desc";
			}
			query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->Open();
			if (query->RecordCount == 1) {
				bkcatalogid = query->FieldByName("id")->AsInteger ;
				jprice = query->FieldByName("Price")->AsFloat ;
			}
			if (query->RecordCount > 1) {
				Tfrmorderimportselect *frm = new Tfrmorderimportselect(Application,query);
				frm->userid = fuserid;
				frm->stgid = fstgid;
				frm->orderbook =  Name;
				frm->orderpress =  PressName;
				frm->showorderbook();
				if (frm->ShowModal() == mrOk  ) {
					if (frm->newbook ) {
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
						comAddcatalog->Parameters->ParamByName("@PressCount")->Value = Num;
						comAddcatalog->Parameters->ParamByName("@Press")->Value = PressName;
						comAddcatalog->Parameters->ParamByName("@pressindex")->Value = pressindex;
						comAddcatalog->Parameters->ParamByName("@barcode")->Value = barcode;
						comAddcatalog->Parameters->ParamByName("@newbook")->Value = 0;

                        try {
							comAddcatalog->Execute();
							bkcatalogid =  comAddcatalog->Parameters->ParamByName("@return_value")->Value;
							if (comAddcatalog->Parameters->ParamByName("@newbook")->Value == 1) {
								newbook = true;
								try {
									vExcelApp.OlePropertyGet("Cells",2+n,1).OlePropertySet("Value","新建该书" );
								} catch (...) {
								}
							}
							else
							{
								try {
									vExcelApp.OlePropertyGet("Cells",2+n,1).OlePropertySet("Value","无与导入出版社相匹配的书目，但书目库有该书" );
								} catch (...) {
								}
							}
							jprice = Price ;

						} catch (...) {
							try {
								vExcelApp.OlePropertyGet("Cells",2+n,1).OlePropertySet("Value","新书创建失败" );
							} catch (...) {
							}
							//MessageBoxA(0,"新建书目不成功！","Excel导入",MB_ICONEXCLAMATION);
						}

					}
					else
					{
						bkcatalogid = query->FieldByName("id")->AsInteger ;
						jprice = query->FieldByName("Price")->AsFloat ;
					}
				}
			}
			if (query->RecordCount == 0) {
				if (chtishi->Checked ) {
					AnsiString msg;
					msg = "是否新建书目:\nISBN:" + ISBN + "\n书名:" + Name + "\n定价:" + FloatToStr(Price) + "\n作者:" + Author + "\n出版社:" +  PressName + "\n版次:" +  Num ;
					if (MessageBoxA(0,msg.c_str(),"询问",MB_ICONQUESTION|MB_OKCANCEL)==1 ){
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
						comAddcatalog->Parameters->ParamByName("@PressCount")->Value = Num;
						comAddcatalog->Parameters->ParamByName("@Press")->Value = PressName;
						comAddcatalog->Parameters->ParamByName("@pressindex")->Value = pressindex;
						comAddcatalog->Parameters->ParamByName("@barcode")->Value = barcode;
						comAddcatalog->Parameters->ParamByName("@newbook")->Value = 0;

						try {
							comAddcatalog->Execute();
							bkcatalogid =  comAddcatalog->Parameters->ParamByName("@return_value")->Value;
							if (comAddcatalog->Parameters->ParamByName("@newbook")->Value == 1) {
								newbook = true;
								try {
									vExcelApp.OlePropertyGet("Cells",2+n,1).OlePropertySet("Value","新建该书" );
								} catch (...) {
								}
							}
							else
							{
								try {
									vExcelApp.OlePropertyGet("Cells",2+n,1).OlePropertySet("Value","无与导入出版社相匹配的书目，但书目库有该书" );
								} catch (...) {
								}
							}
							jprice = Price ;
						} catch (...) {
							try {
								vExcelApp.OlePropertyGet("Cells",2+n,1).OlePropertySet("Value","新书创建失败" );
							} catch (...) {
							}

							//MessageBoxA(0,"新建书目不成功！","Excel导入",MB_ICONEXCLAMATION);
						}

					}
				}
				else
				{
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
					comAddcatalog->Parameters->ParamByName("@PressCount")->Value = Num;
					comAddcatalog->Parameters->ParamByName("@Press")->Value = PressName;
					comAddcatalog->Parameters->ParamByName("@pressindex")->Value = pressindex;
					comAddcatalog->Parameters->ParamByName("@barcode")->Value = barcode;
					comAddcatalog->Parameters->ParamByName("@newbook")->Value = 0;
					try {
						comAddcatalog->Execute();
						bkcatalogid =  comAddcatalog->Parameters->ParamByName("@return_value")->Value;
						if (comAddcatalog->Parameters->ParamByName("@newbook")->Value == 1) {
							newbook = true;
							try {
								vExcelApp.OlePropertyGet("Cells",2+n,1).OlePropertySet("Value","新建该书" );
							} catch (...) {
							}
						}
						else
						{
							try {
								vExcelApp.OlePropertyGet("Cells",2+n,1).OlePropertySet("Value","无与导入出版社相匹配的书目，但书目库有该书" );
							} catch (...) {
							}
						}
						jprice = Price ;


					} catch (...) {
						try {
							vExcelApp.OlePropertyGet("Cells",2+n,1).OlePropertySet("Value","新书创建失败" );
						} catch (...) {
						}
						//MessageBoxA(0,"新建书目不成功！","Excel导入",MB_ICONEXCLAMATION);
					}

				}
			}
			FixedPrice =  jprice*amount;
			DiscountedPrice = jprice*amount*discount/100;
			if (bkcatalogid >= 0) {
				if (aq->State != dsInsert) {
					aq->Append();
                }
					aq->FieldByName("OrderNtHeaderID")->AsInteger = headerid;
					aq->FieldByName("BkcatalogID")->AsInteger = bkcatalogid;
					aq->FieldByName("Amount")->AsInteger =  amount;
					aq->FieldByName("UnsendAmount")->AsInteger = amount;
					aq->FieldByName("Discount")->AsFloat = discount;
					aq->FieldByName("FixedPrice")->AsFloat = FixedPrice ;
					aq->FieldByName("DiscountedPrice")->AsFloat = DiscountedPrice ;
					aq->FieldByName("bk")->AsString = remarks;
					aq->FieldByName("xuxiao")->AsString = xuexiao;
					aq->FieldByName("class")->AsString = classname;
					aq->FieldByName("newbook")->AsBoolean  = newbook;
					aq->FieldByName("xiaoqu")->AsString = xiaoqu;
					aq->FieldByName("xueyuan")->AsString = xueyuan;
					aq->FieldByName("course")->AsString = course;
					aq->FieldByName("incode")->AsString = incode;
					aq->FieldByName("teacher")->AsString = teacher;
					aq->FieldByName("telphone")->AsString = telphone;
					try {
						aq->Post();
						inportamount = inportamount + 1;
					} catch (...) {
						try {
							vExcelApp.OlePropertyGet("Cells",2+n,1).OlePropertySet("Value","导入失败" );
						} catch (...) {
						}
					}
			}
		}
		qry->Next();
		n = n + 1;
	}
	//dsdg->Append();
	Label1->Caption = "总载出记录" + IntToStr(qry->RecordCount) + "条，导入" + IntToStr(inportamount) + "条记录。" ;
	Label2->Visible = false;
	AnsiString message;
	message = "数据导入成功！总共导入" + IntToStr(inportamount) + "条记录。" ;
	MessageBoxA(0,message.c_str(),"Excel导入",MB_ICONEXCLAMATION);
	Import= true;

	//Wb.OleProcedure("Save");
        vExcelApp.OlePropertyGet("WorkBooks").OleProcedure("Close");
       //	Wb.OleProcedure("Close");
	con1->Connected =false;
	vExcelApp.OleProcedure("Quit");
	vExcelApp = Unassigned;

	ModalResult = mrOk ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmExcelImport::BtnExitClick(TObject *Sender)
{
  if (Import) {
	  Close();
  }else
  {

          ShowMsg(Handle ,"正在导入中，不能退出！",3);
  }
}
//---------------------------------------------------------------------------



void __fastcall TfrmExcelImport::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F7) {     //导入
		BtnImport->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 78 ) {    //最小化
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 81 ) {    //退出
		BtnExit->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==90) {   //恢复窗口
		WindowState = wsNormal  ;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmExcelImport::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------
AnsiString TfrmExcelImport::GetNum(AnsiString Anstr)
{
	AnsiString strnum;
	for(int i=1;i<=Anstr.Length();i++)
	{
		if((Anstr[i] >= '0' && Anstr[i] <= '9') || Anstr[i] == 'X' || Anstr[i] == 'x' )
		{
		 	strnum = strnum + Anstr[i];
		}
	}
	return strnum;
}
//---------------------------------------------------------------------------


