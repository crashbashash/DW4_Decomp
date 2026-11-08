typedef struct { char pad[16]; unsigned int flags; void *a; int pad2; void *b; int c; int d; int e; } R;
typedef struct { char pad[20]; int a; int pad2; int b; int type; int c; int d; int e; } P;
P *FUN_0010dc00(int, unsigned int);
P *FUN_0010dbd0(int, unsigned int);
int FUN_0010d708(int, P *, int, int, int, int);
void FUN_00115cc8(int, void (*)(P *), P *);
void FUN_0010dd10(P *);
void FUN_0010dd50(R *r, int id) {
    P *p;
    if (r->flags & 4) {
        p = FUN_0010dc00(id, r->flags >> 16);
    } else {
        p = FUN_0010dbd0(id, r->flags);
    }
    p->a = (int)r->a;
    p->b = (int)r->b;
    p->type = 0x8000000c;
    p->c = r->c;
    p->d = r->d;
    p->e = r->e;
    if (FUN_0010d708(0x80000008, p, 64, r->c, r->d, r->e) == 0) {
        FUN_00115cc8(0x800, FUN_0010dd10, p);
    }
}
