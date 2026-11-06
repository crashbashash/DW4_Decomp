typedef struct Q { char pad4[4]; int f4; } Q;
int igObject_Destroy();
extern Q * DAT_0055f508[4];
void FUN_0013f730(void) {
    Q *p;

    p = DAT_0055f508[0];
    if (p != 0) {
        p->f4 -= 1;
        if ((p->f4 & 0x7fffff) == 0) {
            igObject_Destroy(p);
        }
    }
    DAT_0055f508[0] = 0;
}
