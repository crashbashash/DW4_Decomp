typedef struct Obj { char pad[20]; int f20; int f24; } Obj;

void FUN_001429d0(Obj *arg0) {
    if (arg0->f24 == 0) {
        arg0->f24 = arg0->f20;
    }
}
