/* 0x0026af80 — FUN_0026af80 (76 bytes). Formats a file reference as "%08x.%08x" (offset, size rounded up to 2048-byte sectors) and passes that name with the third argument to FUN_002618c0. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern char s_08x_08x_004ee4a0[]; /* '%08x.%08x' */
int sprintf(char *buffer, const char *format, ...);
int FUN_002618c0(const char *name, int arg);

void FUN_0026af80(int offset, unsigned int size, int arg) {
    char name[32];

    sprintf(name, s_08x_08x_004ee4a0, offset, (size + 2047) >> 11);
    FUN_002618c0(name, arg);
}
