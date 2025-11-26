#include "storage.h"
#include <sqlite3.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <ctime>

// Get all versions of a document
std::vector<DocumentVersion> Storage::getVersions(int docId) {
    std::vector<DocumentVersion> out;
    const char* sql = "SELECT versionId, docId, content, timestamp FROM versions WHERE docId=? ORDER BY versionId ASC;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db_) << "\n";
        return out;
    }

    sqlite3_bind_int(stmt, 1, docId);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        DocumentVersion v;
        v.versionId = sqlite3_column_int(stmt, 0);
        v.docId = sqlite3_column_int(stmt, 1);
        const unsigned char* text = sqlite3_column_text(stmt, 2);
        v.content = text ? reinterpret_cast<const char*>(text) : "";
        v.timestamp = static_cast<std::time_t>(sqlite3_column_int64(stmt, 3));
        out.push_back(std::move(v));
    }

    sqlite3_finalize(stmt);
    return out;
}

// Get metadata of a document
DocumentMeta Storage::getMeta(int docId) {
    DocumentMeta m;
    const char* sql = "SELECT id, title, author, tags FROM documents WHERE id=?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db_) << "\n";
        return m;
    }

    sqlite3_bind_int(stmt, 1, docId);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        m.id = sqlite3_column_int(stmt, 0);
        const unsigned char* title = sqlite3_column_text(stmt, 1);
        m.title = title ? reinterpret_cast<const char*>(title) : "";
        const unsigned char* author = sqlite3_column_text(stmt, 2);
        m.author = author ? reinterpret_cast<const char*>(author) : "";

        const unsigned char* tags_c = sqlite3_column_text(stmt, 3);
        if (tags_c) {
            std::string tags(reinterpret_cast<const char*>(tags_c));
            size_t pos = 0;
            while (true) {
                auto comma = tags.find(',', pos);
                if (comma == std::string::npos) {
                    if (pos < tags.size()) m.tags.push_back(tags.substr(pos));
                    break;
                }
                m.tags.push_back(tags.substr(pos, comma - pos));
                pos = comma + 1;
            }
        }
    }

    sqlite3_finalize(stmt);
    return m;
}

// Search documents by title or tags
std::vector<DocumentMeta> Storage::searchMetaByTitleOrTag(const std::string &query) {
    std::vector<DocumentMeta> out;
    const char* sql = "SELECT id, title, author, tags FROM documents WHERE title LIKE ? OR tags LIKE ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db_) << "\n";
        return out;
    }

    std::string like = "%" + query + "%";
    sqlite3_bind_text(stmt, 1, like.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, like.c_str(), -1, SQLITE_TRANSIENT);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        DocumentMeta m;
        m.id = sqlite3_column_int(stmt, 0);

        const unsigned char* title = sqlite3_column_text(stmt, 1);
        m.title = title ? reinterpret_cast<const char*>(title) : "";

        const unsigned char* author = sqlite3_column_text(stmt, 2);
        m.author = author ? reinterpret_cast<const char*>(author) : "";

        const unsigned char* tags_c = sqlite3_column_text(stmt, 3);
        if (tags_c) {
            std::string tags(reinterpret_cast<const char*>(tags_c));
            size_t pos = 0;
            while (true) {
                auto comma = tags.find(',', pos);
                if (comma == std::string::npos) {
                    if (pos < tags.size()) m.tags.push_back(tags.substr(pos));
                    break;
                }
                m.tags.push_back(tags.substr(pos, comma - pos));
                pos = comma + 1;
            }
        }

        out.push_back(std::move(m));
    }

    sqlite3_finalize(stmt);
    return out;
}
