// CPSC 335 - Project 2
// Algorithm 2: String Run Encoding 
// Author: Joshua Zamora
// Email: JoshuaMZamora@csu.fullerton.edu

#include <iostream>
#include <string>
using namespace std;

// Function that performs run-length encoding on the input string
string runEncode(const string& s) {
    // Return empty string if input is empty
    if (s.empty()) return "";

    string out;               // Stores the encoded result
    out.reserve(s.size());    // Reserve memory to improve performance

    int n = (int)s.size();    // Length of the input string
    int cnt = 1;              // Counter for repeating characters

    // Loop through the string starting from the 2nd character
    for (int i = 1; i < n; ++i) {
        if (s[i] == s[i - 1]) {
            
            ++cnt;
        }
        else {
        
            if (cnt == 1)
                out.push_back(s[i - 1]);                  // Single character
            else
                out += to_string(cnt) + s.substr(i - 1, 1); // Encode run as number + char
            cnt = 1;  // Reset counter for next run
        }
    }

    // Handle the final run
    if (cnt == 1)
        out.push_back(s.back());                          
    else
        out += to_string(cnt) + s.substr(n - 1, 1);       

    return out; // Return the encoded string
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "Enter text to encode (type 'exit' to quit):\n";
    string line;

    // Repeatedly get user input until they type exit
    while (true) {
        cout << "> ";
        getline(cin, line); 
        if (!cin || line == "exit" || line == "quit") break; // Exit condition

        // Encode the input line and print the result
        string encoded = runEncode(line);
        cout << "Encoded: " << encoded << "\n";
    }

    cout << "Goodbye!\n";
    return 0;
}
