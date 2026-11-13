char *strcpy(char *dst, const char *src);
extern char *padReqStateString[4];
extern char text_empty_2[];

void scePadReqIntToStr(unsigned int state, char *str) {
    if (state < 4) {
        strcpy(str, padReqStateString[state]);
        return;
    }
    *str = text_empty_2[0];
}
