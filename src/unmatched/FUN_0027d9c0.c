/* 0x0027d9c0 — FUN_0027d9c0 (76 bytes). Packs two words and a two-word pair into the shared send buffer and issues request 0x27 through FUN_00273820. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_00273820();
extern int DAT_005707c0[4]; /* request send buffer shared by the 0x0027d... wrappers */

void FUN_0027d9c0(int arg0, int arg1, int *pair) {
    int first = pair[0]; /* read before the buffer stores, as retail schedules it */

    DAT_005707c0[0] = arg0;
    DAT_005707c0[1] = arg1;
    DAT_005707c0[2] = first;
    DAT_005707c0[3] = pair[1];
    FUN_00273820(0x27, DAT_005707c0, 4, 0, 0);
}
