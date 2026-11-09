struct Entry { int vtable; unsigned references; char pad[12]; char *name; };
struct EntryList { int w0; int w4; int count; int capacity; Entry **data; };
struct Table { char pad[304]; EntryList *entries; };
extern "C" {
void StringChunk_ReleaseHeader(int, int *);
int igObject_Destroy(Entry *);
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
struct EntryRef {
    Entry *p;
    EntryRef(Entry *object) : p(object) {
        if (p != 0) {
            p->references = p->references + 1;
        }
    }
    ~EntryRef() {
        Entry *object = p;
        if (object != 0) {
            object->references = object->references - 1;
            if ((object->references & 0x7FFFFF) == 0) {
                igObject_Destroy(object);
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
            EntryRef entry(table->entries->data[i]);
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
