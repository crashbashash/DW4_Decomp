extern "C" void memcpy(void *, void *, int);
extern "C" void FUN_002f8870(int, void *);
extern "C" int FUN_003081d0(int *, ...);
extern int DAT_004fbea0[4];
extern int DAT_004fbed0[4];
struct Alloc {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4();
    virtual void *Realloc(void *p, int n);
};
extern Alloc *DAT_00587218[4];
extern unsigned char GPR_00554ce4;
extern unsigned char GPR_00554ce8;

typedef struct Ranges {
    char pad[2020];
    unsigned int *data;   /* 2020 */
    int cap;              /* 2024 */
    int count;            /* 2028 */
    int half;             /* 2032 */
    char pad2[20];
    int total;            /* 2056 */
} Ranges;

typedef struct Obj {
    char pad[112];
    Ranges *r;            /* 112 */
    char pad2[68];
    int lvlA;             /* 184 */
    int lvlB;             /* 188 */
} Obj;

extern "C" void Gap__Core__igArenaMemoryPool__vfunc_111(Obj *o, unsigned int lo, int len) {
    unsigned int hi;
    int i;
    Ranges *r;
    bool found;
    found = 0;
    r = o->r;
    r->total += len;
    if (len < 0) hi = lo; else hi = lo + len;
    i = r->count - 2;
    for (; i >= 0; i -= 2) {
        unsigned int *e = (unsigned int *)((char *)r->data + i * 4);
        unsigned int a = e[0];
        unsigned int *h;
        if (lo >= a && (h = e + 1, lo <= e[1])) {
            if (found) {
                if (o->lvlB >= 2 && GPR_00554ce4 == 0) {
                    int rc = FUN_003081d0(DAT_004fbea0, r->data, h, a);
                    if (rc != 1 && rc == 2) GPR_00554ce4 = 1;
                }
                return;
            } else {
                if (len < 0 && a == hi) {
                    int j = i + 2;
                    if (j < r->count) {
                        memcpy(e, (char *)r->data + j * 4, (r->count - j) * 4);
                    }
                    r->count -= 2;
                } else if (len < 0 || e[1] < hi) {
                    *h = hi;
                }
                found = 1;
                if (o->lvlA < 2) break;
            }
        }
        if (len > 0) break;
    }
    if (!found && len >= 0) {
        int ncap;
        int cap = r->cap;
if (r->count >= cap) {
            void *np;
            ncap = cap + 2;
            if (ncap == 0) ncap = 512;
            np = DAT_00587218[0]->Realloc(r->data, ncap * 4);
            if (np != 0) {
                r->data = (unsigned int *)np;
                r->cap = ncap;
            } else {
                if (o->lvlB > 0) {
                    FUN_002f8870(0, o);
                    if (GPR_00554ce8 == 0) {
                        int rc = FUN_003081d0(DAT_004fbed0);
                        if (rc != 1 && rc == 2) GPR_00554ce8 = 1;
                    }
                }
                return;
            }
        }
        {
            int h;
            r->data[r->count] = lo;
            r->data[r->count + 1] = lo + len;
            r->count += 2;
            h = r->count / 2;
            if (r->half < h) r->half = h;
        }
    }
}
