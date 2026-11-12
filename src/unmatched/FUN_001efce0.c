int p2RegisterPredicateName();
int FUN_00204240();
void p2PreviousFinishFuncDonePredicate(void);
extern int DAT_00490b60[4];
extern int DAT_004e4fe0[4];
extern int DAT_005691b8[4];
void FUN_001efce0(void) {
    DAT_005691b8[0] = 0;
    FUN_00204240(7, &DAT_005691b8[0]);
    if (DAT_00490b60[0] != 0) {
        p2RegisterPredicateName(p2PreviousFinishFuncDonePredicate, &DAT_004e4fe0[0]);
    }
}
