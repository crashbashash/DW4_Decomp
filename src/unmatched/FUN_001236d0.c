/* Converts a string through FUN_0012bf90 with no end pointer; the shape of atof over strtod
 * (hypothesis). */
void FUN_0012bf90(const char *s, char **end);

void FUN_001236d0(const char *s) {
    FUN_0012bf90(s, 0);
}
