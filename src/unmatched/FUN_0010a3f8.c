/* The incoming argument is forwarded as the first argument, so the constant pointer goes in a1
 * rather than a0. */
int _sceMpegMessage();
extern int DAT_004d23a0[4];
void FUN_0010a3f8(int self) {
    _sceMpegMessage(self, &DAT_004d23a0[0]);
}
