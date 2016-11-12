//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "NotCheckBook.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "RzDBGrid"
#pragma resource "*.dfm"
TfrmNotCheckBook *frmNotCheckBook;
//---------------------------------------------------------------------------
__fastcall TfrmNotCheckBook::TfrmNotCheckBook(TComponent* Owner,TADOQuery *aquery)
	: TForm(Owner)
{
	ds->DataSet = aquery;
	aquery->Active = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmNotCheckBook::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmNotCheckBook::BtnImportClick(TObject *Sender)
{
	ModalResult = mrOk ;
}
//---------------------------------------------------------------------------
bool __fastcall TfrmNotCheckBook::DbgridToExcel(TRzDBGrid* dbg)
{
	AnsiString temptext ;
	int k = dbg->DataSource ->DataSet ->RecordCount ,n=0;
	if(k == 0)
	{
		ShowMsg(Handle ,"没有数据！",3);
		return false;
	}
	Variant     v;
	v   =Variant::CreateObject("Excel.Application");
	v.OlePropertySet("Visible",true);
	v.OlePropertyGet("WorkBooks").OleFunction("Add");
//  在Excel中成字符串显示
	v.OlePropertyGet("Cells",1,4).OlePropertySet("Value","未盘书" );

	n=1;

	int t1= 0;
	for(int q=0;q<dbg->FieldCount ;++q)
	{
		if (dbg->Columns->Items[q]->Visible == true) {
			t1++;
			temptext = "'"+ dbg->Columns ->Items [q]->Title ->Caption;
			v.OlePropertyGet("Cells",1+n,(t1)).OlePropertySet("Value",temptext .c_str() );
		}
	}



	int t2 = dbg->DataSource ->DataSet ->RecordCount ;

	dbg->DataSource ->DataSet ->First();
	for(int   i=2+n;i<=t2+1+n ;i++)
	{
		t1=0;
		for(int j=1;j<dbg->Columns ->Count+1  ;j++)
		{
			if (dbg->Columns->Items[j-1]->Visible == true) {
				t1++;
				temptext = "'"+ dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
				v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
			}
		}
		dbg->DataSource ->DataSet ->Next() ;
	}
	return false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmNotCheckBook::BtnPreviewNextPageClick(TObject *Sender)
{
	if (!ds->DataSet->IsEmpty() ) {
		DbgridToExcel(RzDBGrid1);
	}
}
//---------------------------------------------------------------------------




