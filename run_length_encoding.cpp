// CPSC 335 - Project 2
// Algorithm 2: String Run Encoding (lowercase letters and spaces; runs > 1 encoded as kx)
// Author: Joshua Zamora
// Email: JoshuaMZamora@csu.fullerton.edu

#include <iostream>
#include <string>
using namespace std;

string runEncode(const string& s) {
    if (s.empty()) return "";
    string out;
    out.reserve(s.size());

    int n = (int)s.size();
    int cnt = 1;

    for (int i = 1; i < n; ++i) {
        if (s[i] == s[i - 1]) {
            ++cnt;
        }
        else {
            if (cnt == 1) out.push_back(s[i - 1]);
            else out += to_string(cnt) + s.substr(i - 1, 1);
            cnt = 1;
        }
    }
    if (cnt == 1) out.push_back(s.back());
    else out += to_string(cnt) + s.substr(n - 1, 1);
    return out;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "Enter text to encode (type 'exit' to quit):\n";
    string line;
    while (true) {
        cout << "> ";
        getline(cin, line);
        if (!cin || line == "exit" || line == "quit") break;

        string encoded = runEncode(line);
        cout << "Encoded: " << encoded << "\n";
    }

    cout << "Goodbye!\n";
    return 0;
}
