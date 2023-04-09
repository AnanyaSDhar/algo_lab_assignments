#include <iostream>
#include <queue>
#include <unordered_map>
#include <string>
#include <fstream>
using namespace std;

string encode(string text, unordered_map<char, string> codes){
    string encoded = "";
    for (char c : text) {
        encoded += codes[c];
        encoded += " ";
    }
    return encoded;
}

int main(){
    FILE* file;
    file = fopen("file3.txt", "r");
    char ch;
    string text;
    while ((ch=getc(file))!=EOF) {
      text=text+ch;
   }

    FILE * file2;
    file2 = fopen("code_table1.txt", "r");
    if (!file2) {
        cerr << "Failed to open input file." << endl;
        return 1;
    }

    unordered_map<char, string> codes;
    char ch1;
    while ((ch1 = getc(file2)) != EOF) {
        if (ch1 == '\n') {
            continue; // ignore blank lines
        }

        char key = ch1;
        cout << key << "\t";
        string code = "";
        while (true) {
            ch1 = getc(file2);
            if (ch1 == '=') {
                cout << "{=}";
            } else if (ch1 != '\n' && ch1 != EOF) {
                code += ch1;
                cout << "{" << ch1 << "}";
            } else {
                break;
            }
        }
        cout << code << endl;
        codes[key] = code;
    }
    cout << "Element  Frequency" << endl;
    for (auto i : codes){
        cout << i.first << " \t\t\t " << i.second << endl;
    }

    string result=encode(text,codes);
    cout<<endl<<"Result of encoding second document using the code table form first document:"<<endl<<endl;
    for( char i: result){
        cout<<i;
    }
    cout<<endl;

    ofstream output2("Encoded3_using1.txt");
    output2<<result;
    output2.close();
}