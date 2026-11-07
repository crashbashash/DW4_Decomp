void *FUN_002b9500();
int FUN_002eb010();
int FUN_00307700();
void *FUN_00307c10();
int FUN_0030b3c0();
int FUN_0030b460();
int FUN_0030bce0();
int FUN_0030bee0();
int StringChunk_ReleaseHeader();
int StringList_CopyRetained();
int StringPool_Construct();
int *StringPool_Intern();
int igObject_Destroy();
int igObject_GetAllocator();
int strlen();
extern char *DAT_004c22f0[4];
extern char DAT_004fb190[];
extern int DAT_00586f20[4];
typedef struct Str { char pad[4]; int _refCount; char *text; int length; } Str;
typedef struct SL { char pad[8]; int count; int cap; int **data; } SL;
typedef struct Pair { char pad[12]; void *value; } Pair;
static inline int pool(void) {
    int p;
    if (DAT_00586f20[0] == 0) {
        p = FUN_002eb010(0x10);
        if (p != 0) {
            p = StringPool_Construct(p);
        }
        DAT_00586f20[0] = p;
    }
    return DAT_00586f20[0];
}
static inline char *text(Str *s) { char *t = s->text; if (t == 0) { return DAT_004c22f0[0]; } return t; }
static inline int *intern(char *s) {
    if (s == 0) {
        return 0;
    }
    return StringPool_Intern(pool(), s);
}
static inline void releaseRef(int *old) {
    int *hd;
    int rc;
    if (old != 0) {
        hd = old - 2;
        rc = old[-1] - 1;
        old[-1] = rc;
        if (rc == 0) {
            StringChunk_ReleaseHeader(*hd, hd);
        }
    }
}
static inline void setAt(SL *l, int i, int **v) {
    int n = l->count;
    if (n != 0 && i >= 0 && i < n) {
        int **slot = &l->data[i];
        int *w = *v;
        if (w != 0) {
            w[-1] = w[-1] + 1;
        }
        releaseRef(*slot);
        *slot = *v;
    }
}
static inline void append(Str *c, char *s) { int at = c->length; FUN_0030b460(c, s, at, strlen(s)); }
int FUN_00306aa0(void *self, int section, int key, SL *list, int create) {
    Str *a;
    Str *b;
    int *r1;
    int *tmp;
    int *r2;
    int *r3;
    int saved;
    int i; Pair *p; int n; int j; Str *c; char *s2; Str *held; Str *c2; int at; int at2;

    *(int volatile *)&saved = key;
    p = FUN_00307c10(self, section, key, 0);
    if (p != 0) {
        FUN_0030bce0(p->value, 0x2C, list);
        *(Str *volatile *)&a = FUN_002b9500(igObject_GetAllocator(self));
        for (i = 0; i < list->count; i++) {
            StringList_CopyRetained(&r1, list, i);
            FUN_0030b3c0(a, r1);
            releaseRef(r1);
            FUN_0030bee0(a);
            *(int *volatile *)&tmp = intern(text(a));
            setAt(list, i, &tmp);
            releaseRef(tmp);
        }
        held = a;
        if (held != 0) {
            held->_refCount = held->_refCount - 1;
            if (((unsigned long long)((long long)held->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(held);
            }
        }
    } else if (create != 0) {
        *(Str *volatile *)&b = FUN_002b9500(igObject_GetAllocator(self));
        n = list->count;
        if (n != 0) {
            StringList_CopyRetained(&r2, list, 0);
            FUN_0030b3c0(b, r2);
            releaseRef(r2);
        }
        for (j = 1; j < n; j++) {
            c = b; at = c->length;
            FUN_0030b460(c, DAT_004fb190, at, strlen(DAT_004fb190));
            StringList_CopyRetained(&r3, list, j);
            c2 = b; s2 = (char *)r3; at2 = c2->length; FUN_0030b460(c2, s2, at2, strlen(s2));
            releaseRef(r3);
        }
        FUN_00307700(self, section, saved, text(b));
        held = b;
        if (held != 0) {
            held->_refCount = held->_refCount - 1;
            if (((unsigned long long)((long long)held->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(held);
            }
        }
    }
    return p != 0;
}
