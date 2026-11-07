struct B { volatile signed char m : 7; unsigned char x : 1; };
struct S { char pad0[70]; volatile signed char f70 : 7; unsigned char x : 1; char f71; char f72; };
int FUN_0020b9d0();
extern struct S *DAT_0056c0e0[17];
extern unsigned int DAT_0056c128[4];
void FUN_0020c8b0(struct S *arg0) {
    int s1;
    unsigned int s0;
    struct S *o;
    if (arg0->f70 == 4 || arg0->f70 == 5 || arg0->f70 == 1) return;
    if (arg0->f72 != 0) {
        arg0->f72 = 0;
        FUN_0020b9d0(arg0);
        DAT_0056c128[0] &= ~1;
        s0 = DAT_0056c128[0];
        s1 = 0;
        while (s0 != 0) {
            s0 = s0 >> 1;
            s1 += 1;
            if (s0 & 1) {
                o = DAT_0056c0e0[s1];
                if (o != 0 && (((struct B *)((char *)o + 70))->m == 3 || ((struct B *)((char *)o + 70))->m == 2)) {
                    FUN_0020b9d0(o);
                }
            }
        }
        DAT_0056c128[0] = 0;
    }
}
