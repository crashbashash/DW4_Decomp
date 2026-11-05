/* 0x002a6010 — FUN_002a6010 (52 bytes). Fills a record from a five-word source plus two caller values (+16, +32). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct SfdFive {
    int f0;
    int f4;
    int f8;
    int f12;
    int f16;
} SfdFive;

typedef struct SfdRecord {
    int f0;
    int f4;
    int f8;
    int f12;
    int f16;
    int f20;
    int pad24[2];
    int f32;
} SfdRecord;

void FUN_002a6010(SfdRecord *out, int a, SfdFive *src, int b) {
    /* matching construct: statement-order sweep — src->f16 is read before the copies */
    int fifth = src->f16;

    out->f0 = src->f0;
    out->f4 = src->f4;
    out->f8 = src->f8;
    out->f12 = src->f12;
    out->f20 = fifth;
    out->f16 = a;
    out->f32 = b;
}
