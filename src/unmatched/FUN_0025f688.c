#define SWAP16(x) (((x) >> 8) | (((x) << 8) & 0xFF00))

int FUN_0025f688(unsigned char *hdr, int size, short *out) {
    const unsigned short *words = (const unsigned short *)hdr;
    if (size < 18) {
        return -1;
    }
    if ((unsigned short)SWAP16(words[0]) != 0x8000) {
        return -2;
    }
    if ((short)((words[1] << 8) & 0xFF00 | hdr[3]) < 14) {
        return -1;
    }
    *out = SWAP16(words[8]);
    return 0;
}
