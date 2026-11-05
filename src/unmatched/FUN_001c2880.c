typedef struct R { int w0; int refs; } R;
typedef struct OL { char p[8]; int count; int cap; R **data; } OL;
typedef struct S { char pad[64]; OL *l64; OL *l68; char b72; char pad73[3]; R *f76; R *f80; R *f84; R *f88; R *f92; R *f96; R *f100; R *f104; R *f108; } S;
int igObject_Destroy(R *);
void FUN_001c2880(S *arg0) {
    OL *l;
    int n;
    int i;
    int n2;
    int i2;
    R *p;
    R *q;
    l = arg0->l64;
    n = l->count;
    for (i = 0; i < n; i++) {
        p = l->data[i];
        if (p != 0) {
            p->refs = p->refs - 1;
            if (((unsigned long long)((long long)p->refs << 0x29) >> 0x29) == 0) igObject_Destroy(p);
        }
    }
    n2 = l->count;
    for (i2 = 0; i2 < n2; i2++) {
        l->data[i2] = 0;
    }
    l->count = 0;
    l = arg0->l68;
    n = l->count;
    for (i = 0; i < n; i++) {
        p = l->data[i];
        if (p != 0) {
            p->refs = p->refs - 1;
            if (((unsigned long long)((long long)p->refs << 0x29) >> 0x29) == 0) igObject_Destroy(p);
        }
    }
    n2 = l->count;
    for (i2 = 0; i2 < n2; i2++) {
        l->data[i2] = 0;
    }
    l->count = 0;
    arg0->b72 = 0;
    q = arg0->f76;
    if (q != 0) {
        q->refs = q->refs - 1;
        if (((unsigned long long)((long long)q->refs << 0x29) >> 0x29) == 0) igObject_Destroy(q);
    }
    arg0->f76 = 0;
    q = arg0->f80;
    if (q != 0) {
        q->refs = q->refs - 1;
        if (((unsigned long long)((long long)q->refs << 0x29) >> 0x29) == 0) igObject_Destroy(q);
    }
    arg0->f80 = 0;
    q = arg0->f84;
    if (q != 0) {
        q->refs = q->refs - 1;
        if (((unsigned long long)((long long)q->refs << 0x29) >> 0x29) == 0) igObject_Destroy(q);
    }
    arg0->f84 = 0;
    q = arg0->f88;
    if (q != 0) {
        q->refs = q->refs - 1;
        if (((unsigned long long)((long long)q->refs << 0x29) >> 0x29) == 0) igObject_Destroy(q);
    }
    arg0->f88 = 0;
    q = arg0->f92;
    if (q != 0) {
        q->refs = q->refs - 1;
        if (((unsigned long long)((long long)q->refs << 0x29) >> 0x29) == 0) igObject_Destroy(q);
    }
    arg0->f92 = 0;
    q = arg0->f96;
    if (q != 0) {
        q->refs = q->refs - 1;
        if (((unsigned long long)((long long)q->refs << 0x29) >> 0x29) == 0) igObject_Destroy(q);
    }
    arg0->f96 = 0;
    q = arg0->f100;
    if (q != 0) {
        q->refs = q->refs - 1;
        if (((unsigned long long)((long long)q->refs << 0x29) >> 0x29) == 0) igObject_Destroy(q);
    }
    arg0->f100 = 0;
    q = arg0->f104;
    if (q != 0) {
        q->refs = q->refs - 1;
        if (((unsigned long long)((long long)q->refs << 0x29) >> 0x29) == 0) igObject_Destroy(q);
    }
    arg0->f104 = 0;
    q = arg0->f108;
    if (q != 0) {
        q->refs = q->refs - 1;
        if (((unsigned long long)((long long)q->refs << 0x29) >> 0x29) == 0) igObject_Destroy(q);
    }
    arg0->f108 = 0;
}
