/* 0x0029fbc8 — FUN_0029fbc8 (208 bytes). Scans for the first valid frame header (0xFF, 0xF8 sync, then FUN_0029fc98 checks) and returns its position, or 0. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
void FUN_0029fc98();

/* Frame header fields unpacked by FUN_0029fc98 from an 0xFFFx sync word (layout of an MPEG audio
 * header: f0 version, f2 bitrate index with 15 invalid, f3 sample-rate index with 3 reserved). */
struct FrameHeader {
    unsigned char f0, f1, f2, f3, f4, f5, f6, f7, f8, f9, f10;
};

/* Returns the first position of a valid frame header in the next `remaining` bytes, or 0. */
unsigned char *FUN_0029fbc8(struct FrameHeader *header, unsigned char *p, int remaining) {
    for (; remaining >= 4; remaining--, p++) {
        if (p[0] == 0xFF && (p[1] & 0xF8) == 0xF8) {
            FUN_0029fc98(header, p);
            if (header->f0 != 0 && header->f2 != 15 && header->f3 != 3) {
                return p;
            }
        }
    }
    return 0;
}
