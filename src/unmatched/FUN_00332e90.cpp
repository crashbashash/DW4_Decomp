typedef struct Obj { int w0; int references; } Obj;
typedef struct OList { int pad0[2]; int count; int pad1; Obj **data; } OList;
typedef struct SList { int pad0; int references; int count; int pad1; int **data; } SList;
extern "C" {
int FUN_002eb010(int);
int List_Reserve(void *, int, int);
int StringChunk_ReleaseHeader(int, int *);
int StringPool_Construct(int);
char *StringPool_Intern(int, char *);
int igObject_Destroy(void *);
extern int DAT_00586f20[4];
extern SList *DAT_00587608[4];
extern OList *DAT_00587620[4];
void FUN_00332e90(int arg0, char *arg1);
}
/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at
 * p[-2]); releases the token on scope exit. */
class StringRef {
public:
    char *p;
    StringRef(char *s) : p(s) {}
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
};
extern "C" int StringList_AppendRetained(void *, StringRef *);
void FUN_00332e90(int arg0, char *arg1) {
    int v;
    int ok;
    SList *t;
    OList *t2;
    if (arg1 != 0) {
        char *r;
        if (arg1 == 0) {
            r = 0;
        } else {
            if (DAT_00586f20[0] == 0) {
                v = FUN_002eb010(16);
                if (v != 0) v = StringPool_Construct(v);
                DAT_00586f20[0] = v;
            }
            r = StringPool_Intern(DAT_00586f20[0], arg1);
        }
        {
            StringRef name(r);
            StringList_AppendRetained(DAT_00587608[0], &name);
        }
    } else {
        SList *l;
        int n;
        int i;
        int *old;
        int **p;
        int *np;
        l = DAT_00587608[0];
        n = l->count;
        i = 0;
        if (0 < n) {
            do {
                p = &l->data[i];
                if (DAT_00586f20[0] == 0) {
                    v = FUN_002eb010(16);
                    if (v != 0) v = StringPool_Construct(v);
                    DAT_00586f20[0] = v;
                }
                np = (int *)StringPool_Intern(DAT_00586f20[0], 0);
                old = *p;
                if (old != 0) {
                    int *hd = old - 2;
                    v = old[-1] - 1;
                    old[-1] = v;
                    if (v == 0) StringChunk_ReleaseHeader(*hd, hd);
                }
                i++;
                *p = np;
            } while (i < n);
        }
        l->count = 0;
        ok = DAT_00587608[0]->count > 0;
        if (ok == 0) List_Reserve(DAT_00587608[0], 0, 4);
        t = DAT_00587608[0];
        if (t != 0) {
            t->references = t->references - 1;
            if (((unsigned long long)((long long)t->references << 0x29) >> 0x29) == 0)
                igObject_Destroy(t);
        }
        DAT_00587608[0] = 0;
        {
            OList *l2 = DAT_00587620[0];
            if (l2 != 0) {
                int n2 = l2->count;
                int i2;
                int m, j;
                for (i2 = 0; i2 < n2; i2++) {
                    Obj *o = l2->data[i2];
                    if (o != 0) {
                        o->references = o->references - 1;
                        if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0)
                            igObject_Destroy(o);
                    }
                }
                m = l2->count;
                for (j = 0; j < m; j++) l2->data[j] = 0;
                l2->count = 0;
                ok = DAT_00587620[0]->count > 0;
                if (ok == 0) List_Reserve(DAT_00587620[0], 0, 4);
                t2 = DAT_00587620[0];
                if (t2 != 0) {
                    t2->pad0[1] = t2->pad0[1] - 1;
                    if (((unsigned long long)((long long)t2->pad0[1] << 0x29) >> 0x29) == 0)
                        igObject_Destroy(t2);
                }
                DAT_00587620[0] = 0;
            }
        }
    }
}
