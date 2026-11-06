/* Returns the length of the leading run of the string that contains none of the reject characters. */
unsigned int FUN_0012a710(const char *string, const char *reject) {
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
