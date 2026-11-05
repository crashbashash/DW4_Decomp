int printf();
int FUN_001eb380();
int FUN_001eb3f0();
extern int DAT_00496600[];
extern int DAT_004e4bf8[4];
extern int DAT_004e5530[4];
extern int DAT_004e5550[4];
extern int DAT_004e5570[4];
extern int DAT_004e5590[4];
extern int DAT_004e55a8[4];
extern int DAT_004e55b8[4];
extern int DAT_0056b8e0[];
extern int DAT_0056ba18[4];
extern int DAT_0056ba1c[4];
extern int DAT_0056ba20[4];
extern int DAT_0056d678[4];
void FUN_0020e4a0(void) {
    int t3;
    int t1;
    int n;
    int m;
    int *p;
    int i;
    int k;
    int t2;
    int j;
    n = 0;
    printf(DAT_004e5530, DAT_0056ba18[0]);
    for (i = 0; i < DAT_0056ba18[0]; i++, n++) {
        p = &DAT_0056b8e0[n];
        t1 = FUN_001eb380(*p);
        printf(DAT_004e5550, n, *p, t1, FUN_001eb3f0(*p));
    }
    printf(DAT_004e5570, DAT_0056ba1c[0]);
    for (j = 0; j < DAT_0056ba1c[0]; j++, n++) {
        p = &DAT_0056b8e0[n];
        t2 = FUN_001eb380(*p);
        printf(DAT_004e5550, n, *p, t2, FUN_001eb3f0(*p));
    }
    printf(DAT_004e5590, DAT_0056ba20[0]);
    for (k = 0; k < DAT_0056ba20[0]; k++, n++) {
        p = &DAT_0056b8e0[n];
        t3 = FUN_001eb380(*p);
        printf(DAT_004e5550, n, *p, t3, FUN_001eb3f0(*p));
    }
    printf(DAT_004e55a8);
    m = 0;
    do {
        if (DAT_0056d678[0] & (1u << m)) {
            printf(DAT_004e55b8, DAT_00496600[m]);
        }
        m++;
    } while (m <= 9);
    printf(DAT_004e4bf8);
}
