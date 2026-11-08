double strtod(const char *s, char **end);

double atof(const char *s)
{
    return strtod(s, 0);
}
