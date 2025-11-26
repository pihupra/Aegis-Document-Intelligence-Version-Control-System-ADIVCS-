#include "versioning.h"
#include "storage.h"
#include "diff_myers.h"
#include <sstream>

Versioning::Versioning(Storage &storage) : storage_(storage) {}

static std::vector<std::string> split_lines(const std::string& s) {
    std::vector<std::string> out;
    std::istringstream iss(s);
    std::string line;
    while (std::getline(iss, line)) out.push_back(line);
    return out;
}

std::vector<DiffOp> Versioning::diffVersions(int docId, int v1, int v2) {
    auto versions = storage_.getVersions(docId);
    std::string c1, c2;
    for (auto &v : versions) { if (v.versionId == v1) c1 = v.content; if (v.versionId == v2) c2 = v.content; }
    return myers_diff(split_lines(c1), split_lines(c2));
}

bool Versioning::rollbackTo(int docId, int versionId) {
    auto versions = storage_.getVersions(docId);
    for (auto &v : versions) if (v.versionId == versionId) return storage_.addVersion(docId, v.content);
    return false;
}
