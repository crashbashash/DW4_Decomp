/* 0x0029f800 — FUN_0029f800 (124 bytes). Returns text advanced past one element: by the decoder's consumed length when a FUN_0028da88 decoder exists, else by min(length, 6). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
void FUN_0028b750();
void *FUN_0028da88();
int FUN_0028dc28();

/* Returns text advanced past one element: by the decoder's length when available, else by min(length, 6). */
char *FUN_0029f800(char *text, int length) {
    void *decoder;
    int consumed;
    int flags;

    decoder = FUN_0028da88();
    if (decoder == 0) {
        return text + (length < 7 ? length : 6);
    }
    FUN_0028b750(decoder, text, length, &consumed, &flags);
    FUN_0028dc28(decoder);
    return text + consumed;
}
