/* Upper-cases a character: subtracts 32 when the character-class table (indexed from c + 1) marks
 * it lower case (bit 1). */
extern const char D_004d3d10[];    /* character-class table; entry c + 1 describes c (bit 0 upper, bit 1 lower) */

int FUN_0012c4c8(int c) {
    return ((D_004d3d10 + 1)[c] & 2) ? c - ('a' - 'A') : c;
}
