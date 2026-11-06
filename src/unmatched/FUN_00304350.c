typedef struct Q { char pad4[4]; int f4; } Q;
int igObject_Destroy();
extern Q * DAT_005871b0[4];
void FUN_00304350(Q *arg0) {
    Q *p;

    p = DAT_005871b0[0];
    if (p != 0) {
        p->f4 -= 1;
        if ((p->f4 & 0x7fffff) == 0) {
            igObject_Destroy(p);
        }
    }
    if (arg0 != 0) {
        arg0->f4 += 1;
    }
    DAT_005871b0[0] = arg0;
}
