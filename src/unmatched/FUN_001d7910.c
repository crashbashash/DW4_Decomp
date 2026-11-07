void FUN_00300c00(void *, void *, int);
int igMetaObject_CountTree(void *);
void *FUN_002fe300(void *, int);
void FUN_001e06c0(void *, void *, void *);
void FUN_001e07a0(void);
typedef struct ShaderTraversalPair { void *_meta; void *_function; } ShaderTraversalPair;
typedef struct ShaderTraversalPairs { ShaderTraversalPair _pairs[4]; } ShaderTraversalPairs;
extern ShaderTraversalPairs DAT_0048dac0;
extern void *DAT_005628e0;
extern void *DAT_005628e8;
extern void *DAT_00562640;
extern void *DAT_005618d8;
extern void *DAT_00561a98;
extern void *DAT_00561860;
extern void *DAT_00561e98;
extern void *DAT_00561ee8;
extern void *DAT_00561578;
extern void *DAT_00561570;
static inline void clearBytes(char *p, unsigned int n) {
    if (p != 0) {
        do {
            *p = 0;
            n--;
            p++;
        } while (n != 0);
    }
}
void FUN_001d7910(void) {
    void *metas[7];
    ShaderTraversalPairs pairs;
    int i;
    int count;
    int child;
    ShaderTraversalPair *p;
    int n;
    int j;
    void **m;
    FUN_00300c00(DAT_005628e0, DAT_00562640, 1);
    FUN_00300c00(DAT_005628e8, DAT_00562640, 1);
    clearBytes((char *)metas, 28);
    metas[0] = DAT_005618d8;
    metas[1] = DAT_00561a98;
    metas[2] = DAT_00561860;
    metas[3] = DAT_00561e98;
    metas[4] = DAT_00561ee8;
    metas[5] = DAT_00561578;
    metas[6] = DAT_00561570;
    for (i = 0; i < 7; i++) {
        m = &metas[i];
        count = igMetaObject_CountTree(*m);
        for (child = 0; child < count; child++) {
            FUN_001e06c0(DAT_005628e0, FUN_002fe300(*m, child), FUN_001e07a0);
        }
    }
    pairs = DAT_0048dac0;
    pairs._pairs[0]._meta = DAT_00561860;
    pairs._pairs[1]._meta = DAT_00561e98;
    pairs._pairs[2]._meta = DAT_00561ee8;
    pairs._pairs[3]._meta = DAT_00561a98;
    for (i = 0; i < 4; i++) {
        p = &pairs._pairs[i];
        n = igMetaObject_CountTree(p->_meta);
        for (j = 0; j < n; j++) {
            FUN_001e06c0(DAT_005628e8, FUN_002fe300(p->_meta, j), p->_function);
        }
    }
}
