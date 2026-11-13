/* The incoming argument is forwarded as the first argument, so the constant pointer goes in a1
 * rather than a0. */
int _sceMpegMessage();
extern int DAT_004d2388[4];
void FUN_0010a3e8(int self) {
    _sceMpegMessage(self, &DAT_004d2388[0]);
}
