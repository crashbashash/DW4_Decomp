extern const char _ctype_[];
#define CTYPE_UPPER 0x01
#define IS_UPPER(c) ((_ctype_ + 1)[(int)(c)] & CTYPE_UPPER)

char *strlwr(char *string) {
    char *result = string;

    while (*string != '\0') {
        int c = *string;

        if (IS_UPPER(c)) {
            *string = c - 'A' + 'a';
        }
        ++string;
    }
    return result;
}
