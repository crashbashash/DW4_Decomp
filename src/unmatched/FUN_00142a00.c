typedef struct Obj { char pad[16]; int f16; int f20; } Obj;

void FUN_00142a00(Obj *arg0) {
    if (arg0->f20 == 0) {
        arg0->f20 = arg0->f16;
    }
}
