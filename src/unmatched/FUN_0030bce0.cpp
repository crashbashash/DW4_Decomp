extern "C" {
extern int DAT_00586f20[4];
int strlen(...);
int FUN_002eb010(...);
int Memory_FreeBuffer(...);
void StringChunk_ReleaseHeader(...);
int StringList_AppendRetained(...);
int StringPool_Construct(...);
void *StringPool_Intern(...);
char *igObject_DuplicateString(...);
}
struct SrcStr { char p0[8]; int f8; int f12; };
struct List { char p0[8]; int count; char p12[4]; void **items; };
struct Rel {
    static inline void go(void *p) {
        if (p != 0) {
            int *t = (int *)((char *)p - 8);
            int v = *(int *)((char *)p - 4) - 1;
            *(int *)((char *)p - 4) = v;
            if (v == 0) StringChunk_ReleaseHeader(*t, t);
        }
    }
};
extern "C" void FUN_0030bce0(SrcStr *src, long long delim, List *list) {
    int n = list->count;
    for (int i = 0; i < n; i++) {
        void **slot = (void **)((char *)list->items + i * 4);
        if (DAT_00586f20[0] == 0) {
            int v = FUN_002eb010(0x10);
            if (v != 0) v = StringPool_Construct(v);
            DAT_00586f20[0] = v;
        }
        void *ni = StringPool_Intern(DAT_00586f20[0], 0);
        Rel::go(*slot);
        *slot = ni;
    }
    list->count = 0;
    if (src->f8 != 0) {
        char *buf = igObject_DuplicateString(src, src->f8);
        for (unsigned i = 0; i < (unsigned)src->f12; i++) {
            if ((char)delim == buf[i]) buf[i] = 0;
        }
        char *p = buf;
        while (p < buf + src->f12) {
            void *s;
            if (p == 0) s = 0;
            else {
                if (DAT_00586f20[0] == 0) {
                    int v = FUN_002eb010(0x10);
                    if (v != 0) v = StringPool_Construct(v);
                    DAT_00586f20[0] = v;
                }
                s = StringPool_Intern(DAT_00586f20[0], p);
            }
            void *sp = s;
            StringList_AppendRetained(list, &sp);
            Rel::go(sp);
            p += strlen(p) + 1;
        }
        Memory_FreeBuffer(buf);
    }
}
