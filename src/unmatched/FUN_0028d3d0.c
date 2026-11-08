unsigned char *FUN_0028d430(unsigned char *buf, int size, int code);

int FUN_0028d3d0(unsigned char *buf, int size) {
    unsigned char *p = FUN_0028d430(buf, size, 0xba);

    if (p == 0) {
        return 0;
    }
    p += 4;
    size -= p - buf;
    if (size <= 0) {
        return 0;
    }
    return (*p >> 6) == 0;
}
