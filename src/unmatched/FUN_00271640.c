/* 0x00271640 — FUN_00271640 (48 bytes). Clears the 56-byte block DAT_004a9288 with memset after a discarded read of the word that follows it (DAT_004a92c0). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
/* The read of DAT_004a92c0 survives -O2 with its value unused: it is volatile. */
extern volatile int DAT_004a92c0;
extern char DAT_004a9288[56];
void *memset(void *dst, int value, unsigned int size);

void FUN_00271640(void) {
    DAT_004a92c0;
    memset(DAT_004a9288, 0, sizeof(DAT_004a9288));
}
