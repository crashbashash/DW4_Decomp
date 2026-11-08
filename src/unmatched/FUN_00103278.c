typedef struct {
    unsigned int b0 : 1;
    unsigned int b1 : 1;
    unsigned int b2 : 2;
    unsigned int b4 : 4;
    unsigned int b8 : 1;
} Flags;
typedef struct {
    Flags f;
    int pad[7];
    int x20;
} Obj;
void FUN_00102c98(Obj *o);
void FUN_00103278(Obj *o) {
    FUN_00102c98(o);
    o->x20 = 0;
    o->f.b2 = 1;
    o->f.b0 = 0;
    o->f.b8 = 1;
}
