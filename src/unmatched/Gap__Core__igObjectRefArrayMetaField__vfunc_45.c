int igObject_IsAlikeExactly();
struct M { char pad[8]; int f8; char pad2[56]; int f68; };
int Gap__Core__igObjectRefArrayMetaField__vfunc_45(struct M *arg0, int arg1, int arg2) {
    int i;
    int off;
    int a;
    int b;
    for (i = 0; i < arg0->f68; i++) {
        off = arg0->f8;
        a = *(int *)(arg1 + off + i * 4);
        b = *(int *)(arg2 + off + i * 4);
        if (a != b) {
            if (a == 0 || b == 0) {
                return 0;
            }
            if (!(igObject_IsAlikeExactly(a, b) & 0xFF)) {
                return 0;
            }
        }
    }
    return 1;
}
