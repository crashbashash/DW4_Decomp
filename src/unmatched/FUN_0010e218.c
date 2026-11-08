typedef struct P { char p0[12]; int f12; int pad16; int pad20; int pad24; int f28; int f32; int f36; int f40; int f44; int f48; int f52; char p1[4]; struct P *next; struct Q *q; } P;
typedef struct Q { int id; int busy; int pad; P *head; void *tail; } Q;
typedef struct { int pad[4]; int a16; void *a20; int pad24; void *a28; int a32; int a36; int a40; int a44; int a48; P *p; } R;
void FUN_0010bd90(int);
void FUN_0010e218(R *r) {
    P *p = r->p;
    Q *q = p->q;
    if (q->head == 0) {
        q->head = p;
    } else {
        ((P *)q->tail)->next = p;
    }
    q->tail = p;
    p->f32 = (int)r->a20;
    p->f28 = (int)r->a28;
    p->f36 = r->a32;
    p->f12 = r->a36;
    p->f40 = r->a40;
    p->f44 = r->a44;
    p->f48 = r->a48;
    p->f52 = r->a16;
    if (q->id >= 0 && q->busy == 0) {
        FUN_0010bd90(q->id);
    }
}
