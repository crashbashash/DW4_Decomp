typedef struct B { char p0[8]; float x0, y0, z0, x1, y1, z1; } B;
int FUN_0018ffa0();
int FUN_0018b350(B *arg0, B *arg1) {
    if (!(arg0->x0 <= arg0->x1) || !(arg1->x0 <= arg1->x1)) {
        return 0;
    }
    if (FUN_0018ffa0(arg0, arg1) != 0) {
        if (arg0->x0 <= arg1->x0) {
            if (!(arg0->x1 < arg1->x1) && (arg0->y0 <= arg1->y0) && !(arg0->y1 < arg1->y1) && (arg0->z0 <= arg1->z0) && !(arg0->z1 < arg1->z1)) {
                return 2;
            }
        }
        return 1;
    }
    return 0;
}
