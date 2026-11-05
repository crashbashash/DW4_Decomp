/* 0x00285f48 — FUN_00285f48 (80 bytes). Chooses the decoder mode at +56: 1 for progressive or field-structured (1/2) pictures, otherwise 3 when +308 is 1, else 2. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */

/* Members of the decoder object used here. */
struct Decoder00285f48 {
    char pad0[56];
    int mode; /* +56 */
    char pad60[12];
    int progressive; /* +72 */
    char pad76[204];
    int structure; /* +280 */
    char pad284[24];
    int f308; /* +308 */
};

void FUN_00285f48(struct Decoder00285f48 *d) {
    if (d->progressive == 1 || d->structure == 1 || d->structure == 2) {
        d->mode = 1;
    } else if (d->f308 == 1) {
        d->mode = 3;
    } else {
        d->mode = 2;
    }
}
