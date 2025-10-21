// CPSC 335 - Project 2
// Algorithm 1: Minimum turns for two cooperating knights to achieve a capture
// Author: Joshua Zamora
// Email: JoshuaMZamora@csu.fullerton.edu

#include <bits/stdc++.h>
using namespace std;

static const int DX[8] = {-2,-1, 1, 2, 2, 1,-1,-2};
static const int DY[8] = { 1, 2, 2, 1,-1,-2,-2,-1};

struct State {
    int ax, ay, bx, by;
    uint8_t mover; // 0 = A moves, 1 = B moves
    bool operator==(const State& o) const {
        return ax==o.ax && ay==o.ay && bx==o.bx && by==o.by && mover==o.mover;
    }
};

struct StateHash {
    size_t operator()(const State& s) const noexcept {
        // Simple mix
        uint64_t v = 1469598103934665603ULL;
        auto h = [&](int x){ v ^= (uint64_t)(x*1315423911); v *= 1099511628211ULL; };
        h(s.ax); h(s.ay); h(s.bx); h(s.by); h((int)s.mover);
        return (size_t)v;
    }
};

static inline bool inBox(int x, int y, int minX, int minY, int maxX, int maxY) {
    return x>=minX && x<=maxX && y>=minY && y<=maxY;
}

// returns minimal number of *turns* (rounds), as defined by the spec example
long long min_turns_knight_capture(pair<int,int> A, pair<int,int> B) {
    if (A == B) return 0;

    int ax = A.first, ay = A.second;
    int bx = B.first, by = B.second;
    int dx = abs(ax - bx), dy = abs(ay - by);
    int span = max(dx, dy);
    int pad = 20;

    int minX = min(ax, bx) - (span + pad);
    int maxX = max(ax, bx) + (span + pad);
    int minY = min(ay, by) - (span + pad);
    int maxY = max(ay, by) + (span + pad);

    unordered_set<State, StateHash> vis;
    deque<pair<State,int>> q; // (state, plies)

    State start{ax, ay, bx, by, 0};
    vis.insert(start);
    q.push_back({start, 0});

    while (!q.empty()) {
        auto [s, plies] = q.front();
        q.pop_front();

        if (s.mover == 0) { // A moves
            for (int k = 0; k < 8; ++k) {
                int nxA = s.ax + DX[k];
                int nyA = s.ay + DY[k];
                if (!inBox(nxA, nyA, minX, minY, maxX, maxY)) continue;

                // A captures B immediately?
                if (nxA == s.bx && nyA == s.by) {
                    long long p = plies + 1; // plies used total
                    return (p + 1) / 2;      // ceil(p/2) for integer p
                }

                State t{nxA, nyA, s.bx, s.by, 1};
                if (!vis.count(t)) {
                    vis.insert(t);
                    q.push_back({t, plies + 1});
                }
            }
        } else { // B moves
            for (int k = 0; k < 8; ++k) {
                int nxB = s.bx + DX[k];
                int nyB = s.by + DY[k];
                if (!inBox(nxB, nyB, minX, minY, maxX, maxY)) continue;

                // B captures A immediately?
                if (nxB == s.ax && nyB == s.ay) {
                    long long p = plies + 1;
                    return (p + 1) / 2;
                }

                State t{s.ax, s.ay, nxB, nyB, 0};
                if (!vis.count(t)) {
                    vis.insert(t);
                    q.push_back({t, plies + 1});
                }
            }
        }
    }
    // With generous padding we should always find a capture.
    // In case of an unexpected bound miss, fall back to a large number.
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Example from the spec:
    // knightA = [0,0], knightB = [4,2] -> expected 1 turn
    pair<int,int> A, B;
    if (!(cin >> A.first >> A.second >> B.first >> B.second)) {
        cerr << "Usage: provide four integers: ax ay bx by\n";
        cerr << "Example: 0 0 4 2\n";
        return 1;
    }
    long long ans = min_turns_knight_capture(A, B);
    cout << ans << "\n";
    return 0;
}
