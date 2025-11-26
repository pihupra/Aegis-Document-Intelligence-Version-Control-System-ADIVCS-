#include "storage.h"
#include "versioning.h"
#include <iostream>
#include <sstream> // Needed for std::ostringstream
#include "diff_myers.h"



void printMenu(){
    std::cout<<"\\nAegis Document System\\n1. Create document\\n2. Add version (edit)\\n3. List versions\\n4. Diff versions\\n5. Search by title/tag\\n0. Exit\\n";
}

int runCLI(Storage &st){
    Versioning ver(st);
    while(true){
        printMenu();
        int opt; if(!(std::cin>>opt)) break;
        if(opt==0) break;
        if(opt==1){
            DocumentMeta m; std::string content; std::cout<<"Title: "; std::cin.ignore(); std::getline(std::cin,m.title);
            std::cout<<"Author: "; std::getline(std::cin,m.author);
            std::cout<<"Tags (comma separated): "; std::string tags; std::getline(std::cin,tags);
            m.tags.clear(); size_t pos=0; while(true){ auto c=tags.find(',',pos); if(c==std::string::npos){ if(pos<tags.size()) m.tags.push_back(tags.substr(pos)); break;} m.tags.push_back(tags.substr(pos,c-pos)); pos=c+1; }
            std::cout<<"Initial content (end with a single line containing only .):\\n";
            std::string line; std::ostringstream oss;
            while(true){ std::getline(std::cin,line); if(line==".") break; oss<<line<<"\\n"; }
            content = oss.str();
            int id = st.createDocument(m,content);
            std::cout<<"Created doc id="<<id<<"\\n";
        } else if(opt==2){
            int id; std::cout<<"Doc id: "; std::cin>>id; std::cin.ignore();
            std::cout<<"New content (end with single .):\\n"; std::string line; std::ostringstream oss;
            while(true){ std::getline(std::cin,line); if(line==".") break; oss << line<<"\\n"; }
            st.addVersion(id,oss.str());
            std::cout<<"Added version\\n";
        } else if(opt==3){
            int id; std::cout<<"Doc id: "; std::cin>>id;
            auto vers = st.getVersions(id);
            for(auto &v:vers) std::cout<<v.versionId<<" - "<<v.timestamp<<" chars="<<v.content.size()<<"\\n";
        } else if(opt==4){
            int id,v1,v2; std::cout<<"Doc id, v1, v2: "; std::cin>>id>>v1>>v2;
            auto diffs = ver.diffVersions(id,v1,v2);
            for(auto &d:diffs){
                if(d.type==DiffOp::Equal) std::cout<<"  "<<d.line<<"\\n";
                else if(d.type==DiffOp::Insert) std::cout<<"+ "<<d.line<<"\\n";
                else std::cout<<"- "<<d.line<<"\\n";
            }
        } else if(opt==5){
            std::string q; std::cout<<"Query: "; std::cin>>q;
            auto res = st.searchMetaByTitleOrTag(q);
            for(auto &m:res) std::cout<<m.id<<" | "<<m.title<<" | "<<m.author<<"\\n";
        }
    }
    return 0;
}
