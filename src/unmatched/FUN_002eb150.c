int FUN_0030cfa0();
int List_Reserve();
int List_Resize();
struct L { char pad[8]; int f8; int f12; };
struct O { char pad[16]; struct L *f16; struct L *f20; int f24; int f28; };
void FUN_002eb150(struct O *arg0) {
    struct L *a;
    a = arg0->f16;
    if (0 <= a->f12) {
        a->f8 = 0;
    } else {
        List_Resize(a, 0, 4);
    }
    a = arg0->f16;
    if (!(0 < a->f8)) {
        List_Reserve(a, 0, 4);
    }
    if (arg0->f20 != 0) {
        a = arg0->f20;
        if (0 <= a->f12) {
            a->f8 = 0;
        } else {
            List_Resize(a, 0, 4);
        }
        a = arg0->f20;
        if (!(0 < a->f8)) {
            List_Reserve(a, 0, 4);
        }
    }
    FUN_0030cfa0(arg0->f24);
    FUN_0030cfa0(arg0->f28);
}
