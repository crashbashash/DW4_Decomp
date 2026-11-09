int FUN_0025f588(unsigned char *hdr, int len, short *ofst, signed char *type, signed char *bsize,
                 signed char *bits, signed char *nch, int *sfreq, int *nsmpl, int *blksmpl)
{
    if (len < 16) {
        return -1;
    }
    if ((hdr[1] | (hdr[0] << 8)) != 0x8000) {
        return -2;
    }
    *ofst = ((hdr[2] << 8) | hdr[3]) + 4;
    *type = hdr[4];
    *bits = hdr[5];
    *bsize = hdr[6];
    *nch = hdr[7];
    *sfreq = (hdr[8] << 24) | (hdr[9] << 16) | (hdr[10] << 8) | hdr[11];
    *nsmpl = (hdr[12] << 24) | (hdr[13] << 16) | (hdr[14] << 8) | hdr[15];
    if (*bsize == 0) {
        *blksmpl = 0;
    } else {
        *blksmpl = (*bits * 8 - 16) / *bsize;
    }
    return 0;
}
