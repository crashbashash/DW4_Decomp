typedef struct MatrixStackEntry { float f[16]; } MatrixStackEntry;
typedef struct ReleasableList { int pad0, pad4; volatile int n; int cap; int *data; } ReleasableList;
typedef struct MatrixStackList { int pad0, pad4; volatile int n; int cap; MatrixStackEntry *data; } MatrixStackList;
typedef struct CountedObject { int vt; int rc; } CountedObject;
typedef struct TraversalMatrixState { int p[8]; MatrixStackList *mats; ReleasableList *objs; } TraversalMatrixState;
int List_Resize(void *, int, int);
int Matrix44_Copy(void *, void *);
int igObject_Destroy(void *);
extern int DAT_004e0ef0[4];
void FUN_001ce970(TraversalMatrixState *self) {
    ReleasableList *o;
    int cnt;
    int idx;
    int j;
    MatrixStackList *m;
    int n;
    int i;
    self->mats->n = 0;
    m = self->mats;
    idx = m->n;
    if (idx < m->cap) {
        m->n = m->n + 1;
    } else {
        List_Resize(m, idx + 1, 64);
    }
    Matrix44_Copy(m->data + idx, DAT_004e0ef0);
    o = self->objs;
    n = o->n;
    for (i = 0; i < n; i++) {
        CountedObject *p = (CountedObject *)o->data[i];
        if (p != 0) {
            p->rc = p->rc - 1;
            if (((unsigned long long)((long long)p->rc << 0x29) >> 0x29) == 0) {
                igObject_Destroy(p);
            }
        }
    }
    cnt = o->n;
    for (j = 0; j < cnt; j++) {
        o->data[j] = 0;
    }
    o->n = 0;
}
