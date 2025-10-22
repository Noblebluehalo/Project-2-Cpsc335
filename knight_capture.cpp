// CPSC 335 - Project 2
// Algorithm 1: Minimum turns for two cooperating knights to achieve a capture
// Author: Joshua Zamora
// Email: JoshuaMZamora@csu.fullerton.edu

#include <iostream>
#include <queue>
#include <deque>
#include <unordered_set>
#include <cmath>
using namespace std;

// Shows the positions of both knights and which one moves next
struct State {
    int ax, ay, bx, by; // Positions of knight A and knight B
    int mover;          // 0 = A moves, 1 = B moves
    bool operator==(const State& o) const {
        return ax == o.ax && ay == o.ay &&
            bx == o.bx && by == o.by &&
            mover == o.mover;
    }
};

// Custom hash function for unordered_set to store State objects
struct StateHash {
    size_t operator()(const State& s) const {
        unsigned long long v = 1469598103934665603ULL;
        auto h = [&](int x) {
            v ^= static_cast<unsigned long long>(x) * 1315423911ULL;
            v *= 1099511628211ULL;
            };
        h(s.ax); h(s.ay); h(s.bx); h(s.by); h(s.mover);
        return static_cast<size_t>(v);
    }
};

// All 8 possible knight moves
static const int DX[8] = { -2,-1, 1, 2, 2, 1,-1,-2 };
static const int DY[8] = { 1, 2, 2, 1,-1,-2,-2,-1 };

// Checks if a position is within the search boundaries
inline bool inBox(int x, int y, int minX, int minY, int maxX, int maxY) {
    return x >= minX && x <= maxX && y >= minY && y <= maxY;
}

// Stores the result: number of turns and which knight captured
struct Result {
    long long turns;
    char captor; // 'A' or 'B'
};

// Finds the minimum number of turns for a capture
Result min_turns_knight_capture(pair<int, int> A, pair<int, int> B) {
    Result result = { -1, '?' }; // Default result (no capture)

    // If both knights start on the same square
    if (A == B) {
        result.turns = 0;
        result.captor = 'A';
        return result;
    }

    // Calculate the bounding box around the two knights
    int ax = A.first, ay = A.second;
    int bx = B.first, by = B.second;
    int dx = abs(ax - bx);
    int dy = abs(ay - by);
    int span = (dx > dy) ? dx : dy;
    int pad = 20; 

    int minX = (ax < bx ? ax : bx) - (span + pad);
    int maxX = (ax > bx ? ax : bx) + (span + pad);
    int minY = (ay < by ? ay : by) - (span + pad);
    int maxY = (ay > by ? ay : by) + (span + pad);

    // BFS data structures
    unordered_set<State, StateHash> vis;       // Keeps track of visited states
    deque< pair<State, int> > q;               // Queue

    // Starting state: both knights at initial positions, A moves first
    State start = { ax, ay, bx, by, 0 };
    vis.insert(start);
    q.push_back(make_pair(start, 0));

    // Breadth-First Search
    while (!q.empty()) {
        State s = q.front().first; 
        int plies = q.front().second; 
        q.pop_front();

        if (s.mover == 0) { // Knight A moves
            for (int k = 0; k < 8; ++k) {
                int nxA = s.ax + DX[k];
                int nyA = s.ay + DY[k];
                if (!inBox(nxA, nyA, minX, minY, maxX, maxY)) continue;

                // A captures B
                if (nxA == s.bx && nyA == s.by) {
                    result.turns = (plies + 2) / 2; // Convert plies to turns
                    result.captor = 'A';
                    return result;
                }

                // Create next state (B moves next)
                State t = { nxA, nyA, s.bx, s.by, 1 };
                if (vis.find(t) == vis.end()) {
                    vis.insert(t);
                    q.push_back(make_pair(t, plies + 1));
                }
            }
        }
        else { // Knight B moves
            for (int k = 0; k < 8; ++k) {
                int nxB = s.bx + DX[k];
                int nyB = s.by + DY[k];
                if (!inBox(nxB, nyB, minX, minY, maxX, maxY)) continue;

                // B captures A
                if (nxB == s.ax && nyB == s.ay) {
                    result.turns = (plies + 2) / 2;
                    result.captor = 'B';
                    return result;
                }

                // Create next state (A moves next)
                State t = { s.ax, s.ay, nxB, nyB, 0 };
                if (vis.find(t) == vis.end()) {
                    vis.insert(t);
                    q.push_back(make_pair(t, plies + 1));
                }
            }
        }
    }

    return result; // Return result if no capture found
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "Enter positions of the two knights (A and B):\n";
    cout << "Format: ax ay bx by\n> ";

    pair<int, int> A, B;
    cin >> A.first >> A.second >> B.first >> B.second;

    // Run the BFS algorithm
    Result res = min_turns_knight_capture(A, B);

    // Display the result
    if (res.turns == -1)
        cout << "\nNo capture found within search bounds.\n";
    else
        cout << "\nKnight " << res.captor << " captured the opponent in "
        << res.turns << " turn"
        << (res.turns == 1 ? "" : "s") << "!\n";

    system("pause");
    return 0;
}
