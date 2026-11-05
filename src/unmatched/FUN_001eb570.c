struct E { char pad[44]; int f2c; char pad2[16]; };
int FUN_00330770();
extern int DAT_00568da0[4];
extern struct E DAT_00562da0[];
void FUN_001eb570(void) {
    int i;
    int *pf;
    for (i = 0; i <= DAT_00568da0[0]; i++) {
        pf = &DAT_00562da0[i].f2c;
        if (*pf != 0) {
            FUN_00330770(*pf, 6);
            *pf = 0;
        }
    }
}
