typedef struct TagCallEntry {
    void *table;
    void (*begin)(void *obj, int id);
    void (*end)(void *arg, int id);
    void *arg;
} TagCallEntry;

typedef struct TagCallObj {
    char pad[8072];
    int type;
} TagCallObj;

void FUN_0029dd10(TagCallObj *obj, int type, int id, TagCallEntry *entry);
int FUN_002a1f28(void *table, int a, int b);

int FUN_002a1e50(TagCallObj *obj, int id, int a, int b)
{
    TagCallEntry entry;
    int ret;
    void (*begin)(void *obj, int id);
    void (*end)(void *arg, int id);
    void *arg;

    if (obj->type == 8)
        return 1;
    FUN_0029dd10(obj, obj->type, id, &entry);
    begin = entry.begin;
    end = entry.end;
    arg = entry.arg;
    if (entry.table == 0)
        return 1;
    ret = FUN_002a1f28(entry.table, a, b);
    if (ret == 1) {
        if (begin != 0)
            begin(obj, id);
        if (end != 0)
            end(arg, id);
    }
    return ret;
}
