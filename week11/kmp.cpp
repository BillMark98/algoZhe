#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef int Position;

#define NOTFOUND -1
Position KMP(string & origin, string & pattern);

void BuildMatch(string & pattern, vector<int> & match);

int main()
{
    string origin;
    int N;
    cin >> origin >> N;
    string temp;
    Position pos;
    while (N--) {
        cin >> temp;
        pos = KMP(origin, temp);
        if (pos != NOTFOUND) {
            cout << origin.substr(pos) << endl;
        }
        else {
            cout << "Not Found\n";
        }
    }
}

Position KMP(string & origin, string & pattern)
{
    vector<int> match;
    match.resize(pattern.length());
    BuildMatch(pattern, match);

    Position s = 0,p = 0;
    int lenOrigin = origin.length();
    int lenPattern = pattern.length();
    if (lenOrigin < lenPattern) 
        return NOTFOUND;

    while (s < lenOrigin && p < lenPattern) {
        if (origin[s] == pattern[p]) {
            s++;
            p++;
        }
        else if (p >= 1){
            p = match[p - 1] + 1;
        }
        else {
            s++;
        }
    }
    // if (p == lenPattern - 1) {
    //     return s - lenPattern;
    // }
    // else {
    //     return NOTFOUND;
    // }
    return p == lenPattern ? (s - lenPattern) : NOTFOUND;
}

void BuildMatch(string & pattern, vector<int> & match)
{
    match[0] = -1;
    int len = pattern.length();
    for (int i = 1; i < len; i++) {
        int pos = match[i - 1] + 1;
        while (pos >= 1 && pattern[i] != pattern[pos]) {
            pos = match[pos - 1] + 1;
        }
        if (pattern[i] == pattern[pos]) {
            match[i] = pos;
        }
        else {
            match[i] = -1;
        }
    }
}