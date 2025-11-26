#pragma once
#include "model.h"
#include <string>
#include <vector>

class Storage;

class Versioning {
public:
    explicit Versioning(Storage& storage);

    std::vector<DiffOp> diffVersions(int docId, int v1, int v2);
    bool rollbackTo(int docId, int versionId);
private:
    Storage& storage_;
};
