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
void FUN_00102c98(Obj *o);
unsigned int FUN_00102d90(unsigned int a);
void FUN_001032c0(Obj *o, unsigned int a, int b) {
    unsigned int t = FUN_00102d90(a);
    FUN_00102c98(o);
    if (o->x10 != 0xFFFFFFFF) o->x10 = t;
    o->x20 = b;
    o->f.b2 = 0;
    o->f.b0 = 0;
    o->f.b8 = 1;
}
