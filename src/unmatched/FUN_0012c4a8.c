/* Lower-cases a character: adds 32 when the character-class table D_004d3d10 (indexed from c + 1)
 * marks it upper case (bit 0). The shape of tolower over newlib's _ctype_ (hypothesis). */
extern const char D_004d3d10[];    /* character-class table; entry c + 1 describes c (bit 0 upper, bit 1 lower) */

int FUN_0012c4a8(int c) {
    return ((D_004d3d10 + 1)[c] & 1) ? c + ('a' - 'A') : c;
}
