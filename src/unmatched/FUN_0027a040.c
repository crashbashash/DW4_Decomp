extern int DAT_004b1dc8;
extern int DAT_004b1dc0;
extern int DAT_004b1df0;
void FUN_0027a040(void *handle, int value) {
    if (DAT_004b1dc8 == 1 && DAT_004b1dc0 <= 0) {
        return;
    }
    if (*(signed char *)((char *)handle + 84) == value) {
        return;
    }
    if (DAT_004b1df0 == 0 && value == 1) {
        return;
    }
    *(signed char *)((char *)handle + 84) = value;
}
