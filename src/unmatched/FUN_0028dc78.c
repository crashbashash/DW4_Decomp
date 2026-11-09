int FUN_0028dc78(const unsigned char *p) {
    unsigned int code = p[0];
    int type;
    code <<= 8;
    code |= p[1];
    code <<= 8;
    code |= p[2];
    code <<= 8;
    code |= p[3];
    if (code == 0x100) {
        type = 4;
    } else if (code == 0x101) {
        type = 3;
    } else if (code - 0x102 < 0xAE) {
        type = 1;
    } else if (code == 0x1B2) {
        type = 32;
    } else if (code == 0x1B3) {
        type = 64;
    } else if (code == 0x1B5) {
        type = 16;
    } else if (code == 0x1B7) {
        type = 128;
    } else if (code == 0x1B8) {
        type = 8;
    } else {
        type = 0;
    }
    return type;
}
