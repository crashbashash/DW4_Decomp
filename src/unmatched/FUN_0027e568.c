/* Formats two numbers into buf as "<first> <second>": FUN_0027e458 (decimal conversion with a size
 * limit) for each, separated by a space appended with strncat (strncat-shaped). */
unsigned int strlen(const char *);
char *strncat(char *dst, const char *src, unsigned int n);
void FUN_0027e458(long value, char *buf, long size);

extern char DAT_004f25c0[]; /* " " */

void FUN_0027e568(long first, long second, char *buf, long size) {
    char *end;

    FUN_0027e458(first, buf, size);
    strncat(buf, DAT_004f25c0, (int)size - strlen(buf) - 1);
    end = buf + strlen(buf);
    FUN_0027e458(second, end, 4 - strlen(buf));
}
