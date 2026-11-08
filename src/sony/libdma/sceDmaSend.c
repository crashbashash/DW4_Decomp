typedef struct {
    unsigned int b0 : 1;
    unsigned int b1 : 1;
    unsigned int b2 : 2;
    unsigned int b4 : 4;
    unsigned int b8 : 1;
} Flags;
typedef struct {
    Flags f;
    int pad[3];
    unsigned int x10;
    int pad2[3];
    int x20;
    int pad3[3];
    unsigned int x30;
} Obj;
void WaitDma(Obj *o);
unsigned int FUN_00102d90(unsigned int a);

void sceDmaSend(Obj *o, unsigned int a) {
    unsigned int t = FUN_00102d90(a);
    WaitDma(o);
    if (o->x30 != 0xFFFFFFFF) o->x30 = t;
    o->x20 = 0;
    o->f.b2 = 1;
    o->f.b0 = 1;
    o->f.b8 = 1;
}
