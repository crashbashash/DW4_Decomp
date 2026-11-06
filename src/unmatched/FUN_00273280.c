/* 0x00273280 — FUN_00273280 (112 bytes). Test RPC reply: fills the reply buffer with 0xAA bytes, then writes
   "Hello from EE (%d)" with the running counter 0x004a9b24 and advances the counter.
   Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern int sprintf(char *buffer, const char *format, ...);
extern volatile int DAT_004a9b24;
extern const char Hello_from_EE_d[];

void FUN_00273280(int unused, char *buffer, int size) {
    int i;

    for (i = 0; i < size; i++) {
        buffer[i] = 0xAA;
    }
    sprintf(buffer, Hello_from_EE_d, DAT_004a9b24);
    DAT_004a9b24++;
}
