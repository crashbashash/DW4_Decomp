unsigned char *FUN_0025bc40(unsigned char *buf, int *sfreq, int *nch, int *bits,
                            int *nsmpl);

int FUN_0025c038(unsigned char *buf, int len, short *hdrlen, signed char *type, signed char *bits,
                 signed char *blklen, signed char *nch, int *sfreq, int *nsmpl, int *flag)
{
    int freq;
    int ch;
    int bps;
    int smpl;
    unsigned char *data;

    if (len < 4096) {
        *hdrlen = 0;
        return -1;
    }
    data = FUN_0025bc40(buf, &freq, &ch, &bps, &smpl);
    if (data == 0) {
        return -1;
    }
    *hdrlen = data - buf;
    if (*hdrlen <= 0) {
        return -1;
    }
    *sfreq = freq;
    *nch = ch;
    *bits = bps;
    *nsmpl = smpl;
    *type = -1;
    *blklen = *nch * *bits / 8;
    *flag = 1;
    return 0;
}
