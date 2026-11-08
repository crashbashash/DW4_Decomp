char *strrchr(const char *string, int character) {
    const char *last = 0;
    char wanted = character;

    while (*string) {
        if (*string == wanted) {
            last = string;
        }
        string++;
    }
    if (*string == wanted) {
        last = string;
    }
    return (char *)last;
}
