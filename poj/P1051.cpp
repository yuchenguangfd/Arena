/*
 * Problem: P,MTHBGWB
 * http://poj.org/problem?id=1051
 */

#include <string>
#include <iostream>
#include <cctype>

int main() {
    using namespace std;
    const string Morse[30] = {
            ".-", "-...", "-.-.", "-..", ".", "..-.", "--.",
            "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.",
            "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--",
            "--..", "..--", ".-.-", "---.", "----" };
    int numCase;
    cin >> numCase;
    for (int caseID = 1; caseID <= numCase; ++caseID) {
        string str1;
        cin >> str1;
        int count[200];
        string code = "";
        for (int i = 0; i < str1.length(); i++) {
            int num;
            if (isalpha(str1[i]))
                num = str1[i] - 'A';
            else if (str1[i] == '_')
                num = 26;
            else if (str1[i] == ',')
                num = 27;
            else if (str1[i] == '.')
                num = 28;
            else if (str1[i] == '?')
                num = 29;
            code += Morse[num];
            count[i] = Morse[num].length();
        }

        cout << caseID << ": ";
        int s(-1), t;
        for (int p = str1.length() - 1; p >= 0; p--) {
            string tmp;
            t = s + count[p];
            for (int i = s + 1; i <= t; i++)
                tmp += code[i];
            s = t;
            int num;
            for (num = 0; num < 30; num++)
                if (Morse[num] == tmp)
                    break;
            char ch;
            if (num < 26)
                ch = num + 'A';
            else if (num == 26)
                ch = '_';
            else if (num == 27)
                ch = ',';
            else if (num == 28)
                ch = '.';
            else if (num == 29)
                ch = '?';
            cout << ch;
        }
        cout << endl;
    }
    return 0;
}
