#include "storage.h"
#include "versioning.h"
#include <cassert>

int main() {
    Storage st("aegis.db");
    DocumentMeta m; m.title="Test"; m.author="Me"; m.tags={"tag1","tag2"};
    int id = st.createDocument(m,"Hello World");
    assert(id>0);
    st.addVersion(id,"Hello World v2");
    auto vers = st.getVersions(id);
    assert(vers.size() == 2);
    return 0;
}
