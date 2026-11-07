typedef struct CallStackHashTable { int vt; int rc; unsigned int count; } CallStackHashTable;
typedef struct CallStackTableView { char pad[20]; CallStackHashTable *table; } CallStackTableView;
unsigned int Gap__Core__igCallStackTable__vfunc_29(CallStackTableView *self, unsigned int *stack) {
    CallStackHashTable *t = self->table;
    unsigned int sum = 0;
    unsigned int n;
    unsigned int v;
    unsigned int r;
    if (t != 0) { n = t->count; } else { n = 0; }
    if (stack != 0 && t != 0) {
        r = 0;
        if (n != 0) {
            v = *stack;
            while (v != 0) { sum += v; stack++; v = *stack; }
            r = sum % n;
        }
    } else {
        r = 0;
    }
    return r;
}
