#include "dw4/igSmartPointer.h"

struct Entry : public igObject { char pad[12]; char *name; };
struct EntryList { int w0; int w4; int count; int capacity; Entry **data; };
struct Table { char pad[304]; EntryList *entries; };
extern "C" {
void StringChunk_ReleaseHeader(int, int *);
}
struct StringRef {
    char *p;
    StringRef();
    ~StringRef() {
        if (p != 0) {
            int *header = (int *)p - 2;
            int count = header[1] - 1;
            header[1] = count;
            if (count == 0) {
                StringChunk_ReleaseHeader(header[0], header);
            }
        }
    }
};

extern "C" StringRef FUN_001554a0();
extern "C" int FUN_00155f10(Table *table) {
    StringRef name = FUN_001554a0();
    int i = 0;
    if (table->entries->count > 0) {
        for (; i < table->entries->count; i++) {
            igSmartPointer<Entry> entry(table->entries->data[i], kRetainReference);
            if (entry.p == 0) {
                continue;
            }
            if (entry.p->name == name.p) {
                return i;
            }
        }
    }
    return -1;
}
