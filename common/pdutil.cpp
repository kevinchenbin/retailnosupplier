//---------------------------------------------------------------------------


#pragma hdrstop

#include "pdutil.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

TDateTime GetDBTime(TADOQuery* qry)
{
	qry->Close();
	qry->SQL->Clear();
	qry->SQL->Add("Select Convert(Varchar(20), GetDate(), 20)");
	qry->Open();
	qry->First();
	TDateTime dt;
	dt = TDateTime::CurrentDateTime();
	if (!qry->IsEmpty())
	{
		String time = qry->Fields->FieldByNumber(1)->AsString;
		int y,m,d,hh,mm,ss;
		y = time.SubString(0,4).ToInt();
		m = time.SubString(6,2).ToInt();
		d = time.SubString(9,2).ToInt();
		hh = time.SubString(12,2).ToInt();
		mm = time.SubString(15,2).ToInt();
		ss = time.SubString(18,2).ToInt();
        dt = TDateTime(y, m, d, hh, mm, ss, 0);
	}
	qry->Close();
	return dt;
}
//-----------------
String ISBNToBarcode(String ss)
{
	int oddSum = 0,evenSum = 0,Sum=0,temp;
	String tail;
	temp = ss.Length() - ss.Pos(" ")+1;
	ss=ss.Delete(ss.Pos(" "),temp);
	if(ss.Length() == 13 )
	return ss;
	else
	if(ss.Length() == 10 )
	ss = IntToStr(978)+ss;
	for(int i=2;i<ss.Length();i+=2)
	oddSum = oddSum + StrToInt(ss[i]);
	oddSum *= 3;
	for(int i=1;i<ss.Length();i+=2 )
	evenSum = evenSum + StrToInt(ss[i]);
	Sum = oddSum + evenSum;
	if(Sum%10 == 0)
	tail = "0";
	else
	tail = IntToStr((Sum/10 + 1)*10-Sum);
	int j = ss.Length()-1;
	ss.Delete(ss.Length(),1 );

	ss = ss+tail;
	//ss = "978" + ss;
	return ss;

}
//--------------
String BuildISBNCode(String ss)
{
	if(ss == "")
	{
		return "";
	}
	else
	{
		String t;
	   int i,k,rs[9];
	   t="hello" ;
	   //ShowMessage(t);
	   k = StringToIsbn(ss,rs);
	   String t1;
	   for(i=0;i<9;i++)
	   t1 = t1 + IntToStr(rs[i]);
	   //ShowMessage(t1);
	   //ShowMessage(k);
   //k=345;
   if(k==345)
   {
		t1 = t1+"x";
		//dbedtISBN->DataSource ->DataSet ->Edit();
		//dbedtISBN->DataSource ->DataSet ->FieldByName("ISBN")->Value = t1;
   }
   else
   {
		t1 = t1 + IntToStr(k);
		//dbedtISBN->DataSource ->DataSet ->Edit();
		//dbedtISBN->DataSource ->DataSet ->FieldByName("ISBN")->Value = t1;
		//dbedtISBN->Text = t1;//IntToStr(rs[i]);
   }
   return t1;
	}

}
//------
int StringToIsbn(String str,int rs[])
{
	String str1;
	str1=str;
	int t,s=0;
	int k,a=9,temp;
	Trim(str1);
	temp = str1.Length() - str1.Pos(" ")+1;
	str1=str1.Delete(str1.Pos(" "),temp);
	k = str1.Length();
	for(int i=0;i<k;i++)
	{
		String c;

		// 得到最后一个字符
		c = str1.LastChar();
		t = StrToInt(c);
		if(i>0&&i<10)
		{
		//按规则计算isbn代码和
			s = s + t*a--;
		//得到isbn前9位数字
			rs[9-i] = t;
			//ShowMessage(rs[9-i]);
		}
		str1.Delete(str1.Length(),1 );
	}
	//获取isbn最后一位数字
	a = s%11;
	if(a==10)
	return 345;
	else
	return a;
}

//------------
bool DbgridToExcel(TRzDBGrid* dbg)
{
	ShowMessage("excel导出时不要有操作，导出完成后会提示");
	if(!dbg->DataSource ->DataSet ->Active )
	{
		ShowMessage("没有数据");
		return false;
	}
	int k = dbg->DataSource ->DataSet ->RecordCount  ;
	if(k == 0)
	{
		ShowMessage("没有数据");
		return false;
	}
	Variant     v;
	v   =Variant::CreateObject("Excel.Application");
	v.OlePropertySet("Visible",true);
	v.OlePropertyGet("WorkBooks").OleFunction("Add");


	for(int q=0;q<dbg->FieldCount ;++q)
	v.OlePropertyGet("Cells",1,(q+1)).OlePropertySet("Value",dbg->Columns ->Items [q]->Title ->Caption .t_str() );

	int t2 = dbg->DataSource ->DataSet ->RecordCount ;

	dbg->DataSource ->DataSet ->First();
	for(int   i=1;i< t2+1 ;i++)
	{
		for(int j=1;j<dbg->Columns ->Count+1  ;j++)
		{
			v.OlePropertyGet("Cells",i+1,j).OlePropertySet("Value",dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString .c_str() );  // AsString .c_str()
		}
		dbg->DataSource ->DataSet ->Next() ;
	}
	v.OlePropertySet("Visible",false);
	ShowMessage("导出完毕，请设置保存路径");
	v.OlePropertySet("Visible",true);
	return false;
}
//----------------
//------------
bool DbgridToExcel(TDBGrid* dbg)
{
	int k = dbg->DataSource ->DataSet ->RecordCount  ;
	if(k == 0)
	{
		ShowMessage("没有数据");
		return false;
	}
	Variant     v;
	v   =Variant::CreateObject("Excel.Application");
	v.OlePropertySet("Visible",true);
	v.OlePropertyGet("WorkBooks").OleFunction("Add");

	for(int q=0;q<dbg->FieldCount ;++q)
	v.OlePropertyGet("Cells",1,(q+1)).OlePropertySet("Value",dbg->Columns ->Items [q]->Title ->Caption .t_str() );

	int t2 = dbg->DataSource ->DataSet ->RecordCount ;

	dbg->DataSource ->DataSet ->First();
	for(int   i=1;i< t2+1 ;i++)
	{
		for(int j=1;j<dbg->Columns ->Count+1  ;j++)
		{
			v.OlePropertyGet("Cells",i,j).OlePropertySet("Value",dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString .c_str() );  // AsString .c_str()
		}
		dbg->DataSource ->DataSet ->Next() ;
	}
	return false;
}
//----------------
//------------
bool DataSetToExcel(TADODataSet* dset)
{
	if(dset->Active == false)
	return 0;
	if(dset->RecordCount == 0)
	return 0;
	Variant     v;
	v   =Variant::CreateObject("Excel.Application");
	v.OlePropertySet("Visible",false);
	v.OlePropertyGet("WorkBooks").OleFunction("Add");
	try
	{
		int t2 = dset ->RecordCount ;// RecordCount ;
		dset->First();//  >DataSource ->DataSet ->First();
		for(int   i=1;i< t2+1 ;i++)
		{
			for(int j=1;j<dset ->FieldCount+1 ;j++)
			{
				v.OlePropertyGet("Cells",i,j).OlePropertySet("Value",dset->Fields ->Fields [j-1]->AsAnsiString .c_str());  //dsetCheck ->FieldByName(dsetCheck->GetFieldNames(dsetCheck->Fields [j-1].c )  Fields [j-1].GetFieldNames()   dbgrdCheck->Columns ->Items [j-1]->FieldName )->AsAnsiString .c_str() );  // AsString .c_str()
			}
			dset->Next();//  ->Next() ;
		}
	}
	catch(...)
	{
		ShowMessage("没有数据！");
	}
	v.OlePropertySet("Visible",true);
	return false;
}

  //------------
bool DataSetToExcel(TDataSet* dset)
{
	if(dset->Active == false)
	return 0;
	if(dset->RecordCount == 0)
	return 0;
	Variant     v;
	v   =Variant::CreateObject("Excel.Application");
	v.OlePropertySet("Visible",false);
	v.OlePropertyGet("WorkBooks").OleFunction("Add");
	try
	{
		int t2 = dset ->RecordCount ;// RecordCount ;
		dset->First();//  >DataSource ->DataSet ->First();
		for(int   i=1;i< t2+1 ;i++)
		{
			for(int j=1;j<dset ->FieldCount+1 ;j++)
			{
				v.OlePropertyGet("Cells",i,j).OlePropertySet("Value",dset->Fields ->Fields [j-1]->AsAnsiString .c_str());  //dsetCheck ->FieldByName(dsetCheck->GetFieldNames(dsetCheck->Fields [j-1].c )  Fields [j-1].GetFieldNames()   dbgrdCheck->Columns ->Items [j-1]->FieldName )->AsAnsiString .c_str() );  // AsString .c_str()
			}
			dset->Next();//  ->Next() ;
		}
	}
	catch(...)
	{
		ShowMessage("没有数据！");
	}
	v.OlePropertySet("Visible",true);
	return false;
}


