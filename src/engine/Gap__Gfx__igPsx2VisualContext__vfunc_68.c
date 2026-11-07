unsigned int Gap__Gfx__igPsx2VisualContext__vfunc_68(void *arg0) {
    unsigned int t = *(unsigned int *)((char *)arg0 + 956);
    unsigned int a = (t & 0x80000000) >> 7;
    return (t & 0xFFFFFF) | (a + (((t & 0xFF000000) - a) * 2));
}
