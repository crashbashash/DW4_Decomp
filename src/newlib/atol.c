int strtol(const char *s, char **end, int base);

int atol(const char *s)
{
    return strtol(s, 0, 10);
}
