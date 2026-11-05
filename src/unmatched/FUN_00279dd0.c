/* 0x00279dd0 — FUN_00279dd0 (84 bytes). Sends request 11 with a one-word payload through FUN_00273820,
   unless the library is in mode 1 (0x004b1dc8) with no entries (0x004b1dc0). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern void FUN_00273820(int request, int *payload, int words, int a3, int t0);
extern int DAT_004b1dc0;
extern int DAT_004b1dc8;

void FUN_00279dd0(int value) {
    int payload;

    if (DAT_004b1dc8 != 1 || DAT_004b1dc0 > 0) {
        payload = value;
        FUN_00273820(11, &payload, 1, 0, 0);
    }
}
