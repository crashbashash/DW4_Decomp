unsigned int strcspn(const char *string, const char *reject) {
    const char *start = string;
    const char *candidate;

    while (*string) {
        for (candidate = reject; *candidate; candidate++) {
            if (*string == *candidate) {
                break;
            }
        }
        if (*candidate) {
            break;
        }
        string++;
    }
    return string - start;
}
