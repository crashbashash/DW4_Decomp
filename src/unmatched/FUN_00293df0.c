/* Copies a picture header's fields (+88, +92, the flag bytes +108..+110, +60, +64) into the eight-
 * word summary at +140 of the decoder, clearing its last word. */

struct Picture00293df0 {
    char pad0[60];
    int f60;            /* +60 */
    int f64;            /* +64 */
    char pad68[88 - 68];
    int structure;      /* +88 */
    int f92;            /* +92 */
    char pad96[108 - 96];
    signed char f108;   /* +108 */
    signed char f109;   /* +109 */
    signed char f110;   /* +110 */
};

struct Summary00293df0 {
    int structure; /* +0 */
    int f4;        /* +4 */
    int f8;        /* +8 */
    int f12;       /* +12 */
    int f16;       /* +16 */
    int f20;       /* +20 */
    int f24;       /* +24 */
    int f28;       /* +28 */
};

struct Decoder00293df0 {
    char pad0[140];
    struct Summary00293df0 summary; /* +140 */
};

void FUN_00293df0(struct Decoder00293df0 *decoder, struct Picture00293df0 *picture) {
    struct Summary00293df0 *summary = &decoder->summary;
    int f60 = picture->f60; /* read first: retail schedules this load ahead of the stores */

    summary->structure = picture->structure;
    summary->f4 = picture->f92;
    summary->f8 = picture->f108;
    summary->f12 = picture->f109;
    summary->f16 = picture->f110;
    summary->f20 = f60;
    summary->f24 = picture->f64;
    summary->f28 = 0;
}
