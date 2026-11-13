char *strcpy(char *dst, const char *src);
extern char *padStateString[8];
extern char text_empty_2[];

void scePadStateIntToStr(unsigned int state, char *str) {
    if (state < 8) {
        strcpy(str, padStateString[state]);
        return;
    }
    *str = text_empty_2[0];
}
