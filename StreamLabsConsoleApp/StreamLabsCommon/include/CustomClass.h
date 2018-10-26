#ifdef CUSTOMCLASS_EXPORTS  
#define CUSTOMCLASS_API __declspec(dllexport)   
#else  
#define CUSTOMCLASS_API __declspec(dllimport)   
#endif 

#include <string>
using namespace std;

class  __declspec(dllexport) CustomClass
{
private:
	int a;
	int id;
	string str;
	static int counter;
public:
	CustomClass();
	~CustomClass();
	void IncrementInteger();
	void DecrementInteger();
	int GetInteger();
	void SetInteger(int newValue);

	void ReverseString();
	string GetString();
	void SetString(string newString);

};

