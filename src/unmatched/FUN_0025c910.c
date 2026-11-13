unsigned char *adxb_GetAuInfo(unsigned char *buf, int len, int *sfreq, int *nch, int *bits,
                            int *nsmpl, int *loop);

int FUN_0025c910(unsigned char *buf, int len, short *hdrlen, signed char *type, signed char *bits,
                 signed char *blklen, signed char *nch, int *sfreq, int *nsmpl, int *flag, int *loop)
{
    int freq;
    int ch;
    int bps;
    int smpl;
    unsigned char *data;

    if (len < 8) {
        *hdrlen = 0;
        return -1;
    }
    data = adxb_GetAuInfo(buf, len, &freq, &ch, &bps, &smpl, loop);
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
