/* Aligned stack allocation with a repeated null check. */
struct S { char p[112]; unsigned short f112; char q[14]; int f128; int f132; int *f136; unsigned char f140; };
int Gap__Core__igStackMemoryPool__vfunc_53(struct S *arg0) {
    int temp_a1_2;
    int temp_a2;
    int temp_a3;
    int temp_a4;
    int temp_v1;
    unsigned short temp_a1;

    if (arg0->f140 == 0) {
        return 0;
    }
    temp_a3 = arg0->f128;
    if (temp_a3 == 0) {
        return 0;
    }
    if (temp_a3 == 0) {
        return 0;
    }
    temp_a1 = arg0->f112;
    temp_a2 = arg0->f132;
    temp_a4 = temp_a1 - 1;
    temp_v1 = temp_a4 & (temp_a1 - (temp_a2 & temp_a4));
    temp_a1_2 = temp_a3 + temp_v1;
    if (((int)arg0->f136 - temp_a2) < temp_a1_2) {
        return 0;
    }
    arg0->f132 = temp_a2 + temp_a1_2;
    *arg0->f136 = temp_a1_2;
    arg0->f136 = arg0->f136 - 1;
    return temp_a2 + temp_v1;
}
