/* Packs two words and a two-word pair into the shared send buffer and issues request 0x27 through
 * DTX_CallUrpc. */
int DTX_CallUrpc();
extern int sjrmt_sbuf[4]; /* request send buffer shared by the 0x0027d... wrappers */

void FUN_0027d9c0(int arg0, int arg1, int *pair) {
    int first = pair[0];

    sjrmt_sbuf[0] = arg0;
    sjrmt_sbuf[1] = arg1;
    sjrmt_sbuf[2] = first;
    sjrmt_sbuf[3] = pair[1];
    DTX_CallUrpc(0x27, sjrmt_sbuf, 4, 0, 0);
}
