#include "dw4/igSmartPointer.h"

struct KeyedEntry : public igObject { char *name; };
struct KeyedEntryList { int w0; int w4; int count; int capacity; KeyedEntry **data; };
struct KeyedEntryOwner { char pad[308]; KeyedEntryList *entries; };
struct NamedValue { const char *name; int value; };
extern "C" {
void StringChunk_ReleaseHeader(int, int *);
int strcmp(const char *, const char *);
extern char DAT_004e0858[];
extern NamedValue DAT_0048a260[47];
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

static inline const char *nameOf(const KeyedEntry *entry) {
    return entry->name ? entry->name : DAT_004e0858;
}

extern "C" StringRef FUN_001554a0();
extern "C" int FUN_001560b0(KeyedEntryOwner *table) {
    StringRef name = FUN_001554a0();
    int i = 0;
    if (table->entries->count > 0) {
        for (i = 0; i < table->entries->count; i++) {
            igSmartPointer<KeyedEntry> entry(table->entries->data[i], kRetainReference);
            if (entry.p && nameOf(entry.p) == name.p) {
                return i + 47;
            }
        }
    }
    for (i = 0; i < 47; i++) {
        if (strcmp(DAT_0048a260[i].name, name.p) == 0) {
            return DAT_0048a260[i].value;
        }
    }
    return -1;
}
