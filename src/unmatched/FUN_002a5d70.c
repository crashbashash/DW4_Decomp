/* Copies seven words and a signed byte of a source record into a compact output record. */
typedef struct SfdSource {
    char pad0[16];
    int f16;
    int f20;
    char pad24[4];
    int f28;
    int f32;
    int f36;
    int f40;
    int f44;
    char pad48[36];
    unsigned char f84;      /* +84 */
} SfdSource;

typedef struct SfdSummary {
    int f0;
    int f4;
    int f8;
    int f12;
    int f16;
    int f20;
    int f24;
    short f28;
    short f30;
} SfdSummary;

void FUN_002a5d70(SfdSource *src, SfdSummary *out) {
    out->f0 = src->f16;
    out->f4 = src->f28;
    out->f8 = src->f32;
    out->f12 = src->f36;
    out->f16 = src->f40;
    out->f20 = src->f44;
    out->f24 = src->f20;
    out->f28 = (signed char)src->f84;
    out->f30 = 0;
}
