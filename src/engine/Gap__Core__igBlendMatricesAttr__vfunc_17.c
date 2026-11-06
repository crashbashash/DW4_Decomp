typedef struct Obj { char pad[16]; int f16; int f20; } Obj;

void Gap__Core__igBlendMatricesAttr__vfunc_17(Obj *arg0) {
    if (arg0->f20 == 0) {
        arg0->f20 = arg0->f16;
    }
}
