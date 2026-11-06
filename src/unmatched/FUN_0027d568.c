/* Parses seven hex digits text[0..6] (most significant first) into an integer through the digit-
 * value table DAT_004ba2b8 indexed by character; the inverse of FUN_0027d4d0. */
extern int DAT_004ba2b8[];

int FUN_0027d568(signed char *text) {
    int value;

    value = DAT_004ba2b8[text[0]];
    value = value * 16 + DAT_004ba2b8[text[1]];
    value = value * 16 + DAT_004ba2b8[text[2]];
    value = value * 16 + DAT_004ba2b8[text[3]];
    value = value * 16 + DAT_004ba2b8[text[4]];
    value = value * 16 + DAT_004ba2b8[text[5]];
    value = value * 16 + DAT_004ba2b8[text[6]];
    return value;
}

