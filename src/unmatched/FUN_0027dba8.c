/* Between FUN_0027b2b0/FUN_0027b2c8, dispatches every inactive entry of a list to its object's
 * method at vtable +32; hangs on a null list. */
int FUN_0027b2b0();
int FUN_0027b2c8();

struct Object0027dba8;
struct ObjectVtbl0027dba8 {
    char pad0[32];
    void (*method32)(struct Object0027dba8 *self, int id, void *data); /* +32 */
};
struct Object0027dba8 {
    struct ObjectVtbl0027dba8 *vtbl;
};
struct Owner0027dba8 {
    int f0;
    struct Object0027dba8 *object; /* +4 */
};

struct Entry0027dba8 {
    char busy;                   /* +0: non-zero entries are skipped */
    char id;                     /* +1 */
    char pad2[2];
    struct Owner0027dba8 *owner; /* +4 */
    char data[8];                /* +8 */
};

struct List0027dba8 {
    int count;                   /* +0 */
    char pad4[12];
    struct Entry0027dba8 entries[1]; /* +16 */
};

void FUN_0027dba8(int unused, struct List0027dba8 *list) {
    struct Entry0027dba8 *entry;
    int n;
    int i;

    if (list == 0) {
        while (1) {
        }
    }
    n = list->count;
    FUN_0027b2b0();
    for (i = 0; i < n; i++) {
        entry = &list->entries[i];
        if (entry->busy == 0) {
            struct Object0027dba8 *object = entry->owner->object;
            object->vtbl->method32(object, entry->id, entry->data);
        }
    }
    FUN_0027b2c8();
}
