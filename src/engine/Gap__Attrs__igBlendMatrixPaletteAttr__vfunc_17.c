typedef struct Obj { char pad[20]; int f20; int f24; } Obj;

void Gap__Attrs__igBlendMatrixPaletteAttr__vfunc_17(Obj *arg0) {
    if (arg0->f24 == 0) {
        arg0->f24 = arg0->f20;
    }
}
