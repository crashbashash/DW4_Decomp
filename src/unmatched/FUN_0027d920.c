int DTX_CallUrpc();
extern int sjrmt_sbuf[4];
void FUN_0027d920(int arg0) {
    sjrmt_sbuf[0] = arg0;
    DTX_CallUrpc(0x25, &sjrmt_sbuf[0], 1, 0, 0);
}
