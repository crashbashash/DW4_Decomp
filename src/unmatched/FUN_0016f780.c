/* matching construct: 48-variant sweep — declaration order */
void FUN_0016f780(unsigned char *dst, unsigned short *src, int count)
{
    unsigned char *d = dst + count * 3 - 3;
    unsigned short *s = src + count - 1;
    int i;
    unsigned int px;

    for (i = 0; i < count; i++) {
        px = *s;
        d[0] = (px & 0x1F) << 3;
        d[1] = (px >> 3) & 0xFC;
        d[2] = (px >> 8) & 0xF8;
        s--;
        d -= 3;
    }
}
