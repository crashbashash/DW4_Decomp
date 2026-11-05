typedef struct M { float f[16]; } M;
typedef struct L { int pad0, pad4; volatile int n; int cap; int *data; } L;
typedef struct ML { int pad0, pad4; volatile int n; int cap; M *data; } ML;
typedef struct O { int vt; int rc; } O;
typedef struct S { int p[8]; ML *mats; L *objs; } S;
int List_Resize(void *, int, int);
int Matrix44_Copy(void *, void *);
int igObject_Destroy(void *);
extern int DAT_004e0ef0[4];
void FUN_001ce970(S *self) {
    int j, cnt; ML *m; int idx; int i, n; L *o;
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
        O *p = (O *)o->data[i];
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
