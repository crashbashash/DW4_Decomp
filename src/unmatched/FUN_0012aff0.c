/* Returns the first occurrence of the needle string inside the haystack string, or 0. */
char *FUN_0012aff0(const char *haystack, const char *needle) {
    if (*haystack == 0) {
        if (*needle) {
            return 0;
        }
        return (char *)haystack;
    }
    while (*haystack) {
        unsigned int i;

        i = 0;
        while (1) {
            if (needle[i] == 0) {
                return (char *)haystack;
            }
            if (needle[i] != haystack[i]) {
                break;
            }
            i++;
        }
        haystack++;
    }
    return 0;
}
