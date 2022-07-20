#include <iostream>
#include <map>
 
using namespace std;
 
int main() {
 
    /**
     * Escreva a sua solução aqui
     * Code your solution here
     * Escriba su solución aquí
     */
 	int tttt;
 	cin>>tttt;
 	cin.ignore();
	while (tttt != 0) {
	    string text;
        getline(cin, text);
        int textSize = text.length();
        int fpointer = 0;
        int spointer = -1;
        map<char, int> letters;
        int maxSize = -1;
        while (spointer != textSize - 1) {
            pair<char, int> newPair(text[spointer + 1], 1);
            auto itr = letters.find(text[spointer + 1]);
            if (itr != letters.end()) {
                spointer++;
                itr->second++;
            } else if (letters.size() < tttt) {
                spointer++;
                letters.insert(newPair);
            } else {
                auto firstPair = letters.find(text[fpointer]);
                if (firstPair->second != 1) {
                    firstPair->second--;
                } else {
                    letters.erase(firstPair);
                    spointer++;
                    letters.insert(pair<char, int>(text[spointer], 1));
                }
                fpointer++;
            }
            
            if ((spointer - fpointer + 1) > maxSize) {
                maxSize = (spointer - fpointer + 1);
            }
        }
        
        cout << maxSize << endl;
        
	    cin>>tttt;
	    cin.ignore();
	}
 
    return 0;
}