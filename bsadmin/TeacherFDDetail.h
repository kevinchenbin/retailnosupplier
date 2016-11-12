//---------------------------------------------------------------------------

#ifndef TeacherFDDetailH
#define TeacherFDDetailH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "DBGridEh.hpp"
#include "GridsEh.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include "frxClass.hpp"
#include "frxDBSet.hpp"
//---------------------------------------------------------------------------
class Tfrmfddetail : public TForm
{
__published:	// IDE-managed Components
	TDBGridEh *DBGridEh1;
	TADOQuery *aq;
	TDataSource *DataSource1;
	TfrxReport *frxfddetail;
	TfrxDBDataset *frxDBDataset1;
	TButton *Button1;
	TButton *Button2;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall frxfddetailGetValue(const UnicodeString VarName, Variant &Value);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall Tfrmfddetail(TComponent* Owner);
	TADOConnection *fcon;
	int tearchid;
	AnsiString begintime;
	AnsiString endtime;
	AnsiString tearchname;
	 float sumvalue;
	 AnsiString su;
	void loaddata();
	void printorpriver(int atype);
	AnsiString Touppnum(AnsiString ychar);
	AnsiString Doubletostring(double num);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmfddetail *frmfddetail;
//---------------------------------------------------------------------------
#endif
