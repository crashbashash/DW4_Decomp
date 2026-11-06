/* Formats a file reference as "%08x.%08x" (offset, size rounded up to 2048-byte sectors) and
 * passes that name with the first argument to FUN_00263980. */
extern char text_08x_08x[]; /* '%08x.%08x' */
int sprintf(char *buffer, const char *format, ...);
int FUN_00263980(int owner, const char *name);

void FUN_0026af30(int owner, int offset, unsigned int size) {
    char name[32];

    sprintf(name, text_08x_08x, offset, (size + 2047) >> 11);
    FUN_00263980(owner, name);
}
