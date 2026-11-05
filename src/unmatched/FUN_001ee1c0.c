typedef struct N { long long w0; int pad8[3]; struct N *next; int f24; unsigned char b0:1, b1:1, b2:1; } N;
int FUN_00204240();
extern N *DAT_00568e58[4];
N *FUN_001ee1c0(void) {
    N *o;
    if (DAT_00568e58[0] == 0) {
        FUN_00204240(0xD, &DAT_00568e58[0]);
    }
    o = DAT_00568e58[0];
    DAT_00568e58[0] = o->next;
    o->w0 = 0;
    o->f24 = 0;
    o->b1 = 1;
    o->b2 = 0;
    return o;
}
