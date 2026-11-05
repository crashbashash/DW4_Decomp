/* 0x00275200 — FUN_00275200 (32 bytes). Stores three configuration bytes into 0x004ab440 and the word
   argument into 0x004ab444. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern char DAT_004ab440[3];
extern int DAT_004ab444;

void FUN_00275200(int b0, int b1, int b2, int word) {
    DAT_004ab440[0] = b0;
    DAT_004ab440[1] = b1;
    DAT_004ab440[2] = b2;
    DAT_004ab444 = word;
}
