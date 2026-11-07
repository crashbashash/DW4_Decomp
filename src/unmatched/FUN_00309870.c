typedef struct R { int w0; int refs; } R;
typedef struct Lst { char pad8[8]; int n; char pad12[4]; R **data; } Lst;
typedef struct Ob { char pad12[12]; R *f12; Lst *f16; } Ob;
int igObject_Destroy();

void FUN_00309870(Ob *arg0) {
    int m;
    int j;
    Lst *l;
    int n;
    int i;
    R *p;
    R *q;

    l = arg0->f16;
    n = l->n;
    for (i = 0; i < n; i++) {
        p = l->data[i];
        if (p != 0) {
            p->refs = p->refs - 1;
            if (((unsigned long long)((long long)p->refs << 0x29) >> 0x29) == 0) {
                igObject_Destroy(p);
            }
        }
    }
    m = l->n;
    for (j = 0; j < m; j++) {
        l->data[j] = 0;
    }
    l->n = 0;
    q = arg0->f12;
    if (q != 0) {
        q->refs = q->refs - 1;
        if (((unsigned long long)((long long)q->refs << 0x29) >> 0x29) == 0) {
            igObject_Destroy(q);
        }
    }
    arg0->f12 = 0;
}
