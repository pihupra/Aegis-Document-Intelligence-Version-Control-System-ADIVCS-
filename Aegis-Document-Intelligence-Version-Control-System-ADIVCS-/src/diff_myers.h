#pragma once
#include <string>
#include <vector>

struct DiffOp {
    enum Type { Equal, Insert, Delete } type;
    std::string line;
};

std::vector<DiffOp> myers_diff(const std::vector<std::string>& a, const std::vector<std::string>& b);
