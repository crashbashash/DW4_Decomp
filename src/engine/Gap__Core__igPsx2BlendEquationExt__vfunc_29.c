typedef struct Obj { char pad[24]; int f24; } Obj;

void Gap__Core__igPsx2BlendEquationExt__vfunc_29(Obj *arg0, int arg1) {
    if ((arg1 != 0) && (arg0->f24 == 0)) {
        arg0->f24 = arg1;
    }
}
