/* newlib atoi(s). */
long FUN_0012c218(const char *s, char **end, int base);

int FUN_001236e8(const char *s)
{
    return (int)FUN_0012c218(s, 0, 10);
}
