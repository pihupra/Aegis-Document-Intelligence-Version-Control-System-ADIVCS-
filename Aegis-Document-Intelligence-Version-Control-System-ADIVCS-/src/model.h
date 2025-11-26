#pragma once
#include <string>
#include <vector>
#include <ctime>


struct DocumentVersion {
int versionId{-1};
int docId{-1};
std::string content;
std::time_t timestamp{0};
};


struct DocumentMeta {
int id{-1};
std::string title;
std::string author;
std::vector<std::string> tags;
};