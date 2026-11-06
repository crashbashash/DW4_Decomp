typedef struct Obj { char pad[24]; int f24; } Obj;

void FUN_0016e180(Obj *arg0, int arg1) {
    if ((arg1 != 0) && (arg0->f24 == 0)) {
        arg0->f24 = arg1;
    }
}
