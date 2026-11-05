struct R { char pad[564]; unsigned char a[16]; };
int FUN_001e74b0();
int FUN_001e7500();
extern int DAT_00560a08[8];
extern int DAT_00569330[4];
extern int DAT_00569340[4];
extern int * DAT_0056ad80[4];
void FUN_0017a8f0(struct R *arg0, int arg1, int arg2) {
    int n;
    int j;
    if (arg1 < 15) {
        n = arg1;
    } else {
        n = 15;
    }
    if (n < 8) {
        if (arg0->a[n] == (arg2 & 0xFF)) {
            DAT_00560a08[n] += 1;
        }
    }
    arg0->a[n] = arg2;
    if (n > 1) {
        j = n - 1;
    } else {
        j = 0;
    }
    DAT_00569330[0] = n;
    DAT_0056ad80[0] = &DAT_00569340[j * 112];
    if (arg2 != 0) {
        FUN_001e74b0(1, n);
    } else {
        FUN_001e7500(1, n);
    }
    DAT_00569330[0] = 0;
    DAT_0056ad80[0] = DAT_00569340;
}
