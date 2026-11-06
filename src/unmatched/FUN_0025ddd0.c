/* Sets the decoder output buffer and its capacity in frames (bytes divided by the frame size from
 * f15, or by bytes-per-sample times f14 when f152 is non-zero) and clears the transfer counters. */
/* CRI ADX decoder block, limited to the fields this function touches. */
typedef struct DecoderBlock {
    short f0;
    short state;
    char f4[8];
    signed char f12;
    signed char f13;
    signed char f14;
    signed char f15;
    int f16;
    int f20;
    int f24;
    short f28;
    short f30;
    int f32;
    short f36;
    short f38;
    int f40;
    int f44;
    int f48;
    int f52;
    char f56[4];
    int f60;
    int f64;
    int f68;
    int f72;
    int f76;
    int f80;
    int f84;
    int f88;
    int f92;
    int f96;
    int f100;
    char f104[12];
    int f116;
    char f120[16];
    int f136;
    int f140;
    int f144;
    int f148;
    short f152;
    unsigned short f154;
    short f156;
    short f158;
    unsigned short f160;
    unsigned short f162;
    unsigned short f164;
    char f166[78];
    int f244;
    int f248;
    void (*f252)(void *context, int count, int bytes);
    void *f256;
} DecoderBlock;

void FUN_0025ddd0(DecoderBlock *block, int buffer, int bytes) {
    if (block->f152 == 0) {
        block->f72 = buffer;
        block->f76 = bytes / block->f15;
        block->f116 = 0;
    } else {
        block->f72 = buffer;
        block->f76 = bytes / (block->f13 / 8 * block->f14);
        block->f116 = 0;
    }
    block->f144 = 0;
    block->f148 = 0;
    block->f248 = 0;
    block->f244 = 0;
}
