char *strpbrk(const char *string, const char *accept) {
    const char *candidate = accept;

    if (!*string) {
        return 0;
    }
    while (*string) {
        for (candidate = accept; *candidate; candidate++) {
            if (*string == *candidate) {
                break;
            }
        }
        if (*candidate) {
            break;
        }
        string++;
    }
    if (*candidate == '\0') {
        string = 0;
    }
    return (char *)string;
}
