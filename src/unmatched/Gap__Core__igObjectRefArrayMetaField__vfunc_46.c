int igObject_IsAlikeDeep();
struct S { char p[8]; int off; char q[56]; int n; };
int Gap__Core__igObjectRefArrayMetaField__vfunc_46(struct S *arg0, int arg1, int arg2) {
    int i;
    for (i = 0; i < arg0->n; i++) {
        int a = *(int *)(arg1 + arg0->off + i * 4);
        int b = *(int *)(arg2 + arg0->off + i * 4);
        if (a != b) {
            if (a == 0 || b == 0) {
                return 0;
            }
            if (!(igObject_IsAlikeDeep(a, b) & 0xFF)) {
                return 0;
            }
        }
    }
    return 1;
}
