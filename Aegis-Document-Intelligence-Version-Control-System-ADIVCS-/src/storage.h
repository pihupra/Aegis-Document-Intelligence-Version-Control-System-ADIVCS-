#pragma once
#include "model.h"
#include <sqlite3.h>
#include <string>
#include <vector>


class Storage {
public:
explicit Storage(const std::string& dbPath);
~Storage();


bool init();


int createDocument(const DocumentMeta& meta, const std::string& content);
bool addVersion(int docId, const std::string& content);
std::vector<DocumentVersion> getVersions(int docId);
DocumentMeta getMeta(int docId);
std::vector<DocumentMeta> searchMetaByTitleOrTag(const std::string& query);


private:
sqlite3* db_{nullptr};
std::string path_;
};