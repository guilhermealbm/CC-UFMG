#include <iostream>
 
using namespace std;
 
int main() {
 
    /**
     * Escreva a sua solução aqui
     * Code your solution here
     * Escriba su solución aquí
     */
     
     int tttt; cin >> tttt;
     while (tttt != 0) {
         char sorb; cin>>sorb;
         if (sorb == 'S') {
             string input; cin >> input;
             string result1 = "", result2 = "", result3 = "";
             for (int i = 0; i < input.length(); i++) {
                 char currChar = input[i];
                 if (currChar == '1' || currChar == '2' || currChar == '5' || currChar == '8') {
                     result1.append("*.");
                 } else if (currChar == '3' || currChar == '4' || currChar == '6' || currChar == '7') {
                     result1.append("**");
                 } else {
                     result1.append(".*");
                 }
                 
                 if (currChar == '1' || currChar == '3') {
                     result2.append("..");
                 } else if (currChar == '2'|| currChar == '6' || currChar == '9') {
                     result2.append("*.");
                 } else if (currChar == '7' || currChar == '8' || currChar == '0') {
                     result2.append("**");
                 } else {
                     result2.append(".*");
                 }
                 
                 result3.append("..");
                 
                 if (i != input.length() - 1) {
                     result1.append(" ");
                     result2.append(" ");
                     result3.append(" ");
                 }
             } 
             cout << result1 << endl;
             cout << result2 << endl;
             cout << result3 << endl;
         } else {
             string input1 = "";
             string input2 = "";
             string input3 = "";
             string result = "";

             for (int i = 0; i < tttt; i++) {
                 string temp; cin >> temp;
                 input1.append(temp);
             }

             for (int i = 0; i < tttt; i++) {
                 string temp; cin >> temp;
                 input2.append(temp);
             }

             for (int i = 0; i < tttt; i++) {
                 string temp; cin >> temp;
                 input3.append(temp);
             }
             
             for (int i = 0; i < input1.length(); i = i + 2) {
                 if (input1[i] == '*' && input1[i + 1] == '.' && input2[i] == '.' && input2[i + 1] == '.')
                    result.append("1");
                 else if (input1[i] == '*' && input1[i + 1] == '.' && input2[i] == '*' && input2[i + 1] == '.')
                    result.append("2");
                 else if (input1[i] == '*' && input1[i + 1] == '*' && input2[i] == '.' && input2[i + 1] == '.')
                    result.append("3");
                 else if (input1[i] == '*' && input1[i + 1] == '*' && input2[i] == '.' && input2[i + 1] == '*')
                    result.append("4");
                 else if (input1[i] == '*' && input1[i + 1] == '.' && input2[i] == '.' && input2[i + 1] == '*')
                    result.append("5");
                 else if (input1[i] == '*' && input1[i + 1] == '*' && input2[i] == '*' && input2[i + 1] == '.')
                    result.append("6");
                 else if (input1[i] == '*' && input1[i + 1] == '*' && input2[i] == '*' && input2[i + 1] == '*')
                    result.append("7");
                 else if (input1[i] == '*' && input1[i + 1] == '.' && input2[i] == '*' && input2[i + 1] == '*')
                    result.append("8");
                 else if (input1[i] == '.' && input1[i + 1] == '*' && input2[i] == '*' && input2[i + 1] == '.')
                    result.append("9");
                 else
                    result.append("0");
             }
             
             cout << result << endl;
             
         }
         
         cin >> tttt;
     }
 
    return 0;
}