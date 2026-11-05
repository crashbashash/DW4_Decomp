int igObject_IsAlikeShallow();
struct O { char p0[8]; int f8; char p1[56]; int f68; };

int Gap__Core__igObjectRefArrayMetaField__vfunc_47(struct O *arg0, int arg1, int arg2) {
    int i;
    int a;
    int b;

    for (i = 0; i < arg0->f68; i++) {
        a = *(int *)(arg1 + arg0->f8 + i * 4);
        b = *(int *)(arg2 + arg0->f8 + i * 4);
        if (a != b) {
            if ((a == 0) || (b == 0)) {
                return 0;
            }
            if (!(igObject_IsAlikeShallow(a, b) & 0xFF)) {
                return 0;
            }
        }
    }
    return 1;
}
