#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <queue>
#include <deque>
#include <bitset>
#include <iterator>
#include <list>
#include <stack>
#include <map>
#include <set>
#include <functional>
#include <numeric>
#include <utility>
#include <limits>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
 
using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define f first
#define s second
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define INF 0x3f3f3f3f
#define LINF 0x3f3f3f3f3f3f3f3fLL

typedef long long ll;
typedef pair<int, int> ii;

int convertNote(string note) {
    static int notes[7] = {9, 11, 0, 2, 4, 5, 7};
    int cNote = notes[note[0] - 'A'];
    if(note.length() >= 2) {
        if(note[1] == '#')
            cNote++;
        else
            cNote--;
    }

    return cNote % 12;
}

int getNotesDiff(int note, int prev) {
    int diff = note - prev;
    if (diff < -6) return 12 + diff;
    if (diff > 6) return diff - 12;
    if (abs(diff) == 6) return 6;
    return diff;
}

void lps(vector<int>& text, vector<int>& Lps){
    Lps[0] = 0;                   
    int len = 0;
    int i = 1;
    while (i < text.size()) {
        if(text[i] == text[len]) {   
            len++;
            Lps[i] = len;
            i++;
            continue;
        } else {                   
            if (len==0) { 
                Lps[i] = 0;
                i++;
                continue;
            } else {              
                len = Lps[len-1];
                continue;
            }
        }
    }
}

bool KMP(vector<int>& pattern, vector<int>& text){
    int n = text.size();
    int m = pattern.size();
    vector<int>Lps(m);
    
    lps(pattern, Lps);
    
    int i=0, j=0;
    while(i < n){
        if(pattern[j] == text[i]) {i++;j++;}

        if (j == m) { 
            return true;
        } else if (i < n && pattern[j] != text[i]) { 
            if (j == 0)         
                i++;
            else
                j = Lps[j - 1]; 
        }
    }
    return false;
}


int main(){ _
 
    /**
     * Escreva a sua solução aqui
     * Code your solution here
     * Escriba su solución aquí
     */

    while (true) {
        int m, t; cin >> m; cin >> t;
        if (m == 0 && t == 0)
            return 0;

        vector<int> music;
        string note; cin >> note;
        int oldNote = convertNote(note);
        for (int i = 1; i < m; i++) {
            cin >> note;
            int newNote = convertNote(note);
            music.push_back(getNotesDiff(newNote, oldNote));
            oldNote = newNote;
        }

        vector<int> original;
        cin >> note;
        oldNote = convertNote(note);
        
        for (int i = 1; i < t; i++) {
            cin >> note;
            int newNote = convertNote(note);
            original.push_back(getNotesDiff(newNote, oldNote));
            oldNote = newNote;
            
        }

        

        m--;t--;

        // for (int i = 0; i < m; i++) {
        //     cout << music[i] << " ";
        // }

        // cout << endl;

        // for (int i = 0; i < t; i++) {
        //     cout << original[i] << " ";
        // }

        // cout << endl;

        // cout << music.size() << "  " << original.size() << endl;
        
        bool isCopy = KMP(original, music);
        // for (int i = 0; i < (m - t + 1); i++) {
        //     // vector<int> newVec(music.begin() + i, music.begin() + i + t);

        //     bool isCopy_ = true;
        //     for (int j = i; j < i + t; j++) {
        //         if (music[j] != original[j - i]) {
        //             isCopy_ = false;
        //             break;
        //         }
        //     }

        //     if (isCopy_) {
        //         isCopy = true;
        //         break;
        //     }
        // }

        if (isCopy)
            cout << "S" << endl;
        else
            cout << "N" << endl;
        
    }
 
    return 0;
}
