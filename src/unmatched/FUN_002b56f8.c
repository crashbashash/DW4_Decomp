/* Copies the three characters at base+offset and converts them as a hexadecimal number through
 * FUN_002b5758; returns 0 for a null base or a negative index. */
struct Chars3 {
    char c[3];
};

long FUN_002b5758(struct Chars3 *text, char **end, int radix);

int FUN_002b56f8(char *base, int index, int offset) {
    struct Chars3 digits;
    char *end;

    if (base == 0 || index < 0) {
        return 0;
    }
    digits = *(struct Chars3 *)(base + offset);
    return FUN_002b5758(&digits, &end, 16);
}
