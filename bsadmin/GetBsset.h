
#include <Classes.hpp>
class SYSSet
{
	 private:
		TStringList *BSSET;
	 public:
	 String  Name;
	 bool ValueBool ;
	 String ValueStr;
	 void Add(String name , TObject * Node);
	 void GetSetInfo(String name);
	 SYSSet()
	 {
		BSSET = new TStringList();

	 }
	 ~SYSSet()
	 {
		delete   BSSET;

	 }

};
void SYSSet::Add(String name , TObject * Node)
{

	BSSET->AddObject(name,Node);
}
void SYSSet::GetSetInfo(String name)
{
     int index;
   index = BSSET->IndexOf(name);
   if (index == -1) {
	   ValueBool=false;
	   ValueStr = "";
   }else
   {
		 // ValueBool =true;
	   ValueBool = ((SYSSet*)(BSSET->Objects[index]))->ValueBool ;
	   ValueStr =  ((SYSSet*)(BSSET->Objects[index]))->ValueStr;
   }

}


