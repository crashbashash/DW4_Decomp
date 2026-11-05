/* 0x002907f0 — FUN_002907f0 (164 bytes). Advances a (pointer, remaining, offset) cursor to the next start code found by FUN_0028de10 and returns its FUN_0028dc78 class; with none found the whole remainder is skipped and 0 returned. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
unsigned char *FUN_0028de10(unsigned char *data, int size, int code);
int FUN_0028dc78(unsigned char *p);

int FUN_002907f0(unsigned char **data, int *remaining, int *offset) {
    unsigned char *found;
    int skip;
    int type;

    found = FUN_0028de10(*data, *remaining, -1);
    type = 0;
    if (found == 0) {
        skip = *remaining;
    } else {
        type = FUN_0028dc78(found);
        skip = found - *data;
    }
    *remaining -= skip;
    *data += skip;
    *offset += skip;
    return type;
}
