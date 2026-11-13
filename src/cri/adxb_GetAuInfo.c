/* Sun/NeXT AU (".snd") header parse for ADXB format 4: reads the big-endian header words, sets the PCM format
 * (0 = 16-bit, 1 = 8-bit, 2 = 8-bit mu-law) and returns the start of the sample data. */
#define GET32(p) ((p)[0] | ((p)[1] << 8) | ((p)[2] << 16) | ((p)[3] << 24))
#define SWAP32(x) ((((x) >> 24) & 0xFF) | (((x) >> 8) & 0xFF00) | (((x) << 8) & 0xFF0000) | ((x) << 24))

unsigned char *adxb_GetAuInfo(unsigned char *buf, int len, int *sfreq, int *nch, int *bits, int *nsmpl,
                            int *fmt)
{
    unsigned char *p;
    unsigned int magic;
    unsigned int ofst;
    unsigned int size;
    unsigned int enc;
    int word;
    int ch;

    p = buf;
    magic = GET32(p);
    p += 4;
    if (magic != 0x0064732E && magic != 0x646E732E) {
        return 0;
    }
    ofst = GET32(p);
    ofst = SWAP32(ofst);
    p += 4;
    if (len < (int)ofst) {
        return 0;
    }
    size = GET32(p);
    size = SWAP32(size);
    p += 4;
    enc = GET32(p);
    enc = SWAP32(enc);
    p += 4;
    switch (enc) {
    case 1:
        *fmt = 2;
        *bits = 8;
        break;
    case 2:
        *fmt = 1;
        *bits = 8;
        break;
    case 3:
        *fmt = 0;
        *bits = 16;
        break;
    default:
        return 0;
    }
    *sfreq = GET32(p);
    p += 4;
    *sfreq = SWAP32(*sfreq);
    word = GET32(p);
    p += 4;
    ch = SWAP32(word);
    *nch = ch;
    if (*fmt == 2) {
        *nsmpl = (int)size / ch;
    } else if (*fmt == 1) {
        *nsmpl = (int)size / ch;
    } else if (*fmt == 0) {
        *nsmpl = (int)size / 2 / ch;
    } else {
        *nsmpl = 0x7FFF0000;
    }
    return buf + ofst;
}
