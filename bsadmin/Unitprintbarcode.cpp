//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unitprintbarcode.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma link "RzButton"
#pragma link "RpCon"
#pragma link "RpConDS"
#pragma link "RpDefine"
#pragma link "RpRave"
#pragma link "RpBase"
#pragma link "RpSystem"
#pragma link "frxClass"
#pragma link "frxDBSet"
#pragma link "frxBarcode"
#pragma resource "*.dfm"
Tfrmprintbarcode *frmprintbarcode;
//---------------------------------------------------------------------------
__fastcall Tfrmprintbarcode::Tfrmprintbarcode(TComponent* Owner,TADOConnection *con,int user)
	: TForm(Owner)
{
	AnsiString sql;
	query->Connection = con;
	fcon = con;
	userid = user;
	sql = "select * from bs_userbarcode where userid = " + IntToStr(userid) ;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	spdabao->Connection = con;
	querydabao->Connection = con;
        createbarcode->Connection=con;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmprintbarcode::RzButton2Click(TObject *Sender)
{
	Close();
}
AnsiString Tfrmprintbarcode::CheckSumModulo10(AnsiString data)
{
     int i,fak,sum,len;
     AnsiString resultstr;
     sum=0;
     len=data.Length();
     fak=len;
     for (int i=1; i <= len; i++) {

          if ((fak % 2)==0) {
                     sum=sum+(StrToInt(data.SubString(i,1))*1);
          }else  sum=sum+(StrToInt(data.SubString(i,1))*3);
        fak--;
     }

      if ((sum % 10)==0) {
              resultstr=    data+"0";
      }else

      resultstr = data+IntToStr(10-(sum % 10));
      return  resultstr;

      /*	for i:=1 to Length(data) do
	begin
		if (fak mod 2) = 0 then
			sum := sum + (StrToInt(data[i])*1)
		else
			sum := sum + (StrToInt(data[i])*3);
		dec(fak);
	end;
	if (sum mod 10) = 0 then
		result := data+'0'
	else
		result := data+IntToStr(10-(sum mod 10)); */



}
//---------------------------------------------------------------------------

void __fastcall Tfrmprintbarcode::RzButton1Click(TObject *Sender)
{
	//ModalResult = mrOk ;
	if (query->State == dsEdit  ) {
		query->Post();
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmprintbarcode::RzButton3Click(TObject *Sender)
{
	spdabao->Parameters->ParamByName("@userid")->Value = userid;
	spdabao->ExecProc();

	AnsiString sql;
	sql = "select * from bs_userbarcode where userid = " + IntToStr(userid) + " order by name";
	querydabao->Close();
    querydabao->SQL->Clear();
	querydabao->SQL->Add(sql);
	querydabao->Open();

	frxdbpbag->DataSet = querydabao;

	frxpbag->LoadFromFile(Sysutils::ExtractFilePath(Application->ExeName) + "UserBarcode.fr3");
	frxpbag->PrepareReport(true);

	if (((TRzButton*)(Sender))->Tag==1) {
		frxpbag->ShowPreparedReport();
	}else
	{
		frxpbag->Print();
	}

	return;
}
//---------------------------------------------------------------------------



void __fastcall Tfrmprintbarcode::RzButton5Click(TObject *Sender)

{
//自动生成条码最大值
    int maxvalue;
    int med;
    String sql;
    String bb;
    String barcode;
    int e;






    TADOQuery *aqq;
    aqq = new TADOQuery(NULL);
    aqq->Connection =fcon;;


     med=1000000;
     createbarcode->Close();
     createbarcode->SQL->Clear();
     createbarcode->SQL->Add("select max(Barcode) as maxvalue from SYS_Barcode ");
     createbarcode->Open();
     maxvalue=createbarcode->FieldByName("maxvalue")->AsInteger;

     DBGrid1->DataSource->DataSet->DisableControls();
     query->First();
     while (!query->Eof)
     {

     //  if (query->FieldByName("userbarcode")->AsAnsiString=="") {
            maxvalue=maxvalue+1;
            e= maxvalue+ med;
            bb= IntToStr(e);
           // ShowMessage(bb);
            barcode="100000" + bb.SubString(2,6);
           // barcode="100000000089";
            sql="Update BS_BookCatalog set barcode='"+CheckSumModulo10(barcode)+"' where id="+query->FieldByName("catalogid")->AsAnsiString;;

          //  aqq->SQL->Clear();
            aqq->SQL->Add(sql+";");
           // aqq->ExecSQL();
     //  }

       query->Next();
     }
    // aqq->SQL->Clear();
     aqq->SQL->Add("update bs_userbarcode set userbarcode=BS_BookCatalog.barcode from bs_userbarcode ,BS_BookCatalog where bs_userbarcode.catalogid=BS_BookCatalog.id ");
     aqq->ExecSQL();
     DBGrid1->DataSource->DataSet->EnableControls();




    	sql = "select * from bs_userbarcode where userid = " + IntToStr(userid) ;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();

         maxvalue++;
        sql = "update SYS_Barcode set Barcode="+IntToStr(maxvalue);
        aqq->Connection =createbarcode->Connection;;
     aqq->Close();
     aqq->SQL->Clear();
       aqq->SQL->Add(sql);
       aqq->ExecSQL();
        delete aqq;

}
//---------------------------------------------------------------------------

