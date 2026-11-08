/* Parses the two ASCII digits at +16/+17 of a header record as a decimal number (atoi);
 * returns 0 for a null record or a negative index. */
struct Chars2 {
    char c[2];
};

struct Header {
    char pad0[16];
    struct Chars2 digits; /* +16 */
};

int atoi(struct Chars2 *text);

int FUN_002b52d8(struct Header *header, int index) {
    struct Chars2 digits;

    if (header == 0 || index < 0) {
        return 0;
    }
    digits = header->digits;
    return atoi(&digits);
}
