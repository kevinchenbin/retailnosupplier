//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TeacherFDDetail.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma link "frxClass"
#pragma link "frxDBSet"
#pragma resource "*.dfm"
Tfrmfddetail *frmfddetail;
//---------------------------------------------------------------------------
__fastcall Tfrmfddetail::Tfrmfddetail(TComponent* Owner)
	: TForm(Owner)
{
}
void Tfrmfddetail::loaddata()
{
  AnsiString sql;

  sql = "exec TeacherFDSearchDetail "+IntToStr(tearchid);
 if (begintime=="") {
   sql=sql+" ,'1998-01-01','2090-01-01'";
 }else
 { sql=sql+",'"+begintime +"','"+endtime+"'";

  }
  aq->Connection = fcon;
  aq->Close();
  aq->SQL->Clear();
  aq->SQL->Add(sql);
  aq->Open();





}
AnsiString Tfrmfddetail::Doubletostring(double num)
{
 	AnsiString outnum,ychar,outstring,outzs,outxs;
	outnum = FormatFloat("0.00",num);
	outzs = outnum.SubString(0,outnum.Pos(".")-1);
	outxs = outnum.SubString(outnum.Pos(".") + 1,2);
	//outnum = outnum.SubString(0,outnum.Pos(".")-1) + outnum.SubString(outnum.Pos(".")+1,2);

	AnsiString danwei[8] = {"Çª","°Û","Ê°","Íò","Çª","°Û","Ê°","Ôª"};
	int len = outzs.Length() ;
	for (int i = 0; i < 8; i++) {
		if (len < 8-i) {

		}
		else
		{
			if (outzs.SubString(len-7 + i,1) == "-") {
				outstring = "¸º";
			}
			else
			{
				outstring = outstring + Touppnum(outzs.SubString(len-7 + i,1)) + danwei[i];
			}
		}
	}
	AnsiString danwei1[2] = {"½Ç","·Ö"};
	len = outxs.Length() ;
	for (int i = 0; i < len; i++) {
		outstring = outstring + Touppnum(outxs.SubString(i+1,1)) + danwei1[i];
	}
	return  outstring;





}
AnsiString Tfrmfddetail::Touppnum(AnsiString ychar)
{
	AnsiString mchar;
	if (ychar == "") {
    	return " ";
	}
	int i;
	try {
		i = StrToInt(ychar);
	} catch (...) {
		return " ";
	}
	switch (i) {
		case 0:
			mchar = "Áã";
		break;
		case 1:
			mchar = "Ò¼";
		break;
		case 2:
			mchar = "·¡";
		break;
		case 3:
			mchar = "Èþ";
		break;
		case 4:
			mchar = "ËÁ";
		break;
		case 5:
			mchar = "Îé";
		break;
		case 6:
			mchar = "Â½";
		break;
		case 7:
			mchar = "Æâ";
		break;
		case 8:
			mchar = "°Æ";
		break;
		case 9:
			mchar = "¾Á";
		break;
    default:
		;
	}
	return mchar;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmfddetail::FormShow(TObject *Sender)
{
loaddata();
}
//---------------------------------------------------------------------------
void Tfrmfddetail::printorpriver(int atype)
{
  AnsiString ps;
	aq->DisableControls();
	ps = ExtractFilePath(Application->ExeName) +"fddetail.fr3";
   //	sumvalue=DBGridEh1->SumList->SumCollection->Items[7]->SumValue;
   su=DBGridEh1->GetFooterValue(aq->RecordCount,DBGridEh1->Columns->Items[7]);
	 sumvalue=StrToFloat(su);

	frxfddetail->LoadFromFile(ps);
		frxfddetail->PrepareReport(true);

 	if (atype == 0) {          //
			frxfddetail->PrintOptions->ShowDialog = false;
			   frxfddetail->Print();

		}
		else
		{ 	frxfddetail->ShowPreparedReport();
		}

  aq->EnableControls();

}
//---------------------------------------------------------------------------

void __fastcall Tfrmfddetail::frxfddetailGetValue(const UnicodeString VarName, Variant &Value)
{
	if (CompareText(VarName,"\"name\"")==0  ) {  //ÐòºÅ
		 Value = tearchname;
	}
		if (CompareText(VarName,"\"date\"")==0  ) {  //ÐòºÅ
			if (begintime=="") {
			Value ="";
			}else
			{
			  Value =begintime +" µ½ "+endtime;
			}
	}
		if (CompareText(VarName,"\"total\"")==0  ) {  //ÐòºÅ
		 Value = su;;
	}
		if (CompareText(VarName,"\"daxie\"")==0  ) {  //ÐòºÅ
		 Value = Doubletostring(sumvalue);;
	}
		if (CompareText(VarName,"\"totala\"")==0  ) {  //ÐòºÅ
		 Value = su;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmfddetail::Button1Click(TObject *Sender)
{
   printorpriver(0);
}
//---------------------------------------------------------------------------

void __fastcall Tfrmfddetail::Button2Click(TObject *Sender)
{
   printorpriver(1);
}
//---------------------------------------------------------------------------

