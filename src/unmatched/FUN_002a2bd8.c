/* 0x002a2bd8 — FUN_002a2bd8 (136 bytes). Resets a stream parameter block: handles and counters to 0, times to LONG_MAX/INT_MAX, unknown fields to -1. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
/* Stream parameter block reset to "unknown" values. */
struct Params {
    int handle;
    int f4;
    int f8;
    int pad12;
    long f16;
    long f24;
    int f32;
    int f36;
    int f40;
    int f44;
    int f48;
    int f52;
    int f56;
    int f60;
    int f64[68];
    int f336;
    int f340;
    int f344;
};

void FUN_002a2bd8(struct Params *params) {
    int i;

    params->handle = 0;
    params->f4 = 0;
    params->f8 = 0;
    params->f16 = 0x7FFFFFFFFFFFFFFF;
    params->f24 = 0x7FFFFFFFFFFFFFFF;
    params->f32 = 0;
    params->f36 = 0x7FFFFFFF;
    params->f40 = 0x7FFFFFFF;
    params->f44 = -1;
    params->f48 = -1;
    params->f52 = -1;
    params->f56 = -1;
    params->f60 = 0;
    for (i = 67; i >= 0; i--) {
        params->f64[i] = 0;
    }
    params->f336 = 0;
    params->f340 = 0;
    params->f344 = -1;
}
