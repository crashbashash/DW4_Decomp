/* 0x00285e98 — FUN_00285e98 (172 bytes). Derives the decoder geometry: full width/height from the low (+4/+8) and extension (+80/+84, <<12) fields, macroblock counts (16-pixel; 32-line pairs doubled for structure 3 when not progressive), and the padded sizes and halves. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */

/* Members of the decoder object used here (MPEG-style geometry; roles inferred from the arithmetic). */
struct Decoder00285e98 {
    char pad0[4];
    int width; /* +4 */
    int height; /* +8 */
    char pad12[60];
    int progressive; /* +72 */
    char pad76[4];
    int widthExt; /* +80 */
    int heightExt; /* +84 */
    char pad88[192];
    int structure; /* +280 */
    char pad284[424];
    int fullWidth; /* +708 */
    int fullHeight; /* +712 */
    int mbWidth; /* +716 */
    int mbHeight; /* +720 */
    char pad724[224];
    int paddedWidth; /* +948 */
    int paddedHeight; /* +952 */
    int halfWidth; /* +956 */
    int halfHeight; /* +960 */
};

void FUN_00285e98(struct Decoder00285e98 *d) {
    int width = (d->widthExt << 12) | d->width;
    int height = (d->heightExt << 12) | d->height;

    d->mbWidth = (unsigned int)(width + 15) >> 4;
    d->fullWidth = width;
    d->fullHeight = height;
    if (d->progressive == 1) {
        d->mbHeight = (unsigned int)(height + 15) >> 4;
    } else if (d->structure == 3) {
        d->mbHeight = ((unsigned int)(height + 31) >> 5) * 2;
    } else {
        d->mbHeight = (unsigned int)(height + 31) >> 5;
    }
    d->paddedWidth = d->mbWidth * 16;
    d->paddedHeight = d->mbHeight * 16;
    d->halfWidth = d->paddedWidth >> 1;
    d->halfHeight = d->paddedHeight >> 1;
}
