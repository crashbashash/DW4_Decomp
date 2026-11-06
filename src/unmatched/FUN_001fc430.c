/* The ternaries keep the zero/one constants in the branch delay slots, and the negated bit is an
 * unsigned char. */
extern unsigned int DAT_00562c70[4];
extern int DAT_00569330[4];
extern int DAT_0056b058[4];
int FUN_001fc430(int arg0, int arg1, int arg2) {
    int a6;
    int a5;
    int v;
    int v2;
    unsigned int w;
    unsigned int b;
    a5 = 0;
    if ((DAT_00562c70[DAT_00569330[0]] >> 23) & 1) {
        a5 = DAT_0056b058[0];
    }
    for (a6 = 0; a6 <= a5; a6++) {
        w = DAT_00562c70[a6];
        b = (w >> 1) & 1;
        if (arg1 == b) {
            v = arg2 != 0 ? ((w >> 10) & 1) : 0;
            if (v == 0) {
                goto b9;
            }
        }
        if (arg0 != 0) {
            arg0 = 0;
            break;
        }
b9:
        if (arg1 == b) {
            v2 = arg2 != 0 ? (unsigned char)!((w >> 10) & 1) : 1;
            if (v2 != 0 && arg0 == 0) {
                arg0 = 1;
                break;
            }
        }
    }
    return arg0;
}
