int FUN_001143b0(unsigned char *dst, unsigned char *src, unsigned int size)
{
    unsigned int i;
    for (i = 0; i < size; i++) {
        *dst++ = *src++;
    }
    return 0;
}
