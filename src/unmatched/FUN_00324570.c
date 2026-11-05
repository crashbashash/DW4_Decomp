typedef struct H { unsigned a : 5; unsigned size : 19; unsigned b : 7; unsigned flag : 1; unsigned w4; unsigned s2 : 12; unsigned c : 4; } H;

unsigned int FUN_00324570(int arg0, char *arg1) {
    H *hdr;

    hdr = (H *)(arg1 - 4);
    if (hdr->flag == 1) {
        hdr = (H *)(arg1 - 0xC);
    }
    if (hdr == 0) {
        return 0;
    }
    if (hdr->flag == 0) {
        return hdr->size;
    }
    return hdr->size + (hdr->s2 << 0x13);
}
