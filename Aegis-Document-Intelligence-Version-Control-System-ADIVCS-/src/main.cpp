#include "storage.h"

int runCLI(Storage &st);

int main(){
    Storage st("aegis.db");
    return runCLI(st);
}
