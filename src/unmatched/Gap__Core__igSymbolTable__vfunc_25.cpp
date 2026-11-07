struct igResult { int w0; igResult() {} igResult(const igResult &o) { w0 = o.w0; } igResult &operator=(const igResult &o) { w0 = o.w0; return *this; } };
extern "C" {
extern igResult DAT_004fb410;
extern igResult DAT_004fb418;
char *FUN_0030d1d0(...);
char *strncpy(...);
}
struct Entry { int name; int a; int b; int path; };
struct List { char pad[8]; int count; int capacity; Entry *data; };
struct Table { char pad[28]; List *entries; int pad2; void *names; void *paths; };
extern "C" igResult Gap__Core__igSymbolTable__vfunc_25(Table *self, int idx, char *name, int nameSize, int *a, int *b, char *path, int pathSize) {
    igResult result = DAT_004fb418;
    Entry *e;
    char *s;

    if (idx >= 0 && idx * 4 < self->entries->count) {
        e = &self->entries->data[idx];
        *a = e->a;
        if (name != 0) {
if ((s = FUN_0030d1d0(self->names, e->name)) != 0) { strncpy(name, s, nameSize); } else { *name = 0; }
        }
        *b = e->b;
        if (path != 0) {
if ((s = FUN_0030d1d0(self->paths, e->path)) != 0) { strncpy(path, s, pathSize); } else { *path = 0; }
        }
        result = DAT_004fb410;
    } else {
        if (name != 0) {
            *name = 0;
        }
        *a = 0;
        *b = 0;
        if (path != 0) {
            *path = 0;
        }
    }
    return result;
}
