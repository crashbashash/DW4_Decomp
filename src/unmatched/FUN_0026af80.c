/* Formats a file reference as "%08x.%08x" (offset, size rounded up to 2048-byte sectors) and
 * passes that name with the third argument to FUN_002618c0. */
extern char text_08x_08x[]; /* '%08x.%08x' */
int sprintf(char *buffer, const char *format, ...);
int FUN_002618c0(const char *name, int arg);

void FUN_0026af80(int offset, unsigned int size, int arg) {
    char name[32];

    sprintf(name, text_08x_08x, offset, (size + 2047) >> 11);
    FUN_002618c0(name, arg);
}
