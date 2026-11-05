/* 0x0027eb68 — FUN_0027eb68 (168 bytes). Resets the server-manager state: clears the 32-byte block at
   0x004bb020, the four 8-byte slots at 0x00570ba0 / 0x00570ba8 / 0x00570bc0 / 0x00570bc8, the six words
   at 0x004bb000 and the owner word 0x00570bb8. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern void *memset(void *dest, int value, unsigned int size);
extern int DAT_004bb000[6];
extern char DAT_004bb020[32];
extern char DAT_00570ba0[8];
extern char DAT_00570ba8[8];
extern int DAT_00570bb8;
extern char DAT_00570bc0[8];
extern char DAT_00570bc8[8];

void FUN_0027eb68(void) {
    int *word;
    int i;

    memset(DAT_004bb020, 0, sizeof(DAT_004bb020));
    memset(DAT_00570ba0, 0, sizeof(DAT_00570ba0));
    memset(DAT_00570ba8, 0, sizeof(DAT_00570ba8));
    memset(DAT_00570bc0, 0, sizeof(DAT_00570bc0));
    memset(DAT_00570bc8, 0, sizeof(DAT_00570bc8));
    word = DAT_004bb000;
    for (i = 0; i < 6; i++) {
        *word++ = 0;
    }
    DAT_00570bb8 = 0;
}
