typedef struct R { int w0; int refs; } R;
int FUN_00140ad0();
int igObject_Destroy();

void FUN_00141190(int *arg0, int arg1) {
    int i;
    R *p;
    if (arg1 == 1) {
        for (i = 0; i < 6; i++) {
            p = (R *)arg0[18 + i];
            if (p != 0) {
                if (p != 0) {
                    p->refs = p->refs - 1;
                    if (((unsigned long long)((long long)p->refs << 0x29) >> 0x29) == 0) {
                        igObject_Destroy(p);
                    }
                }
                arg0[18 + i] = 0;
            }
        }
    } else if (arg1 == 2) {
        FUN_00140ad0(arg0, 0, 0);
    }
}
