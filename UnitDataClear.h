//---------------------------------------------------------------------------

#ifndef UnitDataClearH
#define UnitDataClearH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ADODB.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
	TComboBox *cbstg;
	TLabel *Label1;
	TComboBox *cbpx;
	TLabel *Label2;
	TDateTimePicker *DateTimePicker1;
	TDateTimePicker *DateTimePicker2;
	TLabel *Label3;
	TLabel *Label4;
	TSpeedButton *sb;
	TDataSource *DataSource1;
	TDBGrid *DBGrid1;
	TDBGrid *DBGrid2;
	TDataSource *DataSource2;
	TADOQuery *ADOQuery1;
	TADOQuery *ADOQuery2;
	void __fastcall cbpxChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
