long strtol(const char *s, char **end, int base);

int atoi(const char *s)
{
    return (int)strtol(s, 0, 10);
}
