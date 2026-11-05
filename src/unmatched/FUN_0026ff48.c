/* 0x0026ff48 — FUN_0026ff48 (100 bytes). Copies the string DAT_0056e420 (with its terminator) into dst, or stores an empty string when it is empty. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern char DAT_0056e420[];
unsigned int strlen(const char *s);
void *memcpy(void *dst, const void *src, unsigned int n);

void FUN_0026ff48(char *dst) {
    unsigned int length = strlen(DAT_0056e420);

    if (DAT_0056e420[0] == 0) {
        dst[0] = 0;
        return;
    }
    memcpy(dst, DAT_0056e420, length + 1);
}
