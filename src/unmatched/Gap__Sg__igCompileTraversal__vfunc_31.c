typedef struct RefCountedEntry { int w0; int ref; } RefCountedEntry;
typedef struct RefCountedEntryList { char pad0[8]; int cnt; int pad12; RefCountedEntry **data; } RefCountedEntryList;
int igObject_Destroy();
static inline void clearEntries(RefCountedEntryList *l) {
    int n;
    int m;
    int i;
    int j;
    n = l->cnt;
    for (i = 0; i < n; i++) {
        RefCountedEntry *o = l->data[i];
        if (o) {
            o->ref = o->ref - 1;
            if (((unsigned long long)((long long)o->ref << 0x29) >> 0x29) == 0) igObject_Destroy(o);
        }
    }
    m = l->cnt;
    for (j = 0; j < m; j++) l->data[j] = 0;
    l->cnt = 0;
}
void Gap__Sg__igCompileTraversal__vfunc_31(char *p) {
    clearEntries(*(RefCountedEntryList **)(p + 472));
    clearEntries(*(RefCountedEntryList **)(p + 476));
    *(int *)(*(char **)(p + 492) + 8) = 0;
    clearEntries(*(RefCountedEntryList **)(p + 504));
    p[484] = 0;
    p[496] = 0;
}
