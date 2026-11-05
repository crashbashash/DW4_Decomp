/* 0x0029f4b8 — FUN_0029f4b8 (152 bytes). Decodes one element of text with a FUN_0028da88 decoder and, when its flags carry 0x10000, returns word +12 of the FUN_0028d4a8 info through *out. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
void FUN_0028b750();
void FUN_0028d4a8();
void *FUN_0028da88();
int FUN_0028dc28();

/* Filled by FUN_0028d4a8; only +12 is read here. */
struct Info29f4b8 {
    int f0, f4, f8;
    int f12;
};

void FUN_0029f4b8(char *text, int length, int *out) {
    struct Info29f4b8 info;
    int consumed;
    int flags;
    void *decoder;

    decoder = FUN_0028da88();
    if (decoder != 0) {
        FUN_0028b750(decoder, text, length, &consumed, &flags);
        if (flags & 0x10000) {
            FUN_0028d4a8(decoder, &info);
            FUN_0028dc28(decoder);
            *out = info.f12;
        }
    }
}
