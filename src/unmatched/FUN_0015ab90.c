/* matching construct: 24-variant sweep — statement and declaration order */
void FUN_0015ab90(unsigned char *dst, unsigned char *src, int count)
{
    int i;
    unsigned int packed;

    dst = dst + count - 1;
    src = src + ((count + 1) >> 1) - 1;
    i = 0;
    if (count & 1) {
        *dst = ((unsigned int)*src >> 4) & 0xF;
        i++;
        src--;
        dst--;
    }
    for (; i < count; i += 2) {
        packed = *src;
        dst[0] = (packed >> 4) & 0xF;
        dst[-1] = packed & 0xF;
        src--;
        dst -= 2;
    }
}
