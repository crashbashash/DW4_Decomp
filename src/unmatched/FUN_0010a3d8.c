/* The incoming argument is forwarded as the first argument, so the constant pointer goes in a1
 * rather than a0. */
int FUN_00109b10();
extern int DAT_004d2358[4];
void FUN_0010a3d8(int self) {
    FUN_00109b10(self, &DAT_004d2358[0]);
}
