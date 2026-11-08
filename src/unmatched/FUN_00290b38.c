unsigned char *FUN_0028de10(unsigned char *data, int size, int code);
int FUN_00291420(void);
int FUN_0028dc78(unsigned char *p);

int FUN_00290b38(unsigned char *data, int size) {
    unsigned char *p = FUN_0028de10(data, size, 64);

    if (p == 0) {
        return 0;
    }
    if (FUN_00291420() != 0) {
        return 1;
    }
    p += 4;
    size -= p - data;
    if (size <= 0) {
        return 0;
    }
    p = FUN_0028de10(p, size, -1);
    if (p == 0) {
        return 0;
    }
    if (FUN_0028dc78(p) & 0x10) {
        return 0;
    }
    return 1;
}
