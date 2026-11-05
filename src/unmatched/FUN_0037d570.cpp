extern "C" {
typedef struct Target { int w0, w4, w8, w12; int kind; } Target;
typedef struct Entry { int w0, w4, w8; Target *target; int w16, w20; long long armed; short type; } Entry;
typedef struct EntryList { int w0, w4; int count; int w12; Entry **items; } EntryList;
typedef struct Owner { char pad[40]; EntryList *list; } Owner;
int FUN_003a70c0(Target *t);
void FUN_003a6f70(Target *t, int v);
void FUN_0037d570(Owner *self, int on);
}

void FUN_0037d570(Owner *self, int on) {
    int i;
    for (i = 0; i < self->list->count; i++) {
        Entry *e = self->list->items[i];
        if (e->armed != 0 && e->type == 4) {
            Target *t = e->target;
            if (FUN_003a70c0(t) == 1) {
                if (on != 0) {
                    FUN_003a6f70(t, t->kind == 3 ? 127 : 0);
                } else {
                    FUN_003a6f70(t, t->kind == 3 ? 0 : -999);
                }
            }
        }
    }
}
