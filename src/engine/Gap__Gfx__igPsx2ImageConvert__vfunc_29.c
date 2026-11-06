/* Swaps the red and blue 5-bit fields of n little-endian 16-bit RGB565 pixels in place (bits 0..4
 * <-> bits 11..15, green kept). */
void Gap__Gfx__igPsx2ImageConvert__vfunc_29(void *arg0, unsigned char *p, int n) {
    unsigned int t; /* matching construct: permuter — the assembled pixel word is declared at function scope, the other temporaries inside the loop; the unit compiler (combat build) colours the registers as retail only this way */
    int i;
    for (i = 0; i < n; i++) {
        unsigned int v, hi, lo;
        hi = p[1];
        lo = p[0];
        hi = hi << 8;
        t = lo | hi;
        v = ((t & 0x1F) << 11) | (((t & 0xF800) >> 11) | (t & 0x7E0));
        p[0] = v;
        p[1] = (v & 0xFF00) >> 8;
        p += 2;
    }
}
