/* Converts a decimal string through FUN_0012c218 with no end pointer; the shape of atoi over
 * strtol (hypothesis). */
int FUN_0012c218(const char *s, char **end, int base);

int FUN_00123710(const char *s) {
    return FUN_0012c218(s, 0, 10);
}
