/* Calls FUN_0010b918 with base and the address of the last byte of a length-byte span starting at
 * base. */
void FUN_0010b918(char *start, char *last);

void FUN_00260a40(char *base, int length) {
    FUN_0010b918(base, base + length - 1);
}
