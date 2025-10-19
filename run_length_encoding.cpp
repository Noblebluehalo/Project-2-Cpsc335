// CPSC 335 - Project 2
// Algorithm 2: String Run Encoding (lowercase letters and spaces; runs > 1 encoded as kx)
// Author: Joshua Zamora

#include <bits/stdc++.h>
using namespace std;

string runEncode(const string& s) {
    if (s.empty()) return "";
    string out;
    out.reserve(s.size()); // heuristic

    int n = (int)s.size();
    int cnt = 1;

    for (int i = 1; i < n; ++i) {
        if (s[i] == s[i-1]) {
            ++cnt;
        } else {
            if (cnt == 1) out.push_back(s[i-1]);
            else          out += to_string(cnt) + s.substr(i-1, 1);
            cnt = 1;
        }
    }
    // flush last run
    if (cnt == 1) out.push_back(s.back());
    else          out += to_string(cnt) + s.substr(n-1, 1);

    return out;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line, all;
    // Read whole stdin as one string (keeps spaces)
    while (getline(cin, line)) {
        if (!all.empty()) all.push_back('\n');
        all += line;
    }
    cout << runEncode(all) << "\n";
    return 0;
}
