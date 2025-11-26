#include "diff_myers.h"
#include <algorithm>
#include <vector>
#include <iostream>

// Simplified Myers' diff implementation
static inline void backtrack(const std::vector<std::vector<int>>& trace, int N, int M, std::vector<DiffOp>& out, const std::vector<std::string>& a, const std::vector<std::string>& b) {
    int x = N, y = M;
    for (int d = (int)trace.size() - 1; d >= 0; --d) {
        int k = x - y;
        int prev_k;
        if (k == -d || (k != d && trace[d-1][k-1 + d-1] < trace[d-1][k+1 + d-1])) prev_k = k + 1;
        else prev_k = k - 1;
        int prev_x = trace[d-1][prev_k + d-1];
        int prev_y = prev_x - prev_k;
        while (x > prev_x && y > prev_y) { out.push_back({DiffOp::Equal, a[x-1]}); --x; --y; }
        if (x == prev_x) { out.push_back({DiffOp::Insert, b[y-1]}); --y; }
        else { out.push_back({DiffOp::Delete, a[x-1]}); --x; }
    }
    std::reverse(out.begin(), out.end());
}

std::vector<DiffOp> myers_diff(const std::vector<std::string>& a, const std::vector<std::string>& b) {
    int N = (int)a.size(), M = (int)b.size();
    if (N == 0) { std::vector<DiffOp> out; for (auto &line : b) out.push_back({DiffOp::Insert, line}); return out; }
    if (M == 0) { std::vector<DiffOp> out; for (auto &line : a) out.push_back({DiffOp::Delete, line}); return out; }

    int maxd = N + M;
    std::vector<int> v(2*maxd+1);
    std::vector<std::vector<int>> trace;
    v[maxd+1] = 0;

    for (int d=0; d<=maxd; ++d) {
        std::vector<int> v_snapshot(2*maxd+1);
        for (int k=-d; k<=d; k+=2) {
            int idx = k + maxd;
            int x;
            if (k == -d || (k != d && v[idx-1] < v[idx+1])) x = v[idx+1]; else x = v[idx-1] + 1;
            int y = x - k;
            while (x < N && y < M && a[x] == b[y]) { ++x; ++y; }
            v_snapshot[idx] = x; v[idx] = x;
            if (x >= N && y >= M) {
                trace.push_back(v_snapshot);
                std::vector<DiffOp> out;
                backtrack(trace, N, M, out, a, b);
                return out;
            }
        }
        trace.push_back(v_snapshot);
    }
    return {};
}
